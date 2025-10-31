#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
#define RIGHT		1
#define LEFT		-1
#define DOWN		2
#define UP			-2
#define STOP		0

using namespace std;

const int x_Lines = 70;
const int y_Lines = 45;
const double Pi = 3.14159;

void Put_Block(int x,int y, int color = BLACK) {
	setfillstyle(SOLID_FILL,color);
	bar(x*getmaxx()/x_Lines,y*getmaxy()/y_Lines,(x+1)*getmaxx()/x_Lines,(y+1)*getmaxy()/y_Lines);
}


void Show_Boxes(vector<vector<int> > &grid) {
	for(int i = 0; i < grid.size(); i++) {
		for(int j = 0; j < grid[0].size(); j++) {
			if(grid[i][j] == 1) {
				Put_Block(i,j,CYAN);
			}
			if(grid[i][j] == 7) {
				Put_Block(i,j,GREEN);
			}
		}
	}
}

void Put_Border(vector<vector<int> > &grid) {
	for (int i = 0; i < x_Lines; i++) {
		for (int j = 0; j < y_Lines; j++) {
			if (i < 2 || j < 2 || x_Lines-i < 3 || y_Lines-j < 3) {
				grid[i][j] = 1;
			}
			else {
				grid[i][j] = 0;
			}
		}
	}
}

bool Move_Block(int &x, int &y, int dir, vector<vector<int> > &grid) {
	int new_x = x + dir%2;
	int new_y = y + dir/2;
	int color = BLACK;
	if (new_x < 0) {
		new_x = 0;
	}
	if (new_x == x_Lines) {
		new_x--;
	}
	if (new_y < 0) {
		new_y++;
	}
	if (new_y == y_Lines) {
		new_y--;
	}
	if (x != new_x || y != new_y) {
		if (grid[x][y] == 1) {
			color = CYAN;
		}
		if (grid[x][y] == 9) {
			color = MAGENTA;
		}
		Put_Block(x,y,color);
		Put_Block(new_x,new_y,RED);
		x = new_x;
		y = new_y;
		if (grid[x][y] == 9) {
			return true;
		}
		if (grid[x][y] == 0) {
			grid[x][y] = 9;
		}
	}
	return false;
}


bool Maze_Solve(vector<vector<int> > &M,int x, int y, int apple_X, int apple_Y, int &num_Calls, int& dir) {
	num_Calls++;
	if (x == apple_X && y == apple_Y) {
		return true;
	}
	if (M[x][y] == 0) {
		return true;
	}
	if (num_Calls > 1000) {
		//return false;
	}
	if (M[x][y] == 8 || M[x][y] == 1 || M[x][y] == 9) {
    	return false;
	}
	M[x][y] = 8;
	for (int i  = 0; i < 4; i++) {
		if (y != 0 && Maze_Solve(M,x+dir%2,y+dir/2,apple_X,apple_Y,num_Calls,dir)){
	    	return true;
	    }
	    dir += -3*(dir%2) - dir/2; 
	}
  return false;
}

class Bullet {
	public:
		Bullet(double x, double y, int a = 45) {
			x_Pos = x;
			y_Pos = y;
			angle = a;
			radius = 3;
		}
		int get_x() {
			return x_Pos;
		}
		int get_y() {
			return y_Pos;
		}
		void Move(vector<vector<int> > grid) {
			Hide_Bullet();
			int mov_x = 2*sin(angle*Pi/180);
			int mov_y = -2*cos(angle*Pi/180);
			bool changed = false;
			if (grid[x_Pos+mov_x][y_Pos] == 1) {
				angle = 360-angle;
				mov_x = 2*sin(angle*Pi/180);
				changed = true;
			}
			if (grid[x_Pos][y_Pos+mov_y] == 1) {
				angle = 180-angle;
				mov_y = -2*cos(angle*Pi/180);
				changed = true;
			}
			if (grid[x_Pos+mov_x][y_Pos+mov_y] == 1 && !changed) {
				angle -= 180;
				mov_x = 2*sin(angle*Pi/180);
				mov_y = -2*cos(angle*Pi/180);
			}
			x_Pos += mov_x;
			y_Pos += mov_y;
			Show_Bullet();
			return;
		}
		void Show_Bullet() {
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL,LIGHTGRAY);
			fillellipse((x_Pos+.5)*getmaxx()/x_Lines,(y_Pos+.5)*getmaxy()/y_Lines,radius,radius);
		}
		void Hide_Bullet() {
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			fillellipse((x_Pos+.5)*getmaxx()/x_Lines,(y_Pos+.5)*getmaxy()/y_Lines,radius,radius);
		}
	private:
		int x_Pos;
		int y_Pos;
		int angle;
		int radius;
};


