/*
 * This file is responsible for all of the functions that relate to a data statement
 * in the assembly language.
 */
#include "data.h"


/*This function gets a StrippedLine object and checks if the next word it holds is a data statement
 * if it is it calls the appropriate function to handle the rest and returns True otherwise it just returns False*/
Boolean checkData(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	String dName = getLabel(sl->wordIndex, &(sl->words));/*the next word is the StrippedLine object*/
	if(equals(dName, ".data")) dataFunc(sl, ds, addLabel);
	else if(equals(dName, ".string")) stringFunc(sl, ds, addLabel);
	else if(equals(dName, ".struct")) structFunc(sl, ds, addLabel);
	else if(equals(dName, ".entry")) entryFunc(sl, ds, addLabel);
	else if(equals(dName, ".extern")) externFunc(sl, ds, addLabel);
	else return False;
	return True;
}

/*This function is called if a '.data' statement was detected and it
 * adds the appropirate encoded data to the data array*/
void dataFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	updateDataLabel(ds, addLabel);
	(sl->wordIndex)++;
	if (sl->wordsLength > sl->wordIndex)
	{
		Word num;
		TableNode values;
		TableNode *valPtr = &values;
		stripCommas(sl, valPtr);
		valPtr = valPtr->next;
		while(valPtr != NULL)
		{
			num = getNum(valPtr->label, True);
			addDataWord(num, ds);
			valPtr = valPtr->next;
		}
	}
	else
		raiseError("Expected at least 1 argument");

}
/*This function is called if a '.string' statement was detected and it
 * adds the appropriate encoded data to the data array*/
void stringFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	String extractedStr;
	updateDataLabel(ds, addLabel);
	(sl->wordIndex)++;
	if (sl->wordsLength -sl->wordIndex == 1)
	{
		extractedStr = extractString(getLabel(sl->wordIndex, &(sl->words)));
		addString(extractedStr, ds);
	}
	else
		raiseError("Expected 1 argument");

}
/*This function is called if a '.struct' statement was detected and it
 * adds the appropriate encoded data to the data array*/
void structFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	Word num;
	TableNode values;
	TableNode *valPtr = &values;
	String extractedStr;
	updateDataLabel(ds, addLabel);
	(sl->wordIndex)++;
	stripCommas(sl, valPtr);
	valPtr = valPtr->next;
	num = getNum(valPtr->label, True);
	addDataWord(num, ds);
	valPtr = valPtr->next;
	extractedStr = extractString(valPtr->label);
	addString(extractedStr, ds);
	if(valPtr->next != NULL)
		raiseError("Expected 2 arguments");


}
/*This function is called if a '.entry' statement was detected and it
 * adds the label to the entry table */
void entryFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	String entryStr;
	if(addLabel)
		removeLast(&(ds->symbolTable));
	(sl->wordIndex)++;
	if(sl->wordsLength - sl->wordIndex != 1)
		raiseError("Expected 1 argument");
	else
	{
		entryStr = getLabel(sl->wordIndex, &(sl->words));
		if(checkIfIn(entryStr, &(ds->entryTable)))
			raiseError("Label was already declared as entry");
		else if(checkIfIn(entryStr, &(ds->externTable)))
			raiseError("Label was already declared as extern");
		else
			addNode(entryStr, 0, &(ds->entryTable), True, 0);
	}
}
/*This function is called if a '.extern' statement was detected and it
 * adds the label to the extern table */
void externFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	String externStr;
	if(addLabel)
		removeLast(&(ds->symbolTable));
	(sl->wordIndex)++;
	if(sl->wordsLength - sl->wordIndex != 1)
		raiseError("Expected 1 argument");
	else
	{
		externStr = getLabel(sl->wordIndex, &(sl->words));
		if(checkIfIn(externStr, &(ds->symbolTable)))
			raiseError("Label has been declared");
		else if(checkIfIn(externStr, &(ds->externTable)))
			raiseError("Label was already declared as extern");
		else if (checkIfIn(externStr, &(ds->entryTable)))
			raiseError("Label was already declared as entry");
		else
		{
			addNode(externStr, 0, &(ds->externTable), True, 0);
			addNode(externStr, 0, &(ds->symbolTable), True, 0);
		}
	}
}
/*this function updates the infromation of the last label in the symbol table.
 * explanation: if a label is detected at the start of a line it is added to the symbol table
 * without knowing it's type(Data statement or instruction) and it's position in the corresponding array
 * therefore this function is needed to update that information*/
void updateDataLabel(DataStructs *ds, Boolean addLabel)
{
	if(addLabel)
	{
		TableNode *label = getLast(&(ds->symbolTable));
		label->data = ds->dataCounter;
		label->type = DATA;
	}
}

/*this function adds the given word to the data array*/
void addDataWord(Word num, DataStructs *ds)
{
	if(ds->dataCounter >= MAX_SIZE)
		raiseError("Memory error - exceeded memory limit");
	else
	{
		ds->dataArr[ds->dataCounter] = num;
		(ds->dataCounter)++;
	}
}
/*this function adds the given string to the data array*/
void addString(String str, DataStructs *ds)
{
	int strLength = getLength(str);
	if(ds->dataCounter + strLength + 1 >= MAX_SIZE)
		raiseError("Memory error - exceeded memory limit");
	else
	{
		int index = 0;
		for(;str[index] != '\0';index++)
			ds->dataArr[ds->dataCounter + index] = str[index];
		ds->dataArr[ds->dataCounter + strLength] = '\0';
		ds->dataCounter += strLength + 1;
	}
}

