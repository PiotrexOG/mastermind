#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
using namespace std;
string Rcode = "1111";
int licznik = 0;

list<int> possibilities[8][4];

int resultHistory[14][6];


struct Point {
	int appeared = 0;
	int correctCol = 0;
	int correctPos = 0;
};

void masterLogic(string Code, int corPos, int round);
void justCallMe(int a, int row, int color);
Point numOfAppear(string code) {
	int appearedNum = 0;
	int correctPosdNum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (code[j] == Rcode[i])
				appearedNum++;
		}
		if (code[i] == Rcode[i])
			correctPosdNum++;
	}

	Point result;
	result.appeared = appearedNum;
	result.correctCol = appearedNum - correctPosdNum;
	result.correctPos = correctPosdNum;
	for (int i = 0; i < 4; i++) {
		resultHistory[licznik][i] = code[i] - 49;
	}
	resultHistory[licznik][4] = result.correctCol;
	resultHistory[licznik][5] = result.correctPos;
	cout << code << " A" << result.correctCol << " C" << correctPosdNum << endl;
	if (code == "1235" && result.correctPos == 4)
		cout << "halo";
	masterLogic(code, result.correctPos, licznik);
	licznik++;

	if (correctPosdNum == 4)
		cout << code << " kroki: " << licznik << endl << endl;
	//if (licznik > 12)
	//	cout << "o cie chhuj";
	return result;
}


string reversePair(string code, int first, int second) {
	char tmp = code[first];
	code[first] = code[second];
	code[second] = tmp;
	return code;
}

string rotateString(string code) {
	char tmp = code[3];
	code[3] = code[2];
	code[2] = code[1];
	code[1] = code[0];
	code[0] = tmp;
	return code;
}

void correctPosPlacement(string code0, Point result) {
	string code1;
	string code2;
	string code3;
	int app = result.correctPos;
	switch (app) {
	case 2:
		switch (numOfAppear(reversePair(code0, 0, 1)).correctPos) {
		case 0:
			numOfAppear(reversePair(code0, 2, 3));
			break;
		case 1:
			switch (numOfAppear(reversePair(code0, 1, 2)).correctPos) {
			case 0:
				numOfAppear(reversePair(code0, 0, 3));
				break;
			case 1:
				switch (numOfAppear(reversePair(code0, 0, 2)).correctPos) {
				case 0:
					numOfAppear(reversePair(code0, 1, 3));
					break;
				case 4:
					return;
				}
				break;
			case 4:
				return;
			}
			break;
		case 4:
			return;
		}
		break;

	case 1:
		code1 = reversePair(code0, 0, 1);
		switch (numOfAppear(code1).correctPos) {
		case 0:
			code1 = reversePair(code0, 2, 3);
			break;
		}
		switch (numOfAppear(reversePair(code1, 1, 2)).correctPos) {
		case 0:
			numOfAppear(reversePair(code1, 0, 3));
			break;
		case 1:
			switch (numOfAppear(reversePair(code1, 0, 2)).correctPos) {
			case 0:
				numOfAppear(reversePair(code1, 1, 3));
				break;
			case 4:
				return;
			}
			break;
		case 4:
			return;
		}
		break;

	case 0:
		code1 = rotateString(code0);
		switch (numOfAppear(code1).correctPos) {
		case 0:
			code2 = rotateString(code1);
			switch (numOfAppear(rotateString(code2)).correctPos) {
			case 0:
				code3 = rotateString(code2);
				numOfAppear(code3);
				break;
			case 4:
				return;
			}
			break;
		case 1:
			code2 = rotateString(code1); // code2 has 2 right
			switch (numOfAppear(reversePair(code2, 0, 1)).correctPos) {
			case 0:
				numOfAppear(reversePair(code2, 2, 3));
				break;
			case 1:
				switch (numOfAppear(reversePair(code2, 1, 2)).correctPos) {
				case 0:
					numOfAppear(reversePair(code2, 0, 3));
					break;
				case 4:
					return;
				}
				break;
			case 4:
				return;
			}
			break;
		case 2:
			switch (numOfAppear(reversePair(code1, 0, 2)).correctPos) {
			case 0:
				numOfAppear(reversePair(code1, 1, 3));
				break;
			case 4:
				return;
			}
			break;
		case 4:
			return;
		}
		break;

	case 4:
		return;
	}


}

