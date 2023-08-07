#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
string Rcode = "1111";
int licznik = 0;

struct Point {
	int appeared = 0;
	int correct = 0;
};

Point numOfAppear(string code) {
	int appearedNum = 0;
	int correctdNum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (code[j] == Rcode[i])
				appearedNum++;
		}
		if (code[i] == Rcode[i])
			correctdNum++;
	}
	licznik++;
	if (licznik > 13)
		cout << "siema";
	Point result;
	result.appeared = appearedNum;
	result.correct = correctdNum;
	cout << code << " A" << appearedNum << " C" << correctdNum << endl;
	if (correctdNum == 4)
		cout << code << " kroki: " << licznik << endl << endl;
	if (licznik > 12)
		cout << "o cie chhuj";
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

void correctPlacement(string code0, Point result) {
	string code1;
	string code2;
	string code3;
	string code4;
	string code5;
	int app = result.correct;
	switch (app) {
	case 2:
		switch (numOfAppear(reversePair(code0, 0, 1)).correct) {
		case 0:
			numOfAppear(reversePair(code0, 2, 3));
			break;
		case 1:
			switch (numOfAppear(reversePair(code0, 1, 2)).correct) {
			case 0:
				numOfAppear(reversePair(code0, 0, 3));
				break;
			case 1:
				switch (numOfAppear(reversePair(code0, 0, 2)).correct) {
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
		switch (numOfAppear(code1).correct) {
		case 0:
			code1 = reversePair(code0, 2, 3);
			break;
		}
		switch (numOfAppear(reversePair(code1, 1, 2)).correct) {
		case 0:
			numOfAppear(reversePair(code1, 0, 3));
			break;
		case 1:
			switch (numOfAppear(reversePair(code1, 0, 2)).correct) {
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
		switch (numOfAppear(code1).correct) {
		case 0:
			code2 = rotateString(code1);
			switch (numOfAppear(rotateString(code2)).correct) {
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
			switch (numOfAppear(reversePair(code2, 0, 1)).correct) {
			case 0:
				numOfAppear(reversePair(code2, 2, 3));
				break;
			case 1:
				switch (numOfAppear(reversePair(code2, 1, 2)).correct) {
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
			switch (numOfAppear(reversePair(code1, 0, 2)).correct) {
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
	//cout << "zaczynam sprawdzenie z kode" << code << " A" << res.appeared << " C" << res.correct << endl;
	//Point res = numOfAppear(code);
	correctPlacement(code, res);
	return 0;
}


string findCompletion(string origin) {
	string completion = "1111";
	bool table[8]{ 1,1,1,1,1,1,1,1 };
	for (int i = 0; i < 4; i++) {
		int j = origin[i] - 48;
		table[j - 1] = 0;
	}

	int pos = 0;
	for (int i = 0; i < 9; i++) {
		if (table[i] == 1) {
			completion[pos] = i + 1 + 48;
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





	for (int i = 1; i < 800; i++) {
		for (int j = 0; j < 4; j++) {
			cout << result[i][j];
			Rcode[j] = result[i][j] + 48;
		}
		//Rcode = "4628";
		cout << endl;
		licznik = 0;
		findTripple();
	}


	//for (int i = 0; i < index; i++) {
	//	cout << numbers[i] << " ";
	//	Rcode = numbers[i];
	//	licznik = 0;
	//	findTripple();
	//}

	//Rcode = "2361";
	//licznik = 0;
	//findResult("1623");

	//for (int i = 0; i < 70; i++) {
	//	Rcode = Tab[i];
	//	licznik = 0;
	//	findTripple();
	//}

	return 0;
}