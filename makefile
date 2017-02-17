build-t1:
	gcc Task1.c -o Task1
run-t1:
	./Task1
build-t2:
	gcc task2.c -o task2
run-t2:
	./task2
clean:
	rm -f Task1, task2
