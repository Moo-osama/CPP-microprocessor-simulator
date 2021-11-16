#include <iostream>
#include <fstream>
#include "reader.h"
using namespace std;

int main()
{
    vector<Instruction> inst_mem;
    file_reader reader("master.txt");
    inst_mem = reader.instruction_mem();

    ofstream myfile("example.txt");
    if (myfile.is_open())
    {
        myfile << inst_mem[0].getcontent();
        myfile << inst_mem[1].getcontent();
        myfile.close();
    }
    else
        cout << "Unable to open file";
    return 0;
}