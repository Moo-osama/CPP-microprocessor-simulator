
#include "SIM.h"

using namespace std;
SIM::SIM() //constructor
{
}
void SIM::process(string filename)
{
	file_reader read_me(filename);		  // initialize reader object and pass filename to read text file
	inst_mem = read_me.instruction_mem(); // return data of instruction memory
	
	executor execute_me(inst_mem);				// initialize executor object to start execution
	execute_me.execute();						// execute instructions inside instruction memory
}