#include <graphics.h>
#include<cmath>

const double Pi = 3.14159265358979;

enum shpaes { SQUARE, RECTANGLE, TRAPEZOID, CIRCLE, ELLIPSE, DIAMOND, HEART
};


using namespace std;


class Coordinate {
	public:
		Coordinate() {
		}
		Coordinate (int x, int y) {
			xVal = x;
			yVal = y;
		}
		int getXVal () {
			return xVal;
		}
		int getYVal() {
			return yVal;
		}
	private:
		int xVal;
		int yVal;
};


void drawShape(int shapeID, Coordinate center, int width, int height, int color = WHITE, int fill = EMPTY_FILL, int bkgColor = BLACK) {

	setcolor(color);
	if (fill == EMPTY_FILL) {
		setfillstyle(SOLID_FILL,bkgColor);
	} else {
		setfillstyle(fill, color);
		setbkcolor(bkgColor);

	}
	
	if (shapeID == SQUARE) {
		int sideLength = min(height,width);
		bar3d(center.getXVal()-sideLength/2,center.getYVal()-sideLength/2,center.getXVal()+sideLength/2,center.getYVal()+sideLength/2,0,1);
	} else if (shapeID == RECTANGLE) {
		bar3d(center.getXVal()-width/2,center.getYVal()-height/2,center.getXVal()+width/2,center.getYVal()+height/2,0,1);
	} else if (shapeID == TRAPEZOID) {
		int farWidth = width/2;
		int nearWidth = width/3;
		height = min(height/2,nearWidth);
		int trapezoid[8];
		//sequenced xVals and yVals of points
		trapezoid[0] = center.getXVal()-farWidth;
		trapezoid[1] = center.getYVal()+height;
		trapezoid[2] = center.getXVal()-nearWidth;
		trapezoid[3] = center.getYVal()-height;
		trapezoid[4] = center.getXVal()+nearWidth;
		trapezoid[5] = center.getYVal()-height;
		trapezoid[6] = center.getXVal()+farWidth;
		trapezoid[7] = center.getYVal()+height;
		fillpoly(4,trapezoid);
	} else if (shapeID == CIRCLE) {
		int radius = min(height, width)/2;
		fillellipse(center.getXVal(), center.getYVal(), radius, radius);
	} else if (shapeID == ELLIPSE) {
		int xRadius = width/2;
		int yRadius = height/2;
		fillellipse(center.getXVal(), center.getYVal(), xRadius, yRadius);
	} else if (shapeID == DIAMOND) {
		int diamond[8];
		//sequenced xVals and yVals of points
		diamond[0] = center.getXVal();
		diamond[1] = center.getYVal()+height/2;
		diamond[2] = center.getXVal()+width/2;
		diamond[3] = center.getYVal();
		diamond[4] = center.getXVal();
		diamond[5] = center.getYVal()-height/2;
		diamond[6] = center.getXVal()-width/2;
		diamond[7] = center.getYVal();
		fillpoly(4,diamond);
	} else {
		line(0,0,100,100);
	}
}


void drawPolygon(int numSides, Coordinate center, int radius, int color = WHITE, int fill = EMPTY_FILL, int bkgColor = BLACK) {
	if (numSides < 3) {
		return;
	}
	setcolor(color);
	if (fill == EMPTY_FILL) {
		setfillstyle(SOLID_FILL,bkgColor);
	} else {
		setfillstyle(fill, color);
		setbkcolor(bkgColor);

	}
	double theta = (numSides-2)*Pi/numSides;
	double innerRadius = radius*sin(theta/2);
	double lineLength = 2*radius*cos(theta/2);
	int polygon[numSides*2];
	
	//start point on left side of bottom edge
	double currPointX = center.getXVal()-lineLength/2;
	double currPointY = center.getYVal()+innerRadius;
	//theta to positive x for line as it traces polygon
	double currTheta = 0;
	
	for (int i = 0; i < numSides; ++i) {
		//store current point
		polygon[2*i] = currPointX;
		polygon[2*i+1] = currPointY;
		
		//get new point
		currPointX += cos(currTheta)*lineLength;
		currPointY -= sin(currTheta)*lineLength;
		
		//change currTheta to trace polygon
		currTheta += Pi-theta;
	}
	
	fillpoly(numSides,polygon);
	
}

