// Test Cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
unsigned long int members[] = {
	0x053960b6,
	0xe53f68b6,
	0xd50d59d6,
	0x43c5D98b,
	0xa3f4cd8b,
	0x030fb68b,
	0xc5f061b6,
	0xb3a7bd8b,
	0xf5ce65b6,
	0xa59a66b6,
	0xa344cb8b,
	0x556863b6,
	0x54754430,
	0x63a5eb8b,
	0xd390c78b,
	0xe5e75eb6,
	0x8388c18b,
	0x7e389385 };

long unsigned int temp;
int xyz[4];

int main()
{
	cout << "Enter a byte of Hex at a time..." << endl;
	for (int i = 3; i >=0; i--) {
		cin >> hex >> xyz[i];
		cout << xyz[i] << endl;
	}
	system("pause");
	for (int i = 0; i <= sizeof(xyz)/sizeof(xyz[1]); i++) {
		temp += xyz[i]*pow(256, i);
		cout << xyz[i] << endl;
	}
	cout << "Looking for " << temp << '\n';
	for (int i = 0; i <= (sizeof(members) / sizeof(members[1]))-1; i++) {
		if (temp == members[i]) {
			cout << "Success" << '\n';
			cout << "Found " << members[i] << " at index " << i << " of the array" << '\n';
			system("pause");
			return 0;
		}
		
	}
	cout << "No match Found" << '\n';
	system("pause");
    return 0;
}