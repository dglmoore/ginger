all: index.html

%.html: %.adoc
	asciidoctor -b html5 $<

clean:
	rm -rf *.html

.PHONY: clean