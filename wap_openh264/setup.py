from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy as np

INSTALL_DIR = '../../openh264'
module = Extension('openh264',
                   language = "c++",
                   include_dirs=['%s/%s' %(INSTALL_DIR, x) for x in ['codec/decode/inc', 'codec/api/svc', 'test', 'gtest/include']] + ['./src'] + [np.get_include()],
                   libraries=['openh264', 'gtest'],
                   extra_compile_args = ['-fPIC'],
                   library_dirs=['%s' %(INSTALL_DIR)],
                   sources = ['./src/ctestDecH264.pyx', './src/waptestDecH264.cpp'])

setup(name = 'openh264',
      version = '1.0',
      description = 'Basic wrapper around openh264 to decode/encode h264 video streams',
      #ext_modules = cythonize([module], gdb_debug=True),
      ext_modules = [module],
      cmdclass = {'build_ext': build_ext})


