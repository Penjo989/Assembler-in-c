
#include "data.h"

extern String file;


/*saves final object file*/
void saveObFile(DataStructs *ds)
{
	FILE *fp;
	int i;
	String newFileName = changeFileType(file, "ob");
	fp = fopen(newFileName, "w");
	if(fp == NULL)
	{
		printf("An error occurred while opening: %s\n", newFileName);
		return;
	}

	fprintf(fp, " %s %s \n", wordToString(ds->instCounter), wordToString(ds->dataCounter));
	i = 0;
	for(; i < ds->instCounter; i++)
		fprintf(fp, "%s\t%s\n", wordToString(i + MEM_START_POS), wordToString(ds->instArr[i]));
	for(i = 0; i < ds->dataCounter; i++)
		fprintf(fp, "%s\t%s\n", wordToString(i + MEM_START_POS + ds->instCounter), wordToString(ds->dataArr[i]));
	fclose(fp);
}
/*saves final entry file*/
void saveEntryFile(DataStructs *ds)
{
	FILE *fp;
	TableNode *ent = &(ds->entryTable);
	Word address;
	TableNode *symbolTableNode;
	String newFileName = changeFileType(file, "ent");
	fp = fopen(newFileName, "w");
	if(fp == NULL)
	{
		printf("An error occurred while opening: %s\n", newFileName);
		return;
	}

	ent = ent->next;
	while(ent != NULL)
	{
		symbolTableNode = getNodeByLabel(&(ds->symbolTable), ent->label);
		address = symbolTableNode->data + MEM_START_POS;
		address += (symbolTableNode->type == DATA) ? ds->instCounter : 0;
		fprintf(fp, "%s\t%s\n", ent->label, wordToString(address));
		ent = ent->next;
	}

	fclose(fp);
}
/*saves final extern file*/
void saveExternFile(DataStructs *ds)
{
	FILE *fp;
	TableNode *lc = &(ds->labelCallTable);
	Word address;
	String newFileName = changeFileType(file, "ext");
	fp = fopen(newFileName, "w");
	if(fp == NULL)
	{
		printf("An error occurred while opening: %s\n", newFileName);
		return;
	}
	lc = lc->next;
	while(lc != NULL)
	{
		if(checkIfIn(lc->label, &(ds->externTable)))
		{
			address = lc->data + MEM_START_POS;
			fprintf(fp, "%s\t%s\n", lc->label, wordToString(address));
		}
		lc = lc->next;
	}

	fclose(fp);
}
/*write line to file*/
void WriteToFile(String line, FILE *file)
{
	fprintf(file, "%s", line);
}
/*gets LinesNode object and file and writes all of the lines from the node to the file*/
void WriteLinesToFile(LinesNode *lines, FILE *file){
	while(lines != NULL){
		WriteToFile(lines->line, file);
		lines = lines -> next;
	}
}