int findResult(string code, Point res) {
	//cout << "zaczynam sprawdzenie z kode" << code << " A" << res.appeared << " C" << res.correctPos << endl;
	//Point res = numOfAppear(code);
	correctPosPlacement(code, res);
	return 0;
}


string findCompletion(string origin) {
	string completion = "1111";
	bool table[8]{ 1,1,1,1,1,1,1,1 };
	for (int i = 0; i < 4; i++) {
		int j = origin[i] - 49;
		table[j] = 0;
	}

	int pos = 0;
	for (int i = 0; i < 9; i++) {
		if (table[i] == 1) {
			completion[pos] = i + 49;
			pos++;
		}
	}

	return completion;
}

void findQuadra(string code) {
	int accurate;
	Point res;
	string completion = findCompletion(code);
	string tmp = code;
	int help = 0;
	for (int j = 0; j < 4; j++) {
		char pierwsze = tmp[j];
		tmp[j] = completion[help];
		res = numOfAppear(tmp);
		accurate = res.appeared;
		if (accurate == 4) {
			findResult(tmp, res);
			//printResult(tmp);
			return;
		}
		else if (accurate == 3) {
			char drugie = tmp[j];
			help++;
			tmp[j] = completion[help];
			res = numOfAppear(tmp);
			accurate = res.appeared;
			if (accurate == 4) {
				//printResult(tmp);
				findResult(tmp, res);
				return;
			}
			else if (accurate == 3) {
				help++;
				tmp[j] = completion[help];
				res = numOfAppear(tmp);
				accurate = res.appeared;
				if (accurate == 4) {
					//printResult(tmp);
					findResult(tmp, res);
					return;
				}
				else if (accurate == 3) {
					help++;
					tmp[j] = completion[help];
					res = numOfAppear(tmp); //dodatkowo
					findResult(tmp, res);
					return;
				}
			}
			else if (accurate == 2) {
				tmp[j] = pierwsze;
				j++;
				for (; j < 4; j++) {
					char pi = tmp[j];
					tmp[j] = drugie;
					if (j == 3) {
						res = numOfAppear(tmp); //dodatkowo
						findResult(tmp, res);
						return;
					}
					res = numOfAppear(tmp);
					accurate = res.appeared;
					if (accurate == 4) {
						//printResult(tmp);
						findResult(tmp, res);
						return;
					}
					tmp[j] = pi;
				}
			}
		}
		else if (accurate == 2) {
			tmp[j] = code[j];
			help++;
			if (j == 2) {
				tmp[j + 1] = completion[help];
				res = numOfAppear(tmp); //dodatkowo
				findResult(tmp, res);
				return;
			}
		}
	}
}

void findTripple() {
	const int numOfSeq = 5;
	string table[numOfSeq] = { "1234", "1256", "1278", "1357", "2368" };
	Point res;
	for (int i = 0; i < numOfSeq; i++) {
		res = numOfAppear(table[i]);
		int accurate = res.appeared;
		string tmp = table[i];
		if (accurate == 0 || accurate == 1) {
			tmp = findCompletion(tmp);
		}
		if (accurate == 0) {
			res = numOfAppear(tmp);
			accurate = res.appeared;
		}
		if (accurate == 4) {
			//printResult(tmp);
			findResult(tmp, res);
			return;
		}
		else if (accurate == 1 || accurate == 3) {
			findQuadra(tmp);
			return;
		}
	}
	cout << "halo" << endl;
}

void showlist(list<int> g)
{
	list<int>::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
}




