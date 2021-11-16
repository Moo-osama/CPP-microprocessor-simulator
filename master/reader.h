#include <string>
#include <vector>
#include "instruction.h"							// include instruction class
#pragma once
using namespace std;
class file_reader
{
	string filepath;								// file to read
public:
	file_reader(string);							// constructor
	vector<Instruction> instruction_mem() const;	// function to return instruction memory data
	void setFilePath(string);						
	string getFilePath() const;
};

