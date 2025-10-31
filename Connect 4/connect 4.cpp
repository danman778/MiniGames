#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
using namespace std;



void Set_Up_Board(int game_Board[][6]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			game_Board[i][j] = 0;
		}
	}
}

void Disp_Board(int board[7][6]) {
	int row = getmaxx();
	int col = getmaxy();
	cleardevice();
	setlinestyle(SOLID_LINE,0,3);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,YELLOW);
	line(row,col,row,col/7);
	for (int i = 0; i < 7; i++) {
		line(i*row/7,col,i*row/7,col/7);
		line(0,col-i*col/7,row,col-i*col/7);
	}
	setlinestyle(SOLID_LINE,0,1);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			if (board[i][j] != 0) {
				if (board[i][j] == 1) {
					setfillstyle(SOLID_FILL,RED);
				}
				else {
					setfillstyle(SOLID_FILL,YELLOW);
				}
				fillellipse(i*row/7+row/14,j*col/7+3*col/14,row/14,col/14);
			}
		}
	}
}


void Disp_Piece (int the_Row,int row,int col,int turn_Color) {
	setcolor(turn_Color);
	setfillstyle(XHATCH_FILL,turn_Color);
	fillellipse(the_Row*row/7+row/14,col/14,row/14,col/14);
}

void Put_Board (int board[][6], int row_To_Put, int num_To_Put) {
	int test = 5;
	while (board[row_To_Put][test] != 0 ) {
		test-=1;
	}
	board[row_To_Put][test] = num_To_Put;
}

void Print_Board(int board[7][6]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			cout << board[j][i];
		}
		cout << endl;
	}
}


void Store_Grid(int grid[7][6], int moveNum, vector<vector<vector<int> > >& stoVec) {
	vector<vector<int> > temp(7,vector<int>(6,0));
	stoVec.push_back(temp);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			stoVec[moveNum][i][j] = grid[i][j];
		}
	}
}

bool Undo_Move(int grid[][6], int* moveNum, vector<vector<vector<int> > >& stoVec) {
	if (*moveNum < 2) {
		return false;
	}
	int setNum;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++) {
			setNum = stoVec[*moveNum - 2][i][j];
			grid[i][j] = setNum;
		}
	}
	stoVec.pop_back();
	*moveNum -= 1;
	return true;
}

void Switch_Color(int* color) {
	if (*color == RED) {
		*color = YELLOW;
		}
	else {
		*color = RED;
	}
}



int main () {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	int game_Board[7][6];
	vector<vector<vector<int> > > sto_Vec(1, vector<vector<int> > (7, vector<int>(6,0)));
	int row = getmaxx();
	int col = getmaxy();
	char inpt;
	cout << "Connect 4!" << endl << "  [click board to start]" << endl;
	int turn = 1;
	int turn_Color = RED;
	int move_Num = 1;
	int curr_Row = -1;
	int disped_Piece = -1;
	Set_Up_Board(game_Board);
	Disp_Board(game_Board);
	while (!ismouseclick(WM_LBUTTONDOWN)) {
		delay(1);
	}
	clearmouseclick(WM_LBUTTONDOWN);
	while (1) {
		curr_Row = (mousex()*7)/row;
		if (curr_Row != disped_Piece) {
			Disp_Piece(disped_Piece,row,col,BLACK);
			Disp_Piece(curr_Row,row,col,turn_Color);
		}
		disped_Piece = curr_Row;
		if (ismouseclick(WM_LBUTTONDOWN) && game_Board[curr_Row][0] == 0) {
			Put_Board(game_Board,curr_Row,turn);
			Disp_Board(game_Board);
			clearmouseclick(WM_LBUTTONDOWN);
			turn = -turn;
			Store_Grid(game_Board,move_Num,sto_Vec);
			move_Num += 1;
			Switch_Color(&turn_Color);
		}
		clearmouseclick(WM_LBUTTONDOWN);
		if(_kbhit()) {
			inpt = _getch();
			if (inpt == 'u') {
				if (Undo_Move(game_Board,&move_Num,sto_Vec)){
					Disp_Board(game_Board);
					turn = -turn;
					Switch_Color(&turn_Color);
				}
			}
		}
	}
	
	
	
	getch();
	closegraph();
	return 0;
}
