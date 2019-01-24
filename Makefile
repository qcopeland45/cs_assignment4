newShape: main.o functions.o
	clang++ -o newShape main.o functions.o

main.o: main.cpp
	clang++ -c main.cpp

functions.o: functions.cpp
	clang++ -c functions.cpp

test: newShape
	./myTest.sh

clean:
	rm -f newShape
	rm -f main.o
	rm -f functions.o
	rm -f testOutput.txt