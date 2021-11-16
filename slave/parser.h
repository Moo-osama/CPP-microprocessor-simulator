#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "instruction.h"

using namespace std;

class parser
{
private:
    string opcode;
    int operand1;
    int operand2;
    int operand3;

public:
    void parse( Instruction instruction);       // function to parse instructions
    string getOpcode();                         // get instruction type
    int getOperand1();                          // get operand 1
    int getOperand2();                          // get operand 2
    int getOperand3();                          // get operand 3
}; 

