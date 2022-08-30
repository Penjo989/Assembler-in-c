# Assembler By Eyal Angel And Nitay Levanon
A simple assembler written in c as the final project of course number 20465(The Open University Of Israel).

## Table Of Contents
- [Introduction](#intro)

    - [About The Course](#about)
    - [The Assembler And The Imaginary Computer](#imagine)
    
- [The Code](#code)

    - [Structures](#structs)

    - [The Pre-Assembler](#pre)
    
    - [The Assembler](#ass)

    - [Error Handeling](#error)

- [Summary And Reflection](#sum)

## <a name = "intro"></a>Introduction
### <a name = "about"></a>About The Course
Course number 20465 is all about learning ansi c. Throughout the course we've learned how to manipulate memory, use compilers and debuggers and overall produce elegant code in c.
The final project of the course was to write an assembler for an imaginary computer on which we will explain in the next paragraph.

### <a name = "imagine"></a>The Assembler And The Imaginary Computer
The imaginary assembly language for which we've written the assembler is just like every other assembly language. 

- The language has 16 types of instructions that get between 0 - 2 operands, 5 types of data statements and labels that can point to these statements\instructions .

- The language supports writing code in different files and linking between labels(although the linkage and loading parts of the assembler aren't part of the requirements for the final project).

- The language supports macros(which are handled in *[The Pre-Assembler phase](#pre)*).

The computer that the assembler is written for is 10 bit meaning every word in the computer is of size 10 bits and words are represented as 2 - 32 bit characters for example 100(decimal) is `$%`.

## <a name = "code"></a>The Code
### <a name = "structs"></a>Structures
<a name = "TableNode"></a>**TableNode** is a simple node that contains 3 fields:


- String label - just a string
- Word data - used for storing memory addresses and other information
- int line -  just holds the line number of the last read line when the node was created


```c
struct TableNode
{
	String label;
	struct TableNode *next;
	Word data;
	int line;
};

```
<a name = "Stripped"></a>**StrippedLine** is a structure that is used to parse through seperated words that are contained in a [TableNode](#TableNode) chain. 
The structure contains the following fields:

- TableNode words - a TableNode chain that contains the separated words
- int wordsLength - the amount of words in 'words'
- int wordIndex - the index of the current word being examined by the assembler


```c
struct StrippedLine
{
	TableNode words;
	int wordsLength;
	int wordIndex;
};
```
<a name = "Encoded"></a>**EncodedData** is used to hold the encoded data of an instruction.
it's fields are:

 - Word data - the list of encoded words
 - int dataLength - the amount of words encoded(varies from 0 - 4)
 - char op1 - the first operand's type
 - char op2 - the second operand's type

```c
struct EncodedData
{
	Word data[4];
	int dataLength;
	char op1, op2;
};

```
<a name = "LinesNode"></a>**LinesNode** is a simple node that contains only one field:
 
 
 - String line - just a string

```c
struct LinesNode{
	String line;
	struct LinesNode *next;
};

```
<a name = "MacroTable"></a>**MacroTable** is a node that represents a macro, it's fields are:

- String name - the name of the macro
- LinesNode lines - a pointer to the lines chain

```c
struct MacroTable
{
	String name;
	struct MacroTable *next;
	LinesNode *lines;
};
```


## <a name = "pre"></a>The Pre-Assembler
The pre-assembler is the part of the program in which the macros are replaced. 
The pre-assembler does this by reading line by line from the given `.as` file and following the next algorithm: if a macro declration is identified the pre-assembler adds a new [MacroTable](#MacroTable) node to an already existing chain. The pre-assembler than continues to add the lines it reads to the macro node up-until it reads an `endmacro` statement. The macro will than continue to parse through the file and if it detects a call to 
a macro it will write the saved lines to the new `.am` file.

finally if no errors occured(such as declaring a macro after a saved word) the Assembler will come into action.

## <a name = "ass"></a>The Assembler

The assembler part of the project is as expected the most complicated one. To put it simple, First the assembler goes over each line in the given `.am` file calling the `handelLine` function.
The `handelLine` function starts by stripping the line and putting it's words into a [StrippedLine](#Stripped) object. The function than procceeds to check if the first word stored in the 
object is a label, and if so it adds it to a symbol table. The function then proccedes to check if the next word in the line is a data statement or an instruction and for every option it acts 
according to the project's instructions.

After `handleLine` was called for each line, the function calls a function called `checkEntries` that makes sure that every label used in an `.entry` statement actually exists.

Because labels can be declared after being used in the `.am` file, the assembler calls a function named `linkLabels` which goes through every instance a label was used, checks if it exists in the symbol table and updates it's address in the final **machine image**.

If everything goes well after the `linksLabels` function the assembler will go on and create an `.ob` and save the binary code(which will be represented with 32 bits) and if necessery will also create  `.ent` and `.ext`
for the linkage and loading stages(which are not part of this project as mentioned before).

## <a name = "error"></a>Error Handeling
The project's error handeling is pretty simple. There is an external `error` variable which contains the state of the project. And there is a function called `raiseError` which 
gets a string describing the error. When `raiseError` is called it changes `error` to `True` and print's the given string in addition to all the information about the error(such as file, line and error num).

```c
void raiseError(String errorStr)
{
	static int errorNum = 1;
	printf("Error (%s) no.%d (line %d), %s.\n", file, errorNum++, lineCounter, errorStr);
	error = True;
}
```

## <a name = "sum"></a>Summary And Reflection
After spending the last 2 weeks working in the project, we've come to the conclusion that it was very mind-opening and informative because not only did it make us feel more comfortable with c, it also brought us one step closer to understanding how computers work. 

We had a great time working on this project and we learned alot about how to work as a team and how to plan a pretty large scale program and execute it well, Therefore we think the project was totaly worth it.
