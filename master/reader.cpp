#include "reader.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

file_reader::file_reader(string path = "") : filepath(path)
{
}

string file_reader::getFilePath() const
{
	return filepath;
}

vector<Instruction> file_reader::instruction_mem() const
{
	ifstream fin;
	fin.open(getFilePath()); // open file
	if (!fin)
	{
		std::cout << "error opening file with path " << getFilePath() << endl;
		exit(1);
	}
	vector<Instruction> inst_mem;
	int instCount = 0;
	string temp_inst;
	Instruction temp_instruction;
	while (getline(fin, temp_inst))
	{ // get instruction line by line
		instCount++;
		temp_instruction.setAddress(instCount);			   // set inst address
		temp_instruction.setcontent(temp_inst.c_str());	   // set inst content data
		inst_mem.push_back(temp_instruction);			   // add to inst memory
		cout << "Read instruction: " << temp_inst << endl; // showing debug messages
	}

	return inst_mem;
}

void file_reader::setFilePath(string path)
{
	filepath = path;
}
