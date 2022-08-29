

#include "data.h"
/*gets String and boolean and checks if the given String is a valid number(depending on the boolean's value)
 * if so returns the number else returns 0 and raises error*/
Word getNum(String numStr, Boolean mem)
{
	Boolean positive = (numStr[0] != '-');

	Word num = 0;
	int index = (positive && numStr[0] != '+') ? 0 : 1;
	int mask = (mem) ? 1023 : 255;
	int maxPositive = (mem) ? 511 : 127;


	for(;numStr[index] != '\0';index++)
	{
		if(isNum(numStr[index]) == False)
		{
			raiseError("Expected decimal number");
			return 0;
		}
		num *= 10;
		num += atoi(numStr[index]);
		if((positive && num > maxPositive) || (positive == False && num > maxPositive + 1))
		{
			raiseError("Number is too large");
			return 0;
		}
	}
	if(positive)
		return num;
	else
	{
		num = num^mask;
		num++;
		return num;

	}
}

/*gets word and a string of it's 32 bit representation*/
String wordToString(Word data)
{
	static char symbols[] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
			'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};
	String output = (String) calloc(3, sizeof(char));
	output[1] = symbols[data&31];
	output[0] = symbols[(data >> 5)&31];
	output[2] = '\0';
	return output;
}


