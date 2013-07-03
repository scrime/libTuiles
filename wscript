#!/usr/bin/env python

import sys

def options(opt):
        opt.load('compiler_cxx')

def configure(conf):
        conf.load('compiler_cxx')
        conf.env.INCLUDES = ['.', 'tuiles', 
                            '/usr/include', '/usr/local/include']
        conf.env.LIB      = ['m', 'xml2', 'jack']
        conf.env.LIBPATH  = ['.', '/usr/lib', '/usr/local/lib']
        conf.env.CXXFLAGS = ['-O3', '-Wall'] 
        conf.env.DEFINES  = ['DEBUG(x)=//x']

        conf.setenv('debug', env=conf.env.derive())
        conf.env.CXXFLAGS = ['-g', '-Wall']
        conf.env.DEFINES  = ['DEBUG(x)=std::cout<< x <<std::endl;']

def build(bld):
    #COMMANDS
    bld.objects(
        source       = bld.path.ant_glob('src/commands/*.cpp'),
        target       = 'commands',
    )
	#LIBTUILES
    bld.stlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = ['commands'],
        target       = 'Tuiles'+bld.variant,
        install_path = '${PREFIX}/lib',
    )
    bld.shlib(
        source       = bld.path.ant_glob('src/*.cpp'),
        use          = ['commands'],
        target       = 'Tuiles'+bld.variant,
        install_path = '${PREFIX}/lib',
    )
	#EXAMPLES
    bld.program(
          source       = 'examples/simple.cpp',
          use          = ['Tuiles'+bld.variant],
          target       = 'simple'+bld.variant,
    )
    bld.program(
          source       = 'examples/complex.cpp',
          use          = ['Tuiles'+bld.variant],
          target       = 'complex'+bld.variant,
    )

from waflib.Build import BuildContext, CleanContext
class debug(BuildContext): 
        cmd = 'debug'
        variant = 'debug' 

