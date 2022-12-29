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

__version__ = "1.0"

DEF_STR_MAX_LEVEL = "MAX_LEVEL"
MAX_LEVEL = 100

def main():

    parser = ArgumentParser(description="Map importer",
                            epilog="Copyright (C) 2020 Juan J Martinez <jjm@usebox.net>",
                            )

    
    parser.add_argument("id", help="variable name")
    parser.add_argument(
        "--map-count", dest="mc", default=0, type=int,
        help="map count")

    args = parser.parse_args()
    LEVEL_COUNT = 0

    for j in range(1, MAX_LEVEL):
        mapname = "map%d" % (j)
        mapjson = "map%d.json" % (j)
        if os.path.isfile(mapjson) == 0:
            break 
        LEVEL_COUNT+=1;

    if args.mc != 0:
        LEVEL_COUNT = mc
 
    print("#ifndef _%s_H" % args.id.upper())
    print("#define _%s_H" % args.id.upper())

    print("#define %s %d" % (DEF_STR_MAX_LEVEL, LEVEL_COUNT))
    
    print("#ifdef LOCAL")

    print("#include \"map.h\"")

    print("unsigned char** g_map[%s + 1] =  {" % (DEF_STR_MAX_LEVEL) )
    for j in range(1, LEVEL_COUNT + 1):
        print("   map%d, " % (j) )
    
    print("   0,")
    print("};")

    print("unsigned char g_map_room_count[%s + 1] =  {" % (DEF_STR_MAX_LEVEL) )
    for j in range(1, LEVEL_COUNT + 1):
        print("   MAP%d_RW_COUNT, " % (j) )
    
    print("   0,")
    print("};")


    print("#else")

    print("extern unsigned char** g_map[%s + 1];" % (DEF_STR_MAX_LEVEL) )

    print("extern unsigned char g_map_room_count[%s + 1];" % (DEF_STR_MAX_LEVEL) )

    print("#endif // LOCAL")
    print("#endif // _%s_H" % args.id.upper())


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
