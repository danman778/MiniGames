#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>
#include<graphics_lib.h>
#include<sstream>
using namespace std;

const double cardToRectangleRatio = .8;
const double shapeToCardRatio = .8;
const int buttonPaddingPxls = 10;
const Coordinate easySetting = Coordinate(4,4);
const Coordinate mediumSetting = Coordinate(8,6);
const Coordinate hardSetting = Coordinate(10,10);

//Strings
const char memLbl[] = "MEMORY";
const char swapLbl[] = "SWAP";
const char playLbl[] = "PLAY";
const char sizeLbl[] = "SIZE: ";
const char settingsLbl[] = "SETTINGS";
const char okLbl[] = "OK";
const char easyLbl[] = "EASY: ";
const char mediumLbl[] = "MEDIUM: ";
const char hardLbl[] = "HARD: ";
const char customLbl[] = "CUSTOM: ";
const char reccomendLbl[] = "Reccomended Ratio Around";
const char customMsg[] = "Width and height must both be positive integers with one being even!";



class Settings {
	public:
		static Settings* getInstance() {
			if (instancePtr == NULL) {
				instancePtr = new Settings();
				return instancePtr;
			} else {
				return instancePtr;
			}
		}
		void setRows(int rows) {
			this->rows = rows;
		}
		int getRows() {
			return rows;
		}
		void setCols(int cols) {
			this->cols = cols;
		}
		int getCols() {
			return cols;
		}
		int getNumColors() {
			return colors.size();
		}
		int getColor(int i) {
			return colors.at(i);
		}
		int getNumFillStyles() {
			return fillStyles.size();
		}
		int getFillStyle(int i) {
			return fillStyles.at(i);
		}
		
		void setShapes(int n) {
			if (n>0) {
				shapes.push_back(SQUARE);
			}
			if (n>1) {
				shapes.push_back(CIRCLE);
			}
			if (n > 2) {
				shapes.push_back(TRAPEZOID);
			}
			if (n>3) {
				shapes.push_back(DIAMOND);
			}
			//after the first four shapes it defaults to n-gons starting at pentagons
			//it will record the number of sides instead of the shapeID past index 3 in shapes
			for (int i = 5; i <= n; i++) {
				shapes.push_back(i);
			}
		}
		
		
	private:
		int rows;
		int cols;
		static Settings* instancePtr;
		vector<int> fillStyles;
		vector<int> colors;
		vector<int> shapes;
		Settings(){
			vector <int> styles;
			styles.push_back(EMPTY_FILL);
			styles.push_back(SOLID_FILL);
			styles.push_back(LINE_FILL);
			styles.push_back(SLASH_FILL);
			styles.push_back(XHATCH_FILL);
			this->fillStyles = styles;
			vector <int> colos;
			colos.push_back(LIGHTRED);
			colos.push_back(LIGHTBLUE);
			colos.push_back(CYAN);
			colos.push_back(LIGHTMAGENTA);
			colos.push_back(MAGENTA);
			colos.push_back(DARKGRAY);
			colos.push_back(GREEN);
			this->colors = colos;
		}
	
};

class Button {
	public:
		Button(Coordinate center, int width, int height, string text, int defaultColor = BLACK, int hoverColor = DARKGRAY, int textColor = WHITE) {
			this->center = center;
			this->text = text;
			this->height = height;
			this->width = width;
			this->defaultColor = defaultColor;
			this->hoverColor = hoverColor;
			this->textColor = textColor;
			this->hasMouseHover = false;
			checkMouseHover();
		}
		int getWidth() {
			return width;
		}
		void setWidth(int width) {
			this->width = width;
		}
		int getHeight() {
			return height;
		}
		void setHeight() {
			this->height = height;
		}
		void checkMouseHover() {
			if (center.getXVal()-width/2 <= mousex() &&
				center.getXVal()+width/2 >= mousex() &&
				center.getYVal()-height/2 <= mousey() &&
				center.getYVal()+height/2 >= mousey()) {
				if (this->hasMouseHover == false) {
					this->hasMouseHover = true;
					drawButton();
				}
			} else {
				if (this->hasMouseHover == true) {
					this->hasMouseHover = false;
					drawButton();
				}
			}
		}
		bool getMouseHover() {
			return hasMouseHover;
		}
		void drawButton() {
			setlinestyle(SOLID_LINE,1,NORM_WIDTH);
			int bkColor;
			if (hasMouseHover) {
				bkColor = hoverColor;
			} else {
				bkColor = defaultColor;
			}
			drawShape(RECTANGLE,center,width,height,textColor, EMPTY_FILL, bkColor);
			settextjustify(CENTER_TEXT, CENTER_TEXT);
			settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
			setcolor(textColor);
			setbkcolor(bkColor);
			outtextxy(center.getXVal(),center.getYVal()+buttonPaddingPxls/2,const_cast<char*>(text.c_str()));
		}
		string getTxt() {
			return text;	
		}
		
