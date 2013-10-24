#include "SurfaceNode.h"


SurfaceNode::SurfaceNode(std::string filename, int x, int y,bool moveable, bool standable) 
{
	this->texture = nullptr;
	this->moveable = moveable;
	this->stadable = standable;
	this->filename = filename;
	this->x = x;
	this->y = y;
}


SurfaceNode::~SurfaceNode(void)
{
}

void SurfaceNode::setTexture(SDL_Texture* texture, SDL_Texture* selected)
{
	this->texture = texture;
	this->selected = selected;
}

std::string SurfaceNode::getFileName() const {
	return filename;
}

SDL_Texture* SurfaceNode::getTexture() const{
	return texture;
}


SDL_Texture* SurfaceNode::getSelected() const{
	return selected;
}
int SurfaceNode::getX() {
	return x;
}

int SurfaceNode::getY() {
	return y;
}

void SurfaceNode::setX(int x) {
	this->x = x;
}



void SurfaceNode::setY(int y) {
	this->y = y;
}

bool SurfaceNode::isMoveable() {
	return moveable;
}

bool SurfaceNode::isStandable() {
	return stadable;
}

void SurfaceNode::swap() {
	SDL_Texture* temp = texture;
	texture = selected;
	selected = temp;
}

int SurfaceNode::getActionPoints() {
	return actionpoints;
}

void SurfaceNode::setActionPoints(int x) {
	this->actionpoints = x;
}