void Fill_Grid(vector<vector<int> > &grid, int x, int y, vector<Bullet> bullets) {
	int num;
	int start_Dir;
	int fill_to = 0;
	for (int i = 0; i < x_Lines; i++) {
		for (int j = 0; j < y_Lines; j++) {
			if (grid[i][j] == 0) {
				grid[i][j] = 2;
			}	
		}
	}
	int h = 0;
	for (int h = 0; h < bullets.size(); h++) {
		for (int i = 0; i < x_Lines; i++) {
			for (int j = 0; j < y_Lines; j++) {
				num = 0;
				start_Dir = DOWN;
				if (!Maze_Solve(grid,i,j,bullets.at(h).get_x(),bullets.at(h).get_y(),num,start_Dir)) {
					fill_to = 3;
				}
				else {
					fill_to = 0;
				}
				for (int k = 0; k < x_Lines; k++) {
					for (int l = 0; l < y_Lines; l++) {
						if (grid[k][l] == 8) {
							grid[k][l] = fill_to;
						}
					}
				}
			}
		}
	}
	fill_to = 1;
	for (int i = 1; i < bullets.size(); i++) {
		grid[bullets.at(i).get_x()][bullets.at(i).get_y()] = 0;
	}
	for (int i = 0; i < x_Lines; i++) {
		for (int j = 0; j < y_Lines; j++) {
			num = 0;
			if (grid[i][j] == 9 || grid[i][j] == 3) {
				grid[i][j] = 1;
			}
			if (grid[i][j] == 2) {
				grid[i][j] = 0;
			}
		}
	}
	Show_Boxes(grid);
}


int main() {
	//initialize
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	vector<vector<int> > grid(x_Lines,vector<int>(y_Lines,0));
	Put_Border(grid);
	Show_Boxes(grid);
	int input;
	int x_Pos = x_Lines / 2;
	int y_Pos = 0;
	int lvl_Num = 1;
	int lives = 3;
	bool is_Out = true;
	int curr_Dir = STOP;
	bool is_Dead = false;
	double num_Blocks;
	vector<Bullet> bullet_List;
	Bullet B_1 = Bullet(20,20);
	bullet_List.push_back(B_1);
	cout << "Welcome to xonix!"<<endl;
	cout << "Use arrow keys to move" << endl;
	Put_Block(x_Pos,y_Pos,RED);
	while(lives) {
		delay(30);
		if (kbhit()){
			input = getch();
			if (input == 0) {
				input = getch();
			}
			if (input == 75) {
				curr_Dir = LEFT;
			}
			if (input == 77) {
				curr_Dir = RIGHT;
			}
			if(input == 72) {
				curr_Dir = UP;
			}
			if(input == 80) {
				curr_Dir = DOWN;
			}
			if (input == 82) {
				curr_Dir = STOP;
			}
		}
		is_Dead = Move_Block(x_Pos,y_Pos,curr_Dir,grid);
		if (is_Out && grid[x_Pos][y_Pos] == 9) {
			is_Out = false;
		}
		if (!is_Out && grid[x_Pos][y_Pos] == 1) {
			curr_Dir = STOP;
			Fill_Grid(grid,x_Pos,y_Pos,bullet_List);
			is_Out = true;
			system("CLS");
			num_Blocks = 0;
			for (int i = 2; i < x_Lines-2; i++) {
				for (int j = 2; j < y_Lines-2; j++) {
					num_Blocks += grid[i][j];
				}
			}
			int per_Covered = 100*num_Blocks/(x_Lines-4)/(y_Lines-4);
			cout << "Percent covered: " << per_Covered << endl;
			if (per_Covered >= 75) {
				system("CLS");
				cout << "Level " << lvl_Num << " beat!" << endl;
				lvl_Num++;
				cleardevice();
				Put_Border(grid);
				B_1 = Bullet(20,20);
				bullet_List.push_back(B_1);
				x_Pos = x_Lines/2;
				y_Pos = 0;
				Show_Boxes(grid);
				num_Blocks = 0;
			}
			Put_Block(x_Pos,y_Pos,RED);
		}
		for (int i = 0; i < bullet_List.size(); i++) {
			bullet_List.at(i).Move(grid);
			is_Dead =  is_Dead || grid[bullet_List.at(i).get_x()][bullet_List.at(i).get_y()];
		}
		if (is_Dead) {
			lives--;
			delay(500);
			curr_Dir = STOP;
			if (lives) {
				is_Out = true;
				cleardevice();
				x_Pos = x_Lines/2;
				y_Pos = 0;
				for (int i = 0; i < x_Lines; i++) {
					for (int j = 0; j < y_Lines; j++) {
						if (grid[i][j] == 9) {
							grid[i][j] = 0;
						}
					}
				}
				Show_Boxes(grid);
				Put_Block(x_Pos,y_Pos,RED);	
				cout << lives << " lives left" << endl;			
			}
		}
	}
	cout << "You died" << endl;
	getch();
	closegraph();
	return 0;
}
