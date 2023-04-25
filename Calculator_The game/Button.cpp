#include "Button.h"
Button::Button() : Shadow_box({ 0,0,0,0 }), Button_Pushed(0), Button_Hovered(0), Shadow_offset(5) {}
void Button::Set_Button(const char* Alphabet, SDL_Color Text_Color, COORD Position, Size Button_Size, int Font_Size, SDL_Color Box_Color, bool BOLD) {
	Main_Text_Box.set_Text_Box(Alphabet, Font_Size, Text_Color, Position, Button_Size, Box_Color, BOLD);
	Shadow_box = { Position.X + Shadow_offset, Position.Y + Shadow_offset, Button_Size.height, Button_Size.width };
}
void Button::set_char_of_button(char Alphabet) {
	Main_Text_Box.set_Box_Text_Char(Alphabet, 100, { 0, 0, 255 }, 1);
}
void Button::set_Text_of_button(const char* Alphabet, SDL_Color Font_Color, bool BOLD) {
	Main_Text_Box.set_Box_Text(Alphabet, 100, Font_Color, BOLD);
}
void Button::set_Button_Color(SDL_Color newColor) { Main_Text_Box.set_Box_Color(newColor); }
void Button::set_Button_Size(Size Button_Size) { this->Main_Text_Box.set_Box_Size(Button_Size); }
void Button::set_Button_Pushed(bool Button_pushed) { this->Button_Pushed = Button_pushed; }
void Button::set_Button_Hovered(bool Button_hovered) { this->Button_Hovered = Button_hovered; }
bool Button::Check_if_Mouse_in_Button_Area(int x, int y) const {
	return (x >= Main_Text_Box.get_Box_Position().X
		&& x < Main_Text_Box.get_Box_Position().X + Main_Text_Box.get_Box_Size().height
		&& y >= Main_Text_Box.get_Box_Position().Y
		&& y < Main_Text_Box.get_Box_Position().Y + Main_Text_Box.get_Box_Size().width);
}

bool Button::operator==(Button Button2) {
	return (Main_Text_Box.get_Box_Position().Y == Button2.Main_Text_Box.get_Box_Position().Y && Main_Text_Box.get_Box_Position().X == Button2.Main_Text_Box.get_Box_Position().X);
}
void Button::Diplay_Shadow() const {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (Button_Pushed)//inner shadow
		roundedBoxRGBA(renderer, Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y, Shadow_box.x + Main_Text_Box.get_Box_Size().height, Shadow_box.y + Main_Text_Box.get_Box_Size().width, 20, Main_Text_Box.get_Box_Color().r * (0.55), Main_Text_Box.get_Box_Color().g * (0.55), Main_Text_Box.get_Box_Color().b * (0.55), Transparency + 30);
	else
		roundedBoxRGBA(renderer, Main_Text_Box.get_Box_Position().X, Main_Text_Box.get_Box_Position().Y, Shadow_box.x + Main_Text_Box.get_Box_Size().height, Shadow_box.y + Main_Text_Box.get_Box_Size().width, 20, 75, 75, 75, Transparency);
}
void Button::Display_Button(bool Blocked) {
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
void Button::Display_Text_Button() {
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
COORD Button::get_Position() const { return Main_Text_Box.get_Box_Position(); }
bool Button::get_Button_Pushed() const { return Button_Pushed; }
bool Button::get_Button_Hovered() const { return Button_Hovered; }
Size Button::get_Button_Size() const { return Main_Text_Box.get_Box_Size(); }
string Button::get_text_of_button() { return Main_Text_Box.get_text_for_Box(); }
Text_Box Button::get_Main_Text_Box() const { return Main_Text_Box; }