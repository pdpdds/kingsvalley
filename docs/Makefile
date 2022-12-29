all: ubox-lib-ref.html spman-lib-ref.html mplayer-lib-ref.html extra-lib-ref.html tools-ref.html changes.html

ubox-lib-ref.html: ../include/ubox.h ../tools/hdoc.py footer.md header.html
	../tools/hdoc.py --footer footer.md "ubox.lib reference" < ../include/ubox.h > reference.ubox.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -F ../tools/pandocfilter-pygments.py -B header.html reference.ubox.md -o $@

spman-lib-ref.html: ../include/spman.h ../tools/hdoc.py footer.md spman.md header.html
	../tools/hdoc.py --header spman.md --footer footer.md "spman.lib reference" < ../include/spman.h > reference.spman.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -F ../tools/pandocfilter-pygments.py -B header.html reference.spman.md -o $@

mplayer-lib-ref.html: ../include/mplayer.h ../tools/hdoc.py footer.md mplayer.md header.html
	../tools/hdoc.py --header mplayer.md --footer footer.md "mplayer.lib reference" < ../include/mplayer.h > reference.mplayer.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -F ../tools/pandocfilter-pygments.py -B header.html reference.mplayer.md -o $@

extra-lib-ref.html: ../include/ap.h ../tools/hdoc.py footer.md extra.md header.html
	../tools/hdoc.py --header extra.md --footer footer.md "extra libs reference" < ../include/ap.h > reference.extra.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -F ../tools/pandocfilter-pygments.py -B header.html reference.extra.md -o $@

tools-ref.html: ../tools/hdoc.py footer.md tools.md header.html
	../tools/hdoc.py --header tools.md --footer footer.md "tools reference" < /dev/null > reference.tools.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -F ../tools/pandocfilter-pygments.py -B header.html reference.tools.md -o $@

changes.html: ../CHANGES.md
	pandoc -s -t html5 -c water.css -c monokai.css --toc --no-highlight -B header.html -M title:"What's new?" ../CHANGES.md -o $@

clean:
	rm -f *-lib-ref.html changes.html reference.*.md

.PHONY: clean all
