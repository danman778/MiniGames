#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
using namespace std;


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
	cout << endl;
	return lines;
}

int Get_Percent() {
	cout << "input percent blocks: ";
	int percent;
	cin >> percent;
	cout << endl;
	return percent;
}

void Show_Grid(int lines){
	for(int i = 0; i < lines; i++){
		line (0,i*480/(lines),640,i*480/(lines));
		line (i*640/lines,0,i*640/lines,480);
	}
}

Random_Grid(vector<vector<int> > &grid, int percent) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			int is_Box = rand() % 100;
			if (is_Box < percent) {
				grid[i][j] = 1;
			}
		}
	}
}

void Show_Boxes(vector<vector<int> > &grid, int x, int y, int num = 3) {
	if (num == 3) {
		num = grid.size();
		for (int i = -1; i < 2; i++) {
			if (x+i < 0) {
				if (grid[grid.size()-1][y] == 1) {
					Block(grid.size()-1,y,grid.size());
				}
			}
			else if (x+i >= grid.size()) {
				if (grid[0][y] == 1) {
					Block(0,y,grid.size());
				}
			}
			else if(grid[x+i][y] == 1) {
				Block(x+i,y,grid.size());
			}
			if (y+i < 0) {
				if (grid[x][grid.size()-1] == 1) {
					Block(x,grid.size()-1,grid.size());
				}
			}
			else if (y+i >= grid.size()) {
				if (grid[x][0] == 1) {
					Block(x,0,grid.size());
				}
			}
			else if(grid[x][y+i] == 1) {
				Block(x,y+i,grid.size());
			}
		}
	}
	else {
		for(int i = 0; i < grid.size(); i++) {
			for(int j = 0; j < grid.size(); j++) {
				if(grid[i][j] == 1) {
					Block(i,j,grid.size());
				}
				if(grid[i][j] == 9) {
					Sol_Block(i,j,grid.size());
				}
			}
		}
	}
}

void Show_Cursor(vector<vector<int> > &grid, int x, int y,int color = GREEN) {
	int n = grid.size();
	setfillstyle(3,color);
	if(grid[x][y] == 1) {
		setbkcolor(BLUE);
	}
	bar(x*640/n,y*480/n,(x+1)*640/n+1,(y+1)*480/n+1);
	setbkcolor(BLACK);
}

bool Maze_Solve(vector<vector<int> > &M,int x, int y, int &calls, int &dir) {
	if (M[x-1][y-1] != 0 ){
    	return false;
	}
	calls++;
	if (calls > 100000) {
		return false;
	}
	M[x-1][y-1] = 9;
	if (x == M.size() && y == M[0].size()){
		return true;
	}
	for (int i  = 0; i < 4; i++) {
		if (x+dir%2<=M.size() && x+dir%2>0 && y+dir/2<=M.size() && y+dir/2>0 && Maze_Solve(M,x+dir%2,y+dir/2,calls,dir)){
	    	return true;
	    }
	    dir += -3*(dir%2) - dir/2; 
	}
	M[x-1][y-1] = 8;
  return false;
}

void Clr_Line(vector<vector<int> > &grid) {
	for(int i = 0; i < grid.size(); i++) {
		for(int j = 0; j < grid[0].size(); j++) {
			if(grid[i][j] == 9) {
				grid[i][j] = 0;
			}
		}
	}
}

int main() {
	//initialize
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	int num_Lines = Get_Grid_Size();
	bool keep_Editing = true;
	int input;
	Show_Grid(num_Lines);
	vector<vector<int> > grid(num_Lines,vector<int>(num_Lines,0));
	int percent_Block = Get_Percent();
	Random_Grid(grid,percent_Block);
	cout << "Welcome to maze_solver random edition!"<<endl;
	cout << "The path goes from the top left corner to bottom right corner" << endl;
	cout << "Use wasd to move" << endl;
	cout << "Hit enter to toggle blocks!" << endl;
	cout << "and 't' to toggle grid" << endl;
	cout << "Press 'm' when finished" << endl;
	bool grid_On = false;
	cleardevice();
	while(keep_Editing) {
		Clr_Line(grid);
		int x_Pos = 0;
		int y_Pos = 0;
		bool still_Building = true;
		Show_Cursor(grid,x_Pos,y_Pos);
		Show_Boxes(grid,0,0,0);
		while(still_Building) {
			if (_kbhit() || kbhit()){
				Show_Cursor(grid,x_Pos,y_Pos,BLACK);
				if (_kbhit()) {
					input = _getch();
				}
				else {
					input = getch();
				}
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
				grid[0][0] = 0;
				grid[num_Lines-1][num_Lines-1] = 0;
				Show_Boxes(grid,x_Pos,y_Pos);
				Show_Cursor(grid,x_Pos,y_Pos);
			}
		}
		cleardevice();
		Show_Boxes(grid,0,0,0);
		cout << "solving..." << endl;
		delay(1000);
		setfillstyle(SOLID_FILL,DARKGRAY);
		floodfill(1,1,BLUE);
		int dir = 2;
		int calls = 0;
		bool has_Sol = Maze_Solve(grid,1,1,calls,dir);
		Show_Boxes(grid,0,0,0);
		if (!has_Sol) {
			cout << "no dice, sorry" << endl;
		}
		cout << "Edit maze? (y/n)" << endl;
		char cont;
		cin >> cont;
		if (cont != 'y') {
			keep_Editing = false;
			cout << "ok bye!" << endl;
		}
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid.size(); j++) {
				if (grid[i][j] != 0 && grid[i][j] != 1) {
					grid[i][j] = 0;
				}
			}
		}
		cleardevice();
	}
	getch();
	closegraph();
	return 0;
}
