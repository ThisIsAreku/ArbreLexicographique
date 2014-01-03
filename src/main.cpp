/*
* main.cpp
*
* Copyright 2013 Alexandre Boucey <alexandre.boucey@alumni.univ-avignon.fr>
*
* This file is part of APC.
*
* APC is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* APC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with APC.  If not, see <http://www.gnu.org/licenses/>.
*
*
*/

#include <iostream>
#include <fstream>
#include <ctime>

#include "apc.h"

#define DEBUG true

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;

int main(int argc, char** argv){
	string source_dict, seek_dict;
	if(argc < 2)
	{
		source_dict = "Gros.txt";
		seek_dict = "Petit.txt";
	}
	else if(argc < 3)
	{
		source_dict = argv[1];
		seek_dict = "Petit.txt";
	}else{
		source_dict = argv[1];
		seek_dict = argv[2];
	}
	APC apc;
	long totalWords = 0, totalInsertedWords = 0, foundWords = 0, seekWords = 0;
	double doublePercent, foundPercent, seekPercent;
	clock_t tStart;


	cout << "Source is : " << source_dict << ", test is : " << seek_dict << endl;

	cout << "LOADING WORDS FROM " << source_dict << endl;
	ifstream source(source_dict);
	string word;
	tStart = clock();
	while(!source.eof()){
		source >> word;
		if(apc.insertWord(word))
			totalInsertedWords++;
		totalWords++;
	}
	cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" << endl;
	doublePercent = (totalInsertedWords * 100) / (double)totalWords;


	cout << "TESTING WORDS FROM " << seek_dict << endl;;
	ifstream seek(seek_dict);
	tStart = clock();
	while(!seek.eof()){
		seek >> word;
		if(apc.contains(word))
			foundWords++;
		seekWords++;
	}
	cout << "Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s" << endl;
	foundPercent = (foundWords * 100) / (double)totalWords;
	seekPercent = (foundWords * 100) / (double)seekWords;

	cout << "Total: " << totalWords << " words, " << totalWords - totalInsertedWords << " doubles (" << doublePercent << "% of unique words)" << endl;
	cout << "Found: " << foundWords << " (" << foundPercent << "% of source dict), in " << seekWords << " words (" << seekPercent << "% of seek dict)" << endl;
	cout << "Source is : " << source_dict << ", test is : " << seek_dict << endl;

}