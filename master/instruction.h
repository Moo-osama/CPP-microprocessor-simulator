#pragma once
class Instruction
{
	int address;
	char* content;
public:
	Instruction();
	~Instruction();
	int getAddress() const;
	const char* getcontent() const;
	void setAddress(int addr);
	void setcontent(const char* information);

}; 

