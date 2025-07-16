
/*
Bank-switching using the MMC3 mapper.
We use a special linker config that sets up
64 KB of PRG ROM and 64 KB of CHR ROM.
Macros are used to set MMC3 registers and switch banks.
CC65 #pragma directives are used to put things in various
PRG ROM segments (CODE0-CODE6, CODE).
*/

// bank-switching configuration
#define NES_MAPPER 4		// Mapper 4 (MMC3)
#define NES_PRG_BANKS 4		// # of 16KB PRG banks
#define NES_CHR_BANKS 8		// # of 8KB CHR banks

#include <peekpoke.h>
#include <string.h>
#include "neslib.h"

//#resource "famistudio_note_table_lsb.bin"
//#resource "famistudio_note_table_msb.bin"
//#link "famistudio.s"

#include "famistudio.h"


//#link "song.s"
extern unsigned char music_data_shatterhand[];

// link the pattern table into CHR ROM
//#link "chr_generic.s"

#define MMC_MODE 0x00

#define MMC3_SET_REG(r,n)\
	POKE(0x8000, MMC_MODE|(r));\
	POKE(0x8001, (n));

#define MMC3_CHR_0000(n) MMC3_SET_REG(0,n)
#define MMC3_CHR_0800(n) MMC3_SET_REG(1,n)
#define MMC3_CHR_1000(n) MMC3_SET_REG(2,n)
#define MMC3_CHR_1400(n) MMC3_SET_REG(3,n)
#define MMC3_CHR_1800(n) MMC3_SET_REG(4,n)
#define MMC3_CHR_1C00(n) MMC3_SET_REG(5,n)
#define MMC3_PRG_8000(n) MMC3_SET_REG(6,n)
#define MMC3_PRG_A000(n) MMC3_SET_REG(7,n)

#define MMC3_MIRROR(n) POKE(0xa000, (n))

void main(void)
{
  famistudio_init(FAMISTUDIO_PLATFORM_NTSC, music_data_shatterhand);  
  nmi_set_callback(famistudio_update);
  famistudio_music_play(0);  
  for(;;) {
    //famistudio_update();
    //ppu_wait_nmi();
  }
}
