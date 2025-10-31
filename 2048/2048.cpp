#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
using namespace std;

void box(int x, int y, int num, int color = 0) {
	if (num == 0) {
		return;
	}
	if (num == 2) {
		setcolor(color);
		line(x+10,y+10,x-10,y+10);
		line(x-10,y+10,x+10,y-10);
		ellipse(x,y-10,0,180,10,10);
	}
	if (num == 4) {
		color = color*2;
		setcolor(color);
		line(x+10,y,x-10,y);
		line(x,y+15,x,y-15);
		line(x-10,y,x-10,y-15);
	}
	if (num == 8) {
		color= color *3;
		setcolor(color);
		circle(x,y-10,10);
		circle(x,y+10,10);
	}
	if (num == 16) {
		color = color*4;
		setcolor(color);
		line (x-20,y-15,x-20,y+15);
		line (x+20,y-15,x,y+10);
		ellipse(x+10,y+10,180,440,10,10);
	}
	if (num == 32) {
		color = color*5;
		setcolor(color);
		ellipse(x-10,y-10,270,500,10,8);
		ellipse(x-10,y+6,220,450,10,8);
		line(x+30,y+10,x+10,y+10);
		line(x+10,y+10,x+30,y-10);
		ellipse(x+20,y-10,0,180,10,10);
	}
	if (num == 64) {
		color = color*6;
		setcolor(color);
		line (x,y-15,x-20,y+10);
		ellipse(x-10,y+10,180,440,10,10);
		line(x+30,y,x+10,y);
		line(x+20,y+15,x+20,y-15);
		line(x+10,y,x+10,y-15);
	}
	if (num == 128) {
		color = color*7;
		setcolor(color);
		line(x-20,y+10,x-20,y-19);
		line(x+10,y+10,x-10,y+10);
		line(x-10,y+10,x+10,y-10);
		ellipse(x,y-10,0,180,10,10);
		circle(x+25,y-12,8);
		circle(x+25,y+5,9);
	}
	if (num == 256) {
		color = color*8;
		setcolor(color);
		line(x-20,y+13,x-40,y+13);
		line(x-40,y+13,x-20,y-7);
		ellipse(x-30,y-7,0,180,10,10);
		line(x+10,y-17,x-10,y-17);
		line(x-10,y-17,x-10,y-2);
		ellipse(x-1,y+7,225,135,10,10);
		line (x+40,y-20,x+20,y+5);
		ellipse(x+30,y+5,180,440,10,10);
	}
	if (num == 512) {
		color = color*9;
		setcolor(color);
		line(x-11,y-20,x-30,y-20);
		line(x-30,y-20,x-30,y-5);
		ellipse(x-21,y+2,225,135,10,10);
		line(x,y+10,x,y-20);
		line(x+30,y+10,x+10,y+10);
		line(x+10,y+10,x+30,y-10);
		ellipse(x+20,y-10,0,180,10,10);
	}
	if (num == 1024) {
		color = color*10;
		setcolor(color);
		line(x-35,y+10,x-35,y-20);
		ellipse(x-18,y-5,0,360,10,17);
		line(x+15,y+10,x-5,y+10);
		line(x-5,y+10,x+15,y-10);
		ellipse(x+5,y-10,0,180,10,10);
		line(x+40,y-5,x+20,y-5);
		line(x+30,y+10,x+30,y-20);
		line(x+20,y-5,x+20,y-20);
	}
	if (num == 2048) {
		color = color*11;
		setcolor(color);
		line(x-15,y+10,x-35,y+10);
		line(x-35,y+10,x-15,y-10);
		ellipse(x-25,y-10,0,180,10,10);
		ellipse(x-3,y-5,0,360,9,17);
		line(x+30,y-5,x+10,y-5);
		line(x+20,y+10,x+20,y-20);
		line(x+10,y-5,x+10,y-20);
		ellipse(x+40,y-12,0,360,6,8);
		ellipse(x+40,y+5,0,360,6,9);
	}
	rectangle(x-48,y-48,x+48,y+48);
}

void Clear(int array[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j =0; j < 4; j++) {
			array[i][j] = 0;
		}
	}
}


bool MoveLeft(int grid[][4]) {
	int temp;
	bool retVal = 0;
	int hasMerged[4][4];
	Clear(hasMerged);
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j] != 0) {
				if (grid[i-1][j] == grid [i][j] && hasMerged[i-1][j] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i-50,100*j+50,temp);
					box(100*i-50,100*j+50,2*temp,1);
					grid[i-1][j] *= 2;
					grid[i][j] = 0;
					retVal = 1;
					hasMerged[i-1][j] = 1;
				}
				if (grid[i-1][j] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i-50,100*j+50,temp,1);
					grid[i-1][j] = grid[i][j];
					grid[i][j] = 0;
					retVal = 1;
					if (i != 1) { 
						i-=1;
						j-=1;
					}
				}
			}
		}
	}
	return retVal;
}

