#include"common.h"
#include"Board.h"
TTF_Font* font = TTF_OpenFont("arial.ttf", 100);
SDL_Window* window = SDL_CreateWindow("Calculator: The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width/*width*/, Screen_Height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
int Transparency = 120;
Text_Box Current_Number_Board, Score_Board, Moves_Board, emptyButton1, emptyButton2, Timer_Board;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();		font = TTF_OpenFont("arial.ttf", 100);//16  //max : 7332 /1000
	if (font == NULL)
		cout << "ERROR!!!\n(Arial.ttf) Font Not Found - unable to render text" << endl;
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Event event;
	Board Calculator_Game;
	srand(time(nullptr)); // function to generate random number every time rand function call
	Button Moves_Button, Chrono_Button;
	Text_Box Play_Game_message;
	Moves_Button.Set_Button("Moves Mode", { 255,255,255,255 }, { (Screen_Width - 170) / 2 - 95,(Screen_Height - 50) / 2 }, { 170, 50 }, 40, { 48, 68, 193, 255 }, 0);
	Chrono_Button.Set_Button("Chrono Mode", { 255,255,255,255 }, { (Screen_Width - 170) / 2 + 95,(Screen_Height - 50) / 2 }, { 170, 50 }, 40, { 48, 68, 193, 255 }, 0);
	Play_Game_message.set_Text_Box("Select Game Mode", 50, { 255,255,255,255 }, { (Screen_Width - 300) / 2,((Screen_Height - 70) / 2) - 100 }, { 300, 70 }, { 48, 68, 193, 255 }, 0);
	int MouseX, MouseY;
	Moves_Button.Display_Text_Button();
	Chrono_Button.Display_Text_Button();
	short Game_Mode = -1;
	while (Game_Mode != 1 && Game_Mode != 0) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
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
				Moves_Button.set_Button_Hovered(Moves_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
				Chrono_Button.set_Button_Hovered(Chrono_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
				if (Moves_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY) != Moves_Button.get_Button_Hovered())
				{
					Moves_Button.set_Button_Hovered(Moves_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
					Moves_Button.Display_Text_Button();
				}
				else if (Chrono_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY) != Chrono_Button.get_Button_Hovered())
				{
					Chrono_Button.set_Button_Hovered(Chrono_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY));
					Chrono_Button.Display_Text_Button();
				}
			}
			if (event.type == SDL_MOUSEBUTTONUP)	//mouse click on Button //RELEASED
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Moves_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					Moves_Button.set_Button_Pushed(0);
					Moves_Button.Display_Text_Button();
					Calculator_Game.Set_Game_Mode(0);
					Game_Mode = 0;
					break;
				}
				else if (Chrono_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					//RELEASED
					Game_Mode = 1;
					Calculator_Game.Set_Game_Mode(1);
					Chrono_Button.set_Button_Pushed(0);
					Chrono_Button.Display_Text_Button();
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {	//mouse click on Button

				if (Moves_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					Moves_Button.set_Button_Pushed(!Moves_Button.get_Button_Pushed());
					Moves_Button.Display_Text_Button();
					break;
				}
				if (Chrono_Button.Check_if_Mouse_in_Button_Area(MouseX, MouseY)) {
					Chrono_Button.set_Button_Pushed(!Chrono_Button.get_Button_Pushed());
					Chrono_Button.Display_Text_Button();
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 225, 190, 190, 50);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		Chrono_Button.Display_Button(0);
		Moves_Button.Display_Button(0);
		Play_Game_message.Display_Text_Box({ 0 }, 0);
		SDL_RenderPresent(renderer);
	}
	Calculator_Game.New_Game();
	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
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
			}
			if (event.type == SDL_MOUSEBUTTONUP)	//mouse click on Button
			{
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Calculator_Game.Check_for_Letters_input(MouseX, MouseY, 0)) {
					break;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {	//mouse click on Button
				SDL_GetMouseState(&MouseX, &MouseY);
				if (Calculator_Game.Check_for_Letters_input(MouseX, MouseY, 1)) {
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 225, 190, 190, 50);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		Calculator_Game.Display_Game();
		SDL_RenderPresent(renderer);
	}
}

