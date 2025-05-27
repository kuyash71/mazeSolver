/*____________________________________________\
|                                             |
|		MAZE SOLVER MICROMOUSE SIMULATION     |
|				USING 19x19 MAZE              |
|		  A*(A-Star) AND DFS ALGORITHMS       |
|			       BY KUYASH                  |
|			   İSMAİL FATİH ÇOLAK             |
|			        14.10.24                  |
\____________________________________________*/

#include <iostream>
#include <windows.h>
#include<cmath>

using namespace std;

int finaleROW = 1, finaleCOL = 17, roadNUM = 1;

int find_smallest(int x, int y, int z, int t) {
	if (x < y && x < z && x < t) {
		return x;
	}
	else if (y < x && y < t && y < z) {
		return y;
	}
	else if (z < x && z < y && z < t) {
		return z;
	}
	else if (t < x && t < y && t < z) {
		return t;
	}
}
void printMAP(int map[19][19]) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (map[i][j] == 99) {
				cout << "\xE2\xAC\x9B" << " ";
			}
			else if (map[i][j] == 98) {
				cout << "\xE2\x97\xBE" << " ";
			}
			else if (map[i][j] == 00) {
				cout << "   ";
			}
			else if (map[i][j] < 10) {
				cout << "0" << map[i][j] << " ";
			}
			else {
				cout << map[i][j] << " ";
			}
		}
		cout << endl;
	}
}
void clear() {system("cls");}
int cost(int x, int y) {
	double sezgisel_uzaklık;
	int uzaklık_row, uzaklık_col;
	uzaklık_row = x - finaleROW;
	uzaklık_col = finaleCOL - y;
	sezgisel_uzaklık = sqrt(uzaklık_row * uzaklık_row + uzaklık_col * uzaklık_col);
	return roadNUM + 1 + sezgisel_uzaklık;
}

