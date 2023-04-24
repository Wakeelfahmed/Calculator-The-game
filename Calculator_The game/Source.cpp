//#include <iostream>
//#include <conio.h>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <Windows.h> // for COORD
//#include <cstdlib>   // for rand() and srand()
//#include <ctime>     // for time()
//#include <algorithm> // for sort(),unique() etc
//#include <vector>    // for vector
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL.h"		//for SDL GUI
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL_ttf.h"	//for SDL GUI Font
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL2_gfxPrimitives.h"	//for Advanced SDL GUI
//#include<string>
//#include<string.h>
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL.h"		//for SDL GUI
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL_ttf.h"	//for SDL GUI Font
//#include "C:\SDL2-devel-2.26.1-VC\include\SDL2_gfxPrimitives.h"	//for Advanced SDL GUI
#include"Text_Box.h"
int Transparency = 120;
//TTF_Font* font;
//SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/*width*/, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//#include"Globals.h"
//TTF_Font* font = TTF_OpenFont("arial.ttf", 100);;
//SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/*width*/, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

#include"common.h"
TTF_Font* font = TTF_OpenFont("arial.ttf", 100);;
SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/*width*/, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer;
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
	void Display_Button(bool Blocked) {
		if (Blocked) {
			//Text_Box Temp;
			Main_Text_Box.set_Box_Text("", 0, { 0 }, 0);
			Main_Text_Box.Display_Text_Box({ 176, 152, 152, 255 }, 1);
			return;
		}
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
	void testfl() {
		Main_Text_Box.get_text_for_Box();
	}
	COORD get_Position() const { return Main_Text_Box.get_Box_Position(); }
	bool get_Button_Pushed() const { return Button_Pushed; }
	bool get_Button_Hovered() const { return Button_Hovered; }
	Size get_Button_Size() const { return Main_Text_Box.get_Box_Size(); }
	//char get_char_of_button() const { return Main_Text_Box.get_text_for_Box().front(); }
	string get_text_of_button() { return Main_Text_Box.get_text_for_Box(); }
	Text_Box get_Main_Text_Box() const { return Main_Text_Box; }
};
Text_Box Current_Number_Board, Score_Board, Moves_Board, emptyButton1, emptyButton2;
#define Num_of_Buttons 7
class Board {
	Button Calculator_buttons[Num_of_Buttons]; //using 1D array as it faster than 2D
	int level;
	int Starting_Number, Current_number, Final_Number, Moves_Count, Moves;
	bool Operator_Available[Num_of_Buttons]{ 0 };
	vector<int> solution; // In solution i will append 1 for subtraction ,2 for addition, 3(*),4(droping digit) and 5 for append digit
public:
	Board() : Starting_Number(0), Current_number(0), Final_Number(0), Moves_Count(0), level(1) {}
	void Set_Board(string Set_Board_Letters) {
		Set_Board_Letters = "ATEHHDSEVTMFWLIA";		short intial_Position = 220;
		for (short i = 0; i < Num_of_Buttons; i++) {
			string temp(1, Set_Board_Letters[i]);
			Calculator_buttons[i].Set_Button(temp.c_str(), { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + intial_Position)) }, { 100,100 }, 100, { 0, 0, 0, 255 }, 0);
		}
		short i = 0;
		SDL_Color Buttons_Color = { 19 ,19 ,19 };
		/*0*/Calculator_buttons[i].Set_Button("-", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*1*/Calculator_buttons[i].Set_Button("+", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*2*/Calculator_buttons[i].Set_Button("x", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, Buttons_Color, 0);		i++;
		/*3*/Calculator_buttons[i].Set_Button("<<", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 251, 153, 2, 255 }, 0);		i++;
		/*4*/Calculator_buttons[i].Set_Button(">>", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 251, 153, 2, 255 }, 0);		i++;
		/*5*/Calculator_buttons[i].Set_Button("Hint", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 46, 228, 52, 255 }, 0);		i++;
		emptyButton1.set_Text_Box("", 0, { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, { 176, 152, 152, 255 }, 0); i++;
		/*6*/Calculator_buttons[6].Set_Button("CLR", { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, 80, { 255,0, 0, 255 }, 0); i++;
		emptyButton2.set_Text_Box("", 0, { 255, 255, 255 }, { short(10 + (i % 3) * (100 + 30)), short((10 + (i / 3) * (100 + 10) + intial_Position)) }, { 120,100 }, { 176, 152, 152, 255 }, 0); i++;
		Initialize_Level_Values();
		Show_Solution();
	}
	void Show_Solution() {
		for (int i = 0; i < Moves_Count; i++)
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
		}	cout << endl;

	}
	void Check_for_Hovering(int x, int y) {
		for (short i = 0; i < Num_of_Buttons; i++)
			Calculator_buttons[i].set_Button_Hovered(Calculator_buttons[i].Check_if_Mouse_in_Button_Area(x, y));
	}
	void Reset_Pressed_Letters() {
		Display_Board();
	}
	void Restart_level() {
		Current_number = Starting_Number;
		Moves_Count = Moves;
	}
	void Initialize_Level_Values() {
		srand(time(nullptr)); // function to generate random number every time rand function call
		Current_number = rand() % 11; // Assigning random number to starting variable
		Starting_Number = Current_number;  //Saving the starting number for level restart/fail
		Operator_Available[5] = 1;
		Operator_Available[6] = 1;
		int final_number = Current_number;
		int Sub = rand() % 2 + 1;  // value which will use for subtraction
		int Add = rand() % 11 + 1; // value which will use for addition
		int temp1 = rand() % 4 + 3;   // Getting random movements to play game
		Moves_Count = temp1;
		Moves = Moves_Count;
		int finish_number_solution = Current_number;
		string tostring = "-" + to_string(Sub);
		Calculator_buttons[0].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		tostring = "+" + to_string(Add);
		Calculator_buttons[1].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		if (level < 6) // for level 1-5
		{
			Operator_Available[0] = 1; //-
			Operator_Available[1] = 1; //+
			Operator_Available[2] = 0; //*
			Operator_Available[3] = 0; //<<
			Operator_Available[4] = 0; //>>
			if (temp1 > 3)
			{
				temp1 = 3;
				Moves_Count = temp1;
				Moves = Moves_Count;
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
			return;
		}

		Calculator_buttons[3].set_Text_of_button("<<", { 255,255,255 }, 0);
		int Mul = rand() % 5 + 2;  // value which will use for multiplication
		tostring = "x" + to_string(Mul);
		Calculator_buttons[2].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);

		int Append = rand() % 10;     // value which will use for append at last
		tostring = ">>" + to_string(Append);

		Calculator_buttons[4].set_Text_of_button(tostring.c_str(), { 255,255,255 }, 0);
		solution.clear();

		if (level < 11) // for level 6-10
		{
			Operator_Available[0] = 1; //-
			Operator_Available[1] = 1; //+
			Operator_Available[2] = 1; //*
			Operator_Available[3] = 0; //<<
			Operator_Available[4] = 0; //>>
			temp1 = 3;
			Moves_Count = temp1;
			Moves = Moves_Count;
			const int size = 3;
			int arr[size];

			for (int i = 0; i < size; i++)
			{
				int applying_rules = rand() % 3 + 1;
				arr[i] = applying_rules;

				for (int j = 0; j < i; j++)
				{
					while (arr[i] == arr[j])
					{
						int applying_rules = rand() % 3 + 1;
						arr[i] = applying_rules;
						j = 0;
					}
				}
			}
			for (int i = 0; i < temp1; i++)
			{
				if (arr[i] == 1)
				{
					solution.push_back(1);
					final_number -= Sub; // subtracting random generated number
				}
				else if (arr[i] == 2)
				{
					solution.push_back(2);
					final_number += Add; // adding random generated number
				}
				else
				{
					solution.push_back(3);
					final_number *= Mul; // multiplying random generated number
				}
			}
			Final_Number = final_number;
		}


		else if (level < 16) // for level 11-15
		{
			Operator_Available[0] = 1; //-
			Operator_Available[1] = 1; //+
			Operator_Available[2] = 1; //*
			Operator_Available[3] = 1; //<<
			Operator_Available[4] = 1; //>>
			temp1 = 5;
			Moves_Count = temp1;
			Moves = Moves_Count;
			const int size = 5;
			int arr[size];

			for (int i = 0; i < size; i++) // to make unique solution
			{
				int applying_rules = rand() % 5 + 1;
				arr[i] = applying_rules;

				for (int j = 0; j < i; j++)
				{
					while (arr[i] == arr[j])
					{
						applying_rules = rand() % 5 + 1;
						arr[i] = applying_rules;
						j = 0;
					}
				}
			}
			for (int i = 0; i < temp1; i++) // if <,> these operaor came next to each other change them 
			{
				if (arr[i] == 4 || arr[i] == 5)
				{
					if (arr[i + 1] == 5 || arr[i + 1] == 4)
					{
						arr[i] = 3;
					}
				}
			}
			for (int i = 0; i < temp1; i++)
			{
				if (arr[i] == 1)
				{
					solution.push_back(1);
					final_number -= Sub; // subtracting random generated number
				}
				else if (arr[i] == 2)
				{
					solution.push_back(2);
					final_number += Add; // adding random generated number
				}
				else if (arr[i] == 3)
				{
					solution.push_back(3);
					final_number *= Mul; // multiplying random generated number
				}
				else if (arr[i] == 4)
				{
					solution.push_back(4);
					final_number = (final_number / 10); // dropping the last digit
				}
				else
				{
					solution.push_back(5);
					final_number = final_number * 10 + Append; // appending random generated number
				}
			}
			Final_Number = final_number;
		}
	}
	void Display_Board() {
		for (int i = 0; i < Num_of_Buttons; i++)
			if (Operator_Available[i] == 0)
				Calculator_buttons[i].Display_Button(1); //blocked, dont show
			else
				Calculator_buttons[i].Display_Button(0); //allowed
		emptyButton1.Display_Text_Box({ 0 }, 0);
		emptyButton2.Display_Text_Box({ 0 }, 0);
		Display_Level();
		Display_Moves();
		Display_Final_Number();
		Display_Current_Number("", 150, 0);
	}
	bool Check_for_Letters_input(int x, int y, bool Mousedown_or_up) {//1 for down, 0 for up
		for (int i = 0; i < Num_of_Buttons; i++)
			if (Calculator_buttons[i].Check_if_Mouse_in_Button_Area(x, y))
			{
				if (Mousedown_or_up)
					Calculator_buttons[i].set_Button_Pushed(1);
				else
					Calculator_buttons[i].set_Button_Pushed(0);
				if (Calculator_buttons[i].get_Button_Pushed()) {}
				else {	//if button released
					if (i == 6) {
						cout << "Reset level\n";
						Restart_level();
						return 1;
					}
					if (i == 5) {
						cout << "Hint : \'";
						if (solution[Moves - Moves_Count] == 1)
							cout << "-";
						else if (solution[Moves - Moves_Count] == 2)
							cout << "+";
						else if (solution[Moves - Moves_Count] == 3)
							cout << "*";
						else if (solution[Moves - Moves_Count] == 4)
							cout << "<"; // for drop digit
						else if (solution[Moves - Moves_Count] == 5)
							cout << ">"; // for append digit
						cout << "\'\n";
						return 1;
					}
					if (Operator_Available[i]) {
						cout << "Operator  " << Calculator_buttons[i].get_text_of_button() << endl;
						string suffix = Calculator_buttons[i].get_text_of_button().substr(1);
						if (i == 0) {
							//cout << "got" << suffix << endl;
							Current_number -= stoi(suffix);
						}
						if (i == 1) {
							//cout << "got" << suffix << endl;
							Current_number += stoi(suffix);
						}
						if (i == 2) {
							//cout << "got" << suffix << endl;
							Current_number *= stoi(suffix);
						}
						if (i == 3) { //<<
							suffix = Calculator_buttons[i].get_text_of_button().substr(2);
							Current_number /= 10;
						}
						if (i == 4) { //>>
							suffix = Calculator_buttons[i].get_text_of_button().substr(2);
							Current_number = (Current_number * 10) + stoi(suffix); // appending the digit at last
						}
						Moves_Count--;
						if (Current_number == Final_Number)
						{
							if (level == 15) {
								Display_Current_Number("Game Complete", 90, 1);
								SDL_RenderPresent(renderer);
								solution.clear();
								SDL_Delay(950);
								level = 1; 	Initialize_Level_Values(); Show_Solution();
								return 1;
							}
							else
								Display_Current_Number("Level Up", 140, 1);
							SDL_RenderPresent(renderer);
							cout << "lvl up\n";
							level++; solution.clear();
							SDL_Delay(950);
							Initialize_Level_Values();
							Show_Solution();
						}
						if (Moves_Count == 0)
						{
							Display_Current_Number("Level Falied", 100, 1);
							SDL_RenderPresent(renderer);
							cout << "lvl failed\n";
							SDL_Delay(950);
							Restart_level();
						}
					}
				}
				return 1;
			}
		return 0;
	}
	void Display_Current_Number(string New_message, short font_size, bool new_message) const {
		TTF_CloseFont(font);
		font = TTF_OpenFont("Digital7Monoitalic.ttf", 200);//16  //max : 7332 /1000
		if (font == NULL)
			cout << "ERROR!!!\t(Digital7Monoitalic.ttf) Font Not Found - unable to render text" << endl;
		COORD Center;
		Center.X = (Width - 370) / 2;
		Center.Y = 123;
		if (new_message)
			Current_Number_Board.set_Text_Box(New_message.c_str(), font_size, { 255,255,255,255 }, Center, { 370,100 }, { 75, 75, 75, 255 }, 0);
		else
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
		Moves_Board.set_Text_Box(("Moves " + to_string(Moves_Count)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Moves_Board.Display_Text_Box({ 0 }, 0);
	}
	void Display_Final_Number() const {
		COORD Center;
		Center.X = ((Width - 150) / 2) + 80;
		Center.Y = 55; //Center.X += 80;
		Moves_Board.set_Text_Box(("Target " + to_string(Final_Number)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
		Moves_Board.Display_Text_Box({ 0 }, 0);
	}
	void New_Game() {
		Restart_level();
		Set_Board("ATEHHDSEVTMFWLIA");
	}
	~Board() {}
};
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	//window = SDL_CreateWindow("Pete's Pizza Party 6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//TTF_Font* font = TTF_OpenFont("arial.ttf", 100);;
	//SDL_Window* window;// = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/*width*/, Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//SDL_Renderer* renderer;// = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();		font = TTF_OpenFont("arial.ttf", 100);//16  //max : 7332 /1000

	if (font == NULL)
		cout << "ERROR!!!\n(Arial.ttf) Font Not Found - unable to render text" << endl;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Event event;
	Board Calculator_Game;
	srand(time(nullptr)); // function to generate random number every time rand function call
	Button Rotate_Button, Reset_Button, New_Game_Button;
	Rotate_Button.Set_Button("Rotate", { 255,255,255,255 }, { 23 + 15,507 }, { 99, 50 }, 40, { 48, 68, 193, 255 }, 0);
	Reset_Button.Set_Button("Reset", { 255,255,255,255 }, { 23 + 130,507 }, { 99, 50 }, 40, { 48, 68, 193, 255 }, 0);
	New_Game_Button.Set_Button("New Game", { 255,255,255,255 }, { 23 + 244,507 }, { 140, 50 }, 40, { 255, 128, 0, 255 }, 0);
	string Player_name;
	Calculator_Game.New_Game();
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
				Calculator_Game.~Board();
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
				Calculator_Game.Check_for_Hovering(MouseX, MouseY);
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
				if (Calculator_Game.Check_for_Letters_input(MouseX, MouseY, 0)) {
					break;
				}
				else if (Rotate_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					//Calculator_Game.Board_rotate();
					Rotate_Button.set_Button_Pushed(0);
					Rotate_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				else if (Reset_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					Calculator_Game.Restart_level();
					Reset_Button.set_Button_Pushed(0);
					Reset_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
				else if (New_Game_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					//Calculator_Game.New_Game();
					New_Game_Button.set_Button_Pushed(0);
					New_Game_Button.Display_Text_Button();
					Changes_Made = 1;
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {	//mouse click on Button
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Calculator_Game.Check_for_Letters_input(MouseX, MouseY, 1)) {
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

		Calculator_Game.Display_Board();
		SDL_RenderPresent(renderer);
	}
}

