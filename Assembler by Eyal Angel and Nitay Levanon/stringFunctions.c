/*
 * stringFunctions.c
 *
 *  Created on: Aug 24, 2022
 *      Author: user
 */
#include "data.h"
/*Gets 2 string and checks if they are equal*/
Boolean equals(String a, String b)
{
	int i = 0;
	while(a[i] != '\0' && b[i] != '\0')
	{
		if(a[i] != b[i])
			return False;
		i++;
	}
	return (a[i] == b[i]) ? True : False;
}
/*gets a string and returns a copy of it*/
String getCopy(String a)
{
	String b;
	int index = 1;
	while(a[index] != '\0')
		index++;
	b = (String) calloc(index, sizeof(char));
	for(;index > 0; index--)
		b[index - 1] = a[index - 1];
	return b;
}
/*gets a string and returns it's length*/
int getLength(String a)
{
	int i = 0;
	while(a[i] != '\0') i++;
	return i;
}
/*trims the end of a given string by a given amount and returns the new trimmed string */
String trim(String a, int amount)
{
	int aLength = getLength(a);
	String b = (String) calloc(aLength - amount + 1, sizeof(char));
	int i = 0;
	for(;i < aLength - amount; i++) b[i] = a[i];
	b[aLength - amount] = '\0';
	return b;
}
/*checks if the given char is a digit*/
Boolean isNum(char c)
{
	return c >= '0' && c <= '9';
}

/*checks if the given char is a alphabetical character*/
Boolean isAlphabetical(char c)
{
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}
/*gets a string and extracts it from it's apostrophes*/
String extractString(String a)
{
	int index;
	if(a[0] != '"')
		raiseError("Expected \" at start of string argument");
	index = 1;
	while(a[index] != '\0')
	{
		if(a[index] == '"')
		{
			if(a[index + 1] == '\0')
				return trim(&a[1], 1);
			else
				raiseError("Expected \" at end of string argument");
		}
		index++;
	}
	raiseError("Expected \" at end of string argument");
	return "";

}
