// This is the Project 6 - Term Frequency (a06.cpp)
// Written by: Tara Scherner de la Fuente
// Date: 5 June 2017
// Sources: http://www.cplusplus.com/reference/string/string/begin/,
//			http://www.cplusplus.com/reference/cctype/ispunct/, <-- I guess this was extra credit!

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
  			}
  			inFile.close();
  			cout << "Uses Index to Find Most Frequent: " << findIndexOfMost(words, totalWords) << endl;
  			cout << "Uses Index to Find (one of the) Least Frequent: " << findIndexOfLeast(words, totalWords) << endl;
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
		}
		else
		{
			if(repeat)
			{
			int newWordIndex = search(list, searchWord);
				searchWord = list[newWordIndex].word;
				list[newWordIndex].count = list[newWordIndex].count + 1;
			}
			int newWordIndex = search(list, searchWord);
			if((list[newWordIndex].word).empty())
			{
				list[newWordIndex].count = 0;
			}
		}
		index++;
	}
}

int findIndexOfMost(wordInfo list[], int totalWords)
{
    int most = 0;
	for(int i = 0; i < totalWords - 2; ++i)
	{
		if(list[most].count < list[i].count)
			most = i;
	}
	return cout << "WORD: " << list[most].word << " COUNT: " << list[most].count << endl;
}

int findIndexOfLeast(wordInfo list[], int totalWords)
{
    int least = 0;
	for(int i = 0; i < totalWords - 2; ++i)
	{
		if(list[i].count > 0 && list[least].count > list[i].count)
			least = i;
	}
	return cout << "WORD: " << list[least].word << " COUNT: " << list[least].count << endl;
}
