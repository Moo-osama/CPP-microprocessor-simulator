#pragma once
#include <iostream>
#include <vector>
#include "parser.h"
#include "instruction.h"


using namespace std;
class executor
{
    vector<Instruction> instructions;               // instruction memory vector of type instruction (class object)
    int dataMem[1024];
    

public:
    executor(vector<Instruction> instructionss);    // constructor, passing instruction memory data coming from reader

    void execute();                                 // function to loop over instructions and execute them


    /*********************************************Supported instructions*********************************************/

    void addf(int, int, int);

    void negf(int, int);

    void mulf(int, int, int);

    void jpaf(int, int&);

    void jpof(int, int, int& index);

    void asif(int, int);

    void loef(int, int, int);

    void hltf(int&);
};