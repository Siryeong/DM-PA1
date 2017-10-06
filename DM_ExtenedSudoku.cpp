
/**
Date: 2017/09/20
Discription: This is extened sudoku SAT solver Program
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

#define P(i,j,k) (81*(i-1) + 9*(j-1) + k)
#define NUMOFSTAR 4

using namespace std;

void interpretSATsolver() {
	ifstream inf;
	ofstream ouf;
	system(".\\z3-4.3.2-x64-win\\bin\\z3 -dimacs formula.txt >> formula_result.txt");
	inf.open("formula_result.txt");
	ouf.open("output.txt");

	string s;
	inf >> s; // sat 소모

	int a;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int k = 1; k <= 9; k++) {
				inf >> a;
				if (a > 0)
					ouf << k << " ";
			}
		}
		ouf << endl;
	}
	inf.close();
	ouf.close();

	system("pause");
}

int main(void)
{
	// 스도쿠 퍼즐 불러오기
	int starNum = 0;
	int star[NUMOFSTAR];

	ifstream inf;
	ofstream ouf;
	inf.open("input.txt");
	ouf.open("formula.txt");

	// formula.txt 만들기
	// hint number
	int n = 0;
	char in;
	ouf << "p cnf 729 " << endl;
	int co = 1;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			inf.get(in);
			if (in == 32 || in == '\n') {// except space and enter
				inf.get(in);
			}

			if (in >= 48 && in <= 57) {// hint number: 48 and 57 are ASKII code of 0 and 9 
				n = atoi(&in);
				if (n != 0) {
					ouf << P(i, j, n) << " 0" << endl;
				}
			}
			else if (in == 42) {//star number: 42 is ASKI code of *
				star[starNum] = P(i, j, 0);
				starNum++;
			}
		}
	}

	//every star number should same 
	if (starNum != 1) {
		for (int t = 1; t < starNum; t++) {
			for (int n = 1; n <= 9; n++) {
				ouf << (star[t - 1] + n) * -1 << " ";
				ouf << (star[t] + n) << " ";
				ouf << 0 << endl;
				ouf << (star[t - 1] + n) << " ";
				ouf << (star[t] + n) * -1 << " ";
				ouf << 0 << endl;
			}
		}
	}

	inf.close();

	//row every num
	for (int i = 1; i <= 9; i++) {
		for (int n = 1; n <= 9; n++) {
			for (int j = 1; j <= 9; j++) {
					ouf << P(i, j, n) << " ";
			}
			ouf << 0 << endl;
		}
	}

	//col every num
	for (int j = 1; j <= 9; j++) {
		for (int n = 1; n <= 9; n++) {
			for (int i = 1; i <= 9; i++) {
				ouf << P(i, j, n) << " ";
			}
			ouf << 0 << endl;
		}
	}

	// 3x3block every num
	for (int r = 0; r <= 2; r++) {
		for (int s = 0; s <= 2; s++) {
			for (int n = 1; n <= 9; n++) {
				for (int i = 1; i <= 3; i++) {
					for (int j = 1; j <= 3; j++) {
						ouf << P(3 * r + i, 3 * s + j, n) << " ";
					}
				}
				ouf << 0 << endl;
			}
		}
	}

	// cell unique
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			for (int n = 1; n <= 8; n++) {
				for (int m = n + 1; m <= 9; m++) {
					ouf << P(i, j, n) * -1 << " ";
					ouf << P(i, j, m) * -1 << " ";
					ouf << 0 << endl;
				}
			}
		}
	}

	ouf.close();

	interpretSATsolver();
	return 0;
}