#!/usr/bin/env python3

from argparse import ArgumentParser
from collections import defaultdict
from os import path
import json
import os
import subprocess
import struct
import sys
import tempfile
import traceback
import subprocess
import os.path

__version__ = "1.0"

MAX_LEVEL = 100


def main():
    for j in range(1, MAX_LEVEL):
        mapname = "map%d" % (j)
        mapjson = "map%d.json" % (j)
        if os.path.isfile(mapjson) == 0:
            break 
        directive = "python3.9 ../tools/map.py --aplib --room-width 32 --room-height 23 %s %s" % (mapjson, mapname) 
        subprocess.run(directive, shell=True)

    mapname = "map0"
    mapjson = "title.json"
        
    directive = "python3.9 ../tools/map.py --aplib --room-width 32 --room-height 24 %s %s" % (mapjson, mapname) 
    subprocess.run(directive, shell=True)    
       

if __name__ == "__main__":
    remove_list = []

    try:
        main()
    except Exception as ex:
        print("FATAL: %s\n***" % ex, file=sys.stderr)
        traceback.print_exc()

        for filename in remove_list:
            if os.path.exists(filename):
                os.unlink(filename)

        sys.exit(1)
