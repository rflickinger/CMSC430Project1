// CMSC 430 Compiler Theory and Design
// Project 1 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the functions that produces the 
// compilation listing

#include <cstdio>
#include <string>
//#include <stdbool.h>
//#include <stdio.h>
#include <queue>

using namespace std;

#include "listing.h"

static int lineNumber;
static string error = "";
static int totalErrors = 0;
static int lexicalErrors = 0;
static int syntaxErrors = 0;
static int semanticErrors = 0;
static queue<string> errors;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{
	printf("\r");
	displayErrors();
	printf("     \n");
	if(!lexicalErrors && !syntaxErrors && !semanticErrors) 
	{
		printf("Compiled Successfully");
	}
	else
	{
		printf("Lexical Errors: %d\n", lexicalErrors);
		printf("Syntax Errors %d\n", syntaxErrors);
		printf("Semantic Errors %d\n", semanticErrors);
	}
	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate ",
		"Semantic Error, Undeclared " };

	error = messages[errorCategory] + message;
	if(errorCategory == 0)
	{
		lexicalErrors++;
	}
	if(errorCategory == 2 || errorCategory == 3 || errorCategory == 4)
	{
		semanticErrors++;
	}
	if(errorCategory == 1)
	{
		syntaxErrors++;
	}
	totalErrors++;
	errors.push(error);
}

void displayErrors()
{
	while(!errors.empty()) 
	{
		error = errors.front();
		if (error != "")
			printf("%s\n", error.c_str());
		error = "";
		errors.pop();
	}
}
