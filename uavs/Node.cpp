#include "Node.h"




void Node::setID(int ID)
{
	myID = ID;
}

int Node::getID(void)
{
	return myID;
}

int Node::getX(void)
{
	return myX;
}

int Node::getY(void)
{
	return myY;
}

Node::~Node()
{
}
