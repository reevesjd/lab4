/*
    Name:   Memory.cpp
    Desc:   Implementation of the Memory class
    Auth:   Hunter Eller
    Date:   2/4/2019
*/
#include <iostream>
#include <iomanip>
#include <cstdint>

#include "Memory.h"
#include "Tools.h"

/*-------------------------------------------------------------------------
  Constructor:  Memory 
  Description:  Store 64-bit value to a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
Memory::Memory()
{
	mem{};
    memError = 0;
}
/*-------------------------------------------------------------------------
  Function:     store 
  Description:  Store 64-bit value to a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
void   Memory::store	(uint64_t waddr, uint64_t val) // takes word address
{
	if (waddr < 0 || waddr > 1023)
	{
		memError = 1;
	}
	else
	{
		memError = 0;
		mem[waddr] = val;
	}
}
/*-------------------------------------------------------------------------
  Function:     fetch 
  Description:  Fetch a 64-bit value from a word address in memory. Set
                memError if address out of bounds.
--------------------------------------------------------------------------*/
uint64_t  Memory::fetch	(uint64_t waddr) // takes word address
{
	if (waddr < 0 || waddr > 1023)
	{
		memError = 1;
	}
	else
	{
		memError = 0;
		mem[waddr];
	}
}
/*--------------------------------------------------------------------
   Function:   getByte

   Description:  Returns a byte from the specified byte address
                 of Y86 memory array. 
                 If address is out of range the error status is set.
--------------------------------------------------------------------*/
unsigned char   Memory::getByte	(uint64_t byteAddress) // takes byte address
{
	
}
/*--------------------------------------------------------------------
   Function:     putByte

   Description:  Write a single byte into the Y86 simulated memory
                 at the byte address specified by 'address'.
                 If address is out of range the error status is set.                 
--------------------------------------------------------------------*/
void  Memory::putByte(uint64_t byteAddress, uint8_t value) // takes byte address
{
	// your code here
}
/*--------------------------------------------------------------------
   Function:   getWord

   Description:  Returns word starting from the specified byte address.
                 No part of the word must lie outside memory range.
--------------------------------------------------------------------*/
uint64_t   Memory::getWord	(uint64_t byteAddress)	
{
	return 0;
}
/*----------------------------------------------------------------------------------------------
   Function:   putWord

   Description:  Writes a word to memory starting at the specified byte address.
                 No part of the word must lie outside memory range. If there is
				 a memory error (out of range) the memory should not be changed.
------------------------------------------------------------------------------------------------*/
void Memory::putWord	(uint64_t byteAddress, uint64_t wordValue) // byte address must be 8-byte word aligned
{
	// your code here
}
/*--------------------------------------------------------------------
   Function:   reset

   Description:  Clears memory to all zero. Clears error status.
                 
--------------------------------------------------------------------*/
void  Memory::reset	(void) // clears memory to all zero
{
	memset(mem, 0, 64);
	memError = 0;
}
