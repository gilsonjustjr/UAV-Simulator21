#include "server.h"



server::server()
{
}

server::server(System::Windows::Forms::Panel ^ sa)
{
	myID = 0;
	myCounter = 0;
	
	Random ^ rand = gcnew Random();
	Point p;

	myPic = gcnew System::Windows::Forms::PictureBox();
	myPic->Image = Image::FromFile("Images\\server3.png");
	myPic->BackColor = System::Drawing::Color::Transparent;
	myPic->Size = System::Drawing::Size(60, 40);
	myPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;

	myName = "s" + myID.ToString();
	lastMsgFrom = myName;
	p.X = 5;
	p.Y = sa->Height - myPic->Height;
	myPic->Location = p;

	System::Drawing::Drawing2D::GraphicsPath ^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddEllipse(0, 0, myPic->Width + 5, myPic->Height + 5);
	Region ^ rg = gcnew Region(gp);
	myPic->Region = rg;

	myMessageIcon = gcnew PictureBox();
	myMessageIcon->Image = Image::FromFile("Images\\message.png");
	myMessageIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
	myMessageIcon->Size = System::Drawing::Size(12, 12);
	myMessageIcon->Tag = "e" + myID.ToString();
	myMessages = "";

	myPic->Tag = "s" + myID.ToString();
	showMessage(false);

	sa->Controls->Add(myMessageIcon);
	sa->Controls->Add(myPic);
}

int server::getX()
{
	myX = myPic->Location.X;
	return myX;
}

int server::getY()
{
	myY = myPic->Location.Y;
	return myY;
}

int server::getcX()
{
	return myPic->Location.X + myPic->Width / 2;
}

int server::getcY()
{
	return myPic->Location.Y + myPic->Height / 2;
}

int server::getMyCounter()
{
	return myCounter;
}

int server::countMessages()
{
	long count = 0;
	int position = 0;

	while ((position = myMessages->IndexOf("\r\n", position)) != -1)
	{
		count++;
		position++;      
	}

	return count;
}

bool server::hasMessage()
{
	if (myMessageIcon->Visible)
		return true;
	else
		return false;
}

bool server::isConnectedWith(int uav)
{
	return myUAVConnections[uav];
}

void server::showMessage(bool state)
{
	if (state)
	{
		myMessageIcon->Visible = true;
		myMessageIcon->Location = System::Drawing::Point(getX() + 40, getY() + 25);
	}
	else
	{
		myMessageIcon->Visible = false;
	}
}

void server::reset(System::Windows::Forms::Panel ^ sa)
{
	this->setXY(5, sa->Height - myPic->Height);
	this->showMessage(false);
	lastMsgFrom = myName;
	myCounter = 0;
	myMessages = "";
}

void server::setXY(int x, int y)
{
	 myPic->Location = System::Drawing::Point(x, y);
}

void server::setlastMsgFrom(String ^ i)
{
	lastMsgFrom = i;
}

void server::writeMessage(String ^ msg)
{
	myMessages += msg;
	myCounter++;
}

void server::setLabel(bool label)
{
	if (label)
		myLabel = "ID:" + myID + "\r\nCounter:" + myCounter + "\r\nMsgs: " + countMessages();
	else
		myLabel = "";
}

void server::setConnection(Vant ^ v)
{
	myUAVConnections[v->getID()] = true;
}

void server::clearConnection(Vant ^ v)
{
	myUAVConnections[v->getID()] = false;
}

Point server::getNearestPoint2(Point ^ target, int maxDistance)
{
	int distX, distY;
	double distance, angle;
	int myCx, myCy;

	//myCx = myX + myPic->Size.Width / 2;
	//myCy = myY + myPic->Size.Height / 2;

	myCx = getAntennaLocation().X;
	myCy = getAntennaLocation().Y;

	distX = target->X - myCx;
	distY = target->Y - myCy;

	distance = Math::Round(Math::Sqrt((Math::Pow(myCx - target->X, 2) + Math::Pow(myCy - target->Y, 2))), 2);

	angle = Math::Atan2(distY, distX);

	Point p;

	//p.X = myCx + (totalDistance - (maxDistance - myPic->Size.Width / 2))*Math::Cos(angle);
	//p.Y = myCy + (totalDistance - (maxDistance - myPic->Size.Height / 2))*Math::Sin(angle);
	
	p.X = Convert::ToInt32(myCx + (distance - (maxDistance))*Math::Cos(angle));
	p.Y = Convert::ToInt32(myCy + (distance - (maxDistance))*Math::Sin(angle));

	return p;
}

Size ^ server::getSize()
{
	return myPic->Size;
}

String ^ server::getMyLabel()
{
	return myLabel;
}

String ^ server::getMyName()
{
	return myName;
}

String ^ server::getMyMessages()
{
	return myMessages;
}

Point ^ server::getLocation()
{
	return myPic->Location;
}

Point server::getCenterLocation()
{
	Point p;

	p.X = myPic->Location.X + (myPic->Size.Width / 2);
	p.Y = myPic->Location.Y + (myPic->Size.Height / 2);

	return p;
}

Point server::getAntennaLocation()
{
	Point p;
	p.X = myPic->Location.X + (3*myPic->Size.Width / 4);
	p.Y = myPic->Location.Y + (myPic->Size.Height / 3);
	return p;
}


PictureBox ^ server::getPicture()
{
	return myPic;
}

PictureBox ^ server::getMessageIcon()
{
	return myMessageIcon; 
}


server::~server()
{
}
