from __future__ import annotations

import gzip
import json
from pathlib import Path

import matplotlib
import pytest


matplotlib.use("Agg")

DATA = Path(__file__).parent / "data"


@pytest.fixture(params=sorted(DATA.glob("*.json.gz")), ids=lambda path: path.stem.split(".")[0])
def golden(request):
    with gzip.open(request.param, "rt", encoding="utf-8") as stream:
        return json.load(stream)
