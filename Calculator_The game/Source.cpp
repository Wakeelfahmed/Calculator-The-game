#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h> // for COORD
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()
#include <algorithm> // for sort(),unique() etc
#include <vector>    // for vector
#include "C:\SDL2-devel-2.26.1-VC\include\SDL.h"		//for SDL GUI
#include "C:\SDL2-devel-2.26.1-VC\include\SDL_ttf.h"	//for SDL GUI Font
#include "C:\SDL2-devel-2.26.1-VC\include\SDL2_gfxPrimitives.h"	//for Advanced SDL GUI
#include<string>
int Transparency = 120;
#define Width 405
#define Height 571
SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/*width*/, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
TTF_Font* font;
using namespace std;
struct Size {
	int height;
	int width;
	Size() : height(0), width(0) {}
	Size(int h, int w) : height(h), width(w) {}
};
class Text_Box {
protected:
	string text_for_Box{};
	COORD Position{};
	SDL_Surface* buttonTextSurface{};
	SDL_Texture* buttonTextTexture{};
	SDL_Color Box_Color;
	Size Box_Size;
public:
	static double scale;
	static int Rounding_Radius;
	SDL_Rect Box;
	void set_Box_Text_Char(char Text, int Font_Size, SDL_Color Text_Color, int style) {
		if (buttonTextSurface)
			SDL_FreeSurface(buttonTextSurface);
		if (buttonTextTexture)
			SDL_DestroyTexture(buttonTextTexture);
		text_for_Box = "";
		text_for_Box = Text;
		TTF_SetFontSize(font, Font_Size);
		TTF_SetFontStyle(font, style);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		buttonTextSurface = TTF_RenderText_Blended(font, text_for_Box.c_str(), Text_Color); //text Color
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		buttonTextTexture = SDL_CreateTextureFromSurface(renderer, buttonTextSurface);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}
	void set_Box_Text(const char* Text, int Font_Size, SDL_Color Text_Color, int style) {
		if (buttonTextSurface)
			SDL_FreeSurface(buttonTextSurface);
		if (buttonTextTexture)
			SDL_DestroyTexture(buttonTextTexture);
		text_for_Box = Text;
		TTF_SetFontSize(font, Font_Size);
		TTF_SetFontStyle(font, style);
		buttonTextSurface = TTF_RenderText_Blended(font, text_for_Box.c_str(), Text_Color); //text Color
		buttonTextTexture = SDL_CreateTextureFromSurface(renderer, buttonTextSurface);
	}
	void set_Text_Box(const char* Text, int Font_Size, SDL_Color Text_Color, COORD Position, Size Box_Size, SDL_Color Box_Color, bool BOLD) {
		this->Position = Position;
		this->Box_Size = Box_Size;		Box = { Position.X, Position.Y, Box_Size.height, Box_Size.width };
		this->Box_Color = Box_Color;
		set_Box_Text(Text, Font_Size, Text_Color, BOLD);
	}
	void set_Box_Color(SDL_Color Box_Color1) { Box_Color = Box_Color1; }
	void set_Box_Size(Size New_Size) { Box_Size = New_Size; }
	void Display_Text_Box(SDL_Color newcolor, bool usenewcolor_instead_boxcolor) const {
		if (usenewcolor_instead_boxcolor)
			roundedBoxRGBA(renderer, Box.x, Box.y, Box.x + Box.w, Box.y + Box.h, Rounding_Radius, newcolor.r, newcolor.g, newcolor.b, 255);
		else
			roundedBoxRGBA(renderer, Box.x, Box.y, Box.x + Box.w, Box.y + Box.h, Rounding_Radius, Box_Color.r, Box_Color.g, Box_Color.b, 255);
		//scale = .65;//1.5
		int w, h;
		SDL_QueryTexture(buttonTextTexture, nullptr, nullptr, &w, &h);
		double x, y;
		x = Box.x + (Box.w - double(w) * scale) / 2;
		y = Box.y + (Box.h - double(h) * scale) / 2;
		SDL_Rect dst;
		dst = { int(x), int(y), int(w * scale),int(h * scale) };
		SDL_RenderCopy(renderer, buttonTextTexture, nullptr, &dst);
	}
	string get_text_for_Box() const { return text_for_Box; }
	SDL_Rect get_Main_Box() const { return Box; }
	SDL_Color get_Box_Color() const { return Box_Color; }
	Size get_Box_Size() const { return Box_Size; }
	COORD get_Box_Position() const { return Position; }
	SDL_Surface* get_buttonTextSurface() const { return buttonTextSurface; }
	SDL_Texture* get_buttonTextTexture() const { return buttonTextTexture; }
	~Text_Box() {
		//SDL_DestroyTexture(buttonTextTexture);
		//SDL_FreeSurface(buttonTextSurface);
		//cout << "Called Text des\n";
	}
};
double Text_Box::scale = 0.65;
int Text_Box::Rounding_Radius = 20;
class Button {
protected:
	Text_Box Main_Text_Box;
	SDL_Rect Shadow_box;	bool Button_Pushed;		bool Button_Hovered;	int Shadow_offset;
public:
	Button() : Shadow_box({ 0,0,0,0 }), Button_Pushed(0), Button_Hovered(0), Shadow_offset(5) {}
	void Set_Button(const char* Alphabet, SDL_Color Text_Color, COORD Position, Size Button_Size, int Font_Size, SDL_Color Box_Color, bool BOLD) {
		Main_Text_Box.set_Text_Box(Alphabet, Font_Size, Text_Color, Position, Button_Size, Box_Color, BOLD);
		Shadow_box = { Position.X + Shadow_offset, Position.Y + Shadow_offset, Button_Size.height, Button_Size.width };
	}
	void set_char_of_button(char Alphabet) {
		//char ch = &Alphabet;
		Main_Text_Box.set_Box_Text_Char(Alphabet, 100, { 0, 0, 255 }, 1);
	}
	void set_Text_of_button(const char* Alphabet, SDL_Color Font_Color, bool BOLD) {
		Main_Text_Box.set_Box_Text(Alphabet, 100, Font_Color, BOLD);
	}
	void set_Button_Color(SDL_Color newColor) { Main_Text_Box.set_Box_Color(newColor); }
	void set_Button_Size(Size Button_Size) { this->Main_Text_Box.set_Box_Size(Button_Size); }
	void set_Button_Pushed(bool Button_pushed) { this->Button_Pushed = Button_pushed; }
	void set_Button_Hovered(bool Button_hovered) { this->Button_Hovered = Button_hovered; }
	bool Check_if_Mouse_in_Button_Area(int x, int y) const {
		return (x >= Main_Text_Box.get_Box_Position().X
			&& x < Main_Text_Box.get_Box_Position().X + Main_Text_Box.get_Box_Size().height
			&& y >= Main_Text_Box.get_Box_Position().Y
			&& y < Main_Text_Box.get_Box_Position().Y + Main_Text_Box.get_Box_Size().width);
	}
	bool operator==(Button Button2) {
		return (Main_Text_Box.get_Box_Position().Y == Button2.Main_Text_Box.get_Box_Position().Y && Main_Text_Box.get_Box_Position().X == Button2.Main_Text_Box.get_Box_Position().X);
	}
	void Diplay_Shadow() const {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		if (Button_Pushed)//inner shadow
			roundedBoxRGBA(renderer, Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y, Shadow_box.x + Main_Text_Box.get_Box_Size().height, Shadow_box.y + Main_Text_Box.get_Box_Size().width, 20, Main_Text_Box.get_Box_Color().r * (0.55), Main_Text_Box.get_Box_Color().g * (0.55), Main_Text_Box.get_Box_Color().b * (0.55), Transparency + 30);
		else
			roundedBoxRGBA(renderer, Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y, Shadow_box.x + Main_Text_Box.get_Box_Size().height, Shadow_box.y + Main_Text_Box.get_Box_Size().width, 20, 75, 75, 75, Transparency);
	}
	void Display_Button(bool Makes_a_Word) {
		if (Button_Pushed) {
			Main_Text_Box.Box =
			{ Main_Text_Box.get_Box_Position().X + 5, Main_Text_Box.get_Box_Position().Y + 5, Main_Text_Box.get_Box_Size().height - Shadow_offset, Main_Text_Box.get_Box_Size().width - Shadow_offset };
			Shadow_box.x = Main_Text_Box.get_Box_Position().X;
			Shadow_box.y = Main_Text_Box.get_Box_Position().Y;
		}
		else
		{
			Main_Text_Box.Box = { Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y , Main_Text_Box.get_Box_Size().height , Main_Text_Box.get_Box_Size().width };
			Shadow_box.x = Main_Text_Box.get_Box_Position().X + Shadow_offset;
			Shadow_box.y = Main_Text_Box.get_Box_Position().Y + Shadow_offset;
		}
		Diplay_Shadow();
		if (Button_Hovered)
			roundedBoxRGBA(renderer, Main_Text_Box.get_Main_Box().x, Main_Text_Box.get_Main_Box().y, Main_Text_Box.get_Main_Box().x + Main_Text_Box.get_Main_Box().w, Main_Text_Box.get_Main_Box().y + Main_Text_Box.get_Main_Box().h, 20, Main_Text_Box.get_Box_Color().r * 0.80, Main_Text_Box.get_Box_Color().g * 0.80, Main_Text_Box.get_Box_Color().b * 0.80, 255);
		else
			roundedBoxRGBA(renderer, Main_Text_Box.get_Main_Box().x, Main_Text_Box.get_Main_Box().y, Main_Text_Box.get_Main_Box().x + Main_Text_Box.get_Main_Box().w, Main_Text_Box.get_Main_Box().y + Main_Text_Box.get_Main_Box().h, 20, Main_Text_Box.get_Box_Color().r, Main_Text_Box.get_Box_Color().g, Main_Text_Box.get_Box_Color().b, 255);
		//if (!Button_Pushed)
			//filledCircleRGBA(renderer, (Main_Text_Box.get_Box_Position().X + 50), Main_Text_Box.get_Box_Position().Y + 50, 43, 0, 255, 0, 255);

		int w, h;
		SDL_QueryTexture(Main_Text_Box.get_buttonTextTexture(), nullptr, nullptr, &w, &h);
		double x, y;
		x = Main_Text_Box.get_Main_Box().x + (Main_Text_Box.get_Main_Box().w - double(w) * Main_Text_Box.scale) / 2;
		y = Main_Text_Box.get_Main_Box().y + (Main_Text_Box.get_Main_Box().h - double(h) * Main_Text_Box.scale) / 2;
		SDL_Rect dst;
		dst = { int(x), int(y), int(w * Main_Text_Box.scale),int(h * Main_Text_Box.scale) };
		SDL_RenderCopy(renderer, Main_Text_Box.get_buttonTextTexture(), nullptr, &dst);
	}
	void Display_Text_Button() {
		if (Button_Pushed) {
			Main_Text_Box.Box =
			{ Main_Text_Box.get_Box_Position().X + 5, Main_Text_Box.get_Box_Position().Y + 5, Main_Text_Box.get_Box_Size().height - Shadow_offset, Main_Text_Box.get_Box_Size().width - Shadow_offset };
			Shadow_box.x = Main_Text_Box.get_Box_Position().X;
			Shadow_box.y = Main_Text_Box.get_Box_Position().Y;
		}
		else
		{
			Main_Text_Box.Box = { Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y , Main_Text_Box.get_Box_Size().height , Main_Text_Box.get_Box_Size().width };
			Shadow_box.x = Main_Text_Box.get_Box_Position().X + Shadow_offset;
			Shadow_box.y = Main_Text_Box.get_Box_Position().Y + Shadow_offset;
		}
		SDL_Color temp = Main_Text_Box.get_Box_Color();
		Diplay_Shadow();
		if (Button_Hovered) {
			temp.r = temp.r * 0.85;
			temp.g = temp.g * 0.85;
			temp.b = temp.b * 0.85;
			temp.a = 255;
			Main_Text_Box.Display_Text_Box(temp, 1);
			return;
		}
		Main_Text_Box.Display_Text_Box({ 0 }, 0);
	}

