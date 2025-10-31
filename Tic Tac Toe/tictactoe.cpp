#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>

#define HORIZ_WIN		1
#define VERT_WIN		2
#define TL_DIAG_WIN		3
#define TR_DIAG_WIN		4

using namespace std;
const int letter_Width = 30;
const int edge_Buffer = 5;
const int x_Color = LIGHTGREEN;
const int o_Color = CYAN;
int maxx;
int maxy;

void Draw_Lines() {
	for (int i = 1; i < 3; i++) {
		line(i*maxx/3,0,i*maxx/3,maxy);
		line(0,i*maxy/3,maxx,i*maxy/3);
	}
}

void Draw_X(int x_Pos, int y_Pos, string type = "FIXED") {
	if (type == "GHOST") {
		setcolor(LIGHTGRAY);
	}
	else if (type == "INVALID") {
		setcolor(RED);
	}
	else if (type == "ERASE") {
		setcolor(BLACK);
	}
	else if (type == "WIN") {
		setcolor(WHITE);
	}
	else {
		setcolor(x_Color);
	}
	int center_x = x_Pos*maxx/3 + maxx/6;
	int center_y = y_Pos*maxy/3 + maxy/6;
	int j = 1;
	for (int i = 0; i < 4; i++) {
		line(center_x, center_y - j*letter_Width/sqrt(2), (x_Pos+(1-j)/2 + i%2-i/3*2)*maxx/3 + (i%2*-2+1)*j*(edge_Buffer + letter_Width/sqrt(2)), (y_Pos+(1-j)/2)*maxy/3 + j*edge_Buffer);
		line(center_x - (i%2*-2+1)*j*letter_Width/sqrt(2), center_y, (x_Pos+(1-j)/2+i%2-i/3*2)*maxx/3 + (i%2*-2+1)*j*edge_Buffer, (y_Pos+(1-j)/2)*maxy/3 + j*(edge_Buffer + letter_Width/sqrt(2)));
		line((x_Pos+(1-j)/2 + i%2-i/3*2)*maxx/3 + (i%2*-2+1)*j*(edge_Buffer + letter_Width/sqrt(2)), (y_Pos+(1-j)/2)*maxy/3 + j*edge_Buffer,(x_Pos+(1-j)/2+i%2-i/3*2)*maxx/3 + (i%2*-2+1)*j*edge_Buffer, (y_Pos+(1-j)/2)*maxy/3 + j*(edge_Buffer + letter_Width/sqrt(2)));
		if (i == 1) {
			j*=-1;
		}
	}
}

void Draw_O(int x_Pos, int y_Pos, string type = "FIXED") {
	if (type == "GHOST") {
		setcolor(LIGHTGRAY);
	}
	else if (type == "INVALID") {
		setcolor(RED);
	}
	else if (type == "ERASE") {
		setcolor(BLACK);
	}
	else if (type == "WIN") {
		setcolor(WHITE);
	}
	else {
		setcolor(o_Color);
	}
	int center_x = x_Pos*maxx/3 + maxx/6;
	int center_y = y_Pos*maxy/3 + maxy/6;
	ellipse(center_x,center_y,0,360,maxx/6-edge_Buffer,maxy/6-edge_Buffer);
	ellipse(center_x,center_y,0,360,maxx/6-edge_Buffer-letter_Width,maxy/6-edge_Buffer-letter_Width);
}

bool Check_Full(vector<vector<int> > board) {
	for (int i =0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

int Check_Wins(vector<vector<int> > board,int x_box,int y_box) {
	if (board[0][y_box] == board[1][y_box] && board[0][y_box] == board[2][y_box]) {
		return HORIZ_WIN;
	}
	if (board[x_box][0] == board[x_box][1] && board[x_box][0] == board[x_box][2]) {
		return VERT_WIN;
	}
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0) {
		return TL_DIAG_WIN;
	}
	if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != 0) {
		return TR_DIAG_WIN;
	}
	return 0;
}