	private:
		Coordinate center;
		bool hasMouseHover;
		int height;
		int width;
		string text;
		int defaultColor;
		int hoverColor;
		int textColor;
};

class InputTextField {
	private:
		string CurrText;
		Coordinate center;
		int width;
		int height;
		bool hasFocus;
		
	public:
		InputTextField(Coordinate center, int width, int height) {
			this->center = center;
			this->CurrText = "";
			this->hasFocus = false;
			this->height = height;
			this->width = width;
		}
		
		void checkFocus() {
			
		}
};

Settings* Settings::instancePtr = NULL;

bool isEven(int num);

void drawMainScreen();
Button drawButton(Coordinate center, string* text);
void drawNewGame();
bool drawCard(vector<vector<int> > board,vector<int> shapeByID, Coordinate location, boolean faceUp);
bool highlightCard(vector<vector<int> > board, Coordinate location);
Coordinate getCardCenter(Coordinate location);
string getBoardSizeTxt(int rows, int cols);

void runSettingsActivity();
void runPlayActivity();
void runCustomInputFragment();

Coordinate getMouseCard();

bool isValidDims(int rows, int cols);
vector<vector<int> > generateBoard();
vector<int> generateShapes(int numUniqueCards);
bool isMatch(vector<vector<int> > board, Coordinate card1, Coordinate card2);



int main () {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	Settings* settings = Settings::getInstance();
	//default 6x8 board
	settings->setRows(6);
	settings->setCols(8);

	setlinestyle(SOLID_LINE,1,THICK_WIDTH);
	drawMainScreen();
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
	int buttonWidth = max(textwidth(const_cast<char*>(playLbl)),textwidth(const_cast<char*>(settingsLbl))) + buttonPaddingPxls;
	int buttonHeight = max(textheight(const_cast<char*>(playLbl)),textheight(const_cast<char*>(settingsLbl))) + buttonPaddingPxls;
	Button startButton = Button(Coordinate(getmaxx()/2,4.5*getmaxy()/6),buttonWidth,buttonHeight,playLbl);
	Button settingsButton = Button(Coordinate(getmaxx()/2,5*getmaxy()/6),buttonWidth,buttonHeight,settingsLbl);
	startButton.drawButton();
	settingsButton.drawButton();
	vector<Button> homeButtons;
	homeButtons.push_back(startButton);
	homeButtons.push_back(settingsButton);
	bool hasClickedMenu = false;
	while (!hasClickedMenu) {
		for (int i = 0; i < homeButtons.size(); ++i) {
			homeButtons.at(i).checkMouseHover();
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);
			for (int i = 0; i < homeButtons.size(); ++i) {
				Button button = homeButtons.at(i);
				if (button.getMouseHover()) {
					if (button.getTxt() == settingsLbl ) {
						runSettingsActivity();
						drawMainScreen();
						for (int j = 0; j < homeButtons.size(); ++j) {
							Button currButton = homeButtons.at(j);
							currButton.drawButton();
						}
					} else if (button.getTxt() == playLbl) {
						cout << "Play button pressed" << endl;
					} 
				}
			}
		}
	}
	
	//Coordinate center = Coordinate(200,200);
	setlinestyle(SOLID_LINE,1,THICK_WIDTH*1.8);
	//drawShape(RECTANGLE,center,100,100,WHITE,SOLID_FILL);
	//drawPolygon(8,center,30,GREEN,EMPTY_FILL,WHITE);
	
	
	
	getch();
	closegraph();
	return 0;
}

bool isEven(int num)  {
	if (num & 1 == 0) {
		return true;
	}
	return false;
}

string getBoardSizeTxt(int rows, int cols) {
			ostringstream tempStr1,tempStr2;
			tempStr1 << rows;
			tempStr2 << cols;
			return tempStr1.str() + " X " + tempStr2.str();
		}

