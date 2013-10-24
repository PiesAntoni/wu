#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "SurfaceNode.h"
#include <vector>
#include <iterator>
class Surface
{
private:
	SDL_Renderer* renderer;
	SurfaceNode* selected;
	bool locked;
	int relative_x;
	int relative_y;
	int width;
	int height;
	int xsize, ysize;

	SurfaceNode*** map;
	std::vector<SurfaceNode*> movables;

	SurfaceNode* findClicked(int x, int y);


public:
	
	Surface(SDL_Renderer* renderer, int x, int y, int relative_x =0, int relative_y =0);
	~Surface(void);
	void addNode(SurfaceNode* node);
	void drawSurface();
	void moveX(int x);
	void moveY(int y);
	void performAction(int x, int y);


};

