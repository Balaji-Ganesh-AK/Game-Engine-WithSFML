#include "stdafx.h"
#include "IString.h"
#include <cstddef>
#include <cstdlib>

int IString::length(const char* string)
{
	    int i = 0;
		if (string == nullptr)
			return 0;
		while (string[i] != NULL)
		{	
			i++;	
		}
		return i;
}




//char* MakeSentence(char** sentenceWord)
//{
//
//	//std::cout << *strings[2];
//	for (i = 0; sentenceWord[i] != nullptr; i++)
//	{
//		for (j = 0; sentenceWord[i][j] != '\0'; j++)
//		{
//			count++;
//			//sentence[count] = strings[i][j];
//		}
//		count++;
//		//sentence[count] = ' ';
//	}
//	char* sentence = (char*)malloc(count * sizeof(char*));
//
//	for (i = 0; sentenceWord[i] != nullptr; i++)
//	{
//
//		for (j = 0; sentenceWord[i][j] != NULL; j++)
//		{
//			numberOfWords++;
//			if (sentenceWord[i][j] == '\n')
//			{
//				sentenceWord[i][j] = ' ';
//
//			}
//			sentence[numberOfWords] = sentenceWord[i][j];
//
//
//		}
//		if (sentence[numberOfWords] != ' ')
//		{
//			numberOfWords++;
//			sentence[numberOfWords] = ' ';
//		}
//		else
//		{
//
//		}
//	}
//	sentence[numberOfWords] = '.';
//	sentence[numberOfWords + 1] = NULL;
//
//	return sentence;
//}