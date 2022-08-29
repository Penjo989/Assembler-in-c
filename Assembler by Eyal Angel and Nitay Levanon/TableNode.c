#include "data.h"
/*This file contains all of the functions intended for the TableNode struct*/

extern int lineCounter;


/*adds node to end of given chain*/
void addNode(String label, Word data, TableNode *t, Boolean duplicate, char type)
{
	while(t->next != NULL) t = t->next;
	t->next = (TableNode *) malloc(sizeof(TableNode));
	t->next->data = data;
	t->next->type = type;
	if(duplicate) t->next->label = getCopy(label);/*creates copy of given string*/
	else t->next->label = label;

	t->next->line = lineCounter;
	t->next->next = NULL;
}
/*removes last node in given chain*/
void removeLast(TableNode *t)
{
	if(t->next == NULL)
		return;
	if((t->next)->next == NULL)
	{
		t->next = NULL;
		return;
	}
	while((t->next)->next != NULL)
		t = t->next;
	t->next = NULL;
}
/*frees all nodes*/
void freeChain(TableNode *head)
{
	   TableNode *tmp;

	   while (head != NULL)
	    {
	       tmp = head;
	       head = head->next;
	       free(tmp);
	    }
}
/*checks if node with given label is in the given chain, returns True if so*/
Boolean checkIfIn(String label, TableNode *t)
{
	while(t != NULL)
	{
		if(equals(t->label, label)) return True;
		t = t->next;
	}
	return False;
}
/*returns data of node with the given label*/
Word getData(String label, TableNode *t)
{
	while(t != NULL)
	{
		if(equals(t->label, label)) return t->data;
		t = t->next;
	}
	return 0;
}
/*returns type of node with the given label*/
int getType(String label, TableNode *t)
{
	while(t != NULL)
	{
		if(equals(t->label, label)) return t->type;
		t = t->next;
	}
	return 0;
}
/*returns the label of the node in the given index*/
String getLabel(int index, TableNode *t)
{
	while(t->next != NULL && index-- > 0) t = t->next;
	return t->label;
}
/*prints chain*/
void printNodes(TableNode *t)
{
	while(t != NULL)
	{
		printf("label:%s \t data:\t %d \n", t->label, t->data);
		t = t->next;
	}
}
/*resets next to Null and label to ''*/
void resetNext(TableNode *t)
{
	t->next = NULL;
	t->label = "";
}

/*gets node in given index*/
TableNode *getNode(TableNode *t, int index)
{
	while(t->next != NULL && index > 0)
	{
		t = t->next;
		index-= 1;
	}
	return t;
}
/*returns node with given label*/
TableNode *getNodeByLabel(TableNode *t, String label)
{
	while(t->next != NULL && equals(t->label, label) == False)
		t = t->next;
	return t;
}
/*returns last node*/
TableNode *getLast(TableNode *t)
{
	while(t->next != NULL) t = t->next;
	return t;
}
/*returns chain length */
int getChainLength(TableNode *t)
{
	int length = 0;
	for(;t->next != NULL;length++, t = t->next);
	return length;
}
