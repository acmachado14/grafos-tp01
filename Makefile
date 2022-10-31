compile:
	gcc src/main.c src/grafo-lib/grafo.c -lm -o exefile.out

run:
	./exefile.out

json:
	python3 routine/genJson.py

txt:
	python3 routine/genTxt.py