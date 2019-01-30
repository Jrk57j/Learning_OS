#define SHORT     0xFFFF  // two bytes
#define DISKSZ      1024  // bytes
#define PGSZ         128  // bytes
#define FRAMESZ       10  // bits
#define VIRT_ADDR     12  // bits -> need 2 bytes
#define OFFSETBITS     7  // bits
#define PGBITS  VIRT_ADDR - OFFSETBITS


// Part 1
void syserr( const char *msg);
void usage( char *progname);
unsigned short get_pgidx( unsigned short virt_addr, int page_bits, int offset_bits);
unsigned short get_offset( unsigned short virt_addr, int offset_bits);
unsigned short ultosh( unsigned long logical_addr);
unsigned long make_phys_addr( unsigned long logical_addr, int frame_bits, int page_bits, int offset_bits);
