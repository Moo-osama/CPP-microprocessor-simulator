# CPP-microprocessor-simulator
CPP simulation for a microprocessor with concurrent execution and networking capabilities.


CPP simulation of Microprocessor with the concurrent execution and networking capabilities. The microprocessor, which we call Simple Integer Machine (SIM), doesn’t have registers but has two memory banks. The first is an instruction memory. It contains 1024 memory locations each capable of holding one instruction. The second, a data memory, also contains 1024 memory locations each capable of holding one integer value. 

The input will be a text file containing the instructions. Instructions start with a 3 character instruction word at the beginning, like ADD, followed by a single space, then a list of space-separated operands. The number of operands depends on the instruction. There exists a newline character after each instruction. We read this text file at the beginning of the simulation and convert each instruction to a representation that we store in the instruction memory. This representation uses C++ classes.
