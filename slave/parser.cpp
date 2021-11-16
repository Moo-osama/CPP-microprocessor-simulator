#include <cstring>
#include <iostream>
#include <cstdlib>

#include "parser.h"
#include "instruction.h"


using namespace std;

void parser::parse(Instruction instruction)
{

    string s = instruction.getcontent();            // get instruction data
    vector<string> result;                          // vector to store type and operands separately
    istringstream iss(s);
    int count = 0;
    for (string s; iss >> s; )                      // parse by space " "
    {
        result.push_back(s);                        // add to result vector
        count++;                                    // count number of operands

    }
    opcode = result[0].c_str();                     // get inst type at first
        



    if (count > 1){                                 // get operands depending on their number in the instruction
        operand1 = stoi(result[1]);
}
    if (count > 2) {
        operand2 = stoi(result[2]);
    }
    if (count > 3) {
        operand3 = stoi(result[3]);
    }

}  

string parser::getOpcode()
{
    return opcode;
}

int parser::getOperand1()
{
    return operand1;
}

int parser::getOperand2()
{
    return operand2;
}

int parser::getOperand3()
{
    return operand3;
}
