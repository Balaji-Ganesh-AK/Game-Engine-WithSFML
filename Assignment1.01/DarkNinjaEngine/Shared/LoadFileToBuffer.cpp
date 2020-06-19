//#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <cassert>

namespace Engine
{
	std::vector<uint8_t> LoadFileToBuffer(const char* i_pFilename)
	{
		assert(i_pFilename != nullptr);

		std::vector<uint8_t> Buffer;

		FILE* pFile = nullptr;

		if (fopen_s(&pFile, i_pFilename, "rb") == 0)
		{
			assert(pFile != nullptr);

			int FileIOError = fseek(pFile, 0, SEEK_END);
			assert(FileIOError == 0);

			long FileSize = ftell(pFile);
			assert(FileSize >= 0);

			FileIOError = fseek(pFile, 0, SEEK_SET);
			assert(FileIOError == 0);

			Buffer.reserve(FileSize);
			Buffer.resize(FileSize);

			size_t FileRead = fread(&Buffer[0], 1, FileSize, pFile);
			assert(FileRead == FileSize);

			fclose(pFile);
		}

		return Buffer;
	}
}
