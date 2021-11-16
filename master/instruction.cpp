#include "instruction.h"
#include <iostream>
#include <cstring>



Instruction::Instruction() : content(NULL)
{
}  


Instruction::~Instruction()
{

}  


int Instruction::getAddress() const
{
    return address;
} 


const char* Instruction::getcontent() const
{
    return content;
} 


void Instruction::setAddress(int addr)
{
    address = addr;
} 


void Instruction::setcontent(const char* information)
{
    content = new char[strlen(information) + 1];
    strcpy(content, information);
} 