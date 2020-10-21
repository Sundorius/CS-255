/* 
   Assignment 1: Translate Program
   Katsifarakis Manos
   A.M.:csd3195
   file:translate.c
*/

/* @author Sundorius */

#include <stdio.h>

/* Defines for greek chars integer values. */
#define n 237
#define N 205
#define m 236
#define M 204
#define p 240
#define P 208
#define t 244
#define T 212

char const eng[][4] = { "'A\0", "·\0", "'E\0", "'H\0", "'I\0", "»\0", "'O\0", "½\0",
						"'Y\0", "'W\0", "i'\"\0", "A\0", "V\0", "G\0", "D\0", 
						"E\0", "Z\0", "H\0", "8\0", "I\0", "K\0", "L\0", "M\0", 
						"N\0", "KS\0", "O\0", "P\0", "R\0", "\0", "S\0", "T\0", /* Because the position 210 does not exist in array iso 8859-7, I filled it with "\0". */
						"Y\0", "F\0", "X\0", "PS\0", "W\0", "I\"\0", "Y\"\0", 
						"a'\0", "e'\0", "h'\0", "i'\0", "y'\"\0", "a\0", "v\0", 
						"g\0", "d\0", "e\0", "z\0", "h\0", "8\0", "i\0", "k\0", 
						"l\0", "m\0", "n\0", "ks\0", "o\0", "p\0", "r\0", "s\0",
						"s\0", "t\0", "y\0", "f\0", "x\0", "ps\0", "w\0", "i\"\0", 
						"y\"\0", "o'\0", "y'\0", "w'\0" }; 


/* The 3 states of the FSM represented by ann enum. */
typedef enum STATES 
{
	OTHER, F_M, F_N
}FSM_STATES;						

						
void f_n(int c);
void f_m(int c);
void f_other(int c);
void (*functions[3])( int c ) = {f_other, f_m, f_n};
FSM_STATES state;




/*
	Function that returns 1 if the character is a non-greek one or 0 if it is a greek one.
	It takes an integer and returns an integer.
 */
int find_lang(int c)
{
    if(c < 182) return 1;
    else return 0;
}

/*
	===============================================================
	 Functions that represent the FSM.
	===============================================================
*/

/*
	f_other function is responsible to call functions f_n,f_m
	or search and print a char , depending on the char.
*/
void f_other(int c)
{
    if(c == n || c == N)
	{
		state=F_N;
		functions[state](c);
	}
    else if(c == m || c == M)
	{
		state=F_M;
		functions[state](c);
	}
    else
    {
        if(find_lang(c) == 1)
		{
			state=OTHER;
			putchar(c);
		}
        else
        {
			state=OTHER;
            printf("%s", &eng[c-182][0]);
        }
    }
}


/*
	f_n is a recursive function.
	This function is called when the greek char n or N is given as input.
 */	
void f_n(int c)
{
    int nextChar=getchar(); /* get next character */
    if(nextChar == N || nextChar == n)
    {
        putchar(eng[c-182][0]);
		state=F_N;
        functions[state](nextChar);
    }
    else if(c == N)
    {
		state=OTHER;
        if(nextChar == T || nextChar == t)
        {
            putchar('D');
        }
		else
		{
			state=OTHER;
			putchar(eng[c-182][0]);
			functions[state](nextChar);
		}
    }
	else if(c == n)
	{
		state=OTHER;
		if(nextChar == T || nextChar == t)
		{
			putchar('d');
		}
		else
		{
			state=OTHER;
			putchar(eng[c-182][0]);
			functions[state](nextChar);
		}
	}  
}


/*
	f_m is a recursive function.
	This function is called when the greek char m or M is given as input.
 */	
void f_m(int c)
{
    int nextChar=getchar(); /* get next character */
    if(nextChar == M || nextChar == m)
    {
        putchar(eng[c-182][0]);
		state=F_M;
        functions[state](nextChar);
    }
    else if(c == M)
    {
		state=OTHER;
        if(nextChar == P || nextChar == p)
        {
            putchar('B');
        }
		else
		{
			state=OTHER;
			putchar(eng[c-182][0]);
			functions[state](nextChar);
		}
    }
    else if(c == m)
    {
		state=OTHER;
		if(nextChar == P || nextChar == p)
		{
			putchar('b');
		}
		else
		{
			state=OTHER;
			putchar(eng[c-182][0]);
			functions[state](nextChar);
		}
    }
}


/*
	===============================================================
	 Main Function.
	===============================================================
*/
/* Reads from the input stream and stops when there is nothing else to read. */
int main(void)
{
    int c;
	state=OTHER;
    while( (c = getchar()) !=EOF )
    {
        functions[state](c);
    }
	printf("\n");
    return 0;
}
