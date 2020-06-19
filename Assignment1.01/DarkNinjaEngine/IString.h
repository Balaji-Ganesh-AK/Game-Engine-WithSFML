#pragma once
class IString
{
private:
	 int length(const char * string);
	 char* _string(const char *string);
	
};

// Assignment 1.04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#include "pch.h"
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#else
//#include <stdlib.h>
//#endif // _DEBUG
//
//#define MAX_LEN 100
//#include <iostream>
//#pragma warning(disable : 4996)
//int i, j, numberOfWords = -1, count = 0;
//int customStrLength(const char* length)
//{
//	i = 0;
//	if (length == nullptr)
//		return 0;
//	while (length[i] != NULL)
//	{
//
//		i++;
//
//	}
//	return i;
//}
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
//
//int main()
//{
//
//	const char* strings[] = {
//			"This",
//			"is",
//			"a",
//			"test",
//			nullptr
//	};
//	int wordCount = 0;
//	char** word = (char**)malloc(sizeof(char*));
//	char tempWord[MAX_LEN];
//
//	std::cout << "Enter the words one by one (Enter two times to end)" << std::endl;
//	fgets(tempWord, MAX_LEN, stdin);
//
//
//	tempWord[customStrLength(tempWord) - 1] = '\0';
//
//	while ((customStrLength(tempWord) - 1) != 0)
//	{
//		//increase the size of the array by
//
//		char** temp = (char**)realloc(word, (wordCount + 1) * sizeof(char*));
//
//		if (word == nullptr)
//		{
//			std::cout << "error";
//
//		}
//		else
//			word = temp;
//
//		word[wordCount] = (char*)malloc((customStrLength(tempWord)) * sizeof(char));
//		word[wordCount] = strdup(tempWord);
//		fgets(tempWord, MAX_LEN, stdin);
//		wordCount++;
//
//	}
//	word = (char**)realloc(word, (wordCount + 1) * sizeof(char*));
//	word[wordCount] = nullptr;
//	//std::cout << word[0];
//	char* pSentence = MakeSentence(word);
//	std::cout << pSentence;
//
//	free(word);
//	free(word[wordCount]);
//	free(pSentence);
//
//#if defined(_DEBUG)
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
