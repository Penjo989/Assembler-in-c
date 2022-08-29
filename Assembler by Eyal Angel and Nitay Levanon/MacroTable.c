/*
 * MacroTable.c
 *
 *  Created on: Aug 29, 2022
 *      Author: user
 */
/*this file contains all of the functions intended for the MacroTable struct*/

#include "data.h"

/*gets name and MacroTable pointer and checks if a macro with that name is in the table
 * if it is returns False else returns True and adds a new macro to the end of the chain */
Boolean addMacro(String _name, MacroTable* t){
    while(t->next != NULL) {
        t = t->next;
        if(equals(t->name, _name)){
            return False;
        }
    }
    t->next = (MacroTable*)malloc(sizeof(MacroTable));
    t->next->lines = (LinesNode*)malloc(sizeof(LinesNode));
    t->next->name = getCopy(_name);
    t->next->lines->next = NULL;
    t->next->next = NULL;
    return True;
}

/*adds line to a macro's LinesNode object*/
void addLineToMacro(String line, MacroTable *t){
    addLineNode((t->lines), line);
}

/*checks if a macro with a given name already exists in the given MacroTable*/
Boolean checkIfInMacro(String _name, MacroTable *t){
    while(t->next != NULL){
        if (equals(t->next->name, _name))
            return True;
        t = t->next;
    }
    return False;
}
/*gets a name and a macroTable and returns a pointer to the LinesNode object that belongs to the
 * macro with the given name*/

LinesNode* getLines(String _name, MacroTable *t){
    while(t->next != NULL){
        if (equals(t->next->name, _name))
            return (t->next->lines);
        t = t->next;
    }
    return NULL;
}
/*frees all nodes*/
void freeMacroChain(MacroTable *head)
{
	MacroTable *tmp;
	   while (head != NULL)
	    {
	       tmp = head;
	       freeLinesChain(tmp->lines);
	       head = head->next;
	       free(tmp);
	    }
}

