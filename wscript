#!/usr/bin/env python

import sys

def options(opt):
        opt.load('compiler_cxx')

def configure(conf):
        conf.load('compiler_cxx')
        if sys.platform == 'darwin':
            conf.env.FRAMEWORK_LOOPER = ['Cocoa','OpenGL','AGL']
        conf.check_cfg(path='llvm-config', args='--cflags --libs --ldflags',
                package='', uselib_store='LLVM')


def build(bld):

    #COMMANDS
    bld.objects(
        source       = bld.path.ant_glob('src/commands/*.cpp'),
        target       = 'commands',
        includes     = ['tuiles', '/usr/include', '/usr/local/include'],
        cxxflags     = ['-O3','-Wall'],
    )

	#LIBTUILES
    bld.stlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = 'commands',
        target       = 'Tuiles',
        includes     = ['tuiles', '/usr/include', '/usr/local/include'],
        cxxflags     = ['-O3', '-Wall'],
        lib          = ['m', 'xml2', 'jack'],
        libpath      = ['/usr/lib', '/usr/local/lib'],
        vnum         = '0.0.1',
        install_path = '${PREFIX}/lib',
     )

    bld.shlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = 'commands',
        target       = 'Tuiles',
        includes     = ['tuiles', '/usr/include', '/usr/local/include'],
        cxxflags     = ['-O3', '-Wall'],
        lib          = ['m', 'xml2', 'jack'],
        libpath      = ['/usr/lib', '/usr/local/lib'],
        vnum         = '0.0.1',
        install_path = '${PREFIX}/lib',
    )

	#EXAMPLES
    bld.program(
          source       = 'examples/simple.cpp',
          use          = 'Tuiles',
          target       = 'simple',
          includes     = ['.', '/usr/include', '/usr/local/include'],
          cxxflags     = ['-O3', '-Wall'],
          lib          = ['m', 'jack', 'xml2'],
          libpath      = ['/usr/lib', '/usr/local/lib', '.'],
    )
    bld.program(
          source       = 'examples/complex.cpp',
          use          = 'Tuiles',
          target       = 'complex',
          includes     = ['.', '/usr/include', '/usr/local/include'],
          cxxflags     = ['-O3', '-Wall'],
          lib          = ['m', 'jack', 'xml2'],
          libpath      = ['/usr/lib', '/usr/local/lib', '.'],
    )
    


