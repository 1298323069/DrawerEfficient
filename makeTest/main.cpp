//---------
//main.c
#include <stdio.h>

#include "complicated.hpp"

int main(int argc, char const *argv[])
{
	printf("%s\n",HELLO_STRING);
	printf("%s\n",PROJECT_NAME);
	complicated();
	return 0;
}
