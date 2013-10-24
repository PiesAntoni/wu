#include "Surface.h"


Surface::Surface(SDL_Renderer* renderer, int x, int y, int relative_x , int relative_y )
{
	this->map = new SurfaceNode**[x];
	for(int i=0; i< x; ++i)
		map[i] = new SurfaceNode*[y];

	this->selected = nullptr;
	this->locked = locked;
	this->renderer = renderer;
	this->xsize = x;
	this->ysize = y;
	this->relative_x = relative_x;
	this->relative_y = relative_y;
}


Surface::~Surface(void)
{
}

void Surface::addNode(SurfaceNode* node) {
	int x = node->getX()/48;
	int y = node->getY()/48;

	SDL_Texture* temptexture, *seltexture = nullptr;


	for(int i=0; i<x; i++) {
		for(int j=0; j<y; ++j) {
			if(map[i][j]->getFileName() == node->getFileName() ) {
				node->setTexture(map[i][j]->getTexture(),map[i][j]->getSelected());
				if(node->isMoveable()) {
					movables.push_back(node);
					return;
				}
				map[x][y] = node;
				return;
			}
		}
	}

	temptexture = IMG_LoadTexture(renderer, node->getFileName().c_str());
	if(node->isMoveable()) {
		seltexture = IMG_LoadTexture(renderer,("s"+node->getFileName()).c_str());
	}
	node->setTexture(temptexture,seltexture);
	if(node->isMoveable()) {
		movables.push_back(node);
		return;
	}
	
	map[x][y] = node;
}



void Surface::drawSurface()
{
	SDL_RenderClear(renderer);

	for( int i=0; i<xsize; ++i) {
		for(int j =0; j<ysize; ++j) {
			SDL_Rect pos;
			pos.x = map[i][j]->getX() + relative_x;
			pos.y = map[i][j]->getY() + relative_y;
			SDL_Texture* tex = map[i][j]->getTexture();
			SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
			SDL_RenderCopy(renderer, tex, NULL, &pos);
		}
	}

	for( SurfaceNode* node : movables) {
		SDL_Rect pos;
		pos.x = node->getX() + relative_x;
		pos.y =node->getY() + relative_y;
		SDL_Texture* tex = node->getTexture();
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
		SDL_RenderCopy(renderer, tex, NULL, &pos);
	}


	if(selected != nullptr) {
		int xsel = selected->getX();
		int ysel = selected->getY();
		
		SDL_Texture* highlight = IMG_LoadTexture(renderer, "highlight.png");
		int moves = selected->getActionPoints();
		for(int xs = xsel - moves*48; xs <= xsel + moves*48; xs += 48) {
			for(int ys = ysel - moves*48; ys <= ysel + moves*48; ys += 48) {
				
				SurfaceNode* n = findClicked(xs+1,ys+1);
				if(n!=nullptr && n->isStandable()) {
					SDL_Rect pos;
					pos.x = xs + relative_x;
					pos.y = ys + relative_y;
					//std::cout << pos.x << " " << pos.y << std::endl;
					SDL_QueryTexture(highlight, NULL, NULL, &pos.w, &pos.h);
					SDL_RenderCopy(renderer, highlight, NULL, &pos);
				}
			}
		}
		SDL_DestroyTexture(highlight);
	}


	SDL_RenderPresent(renderer);
}

void Surface::moveX(int x) {
	this->relative_x += x;
}

void Surface::moveY(int y) {
	this->relative_y += y;
}



SurfaceNode* Surface::findClicked(int x, int y) {
	if(x/48.0 < 0.0 || x/48.0 >= xsize || y/48.0 < 0.0 || y/48.0 >= ysize )
		return nullptr;
	
	for( SurfaceNode* node : movables ) {
		if ((node->getX() <= x && x <= node->getX() + 48)
			&& (node->getY() <= y && y <= node->getY() + 48)) {
				return node;
		}
	}
	
	return map[x/48][y/48];
}

void Surface::performAction(int x, int y) {
	SurfaceNode* clicked;
	x = x - relative_x;
	y = y - relative_y;
	if(selected == nullptr) {
		SurfaceNode* clicked = findClicked(x,y);
		if(clicked != nullptr && clicked->isMoveable()) {
			selected = clicked;
			selected->swap();
		}
		else
			return;
	} else {
		clicked = findClicked(x, y);
		if(clicked == nullptr)
			return;
		else if (clicked->getX() < selected->getX() - selected->getActionPoints()*48 ||
			clicked->getX() > selected->getX() + selected->getActionPoints()*48)
			return;
		else if (clicked->getY() < selected->getY() - selected->getActionPoints()*48 ||
			clicked->getY() > selected->getY() + selected->getActionPoints()*48)
			return;

		if(clicked == selected) {
			selected->swap();
			selected = nullptr;
		} else if(!clicked->isStandable())
			return;
		else {
			x -= x%48;
			y -= y%48;
			selected->setX(clicked->getX());
			selected->setY(clicked->getY());
			selected->swap();
			selected = nullptr;
		}
	}


}