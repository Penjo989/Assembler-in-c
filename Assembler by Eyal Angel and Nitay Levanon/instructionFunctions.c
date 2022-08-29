/*
 * This file is responsible for all of the functions that relate to an instruction
 * in the assembly language.
 */
#include "data.h"

/*This function gets a StrippedLine object and checks if the next word it holds is an instruction
 * if it is it calls the appropriate function to handle the rest and returns True otherwise it just returns False*/
Boolean checkInstruction(StrippedLine *sl, DataStructs *ds, Boolean addLabel)
{
	EncodedData ed;
	String instName;
	getEncodedData(sl, &ed, ds);
	instName = getLabel(sl->wordIndex, &(sl->words));
	if(equals(instName, "mov")) movFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "cmp")) cmpFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "add")) addFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "sub")) subFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "not")) notFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "clr")) clrFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "lea")) leaFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "inc")) incFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "dec")) decFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "jmp")) jmpFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "bne")) bneFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "get")) getFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "prn")) prnFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "jsr")) jsrFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "rts")) rtsFunc(sl, &ed, ds, addLabel);
	else if(equals(instName, "hlt")) hltFunc(sl, &ed, ds, addLabel);
	else return False;
	return True;
}
/*This function is called if a 'mov' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void movFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op2 == NONE || ed->op2 == INT)
		raiseError("'mov' instruction got wrong opernads");
	else
	{
		addInstCode(0, ed->op1, ed->op2, ds);
		addEncodedData(ed, ds);

	}
}
/*This function is called if a 'cmp' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void cmpFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op2 == NONE)
		raiseError("'cmp' takes 2 opernads");
	else
	{
		addInstCode(1, ed->op1, ed->op2, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'add' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void addFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op2 == NONE || ed->op2 == INT)
		raiseError("'add' instruction got wrong opernads");
	else
	{
		addInstCode(2, ed->op1, ed->op2, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'sub' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void subFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op2 == NONE || ed->op2 == INT)
		raiseError("'sub' instruction got wrong opernads");
	else
	{
		addInstCode(3, ed->op1, ed->op2, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'not' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void notFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'not' instruction got wrong opernads");
	else
	{
		addInstCode(4, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'clr' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void clrFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'clr' instruction got wrong opernads");
	else
	{
		addInstCode(5, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'lea' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void leaFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if((ed->op1 != MEM && ed->op1 != STRCT) || ed->op2 == NONE || ed->op2 == INT)
		raiseError("'lea' instruction got wrong opernads");
	else
	{
		addInstCode(6, ed->op1, ed->op2, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'inc' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void incFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'inc' instruction got wrong opernads");
	else
	{
		addInstCode(7, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'dec' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void decFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'dec' instruction got wrong opernads");
	else
	{
		addInstCode(8, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'jmp' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void jmpFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'jmp' instruction got wrong opernads");
	else
	{
		addInstCode(9, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'bne' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void bneFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'bne' instruction got wrong opernads");
	else
	{
		addInstCode(10, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'get' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void getFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'get' instruction got wrong opernads");
	else
	{
		addInstCode(11, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'prn' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void prnFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op2 != NONE)
		raiseError("'prn' instruction got wrong opernads");
	else
	{
		addInstCode(12, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'jsr' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void jsrFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 == NONE || ed->op1 == INT || ed->op2 != NONE)
		raiseError("'jsr' instruction got wrong opernads");
	else
	{
		addInstCode(13, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'rts' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void rtsFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel )
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 != NONE  || ed->op2 != NONE)
		raiseError("'rts' instruction takes no opernads");
	else
	{
		addInstCode(14, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*This function is called if a 'hlt' instruction was detected and it
 * adds the appropirate encoded data to the instruction array*/
void hltFunc(StrippedLine *sl, EncodedData * ed, DataStructs *ds, Boolean addLabel)
{
	updateInstLabel(ds, addLabel);
	if(ed->op1 != NONE  || ed->op2 != NONE)
		raiseError("'hlt' instruction takes no opernads");
	else
	{
		addInstCode(15, ed->op2, ed->op1, ds);
		addEncodedData(ed, ds);
	}
}
/*this function gets an opcode and two operand types and adds the appropriate word created by them
 * to the instruction array*/
