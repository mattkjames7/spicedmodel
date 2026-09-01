import setuptools
from setuptools.command.build_py import build_py
from setuptools.dist import Distribution
import glob
import os
import platform
import shutil
import subprocess

with open("README.md", "r") as fh:
    long_description = fh.read()

def getversion():
	'''
	read the version string from __init__
	
	'''
	#get the init file path
	thispath = os.path.abspath(os.path.dirname(__file__))+'/'
	initfile = thispath + 'spicedmodel/__init__.py'
	
	#read the file in
	f = open(initfile,'r')
	lines = f.readlines()
	f.close()
	
	#search for the version
	version = 'unknown'
	for l in lines:
		if '__version__' in l:
			s = l.split('=')
			version = s[-1].strip().strip('"').strip("'")
			break
	return version
	
version = getversion()


class BuildPy(build_py):
	"""Build the bundled C++ library in the staged Python package."""

	def run(self):
		# Copy the package first so that building never modifies the source
		# checkout (the bundled C++ project is a git submodule).
		super().run()
		spiced_dir = os.path.join(
			self.build_lib, "spicedmodel", "__data", "spiced"
		)
		system = platform.system()
		if system == "Windows":
			command = ["cmd", "/c", "compile.bat"]
		else:
			command = ["make"]
		self.announce("building bundled SPICED library", level=2)
		if system == "Linux":
			# libann's makefile does not assign an SONAME, so the dynamic
			# loader cannot match it when libspiced requests "libann.so".
			subprocess.run(["make", "libann"], cwd=spiced_dir, check=True)
			ann_objects = glob.glob(os.path.join(spiced_dir, "build", "*.o"))
			subprocess.run([
				"g++", *ann_objects, "-shared", "-fopenmp",
				"-Wl,-soname,libann.so", "-o",
				os.path.join(spiced_dir, "lib", "libann", "lib", "libann.so"),
			], check=True)
			subprocess.run(["make", "obj", "lib"], cwd=spiced_dir, check=True)
		else:
			subprocess.run(command, cwd=spiced_dir, check=True)
		# Object files are build intermediates, not package data.
		shutil.rmtree(os.path.join(spiced_dir, "build"), ignore_errors=True)


class BinaryDistribution(Distribution):
	"""Ensure wheels containing the shared library are platform-specific."""

	def has_ext_modules(self):
		return True



setuptools.setup(
    name="spicedmodel",
    version=version,
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
	cmdclass={"build_py": BuildPy},
	distclass=BinaryDistribution,
)
