#include <kernel/mm/physical.h>
#include <kernel/mm/paging.h>
#include <kernel/kernel.h>
#include <kernel/console.h>

extern void start;
extern void end;

// enough for 4GB's of physical memory is 131072 bits which is 128KB's in size
// enough for 16MB' of physical memory is 512bytes in size

char pm_bitmap[512];

void physical_init( DWORD mem_upper )
{
	int pm_bitmap_size;
	DWORD physicalAddress;
	
	// calculate the size of the bitmap so we have 1bit
	// for every 4KB page in actual physical memory
	pm_bitmap_size = 512;//( ( ( ( mem_upper / SIZE_1KB ) + 1 ) * 256 ) / 8 );
	
	//pm_bitmap = (char *)&end;
	
	// clear the bitmap so all pages are marked as free
	memset( (BYTE *)pm_bitmap, 0x00, pm_bitmap_size );

	// reserver the bios and video memory
	for( physicalAddress=0xA0000 ; physicalAddress<0x100000 ; physicalAddress+=SIZE_4KB )
		physical_pageAllocAddress( physicalAddress );
		
	// reserve all the memory currently being taken up by the
	// kernel and the physical memory bitmap tacked on to the
	// end of the kernel image, this avoids us allocating this
	// memory later on, lets hope it works :)
	//(pm_bitmap + pm_bitmap_size )
	for( physicalAddress=(DWORD)&start ; physicalAddress<(DWORD)&end ; physicalAddress+=SIZE_4KB )
		physical_pageAllocAddress( physicalAddress );
}

DWORD physical_pageAlloc()
{
	DWORD physicalAddress = 0x00000000;

	// linear search! ohh dear :)
	while( !physical_isPageFree( physicalAddress ) )
		physicalAddress += SIZE_4KB;

	return physical_pageAllocAddress( physicalAddress );
}

DWORD physical_pageAllocAddress( DWORD physicalAddress )
{
	if( physical_isPageFree( physicalAddress ) )
	{
		pm_bitmap[ BITMAP_BYTE_INDEX( physicalAddress ) ] |= ( 1 << BITMAP_BIT_INDEX( physicalAddress ) );
		return physicalAddress;
	}
	return 0L;
}

void physical_pageFree( DWORD physicalAddress )
{
	if( !physical_isPageFree( physicalAddress ) )
		pm_bitmap[ BITMAP_BYTE_INDEX( physicalAddress ) ] &= ~( 1 << BITMAP_BIT_INDEX( physicalAddress ) );
}

inline int physical_isPageFree( DWORD physicalAddress )
{
	if( pm_bitmap[ BITMAP_BYTE_INDEX( physicalAddress ) ] & ( 1 << BITMAP_BIT_INDEX( physicalAddress ) ) )
		return FALSE;
	return TRUE;
}

