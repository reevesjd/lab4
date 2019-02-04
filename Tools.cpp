/*
    Utility functions (e.g., for bit/byte manipulations) used in Y86 simulator.
    
    Author: Hunter Eller 
    version: 1/14/2019
*/
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstdint>
#include "Tools.h"

namespace Tools {
    
/*-----------------------------------------------------------------------------------------------
    getBits
	Extracts bits 'low' to 'high' (inclusive) from 'source' and returns the result as
	an 64-bit integer. 
	Example:
	
	getBits(12,15,0x0123456789abcdef);
	
	would return the value:
	
	0x00000000000000c;
	
	(Bits 12-15 of the 64-bit word, counting from the right correspond to hex digit 'c' in the
	source word. Note that any number of bits from 1 to 64 could be specified depending on the values
	of 'low' and 'high'.
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t getBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && (low <= high));
	source = source << (63 - high);
	return source >> (64 - (high - low + 1));
}
/*-----------------------------------------------------------------------------------------------
    setBits
	Sets (to 1) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t setBits(unsigned low, unsigned high, uint64_t source)
{
	assert(high < 64 && low <= high);
    uint64_t mask = ~0;
    mask = mask >> (63 - (high - low));
	return (mask << low | source);
}
/*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t clearBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && low <= high);
    uint64_t mask = ~0;
	
    mask = mask >> (63 - (high - low));
	mask = mask << low;
	return ~mask & source;
}

/*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source)
{
    assert(bitNum >= 0 && bitNum < 64 && (bitVal == 0 || bitVal == 1));
    uint64_t mask = 1;
    mask = mask << (bitNum);
	
    if (bitVal != 0)
	{
		return (mask | source);
    }
	else if (bitVal == 0)
	{
		clearBits(bitNum, bitNum, source);
	}
	return (~mask & source);
}

/*-----------------------------------------------------------------------------------------------
    getByteNumber
	Returns the specified byte number from the source word.
	
	Example:
	getByteNumber(3,0x0011223344556677);
	
	will return the single byte value:
	
	0x44
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint8_t getByteNumber(unsigned byteNum, uint64_t source)
{
    assert(byteNum < 8);
    uint64_t mask = 0xFF;
	mask = mask << (byteNum * 8);
	return source >> (byteNum * 8);
}
/*-----------------------------------------------------------------------------------------------
    putByteNumber
	Returns the source word after replacing the specified byte (byteNum) with a given 
	byte value (byteVal).
	
	Example:
	putByteNumber(3,0x00,0x0011223344556677);
	
	will return the value:
	
	0x0011223300556677
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint64_t putByteNumber(unsigned byteNum, uint8_t byteVal, uint64_t source)
{
    assert(byteNum < 8);
	uint64_t mask = 0xFF;
    mask = mask << (byteNum * 8);
	return ((source & ~mask) | ((uint64_t)byteVal << (byteNum * 8)));
}
/*-----------------------------------------------------------------------------------------------
    buildWord
	
	Returns a 64 bit word consisting of the 8 parameter bytes, where b0 is the least significant
	and b7 is the most significant byte.
------------------------------------------------------------------------------------------------*/
uint64_t buildWord(unsigned char b0, unsigned char b1,unsigned char b2, unsigned char b3,
                          unsigned char b4, unsigned char b5,unsigned char b6, unsigned char b7)
{
    uint64_t submit = 0;
    submit = putByteNumber(7, b7, submit);
    submit = putByteNumber(6, b6, submit);
    submit = putByteNumber(5, b5, submit);
    submit = putByteNumber(4, b4, submit);
    submit = putByteNumber(3, b3, submit);
    submit = putByteNumber(2, b2, submit);
    submit = putByteNumber(1, b1, submit);
	submit = putByteNumber(0, b0, submit);
		
	return submit;
}
/*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
bool isNegative(uint64_t source)
{
    source = source >> 63;
	return source;
}
/*-----------------------------------------------------------------------------------------------
    expandBits
	
	Reads the source and converts it to a character string consisting of 72 bytes--71 characters
	followed by a '\0' character (string terminator).
	Example usage: 
		char buf[72];
		expandBits(0xAABBCCDDEE001122UL,buf);

		Will cause the following string to be written to the buf[] array (not including quotes):
	
	"10101010 10111011 11001100 11011101 11101110 00000000 00010001 00100010"
	
	Note the space after every group of 8 digits except the last. The last byte of
	the string is the '\0' byte, that is not printable but used to indicate the end
	of a C string.
------------------------------------------------------------------------------------------------*/
void expandBits(uint64_t source, char *bits)
{
	assert(bits != NULL);
	int count = 0;
	
    for (int i = 71; i >= 0; i--)
	{
		if (i == 71)
		{
			bits[i] = '\0';
		}
		else if (i == 8 || i == 17 || i == 26 || i == 35 || i == 44 || i == 53 || i == 62)
		{
			bits[i] = ' ';
		}
		else if (source & ((uint64_t)1 << count))
		{
			bits[i] = '1';
			count ++;
		}
		else 
		{
			bits[i] = '0';
			count++;
		}
    }
}
/*-----------------------------------------------------------------------------------------------
    clearBuffer
	Treats pbuf as a pointer to an array of 'size' bytes and clears them all to zero.
------------------------------------------------------------------------------------------------*/
void clearBuffer(char * pbuf, int size)
{
	assert(size >= 0 && pbuf != NULL);
    for (int i = 0; i < size; i++) {
		pbuf[i] = 0;
    }
}

} // end namespace Y86
