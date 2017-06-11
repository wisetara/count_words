// This is the Project 6 - Term Frequency (a06.cpp)
// Written by: Tara Scherner de la Fuente
// Date: 5 June 2017
// Sources: http://www.cplusplus.com/reference/string/string/begin/,
//			http://www.cplusplus.com/reference/cctype/ispunct/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

const int ARRAY_SIZE = 4999;
const int NOT_FOUND = -1;

struct wordInfo
{
 	string word;
	int count;
};

void processWords(ifstream& inFile, wordInfo list[], int& totalWords);
void countWords(wordInfo list[], int totalWords);
bool search (string words[], string searchWord);
bool searchStruct(wordInfo list[], string searchWord, int count);
int findIndexOfMost (wordInfo list[], int totalWords);
int findIndexOfLeast (wordInfo list[], int totalWords);

int main ()
{
	ifstream inFile;
	string inputTextFile;
	string word;
	int totalWords = 0;
	char reply = 'Y';
	char quitResponse;

	cout << endl << "Let's Come To--er--Count Terms!" << endl << endl;

	while (reply != 'N') {
		cout << "What is your input text file name?" << endl;
		cin >> inputTextFile;
		inFile.open(inputTextFile);
		wordInfo words[ARRAY_SIZE];

		if (inFile.is_open())
		{
			while(!inFile.eof())
			{
				int index;

				processWords(inFile, words, totalWords);
				countWords(words, totalWords);
				// for(int index = 0; index < totalWords; index++)
				// {
				// 	string searchWord = words[index].word;
				// 	int count;
				// 	bool repeat = searchStruct(words, searchWord, count);
				// 	if(!repeat)
				// 	{
				// 		words[index].word = searchWord;
				// 		words[index].count = 1;
				// 		cout << "WORD if: " << searchWord << " COUNT: " << words[index].count << endl;
				// 	}
				// 	else
				// 	{
				// 		int newWordIndex = searchStruct(words, searchWord, count);
				// 		searchWord = words[newWordIndex].word;
				// 		words[newWordIndex].count = words[newWordIndex].count + 1;
				// 		cout << "WORD else: " << searchWord << " COUNT: " << words[newWordIndex].count << endl;
				// 	}
				// 	index++;
				// }


				// countWords(inFile, words, totalWords);

				cout << "Total Words: " << totalWords << endl;
  			}
  			inFile.close();
  			cout << words[50].word << endl;
  			cout << "Press q (or any other key) followed by 'Enter' to quit: ";
  			cin >> quitResponse;
			return 0;
		}
		else
		{
			cout << "It doesn't look like the file opened. :-(" << endl << endl;
			cout << endl << "Would you like to try loading a file again? (Y or N):" << endl;
			cin >> reply;
			reply = static_cast<char>(toupper(reply));
			if (reply == 'N')
			{
				return 0;
			}
		}
	}
}

void processWords(ifstream& inFile, wordInfo list[], int& totalWords)
{
	int index;
	bool duplicate = false;

	for (index = 0; index < ARRAY_SIZE; index++)
	{
		inFile >> list[index].word;

		for (string::iterator i = (list[index].word).begin(); i != (list[index].word).end(); ++i)
			*i = static_cast<char>(tolower(*i));

			for (int i = 0, length = list[index].word.size(); i < length; i++)
			{
				if (ispunct(list[index].word[i]))
				{
					list[index].word.erase(i--, 1);
					length = list[index].word.size();
				}
			}

		for (totalWords = 0; totalWords <= ARRAY_SIZE; totalWords++)
			list[index].count = 0;
	}
}

int search(wordInfo list[], string searchWord)
{
    int index = 0;
    while (index <= ARRAY_SIZE && list[index].word != searchWord)
        index++;
    if (index == ARRAY_SIZE)
        index = NOT_FOUND;
    return index;
}

bool searchStruct(wordInfo list[], string searchWord, int count)
{
	bool found = false;
	int index = NOT_FOUND;

	while(!found && index < count)
	{
		if(list[index].word == searchWord)
			found = true;
		else
			index++;
	}
	return found;
}

void countWords(wordInfo list[], int totalWords)
{
	for(int index = 0; index < totalWords; index++)
	{
		string searchWord = list[index].word;
		int count;
		bool repeat = searchStruct(list, searchWord, count);
		if(!repeat)
		{
			list[index].word = searchWord;
			list[index].count = 1;
			cout << "WORD if: " << searchWord << " COUNT: " << list[index].count << " INDEX: " << index << endl;
		}
		else
		{
			if(repeat)
			{
			int newWordIndex = search(list, searchWord);
				searchWord = list[newWordIndex].word;
				list[newWordIndex].count = list[newWordIndex].count + 1;
				cout << "WORD else: " << searchWord << " COUNT: " << list[newWordIndex].count << " INDEX: " << newWordIndex << endl;
			}
			int newWordIndex = search(list, searchWord);
			if((list[newWordIndex].word).empty())
			{
				list[newWordIndex].count = 0;
				cout << "NOPE: " << searchWord << " COUNT: " << list[newWordIndex].count << " INDEX: " << newWordIndex << endl;
			}
		}
		index++;
	}
}
// int findIndexOfMost(wordInfo list[], int totalWords) {
//     int most;
//     int index;

//     most = list[0].count;
//     for (index = 0; index <= totalWords; index++)
// 	    if (list[index].count > most)
// 	    	most = list[index].count;
//     return index;
// }



// void sort_words()
// {
// 	// Sort the listOfWords by frequency, using alpha order to break ties of frequency
// }

// Main function stores a listOfWords variable tp store the word/frequency info.
// Then call the functions to do the above.

// wordInfo counts[ARRAY_SIZE];
// wordInfo words[ARRAY_SIZE];

// Both of these functions are for use with parallel arrays. If you choose to use an
// array of structs, the headers would be:
// int findIndexOfMost (wordInfo words[], int totalWords);
// int findIndexOfLeast (wordInfo words[], int totalWords);
