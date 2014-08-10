from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

INSTALL_DIR = '../../live555'
module = Extension('live555',
                   language = "c++",
                   include_dirs=['%s/%s/include' % (INSTALL_DIR, x) for x in ['liveMedia', 'BasicUsageEnvironment', 'UsageEnvironment', 'groupsock']] + ['./src'],
                   libraries=['liveMedia', 'groupsock', 'BasicUsageEnvironment', 'UsageEnvironment'],
                   extra_compile_args = ['-fPIC'],
                   library_dirs=['%s/%s' % (INSTALL_DIR, x) for x in ['liveMedia', 'UsageEnvironment', 'groupsock']],
                   sources = ['./src/ctestRtspClient.pyx', './src/waptestRTSPClient.cpp'])

setup(name = 'live555',
      version = '1.0',
      description = 'Basic wrapper around live555 to load RTSP video streams',
      #ext_modules = cythonize([module], gdb_debug=True),
      ext_modules = [module],
      cmdclass = {'build_ext': build_ext})


