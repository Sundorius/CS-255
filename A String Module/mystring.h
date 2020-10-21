#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* @author Sundorius */

/* 
	Returns the length of the string Str. 
	It is a checked runtime error for Str to be NULL.
*/
size_t ms_length(const char *Str);

/* 
	Copies the string pointed by Start 
	(including the terminating null character)
	into the string pointed by Dest.If Dest is not large
	enough, program behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_copy(char *Dest , const char *Start);

/* 
	Copies the first n characters of the string pointed
	by Start into the string pointed by Dest.If Dest is 
	not large enough, program behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_ncopy(char *Dest , const char *Start , size_t n);

/*
	Appends a copy of the Start string to the end of 
	the Dest string, overwriting the null character in 
	the Dest string,but adding it again after the 
	concatanation.If Dest is not large enough, program
	behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_concat(char *Dest, const char *Start);

/*
	Appends the first n characters of the Start string 
	to the end of the Dest string, overwriting the null 
	character in the Dest string,but adding it again after 
	the concatanation.If Dest is not large enough, program
	behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_nconcat(char *Dest , const char *Start , size_t n);

/*
	It compares the strings Str1 and Str2 and returns 
	an integer. If Str1 is greater than Str2 it returns 1,
	if it is less than Str2 it returns -1 and if the two 
	strings are equal it returns 0.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
int ms_compare(const char *Str1,  const char *Str2);

/*
	It compares, at most, the first n bytes of strings 
	Str1 and Str2 and returns an integer. If Str1 is 
	greater than Str2 it returns 1,	if it is less than 
	Str2 it returns -1 and if the two strings are equal 
	it returns 0.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
int ms_ncompare(const char *Str1 , const char *Str2 , size_t n);

/*
	Finds the first occurrence of the substring Str2
	in the string Str1. If not found, returns NULL,
	else it returns a pointer at the position where 
	it was found.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
char *ms_search(const char *Str1, const char *Substring);