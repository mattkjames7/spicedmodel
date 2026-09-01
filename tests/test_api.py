from __future__ import annotations

import ctypes
from pathlib import Path

import numpy as np
import pytest

import spicedmodel


MODELS = [
    spicedmodel.Mav,
    spicedmodel.MavHot,
    spicedmodel.MavPS,
    spicedmodel.MavPT,
    spicedmodel.Prob,
    spicedmodel.PS,
    spicedmodel.PT,
    spicedmodel.Density,
    spicedmodel.PMD,
]


def test_package_and_native_library_import():
    assert spicedmodel.__version__
    assert Path(spicedmodel.__file__).is_file()
    assert isinstance(spicedmodel._CFunctions.liblsmodel, ctypes.CDLL)


@pytest.mark.parametrize("model", MODELS, ids=lambda model: model.__name__)
def test_scalar_and_array_shapes(model):
    scalar = model(12.0, 4.0, Coord="ml")
    assert scalar.shape == ()
    assert scalar.dtype == np.float32
    assert np.isfinite(scalar)

    mlt, radius = np.meshgrid([0.0, 6.0, 12.0], [2.0, 4.0, 5.89])
    array = model(mlt, radius, Coord="ml")
    assert array.shape == mlt.shape
    assert array.dtype == np.float32
    assert np.all(np.isfinite(array))


@pytest.mark.parametrize("model", MODELS, ids=lambda model: model.__name__)
def test_validation_marks_out_of_range_positions(model):
    result = model([0.0, 0.0, 0.0, 0.0], [1.4, 2.0, 5.89, 5.91], Coord="ml")
    assert np.isnan(result[0])
    assert np.isfinite(result[1:3]).all()
    assert np.isnan(result[3])


def test_scalar_and_array_scaling_are_equivalent():
    mlt = np.array([0.0, 6.0, 12.0, 18.0], dtype=np.float32)
    radius = np.full(mlt.shape, 4.0, dtype=np.float32)
    scalar = spicedmodel.Density(mlt, radius, SMR=-70.0, Coord="ml")
    array = spicedmodel.Density(mlt, radius, SMR=np.full(mlt.shape, -70.0), Coord="ml")
    np.testing.assert_array_equal(scalar, array)

    scalar = spicedmodel.MavHot(mlt, radius, F107=150.0, Coord="ml")
    array = spicedmodel.MavHot(mlt, radius, F107=np.full(mlt.shape, 150.0), Coord="ml")
    np.testing.assert_array_equal(scalar, array)


def test_cartesian_and_mlt_coordinates_are_equivalent():
    mlt = np.arange(0.0, 24.0, 3.0, dtype=np.float32)
    radius = np.full(mlt.shape, 4.0, dtype=np.float32)
    angle = mlt * np.pi / 12.0
    x = -radius * np.cos(angle)
    y = -radius * np.sin(angle)
    polar = spicedmodel.Mav(mlt, radius, Coord="ml")
    cartesian = spicedmodel.Mav(x, y, Coord="xy")
    np.testing.assert_allclose(cartesian, polar, rtol=2e-5, atol=2e-5)


def test_dc_and_periodic_components_reconstruct_output():
    mlt = np.arange(0.0, 24.0, 2.0, dtype=np.float32)
    radius = np.full(mlt.shape, 4.0, dtype=np.float32)
    full = spicedmodel.Prob(mlt, radius, Coord="ml")
    dc = spicedmodel.Prob(mlt, radius, Coord="ml", OnlyDC=True)
    periodic = spicedmodel.Prob(mlt, radius, Coord="ml", ShowDC=False)
    np.testing.assert_allclose(full, dc + periodic, rtol=2e-5, atol=2e-5)


def test_m_number_and_reverse_transform_options():
    mlt = np.arange(0.0, 24.0, 2.0, dtype=np.float32)
    radius = np.full(mlt.shape, 4.0, dtype=np.float32)
    m1 = spicedmodel.Prob(mlt, radius, Coord="ml", m=[1, 1])
    m3 = spicedmodel.Prob(mlt, radius, Coord="ml", m=[1, 3])
    assert np.isfinite(m1).all()
    assert not np.array_equal(m1, m3)

    physical = spicedmodel.PS(mlt, radius, Coord="ml", RevTrans=True)
    transformed = spicedmodel.PS(mlt, radius, Coord="ml", RevTrans=False)
    assert np.isfinite(physical).all()
    assert not np.array_equal(physical, transformed)
