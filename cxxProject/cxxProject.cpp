#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

void declareWinner(int winner, SDL_Window* win) {
	switch (winner)
	{
	case 0:
		SDL_SetWindowTitle(win, "Draw");
		break;
	case 1:
		SDL_SetWindowTitle(win, "X wins");
		break;
	case 2:
		SDL_SetWindowTitle(win, "O wins");
	default:
		break;
	}
}
int main(int argc, char* argv[])
{

	SDL_Window* win = SDL_CreateWindow("X to move", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600, 600, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates a surface to load an image into the main memory
	SDL_Surface* s1;
	SDL_Surface* s2;
	SDL_Surface* s3;
	// please provide a path for your image
	s1 = IMG_Load("board.png");
	s2 = IMG_Load("xLetter.png");
	s3 = IMG_Load("oLetter.png");

	// loads image to our graphics hardware memory.
	SDL_Texture* background = SDL_CreateTextureFromSurface(rend, s1);
	SDL_Texture* xLetter = SDL_CreateTextureFromSurface(rend, s2);
	SDL_Texture* oLetter = SDL_CreateTextureFromSurface(rend, s3);


	// clears main-memory
	SDL_FreeSurface(s1);
	SDL_FreeSurface(s2);
	SDL_FreeSurface(s3);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect dest;
	SDL_Rect mouse;
	SDL_Rect position;
	SDL_Rect origin;

	origin.x = 0;
	origin.y = 0;
	origin.w = 600;
	origin.h = 600;

	position.w = 95;
	position.h = 170;

	// set background color
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

	// State of the board

	int state[3][3];
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			state[i][j] = 0;
		}

	}

	// controls animation loop
	int close = 0;

	// speed of box
	int speed = 3000;

	// 1 - X 
	// 2 - O
	int turn = 1;

	bool isWinner = false;

	// animation loop
	while (!close) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of close button
				close = 1;
				break;

			case SDL_MOUSEMOTION:
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
				break;

			case SDL_MOUSEBUTTONDOWN:
			{
				int r = event.button.y / 200;
				int c = event.button.x / 200;
				if (state[r][c] == 0 && !isWinner) {
					state[r][c] = turn;
					turn %= 2;
					turn++;
					if (turn == 1)
						SDL_SetWindowTitle(win, "X to move");
					if (turn == 2)
						SDL_SetWindowTitle(win, "O to move");
					bool isDraw = true;
					for (size_t i = 0; i < 3; i++)
					{
						for (size_t j = 0; j < 3; ++j) {
							if (state[i][j] == 0) {
								isDraw = false;
							}
						}
					}
					if (isDraw) {
						declareWinner(0, win);
						isWinner = true;
					}
					for (size_t row = 0; row < 3; row++)
					{
						int potentialWinner = state[row][0];
						if (potentialWinner == state[row][1] && potentialWinner == state[row][2] && potentialWinner > 0)
						{
							declareWinner(potentialWinner, win);
							isWinner = true;
						}
					}
					for (size_t col = 0; col < 3; col++)
					{
						int potentialWinner = state[0][col];
						if (potentialWinner == state[1][col] && potentialWinner == state[2][col] && potentialWinner > 0)
						{
							declareWinner(potentialWinner, win);
							isWinner = true;
						}
					}
					int potentialWinner = state[0][0];
					if (potentialWinner == state[1][1] && potentialWinner == state[2][2] && potentialWinner > 0) {

						declareWinner(potentialWinner, win);
						isWinner = true;
					}
					potentialWinner = state[0][2];
					if (potentialWinner == state[1][1] && potentialWinner == state[2][0] && potentialWinner > 0) {
						declareWinner(potentialWinner, win);
						isWinner = true;
					}
				}
				break;
			}

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					dest.y -= speed / 30;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					dest.x -= speed / 30;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					dest.y += speed / 30;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					dest.x += speed / 30;
					break;
				case SDL_SCANCODE_R:

					for (size_t i = 0; i < 3; i++)
					{
						for (size_t j = 0; j < 3; j++)
						{
							state[i][j] = 0;
						}
					}
					SDL_SetWindowTitle(win, "X to move");
					turn = 1;
					isWinner = false;

				default:
					break;
				}
			}
		}

		// clears the screen
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, background, NULL, &origin);
		for (size_t r = 0; r < 3; r++)
		{
			for (size_t c = 0; c < 3; c++)
			{
				if (state[r][c] == 1) {
					position.x = 50 + 200 * c;
					position.y = 20 + 200 * r;
					SDL_RenderCopy(rend, xLetter, NULL, &position);
				}
				else if (state[r][c] == 2) {

					position.x = 50 + 200 * c;
					position.y = 20 + 200 * r;
					SDL_RenderCopy(rend, oLetter, NULL, &position);
				}
			}
		}

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	// destroy texture
	SDL_DestroyTexture(xLetter);
	SDL_DestroyTexture(oLetter);
	SDL_DestroyTexture(background);


	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(win);

	// close SDL
	SDL_Quit();

	return 0;
}

