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
const double PI = 3.1415926;
const double THETA_CHANGE = PI/100;
double origin_x;
double origin_y;
int center_x;
int center_y;
int center_y2;
vector<double> p;
vector<double> q;
vector<double> r;
double s;
double theta_h;
double theta_r;


void Draw_Zoom(int color = BLACK, int color2 = BLACK) {
	setfillstyle(SOLID_FILL,color);
	setcolor(WHITE);
	center_x = getmaxx()/60*59;
	center_y = getmaxy()/40*5;
	bar(getmaxx()/60*59-10,getmaxy()/40*5-10,getmaxx()/60*59+10,getmaxy()/40*5+10);
	setfillstyle(SOLID_FILL,color2);
	bar(getmaxx()/60*59-10,getmaxy()/40*5+50,getmaxx()/60*59+10,getmaxy()/40*5+70);
	line(center_x,center_y-6,center_x,center_y+6);
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			line(center_x+10*(i/2*2-1),center_y+10*(1-(i+1)/2%2*2),center_x+10*((i+1)/2%2*2-1),center_y+10*(1-(i+2)/2%2*2));
		}
		line(center_x+6,center_y,center_x-6,center_y);
	center_y +=60;
	}
	center_y2 = center_y-60;
	center_y -=120;
}

bool Is_In_Plus() {
	if (mousex() > center_x-10 && mousex() < center_x+10 && mousey() > center_y-10 && mousey() < center_y+10) {
		return true;
	}
	return false;
}

bool Is_In_Minus() {
	if (mousex() > center_x-10 && mousex() < center_x+10 && mousey() > center_y2-10 && mousey() < center_y2+10) {
		return true;
	}
	return false;
}

void Move_Origin(double dx, double dy) {
	origin_x += dx;
	origin_y += dy;
}

void Calc_Vecs() {
	p[0] = s*(-cos(theta_h+PI/2));
	p[1] = s*(-theta_r*sin(theta_h+PI/2));
	q[0] = s*cos(-theta_h);
	q[1] = -theta_r*sin(-theta_h)*s;
	r[0] = 0;
	r[1] = s/(theta_r*theta_r+1);
}

class object {
	public:
		object(int p_length=1, int q_length=1, int r_length=1) {
			int temp_p = ((mousex()-origin_x)*q[1]-(mousey()-origin_y)*q[0]*1.0)/(p[0]*q[1]-p[1]*q[0]);
			int temp_q = ((mousex()-origin_x)*p[1]-(mousey()-origin_y)*p[0]*1.0)/(q[0]*p[1]-q[1]*p[0]);
			int temp_r = 0;
			if (temp_q < 0) {
				temp_q--;
			}
			if (temp_p < 0) {
				temp_p--;
			}
			if (temp_p == 0) {
				temp_p = ((mousex()-origin_x)*q[1]-(mousey()-origin_y)*q[0]*1.0)/(p[0]*q[1]-p[1]*q[0])-.99;
			}
			if (temp_q == 0) {
				temp_q = ((mousex()-origin_x)*p[1]-(mousey()-origin_y)*p[0]*1.0)/(q[0]*p[1]-q[1]*p[0])-.99;
			}
			cout << temp_p << " " << temp_q << endl;
			pqr_points.push_back(temp_p);
			pqr_points.push_back(temp_q);
			pqr_points.push_back(temp_r);
			pqr_lengths.push_back(p_length);
			pqr_lengths.push_back(q_length);
			pqr_lengths.push_back(r_length);
		}
		void Draw_Object() {
			setcolor(WHITE);
			setfillstyle(SOLID_FILL,GREEN);
			int points[8];
			points[0] = 0;
			points[1] = 0;
			points[2] = 20;
			points[3] = 20;
			points[4] = 0;
			points[5] = 20;
			//fillpoly(3,points);
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					line(origin_x+p[0]*pqr_points[0]+q[0]*(j*pqr_lengths[1]+pqr_points[1])+r[0]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*pqr_points[0]+q[1]*(j*pqr_lengths[1]+pqr_points[1])+r[1]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_x+p[0]*(pqr_lengths[0]+pqr_points[0])+q[0]*(j*pqr_lengths[1]+pqr_points[1])+r[0]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*(pqr_lengths[0]+pqr_points[0])+q[1]*(j*pqr_lengths[1]+pqr_points[1])+r[1]*(i*pqr_lengths[2]+pqr_points[2]));
					line(origin_x+p[0]*(j*pqr_lengths[0]+pqr_points[0])+q[0]*(0*pqr_lengths[1]+pqr_points[1])+r[0]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*(j*pqr_lengths[0]+pqr_points[0])+q[1]*(0*pqr_lengths[1]+pqr_points[1])+r[1]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_x+p[0]*(j*pqr_lengths[0]+pqr_points[0])+q[0]*(1*pqr_lengths[1]+pqr_points[1])+r[0]*(i*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*(j*pqr_lengths[0]+pqr_points[0])+q[1]*(1*pqr_lengths[1]+pqr_points[1])+r[1]*(i*pqr_lengths[2]+pqr_points[2]));
					line(origin_x+p[0]*(i*pqr_lengths[0]+pqr_points[0])+q[0]*(j*pqr_lengths[1]+pqr_points[1])+r[0]*(0*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*(i*pqr_lengths[0]+pqr_points[0])+q[1]*(j*pqr_lengths[1]+pqr_points[1])+r[1]*(0*pqr_lengths[2]+pqr_points[2]),
						origin_x+p[0]*(i*pqr_lengths[0]+pqr_points[0])+q[0]*(j*pqr_lengths[1]+pqr_points[1])+r[0]*(1*pqr_lengths[2]+pqr_points[2]),
						origin_y+p[1]*(i*pqr_lengths[0]+pqr_points[0])+q[1]*(j*pqr_lengths[1]+pqr_points[1])+r[1]*(1*pqr_lengths[2]+pqr_points[2]));
				}
			}
			/*for (int i = 0; i < (x_points.size())/2-1; i++) {
				line(x_points.at(i),y_points.at(i),x_points.at(i+1),y_points.at(i+1));
				line(x_points.at(x_points.size()-1-i),y_points.at(x_points.size()-1-i),x_points.at(x_points.size()-2-i),y_points.at(x_points.size()-2-i));
				line(x_points.at(i),y_points.at(i),x_points.at(i+(x_points.size())/2),y_points.at(i+(x_points.size())/2));

			}
			line(x_points.at((x_points.size()-1)/2),y_points.at((x_points.size()-1)/2),x_points.at(0),y_points.at(0));
			line(x_points.at((x_points.size()-1)/2+1),y_points.at((x_points.size()-1)/2+1),x_points.at(x_points.size()-1),y_points.at(x_points.size()-1));
			line(x_points.at((x_points.size())/2-1),y_points.at((x_points.size())/2-1),x_points.at(x_points.size()-1),y_points.at(x_points.size()-1));*/
		}
	private:
		vector<double> pqr_points;
		vector<int> pqr_lengths;
		
};

