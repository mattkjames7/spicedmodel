#!/usr/bin/env bash

set -euo pipefail

usage() {
  cat <<'EOF'
Usage: ./container-build.sh [x86_64|aarch64]

Build and repair one Python-independent manylinux_2_28 wheel. The architecture
defaults to the Docker host architecture. Cross-architecture builds require
Docker's corresponding binfmt/QEMU support.

Outputs:
  dist/*.whl       Unrepaired Linux wheel
  wheelhouse/*.whl Repaired manylinux wheel
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

case "${1:-$(uname -m)}" in
  x86_64|amd64)
    ARCH="x86_64"
    PLATFORM="linux/amd64"
    ;;
  aarch64|arm64)
    ARCH="aarch64"
    PLATFORM="linux/arm64"
    ;;
  *)
    echo "Unsupported architecture: ${1:-$(uname -m)}" >&2
    usage >&2
    exit 1
    ;;
esac

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
if command -v git >/dev/null 2>&1; then
  REPO_ROOT="$(git -C "${SCRIPT_DIR}" rev-parse --show-toplevel 2>/dev/null || echo "${SCRIPT_DIR}")"
else
  REPO_ROOT="${SCRIPT_DIR}"
fi

if [[ ! -f "${REPO_ROOT}/pyproject.toml" || ! -f "${REPO_ROOT}/CMakeLists.txt" ]]; then
  echo "Could not identify the spicedmodel repository root: ${REPO_ROOT}" >&2
  exit 1
fi

IMAGE="quay.io/pypa/manylinux_2_28_${ARCH}:latest"

echo "Building ${ARCH} wheel with ${IMAGE}"
echo "Repository root: ${REPO_ROOT}"

rm -rf "${REPO_ROOT}/dist" "${REPO_ROOT}/wheelhouse"
mkdir -p "${REPO_ROOT}/dist" "${REPO_ROOT}/wheelhouse"

docker run --rm \
  --platform "${PLATFORM}" \
  -e AUDITWHEEL_PLAT="manylinux_2_28_${ARCH}" \
  -e HOST_UID="$(id -u)" \
  -e HOST_GID="$(id -g)" \
  -v "${REPO_ROOT}:/io" \
  -w /io \
  "${IMAGE}" \
  /bin/bash -lc '
    set -euo pipefail

    # The interpreter is only a build frontend. wheel.py-api="py3" ensures
    # that neither its Python version nor its ABI appears in the wheel tag.
    PYTHON=/opt/python/cp314-cp314/bin/python
    "${PYTHON}" -m pip install --upgrade build
    "${PYTHON}" -m build --wheel --outdir /tmp/dist /io
    cp /tmp/dist/*.whl /io/dist/
    auditwheel repair --plat "${AUDITWHEEL_PLAT}" /tmp/dist/*.whl \
      --wheel-dir /io/wheelhouse
    chown -R "${HOST_UID}:${HOST_GID}" /io/dist /io/wheelhouse || true
  '

echo "Done. Repaired wheel:"
ls -1 "${REPO_ROOT}/wheelhouse"/*.whl
