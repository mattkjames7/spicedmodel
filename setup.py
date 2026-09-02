import setuptools
from setuptools.command.build_py import build_py
from setuptools.dist import Distribution
import os
import platform
import shutil
import stat
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


def remove_readonly(func, path, _exc_info):
	"""Retry removal after clearing Windows read-only attributes."""
	os.chmod(path, stat.S_IWRITE | stat.S_IREAD | stat.S_IEXEC)
	func(path)


class BuildPy(build_py):
	"""Build the bundled C++ library in the staged Python package."""

	def run(self):
		# Copy the package first so that building never modifies the source
		# checkout (the bundled C++ project is a git submodule).
		super().run()
		spiced_dir = os.path.join(
			self.build_lib, "spicedmodel", "__data", "spiced"
		)
		build_dir = os.path.join(spiced_dir, "build")
		install_dir = os.path.join(spiced_dir, "_install")
		system = platform.system()
		self.announce("building bundled SPICED library", level=2)
		subprocess.run([
			"cmake", "-S", spiced_dir, "-B", build_dir,
			"-DCMAKE_BUILD_TYPE=Release",
			"-DBUILD_TESTING=OFF",
			f"-DCMAKE_INSTALL_PREFIX={install_dir}",
		], check=True)
		subprocess.run(
			["cmake", "--build", build_dir, "--config", "Release"], check=True
		)
		subprocess.run(
			["cmake", "--install", build_dir, "--config", "Release"], check=True
		)

		if system == "Windows":
			sources = {
				"libspiced.dll": os.path.join(install_dir, "bin", "spiced.dll"),
				"ann.dll": os.path.join(install_dir, "bin", "ann.dll"),
			}
		elif system == "Darwin":
			sources = {
				"libspiced.dylib": os.path.join(install_dir, "lib", "libspiced.dylib"),
				"libann.dylib": os.path.join(install_dir, "lib", "libann.dylib"),
			}
		else:
			sources = {
				"libspiced.so": os.path.join(install_dir, "lib", "libspiced.so"),
				"libann.so": os.path.join(install_dir, "lib", "libann.so"),
			}

		runtime_dir = os.path.join(spiced_dir, "lib")
		os.makedirs(runtime_dir, exist_ok=True)
		for filename, source in sources.items():
			shutil.copy2(source, os.path.join(runtime_dir, filename), follow_symlinks=True)

		# Keep CMake intermediates and install metadata out of the wheel.
		shutil.rmtree(build_dir, onerror=remove_readonly)
		shutil.rmtree(install_dir, onerror=remove_readonly)


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
