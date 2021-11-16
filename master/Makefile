output: master.o reader.o instruction.o
	g++ master.o reader.o instruction.o -o run

Source.o: master.cpp
	g++ -c master.cpp

reader.o: reader.cpp reader.h
	g++ -c reader.cpp

instruction.o: instruction.cpp instruction.h
	g++ -c instruction.cpp

clean:
	rm *.o run