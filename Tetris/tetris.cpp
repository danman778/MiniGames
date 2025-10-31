#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
using namespace std;


void box(int lx,int by) {
	rectangle(lx+1,by-19,lx+19,by-1);
}

void piece(int x, int by, int type, int r, int useColor = 1) {
	int color = type*useColor;
	setcolor(color);
	int lx = x*20+10;
	if (type == 1) {
		if (r%2 == 0) {
			box(lx+40,by);
			box(lx+20,by);
			box(lx+20,by-20);
			box(lx,by-20);
		}
		if (r%2 == 1) {
			box(lx,by);
			box(lx,by-20);
			box(lx+20,by-20);
			box(lx+20,by-40);
		}
	}
	if (type == 2) {
		if (r%2 == 0) {
			box(lx+40,by-20);
			box(lx+20,by-20);
			box(lx+20,by);
			box(lx,by);
		}
		if (r%2 == 1) {
			box(lx+20,by);
			box(lx+20,by-20);
			box(lx,by-20);
			box(lx,by-40);
		}
	}
	if (type == 3) {
		if (r == 0) {
			box(lx+20,by-20);
			box(lx,by);
			box(lx,by-20);
			box(lx,by-40);
		}
		if (r == 1) {
			box(lx+20,by);
			box(lx,by);
			box(lx+40,by);
			box(lx+20,by-20);
		}
		if (r == 2) {
			box(lx+20,by);
			box(lx+20,by-20);
			box(lx,by-20);
			box(lx+20,by-40);
		}
		if (r == 3) {
			box(lx+20,by);
			box(lx+20,by-20);
			box(lx,by-20);
			box(lx+40,by-20);
		}
	}
	if(type == 4) {
		if (r == 0) {
			box(lx,by-40);
			box(lx+20,by-40);
			box(lx+20,by-20);
			box(lx+20,by);
		}
		if (r == 3) {
			box(lx+40,by);
			box(lx+20,by);
			box(lx,by);
			box(lx+40,by-20);
		}
		if (r == 2) {
			box(lx,by);
			box(lx,by-20);
			box(lx,by-40);
			box(lx+20,by);
		}
		if (r == 1) {
			box(lx,by);
			box(lx,by-20);
			box(lx+20,by-20);
			box(lx+40,by-20);
		}
	}
	if (type == 5) {
		if (r == 0) {
			box(lx+20,by-40);
			box(lx,by);
			box(lx,by-20);
			box(lx,by-40);
		}
		if (r == 1) {
			box(lx+20,by);
			box(lx+40,by);
			box(lx,by-20);
			box(lx,by);
		}
		if (r == 2) {
			box(lx,by);
			box(lx+20,by);
			box(lx+20,by-20);
			box(lx+20,by-40);
		}
		if (r == 3) {
			box(lx,by-20);
			box(lx+20,by-20);
			box(lx+40,by-20);
			box(lx+40,by);
		}
	}
	if (type == 6) {
		if (r%2 == 0) {
			box(lx,by);
			box(lx,by-20);
			box(lx,by-40);
			box(lx,by-60);
		}
		if (r%2 == 1) {
			box(lx,by);
			box(lx+20,by);
			box(lx+40,by);
			box(lx+60,by);
		}
	}
	if (type == 7) {
		box(lx,by);
		box(lx+20,by);
		box(lx,by-20);
		box(lx+20,by-20);
	}
}

