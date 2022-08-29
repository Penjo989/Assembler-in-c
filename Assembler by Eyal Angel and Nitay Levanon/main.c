/*
 ============================================================================
 Name        : main.c
 Author      : Eyal And Nitay
 Version     :
 Copyright   : Your copyright notice
 Description : Simple assembler in Ansi style
 ============================================================================
 */
#include "data.h"

/*External Variables*/
int lineCounter;/*represents the current line read from the assembly file*/
Boolean error/*represents the error status*/;
String file;/*represents the current file being read from*/
/*External Variables*/

int main(int argc, char **argv) {
	int fileIndex = 1;
	for(;fileIndex < argc; fileIndex++)
		run(argv[fileIndex]);
	return 0;
}

/*runs the pre-assembler and the assembler on a given file*/
void run(String filePath)
{
	lineCounter = 1;
	error = False;
	file = getFileName(filePath);

	runPreAssembler(filePath);
	if(error == False)
	{
		lineCounter = 1;
		runAssembler();
	}
}
