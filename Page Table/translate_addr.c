#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"assign3.h"

void syserr( const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void usage( char *progname) {
	fprintf(stderr, "Usage:");
	fprintf(stderr, "\t%s binary-address-file\n", progname);
	exit(EXIT_FAILURE);
}//end usage

/* 
 * retrieve page index from virtual address
 * top n number of bits from virtual address are
 * the index into the page table
 *
 * returns the top page bits from virtual address
 */
unsigned short get_pgidx( unsigned short virt_addr, int page_bits, int offset_bits) {
	static unsigned short bitmask[9] = { 0xF000, 0xF800, 0xFC00, 0xFE00,  
									 	 0xFF00, 0xFF80, 0xFFC0, 0xFFE0, 0xFFF0 };
	unsigned short pgidx = 0;
	pgidx = virt_addr & bitmask[page_bits];
	pgidx = pgidx >> offset_bits;
	return pgidx;
}//end get_pgidx

/*
 * retrieve offset from virtual address
 * bottom n number of bits from virtual address
 * are the offset into the physical (disk) address
 *
 * returns the bottom offset bits from the virtual address
 */
unsigned short get_offset( unsigned short virt_addr, int offset_bits) {
	static unsigned short bitmask[16] = { 0x0000, 0x0001, 0x0003, 0x0007,
										  0x000F, 0x001F, 0x003F, 0x007F,
										  0x00FF, 0x01FF, 0x03FF, 0x0FFF,
										  0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };
	if( offset_bits == 16)
		offset_bits = offset_bits - 1;

	return ( virt_addr & bitmask[offset_bits] );
}// end get_offset

/*
 * convert unsigned long to unsigned short
 *
 * returns the bottom 2 bytes of an unsigned long
 */
unsigned short ultosh( unsigned long logical_addr) {
	return ( logical_addr & SHORT );
}// end ultosh

/*
 * makes a physical address from a logical address
 * concatenates the frame number and offset
 *
 * returns a physical address as an unsigned long
 */
unsigned long make_phys_addr( unsigned long logical_addr, int frame_bits, int page_bits, int offset_bits) {
	static unsigned short bitmask[16] = { 0x0000, 0x0001, 0x0003, 0x0007,
										  0x000F, 0x001F, 0x003F, 0x007F,
										  0x00FF, 0x01FF, 0x03FF, 0x0FFF,
										  0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };
	static unsigned short pgtable[32] = { 2, 4, 1, 7, 3, 5, 6 }; // page numbers
	static unsigned short phys_frames[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	unsigned short virt_addr, frame_num;
	unsigned short offset, pgidx;
	unsigned long phys_addr = 0;

	// convert logical address to short for easier manipulation
	virt_addr = ultosh( logical_addr);
	// get page index
	pgidx = get_pgidx( virt_addr, page_bits, offset_bits);
	// get offset into page
	offset = get_offset( virt_addr, offset_bits);
	// get the frame number 
	frame_num = phys_frames[ pgtable[ pgidx ]];


	if( frame_bits == 16)
		frame_bits = frame_bits - 1;

	// Add frame number to physical address
	phys_addr |= ( frame_num & bitmask[frame_bits] ); // only a certain portion of frame number is valid
	phys_addr = phys_addr << offset_bits; // shift frame number to its appropriate position

	// add offset to physical address and return
	return ( phys_addr | offset );
}// end make_phys_addr
