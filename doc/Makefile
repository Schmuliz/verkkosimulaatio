default:
	doxygen Doxyfile
	pandoc project_document.md -o project_document.pdf

firefox:
	firefox html/index.html

clean:
	rm -rf html latex
