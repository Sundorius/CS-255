#include "mystring.h"

/* @author Sundorius */

/* 
	Returns the length of the C string Str. 
	It is a checked runtime error for Str to be NULL.
*/
size_t ms_length(const char *Str)
{
    size_t length= 0;
    assert(Str != NULL);
    while (Str[length] != '\0')
        length++;
    return length;
}

/* 
	Copies the string pointed by Start 
	(including the terminating null character)
	into the string pointed by Dest.If Dest is not large
	enough, program behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_copy(char *Dest, const char *Start)
{
	int i=0;
    assert(Start != NULL);
    assert(Dest != NULL);
    while(Start[i]!='\0')
    {
        Dest[i]=Start[i];
		i++;
    }
	Dest[i]='\0';
    return Dest;
}

/* 
	Copies the first n characters of the string pointed
	by Start into the string pointed by Dest.If Dest is 
	not large enough, program behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_ncopy(char *Dest, const char *Start, size_t n)
{
	int i=0;
    assert(Start != NULL);
    assert(Dest != NULL);
    while( n>0 && Start[i]!='\0')
    {
        Dest[i] = Start[i];
        n--;
        i++;
    }
    while( n>0 )
    {
        Dest[i] = '\0';
        i++;
        n--;
    }
    return Dest;
}

/*
	Appends a copy of the Start string to the end of 
	the Dest string, overwriting the null character in 
	the Dest string,but adding it again after the 
	concatanation.If Dest is not large enough, program
	behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_concat(char *Dest, const char *Start)
{
	int i=0, j=0;
    assert(Start != NULL);
    assert(Dest != NULL);
    while(Dest[i]!='\0')
        i++;
    while(Start[j]!='\0')
    {
        Dest[i+j] = Start[j];
        j++;
    }
    Dest[i+j]='\0';
    return Dest;
}

/*
	Appends the first n characters of the Start string 
	to the end of the Dest string, overwriting the null 
	character in the Dest string,but adding it again after 
	the concatanation.If Dest is not large enough, program
	behavior is unpredictable.
	It is a checked runtime error for Start to be NULL.
	It is a checked runtime error for Dest to be NULL.
*/
char * ms_nconcat(char *Dest, const char *Start, size_t n)
{
	int i=0, j=0;
    assert(Dest != NULL);
    assert(Start != NULL);
    while(Dest[i]!='\0')
        i++;
    while( n>0 && Start[j]!='\0')
    {
        Dest[i+j] = Start[j];
        j++;
        n--;
    }
    Dest[i+j] = '\0';
    return Dest;
}

/*
	It compares the strings Str1 and Str2 and returns 
	an integer. If Str1 is greater than Str2 it returns 1,
	if it is less than Str2 it returns -1 and if the two 
	strings are equal it returns 0.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
int ms_compare(const char *Str1, const char *Str2)
{
	int res=0, i=0, count1=0, count2=0;
    	assert(Str1 != NULL);
    	assert(Str2 != NULL);
	if(!ms_length(Str2)) return 1; /* If Str2 string is empty. */
	while( Str1[i]!='\0' && Str2[i]!='\0')
	{
		if( (res=Str1[i]-Str2[i])!=0 ) break;
		count1++;
		count2++;
		i++;
	}
	if(res == 0)
	{
		if( (ms_length(Str1)-count1)<(ms_length(Str2)-count2) ) return -1;
		else if( (ms_length(Str1)-count1)>(ms_length(Str2)-count2) ) return 1;
		else return 0;
	}
	else if(res < 0) return -1;
	else return 1;	
}

/*
	It compares, at most, the first n bytes of strings 
	Str1 and Str2 and returns an integer. If Str1 is 
	greater than Str2 it returns 1,	if it is less than 
	Str2 it returns -1 and if the two strings are equal 
	it returns 0.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
int ms_ncompare(const char *Str1, const char *Str2, size_t n)
{
	int s2_len, res=0, i=0;
    assert(Str1 != NULL);
    assert(Str2 != NULL);
	s2_len=ms_length(Str2);
	if(!s2_len) return 1; /* If Str2 string is empty. */
	while( n>0 && Str1[i]!='\0' && Str2[i]!='\0')
	{
		if( (res=Str1[i]-Str2[i])!=0 ) break;
		i++;
		n--;
	}
	if(res == 0) return 0;
	else if(res < 0) return -1;
	else return 1;	
}

/*
	Finds the first occurrence of the substring Str2
	in the string Str1. If not found, returns NULL,
	else it returns a pointer at the position where 
	it was found.
	It is a checked runtime error for Str1 to be NULL.
	It is a checked runtime error for Str2 to be NULL.
*/
char *ms_search(const char *Str1, const char *Substring)
{
	int s2_len, s1_len;
	assert(Str1 != NULL);
    assert(Substring != NULL);
	s2_len=ms_length(Substring);
	s1_len=ms_length(Str1);
	if(!s2_len) return Str1; /* If Substring string is empty. */
	while( s1_len >= s2_len )
	{
		s1_len--;
		if( !ms_ncompare(Str1, Substring, s2_len) ) return Str1;
		Str1++;
	}
	return NULL;
}
int main(void)
{
	char str1[20] = "Computer";
    char str2[20] = "ute";
	char tmp1[20];
	char tmp2[20];
	
	printf("ms_length: length of Str1: %u\n", ms_length(str1));
	printf("ms_length: length of Str2: %u\n", ms_length(str2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_copy: copy str2 to str1: %s\n", ms_copy(tmp1, tmp2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_ncopy: copy %d chars of str2 to str1: %s\n", 2, ms_ncopy(tmp1, tmp2, 2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_concat: concat str2 to str1: %s\n", ms_concat(tmp1, tmp2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_nconcat: concat %d chars of str2 to str1: %s\n", 2,  ms_nconcat(tmp1, tmp2, 2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_compare: compare str1 to str2: %d\n", ms_compare(tmp1, tmp2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_ncompare: compare str1 to str2: %d\n", ms_ncompare(tmp1, tmp2, 2));
	
	ms_copy(tmp1, str1);
	ms_copy(tmp2, str2);
	printf("ms_search: search str2 to str1: %s\n", ms_search(tmp1, tmp2));
	return 0;
}