#include "Game.h"

Game::Game() : Starting_Number(0), Current_number(0), Final_Number(0), Moves_Count(0), level(15) {}
void Game::Set_Game_Interface() {
	short intial_Position = 220;
	/*for (short i = 0; i < Num_of_Buttons; i++) {
		Calculator_buttons[i].Set_Button("", {255, 255, 255}, {short(10 + (i % 3) * (100 + 10)), short((10 + (i / 4) * (100 + 10) + intial_Position))}, {100,100}, 100, {0, 0, 0, 255}, 0);
	}*/
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
void Game::Set_Game_Mode(bool Game_Mode) { this->Game_Mode = Game_Mode; }
void Game::Show_Solution() {
	for (int i = 0; i < Moves_Count; i++)
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
	cout << endl;
}
void Game::Check_for_Hovering(int x, int y) {
	for (short i = 0; i < Num_of_Buttons; i++)
		Calculator_buttons[i].set_Button_Hovered(Calculator_buttons[i].Check_if_Mouse_in_Button_Area(x, y));
}
void Game::Reset_Pressed_Letters() {
	Display_Game();
}
void Game::Restart_level() {
	Current_number = Starting_Number;
	Moves_Count = Moves;
}
void Game::Initialize_Level_Values() {
	system("CLS");
	cout << "level " << level << endl;
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
	if (level == 1) {
		Start_time = time(NULL);
		Timer_Set = 30;
	}
	if (level == 6) {
		Start_time = time(NULL);
		Timer_Set = 45;
	}
	if (level == 11) {
		Start_time = time(NULL);
		Timer_Set = 45;
	}
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
		//Timer_Set = 45;
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
		//Timer_Set = 70;
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
void Game::Display_Game() {
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
	if (Game_Mode) {
		End_time = time(NULL);
		Display_Timer();
		if (Timer_Set - (End_time - Start_time) == 0) {
			Display_Current_Number("Time Up", 150, 1);
			SDL_RenderPresent(renderer);
			SDL_Delay(950);
			cout << "Timer Up - Failed\n";
			if (level <= 5) {
				if (level == 1) {
					Start_time = time(NULL);
				}
				else {
					level = 1;
					Initialize_Level_Values();
				}
			}
			else if (level <= 10) {
				if (level == 6) {
					Start_time = time(NULL);
				}
				else {
					level = 6;
					Initialize_Level_Values();
					Show_Solution();
				}
			}
			else if (level <= 15) {
				if (level == 11) {
					Start_time = time(NULL);
					Show_Solution();
				}
				else {
					level = 11;
					Initialize_Level_Values();
					Show_Solution();
				}
			}
			Restart_level();
		}

	}
}
bool Game::Check_for_Letters_input(int x, int y, bool Mousedown_or_up) {//1 for down, 0 for up
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
					string suffix = Calculator_buttons[i].get_text_of_button().substr(1);
					if (i == 0) {
						Current_number -= stoi(suffix);
					}
					if (i == 1) {
						Current_number += stoi(suffix);
					}
					if (i == 2) {
						Current_number *= stoi(suffix);
					}
					if (i == 3) { //<<
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
							Start_time += 1;
							level = 1; 	Initialize_Level_Values(); Show_Solution();
							return 1;
						}
						else
							Display_Current_Number("Level Up", 140, 1);
						SDL_RenderPresent(renderer);
						cout << "lvl up\n";
						level++; solution.clear();
						SDL_Delay(950);
						Start_time += 1;
						Initialize_Level_Values();
						Show_Solution();
					}
					if (Moves_Count == 0)
					{
						Display_Current_Number("Level Falied", 100, 1);
						SDL_RenderPresent(renderer);
						cout << "lvl failed\n";
						SDL_Delay(950);
						Start_time += 1;
						Restart_level();
					}
				}
			}
			return 1;
		}
	return 0;
}
void Game::Display_Timer() const {
	COORD Center;
	//if (Game_Mode)
	Center.X = ((Screen_Width - 150) / 2) - 80;
	//else
		//Center.X = (Screen_Width - 150) / 2;
	Center.Y = -13;
	string timer_left = to_string(Timer_Set - (End_time - Start_time));
	Timer_Board.set_Text_Box(("Timer " + timer_left).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
	Timer_Board.Display_Text_Box({ 0 }, 0);
}
void Game::Display_Current_Number(string New_message, short font_size, bool new_message) const {
	TTF_CloseFont(font);
	font = TTF_OpenFont("Digital7Monoitalic.ttf", 200);//16  //max : 7332 /1000
	if (font == NULL)
		cout << "ERROR!!!\t(Digital7Monoitalic.ttf) Font Not Found - unable to render text" << endl;
	COORD Center;
	Center.X = (Screen_Width - 370) / 2;
	Center.Y = 123;
	if (new_message)
		Current_Number_Board.set_Text_Box(New_message.c_str(), font_size, { 255,255,255,255 }, Center, { 370,100 }, { 75, 75, 75, 255 }, 0);
	else
		Current_Number_Board.set_Text_Box(to_string(Current_number).c_str(), 150, { 255,255,255,255 }, Center, { 370,100 }, { 75, 75, 75, 255 }, 0);
	Current_Number_Board.Display_Text_Box({ 0 }, 0);
	TTF_CloseFont(font);
	font = TTF_OpenFont("arial.ttf", 100);//16  //max : 7332 /1000
}
void Game::Display_Level() const {
	COORD Center;
	if (Game_Mode)
		Center.X = ((Screen_Width - 150) / 2) + 80;
	else
		Center.X = (Screen_Width - 150) / 2;
	Center.Y = -13;
	Score_Board.set_Text_Box(("Level " + to_string(level)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
	Score_Board.Display_Text_Box({ 0 }, 0);
}
void Game::Display_Moves() const {
	COORD Center;
	Center.X = ((Screen_Width - 150) / 2) - 80;
	Center.Y = 55;		//Center.X -= 80;
	Moves_Board.set_Text_Box(("Moves " + to_string(Moves_Count)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
	Moves_Board.Display_Text_Box({ 0 }, 0);
}
void Game::Display_Final_Number() const {
	COORD Center;
	Center.X = ((Screen_Width - 150) / 2) + 80;
	Center.Y = 55; //Center.X += 80;
	Moves_Board.set_Text_Box(("Target " + to_string(Final_Number)).c_str(), 40, { 255,255,255,255 }, Center, { 150,60 }, { 75, 75, 75, 255 }, 0);
	Moves_Board.Display_Text_Box({ 0 }, 0);
}
void Game::New_Game() {
	Restart_level();
	Set_Game_Interface();
}
int Game::get_level() const { return level; }
