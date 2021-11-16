output: slave.o SIM.o reader.o parser.o instruction.o executor.o
	g++ slave.o SIM.o reader.o parser.o instruction.o executor.o -o run

Source.o: slave.cpp
	g++ -c slave.cpp

SIM.o: SIM.cpp SIM.h
	g++ -c SIM.cpp

reader.o: reader.cpp reader.h
	g++ -c reader.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp

instruction.o: instruction.cpp instruction.h
	g++ -c instruction.cpp

executor.o: executor.cpp executor.h
	g++ -c executor.cpp

clean:
	rm *.o run