void updateList(int color, int row, int value) {
		if (value == -1) {

			justCallMe(color, row, color);

			possibilities[color][row].clear();
			possibilities[color][row].push_back(value);


		}
		else if (value == 100) {


			for (int a = 0; a < 8; a++) {

				if (color != a) {

					justCallMe(a, row, color);

					possibilities[a][row].clear();
					possibilities[a][row].push_back(-1);
				}
			}
			for (int a = 0; a < 4; a++) {

				if (row != a) {

					justCallMe(a, row, color);

					possibilities[color][a].clear();
					possibilities[color][a].push_back(-1);
				}
			}


			possibilities[color][row].clear();
			possibilities[color][row].push_back(value);
		}
		else {
			possibilities[color][row].push_back(value);
		}

}


void masterLogic(string code, int corPos, int round) {

	int value = 0;
	if (corPos == 0) {
		value = -1;
	}
	else if(corPos == 4) {
		value = 100;
	}
	else {
		value = round;
	}
	for (int i = 0; i < 4; i++) {
		int color = code[i] - 49;
		updateList(color, i, value);
	}
}

void justCallMe(int a, int row, int color) {
	list<int>::iterator it;
	for (it = possibilities[a][row].begin(); it != possibilities[a][row].end(); ++it) {
		int round = *it;
		int quantity = resultHistory[round][5];
		int counter = 0;
		int tab[4][2];
		for (int i = 0; i < 4; i++) {

			int colorHistory = resultHistory[round][i];

			if (colorHistory != color) {
				if (!possibilities[colorHistory][i].empty()) {
					if (possibilities[colorHistory][i].back() != -1 && possibilities[colorHistory][i].back() != 100) {
						tab[counter][0] = colorHistory;
						tab[counter][1] = i;
						counter++;
					}
				}
			}
		}

		if (counter == quantity) {
			for (int j = 0; j < quantity; j++) {
				updateList(tab[j][0], tab[j][1], 100);
			}
		}

	}
}

void generateNumbers(int n, int len, vector<int>& curr, vector<vector<int>>& result) {
	if (n == len) {
		result.push_back(curr);
		return;
	}

	for (int i = 1; i <= 8; i++) {
		bool found = false;
		for (int j = 0; j < n; j++) {
			if (curr[j] == i) {
				found = true;
				break;
			}
		}
		if (!found) {
			curr[n] = i;
			generateNumbers(n + 1, len, curr, result);
		}
	}
}

int main()
{
	vector<int> curr(4);
	vector<vector<int>> result;
	generateNumbers(0, 4, curr, result);
	string Tab[70] = { "1234", "1235", "1236", "1237", "1238", "1245", "1246", "1247", "1248", "1256", "1257", "1258", "1267", "1268", "1278", "1345", "1346", "1347", "1348",
					"1356", "1357", "1358", "1367", "1368", "1378", "1456", "1457", "1458", "1467", "1468", "1478", "1567", "1568", "1578", "1678", "2345", "2346", "2347", "2348", "2356", "2357",
				"2358", "2367", "2368", "2378", "2456", "2457", "2458", "2467", "2468", "2478", "2567", "2568", "2578", "2678", "3456", "3457", "3458", "3467", "3468", "3478", "3567", "3568", "3578", "3678", "4567", "4568", "4578", "4678", "5678" };



	//for (int i = 0; i < 800; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		cout << result[i][j];
	//		Rcode[j] = result[i][j] + 48;
	//	}
	//	cout << endl;
	//	licznik = 0;

		Rcode = "1253";

		for (int l = 0; l < 14; l++) {
			for (int j = 0; j < 6; j++) {
				resultHistory[l][j] = 0;
			}
		}

		for (int l = 0; l < 8; l++) {
			for (int j = 0; j < 4; j++) {
				possibilities[l][j].clear();
			}
		}

		findTripple();

		for (int l = 0; l < 14; l++) {
			if (l < 10)
				cout << "0";
			cout << l << " ";
			for (int j = 0; j < 6; j++) {
				cout << resultHistory[l][j] << ' ';
			}
			cout << endl;
		}
	//}

	return 0;
}