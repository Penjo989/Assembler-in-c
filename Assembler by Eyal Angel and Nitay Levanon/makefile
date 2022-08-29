main: assembler.o main.o  TableNode.o functions.o dataFunctions.o mathFunctions.o stringFunctions.o instructionFunctions.o savingFunctions.o preAssembler.o MacroTable.o LinesNode.o
	gcc assembler.o main.o functions.o TableNode.o dataFunctions.o stringFunctions.o mathFunctions.o instructionFunctions.o savingFunctions.o preAssembler.o MacroTable.o LinesNode.o -ansi -Wall -pedantic -o main
	
assembler.o: data.h macros.h assembler.c 
	gcc -c assembler.c -ansi -Wall -pedantic -o assembler.o

functions.o: data.h macros.h functions.c
	gcc -c functions.c -ansi -Wall -pedantic -o functions.o
	
TableNode.o: data.h macros.h TableNode.c
	gcc -c TableNode.c -ansi -Wall -pedantic -o TableNode.o
	
dataFunctions.o: data.h macros.h dataFunctions.c
	gcc -c dataFunctions.c -ansi -Wall -pedantic -o dataFunctions.o
	
instructionFunctions.o: data.h macros.h instructionFunctions.c
	gcc -c instructionFunctions.c -ansi -Wall -pedantic -o instructionFunctions.o


stringFunctions.o: data.h macros.h stringFunctions.c
	gcc -c stringFunctions.c -ansi -Wall -pedantic -o stringFunctions.o
	
mathFunctions.o: data.h macros.h mathFunctions.c
	gcc -c mathFunctions.c -ansi -Wall -pedantic -o mathFunctions.o
	
savingFunctions.o: data.h macros.h savingFunctions.c
	gcc -c savingFunctions.c -ansi -Wall -pedantic -o savingFunctions.o

main.o: data.h macros.h main.c
	gcc -c main.c -ansi -Wall -pedantic -o main.o
	
preAssembler.o: data.h macros.h preAssembler.c
	gcc -c preAssembler.c -g -ansi -Wall -pedantic -o preAssembler.o

MacroTable.o: data.h macros.h MacroTable.c
	gcc -c MacroTable.c -g -ansi -Wall -pedantic -o MacroTable.o

LinesNode.o: data.h macros.h LinesNode.c
	gcc -c LinesNode.c -g -ansi -Wall -pedantic -o LinesNode.o