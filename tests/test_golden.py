from __future__ import annotations

import importlib

import numpy as np


# The bundled C++ model uses platform libm implementations, so the final few
# float32 bits can differ between Linux, macOS, and Windows.
RTOL = 3e-5
ATOL = 2e-5
# Isolated physical-space Fourier terms are calculated by subtracting the
# reverse-transformed DC output. That cancellation varies slightly between
# compilers even when the complete model output is stable.
FOURIER_ATOL = 2e-3


def _array(section):
    return np.asarray(section["values"], dtype=np.float32).reshape(section["shape"])


def test_model_matches_golden_grid(golden):
    package = importlib.import_module("spicedmodel")
    model = getattr(package, golden["model"])
    inputs = golden["inputs"]
    mlt, radius = np.meshgrid(inputs["mlt"], inputs["radius"])

    actual_average = model(mlt, radius, Coord=inputs["coord"])
    np.testing.assert_allclose(
        actual_average, _array(golden["average"]), rtol=RTOL, atol=ATOL, equal_nan=True
    )

    parameter = "F107" if "F107" in inputs else "SMR"
    actual_scaled = np.stack(
        [model(mlt, radius, Coord=inputs["coord"], **{parameter: value})
         for value in inputs[parameter]]
    )
    np.testing.assert_allclose(
        actual_scaled, _array(golden["scaled"]), rtol=RTOL, atol=ATOL, equal_nan=True
    )


def test_model_components_match_golden_grid(golden):
    package = importlib.import_module("spicedmodel")
    model = getattr(package, golden["model"])
    inputs = golden["inputs"]
    mlt, radius = np.meshgrid(inputs["mlt"], inputs["radius"])
    components = golden["components"]

    actual_average_dc = model(mlt, radius, Coord=inputs["coord"], OnlyDC=True)
    actual_average_fourier = np.stack(
        [
            model(mlt, radius, Coord=inputs["coord"], ShowDC=False, m=[m, m])
            for m in inputs["fourier_m"]
        ]
    )
    np.testing.assert_allclose(
        actual_average_dc,
        _array(components["average"]["dc"]),
        rtol=RTOL,
        atol=ATOL,
        equal_nan=True,
    )
    np.testing.assert_allclose(
        actual_average_fourier,
        _array(components["average"]["fourier"]),
        rtol=RTOL,
        atol=FOURIER_ATOL,
        equal_nan=True,
    )

    parameter = "F107" if "F107" in inputs else "SMR"
    actual_scaled_dc = np.stack(
        [
            model(
                mlt,
                radius,
                Coord=inputs["coord"],
                OnlyDC=True,
                **{parameter: value},
            )
            for value in inputs[parameter]
        ]
    )
    actual_scaled_fourier = np.stack(
        [
            np.stack(
                [
                    model(
                        mlt,
                        radius,
                        Coord=inputs["coord"],
                        ShowDC=False,
                        m=[m, m],
                        **{parameter: value},
                    )
                    for m in inputs["fourier_m"]
                ]
            )
            for value in inputs[parameter]
        ]
    )
    np.testing.assert_allclose(
        actual_scaled_dc,
        _array(components["scaled"]["dc"]),
        rtol=RTOL,
        atol=ATOL,
        equal_nan=True,
    )
    np.testing.assert_allclose(
        actual_scaled_fourier,
        _array(components["scaled"]["fourier"]),
        rtol=RTOL,
        atol=FOURIER_ATOL,
        equal_nan=True,
    )


def test_golden_metadata_and_shapes(golden):
    assert golden["schema_version"] == 2
    assert len(golden["package_commit"]) == 40
    assert len(golden["spiced_commit"]) == 40
    assert golden["library_sha256"]
    assert golden["average"]["shape"] == [9, 12]
    assert golden["scaled"]["shape"][-2:] == [9, 12]
    assert golden["inputs"]["fourier_m"] == [1, 2, 3, 4, 5, 6]
    assert golden["components"]["average"]["dc"]["shape"] == [9, 12]
    assert golden["components"]["average"]["fourier"]["shape"] == [6, 9, 12]
    assert golden["components"]["scaled"]["dc"]["shape"][-2:] == [9, 12]
    assert golden["components"]["scaled"]["fourier"]["shape"][-3:] == [6, 9, 12]