	COORD get_Position() const { return Main_Text_Box.get_Box_Position(); }
	bool get_Button_Pushed() const { return Button_Pushed; }
	bool get_Button_Hovered() const { return Button_Hovered; }
	Size get_Button_Size() const { return Main_Text_Box.get_Box_Size(); }
	char get_char_of_button() const { return Main_Text_Box.get_text_for_Box().front(); }
	string get_text_of_button() const { return Main_Text_Box.get_text_for_Box(); }
	Text_Box get_Main_Text_Box() const { return Main_Text_Box; }
};
Text_Box Current_Number_Board, Score_Board, Moves_Board;
class Players
{
protected:
	char Player_Name[50] = "";			int High_score{};		bool isActive{ false };
	int No_of_Player_Profiles{};
public:
	int get_high_score() const { return High_score; }
	void update_high_Score(int new_high_score) { High_score = High_score + (new_high_score - High_score); }
	char* get_Player_Name() { return Player_Name; }
	bool get_IsActive_Status()const { return isActive; }

};
#define Num_of_Buttons 7
class Board {
	Button Alphabets[Num_of_Buttons]; //using 1D array as it faster than 2D
	int level;
	int Starting_Number, Current_number, Final_Number, Moves;
	bool Operator_Available[5]{ 0 };
	vector<int> solution; // In solution i will append 1 for subtraction ,2 for addition, 3(*),4(droping digit) and 5 for append digit
public:
	Board() : Starting_Number(0), Current_number(0), Final_Number(0), Moves(0), level(1) {}
	void Set_Board(string Set_Board_Letters) {
		Set_Board_Letters = "ATEHHDSEVTMFWLIA";		short intial_Position = 220;
		for (short i = 0; i < Num_of_Buttons; i++) {
			string temp(1, Set_Board_Letters[i]);
			Alphabets[i].Set_Button(temp.c_str(), { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + intial_Position)) }, { 100,100 }, 100, { 0, 0, 0, 255 }, 0);
		}
		short i = 0;
		SDL_Color Buttons_Color = { 19 ,19 ,19 };
		/*0*/Alphabets[i].Set_Button("-", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*1*/Alphabets[i].Set_Button("+", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*2*/Alphabets[i].Set_Button("x", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*3*/Alphabets[i].Set_Button("<<", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 251, 153, 2, 255 }, 0);		i++;
		/*4*/Alphabets[i].Set_Button(">>", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 251, 153, 2, 255 }, 0);		i++;
		/*5*/Alphabets[i].Set_Button("Hint", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 46, 228, 52, 255 }, 0);		i++;
		/*6*/Alphabets[i].Set_Button("CLR", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 255,0,0, 255 }, 0);
		Initialize_Level_Values();
	}
	void Check_for_Hovering(int x, int y) {
		for (short i = 0; i < Num_of_Buttons; i++)
			Alphabets[i].set_Button_Hovered(Alphabets[i].Check_if_Mouse_in_Button_Area(x, y));
	}
	void Reset_Pressed_Letters() {
		Display_Board();
	}
	void Reset_game() {
		Reset_Pressed_Letters();
	}
	void Initialize_Level_Values() {
		Current_number = rand() % 11; // Assigning random number to starting variable
		Starting_Number = Current_number;  //Saving the starting number for level restart/fail
		int final_number = Current_number;
		int Sub = rand() % 2 + 1;  // value which will use for subtraction
		int Add = rand() % 11 + 1; // value which will use for addition
		int temp1 = rand() % 4 + 3;   // Getting random movements to play game
		Moves = temp1;
		int finish_number_solution = Current_number;

		string tostring = "-" + to_string(Sub);
		Alphabets[0].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		tostring = "+" + to_string(Add);
		Alphabets[1].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		if (level < 6) // for level 1-5
		{
			Operator_Available[0] = 1;
			Operator_Available[1] = 1;
			if (temp1 > 3)
			{
				temp1 = 3;
				Moves = temp1;
			}
			while (temp1 > 0)
			{
				// this loop will generating target number which user has to calculate
				int applying_rules = rand() % 2;
				if (applying_rules == 1)
				{
					solution.push_back(1);
					final_number -= Sub; // subtracting random generated number

				}
				else if (applying_rules == 0)
				{
					solution.push_back(2);
					final_number += Add; // adding random generated number
				}
				temp1--;
			}
			Final_Number = final_number;
		}
		int Mul = rand() % 5 + 2;  // value which will use for multiplication

		tostring = "x" + to_string(Mul);
		Alphabets[2].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		int Append = rand() % 10;     // value which will use for append at last
		tostring = "<<" + to_string(Append);
		Alphabets[3].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);

		for (int i = 0; i < Moves; i++)
		{
			if (solution[i] == 1)
				cout << "- ";
			else if (solution[i] == 2)
				cout << "+ ";
			else if (solution[i] == 3)
				cout << "* ";
			else if (solution[i] == 4)
				cout << "< "; // for drop digit
			else if (solution[i] == 5)
				cout << "> "; // for append digit
		}
	}
	void Game_Level() {	}
	void Display_Board() {
		for (int i = 0; i < Num_of_Buttons; i++)
			Alphabets[i].Display_Button(0);

		Display_Level();
		Display_Moves();
		Display_Final_Number();
		Display_Current_Number();
	}
	bool Check_for_Letters_input(int x, int y, bool Mousedown_or_up) {//1 for down, 0 for up
		for (int i = 0; i < Num_of_Buttons; i++)
			if (Alphabets[i].Check_if_Mouse_in_Button_Area(x, y))
			{
				if (Mousedown_or_up)
					Alphabets[i].set_Button_Pushed(1);
				else
					Alphabets[i].set_Button_Pushed(0);
				if (Alphabets[i].get_Button_Pushed()) {}
				else {	//if button released
					cout << "Operator  " << Alphabets[i].get_text_of_button() << endl;
					if (Operator_Available[i] || 1) {
						Moves--;
						string suffix = Alphabets[i].get_text_of_button().substr(1);
						if (i == 0) {
							cout << "got" << suffix << endl;
							Current_number -= stoi(suffix);
						}
						if (i == 1) {
							cout << "got" << suffix << endl;
							Current_number += stoi(suffix);
						}
						if (i == 2) {
							cout << "got" << suffix << endl;
							Current_number *= stoi(suffix);
						}
						if (i == 3) { //<<
							suffix = Alphabets[i].get_text_of_button().substr(2);
							cout << "got" << suffix << endl;
							Current_number -= stoi(suffix);
						}
						if (i == 4) { //>>
							suffix = Alphabets[i].get_text_of_button().substr(2);
							cout << "got" << suffix << endl;
							Current_number -= stoi(suffix);
						}
						if (i == 5) {
							cout << "got" << suffix << endl;
							Current_number -= stoi(suffix);
						}
						if (Current_number == Final_Number)
						{
						}
					}


				}
				return 1;
			}
		return 0;
	}
	void Display_Current_Number() const {
		TTF_CloseFont(font);
		font = TTF_OpenFont("Digital7Monoitalic.ttf", 200);//16  //max : 7332 /1000
		if (font == NULL)
			cout << "ERROR!!!\n(Arial.ttf) Font Not Found - unable to render text" << endl;
		COORD Center;
		Center.X = (Width - 370) / 2;
		Center.Y = 123;
		Current_Number_Board.set_Text_Box(to_string(Current_number).c_str(), 150, { 255,255,255,255 }, Center, { 370,100 }, { 75, 75, 75, 255 }, 0);
		Current_Number_Board.Display_Text_Box({ 0 }, 0);
		TTF_CloseFont(font);
		font = TTF_OpenFont("arial.ttf", 100);//16  //max : 7332 /1000
	}
	void Display_Level() const {
		COORD Center;
		Center.X = (Width - 150) / 2;
		Center.Y = -13;
		Score_Board.set_Text_Box(("Level " + to_string(level)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Score_Board.Display_Text_Box({ 0 }, 0);
	}
	void Display_Moves() const {
		COORD Center;
		Center.X = ((Width - 150) / 2) - 80;
		Center.Y = 55;		//Center.X -= 80;
		Moves_Board.set_Text_Box(("Moves " + to_string(Moves)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Moves_Board.Display_Text_Box({ 0 }, 0);
	}
	void Display_Final_Number() const {
		COORD Center;
		Center.X = ((Width - 150) / 2) + 80;
		Center.Y = 55; //Center.X += 80;
		Moves_Board.set_Text_Box(("Target " + to_string(Final_Number)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Moves_Board.Display_Text_Box({ 0 }, 0);
	}
	void Board_rotate() {
		char temp[4];
		for (size_t i = 0; i < 4; i++)
			temp[i] = Alphabets[i].get_char_of_button();
		Alphabets[3].set_char_of_button(Alphabets[0].get_char_of_button());
		Alphabets[0].set_char_of_button(Alphabets[12].get_char_of_button());
		Alphabets[1].set_char_of_button(Alphabets[8].get_char_of_button());
		Alphabets[2].set_char_of_button(Alphabets[4].get_char_of_button());

		Alphabets[12].set_char_of_button(Alphabets[15].get_char_of_button());
		Alphabets[8].set_char_of_button(Alphabets[14].get_char_of_button());
		Alphabets[4].set_char_of_button(Alphabets[13].get_char_of_button());

		{char temp_Inner_Sq = Alphabets[5].get_char_of_button();
		Alphabets[5].set_char_of_button(Alphabets[9].get_char_of_button());
		Alphabets[9].set_char_of_button(Alphabets[10].get_char_of_button());
		Alphabets[10].set_char_of_button(Alphabets[6].get_char_of_button());
		Alphabets[6].set_char_of_button(temp_Inner_Sq);
		}
		Alphabets[15].set_char_of_button(temp[3]);
		Alphabets[13].set_char_of_button(Alphabets[11].get_char_of_button());
		Alphabets[14].set_char_of_button(Alphabets[7].get_char_of_button());
		Alphabets[11].set_char_of_button(temp[2]);
		Alphabets[7].set_char_of_button(temp[1]);

	}
	void New_Game() {
		Reset_game();
		Set_Board("ATEHHDSEVTMFWLIA");
	}
	~Board() {}
};
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();		font = TTF_OpenFont("arial.ttf", 100);//16  //max : 7332 /1000
	if (font == NULL)
		cout << "ERROR!!!\n(Arial.ttf) Font Not Found - unable to render text" << endl;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Event event;
	Board Boggle_Game;
	srand(time(nullptr)); // function to generate random number every time rand function call
	Button Rotate_Button, Reset_Button, New_Game_Button;
	Rotate_Button.Set_Button("Rotate", { 255,255,255,255 }, { 23 + 15,507 }, { 99, 50 }, 40, { 48, 68, 193, 255 }, 0);
	Reset_Button.Set_Button("Reset", { 255,255,255,255 }, { 23 + 130,507 }, { 99, 50 }, 40, { 48, 68, 193, 255 }, 0);
	New_Game_Button.Set_Button("New Game", { 255,255,255,255 }, { 23 + 244,507 }, { 140, 50 }, 40, { 255, 128, 0, 255 }, 0);
	//Invalid_Word_Mess.set_Text_Box("Invalid Word", 40, { 255,255,255,255 }, { 470, 70 }, { 150,60 }, { 255,0,0, 255 }, 0);
	Players Game_Player;
	string Player_name;
	Boggle_Game.New_Game();
	int MouseX, MouseY;
	bool Changes_Made = 1;
	Rotate_Button.Display_Text_Button();
	Reset_Button.Display_Text_Button();
	New_Game_Button.Display_Text_Button();
	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
				//SDL_DestroyTexture(buttonTextTexture);
				//SDL_FreeSurface(buttonTextSurface);
				Boggle_Game.~Board();
				TTF_CloseFont(font);
				TTF_Quit();
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				exit(0);
				return 0;
			}
			if (event.type == SDL_MOUSEMOTION)	//Mouse is hovering
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				Boggle_Game.Check_for_Hovering(MouseX, MouseY);
				//Rotate_Button.set_Button_Hovered(Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
				//Reset_Button.set_Button_Hovered(Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
				//New_Game_Button.set_Button_Hovered(New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
				if (Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY) != Rotate_Button.get_Button_Hovered())
				{
					Changes_Made = 1;
					Rotate_Button.set_Button_Hovered(Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
					Rotate_Button.Display_Text_Button();
				}
				else if (Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY) != Reset_Button.get_Button_Hovered())
				{
					Changes_Made = 1;
					Reset_Button.set_Button_Hovered(Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
					Reset_Button.Display_Text_Button();
				}
				else if (New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY) != New_Game_Button.get_Button_Hovered())
				{
					Changes_Made = 1;
					New_Game_Button.set_Button_Hovered(New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
					New_Game_Button.Display_Text_Button();
				}
			}
			if (event.type == SDL_MOUSEBUTTONUP)	//mouse click on Button
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Boggle_Game.Check_for_Letters_input(MouseX, MouseY, 0)) {
					break;
				}
				else if (Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					Boggle_Game.Board_rotate();
					Rotate_Button.set_Button_Pushed(0);
					Rotate_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				else if (Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					Boggle_Game.Reset_game();
					Reset_Button.set_Button_Pushed(0);
					Reset_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				else if (New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					Boggle_Game.New_Game();
					New_Game_Button.set_Button_Pushed(0);
					New_Game_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {	//mouse click on Button
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Boggle_Game.Check_for_Letters_input(MouseX, MouseY, 1)) {
					break;
				}
				if (Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					Rotate_Button.set_Button_Pushed(!Rotate_Button.get_Button_Pushed());
					Rotate_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				if (Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					Reset_Button.set_Button_Pushed(!Reset_Button.get_Button_Pushed());
					Reset_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				if (New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					New_Game_Button.set_Button_Pushed(!New_Game_Button.get_Button_Pushed());
					New_Game_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 225, 190, 190, 50);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		//Reset_Button.Display_Text_Button();
		//New_Game_Button.Display_Text_Button();

		Boggle_Game.Display_Board();
		SDL_RenderPresent(renderer);
	}
}

