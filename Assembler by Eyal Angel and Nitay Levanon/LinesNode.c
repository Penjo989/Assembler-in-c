/*
 * LinesNode.c
 *
 *  Created on: Aug 29, 2022
 *      Author: user
 */
#include "data.h"

/*Adds LineNode object to end of LineNode chain*/
void addLineNode(LinesNode *t, String _data){
    while(t->next != NULL) t = t->next;
    t->next = (LinesNode*)malloc(sizeof(LinesNode));
    t->next->line = getCopy(_data);
    t->next->next = NULL;
}

/*Prints LineNode chain*/
void printLines(LinesNode *t){
    t = t->next;
    while(t != NULL){
       printf("%s", t ->line);
       t = t->next;
    }
}
/*frees LinesChain*/
void freeLinesChain(LinesNode *head)
{
	LinesNode *tmp;

	   while (head != NULL)
	    {
	       tmp = head;
	       head = head->next;
	       free(tmp);
	    }
}
