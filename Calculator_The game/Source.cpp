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
#define Width 450
#define Height 571
#define Num_of_Buttons 571
SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450/*width*/, 571, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
	void set_Text_of_button(const char* Alphabet) {
		//char ch = &Alphabet;
		Main_Text_Box.set_Box_Text(Alphabet, 100, { 0, 0, 255 }, 1);
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
Text_Box Invalid_Word_Mess, Score_Board, Current_Word_Board;
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
class Board {
	Button Alphabets[16]; //using 1D array as it faster than 2D
	int Score;
	string Current_Word;
	//bool Word_Made;
	int level = 1;
	int Current_number, Final_Number, Moves;
	bool Operator_Available[5];
	vector<int> solution; // In solution i will append 1 for subtraction ,2 for addition, 3(*),4(droping digit) and 5 for append digit
public:
	Board() : Score(0), Current_Word(""), Current_number(0), Final_Number(0), Moves(0) {}
	void Set_Board(string Set_Board_Letters) {
		Set_Board_Letters = "ATEHHDSEVTMFWLIA";
		for (short i = 0; i < 16; i++) {
			string temp(1, Set_Board_Letters[i]);
			Alphabets[i].Set_Button(temp.c_str(), { 0, 54, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 0, 0, 0, 255 }, 0);
		}
		short i = 0;
		Alphabets[i].Set_Button("-", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button("+", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button("*", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button("<<", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button(">>", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button("Hint", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 204, 0, 204, 255 }, 0);
		i++;
		Alphabets[i].Set_Button("CLR", { 0, 0, 255 }, { short(10 + (i % 4) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + 49)) }, { 100,100 }, 100, { 255,0,0, 255 }, 0);
		Initialize_Level_Values();
	}
	void Check_for_Hovering(int x, int y) {
		for (int i = 0; i < 16; i++)
			Alphabets[i].set_Button_Hovered(Alphabets[i].Check_if_Mouse_in_Button_Area(x, y));
	}
	void Reset_Pressed_Letters() {
		for (int i = 0; i < 16; i++)
			Alphabets[i].set_Button_Pushed(0);
		Display_Board();
	}
	void Reset_game() {
		Score = 0;
		Reset_Pressed_Letters();
	}
	void Initialize_Level_Values() {
		int Current_number = rand() % 11; // Assigning random number to starting variable
		int Final_number = Current_number;
		int value1 = rand() % 2 + 1;  // value which will use for subtraction
		int value2 = rand() % 11 + 1; // value which will use for addition
		int value3 = rand() % 5 + 2;  // value which will use for multiplication
		int value4 = rand() % 10;     // value which will use for append at last
		int temp1 = rand() % 4 + 3;   // Getting random movements to play game
		Moves = temp1;
		int finish_number_solution = Current_number;


		string tostring = "- " + to_string(value1);
		Alphabets[0].set_Text_of_button(tostring.c_str());
		tostring = "+ " + to_string(value2);
		Alphabets[1].set_Text_of_button(tostring.c_str());
		if (level < 6) // for level 1-5
		{
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
					Final_number -= value1; // subtracting random generated number

				}
				else if (applying_rules == 0)
				{
					solution.push_back(2);
					Final_number += value2; // adding random generated number
				}
				temp1--;
			}
		}
	}
	void Game_Level() {
	
	}
	void Display_Board() {
		for (int i = 0; i < 16; i++)
			Alphabets[i].Display_Button(0);

		Display_Current_Number();
		Show_Registered_Words();
		Display_Current_Word();
		Display_Score();
	}
	bool Check_for_Letters_input(int x, int y, bool Mousedown_or_up) {//1 for down, 0 for up
		for (int i = 0; i < 16; i++)
			if (Alphabets[i].Check_if_Mouse_in_Button_Area(x, y))
			{
				if (Mousedown_or_up)
					Alphabets[i].set_Button_Pushed(1);
				else
					Alphabets[i].set_Button_Pushed(0);
				if (Alphabets[i].get_Button_Pushed()) {}
				else {	//if button released
					cout << "Operator  " << Alphabets[i].get_text_of_button() << endl;
					if (Operator_Available[i]) {

					}


				}
				return 1;
			}
		return 0;
	}
	int Score_Generator(string Word) {
		switch (Word.size())
		{
		case 2:
		case 3:
		case 4:
			return 1;
		case 5:
			return 2;
		case 6:
			return 3;
		case 7:
			return 5;
		default:
			return 11;
		}
	}
	void Show_Registered_Words() {
		static bool new_game = 0;
		if (Score == 0) {
			new_game = true;
			return;
		}
		int smallest = INT_MAX; int Longest_String = 0;
		if (smallest == Longest_String) {
		}
		Longest_String++;
		string text;
		int i = smallest, number_of_iterations_skiped = 0;
		Text_Box Registered_Word_list;
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		int x_correction = 0;
		Registered_Word_list.set_Text_Box("", 30, { 255,255,255, 255 }, { 450,150 }, { 100,324 }, { 43,31,143,0 }, 0);
		int x = Registered_Word_list.get_Box_Position().X + 5 + x_correction, y = Registered_Word_list.get_Box_Position().Y + 5;
		COORD org = { x ,y };
		static int w, h = 0;
		bool is_First_Word = 1;
		while (i != Longest_String) {
			// Get the size of the text
			TTF_SetFontSize(font, 25);
			TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
			TTF_SizeText(font, "", &w, &h);
			istringstream ss(text);
			int MAX_horizontal_spacing = 0;	static int Max_Box_Height = y;
			if (Score == 0 || new_game == 1) {
				Max_Box_Height = y;
				new_game = 0;
			}
			string word;
			int correction = 0;
			Registered_Word_list.Rounding_Radius = 15;
			while (getline(ss, word, ' ')) {

				SDL_Surface* surface = TTF_RenderText_Blended(font, word.c_str(), { 255,255,255,255 });
				SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_FreeSurface(surface);
				//if (word.size() <= 4 || is_First_Word) {
				//	correction = 25;
				//}
				//else
				//	correction = -5;
				if (is_First_Word || i + 1 == Longest_String)
					Registered_Word_list.Rounding_Radius = 20;
				else
					Registered_Word_list.Rounding_Radius = 0;
				//if (i != smallest)
					//is_First_Word = 0;
				SDL_QueryTexture(texture, NULL, NULL, &w, &h);
				if (MAX_horizontal_spacing < w)
					MAX_horizontal_spacing = w;
				if (Max_Box_Height < y)
					Max_Box_Height = y;
				int Box_Width = 100;
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				if (is_First_Word || i + 1 == Longest_String)
					Registered_Word_list.Rounding_Radius = 20;
				else
					Registered_Word_list.Rounding_Radius = 0;
				if (i + 1 == Longest_String) {
					Registered_Word_list.set_Text_Box("", 25, { 255,255,255, 255 }, { short(x - 5),short(y - 5) }, { 90,Max_Box_Height - y + 40 }, { 43,31,143,0 }, 0);
				}
				else
					Registered_Word_list.set_Text_Box("", 25, { 255,255,255, 255 }, { short(x - 5),short(y - 5) }, { 100,Max_Box_Height - y + 40 }, { 43,31,143,0 }, 0);
				//Registered_Word_list.set_Text_Box("", 30, { 255,255,255, 255 }, { short(x - 5),short(y - 5) }, {100,w + correction }, { 43,31,143,0 }, 0);
				//boxSIZE: width, height
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				Registered_Word_list.Display_Text_Box({ 0 }, 0);
				SDL_Rect rect = { x, y, w, h };
				//roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, 20, 75, 75, 75, 255);
				SDL_RenderCopy(renderer, texture, NULL, &rect);
				y += h;
				SDL_DestroyTexture(texture);
			}
			is_First_Word = 0;
			Registered_Word_list.Rounding_Radius = 20;
			if (text != "")
				x = (x + MAX_horizontal_spacing + 10), y = org.Y;
			//x = (x + MAX_horizontal_spacing + 4 + i + 2 / 2), y = org.Y;
					  //x = (x + MAX_horizontal_spacing + i/2), y = org.Y;
		//else
			//x = (x + MAX_horizontal_spacing + 4 + i + 2 / 2 + 1), y = org.Y;
					  //x = (x + MAX_horizontal_spacing + 12), y = org.Y;
			text = "";
			i++;
			MAX_horizontal_spacing = 0;
			//x_correction = (3 + h);
			if (x > 840) {
				SDL_SetWindowSize(window, x + 8, 571);
				SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			}
		}
	}
	void Display_Current_Word() const {
		if (Current_Word == "")
			return;
		Current_Word_Board.set_Text_Box(Current_Word.c_str(), 40, { 255,255,255,255 }, { 470,70 }, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Current_Word_Board.Display_Text_Box({ 0 }, 0);
	}
	void Display_Current_Number() {
		short width = 200;
		COORD position = { (Width - width) / 2, (Height - 15) / 2 };
		Size box_size = { width, 15 };
		SDL_Color box_color = { 75, 75, 75, 255 };
		SDL_Color text_color = { 0, 0, 0, 255 };

		// Call set_Text_Box function to create a text box in the center of the screen with right-aligned text
		string Temp = to_string(Current_number);
		Current_Word_Board.set_Text_Box(Temp.c_str(), 32, text_color, position, box_size, box_color, false);



		//Current_Word_Board.set_Text_Box(Temp.c_str(), 40, { 255,255,255,255 }, { Width / 2,Height / 2 }, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Current_Word_Board.Display_Text_Box({ 0 }, 0);
	}
	void Display_Score() const {
		static string score_mess;
		score_mess = "Score " + to_string(Score);
		static COORD Center;
		Center.X = (Alphabets[1].get_Position().X + Alphabets[2].get_Position().X) / 2 - 20;
		Center.Y = (Alphabets[1].get_Position().Y + Alphabets[2].get_Position().Y) / 2 - 73;
		Score_Board.set_Text_Box(score_mess.c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Score_Board.Display_Text_Box({ 0 }, 0);
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
	int get_Game_Score() const { return Score; }
	void New_Game() {
		Reset_game();
		Set_Board("ATEHHDSEVTMFWLIA");
		//Temp = Temp->next;
	}
	~Board() {
	}
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
	Invalid_Word_Mess.set_Text_Box("Invalid Word", 40, { 255,255,255,255 }, { 470, 70 }, { 150,60 }, { 255,0,0, 255 }, 0);
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
		SDL_SetRenderDrawColor(renderer, 130, 214, 240, 50);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		Rotate_Button.Display_Text_Button();
		Reset_Button.Display_Text_Button();
		New_Game_Button.Display_Text_Button();

		Boggle_Game.Display_Board();

		if (Boggle_Game.get_Game_Score() > Game_Player.get_high_score())
			Game_Player.update_high_Score(Boggle_Game.get_Game_Score()); //updating Player high score at runtime
		//if (Changes_Made)
		{
			SDL_RenderPresent(renderer);	//Final Output to SDL window
			//cout << "Printing\n";
		}
		//Changes_Made = 0;
	}
}

