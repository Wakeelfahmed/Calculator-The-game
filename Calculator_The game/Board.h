#pragma once
#include "Button.h"
#define Num_of_Buttons 7
class Board {
	Button Calculator_buttons[Num_of_Buttons]; //using 1D array as it faster than 2D
	int level;
	int Starting_Number, Current_number, Final_Number, Moves_Count, Moves;
	bool Operator_Available[Num_of_Buttons]{ 0 };
	vector<int> solution; // In solution i will append 1 for subtraction ,2 for addition, 3(*),4(droping digit) and 5 for append digit
	time_t Start_time, End_time, Timer_Set;
	bool Game_Mode;
public:
	Board();
	void Set_Board();
	void Set_Game_Mode(bool Game_Mode);
	void Show_Solution();
	void Check_for_Hovering(int x, int y);
	void Reset_Pressed_Letters();
	void Restart_level();
	void Initialize_Level_Values();
	void Display_Game();
	bool Check_for_Letters_input(int x, int y, bool Mousedown_or_up);
	void Display_Timer() const;
	void Display_Current_Number(string New_message, short font_size, bool new_message) const;
	void Display_Level() const;
	void Display_Moves() const;
	void Display_Final_Number() const;
	void New_Game();
};

