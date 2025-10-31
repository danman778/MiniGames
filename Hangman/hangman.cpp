#include<graphics.h>
#include<cmath>
#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<vector>

using namespace std;


string Inpt_Word() {
	string the_Word;
	cout << "Hangman word: ";
	cin >> the_Word;
	cout << endl;
	for (int i = 0; i < the_Word.length(); i++) {
		the_Word.at(i) = tolower(the_Word.at(i));
	}
	return the_Word;
}

char Get_Letter() {
	char the_Letter;
	cout << "Your Guess: ";
	cin >> the_Letter;
	cout << endl;
	the_Letter = tolower(the_Letter);
	return the_Letter;
}

void Show_Board(int length) {
	line(388,82,388,54);
	line(388,54,490,54);
	line(490,54,490,210);
	line(450,210,530,210);
	int letter_Length = 400/length;
	for (int i = 0; i < length; i ++) {
		line((i+.1)*letter_Length+110,350,(i+.9)*letter_Length+110,350);
	}
}

bool Check_Letter(string word,char letter) {
	if (word.find(letter) < word.length()) {
		return true;
	}
	return false;
}


bool Has_Letter(vector<char> box, char letter) {
	for (int i = 0; i < box.size(); i++) {
		if (box.at(i) == letter) {
			return true;
		}
	}
	return false;
}

void Store_Letter(char letter,vector<char>* box) {
	box->push_back(letter);
}

void Line_Disp(string word, int length, char* letter, int* the_Letters){
	int position = -1;
	int size = 7;
	int letter_Length = 400/length;
	settextstyle(DEFAULT_FONT,0,size);
	while (letter_Length < textwidth(letter)) {
		size --;
		settextstyle(DEFAULT_FONT,0,size);
	}
	int height = 350-7*size;
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(DEFAULT_FONT,0,size);
	do {
		position = word.find(*letter,position+1);
		if (position != -1) {
			*the_Letters+=1;
			outtextxy((position+.3)*letter_Length+110,height,letter);
		}
	 } while (position != -1);
}

void Err_Disp(char* letter,int mistakes) {
	int size = 5;
	settextstyle(DEFAULT_FONT,0,size);
	outtextxy(mistakes*50+1 - 50*7*(mistakes/7),50*(mistakes/7),letter);
}

void Disp_Hangman(int num_Mistakes) {
	if (num_Mistakes == 1) {
		circle(388,98,16);
	}
	if (num_Mistakes == 2) {
		line(388,114,388,160);
	}
	if (num_Mistakes == 3) {
		line(388,125,420,100);
	}
	if (num_Mistakes == 4) {
		line(388,125,356,100);
	}
	if (num_Mistakes == 5) {
		line (388,160,410,200);
	}
	if (num_Mistakes == 6) {
		line (388,160,366,200);
	}
}

int main () {
	int gd=DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	char letter;
	int mistakes = 0;
	int found_Letters = 0;
	vector<char> letter_Box;
	string word = Inpt_Word();
	system("CLS");
	int length = word.length();
	while (mistakes < 12 && found_Letters < length) {
		Show_Board(length);
		letter = Get_Letter();
		if (!Has_Letter(letter_Box,letter)) {
			if (Check_Letter(word,letter)) {
				Line_Disp(word,length,&letter,&found_Letters);
			}
			else {
				Err_Disp(&letter,mistakes);
				mistakes+=1;
				Disp_Hangman(mistakes);
			}
			Store_Letter(letter,&letter_Box);
		}
	}
	cout << "Game over" << endl;
	getch();
	closegraph();
	return 0;
}
