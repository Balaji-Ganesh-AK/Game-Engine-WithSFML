#pragma once
#include <cassert>
#include <cstdint>


class IBitArray
{

public:
		IBitArray(int i_numBits);
		size_t find_first_set_bit() const;
		size_t find_first_clear_bit() const;

		void set_bit(size_t i_index) const;
		void clear_bit(size_t i_index) const;

		bool is_bit_set(size_t i_index) const;
		bool is_bit_clear(size_t i_index) const;

		bool is_all_bit_set() const;
		bool is_all_bit_clear() const;
	
		void set_all(void) const;
		void clear_all(void) const;
	
	
	private:
		uint64_t* m_pBits;
		size_t bitsPerItem = 32;
		size_t NumOfBlocks;
};



