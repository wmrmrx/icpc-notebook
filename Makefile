all: *
	make tex
	make pdf
# 	$(MAKE) -C tests
	make clean

pdf: notebook.tex
	latexmk --pdf -shell-escape notebook.tex

tex: code/* latex/*
	python3 latex/latex.py > notebook.tex

clean:
	-rm *.aux *.log *.toc *.out *.fls *.fdb_latexmk
	-rm -rf _minted-notebook
