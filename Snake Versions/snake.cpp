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

using namespace std;

int Convert_x(double a) {
	return 300+150*a;
}

int Convert_y(double a) {
	return 200-100*a;
}

void Put_Block(int x,int y,int n, int color = BLACK) {
	setfillstyle(SOLID_FILL,color);
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
				Put_Block(i,j,grid.size());
			}
			if(grid[i][j] == 9) {
				Put_Block(i,j,grid.size());
			}
		}
	}
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

bool Move_Snake(int dir, vector<int> &x, vector<int> &y, int length,int grid_Size)  {
	x.insert(x.begin(),1,(x.at(0) + (dir%2)+grid_Size)%grid_Size);
	y.insert(y.begin(),1,(y.at(0) + (dir/2)+grid_Size)%grid_Size);
	while (length < x.size()) {
		x.pop_back();
		y.pop_back();
	}
	for (int i = 1; i < x.size(); i++) {
		if (x.at(i) == x.at(0) && y.at(i) == y.at(0)) {
			return true;
		}
	}
	return false;
}

void Put_Snake(vector<vector<int> > &grid,vector<int> x,vector<int> y) {
	Put_Block(x.at(0),y.at(0),grid.size(),LIGHTGREEN);
	for (int i = 0; i < x.size(); i++) {
		grid[x.at(i)][y.at(i)] = 2;
	}
	setfillstyle(SOLID_FILL,BLACK);
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid.size(); j++) {
			if (grid[i][j] == 1) {
					Put_Block(i,j,grid.size());
					grid[i][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < x.size(); i++) {
		grid[x.at(i)][y.at(i)] = 1;
	}
}

Make_Apple (vector<int> x, vector<int> y, int size, int &apple_X, int &apple_Y) {
	bool valid_Apple = false;
	while (!valid_Apple) {
		apple_X = rand() % size;
		apple_Y = rand() % size;
		valid_Apple = true;
		for(int i = 0; i < x.size(); i++) {
			if (apple_X == x.at(i) && apple_Y == y.at(i)) {
				valid_Apple = false;
			}
		}
	}
	Put_Block(apple_X,apple_Y,size,RED);
}

int main() {
	//initialize
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	int num_Lines = Get_Grid_Size();
	//Show_Grid(num_Lines);
	vector<vector<int> > grid(num_Lines,vector<int>(num_Lines,0));
	int input;
	int x_Pos = 0;
	int y_Pos = 0;
	int length = 3;
	vector<int> x_Points;
	vector<int> y_Points;
	x_Points.push_back(x_Pos);
	y_Points.push_back(y_Pos);
	int curr_Dir = RIGHT;
	bool is_Dead = false;
	int apple_X;
	int apple_Y;
	cout << "Welcome to snake!"<<endl;
	cout << "Use arrow keys to move" << endl;
	Put_Block(0,0,grid.size(),LIGHTGREEN);
	Make_Apple(x_Points,y_Points,num_Lines,apple_X,apple_Y);
	while(!is_Dead) {
		delay(50);
		if (kbhit()){
			input = getch();
			if (input == 0) {
				input = getch();
			}
			if (input == 75 && curr_Dir != RIGHT) {
				curr_Dir = LEFT;
			}
			if (input == 77 && curr_Dir != LEFT) {
				curr_Dir = RIGHT;
			}
			if(input == 72 && curr_Dir != DOWN) {
				curr_Dir = UP;
			}
			if(input == 80 && curr_Dir != UP) {
				curr_Dir = DOWN;
			}
		}
		is_Dead = Move_Snake(curr_Dir,x_Points,y_Points,length,num_Lines);
		Put_Snake(grid,x_Points,y_Points);
		if (x_Points.at(0) == apple_X && y_Points.at(0) == apple_Y) {
			length++;
			Make_Apple(x_Points,y_Points,num_Lines,apple_X,apple_Y);
			system("CLS");
			cout << "Score: " << length - 3 << endl; 
		}
	}
	cout << "You died" << endl;
	getch();
	closegraph();
	return 0;
}
