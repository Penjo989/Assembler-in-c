#include "data.h"
extern Boolean error;
extern int lineCounter;
extern String file;

/*raises error*/
void raiseError(String errorStr)
{
	static int errorNum = 1;
	printf("Error (%s) no.%d (line %d), %s.\n", file, errorNum++, lineCounter, errorStr);
	error = True;
}
/*gets line and pointer to StrippedLine and returns StrippedLine object*/
void stripLine(String line, StrippedLine *sl)
{
	int index = 0, temp = 0, wordNum = 0, wordArrLength;
	int wordLength = 0;
	String word;
	while(line[temp] != '\0')
	{
		if(line[temp] == ' ' || line[temp] == '\t' || line[temp] == '\n')
		{
			if(wordLength != 0)
			{
				wordArrLength =  wordLength + 1;
				word = (String) calloc(wordArrLength, sizeof(char));
				for(;temp != index; index++)
					word[index - temp + wordLength] = line[index];
				word[wordLength] = '\0';
				addNode(word, 0, &(sl->words), True, 0);
				wordLength = 0;
				wordNum++;
			}
			else temp++;

		}
		else
		{
			if(wordLength == 0)
				index = temp;
			temp++;
			wordLength++;
		}
	}
	if (wordLength != 0){
		wordArrLength =  wordLength + 1;
		word = (String) calloc(wordArrLength, sizeof(char));
		for(;temp != index; index++)
			word[index - temp + wordLength] = line[index];
		word[wordLength] = '\0';
		addNode(word, 0, &(sl->words), True, 0);
		wordNum++;}

	sl->wordsLength = wordNum;
	sl->wordIndex = 0;
}
/*Checks syntax of given label*/
Boolean checkSyntax(String label)
{
	int index, i;
	static String instructions[16] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec",
			"jmp", "bne", "get", "prn", "jsr", "rts", "hlt"};

	Boolean ans = True;
	if(isNum(label[0]))
	{
		raiseError("A label must not start with a number");
		ans = False;
	}
	index = 0;
	while(label[index] != '\0')
	{
		if(isAlphabetical(label[index]) == False && isNum(label[index]) == False)
		{
			raiseError("A label must contain numbers and alphabetical chars only");
			ans = False;
			break;
		}
		index++;
	}
	if(index > 30)
	{
		raiseError("Label can't be longer than 30 characters");
		ans = False;
	}
	if(isRegister(label))
	{
		raiseError("A label can't be called as a register");
		ans = False;
	}
	for(i = 0; i < 16; i++)
	{
		if(equals(label, instructions[i]))
		{
			raiseError("A label can't be named after an instruction");
			ans = False;
		}
	}
	return ans;

}
/*gets a pointer to StrippedLine object and a pointer to a TableNode object. When the function finishes
 * the values chain has all of the words from the StrippedLine object in separate nodes.*/
TableNode *stripCommas(StrippedLine *sl, TableNode *values)
{
	Boolean comma = True;
	TableNode *t = getNode(&(sl->words), sl->wordIndex);
	String a;
	int index,wordLength;
	int i;
	resetNext(values);
	while(t != NULL)
	{
		index = 0;
		wordLength = 0;/*deleteLine*/
		while(True)
		{
			if(t->label[index] == ',' || t->label[index] == '\0')
			{
				if((comma && t->label[index] == ',' )|| (comma && t->next == NULL && t->label[index] == '\0'))
				{
					raiseError("Syntax Error - too many commas");
				}
				if (t->label[index] == ',') comma = True;
				if(wordLength > 0)
				{
					a = (String)calloc(wordLength + 1, sizeof(char));
					i = 0;
					for(;i < wordLength; i++)
						a[i] = t->label[index - wordLength + i];
					a[wordLength] = '\0';
					addNode(a, 0, values, False, 0);
					wordLength = 0;

				}
				if(t->label[index] == '\0') break;

			}
			else
				{
				if(wordLength == 0 && comma == False)
					raiseError("Syntax Error - expected comma between separate values");
				comma = False;
				wordLength++;
				}
			index++;
		}
		t = t->next;
	}
	return values;
}
int atoi(char a)
{
	return a - '0';
}

/*Gets a string and returns whether it is a register or not*/
Boolean isRegister(String a)
{
	Boolean ans = (getLength(a) == 2 && a[0] == 'r' && a[1] >= '0' && a[1] <= '7');
	return ans;

}

/*gets full path of file and returns only the file name*/
String getFileName(String filePath)
{
	int lastSlashIndex = -1;
	int index = 0;
	while(filePath[index] != '\0')
	{
		if(filePath[index] == '/')
			lastSlashIndex = index;
		index++;
	}
	return getCopy(&(filePath[lastSlashIndex + 1]));

}
/*gets String and new new suffix and changes it's suffix*/
String changeFileType(String fileName, String newType)
{
	String newName;
	int index = 0, j;
	int newTypeLength = getLength(newType);

	for(; fileName[index] != '.' && fileName[index] != '\0'; index++);

	newName = (String) calloc(index + newTypeLength + 2, sizeof(char));

	for(index = 0; fileName[index] != '.' && fileName[index] != '\0'; index++)
		newName[index] = fileName[index];
	newName[index++] = '.';
	for(j = 0; j <=  newTypeLength; j++)
		newName[index + j] = newType[j];
	return newName;
}


