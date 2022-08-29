#include <stdio.h>
#include "macros.h"

/*main.c functions*/
void run(String);

/*stdlib.h functions*/
void *malloc(size_t size);
void *calloc(size_t nitems, size_t size);
void free(void *ptr);

/*Assembler.c functions*/
void runAssembler();
void handleLine(String, DataStructs *);
void setupVars(DataStructs *);
Boolean checkLabel(StrippedLine *,  DataStructs *);
void linkLabels(DataStructs *);
void checkEntries(DataStructs *);
void freeDataStructs(DataStructs *);

/*TableNode.c functions*/
void addNode(String , Word , TableNode *, Boolean, char);
void removeLast(TableNode *);
void freeChain(TableNode *);
Boolean checkIfIn(String , TableNode *);
Word getData(String , TableNode *);
int getType(String , TableNode *);
String getLabel(int , TableNode *);
void printNodes(TableNode *);
void resetNext(TableNode *);
TableNode *getNode(TableNode *, int);
TableNode *getNodeByLabel(TableNode *, String);
TableNode *getLast(TableNode *);
int getChainLength(TableNode *);

/*functions.c functions*/
void raiseError(String);
void stripLine(String , StrippedLine *);
Boolean checkSyntax(String);
TableNode *stripCommas(StrippedLine *, TableNode *);
int atoi(char);
Boolean isRegister(String);
String getFileName(String filePath);
String changeFileType(String fileName, String newType);

/*dataFunctions.c functions*/
Boolean checkData(StrippedLine *, DataStructs *, Boolean);
void dataFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel);
void stringFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel);
void structFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel);
void entryFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel);
void externFunc(StrippedLine *sl, DataStructs *ds, Boolean addLabel);
void updateDataLabel(DataStructs *ds, Boolean addLabel);
void addDataWord(Word num, DataStructs *ds);
void addString(String str, DataStructs *ds);

/*instructionFunctions*/
Boolean checkInstruction(StrippedLine *, DataStructs *, Boolean);
void movFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void cmpFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void addFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void subFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void notFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void clrFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void leaFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void incFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void decFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void jmpFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void bneFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void getFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void prnFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void jsrFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void rtsFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void hltFunc(StrippedLine *sl, EncodedData *ed, DataStructs *ds, Boolean addLabel);
void addInstCode(int opcode, char op1, char op2, DataStructs *ds);
void addEncodedData(EncodedData *ed, DataStructs *ds);
void addInstWord(Word num, DataStructs *ds);
void getEncodedData(StrippedLine *sl, EncodedData *ed, DataStructs *ds);
void updateInstLabel(DataStructs *ds, Boolean addLabel);

/*mathFunctions*/
Word getNum(String, Boolean);
String wordToString(Word);

/*stringFunctions*/

Boolean equals(String, String);
String getCopy(String);
int getLength(String);
String trim(String, int);
Boolean isNum(char);
Boolean isAlphabetical(char);
String extractString(String);

/*savingFunctions*/
void saveObFile(DataStructs *);
void saveEntryFile(DataStructs *);
void saveExternFile(DataStructs *);
void WriteToFile(String, FILE*);
void WriteLinesToFile(LinesNode*, FILE*);




/*preassemblerfunctions */

void runPreAssembler(String);
void processFile(String, MacroTable*, MacroTable*);
Boolean macroSearch(StrippedLine*, Boolean*, MacroTable*, MacroTable*);
Boolean endMacroSearch(StrippedLine*, Boolean*);
void checkIfSavedWord(String );

/*MacroTablefunctions*/

Boolean addMacro(String, MacroTable*);
void addLineToMacro(String , MacroTable*);
Boolean checkIfInMacro(String, MacroTable*);
LinesNode* getLines(String, MacroTable*);
void freeMacroChain(MacroTable *);

/*LineNodefunctions*/

void addLineNode(LinesNode*, String);
void printLines(LinesNode*);
void freeLinesChain(LinesNode *);

