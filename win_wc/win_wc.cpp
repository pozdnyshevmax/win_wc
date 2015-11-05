// win_wc.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;

typedef long long count_wc;

count_wc totalL = 0, totalC = 0, totalW = 0;

void report(char *file, count_wc lines, count_wc words, count_wc chars) { // format output
	cout << lines << "	" << words << "	" << chars << "	" << file << endl;
}

void counter(char *file) {

	int countL = 1, countW = 0;

	ifstream ifs(file, std::ifstream::binary); //open file

	if (!ifs.is_open()) {
		cout << "ERROR: can't open file " << file << endl;
		return;
	}

	filebuf* pbuf = ifs.rdbuf(); //read file
	count_wc  countC = pbuf->pubseekoff(0, ifs.end, ifs.in); //get char count
	pbuf->pubseekpos(0, ifs.in);

	char* buffer = new char[countC + 1];//prepere buffer
	buffer[countC] = EOF;
	pbuf->sgetn(buffer, countC + 1);
	bool prevC = false; // previous char isalpha
	for (count_wc i = 0; i < countC + 1; i += 1) {
		if (buffer[i] == '\n') countL++;
		if (!isalpha(buffer[i]) && prevC == true) countW++; // detect end of words
		prevC = isalpha(buffer[i]);
	}
	if (!countC) countL = 0; // if file empty
	ifs.close();
	delete[] buffer;
	report(file,countL,countW,countC);
	totalL += countL;
	totalW += countW;
	totalC += countC;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		cout << "ERROR: no file name" << endl;
	cout << "lines	words	chars	filename" << endl;
	for (int i = 1; i < argc; i++) // for all input files
		counter(argv[i]);
	if (argc > 2) //if count of files > 1
		report("total",totalL,totalW,totalC); // report total statistic
	system("pause");
	return 0;
}

