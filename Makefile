newShape: main.o functions.o
	clang++ -o newShape main.o functions.o

## compiling cpp files 
main.o: 
	clang++ -c main.cpp functions.cpp

#functions.o: functions.cpp
	#clang++ -c functions.cpp

test: newShape
	./myTest.sh

clean:
	rm -f newShape main.o functions.o testOutput.txt classifier classifier.profraw classifier.profdata

	#rm -f main.o
	#rm -f functions.o
	#rm -f testOutput.txt

## code coverage testing 
cover:
	clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp functions.cpp -o classifier
	LLVM_PROFILE_FILE="classifier.profraw" ./classifier < test.txt
	xcrun llvm-profdata merge -sparse classifier.profraw -o classifier.profdata
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata 

## hashtags are comments and will be ignored when running make file
## YOU CAN THINK OF A MAKE FILE AS COMMANDS YOU WOULD RUN IN THE COMMAND LINE
## ONLY MUCH SHORTER VERSIONS, ESSENTIALLY LIKE MACROS