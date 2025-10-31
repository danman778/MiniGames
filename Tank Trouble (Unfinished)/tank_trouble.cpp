#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
#include<ctime>
using namespace std;
const double Pi = 3.14159;

void Pause(int ms) {
	clock_t t;
	t = clock();
	while (t+ms >= clock()) {
	}
	return;
}

void Make_Grid(int horiz_Grid[][10],int vert_Grid[][9]) {
	for (int i = 0; i < 9; i++) {
		horiz_Grid[i][0] = 1;
		horiz_Grid[i][9] = 1;
		vert_Grid[0][i] = 1;
		vert_Grid[9][i] = 1;
		for (int j = 1; j < 9; j++) {
			horiz_Grid[i][j] = 0;
			vert_Grid[j][i] = 0;
			int is_Line = rand() % 100;
			if (is_Line < 40) {
				horiz_Grid[i][j] = 1;
			}
			is_Line = rand() % 100;
			if (is_Line < 40) {
				vert_Grid[j][i] = 1;
			}
		}
	}
}

void Draw_Grid(int horiz_Grid[][10],int vert_Grid[][9]) {
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	int xmax= getmaxx();
	int ymax = getmaxy();
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (horiz_Grid[i][j] == 1) {
				line(xmax/9*i,ymax/9*(j),xmax/9*(i+1),ymax/9*(j));
			}
			if (vert_Grid[j][i] == 1) {
				line(xmax/9*(j),ymax/9*i,xmax/9*(j),ymax/9*(i+1));
			}
		}
	}
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
}

class Bullet {
	public:
		Bullet(double x, double y, int a) {
			x_Pos = x;
			y_Pos = y;
			angle = a;
			radius = 3;
		}
		void Move(int horiz_Lines[][10], int vert_Lines[][9]) {
			Hide_Bullet();
			double mov_x = 1*sin(angle*Pi/180);
			double mov_y = -1*cos(angle*Pi/180);
			double test_x=mov_x+x_Pos;
			double test_y= mov_y+y_Pos;
			if (Vert_Collision(test_x,test_y,vert_Lines)) {
				mov_x *= -1;
				angle = 360-angle;
			}
			if (Horiz_Collision(test_x,test_y,horiz_Lines)) {
				mov_y *= -1;
				angle = 180-angle;
			}
			x_Pos += mov_x;
			y_Pos += mov_y;
			Show_Bullet();
			return;
		}
		bool Vert_Collision(int x, int y, int vert_Lines[][9]) {
			if (x % (getmaxx()/9) == 0 && vert_Lines[x/(getmaxx()/9)][y/(getmaxy()/9)]) {
				return true;
			}
			/*if (x % (getmaxx()/9) <= getmaxx()/9-2-radius && vert_Lines[x/(getmaxx()/9)+1][y/(getmaxy()/9)]) {
				return true;
			}*/
			return false;
		}
		bool Horiz_Collision(int x, int y, int horiz_Lines[][10]) {
			if (y % (getmaxy()/9) ==0 && horiz_Lines[x/(getmaxx()/9)][y/(getmaxy()/9)]) {
				return true;
			}
			/*if (y % (getmaxy()/9) <= getmaxy()/9-2-radius && horiz_Lines[x/(getmaxx()/9)][y/(getmaxy()/9)+1]) {
				return true;
			}*/
			return false;
		}
		void Show_Bullet() {
			setcolor(LIGHTGRAY);
			setfillstyle(SOLID_FILL,LIGHTGRAY);
			fillellipse(x_Pos,y_Pos,radius,radius);
		}
		void Hide_Bullet() {
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			fillellipse(x_Pos,y_Pos,radius,radius);
		}
	private:
		double x_Pos;
		double y_Pos;
		int angle;
		int radius;
};

