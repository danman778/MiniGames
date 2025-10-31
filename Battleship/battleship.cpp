#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
#define HORIZONTAL 0
#define VERTICAL 1
using namespace std;

void Draw_Box(int x, int y, int color = DARKGRAY) {
	if(x>9 || y>9) {
		return;
	}
	int box_Width = getmaxy()/12;
	setfillstyle(SOLID_FILL,color);
	bar(box_Width*(x+1),box_Width*(y+1),box_Width*(x+2),box_Width*(y+2));
}

class player {
	public:
		bool Place_Ship(int size,int x,int y,int rotation) {
			if (x+(1-rotation)*size > 10 || y+(rotation*size) > 10 ) {
				return false;
			}
			for (int i = 0; i < size; i++) {
				if (ship_Board[x+i*(1-rotation)][y+i*rotation] == 1) {
					return false;
				}
			}
			for (int i = 0; i < size; i++) {
				ship_Board[x+i*(1-rotation)][y+i*rotation] = 1;
			}
			return true;
		}
		void Disp_Ships() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (ship_Board[i][j]==1) {
						Draw_Box(i,j,LIGHTGRAY);
					}
				}
			}
		}
		void Disp_Guesses() {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (guess_Board[i][j]==1) {
						Draw_Box(i,j,LIGHTGREEN);
					}
					if (guess_Board[i][j]==-1) {
						Draw_Box(i,j,RED);
					}
				}
			}
		}
		bool Shot_Fired(int x, int y, int opp_Board[10][10]) {
			if(guess_Board[x][y] !=0 ) {
				return false;
			}
			if (opp_Board[x][y]==1) {
				guess_Board[x][y] = 1;
				cout << "HIT" << endl;
				hits++;
			}
			else {
				guess_Board[x][y] = -1;
				cout << "MISS" << endl;
			}
			guesses++;
			return true;
		}
		int ship_Board[10][10];
		void Clear_Boards() {
			//cout << "CLEARING" << endl;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					guess_Board[i][j] = 0;
					ship_Board[i][j] = 0;
				}
			}
		}
		double Get_Hit_Percentage() {
			return hits/guesses*100;
		}
	private:
		int guess_Board[10][10];
		double hits = 0;
		double guesses = 0;
};


void Draw_Grid() {
	int row_Size = getmaxy()/12;
	for (int i = 1; i < 12; i++) {
		line(row_Size*i,row_Size,row_Size*i,11*row_Size);
		line(row_Size,row_Size*i,11*row_Size,row_Size*i);
	}
}

void Draw_Rotate_Button(int color = BLACK) {
	setbkcolor(color);
	settextstyle(SIMPLEX_FONT,HORIZ_DIR,3);
	int width = textwidth("rotate");
	int height = textheight("rotate");
	int text_X = (getmaxx()+11*getmaxy()/12-width)/2;
	int text_Y = (getmaxy()-height)/2;
	outtextxy(text_X,text_Y,"rotate");
	line(text_X-5,text_Y-5,text_X+width+5,text_Y-5);
	line(text_X-5,text_Y-5,text_X-5,text_Y+height+5);
	line(text_X+width+5,text_Y-5,text_X+width+5,text_Y+height+5);
	line(text_X-5,text_Y+height+5,text_X+width+5,text_Y+height+5);
}


void Clear_Box(int x,int y) {
	if(x>9 || y>9) {
		return;
	}
	int box_Width = getmaxy()/12;
	setfillstyle(SOLID_FILL,BLACK);
	bar(box_Width*(x+1),box_Width*(y+1),box_Width*(x+2),box_Width*(y+2));
	Draw_Grid();
}


