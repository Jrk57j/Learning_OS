#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"assign3.h"

/* NOTES:
 *
 * 1024 (2^10) bytes total hdd memory
 *  128 (2^7)  bytes for page/block sz
 *
 *    8 pages/blocks total on disk (2^10 / 2^7 => 2^3 = 8)
 *   12 bit virtual addr
 *   12 - 7 = 5 -> 2^5 = 32 virtual pages
 *   32 entries on page table
 */

int main(int argc, char *argv[])
{
	unsigned long logical_addr;
	unsigned long phys_addr;
	FILE *input, *output;

	if(argc != 2)
		usage(argv[0]);
	
	input = fopen(argv[1], "rb");
	if(!input)
		syserr("Unable to open input file");

	output = fopen("output-part1", "wb");
	if(!output)
		syserr("Unable to open output file");

	while( fread( &logical_addr, sizeof(unsigned long), 1, input)) {
		phys_addr = make_phys_addr( logical_addr, FRAMESZ, PGBITS, OFFSETBITS);
		fwrite( &phys_addr, sizeof(unsigned long), 1, output);
	}

	fclose(input);
	fclose(output);
	exit(EXIT_SUCCESS);
}//end main
