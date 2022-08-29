/*Addressing methods*/
#define NONE -1
#define INT 0
#define MEM 1
#define STRCT 2
#define REG 3


#define MAX_SIZE 156 /*max size of encoded data(because the computer has (256 - 100 = 156 words free)*/
#define MAX_LINE_LENGTH 80
#define MEM_START_POS 100/*start of memory on the computer*/

#define False 0
#define True 1

#define INST 'i'/*represents instruction*/
#define DATA 'd'/*represents data statement*/


#define startMacro "marco"
#define endMacro "endmacro"


typedef char Boolean;
typedef char *String;
typedef unsigned int Word;


struct TableNode/*Simple node structure*/
{
	String label;
	struct TableNode *next;
	Word data;
	int line;
	char type; /*DATA or INST*/

};
typedef struct TableNode TableNode;

/*this structure holds all of the Chains, arrays and other important variables the the assembler uses*/
struct DataStructs
{
	TableNode symbolTable;
	TableNode externTable;/*Chain of all of the labels that were declared external*/
	TableNode entryTable;/*Chain of all of the labels that were declared entry*/
	TableNode labelCallTable;/*This chain contains all of the uses of labels in instructions and their position in instArr*/

	Word dataArr[MAX_SIZE];
	Word instArr[MAX_SIZE];

	int instCounter;
	int dataCounter;
};
typedef struct DataStructs DataStructs;


/*This structure is used to contain a chain of words that were in a line
 * and to track the progress of identifying each word*/
struct StrippedLine
{
	TableNode words;
	int wordsLength;
	int wordIndex;

};
typedef struct StrippedLine StrippedLine;
/*This structure is used to hold the data extracted from an instruction's operands*/
struct EncodedData
{
	Word data[4];
	int dataLength;
	char op1, op2;
};
typedef struct EncodedData EncodedData;

/*Simple node structure that holds only a string*/
struct LinesNode{
	String line;
	struct LinesNode *next;
};
typedef struct LinesNode LinesNode;


/*Simple node structure that is supposed to represent a macro*/
struct MacroTable
{
	String name;
	struct MacroTable *next;
	LinesNode *lines;
};
typedef struct MacroTable MacroTable;
