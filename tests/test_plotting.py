from __future__ import annotations

import matplotlib.pyplot as plt
import pytest

import spicedmodel
from spicedmodel.PlotPlanet import PlotPlanet


@pytest.mark.parametrize(
    "plot_type", ["prob", "ps", "pt", "mav", "mavhot", "mavps", "mavpt", "density", "pmd"]
)
def test_plot_eq_smoke(plot_type):
    kwargs = {"F107": 150.0} if plot_type == "mavhot" else {"SMR": -30.0}
    ax = spicedmodel.PlotEq(
        plot_type,
        ColorBar=False,
        xrnge=[-6.0, 6.0],
        yrnge=[-6.0, 6.0],
        dx=2.0,
        dy=2.0,
        **kwargs,
    )
    assert ax.collections
    assert ax.get_xlabel()
    assert ax.get_ylabel()
    plt.close(ax.figure)


def test_plot_planet_adds_artists():
    figure, ax = plt.subplots()
    PlotPlanet(ax)
    assert len(ax.patches) == 2
    assert len(ax.lines) == 1
    plt.close(figure)
