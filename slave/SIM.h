#pragma once
#include <string>	
#include "instruction.h"			// include class instruction to process each instruction separately
#include "reader.h"					// include class reader to read the instructions text file
#include "executor.h"				// include class executor to parse and execute instructions


using namespace std;
class SIM {
private:
	vector<Instruction> inst_mem;	// instruction memory vector of type instruction (class object)
public:
	SIM();							// constructor
	void process(string filename);	// function to read, parse, and execute text file.
};