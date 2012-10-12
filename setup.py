from distutils.core import setup, Extension

module = Extension('yodawg._dawg',
    include_dirs=['deps/yodawg/src'],
    sources=['deps/yodawg/src/yodawg.c', 'src/_dawg.c'],
)

import yodawg

setup(
    name='yodawg',
    version=yodawg.__version__,
    description='A tight implementation of a DAWG.',
    ext_modules=[module],
    packages=['yodawg'],
)