void addInstCode(int opcode, char op1, char op2, DataStructs *ds)
{
	Word ans = 0;
	ans += opcode << 6;
	ans += ((op1 == NONE) ? INT : op1) << 4;
	ans += ((op2 == NONE) ? INT : op2) << 2;
	addInstWord(ans, ds);

}
/*this function gets an EncodedData object and inserts it's data to the instruction array*/
void addEncodedData(EncodedData *ed, DataStructs *ds)
{
	int index = 0;
	for(;index < ed->dataLength; index++)
		addInstWord(ed->data[index], ds);
}
/*this function adds the given word to the instruction array*/
void addInstWord(Word num, DataStructs *ds)
{
	if(ds->instCounter >= MAX_SIZE)
		raiseError("Memory error - exceeded memory limit");
	else
	{
		ds->instArr[ds->instCounter] = num;
		ds->instCounter++;
	}
}
/*This function returns the encoded data read from a StrippedLine object and updates the
 * labelCallTable if needed*/
void getEncodedData(StrippedLine *sl, EncodedData *ed, DataStructs *ds)
{
	int iteration = 0;
	int index = 0;
	Boolean regUsed = False;

	ed->op1 = NONE;
	ed->op2 = NONE;
	ed->dataLength = 0;

	(sl->wordIndex)++;
	if(sl->wordIndex < sl->wordsLength)
	{
		TableNode values;
		TableNode *valPtr = &values;
		stripCommas(sl, valPtr);

		for(; iteration < 2; iteration++)
		{
			if(valPtr->next == NULL)
				break;
			valPtr = valPtr->next;

			if(valPtr->label[0] == '#')/*checks if word is supposed to be num*/
			{
				if(iteration == 0) ed->op1 = INT;
				if(iteration == 1) ed->op2 = INT;

				ed->data[index] = getNum(&(valPtr->label[1]), False) << 2;
				index++;
			}
			else if(isRegister(valPtr->label))/*checks if word is supposed to be register*/
			{
				if(iteration == 0)
				{
					regUsed = True;
					ed->op1 = REG;
					ed->data[index] = atoi(valPtr->label[1]) << 6;
					index++;
				}
				if(iteration == 1)
				{
					ed->op2 = REG;
					if(regUsed)
						ed->data[index - 1] += atoi(valPtr->label[1]) << 2;
					else
					{
						ed->data[index] = atoi(valPtr->label[1]) << 2;
						index++;
					}

				}

			}
			else /*handles word as if it's a label or structure*/
			{
				int i = 0;
				while(valPtr->label[i] != '\0')
				{
					if(valPtr->label[i] == '.')
					{
						if((valPtr->label[i + 1] == '1' ||  valPtr->label[i + 1] == '2') && valPtr->label[i + 2] =='\0')
						{

							if(iteration == 0) ed->op1 = STRCT;
							if(iteration == 1) ed->op2 = STRCT;
							ed->data[index] = 0;
							addNode(trim(valPtr->label, 2), index + ds->instCounter + 1, &(ds->labelCallTable), True, 0);
							index++;
							ed->data[index] = atoi(valPtr->label[i + 1]) << 2;
							index++;
						}
						else
							raiseError("Syntax Error - expected '<structName>.<1/2>'");

						break;

					}
					i++;
				}
				if(valPtr->label[i] == '\0')
				{
					if(iteration == 0) ed->op1 = MEM;
					if(iteration == 1) ed->op2 = MEM;
					ed->data[index] = 0;
					addNode(valPtr->label, index + ds->instCounter + 1, &(ds->labelCallTable), True, 0);
					index++;
				}
			}


		}
	}
	(sl->wordIndex--);
	ed->dataLength = index;
}


/*this function updates the infromation of the last label in the symbol table.
 * explanation: if a label is detected at the start of a line it is added to the symbol table
 * without knowing it's type(Data statement or instruction) and it's position in the corresponding array
 * therefore this function is needed to update that information*/
void updateInstLabel(DataStructs *ds, Boolean addLabel)
{
	if(addLabel)
	{
		TableNode *label = getLast(&(ds->symbolTable));
		label->data = ds->instCounter;
		label->type = INST;
	}
}
