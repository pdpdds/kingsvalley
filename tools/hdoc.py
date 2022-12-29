#!/usr/bin/env python3

import sys
import re
from subprocess import Popen, PIPE
from argparse import ArgumentParser

__version__ = "0.1"

RE_FN = re.compile("[^\s]+\s+([^\(]+)\(")
RE_STRUCT = re.compile("(struct\s+[^{]+)\s*{")
RE_DEFINE = re.compile("#define\s+([^(]+)\(")
RE_DOC = re.compile("\s+\*\s?(.*\n)")
RE_SEC = re.compile("//\s+@(.*)\n")
RE_SECDOC = re.compile("//\s?(.*\n)")


def main():

    parser = ArgumentParser(
        description="Include docs to markdown",
        epilog="Copyright (C) 2020 Juan J Martinez <jjm@usebox.net>",
    )

    parser.add_argument(
        "--version", action="version", version="%(prog)s " + __version__
    )
    parser.add_argument(
        "--doc-version",
        dest="docver",
        default=None,
        help="Use this as version instead of git tag/commit",
    )
    parser.add_argument(
        "--header",
        dest="header",
        default=None,
        help="Add this file at the begining of the document",
    )
    parser.add_argument(
        "--footer",
        dest="footer",
        default=None,
        help="Add this file at the end of the document",
    )
    parser.add_argument("title", help="Title of the resulting document")

    args = parser.parse_args()

    if args.docver is None:
        proc = Popen(
            ["git", "describe", "--abbrev=0", "--tags"], stdout=PIPE, stderr=PIPE
        )
        out, err = proc.communicate()
        if proc.returncode != 0:
            proc = Popen(
                ["git", "rev-parse", "--short", "HEAD"], stdout=PIPE, stderr=PIPE
            )
            out, err = proc.communicate()
            out = b"git-" + out

        docver = out.decode("utf-8").strip()
    else:
        docver = args.docver

    data = sys.stdin.readlines()
    ref = {}
    section = None
    sections = {}
    while data:
        line = data.pop(0)

        # section comment
        if line.strip().startswith("//"):
            g = RE_SEC.search(line)
            if g:
                section = g.group(1)
                doclines = []
                while True:
                    line = data.pop(0)
                    if not line.strip():
                        break
                    doclines.append(line)

                doc = ""
                for l in doclines:
                    g = RE_SECDOC.match(l)
                    if g:
                        doc += g.group(1)

                sections[section] = doc

        # begin fn/struct comment
        if line.strip() == "/**":
            doclines = []
            while True:
                line = data.pop(0)
                if line.strip() == "*/":
                    break
                doclines.append(line)

            line = data.pop(0)
            g = RE_DEFINE.search(line)
            if g is None:
                g = RE_STRUCT.search(line)
                if g is None:
                    g = RE_FN.search(line)
                    if g is None:
                        continue
                    else:
                        fn = line.strip()
                else:
                    fn = line
                    while True:
                        line = data.pop(0)
                        fn += line
                        if line.strip() == "};":
                            break
            else:
                fn = line
                while True:
                    line = data.pop(0)
                    fn += line
                    if not line.strip().endswith("\\"):
                        fn = fn.rstrip()
                        break

            name = g.group(1).strip()
            anchor = name.replace(" ", "-")

            doc = ""
            for l in doclines:
                g = RE_DOC.match(l)
                if g:
                    doc += g.group(1)
            ref[name] = {
                "name": name,
                "anchor": anchor,
                "fn": fn,
                "doc": doc,
                "section": section,
            }

    print(
        """\
---
title: '{title}'
subtitle: 'Version {version}'
...""".format(
            title=args.title, version=docver
        )
    )

    if args.header:
        with open(args.header, "rt") as fd:
            print(fd.read())

    csec = None
    for k in sorted(ref.keys(), key=lambda k: (ref[k]["section"], k)):
        v = ref[k]
        if csec != v["section"]:
            csec = v["section"]
            print("## %s\n" % csec)
            if csec in sections:
                print(sections[csec])

        print(
            """\
### {name}
```c
{fn}
```

{doc}
""".format(
                **v
            )
        )

    if args.footer:
        with open(args.footer, "rt") as fd:
            print(fd.read())


if __name__ == "__main__":
    main()
