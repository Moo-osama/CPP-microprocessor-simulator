#include <map>
#include <string>
#include "parser.h"
#include "instruction.h"
#include "executor.h"

using namespace std;

executor::executor(vector<Instruction> instructionss) // constructor
{
    instructions = instructionss; // passing instruction memory

    for (int i = 0; i < 1024; i++) // initialize data memory to all zeros
        dataMem[i] = 0;
}

void executor::execute()
{
    parser parse_me; // parser to parse each instruction

    enum StringValue
    { // enum inst type values to swtich on later
        add,
        neg,
        mul,
        jpa,
        jpo,
        asi,
        loe,
        hlt
    };

    static map<string, StringValue> s_mapStringValues; // to map string inst types to enum int values to switch on later

    s_mapStringValues["ADD"] = add;
    s_mapStringValues["NEG"] = neg;
    s_mapStringValues["MUL"] = mul;
    s_mapStringValues["JPA"] = jpa;
    s_mapStringValues["JP0"] = jpo;
    s_mapStringValues["ASI"] = asi;
    s_mapStringValues["LOE"] = loe;
    s_mapStringValues["HLT"] = hlt;

    string type;
    int in1;
    int in2;
    int out1;

    for (int i = 0; i < instructions.size(); i++)
    {
        parse_me.parse(instructions[i]); // parse instruction

        string type = parse_me.getOpcode(); // get instruction type
        in1 = parse_me.getOperand1();       // get operand 1
        in2 = parse_me.getOperand2();       // get operand 2
        out1 = parse_me.getOperand3();      // get operand 3

        switch (s_mapStringValues[type]) // swtich on instruction type
        {
        case add:
            addf(in1, in2, out1);
            break;

        case neg:
            negf(in1, in2);
            break;

        case mul:
            mulf(in1, in2, out1);
            break;

        case jpa:
            jpaf(in1, i);
            break;

        case jpo:
            jpof(in1, in2, i);
            break;

        case asi:
            asif(in1, in2);
            break;

        case loe:
            loef(in1, in2, out1);
            break;

        case hlt:
            hltf(i);
            break;
        default:
            printf("Instruction %d is not a valid instruction!", i + 1);
        }
    }
}

void executor::addf(int in1, int in2, int out1)
{
    int temp1 = dataMem[in1];
    int temp2 = dataMem[in2];
    dataMem[out1] = dataMem[in1] + dataMem[in2];
    printf("The SIM just added memory location %d with value %d & memory location %d \
with value %d and stored it in memory location %d now with value %d \n",
           in1, temp1,
           in2, temp2, out1, dataMem[out1]);
}

void executor::negf(int in1, int out1)
{
    int temp = dataMem[in1];
    dataMem[out1] = -1 * dataMem[in1];
    printf("The SIM just negated memory location %d with value %d \
and stored it in memory location %d now with value %d \n",
           in1, temp,
           out1, dataMem[out1]);
}

void executor::mulf(int in1, int in2, int out1)
{
    int temp1 = dataMem[in1];
    int temp2 = dataMem[in2];
    dataMem[out1] = dataMem[in1] * dataMem[in2];
    printf("The SIM just multiplied memory location %d with value %d & memory \
location %d with value %d and stored it in memory location %d now with value %d \n",
           in1, temp1, in2, temp2, out1, dataMem[out1]);
}

void executor::jpaf(int a1, int &index)
{
    if (a1 < 0 || a1 > 1023)
    {
        cout << "Instruction memory index is out of range!" << endl;
    }
    else
    {
        index = a1 - 1;
        printf("The SIM just went to address %d in instruction memory \n", a1);
    }
}

void executor::jpof(int in1, int a1, int &index)
{
    if (a1 < 0 || a1 > 1023)
    {
        cout << "Instruction memory index is out of range!" << endl;
    }
    else
    {
        if (dataMem[in1] == 0)
        {
            index = a1 - 1;
            printf("The SIM just jumped to address %d in instruction memory \n", a1);
        }
        else
            printf("The SIM just skipped jump instruction (JP0) because memory location %d \
with value %d is not equal to 0 \n",
                   in1, dataMem[in1]);
    }
}

void executor::asif(int in1, int out1)
{
    dataMem[out1] = in1;
    printf("The SIM just assigned the value of memory location %d to %d \n", out1, in1);
}

void executor::loef(int in1, int in2, int out1)
{
    if (dataMem[in1] <= dataMem[in2])
    {
        dataMem[out1] = 1;
        printf("The SIM just assigned the value of memory location %d to 1 \n", out1);
    }
    else
    {
        dataMem[out1] = 0;
        printf("The SIM just assigned the value of memory location %d to 0 \n", out1);
    }
}

void executor::hltf(int &index)
{
    index = instructions.size();
    printf("The SIM just stopped \n");
}