int main() {
	SetConsoleOutputCP(CP_UTF8);

	char finish;
	int sim_speed = 0, failed_steps = 0, algorithm = 0;
	int curROW = 2, curCOL = 1, up = 0, down = 0, left = 0, right = 0; // AV MEANS AVAILABLE
	int cost_up, cost_down, cost_left, cost_right, goalROW, goalCOL;
	bool dfs_search = false, astar_search = false, solving = false, right_av, left_av, down_av, up_av;

	int arr[19][19]{
	{ 99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99 },
	{ 99,00,00,00,99,00,00,00,00,00,00,00,99,00,00,00,99,00,99 },
	{ 99,01,99,00,99,00,99,00,99,00,00,99,99,00,99,99,99,00,99 },
	{ 99,99,99,00,99,00,99,99,99,99,00,00,00,00,00,00,99,00,99 },
	{ 99,00,00,00,99,00,99,00,00,00,00,99,00,99,99,00,00,00,99 },
	{ 99,99,00,99,99,00,00,00,00,99,00,99,00,99,99,00,99,00,99 },
	{ 99,99,00,99,00,00,99,99,99,99,00,99,00,00,00,00,99,00,99 },
	{ 99,00,00,99,00,00,00,00,00,99,99,99,99,99,00,99,99,00,99 },
	{ 99,00,99,99,99,99,99,99,00,99,00,00,00,00,00,00,00,00,99 },
	{ 99,00,00,00,00,99,00,00,00,00,00,99,99,99,99,00,99,00,99 },
	{ 99,00,99,99,00,99,00,99,00,99,00,99,00,00,99,00,99,00,99 },
	{ 99,00,99,00,00,00,00,99,00,99,00,99,00,00,99,00,99,00,99 },
	{ 99,00,99,99,99,99,99,99,00,99,00,99,00,00,99,00,99,00,99 },
	{ 99,00,99,00,00,00,99,99,00,99,00,99,99,00,99,99,99,00,99 },
	{ 99,00,99,00,99,00,00,00,00,00,00,00,00,00,00,00,00,00,99 },
	{ 99,00,99,99,99,99,99,99,99,99,00,99,99,99,99,99,99,00,99 },
	{ 99,00,00,00,00,00,99,99,00,00,00,99,00,00,00,00,00,00,99 },
	{ 99,00,00,99,00,00,00,00,00,00,00,00,00,99,00,99,99,00,99 },
	{ 99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99 },
	};

	do {
		clear();
		cout << "      WHICH SIMULATION WILL YOU USE?" << endl;
		cout << "  1 - A* SEARCH ALGORTIHM" << endl;
		cout << "  2 - DEPTH FIRST SEARCH ALGORTIHM" << endl;
		cin >> algorithm;
	} while (algorithm != 1 && algorithm != 2);

	if (algorithm == 1) { astar_search = true; }
	else if (algorithm == 2) { dfs_search = true; }
	cout << "SIMULATION SPEED:" << endl << "0: VERY FAST" << endl << "1: FAST" << endl << "2-3: NORMAL" << endl << "4-5: SLOW" << endl; cin >> sim_speed;

	while (dfs_search) {
		up = arr[curROW - 1][curCOL];
		right = arr[curROW][curCOL + 1];
		left = arr[curROW][curCOL - 1];
		down = arr[curROW + 1][curCOL];

		if (curCOL == finaleCOL && curROW == finaleROW) {
			dfs_search = false;
			printMAP(arr); cout << endl;
			cout << endl; cout << "SIMULATION FINISHED. " << endl; 
			cout << "Number of Steps: " << roadNUM << endl;
			cout << "Number of Failed Step Attempts: " << failed_steps << endl << endl;
			cout << " TOTAL ATTEMPTS:  " << failed_steps + roadNUM << endl << endl << endl;
			cout << "PRESS ANYTHING TO FINISH PROGRAM ";
			cin >> finish; exit(0);
		}

		if (up == 0) {
			curROW -= 1;
			roadNUM++;
			arr[curROW][curCOL] = roadNUM;
		}
		else if (left == 0) {
			curCOL -= 1;
			roadNUM++;
			arr[curROW][curCOL] = roadNUM;
		}
		else if (right == 0) {
			curCOL += 1;
			roadNUM++;
			arr[curROW][curCOL] = roadNUM;
		}
		else if (down == 0) {
			curROW += 1;
			roadNUM++;
			arr[curROW][curCOL] = roadNUM;
		}
		else {
			if (up == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curROW -= 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (left == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curCOL -= 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (right == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curCOL += 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (down == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curROW += 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else {
				cout << "ERROR??";
				printMAP(arr);
				Sleep(2000);
			}
		}
		printMAP(arr);
		Sleep(sim_speed * 100);
		clear();
	}

	while (astar_search) {
		up = arr[curROW - 1][curCOL];
		right = arr[curROW][curCOL + 1];
		left = arr[curROW][curCOL - 1];
		down = arr[curROW + 1][curCOL];
			
		if (curCOL == finaleCOL && curROW == finaleROW) {
			astar_search = false;
			printMAP(arr); cout << endl;
			cout << endl; cout << "SIMULATION FINISHED. " << endl; 
			cout << "Number of Steps: " << roadNUM << endl;
			cout << "Number of Failed Step Attempts: " << failed_steps << endl << endl;
			cout << " TOTAL ATTEMPTS:  " << failed_steps + roadNUM << endl << endl << endl;
			cout << "PRESS ANYTHING TO FINISH PROGRAM ";
			cin >> finish; exit(0);	}

		if (up == 0) { up_av = true; }	else { up_av = false; }
		if (left == 0) {	left_av = true;	}	else { left_av = false; }
		if (right == 0) {	right_av = true;}	else { right_av = false; }
		if (down == 0) {	down_av = true;	}	else { down_av = false; }

		if (up_av || left_av || right_av || down_av) {

			if (up==0) { cost_up = cost(curROW-1, curCOL); }	else { cost_up = 99999; }
			if (right==0) { cost_right = cost(curROW, curCOL+1); }	else { cost_right = 99999; }
			if (left==0) { cost_left = cost(curROW, curCOL-1); }	else { cost_left = 99999; }
			if (down==0) { cost_down = cost(curROW+1, curCOL); }	else { cost_down = 99999; }

			double minimum_yon = find_smallest(cost_up,cost_right,cost_left,cost_down);

			if (minimum_yon == cost_up) {
				curROW -= 1;
				roadNUM++;
				arr[curROW][curCOL] = roadNUM;
			}
			else if (minimum_yon == cost_right) {
				curCOL += 1;
				roadNUM++;
				arr[curROW][curCOL] = roadNUM;

			}
			else if (minimum_yon == cost_left) {
				curCOL -= 1;
				roadNUM++;
				arr[curROW][curCOL] = roadNUM;

			}
			else if(minimum_yon == cost_down){
				curROW += 1;
				roadNUM++;
				arr[curROW][curCOL] = roadNUM;
			}
			else {
				cout << "ERROR??";
				printMAP(arr);
				Sleep(20000);
			}
		}else {
			if (up == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curROW -= 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (left == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curCOL -= 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (right == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curCOL += 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else if (down == roadNUM - 1) {
				arr[curROW][curCOL] = 98;
				curROW += 1;
				roadNUM -= 1;
				arr[curROW][curCOL] = roadNUM; failed_steps++;
			}
			else {
				cout << "ERROR??";
				printMAP(arr);
				Sleep(2000);
			}
		}
		
		cout << endl; cout << "Heuristic Distance: " << cost(curROW, curCOL) << endl;
		cout << "     UP: " << arr[curROW-1][curCOL] << endl;
		cout << "LEFT: " << arr[curROW][curCOL-1] << " RIGHT: " << arr[curROW][curCOL+1] << endl;
		cout << "    DOWN: " << arr[curROW+1][curCOL] << endl;
		printMAP(arr);
		Sleep(sim_speed * 100);
		clear();
		}
	}