//make 3D

int main() {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	double zoom = 1;
	p.push_back(0);
	p.push_back(0);
	q.push_back(0);
	q.push_back(0);
	r.push_back(0);
	r.push_back(0);
	theta_h = 0;
	theta_r = 0.5;
	s = 20;
	Calc_Vecs();
	origin_x = getmaxx()/2;
	origin_y = getmaxy()/2;
	bool has_Drawn = false;
	int init_x,fin_x,fin_y;
	int init_y;
	bool has_Dragged = false;
	Draw_Zoom();
	vector<object> thing;
	while (1){
		if (GetKeyState(VK_DOWN) < 0) {
			cleardevice();
			if (theta_r < 1) {
				theta_r+=.01;
			}
			Calc_Vecs();
			for(int i = 0; i < thing.size(); i++) {
				thing.at(i).Draw_Object();
			}
			Draw_Zoom();
		}
		if (GetKeyState(VK_UP) < 0) {
			cleardevice();
			if (theta_r > -1) {
				theta_r-=.01;
			}
			Calc_Vecs();
			for(int i = 0; i < thing.size(); i++) {
				thing.at(i).Draw_Object();
			}
			Draw_Zoom();
		}
		if (GetKeyState(VK_RIGHT) < 0) {
			cleardevice();
			theta_h += .01;
			Calc_Vecs();
			for(int i = 0; i < thing.size(); i++) {
				thing.at(i).Draw_Object();
			}
			Draw_Zoom();
		}
		if (GetKeyState(VK_LEFT) < 0) {
			cleardevice();
			theta_h -= .01;
			Calc_Vecs();
			for(int i = 0; i < thing.size(); i++) {
				thing.at(i).Draw_Object();
			}
			Draw_Zoom();
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_MOUSEMOVE);
			clearmouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_LBUTTONUP);
			has_Dragged = false;
			init_x = mousex();
			init_y = mousey();
			while (!ismouseclick(WM_LBUTTONUP)) {
				if (ismouseclick(WM_MOUSEMOVE)) {
					getmouseclick(WM_MOUSEMOVE, fin_x, fin_y);
					cleardevice();
					has_Drawn = true;
					Move_Origin(fin_x-init_x, fin_y-init_y);
					for (int i = 0; i < thing.size(); i++) {
						thing.at(i).Draw_Object();
					}
					line(0,0,5,5);
					init_x = fin_x;
					init_y = fin_y;
					has_Dragged = true;
				}
			}
			if (!has_Dragged) {
				clearmouseclick(WM_LBUTTONUP);
				if (Is_In_Plus()) {
					cleardevice();
					has_Drawn = false;
					s*=1.2;
					Calc_Vecs();
					for (int i = 0; i < thing.size(); i++) {
						thing.at(i).Draw_Object();
					}
				}
				else if (Is_In_Minus()) {
					cleardevice();
					has_Drawn = false;
					s/=1.2;
					Calc_Vecs();
					for (int i = 0; i < thing.size(); i++) {
						thing.at(i).Draw_Object();
					}
				}
				else if (theta_r != 0) {
					thing.push_back(object());
					thing.at(thing.size()-1).Draw_Object();
				}
			}
		}
		if (Is_In_Plus() && !has_Drawn) {
			Draw_Zoom(DARKGRAY,BLACK);
			has_Drawn = true;
		}
		if (Is_In_Minus() && !has_Drawn) {
			Draw_Zoom(BLACK,DARKGRAY);
			has_Drawn = true;
		}
		if (has_Drawn && !Is_In_Plus() && !Is_In_Minus()) {
			Draw_Zoom();
			has_Drawn = false;
		}
	}
	getch();
	closegraph();
	return 0;
}
