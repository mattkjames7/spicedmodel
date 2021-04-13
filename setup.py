import setuptools
from setuptools.command.install import install
import os

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="spicedmodel",
    version="0.0.1",
    author="Matthew Knight James",
    author_email="mattkjames7@gmail.com",
    description="Python wrapper for the Scalable Plasma Ion Composition and Electron Density (SPICED) model",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/mattkjames7/spicedmodel",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License (GPL)",
        "Operating System :: POSIX",
    ],
    install_requires=[
		'numpy',
		'matplotlib',
	],
	include_package_data=True,
)



