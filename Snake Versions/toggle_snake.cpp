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


bool Maze_Solve(vector<vector<int> > &M,int x, int y, vector<int> &x_Path, vector<int> &y_Path, int apple_X, int apple_Y, int &num_Calls) {
	num_Calls++;
	if (num_Calls > 1000) {
		return false;
	}
	if (M[x][y] != 0) {
    	return false;
	}
	M[x][y] = 9;
	if (x == apple_X && y == apple_Y) {
		x_Path.push_back(x);
		y_Path.push_back(y);
		return true;
	}
	if (y != 0 && Maze_Solve(M,x,y-1,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
    }
    else if (y!=0){
    	M[x][y-1] = 1;
	}
	if (y != M[0].size()-1 && Maze_Solve(M,x,y+1,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
		return true;
	}
	else if (y!=M[0].size()-1){
    	M[x][y+1] = 1;
	}
	if (x != M.size()-1 && Maze_Solve(M,x+1,y,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
	}
	else if (x!=M.size()-1) {
    	M[x+1][y] = 1;
	}
	if (x != 0 && Maze_Solve(M,x-1,y,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
    }
    else if(x!=0) {
    	M[x-1][y] = 1;
	}
  return false;
}


bool Maze_Solve2(vector<vector<int> > &M,int x, int y, vector<int> &x_Path, vector<int> &y_Path, int apple_X, int apple_Y, int &num_Calls) {
	num_Calls++;
	if (num_Calls > 1000) {
		return false;
	}
	cout << num_Calls << endl;
	if (M[x][y] != 0) {
    	return false;
	}
	M[x][y] = 9;
	if (x == apple_X && y == apple_Y) {
		x_Path.push_back(x);
		y_Path.push_back(y);
		return true;
	}
	if (x != 0 && Maze_Solve(M,x-1,y,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
    }
    else {
    	M[x-1][y] = 1;
	}
	if (x != M.size()-1 && Maze_Solve(M,x+1,y,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
	}
	else {
    	M[x+1][y] = 1;
	}
	if (y != M[0].size()-1 && Maze_Solve(M,x,y+1,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
		return true;
	}
	else {
    	M[x][y+1] = 1;
	}
	if (y != 0 && Maze_Solve(M,x,y-1,x_Path,y_Path,apple_X,apple_Y,num_Calls)){
		x_Path.push_back(x);
		y_Path.push_back(y);
    	return true;
    }
    else {
    	M[x][y-1] = 1;
	}
	M[x][y] = 0;
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
	bool has_Path;
	bool toggle = true;
	int apple_X;
	int apple_Y;
	vector<int> x_Path;
	vector<int> y_Path;
	cout << "Welcome to snake!"<<endl;
	cout << "Use arrow keys to move" << endl;
	Put_Block(0,0,grid.size(),LIGHTGREEN);
	Make_Apple(x_Points,y_Points,num_Lines,apple_X,apple_Y);
	vector<vector<int> > temp_Grid = grid;
	int num = 0;
	has_Path = Maze_Solve(temp_Grid,x_Points.at(0),y_Points.at(0),x_Path,y_Path,apple_X,apple_Y,num);
	x_Path.pop_back();
	y_Path.pop_back();
	while(!is_Dead) {
		delay(40);
		if (has_Path && !toggle) {
			if (x_Path.at(x_Path.size()-1) < x_Points.at(0)) {
				curr_Dir = LEFT;
			}
			if (x_Path.at(x_Path.size()-1) > x_Points.at(0)) {
				curr_Dir = RIGHT;
			}
			if (y_Path.at(y_Path.size()-1) > y_Points.at(0)) {
				curr_Dir = DOWN;
			}
			if (y_Path.at(y_Path.size()-1) < y_Points.at(0)) {
				curr_Dir = UP;
			}
			x_Path.pop_back();
			y_Path.pop_back();
		}
		else if(!toggle){
			if (grid[(x_Points.at(0)-1+num_Lines)%num_Lines][y_Points.at(0)] == 0) {
				curr_Dir = LEFT;
			}
			else {
				if (grid[(x_Points.at(0)+1)%num_Lines][y_Points.at(0)] == 0) {
					curr_Dir = RIGHT;
				}
				if (grid[x_Points.at(0)][(y_Points.at(0)+1)%num_Lines] == 0) {
					curr_Dir = DOWN;
				}
				if (grid[x_Points.at(0)][(y_Points.at(0)-1+num_Lines)%num_Lines] == 0) {
					curr_Dir = UP;
				}
			}
		}
		if (kbhit()){
			input = getch();
			if (input == 116) {
				toggle = !toggle;
				has_Path = false;
			}
			if (toggle) {
				if (input == 0 && toggle) {
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
		}
		is_Dead = Move_Snake(curr_Dir,x_Points,y_Points,length,num_Lines);
		Put_Snake(grid,x_Points,y_Points);
		if (x_Points.at(0) == apple_X && y_Points.at(0) == apple_Y) {
			length++;
			Make_Apple(x_Points,y_Points,num_Lines,apple_X,apple_Y);
			system("CLS");
			cout << "Score: " << length - 3 << endl; 
			has_Path = false;
		}
		if (!has_Path && !toggle) {
			x_Path.clear();
			y_Path.clear();
			for (int i = 0; i < num_Lines; i++) {
				for (int j = 0; j < num_Lines; j++) {
					temp_Grid[i][j] = grid[i][j];
				}
			}
			temp_Grid[x_Points.at(0)][y_Points.at(0)] = 0;
			num = 0;
			if (!Maze_Solve(temp_Grid,x_Points.at(0),y_Points.at(0),x_Path,y_Path,apple_X,apple_Y,num)) {
				num = 0;
				has_Path = Maze_Solve2(temp_Grid,x_Points.at(0),y_Points.at(0),x_Path,y_Path,apple_X,apple_Y,num);
			}
			else {
				has_Path = true;
			}
			x_Path.pop_back();
			y_Path.pop_back();
		}
	}
	cout << "You died" << endl;
	getch();
	closegraph();
	return 0;
}