void drawMainScreen() {
	setbkcolor(BLACK);
	Settings* settings = Settings::getInstance();
	cleardevice();
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,7);
	setcolor(YELLOW);
	outtextxy(getmaxx()/2,getmaxy()/5,const_cast<char*>(memLbl));
	settextstyle(COMPLEX_FONT,HORIZ_DIR,10);
	setcolor(CYAN);
	outtextxy(getmaxx()/2,2*getmaxy()/5,const_cast<char*>(swapLbl));
	setcolor(GREEN);
	setlinestyle(SOLID_LINE,1,THICK_WIDTH);
	arc(7*getmaxx()/8,3*getmaxy()/11,-140,80,50);
	line(521,190,520,160);
	line(520,160,550,161);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,3);
	setcolor(WHITE);
	outtextxy(getmaxx()/2,4*getmaxy()/6,const_cast<char*>((sizeLbl + getBoardSizeTxt(settings->getCols(),settings->getRows())).c_str()));
}

void runSettingsActivity() {
	setbkcolor(BLACK);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,3);
	Settings* settings = Settings::getInstance();
	cleardevice();
	bool hasExited = false;
	string easyButtonText = const_cast<char*>(easyLbl);
	easyButtonText += " " + getBoardSizeTxt(const_cast<Coordinate*>(&easySetting)->getXVal(),const_cast<Coordinate*>(&easySetting)->getYVal());
	string mediumButtonText = const_cast<char*>(mediumLbl);
	mediumButtonText += " " + getBoardSizeTxt(const_cast<Coordinate*>(&mediumSetting)->getXVal(),const_cast<Coordinate*>(&mediumSetting)->getYVal());
	string hardButtonText = const_cast<char*>(hardLbl);
	hardButtonText += " " + getBoardSizeTxt(const_cast<Coordinate*>(&hardSetting)->getXVal(),const_cast<Coordinate*>(&hardSetting)->getYVal());
	int buttonWidth = max(textwidth(const_cast<char*>(easyButtonText.c_str())),textwidth(const_cast<char*>(mediumButtonText.c_str())));
	buttonWidth = max(buttonWidth,textwidth(const_cast<char*>(hardButtonText.c_str()))) + buttonPaddingPxls;
	int buttonHeight = max(textheight(const_cast<char*>(easyButtonText.c_str())),textheight(const_cast<char*>(mediumButtonText.c_str())));
	buttonHeight = max(buttonHeight,textheight(const_cast<char*>(easyButtonText.c_str()))) + buttonPaddingPxls;
	Button okButton = Button(Coordinate(getmaxx()/2,5*getmaxy()/6),buttonWidth,buttonHeight,okLbl);
	Button easyButton = Button(Coordinate(getmaxx()/2,getmaxy()/6),buttonWidth,buttonHeight,easyButtonText);
	Button mediumButton = Button(Coordinate(getmaxx()/2,2*getmaxy()/6),buttonWidth,buttonHeight,mediumButtonText);
	Button hardButton = Button(Coordinate(getmaxx()/2,3*getmaxy()/6),buttonWidth,buttonHeight,hardButtonText);
	vector<Button> settingsButtons;
	settingsButtons.push_back(okButton);
	settingsButtons.push_back(easyButton);
	settingsButtons.push_back(mediumButton);
	settingsButtons.push_back(hardButton);
	for (int j = 0; j < settingsButtons.size(); ++j) {
		Button currButton = settingsButtons.at(j);
		currButton.drawButton();
	}
	while (!hasExited) {
		for (int i = 0; i < settingsButtons.size(); ++i) {
			settingsButtons.at(i).checkMouseHover();
		}
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);
			for (int i = 0; i < settingsButtons.size(); ++i) {
				Button button = settingsButtons.at(i);
				if (button.getMouseHover()) {
					if (button.getTxt() == okLbl ) {
						return;
					} else if (button.getTxt() == easyButtonText) {
						settings->setRows(const_cast<Coordinate*>(&easySetting)->getYVal());
						settings->setCols(const_cast<Coordinate*>(&easySetting)->getXVal());
						return;
					} else if (button.getTxt() == mediumButtonText) {
						settings->setRows(const_cast<Coordinate*>(&mediumSetting)->getYVal());
						settings->setCols(const_cast<Coordinate*>(&mediumSetting)->getXVal());
						return;
					} else if (button.getTxt() == hardButtonText) {
						settings->setRows(const_cast<Coordinate*>(&hardSetting)->getYVal());
						settings->setCols(const_cast<Coordinate*>(&hardSetting)->getXVal());
						return;
					}
				}
			}
		}
	}
	
}

void runCustomInputFragment() {
	drawShape(RECTANGLE,Coordinate(getmaxx()/2,getmaxy()/2),getmaxx()/2,getmaxy()/2,LIGHTGRAY);
	
	
	
	
}


