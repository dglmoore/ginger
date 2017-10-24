all: html/index.html

html/%.html: src/%.adoc
	asciidoctor -b html5 -D html $<

clean:
	rm -rf html

.PHONY: clean