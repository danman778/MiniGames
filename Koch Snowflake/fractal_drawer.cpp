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
	// So I'm gonna lay a coordinate axis on top of the window
	// This function takes an x value (a) on those axes and converts it to the pixel x value I want
	// I want the origin to be the center and the sides to go to about x=+-2, so the numbers are chosen accordingly through testing
	// There are better ways to do this I didn't know about (using getmaxx()//2 and getmaxx()//4 instead of the hard-coded 300 and 150), 
	// so testing values and looking at their output isn't actually necessary
	return 300+150*a;
}

int Convert_y(double a) {
	// Same idea as Convert_x. Scales differently because the window is short. I should have kept the slope the same though because this messes with angles
	return 200-100*a;
}



void Connect_Points(vector<double> x_nums, vector<double> y_nums, int color = WHITE) {
	// Takes lists containing the x and y values of each coordinate (x_nums = <1,2,3>, y_nums = <9,8,7> corresponds to the 
	// three points (1,9),(2,8),(3,7) in order) and takes in a color argument for the lines to draw (colors like BLACK and WHITE
	// are built in with the graphics library and stored as ints). 
	// This function then draws lines connecting every point
	setcolor(color);	// obvious what this does
	for(int i = 0; i < x_nums.size()-1;i++) {	
		// line(x0,y0,x1,y1) is the command here. Once the color is set that's all you have to do and it draws right.
		// The x and y nums passed in are coordinates on my grid, so I have to convert them to pixel values before actually
		// drawing the lines.
		line(Convert_x(x_nums.at(i)),Convert_y(y_nums.at(i)),Convert_x(x_nums.at(i+1)),Convert_y(y_nums.at(i+1)));
	}
}

void Set_Points(vector<double>& x_nums, vector<double>& y_nums) {
	// the fancy & in the arguments passed in lets me edit the object in memory passed in instead of copies
	// This means changes I make here to x_nums and y_nums will be reflected in main without having to return them.
	// x_nums and y_nums are the same things as from Connect_Points
	
	// Store copies and clear out the originals. 
	vector<double> temp_x = x_nums;
	vector<double> temp_y = y_nums;
	x_nums.clear();
	y_nums.clear();
	// Now build the originals back up from the copies using math I did but don't remember.
	// Basically for each pair of adjacent points I grab the first point, the point 1/3 of the way 
	// between them, the bump somehow, and then the 2/3 distance point. They're all stored in 
	// x_nums and y_nums in order so the Connect_Points function will do what I want
	for (int i = 0; i < temp_x.size()-1; i++) {
		double a = temp_x.at(i);
		double b = temp_y.at(i);
		double c = temp_x.at(i+1);
		double d = temp_y.at(i+1);
		x_nums.push_back(a);
		y_nums.push_back(b);
		x_nums.push_back((2*a+c)/3);
		y_nums.push_back((2*b+d)/3);
		x_nums.push_back((a+c)/2+(d-b)/sqrt(12));
		y_nums.push_back((b+d)/2+(a-c)/sqrt(12));
		x_nums.push_back((a+2*c)/3);
		y_nums.push_back((b+2*d)/3);
	}
	// (1,-1) is the last vertex of my triangle and it's always missed at the end, so put it in too.
	// I have to have it at both the front ant the back so that the Connect_Points function makes a complete loop
	x_nums.push_back(1);
	y_nums.push_back(-1);
}


int main() {
	// Initialize graph. These two lines casually exist at the beginning of literally all of my programs and I never do anything with them
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	// Create vectors for x and y coordinates of each point. 
	// I should have created a point class that just stored both of these at once but whatever
	vector<double> x_points;
	vector<double> y_points;
	
	// Push back the points (1,-1),(0,sqrt(3)-1),and (-1,-1) for my starting triangle. 
	// This is technically equilateral but it doesn't look equilateral because I scaled my x and y differently
	x_points.push_back(1);
	y_points.push_back(-1);
	x_points.push_back(0);
	y_points.push_back(sqrt(3)-1);
	x_points.push_back(-1);
	y_points.push_back(-1);
	x_points.push_back(1);
	y_points.push_back(-1);
	
	char q; // Useless but used in the cin so it stays
	
	// Initialize vectors for the lines I'll need to erase. It's better to do this instead of using the list I already had to erase
	// (just erasing the lines right after drawing), because it needs to calculate the new positions
	// and I don't want the screen black while it does that
	vector<double> clr_x_pts;
	vector<double> clr_y_pts;
	for(int i = 0; i < 70; i++) {	// Apparently after 70 iterations it stops. More than 5 is time-consuming and useless because of limited resolution. I should fix that
		// Prepare to erase current points
		clr_x_pts = x_points;
		clr_y_pts = y_points;
		// Draw lines between current points
		Connect_Points(x_points,y_points);
		// Calculate the next points
		Set_Points(x_points,y_points);
		delay(150);		// This delays for 150 ms but is useless because then I cin
		
		// This prompts the user for input and won't let the program continue until it gets some. 
		// This is why you have to type a char for the next iteration to happen.
		// Also cin is basically a built-in c++ function (technically from <iostream> but like that's used from day 1 in c++)
		cin >> q;		
		Connect_Points(clr_x_pts,clr_y_pts,BLACK);		// Erases the lines drawn by drawing over them in black
	}
	
	// These lines also just exist at the end of every program. They close it sometimes when it's done. I don't think they're necessary but at this point it's tradition
	getch();
	closegraph();
	
	return 0;
}
