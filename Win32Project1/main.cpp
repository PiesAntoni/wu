#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <exception>
#include "Surface.h"
using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

int main(int argc, char** argv) {


	SDL_Init(SDL_INIT_EVERYTHING);
	int WIDTH = 800;
	int HEIGHT = 600;
	window = SDL_CreateWindow("Napierdalac", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH,HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	Surface surf(renderer,64,64);
	
	srand(time(0));
	for(int i=0; i<64; i++) {
		for(int j=0; j<64; j++) {
			if( (rand()%3) != 1)
				surf.addNode(new SurfaceNode("grass.bmp",i * 48, j*48,false,true));
			else
				surf.addNode(new SurfaceNode("treeb.bmp",i * 48, j*48, false, false));
		}
	}
	
	SurfaceNode* node = new SurfaceNode("knight.png", 5*48, 4*48, true,false);
	surf.addNode(node);
	node->setActionPoints(2);
	node = new SurfaceNode("ninja.png", 6*48, 4*48, true, false);
	surf.addNode(node);
	node->setActionPoints(1);

	surf.drawSurface();

	int running = 1;
	SDL_Event event;
	bool fullscreen = false;
	int screenEdge = 40;
	int x_move = 0;
	int y_move = 0;

	while (running) {
		while (SDL_PollEvent(&event) != 0) { 
			if (event.type == SDL_QUIT) {
				running = 0;
				break;
			}

			if(event.type == SDL_MOUSEBUTTONDOWN) {
				int x = event.button.x;
				int y = event.button.y;
				surf.performAction(x,y);
				
			}


			if(event.type == SDL_KEYDOWN ) {
				switch (event.key.keysym.sym) {
					case SDLK_UP:
						surf.moveY(20); break; 
					case SDLK_DOWN:
						surf.moveY(-20); break;
					case SDLK_LEFT:
						surf.moveX(20); break;
					case SDLK_RIGHT:
						surf.moveX(-20); break;
					case SDLK_f:
						if(fullscreen == false) {
							SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
							screenEdge = 2;
						} else {
							SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
							screenEdge = 40;
						}
						fullscreen = !fullscreen;
						break;
				}
			}

			if(event.type == SDL_MOUSEMOTION) {
				x_move = y_move = 0;
				if( event.button.x < screenEdge )
					x_move = 5;
				else if ( event.button.x > WIDTH - screenEdge )
					x_move = -5;

				if( event.button.y < screenEdge )
					y_move = 5;
				else if ( event.button.y > HEIGHT - screenEdge )
					y_move = -5;
			}

			if(event.window.event == SDL_WINDOWEVENT_LEAVE ) {
				x_move = y_move = 0;
			}

			if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
			}
		}

		surf.moveX(x_move);
		surf.moveY(y_move);
		surf.drawSurface();
	}

	SDL_Quit();
	return 0;
}