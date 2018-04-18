#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char MOT[][11]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char POT[][7]={"START","END","LTORG","EQU","ORIGIN"};
char reg[][5]={"AREG","BREG","CREG","DREG"};
char decl[][3]={"DC","DS"};

int POOLTAB[10];
int countl=0,counts=0,countp=0;
typedef struct symbol
{
	int s_no;
	char s_name[200];
	int s_add;
}symbol;
	symbol s[10];
typedef struct litral
{
	int l_no;
	char l_name[100];
	int l_add;
}litral;
	
	litral l[10];

