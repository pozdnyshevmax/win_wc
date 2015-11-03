// CRC_calc.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "ERROR: need filename or mask";
	}
	
	system("pause");
    return 0;
}

