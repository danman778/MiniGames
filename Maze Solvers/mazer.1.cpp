#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
using namespace std;

int Convert_x(double a) {
	return 300+150*a;
}

int Convert_y(double a) {
	return 200-100*a;
}

void Block(int x,int y,int n) {
	setfillstyle(SOLID_FILL,BLUE);
	bar(x*640/n,y*480/n,(x+1)*640/n+1,(y+1)*480/n+1);
}

void Sol_Block(int x,int y,int n) {
	setfillstyle(SOLID_FILL,RED);
	bar(x*640/n,y*480/n,(x+1)*640/n+1,(y+1)*480/n+1);
}


int Get_Grid_Size() {
	cout << "input grid dimension: ";
	int lines;
	cin >> lines;
	return lines;
}

void Show_Grid(int lines){
	for(int i = 0; i < lines; i++){
		line (0,i*480/(lines),640,i*480/(lines));
		line (i*640/lines,0,i*640/lines,480);
	}
}

void Show_Boxes(vector<vector<int> > &grid) {
	for(int i = 0; i < grid.size(); i++) {
		for(int j = 0; j < grid[0].size(); j++) {
			if(grid[i][j] == 1) {
				Block(i,j,grid.size());
			}
			if(grid[i][j] == 9) {
				Sol_Block(i,j,grid.size());
			}
		}
	}
}

void Show_Cursor(vector<vector<int> > &grid, int x, int y) {
	int n = grid.size();
	setfillstyle(3,GREEN);
	if(grid[x][y] == 1) {
		setbkcolor(BLUE);
	}
	bar(x*640/n,y*480/n,(x+1)*640/n+1,(y+1)*480/n+1);
	setbkcolor(BLACK);
}

bool Maze_Solve(vector<vector<int> > &M,int x, int y) {
	if (M[x-1][y-1] != 0 ){
    	return false;
	}
	M[x-1][y-1] = 9;
	if (x == M.size() && y == M[0].size()){
		return true;
	}
	if (y != M[0].size() && Maze_Solve(M,x,y+1)){
		return true;
	}
	if (x != M.size() && Maze_Solve(M,x+1,y)){
    	return true;
	}
	if (x != 1 && Maze_Solve(M,x-1,y)){
    	return true;
    }
	if (y != 1 && Maze_Solve(M,x,y-1)){
    	return true;
    }
	M[x-1][y-1] = 0;
  return false;
}

int main() {
	//initialize
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	int num_Lines = Get_Grid_Size();
	Show_Grid(num_Lines);
	vector<vector<int> > grid(num_Lines,vector<int>(num_Lines,0));
	int input;
	int x_Pos = 0;
	int y_Pos = 0;
	bool still_Building = true;
	bool grid_On = true;
	Show_Cursor(grid,x_Pos,y_Pos);
	cout << "Welcome to maze_solver!"<<endl;
	cout << "The path goes from the top left corner to bottom right corner" << endl;
	cout << "Use wasd to move" << endl;
	cout << "Hit enter to toggle blocks!" << endl;
	cout << "and 't' to toggle grid" << endl;
	cout << "Press 'm' when finished" << endl;
	while(still_Building) {
		if (_kbhit()){
			cleardevice();
			input = _getch();
			if (input == 119) {
				y_Pos -= 1;
				if(y_Pos < 0) {
					y_Pos = num_Lines - 1;
				}
			}
			if (input == 97) {
				x_Pos -= 1;
				if(x_Pos < 0) {
					x_Pos = num_Lines - 1;
				}
			}
			if(input == 115) {
				y_Pos += 1;
				if(y_Pos == num_Lines) {
					y_Pos = 0;
				}
			}
			if(input == 100) {
				x_Pos += 1;
				if(x_Pos == num_Lines) {
					x_Pos = 0;
				}
			}
			if (input == 13) {
				grid[x_Pos][y_Pos] = grid[x_Pos][y_Pos]*(-1) + 1;
			}
			if(input == 116) {
				grid_On = !grid_On;
			}
			if(input == 109) {
				still_Building = false;
			}
			if (grid_On) {
				Show_Grid(num_Lines);
			}
			Show_Boxes(grid);
			Show_Cursor(grid,x_Pos,y_Pos);
		}
	}
	cleardevice();
	Show_Boxes(grid);
	cout << "solving..." << endl;
	delay(1000);
	bool has_Sol = Maze_Solve(grid,1,1);
	Show_Boxes(grid);
	if (!has_Sol) {
		cout << "no dice, sorry" << endl;
	}
	getch();
	closegraph();
	return 0;
}
