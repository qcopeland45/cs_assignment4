compile: 
	clang++ -std=c++14 -c main.cpp functions.cpp

clean:
	rm -f main.o functions.o QuadClassifier Expected_output.txt classifier classifier.profraw classifier.profdata default.profraw

classifier:
	clang++ -std==c++14 -o QuadClassifier main.o functions.o

cover:
	clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp functions.cpp -o classifier
	LLVM_PROFILE_FILE="classifier.profraw" ./classifier < test.txt
	xcrun llvm-profdata merge -sparse classifier.profraw -o classifier.profdata
	xcrun llvm-cov show ./classifier -instr-profile=classifier.profdata