//#include "stdafx.h"

#include <iostream>
#include <intrin.h>
#include "../../../HeaderFiles/Engine/Utility/IBitArray.h"
#pragma intrinsic(_BitScanForward)
IBitArray::IBitArray(int i_numBits):NumOfBlocks(i_numBits)
{
	m_pBits = new uint64_t(i_numBits/ bitsPerItem);

	assert(m_pBits);
	
}

size_t IBitArray::find_first_set_bit() const
{
	size_t n = 0;
	while((m_pBits[n]==0xff)&&(n < NumOfBlocks))
	{
		n++;
	}
	
	uint64_t byte = m_pBits[n];
	
	
	unsigned long mask = byte;
	unsigned long index;
		const unsigned char isNonzero = _BitScanForward(&index, mask);
		if (isNonzero)
		{
			//std::cout << " Index: " << index << std::endl;
			return index;
		}
		else
		{
			//std::cout << " no: " << index << std::endl;
			return NULL;
		}

}

size_t IBitArray::find_first_clear_bit() const
{
	size_t n = 0;
	while ((m_pBits[n] == 0xff) && (n < NumOfBlocks))
	{
		n++;
	}

	uint64_t byte = m_pBits[n];


	unsigned long index;
	int byteInverse = log2(byte) + 1;
	for(int i=0;i<byteInverse;i++)
	{
		byte = (byte ^ (1 << i));
	}
	unsigned long mask = byte;

	const unsigned char isNonzero = _BitScanForward(&index, mask);
	if (isNonzero)
	{
		//std::cout << " Index: " << index << std::endl;
		return index;
	}
	else
	{
		//std::cout << " no: " << index << std::endl;
		return NULL;
	}

}

void IBitArray::set_bit(size_t i_index) const
{
	size_t j = i_index / bitsPerItem;
	const size_t pos = i_index % bitsPerItem;
	size_t flag = 1;
	flag = flag << pos;

	m_pBits[j] = m_pBits[j] | flag;
}

void IBitArray::clear_bit(size_t i_index) const
{
	size_t i = i_index / bitsPerItem;
	size_t pos = i_index % bitsPerItem;
	size_t flag = 1;
	flag = flag << pos;
	flag = ~flag;
	m_pBits[i] = m_pBits[i] & flag;
}

bool IBitArray::is_bit_set(size_t i_index) const
{
	if (m_pBits[i_index / bitsPerItem] & (1 << (i_index % bitsPerItem)))
		return true;
	else
		return false;
}

bool IBitArray::is_bit_clear(size_t i_index) const
{
	if ((m_pBits[i_index / bitsPerItem] & (1 << (i_index % bitsPerItem))) == 0)
		return true;
	else
		return false;
}

bool IBitArray::is_all_bit_set() const
{
	size_t count=0;
	for (size_t i = 0; i < NumOfBlocks; i++)
	{
		if ((m_pBits[i / bitsPerItem] & (1 << (i % bitsPerItem)) )!= 0)
			count++;
	}
	if (count == NumOfBlocks)
		return true;
	return false;
}

bool IBitArray::is_all_bit_clear() const
{
	size_t count = 0;
	for (size_t i = 0; i < NumOfBlocks; i++)
	{
		if ((m_pBits[i / bitsPerItem] & (1 << (i % bitsPerItem)))==0)
			count++;

	}

	if (count == NumOfBlocks)
		return true;
	return false;
	
}

void IBitArray::set_all() const
{
	for (size_t i = 0; i < NumOfBlocks; i++)
	{
		size_t j = i / bitsPerItem;
		const size_t pos = i % bitsPerItem;
		size_t flag = 1;
		flag = flag << pos;

		m_pBits[j] = m_pBits[j] | flag;

	}
}

void IBitArray::clear_all() const
{
	for (size_t i = 0; i < NumOfBlocks; i++)
	{
		size_t j = i / bitsPerItem;
		const size_t pos = i % bitsPerItem;
		unsigned int flag = 1;
		flag = flag << pos;
		flag = ~flag;
		m_pBits[j] = m_pBits[j] & flag;


	}
}