int main () {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	player(P_1);
	player(P_2);
	int xbox;
	int ybox;
	int rot = HORIZONTAL;
	int last_Box[2];
	bool valid_Box = false;
	int box_Width = getmaxy()/12;
	vector<player> player_Box;
	player_Box.push_back(P_1);
	player_Box.push_back(P_2);
	Draw_Grid();
	Draw_Rotate_Button();
	cout << "Welcome to Battleship" << endl << "   [click board to start]" << endl;
	while (!ismouseclick(WM_LBUTTONDOWN)) {
		delay(1);
	}
	for (int i = 0; i < 2; i++) {
		Draw_Grid();
		Draw_Rotate_Button();
		player_Box.at(i).Clear_Boards();
		cout << "Player " << i+1 << " placing.." << endl;
		for (int j =10;j>4; j--) {
			clearmouseclick(WM_LBUTTONDOWN);
			while (!(ismouseclick(WM_LBUTTONDOWN) && valid_Box)) {
				valid_Box = false;
				clearmouseclick(WM_LBUTTONDOWN);
				xbox = (mousex()/box_Width)-1;
				ybox = (mousey()/box_Width)-1;
				if (xbox>=0 && xbox < 10 && ybox >= 0 && ybox < 10) {
					if (xbox != last_Box[0] || ybox != last_Box[1]) {
						for (int k = 0; k < j/2; k++) {
							Clear_Box(last_Box[0]+k*(1-rot),last_Box[1]+k*rot);
						}
						player_Box[i].Disp_Ships();
					}
					for (int k = 0; k < j/2; k++) {
						Draw_Box(xbox+k*(1-rot),ybox+k*rot);
					}
					last_Box[0] = xbox;
					last_Box[1] = ybox;
					if (ismouseclick(WM_LBUTTONDOWN)) {
						valid_Box = player_Box[i].Place_Ship(j/2,xbox,ybox,rot);
						player_Box[i].Disp_Ships();
					}
				}
				else {
					for (int i = 0; i < j/2; i++) {
						Clear_Box(last_Box[0]+i*(1-rot),last_Box[1]+i*rot);
					}
					last_Box[0] = -2;
				}
				int m = mousex();
				int n = mousey();
				if (m>=496 && m <= 582 && n >= 223 && n <= 256)  {
					Draw_Rotate_Button(DARKGRAY);
					if (ismouseclick(WM_LBUTTONDOWN) ) {
					rot = 1-rot;
					}
				}
				else if (last_Box[0]==-2) {
					Draw_Rotate_Button();
				}
			}
		}
		clearmouseclick(WM_LBUTTONDOWN);
		delay(1000);
		cleardevice();
		system("CLS");
		if (i == 0) {
			cout << "Pass device and click board to start placing" << endl;
		}
		else {
			cout << "[click]" << endl;
		}
		while (!ismouseclick(WM_LBUTTONDOWN)) {
			delay(1);
		}
	}
	int i=0;
	cout << "Player " << 1 << ":" << endl;
	cout << "Hit Percentage: " << player_Box[0].Get_Hit_Percentage() << "%" << endl;
	while (1) {
		valid_Box = false;
		clearmouseclick(WM_LBUTTONDOWN);
		xbox = (mousex()/box_Width)-1;
		ybox = (mousey()/box_Width)-1;
		if (xbox>=0 && xbox < 10 && ybox >= 0 && ybox < 10) {
			if (xbox != last_Box[0] || ybox != last_Box[1]) {
				Clear_Box(last_Box[0],last_Box[1]);
				player_Box[i].Disp_Guesses();
			}
			Draw_Box(xbox,ybox);
			last_Box[0] = xbox;
			last_Box[1] = ybox;
			if (ismouseclick(WM_LBUTTONDOWN)) {
				valid_Box = player_Box[i].Shot_Fired(xbox,ybox,player_Box[1-i].ship_Board);
				if (valid_Box) {
					player_Box[i].Disp_Guesses();
					delay(1000);
					cleardevice();
					i=1-i;
					Draw_Grid();
					player_Box[i].Disp_Guesses();
					system("CLS");
					cout << "Player " << i+1 << ":" << endl;
					cout << "Hit Percentage: " << player_Box[i].Get_Hit_Percentage() << "%" << endl;
				}
			}
		}
		else {
			Clear_Box(last_Box[0],last_Box[1]);
			last_Box[0] = -2;
		}
	}
	
	getch();
	closegraph();
	return 0;
}