bool CheckCollision(int x, int by, int type, int r, int g[24][10],bool* lose = 0) {
	int y = (410-by)/20;
	if (type == 1) {
		if (r%2 == 0) {
			if (g[y][x+1] || g[y][x+2] || g[y+1][x] || g[y+1][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r%2 == 1) {
			if (g[y][x]  || g[y+1][x] || g[y+1][x+1] || g[y+2][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	if (type == 2) {
		if (r%2 == 0) {
			if (g[y][x] || g[y][x+1] || g[y+1][x+1] || g[y+1][x+2]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r%2 == 1) {
			if (g[y][x+1] || g[y+2][x] || g[y+1][x] || g[y+1][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	if (type == 3) {
		if (r == 0) {
			if (g[y][x] || g[y+1][x+1] || g[y+1][x] || g[y+2][x]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 1) {
			if (g[y][x+1] || g[y][x+2] || g[y][x] || g[y+1][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 2) {
			if (g[y][x+1] || g[y+2][x+1] || g[y+1][x] || g[y+1][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 3) {
			if (g[y][x+1] || g[y+1][x+2] || g[y+1][x] || g[y+1][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	if (type == 4) {
		if (r == 0) {
			if (g[y][x+1] || g[y+1][x+1] || g[y+2][x+1] || g[y+2][x])  {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 3) {
			if (g[y][x+1] || g[y][x+2] || g[y][x] || g[y+1][x+2]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 2) {
			if (g[y][x+1] || g[y][x] || g[y+1][x] || g[y+2][x]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}if (r == 1) {
			if (g[y+1][x] || g[y+1][x+1] || g[y+1][x+2] || g[y][x]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	if (type == 5) {
		if (r == 0) {
			if (g[y][x] || g[y+1][x] || g[y+2][x] || g[y+2][x+1]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 1) {
			if (g[y][x] || g[y+1][x] || g[y][x+1] || g[y][x+2]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 2) {
			if (g[y][x+1] || g[y+1][x+1] || g[y+2][x+1] || g[y][x]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r == 3) {
			if (g[y+1][x] || g[y+1][x+1] || g[y+1][x+2] || g[y][x+2]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	if (type == 7) {
		if (g[y][x+1] || g[y][x] || g[y+1][x] || g[y+1][x+1]) {
			if (y == 20) {
				*lose = true;
			}
			return false;
		}
	}
	if (type == 6) {
		if (r%2 == 0) {
			if (g[y][x] || g[y+2][x] || g[y+1][x] || g[y+3][x]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
		if (r%2 == 1) {
			if (g[y][x] || g[y][x+1] || g[y][x+2] || g[y][x+3]) {
				if (y == 20) {
					*lose = true;
				}
				return false;
			}
		}
	}
	return true;
}

void PutData(int x, int by, int type, int r, int g[][10]) {
	int y = (410-by)/20 + 1;
	if (type == 1) {
		if (r%2 == 0) {
			g[y][x+1] = type;
			g[y][x+2] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
		if (r%2 == 1) {
			g[y][x] = type;
			g[y+2][x+1] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
	}
	if (type == 2) {
		if (r%2 == 0) {
			g[y][x] = type;
			g[y][x+1] = type;
			g[y+1][x+2] = type;
			g[y+1][x+1] = type;
		}
		if (r%2 == 1) {
			g[y][x+1] = type;
			g[y+2][x] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
	}
	if (type == 3) {
		if (r == 0) {
			g[y+1][x+1] = type;
			g[y+2][x] = type;
			g[y+1][x] = type;
			g[y][x] = type;
		}
		if (r == 1) {
			g[y][x] = type;
			g[y][x+1] = type;
			g[y][x+2] = type;
			g[y+1][x+1] = type;
		}
		if (r == 2) {
			g[y][x+1] = type;
			g[y+2][x+1] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
		if (r == 3) {
			g[y][x+1] = type;
			g[y+1][x+2] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
	}
	if (type == 4) {
		if (r == 0) {
			g[y][x+1] = type;
			g[y+1][x+1] = type;
			g[y+2][x] = type;
			g[y+2][x+1] = type;
		}
		if (r == 1) {
			g[y][x] = type;
			g[y+1][x+2] = type;
			g[y+1][x] = type;
			g[y+1][x+1] = type;
		}
		if (r == 2) {
			g[y][x+1] = type;
			g[y][x] = type;
			g[y+1][x] = type;
			g[y+2][x] = type;
		}
		if (r == 3) {
			g[y][x+1] = type;
			g[y][x+2] = type;
			g[y][x] = type;
			g[y+1][x+2] = type;
		}
	}
	if (type == 5) {
		if (r == 0) {
			g[y][x] = type;
			g[y+1][x] = type;
			g[y+2][x] = type;
			g[y+2][x+1] = type;
		}
		if (r == 1) {
			g[y][x+1] = type;
			g[y][x+2] = type;
			g[y+1][x] = type;
			g[y][x] = type;
		}
		if (r == 2) {
			g[y][x+1] = type;
			g[y][x] = type;
			g[y+2][x+1] = type;
			g[y+1][x+1] = type;
		}
		if (r == 3) {
			g[y+1][x+1] = type;
			g[y][x+2] = type;
			g[y+1][x] = type;
			g[y+1][x+2] = type;
		}
	}
	if (type == 6) {
		if (r%2 == 0) {
			g[y][x] = type;
			g[y+1][x] = type;
			g[y+2][x] = type;
			g[y+3][x] = type;
		}
		if (r%2 == 1) {
			g[y][x+3] = type;
			g[y][x+2] = type;
			g[y][x] = type;
			g[y][x+1] = type;
		}
	}
	if (type == 7) {
		g[y][x+1] = type;
		g[y][x] = type;
		g[y+1][x] = type;
		g[y+1][x+1] = type;
	}
}

void Move(char input, int* x, int i, int type, int r, int g[24][10]) {
	if (input == '4') {
		if (*x == 0) {
			return;
		}
		if (CheckCollision(*x-1,i-20,type,r,g) && CheckCollision(*x-1,i-39,type,r,g)) {
			*x = *x - 1;
		}
	}
	else {
		if (*x == 9 && type == 6 && r%2 == 0) {
			return;
		}
		if (*x == 8 && (type == 7 || ((type == 1 || type == 2) && r%2 == 1) || ((type == 3 || type == 4 || type == 5) && r%2 == 0))) {
			return;
		}
		if (*x == 7 && (((type == 1 || type == 2) && r%2 == 0) || ((type == 3 || type == 4 || type == 5) && r%2 == 1))) {
			return;
		}
		if (*x == 6 && (type == 6 && r%2 == 1)) {
			return;
		}
		if (CheckCollision(*x+1,i-20,type,r,g) && CheckCollision(*x+1,i-39,type,r,g)) {
			*x = *x + 1;
		}
	}
}

void Rotate(char input, int x, int by, int type, int* r, int g[24][10]) {
	int rotate;
	if (input == 'a') {
		rotate = *r+1;
	}
	else {
		rotate = *r+3;
	}
	if (rotate > 3) {
		rotate = rotate - 4;
	}
	if (x == 8 && (((type == 1 || type == 2) && *r%2 == 1 ) || ((type == 3 || type == 4 || type == 5) && *r%2 == 0))) {
		return;
	}
	if ((x == 7 || x == 8 || x == 9) && type == 6 && *r%2 == 0) {
		return;
	}
	if (CheckCollision(x,by-20,type,rotate,g) && CheckCollision(x,by-39,type,rotate,g)) {
		*r = rotate;
	}
}

void RowClear(int row, int g[][10]) {
	for (int k = 0; k < 10; k++) {
		g[row][k] = 0;
	}
	delay(50);
	for (int l = row; l < 23; ++l) {
		for (int j = 0; j < 10; j++) {
			setcolor(g[l+1][j]);
			box(j*20+10,430-l*20);
			g[l][j] = g[l+1][j];
		}
	}
}

void RowCheck(int g[][10],int * points){
	int sum;
	int rows = 0;
	for (int i = 1; i < 21; i++) {
		sum = 0;
		for (int j = 0; j < 10; j++) {
			if (g[i][j] != 0)
			sum += 1;
		}
		if (sum == 10) {
			RowClear(i,g);
			rows += 1;
			*points += 10*rows;
			i-=1;
		}
	}
	if (rows != 0) {
		cout << *points << " points" << endl;
	}
}



int main() {
	//initializations
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	const int starting_height = 10;
	int x=1;
	int n;
	int t = rand() %7 +1;
	int g[24][10];
	for (int i = 0; i < 10; ++i) {
		g[0][i] = 1;
	}
	for (int i = 1; i < 24; ++i) {
		for (int j = 0; j < 10; ++j) {
			g[i][j] = 0;
		}
	}
	string str;
	line(10,10,10,410);
	line(10,410,210,410);
	line(210,410,210,10);
	bool cont = true;
	bool lose = false;
	char input;
	int y;
	int speed = 10;
	int r;
	string a;
	int score = 0;
	cout << "Welcome to fake tetris!" << endl;
	cout << "Have this terminal open to input," << endl;
	cout << "a and d rotate; 4 and 6 move. 5 sends the piece down" << endl;
	cout << " [press enter to start]  " << endl;
	getline(cin,a);
	//start game
	while (!lose) {
		int i = starting_height;
		speed = 10;
		n = rand() % 7 + 1;
		x = 4;
		r = 0;
		piece(12,80,n,r);
		while (cont) {
			if (_kbhit()) {
				input = _getch();
				if(input == '4' || input == '6') {   //4 moves left; 6 right
					Move(input,&x,i,t,r,g);
				}
				if(input == 'a' || input == 'd') {   //a rotates left, d right
					Rotate(input,x,i,t,&r,g);
				}
				if (input == '5') {
					if (speed == 10) {
						speed = 0;
					}
					else {
						speed = 10;
					}
				}
			}
			piece(x,i,t,r);
			delay(speed);
			if (i%20 == 10) {
				bool cont = CheckCollision(x,i,t,r,g,&lose);
				if (!cont) {
					if (_kbhit()) {
						input = _getch();
						if(input == '4' || input == '6') {   //4 moves left; 6 right
							Move(input,&x,i,t,r,g);
						}
						if(input == 'a' || input == 'd') {   //a rotates left, d right
							Rotate(input,x,i,t,&r,g);
						}
						if (input == '5') {
							if (speed == 10) {
								speed = 0;
							}
							else {
								speed = 10;
							}
						}
					}
					PutData(x,i,t,r,g);
					break;
				}
			}
			piece(x,i,t,r,0);
			i+=1;
		}
		RowCheck(g, &score);
		piece(12,80,n,0,0);
		t = n;
		if (lose) {
			cout << "Game over :0" << endl << "  [Ctrl+C to exit]" << endl;
		}
	}
	cin >> a;
	getch();
	closegraph();
	return 0;
}
