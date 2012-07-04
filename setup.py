#!/usr/bin/env python

from distutils.core import setup, Extension
import glob
import os
import os.path
import sys
import platform

#All c source
c_src = glob.glob(os.path.join("src","*.c"))

inc_dirs = []
lib_dirs = []
libs     = []

MTI_HOME = ""
VCS_HOME = ""

#Try get modelsim/vcs home
if os.environ.has_key("VCS_HOME") :
    VCS_HOME = os.environ['VCS_HOME']
elif os.environ.has_key("MTI_HOME") :
    MTI_HOME = os.environ["MTI_HOME"]
else :
    for path in os.environ["PATH"].split(";") :
        if not os.path.lexists(path) :
            continue
        all_files = os.listdir(path)
        if "vsim.exe" in all_files or \
        "vsim" in all_files:
            MTI_HOME = os.path.join(path,"..")                                        
            break
        elif "vcs.exe" in all_files or \
        "vcs" in all_files:
            VCS_HOME = os.path.join(path,"..")
            break

#update include/libs dirs.
if MTI_HOME :
    inc_dirs.append(os.path.join(MTI_HOME,"include"))
    if platform.system() == "Windows" :
        lib_dirs.append(os.path.join(MTI_HOME,"win32"))
        libs.append("mtipli")
        
elif VCS_HOME :
    inc_dirs.append(os.path.join(VCS_HOME,"include"))
    if platform.system() == "Windows" :
        # ToDo
        pass
else :
    print "Can't find variables : MTI_HOME, VCS_HOME."
    quit(0)

setup(name = '',
      version = '1.0',
      description = '',
      author = 'Gene Kong',
      author_email = 'genekong.sw@gmail.com',
      url = 'https://github.com/gyx2545965/pyvpi',
      py_modules = ['pyvpi_cons'],
      ext_modules = [Extension('pyvpi',
                               c_src,
                               include_dirs = inc_dirs,
                               library_dirs = lib_dirs,
                               extra_compile_args = ["-Wunused"],
                               libraries = libs,
                               )]
      )