class Tank {
	public:
		Tank(int x, int y, int a = 0, int b = 3) {
			x_Pos = x;
			y_Pos = y;
			angle = a;
			bullets_Left = b;
			double to_Tank_Points[10] = {x-10,y-15,x+10,y-15,x+10,y+15,x-10,y+15,x-10,y-15};
			copy(to_Tank_Points,to_Tank_Points+10,tank_Points);
			copy(tank_Points,tank_Points+10,test_Points);
			Show_Tank();
		}
		bool Move_Forward(int horiz_Lines[][10], int vert_Lines[][9]) {
			double mov_x = 1*sin(angle*Pi/180);
			double mov_y = -1*cos(angle*Pi/180);
			for (int i = 0;i<9;i+=2){
				test_Points[i]+=mov_x;
				test_Points[i+1]+= mov_y;
			}
			if (Is_Collision(horiz_Lines,vert_Lines)) {
				copy(tank_Points,tank_Points+10,test_Points);
				return false;
			}
			Hide_Tank();
			Show_Tank();
			x_Pos += mov_x;
			y_Pos += mov_y;
			copy(test_Points,test_Points+10,tank_Points);
			return true;
		}
		bool Move_Backward(int horiz_Lines[][10], int vert_Lines[][9]) {
			double mov_x = -1*sin(angle*Pi/180);
			double mov_y = 1*cos(angle*Pi/180);
			for (int i = 0;i<9;i+=2){
				test_Points[i]+=mov_x;
				test_Points[i+1]+= mov_y;
			}
			if (Is_Collision(horiz_Lines,vert_Lines)) {
				copy(tank_Points,tank_Points+10,test_Points);
				return false;
			}
			Hide_Tank();
			Show_Tank();
			x_Pos += mov_x;
			y_Pos += mov_y;
			copy(test_Points,test_Points+10,tank_Points);
			return true;
		}
		bool Turn_Left(int horiz_Lines[][10], int vert_Lines[][9]) {
			Get_Points(x_Pos,y_Pos,angle-2);
			if (Is_Collision(horiz_Lines,vert_Lines)) {
				copy(tank_Points,tank_Points+10,test_Points);
				return false;
			}
			Hide_Tank();
			Show_Tank();
			copy(test_Points,test_Points+10,tank_Points);
			angle-=2;
			return true;
		}
		bool Turn_Right(int horiz_Lines[][10], int vert_Lines[][9]) {
			Get_Points(x_Pos,y_Pos,angle+2);
			if (Is_Collision(horiz_Lines,vert_Lines)) {
				copy(tank_Points,tank_Points+10,test_Points);
				return false;
			}
			Hide_Tank();
			Show_Tank();
			copy(test_Points,test_Points+10,tank_Points);
			angle+=2;
			return true;
		}
		void Get_Points(double x,double y,int theta) {
			for (int i = 0; i< 9; i+=2) {
				test_Points[i] = x+pow(-1,(i+6)/4)*18*cos(pow(-1,1+i/2)*theta*Pi/180-1);
				test_Points[i+1] = y+pow(-1,i/4)*18*sin(pow(-1,1+i/2)*theta*Pi/180-1);
			}
		}
		bool Is_Collision(int horiz_Lines[][10], int vert_Lines[][9]) {
			for(int i = 0; i < 9; i+=2) {
				if ((int(test_Points[i]) % (getmaxx()/9)<=2 || int(test_Points[i]) % (getmaxx()/9)>=getmaxx()/9-2) && vert_Lines[(1+int(test_Points[i])/(getmaxx()/18))/2][int(test_Points[i+1])/(getmaxy()/9)] == 1) {
					return true;
				}
				if ((int(test_Points[i+1]) % (getmaxy()/9)<=2 ||int(test_Points[i+1]) % (getmaxy()/9)>=getmaxy()/9-2) && horiz_Lines[(int(test_Points[i])/(getmaxx()/9))][(1+int(test_Points[i+1])/(getmaxy()/18))/2] == 1) {
					return true;
				}
			}
			return false;
		}
		void Shoot(vector<Bullet> &list) {
			if (bullets_Left == 0) {
				return;
			}
			Bullet B1 = Bullet(x_Pos+15*sin(Pi*angle/180),y_Pos-15*cos(Pi*angle/180),angle);
			list.push_back(B1);
			bullets_Left--;
			return;
		}
		void Show_Tank() {
			setfillstyle(SOLID_FILL,LIGHTGREEN);
			setcolor(LIGHTGREEN);
			int points[8];
			copy(test_Points,test_Points+8,points);
			fillpoly(4,points);
			//line(0,0,5,5);
		}
		void Hide_Tank() {
			setfillstyle(SOLID_FILL,BLACK);
			setcolor(BLACK);
			int points[8];
			copy(tank_Points,tank_Points+8,points);
			fillpoly(4,points);
			//line(0,0,5,5);
		}
	private:
		int bullets_Left;
		double x_Pos;
		double y_Pos;
		int angle;
		double tank_Points[10];
		double test_Points[10];
};


int main () {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	int horiz_Lines[9][10];
	int vert_Lines[10][9];
	int num;
	char inpt;
	int x1;
	int x2;
	int y1;
	int y2;
	clock_t time;
	vector<Bullet> bullet_List;
	while (!kbhit()) {
		num = rand() % 9;
	}
	getch();
	Make_Grid(horiz_Lines,vert_Lines);
	Draw_Grid(horiz_Lines,vert_Lines);
	x1 = rand() % 9;
	y1 = rand() % 9;
	Tank T1 = Tank((x1+.5)*getmaxx()/9,(y1+.5)*getmaxy()/9);
	while(1) {
		//Pause(5);
		time = clock();
		for (int i = 0; i < bullet_List.size(); i++) {
			bullet_List.at(i).Move(horiz_Lines,vert_Lines);
		}
		if(1) {
			if (kbhit()) {
				inpt = getch();
			}
			if (GetKeyState(VK_UP) < 0) {
				T1.Move_Forward(horiz_Lines,vert_Lines);
			}
			if (GetKeyState(VK_DOWN) < 0) {
				T1.Move_Backward(horiz_Lines,vert_Lines);
			}
			if (GetKeyState(VK_LEFT) < 0) {
				T1.Turn_Left(horiz_Lines,vert_Lines);
			}
			if (GetKeyState(VK_RIGHT) < 0) {
				T1.Turn_Right(horiz_Lines,vert_Lines);
			}
			if (inpt == 'm') {
				T1.Shoot(bullet_List);
				cout << "shot \n";
				inpt = 'n';
			}
		}
		while (time+5 >= clock()) {
		}
	}
	
	getch();
	closegraph();
	return 0;
}
