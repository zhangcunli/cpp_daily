#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void test(int& opcode)
{
	opcode += 10;
	std::cout << opcode << std::endl;
	
}

int main()
{
	std::cout << "Test!" << std::endl;
	
	int opcode = 1;
	std::cout << opcode << std::endl;
	
	test(opcode);
	std::cout << opcode << std::endl;	

	return 0;
}

