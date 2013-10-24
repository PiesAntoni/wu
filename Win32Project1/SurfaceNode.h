#pragma once
#include <SDL.h>
#include <string>

class SurfaceNode
{
private:
	SDL_Texture* texture;
	SDL_Texture* selected;
	std::string filename;
	int x;
	int y;
	int actionpoints;
	bool moveable;
	bool stadable;

public:
	SurfaceNode(std::string filename, int x, int y,bool moveable, bool standable) ;
	~SurfaceNode(void);
	void setTexture(SDL_Texture* texture, SDL_Texture* selected);
	std::string getFileName() const;
	SDL_Texture* getTexture() const;
	SDL_Texture* getSelected() const;
	void swap();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	bool isMoveable();
	bool isStandable();
	int getActionPoints();
	void setActionPoints(int);

};

