#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

int main(int argc, char* argv[])
{

	SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600, 600, 0);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates a surface to load an image into the main memory
	SDL_Surface* surface;
	SDL_Surface* s2;

	// please provide a path for your image
	surface = IMG_Load("xLetter.png");
	s2 = IMG_Load("board.png");

	// loads image to our graphics hardware memory.
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Texture* background = SDL_CreateTextureFromSurface(rend, s2);


	// clears main-memory
	SDL_FreeSurface(surface);

	// let us control our image position
	// so that we can move it with our keyboard.
	SDL_Rect dest;
	SDL_Rect mouse;
	SDL_Rect origin;

	origin.x = 0;
	origin.y = 0;
	origin.w = 600;
	origin.h = 600;

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &mouse.h);

	// adjust height and width of our image box.
	dest.w /= 6;
	dest.h /= 6;

	// set background color
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

	// sets initial x-position of object
	dest.x = (1000 - dest.w) / 2;

	// sets initial y-position of object
	dest.y = (1000 - dest.h) / 2;

	// State of the board
	
	int state[3][3];

	// controls animation loop
	int close = 0;

	// speed of box
	int speed = 3000;

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

				}
				else if (state[r][c] == 2) {

				}
			}
		}
		SDL_RenderCopy(rend, tex, NULL, &dest);
		SDL_RenderCopy(rend, tex, NULL, &mouse);
		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	// destroy texture
	SDL_DestroyTexture(tex);

	// destroy renderer
	SDL_DestroyRenderer(rend);

	// destroy window
	SDL_DestroyWindow(win);

	// close SDL
	SDL_Quit();

	return 0;
}
