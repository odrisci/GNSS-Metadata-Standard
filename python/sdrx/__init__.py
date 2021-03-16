"""Python bindings for ION GNSS Metadata standard"""

import os
import sys

# When we build this in tree the CPP bindings are contained in the 'bindings'
# folder. When we install, they will be installed locally in this folder

try:
    from .sdrx_cpp_api import *
except ImportError:
    print(f'sdrx_cpp_api not found, it has not been built')
    raise
