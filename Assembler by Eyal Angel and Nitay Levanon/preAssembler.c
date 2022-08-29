
#include "data.h"

/*
 * This file is responsible for handling the
 * pre-assembler part of the project
 */

/* external variable */
extern Boolean error;
extern String file;
extern int lineCounter;
/* external variable */


/*
* This function is responsible for calling all of the
* functions that the pre-assembler part of the project must
* call.
* */
void runPreAssembler(String filePath)
{
	MacroTable macroTable, *currentMacro;
	macroTable.next = NULL;
	currentMacro = &macroTable;
	processFile(filePath, &macroTable, currentMacro);
	freeMacroChain(macroTable.next);
	file = changeFileType(file, "am");/*changes current file's suffix to am so the assembler could read it*/
}

/*This function goes over each line in the given .as file and handles it similar
 *  to the handle line function in assebmler.c except this function parses through all
 *  of the lines.*/
void processFile(String filePath,MacroTable *macroTable, MacroTable *currentMacro)
{
	Boolean macroMode = False;
	FILE *fp;
	FILE *fw;
	String line = (String)malloc(MAX_LINE_LENGTH * sizeof(String));
	String macroName;
	LinesNode* linesToWrite;
	StrippedLine* LineStripped;
	fp = fopen(filePath, "r");
	fw = fopen (changeFileType(file, "am"), "w");
	if(fp == NULL)
	{
		printf("An error occurred while opening: %s\n", filePath);
		return;
	}
	if(fw == NULL)
	{
		printf("An error occurred while opening: %s\n", filePath);
		return;
	}
	while(True)
	{
		if(feof(fp)) break;
		fgets(line, MAX_LINE_LENGTH, fp);
		LineStripped = (StrippedLine*)malloc(sizeof(StrippedLine));
		LineStripped->words.next = NULL;
		stripLine(line, LineStripped);
		if (LineStripped->wordsLength != 0){
			LineStripped->words = *(LineStripped->words.next);
			if (macroMode == False){
				if (!(macroSearch(LineStripped, &macroMode, currentMacro, macroTable))){
					macroName = (LineStripped->words).label;
					if (!(checkIfInMacro(macroName, macroTable))){
						if(!error) WriteToFile(line, fw);
					}
					else{
						linesToWrite = getLines(macroName, macroTable);
						linesToWrite = linesToWrite->next;
						if(!error)
							WriteLinesToFile(linesToWrite, fw);
					}
				}
				else {
					if (currentMacro -> next != NULL)
						currentMacro = currentMacro -> next;
				}
			}
			else{
				if (!(endMacroSearch(LineStripped, &macroMode)))
					addLineToMacro(line, currentMacro);
				else{
					macroMode = False;
				}
			}
		}
		line[0] = '\0';/*if the current file being read ends with \n this line makes sure it's not read twice*/
		lineCounter++;
	}
	fclose(fp);
	fclose(fw);
}

/*checks if line has new macro declaration*/
Boolean macroSearch(StrippedLine *strippedLine, Boolean *macroMode, MacroTable* currentMacro, MacroTable* macroTable)
{
	String name;
	if ((strippedLine->words).label != NULL){
		if(equals((strippedLine->words).label, "macro")){
			*macroMode = True;
			name = (strippedLine->words).next->label;
			checkIfSavedWord(name);
			if (!(addMacro(name, macroTable))){
				raiseError("macro is already defined");
				return True;
			}
			return True;
		}
		else return False;
	}
	else return False;
}



Boolean endMacroSearch(StrippedLine *strippedLine, Boolean *marcoMode)
{
	if ((strippedLine->words).label != NULL)
		return equals((strippedLine ->words).label, "endmacro");
	return False;
}



/*checks if the given string is named after an instruction or data statement and raises an error if so.*/
void checkIfSavedWord(String a)
{
	static String instructions[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc",
			"dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"};
	static String data[] = {".data", ".string", ".struct", ".entry", ".extern"};
	int index = 0;
	Boolean ans = False;
	for(;index < 16 && ans == False; index++)
		if(equals(a, instructions[index])) ans = True;
	for(index = 0;index < 5 && ans == False; index++)
		if(equals(a, data[index])) ans = True;
	if(ans) raiseError("Macro can't be named after a language saved word");
}






