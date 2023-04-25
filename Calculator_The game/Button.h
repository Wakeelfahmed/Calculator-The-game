#pragma once
#include"Text_Box.h"
extern 	Text_Box Current_Number_Board, Score_Board, Moves_Board, emptyButton1, emptyButton2, Timer_Board;
class Button {
protected:
	Text_Box Main_Text_Box;
	SDL_Rect Shadow_box;	bool Button_Pushed;		bool Button_Hovered;	int Shadow_offset;
public:
	Button();
	void Set_Button(const char* Alphabet, SDL_Color Text_Color, COORD Position, Size Button_Size, int Font_Size, SDL_Color Box_Color, bool BOLD);
	void set_char_of_button(char Alphabet);
	void set_Text_of_button(const char* Alphabet, SDL_Color Font_Color, bool BOLD);
	void set_Button_Color(SDL_Color newColor);
	void set_Button_Size(Size Button_Size);
	void set_Button_Pushed(bool Button_pushed);
	void set_Button_Hovered(bool Button_hovered);
	bool Check_if_Mouse_in_Button_Area(int x, int y) const;
	bool operator==(Button Button2);
	void Diplay_Shadow() const;
	void Display_Button(bool Blocked);
	void Display_Text_Button();
	COORD get_Position() const;
	bool get_Button_Pushed() const;
	bool get_Button_Hovered() const;
	Size get_Button_Size() const;
	string get_text_of_button();
	Text_Box get_Main_Text_Box() const;
};


