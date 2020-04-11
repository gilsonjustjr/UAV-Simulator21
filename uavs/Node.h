#pragma once

#ifndef __NODE_H__
#define __NODE_H__

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class Node
{
private:
	int myX, myY;
	int myID;
	const char myName[20];

public:
	~Node();

	Node(int Ident, int newX, int newY);
	void setID(int ID);
	int getID(void);
	int getX(void);
	int getY(void);

};

#endif