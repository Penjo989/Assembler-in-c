#include "data.h"
/*
 * This file is responsible for handling the
 * assembler part of the project
 */


/*External Variables*/
extern int lineCounter;
extern Boolean error;
extern String file;
/*External Variables*/

/*
* This function is responsible for calling all of the
* functions that the assembler part of the project must
* call.
* */
void runAssembler()
{
	DataStructs ds;
	FILE *fp;
	String line = (String)malloc(MAX_LINE_LENGTH * sizeof(String));


	setupVars(&ds);
	fp = fopen(file, "r");

	if(fp == NULL)
	{
		printf("An error occurred while opening: %s\n", file);
		return;
	}
	/*This loops goes through all of the lines of the given file*/
	while(True)
	{
		if(feof(fp)) break;
		fgets(line, MAX_LINE_LENGTH, fp);
		handleLine(line, &ds);
		line[0] = '\0';/*if the current file being read ends with \n this line makes sure it's not read twice*/
		lineCounter++;
	}
	fclose(fp);
	linkLabels(&ds);
	checkEntries(&ds);

	if(error == False)
	{
		saveObFile(&ds);
		if(ds.entryTable.next != NULL)
			saveEntryFile(&ds);
		if(ds.externTable.next != NULL)
			saveExternFile(&ds);

	}

	freeDataStructs(&ds);

}


/*gets a line and calls all of the necessary functions needed to handle it*/
void handleLine(String line, DataStructs *ds)
{

	Boolean lineFinished = False;/*this boolean signals if the line read has been identified as an instruction or as data*/

	Boolean addLabel = False;
	StrippedLine sl;

	sl.wordIndex = 0;
	resetNext(&(sl.words));

	stripLine(line, &sl);

	if(sl.wordsLength == 0)
		return;

	sl.words = *(sl.words.next);/*the first node contains garbage so it advances to the next one*/
	if(sl.words.label[0] == ';')/*checks if line is a comment*/
		return;
	addLabel = checkLabel(&sl, ds);
	if(addLabel && sl.wordsLength == 1)
		raiseError("Expected instruction or definition after label");
	else
	{
		lineFinished = checkData(&sl, ds, addLabel);
		if(lineFinished == False)
			lineFinished = checkInstruction(&sl, ds, addLabel);
		if(lineFinished == False)
			raiseError("Unidentified statement");
	}

}
/*gets a StrippedLine object and checks if it's first word is a valid label
 * if so, adds it to the symbol table and returns True*/
Boolean checkLabel(StrippedLine *sl, DataStructs *ds)
{
	int index = 0;
	Boolean validLabel = True;
	String label;
	while(sl->words.label[index] != '\0')
	{
		if(sl->words.label[index] == ':')
		{
			sl->wordIndex++;
			if(sl->words.label[index + 1] != '\0')
			{
				raiseError("Expected space after label declaration");
				validLabel = False;
			}
			if(index == 0)
			{
				raiseError("Expected label");
				validLabel = False;
			}
			label = trim(sl->words.label, 1);/*get rid of ':'*/
			validLabel = validLabel && checkSyntax(label);
			if (validLabel)
			{
				if(checkIfIn(label, &(ds->symbolTable)))
				{
					raiseError("Label has already been declared");
				}
				else
				{
					addNode(label, 0, &(ds->symbolTable), True, 0);
					return True;
				}
			}
			return False;

		}
		index++;
	}
	return False;
}

/*after the program has finished processing the file this function links every
 * word that is supposed to be a label's address with it's correct address */
void linkLabels(DataStructs *ds)
{
	TableNode *labelTablePtr = &(ds->labelCallTable);
	Word encodedAddress;
	String label;
	labelTablePtr = labelTablePtr->next;
	while(labelTablePtr != NULL)
	{
		encodedAddress = 0;
		label = labelTablePtr->label;
		if(checkIfIn(label, &(ds->symbolTable)))
		{
			encodedAddress += getData(label, &(ds->symbolTable));
			if(checkIfIn(label, &(ds->externTable)))
			{
				encodedAddress <<= 2;
				encodedAddress += 1;/*corresponds to adding E*/
			}
			else
				{
				encodedAddress += MEM_START_POS;
				if(getType(label, &(ds->symbolTable)) == DATA) encodedAddress += ds->instCounter;
				encodedAddress <<= 2;
				encodedAddress += 2;/*corresponds to adding R*/
				}
			ds->instArr[labelTablePtr->data] = encodedAddress;/*updates encoded label address*/
		}
		else
			{
				lineCounter = labelTablePtr->line;
				raiseError("label hasn't been declared");
			}
		labelTablePtr = labelTablePtr->next;
	}
}

/*makes sure every label that was declared 'entry' actually exists*/
void checkEntries(DataStructs *ds)
{
	TableNode *ent = &(ds->entryTable);
	ent = ent->next;
	while(ent != NULL)
	{
		if(checkIfIn(ent->label, &(ds->symbolTable)) == False)
		{
			lineCounter = ent->line;
			raiseError("label hasn't been declared");
		}
		ent = ent->next;

	}
}
/*resets a 'DataStructs''s variables*/
void setupVars(DataStructs *ds)
{
	resetNext(&(ds->symbolTable));
	resetNext(&(ds->externTable));
	resetNext(&(ds->entryTable));
	resetNext(&(ds->labelCallTable));
	ds->dataCounter = 0;
	ds->instCounter = 0;
}
/*frees all of the allocated space for nodes*/
void freeDataStructs(DataStructs *ds)
{
	freeChain((ds->symbolTable).next);
	freeChain((ds->externTable).next);
	freeChain((ds->entryTable).next);
	freeChain((ds->labelCallTable).next);
}
