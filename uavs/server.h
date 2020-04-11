#pragma once

#include "vants.h"
#include "Sensor.h"

#define MAX_UAV 30

using namespace System;
using namespace Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::IO::Ports;
using namespace System::IO;
using namespace System::Timers;
using namespace System::Windows::Forms::Design;

ref class Sensor;
ref class Vant;

ref class server
{
private:
	int myID;
	int myX, myY;
	int myCounter;
	String ^ myName;
	String ^ lastMsgFrom;
	PictureBox^ myPic;
	PictureBox ^ myMessageIcon;
	String ^ myMessages;
	String ^ myLabel;
	array<bool> ^ myUAVConnections = (gcnew array<bool>(MAX_UAV));
public:
	server();
	server(System::Windows::Forms::Panel^ sa);
	int getX();
	int getY();
	int getcX();
	int getcY();
	int getMyCounter();
	int countMessages();
	bool hasMessage();
	bool isConnectedWith(int uav);
	void showMessage(bool state);
	void reset(System::Windows::Forms::Panel ^ sa);
	void setXY(int x, int Y);
	void setlastMsgFrom(String ^ i);
	void writeMessage(String ^ msg);
	void setLabel(bool label);
	void setConnection(Vant ^ v);
	void clearConnection(Vant ^ v);
	Point getNearestPoint2(Point ^ target, int maxDistance);
	Size ^ getSize();
	String ^ getMyLabel();
	String ^ getMyName();
	String ^ getMyMessages();
	Point ^ getLocation();
	Point getCenterLocation();
	Point getAntennaLocation();
	PictureBox ^ getPicture();
	PictureBox ^ getMessageIcon();

	virtual ~server();
};