bool MoveRight(int grid[][4]) {
	int temp;
	bool retVal = 0;
	int hasMerged[4][4];
	Clear(hasMerged);
	for (int i = 2; i > -1; i--) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j] != 0) {
				if (grid[i+1][j] == grid [i][j] && hasMerged[i+1][j] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+150,100*j+50,temp);
					box(100*i+150,100*j+50,2*temp,1);
					grid[i+1][j] *= 2;
					grid[i][j] = 0;
					retVal = 1;
					hasMerged[i+1][j] = 1;
				}
				if (grid[i+1][j] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+150,100*j+50,temp,1);
					grid[i+1][j] = grid[i][j];
					grid[i][j] = 0;
					retVal = 1;
					if (i != 2) { 
						i+=1;
						j-=1;
					}
				}
			}
		}
	}
	return retVal;
}

bool MoveDown(int grid[][4]) {
	int temp;
	bool retVal = 0;
	int hasMerged[4][4];
	Clear(hasMerged);
	for (int j = 2; j > -1; j--) {
		for (int i = 0; i < 4; i++) {
			if (grid[i][j] != 0) {
				if (grid[i][j+1] == grid [i][j] && hasMerged[i][j+1] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+50,100*j+150,temp);
					box(100*i+50,100*j+150,2*temp,1);
					grid[i][j+1] *= 2;
					grid[i][j] = 0;
					retVal = 1;
					hasMerged[i][j+1] = 1;
				}
				if (grid[i][j+1] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+50,100*j+150,temp,1);
					grid[i][j+1] = grid[i][j];
					grid[i][j] = 0;
					retVal = 1;
					if (j != 2) { 
						i-=1;
						j+=1;
					}
				}
			}
		}
	}
	return retVal;
}

bool MoveUp(int grid[][4]) {
	int temp;
	bool retVal = 0;
	int hasMerged[4][4];
	Clear(hasMerged);
	for (int j = 1; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (grid[i][j] != 0) {
				if (grid[i][j-1] == grid [i][j] && hasMerged[i][j-1] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+50,100*j-50,temp);
					box(100*i+50,100*j-50,2*temp,1);
					grid[i][j-1] *= 2;
					grid[i][j] = 0;
					retVal = 1;
					hasMerged[i][j-1] = 1;
				}
				if (grid[i][j-1] == 0) {
					temp = grid[i][j];
					box(100*i+50,100*j+50,temp);
					box(100*i+50,100*j-50,temp,1);
					grid[i][j-1] = grid[i][j];
					grid[i][j] = 0;
					retVal = 1;
					if (j != 1) { 
						i-=1;
						j-=1;
					}
				}
			}
		}
	}
	return retVal;
}

void StoreGrid(int grid[4][4], int moveNum, vector<vector<vector<int> > >& stoVec) {
	vector<vector<int> > temp(4,vector<int>(4,0));
	stoVec.push_back(temp);
	cout << "move " << moveNum << ":" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			stoVec[moveNum][i][j] = grid[i][j];
			cout << stoVec[moveNum][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool UndoMove(int grid[][4], int* moveNum, vector<vector<vector<int> > >& stoVec) {
	if (*moveNum < 2) {
		return false;
	}
	int eraseNum;
	int setNum;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			eraseNum = grid[i][j];
		 	box(100*i+50,100*j+50,eraseNum);
			setNum = stoVec[*moveNum - 2][i][j];
			if (setNum != 0) {
				 box(100*i+50,100*j+50,setNum,1);
			}
			grid[i][j] = setNum;
		}
	}
	stoVec.pop_back();
	stoVec.pop_back();
	*moveNum -= 2;
	return true;
}

int main() {
	//initialize
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	int grid[4][4];
	vector<vector<vector<int> > > stoVec(0, vector<vector<int> > (4, vector<int>(4,0)));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j<4; j++) {
			grid[i][j] = 0;
		}
	}
	int n,m,c,x,y,num;
	char move;
	bool valid;
	
	//start
	cout << "Welcome to fake 2048!" << endl;
	cout << "Remember to keep this box in front!" << endl;
	cout << "Now go ahead and go for it using the number pad" << endl;
	cout << "and hit 'u' for undo!" << endl;
	setcolor(WHITE);
	line(400,0,400,400);
	line(0,400,400,400);
	int moveNum = 0;
	bool notDead = 1;
	while (notDead) {
		//put box
		do {
			n = rand() % 4;
			m= rand() %4;
		} while (grid[n][m] != 0);
		c = rand() % 10;
		if (c == 0) {
			num = 4;
		}
		else {
			num = 2;
		}
		grid[n][m] = num;
		x = 100*n+50;
		y = 100*m+50;
		box(x,y,num,1);
		
		//move
		valid = 0;
		do {
			if (_kbhit()) {
				move = _getch();
			}
			else {
				move = '0';	
			}
			if (move == '4') {
				valid = MoveLeft(grid);
			} 
			else if (move == '6') {
				valid = MoveRight(grid);
			}
			else if (move == '8') {
				valid = MoveUp(grid);
			}
			else if (move == '2') {
				valid = MoveDown(grid);
			}
			else if (move == 'u') {
				valid = UndoMove(grid,&moveNum,stoVec);
			}
		} while (!valid);
		
		// store grid
		StoreGrid(grid,moveNum,stoVec);
		
		moveNum++;
		
		delay(150);	
	}
	getch();
	closegraph();
	return 0;
}