int main() {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	maxx = getmaxx();
	maxy = getmaxy();
	vector<vector<int> > board(3,vector<int>(3,0));
	bool game_Over = false;
	int box_x,box_y;
	int to_Draw_x = -1;
	int to_Draw_y = -1;
	int turn = 1;
	int win_Type = 0;
	cout << "TIC TAC TOE!" << endl << "   [click board to start]" << endl;
	while (!ismouseclick(WM_LBUTTONDOWN)) {
		delay(1);
	}
	clearmouseclick(WM_LBUTTONDOWN);
	Draw_Lines();
	box_x = mousex()/(maxx/3);
	box_y = mousey()/(maxy/3);
	while (!game_Over) {
		if (ismouseclick(WM_LBUTTONDOWN) && board[box_x][box_y] == 0) {
			if (turn%2 == 1) {
				Draw_X(box_x,box_y);
				board[box_x][box_y] = 1;
			}
			else {
				Draw_O(box_x,box_y);
				board[box_x][box_y] = 2;
			}
			game_Over = Check_Full(board);
			win_Type = Check_Wins(board,box_x,box_y);
			game_Over = game_Over || win_Type;
			turn ++;
		}
		clearmouseclick(WM_LBUTTONDOWN);
		box_x = mousex()/(maxx/3);
		box_y = mousey()/(maxy/3);
		if (box_x != to_Draw_x || box_y != to_Draw_y) {
			if (to_Draw_x == -1) {
				to_Draw_x = box_x;
				to_Draw_y = box_y;
			}
			if (turn%2 == 1) {
				Draw_X(to_Draw_x,to_Draw_y,"ERASE");
			}
			else {
				Draw_O(to_Draw_x,to_Draw_y,"ERASE");
			}
			if (board[to_Draw_x][to_Draw_y] == 1) {
				Draw_X(to_Draw_x,to_Draw_y);
			}
			else if (board[to_Draw_x][to_Draw_y] == 2){
				Draw_O(to_Draw_x,to_Draw_y);
			}
			to_Draw_x = box_x;
			to_Draw_y = box_y;
			if (board[box_x][box_y] != 0) {
				if (turn%2 == 1) {
					Draw_X(box_x,box_y,"INVALID");
				}
				else {
					Draw_O(box_x,box_y,"INVALID");
				}
			}
			else {
				if (turn%2 == 1) {
					Draw_X(box_x,box_y,"GHOST");
				}
				else {
					Draw_O(box_x,box_y,"GHOST");
				}
			}
		}
		delay(50);
	}
	turn--;
	if (win_Type != 0) {
		string draw_Type = "WIN";
		while (1) {
			if (win_Type == HORIZ_WIN) {
				if (turn%2 == 1) {
					Draw_X(0,box_y,draw_Type);
					Draw_X(1,box_y,draw_Type);
					Draw_X(2,box_y,draw_Type);
				}
				else {
					Draw_O(0,box_y,draw_Type);
					Draw_O(1,box_y,draw_Type);
					Draw_O(2,box_y,draw_Type);
				}
			}
			if (win_Type == VERT_WIN) {
				if (turn%2 == 1) {
					Draw_X(box_x,0,draw_Type);
					Draw_X(box_x,1,draw_Type);
					Draw_X(box_x,2,draw_Type);
				}
				else {
					Draw_O(box_x,0,draw_Type);
					Draw_O(box_x,1,draw_Type);
					Draw_O(box_x,2,draw_Type);
				}
			}
			if (win_Type == TL_DIAG_WIN) {
				if (turn%2 == 1) {
					Draw_X(0,0,draw_Type);
					Draw_X(1,1,draw_Type);
					Draw_X(2,2,draw_Type);
				}
				else {
					Draw_O(0,0,draw_Type);
					Draw_O(1,1,draw_Type);
					Draw_O(2,2,draw_Type);
				}
			}
			if (win_Type == TR_DIAG_WIN) {
				if (turn%2 == 1) {
					Draw_X(2,0,draw_Type);
					Draw_X(1,1,draw_Type);
					Draw_X(0,2,draw_Type);
				}
				else {
					Draw_O(2,0,draw_Type);
					Draw_O(1,1,draw_Type);
					Draw_O(0,2,draw_Type);
				}
			}
			if (draw_Type == "WIN") {
				draw_Type = "ERASE";
			}
			else {
				draw_Type = "WIN";
			}
			delay(500);
		}
	}
	
	getch();
	closegraph();
	return 0;
}
