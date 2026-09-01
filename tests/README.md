# Tests

The tests intentionally exercise an installed wheel, not the source tree.

From the repository, build the distributions:

```sh
python3 -m build .
```

From a separate directory, create a virtual environment and install the wheel
plus the test runner:

```sh
python3 -m venv .venv
.venv/bin/python -m pip install /path/to/spicedmodel/dist/*.whl pytest
```

Generate the golden data once, after deliberately selecting the reference
version:

```sh
cd /a/directory/outside/the/repository
.venv/bin/python /path/to/spicedmodel/tests/generate_golden_data.py
```

Then run the tests from that same external directory:

```sh
.venv/bin/python -m pytest /path/to/spicedmodel/tests
```

Each fixture contains the normal average and scaled outputs, plus isolated DC
and `m=1` through `m=6` Fourier outputs for both variants. Normal test runs
only read `tests/data/*.json.gz`; they never regenerate them.
