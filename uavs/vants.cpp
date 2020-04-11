#include "vants.h"
#include <stdlib.h>
#include <iostream>

Vant::Vant() {}

Vant::Vant(int ID, System::Windows::Forms::Panel^ sa)
{
	myID = ID;
	myInit = true;
	myCounter = 0;
	totalDistance = 0;
	myRealSpeed = 1;
	myOldSpeed = 1;
	whereIamNow = -1;
	routeListControl = 0;
	hops = 0;
	myCluster = -1;
	waiting = false;
	decisions = 0;
	//active = false;

	myStopWatch = gcnew Stopwatch();
	Random ^ rand = gcnew Random();
	Point p;

	myTimer = gcnew System::Windows::Forms::Timer;
	myTimer->Tick += gcnew System::EventHandler(this, &Vant::timerTick);
	myTimer->Enabled = false;

	myPic = gcnew System::Windows::Forms::PictureBox();
	myPic->Tag = "U" + myID.ToString();
	myPic->Image = Image::FromFile("Images\\uav.png");
	myPic->BackColor = System::Drawing::Color::Transparent;
	myPic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;

	myName = "U" + myID.ToString();
	lastMsgFrom = myName;
	p.X = rand->Next(myPic->Size.Width, sa->Width - myPic->Size.Width);
	p.Y = rand->Next(myPic->Size.Height, sa->Height - myPic->Size.Height);
	myPic->Location = p;
	myFirstLocation = p;

	System::Drawing::Drawing2D::GraphicsPath ^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddEllipse(0, 0, myPic->Width - 3, myPic->Height - 3);

	Region ^ rg = gcnew Region(gp);
	myPic->Region = rg;

	myLabel->Text = myID.ToString();
	myLabel->Location = System::Drawing::Point(p.X + 25, p.Y + 5);
	myLabel->Visible = true;
	myLabel->AutoSize = true;
	myLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

	myMessageIcon = gcnew PictureBox();
	myMessageIcon->Image = Image::FromFile("Images\\message.png");
	myMessageIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
	myMessageIcon->Size = System::Drawing::Size(12, 12);
	myMessageIcon->Tag = "M" + myID.ToString();
	myMessages = "";

	sa->Controls->Add(myMessageIcon);
	sa->Controls->Add(myPic);
	sa->Controls->Add(myLabel);

	showMessage(false);
	setLabel(true);
}

int Vant::getID()
{
	return myID;
}

int Vant::getX()
{
	myX = myPic->Location.X;
	return myX;
}

int Vant::getY()
{
	myY = myPic->Location.Y;
	return myY;
}

int Vant::getcX()
{
	return myPic->Location.X + (myPic->Size.Width / 2);
}

int Vant::getcY()
{
	return myPic->Location.Y + (myPic->Size.Height / 2);
}

int Vant::getSpeed()
{
	return mySpeed;
}

int Vant::getOldSpeed()
{
	return myOldSpeed;
}

void Vant::setOldSpeed(int oSpeed)
{
	myOldSpeed = oSpeed;
}

void Vant::resetSpeed()
{
	totalDistance = 0;
	myStopWatch->Restart();
}

void Vant::setInit(bool state)
{
	myInit = state;
}

bool Vant::getInit()
{
	return myInit;
}

int Vant::getMyCounter()
{
	return myCounter;
}

void Vant::setMyCounter(int c)
{
	myCounter = c;
}

void Vant::showMessage(bool state)
{
	if (state)
	{
		myMessageIcon->Visible = true;
		myMessageIcon->Location = System::Drawing::Point(getX() + 9, getY() + 15);
	}
	else
	{
		myMessageIcon->Visible = false;
	}
}

void Vant::sendMessage(Vant ^ v, bool remember)
{
	if (!remember)
	{
		v->setlastMsgFrom(myName);
		v->showMessage(true);
		v->writeMessage(myMessages);

		lastMsgFrom = v->getMyName();
		this->showMessage(false);
		myMessages = "";
	}
	else
	{
		if ((v->getlastMsgFrom() != myName || lastMsgFrom != v->getMyName()))
		{
			v->setlastMsgFrom(myName);
			v->showMessage(true);
			v->writeMessage(myMessages);
			lastMsgFrom = v->getMyName();
			this->showMessage(false);
			myMessages = "";
		}
	}
}

void Vant::copyMessage(Vant ^ v)
{
	if (v->getlastMsgFrom() != myName && lastMsgFrom != v->getMyName())
	{
		String ^ str;
		str = v->getMyMessages();
		v->setlastMsgFrom(myName);
		v->showMessage(true);
		v->writeMessage(myMessages);
		this->writeMessage(str);
	}
}

void Vant::sendMessage(server ^ ss)
{
	ss->setlastMsgFrom(myName);
	ss->showMessage(true);
	ss->writeMessage(myMessages);

	lastMsgFrom = ss->getMyName();
	showMessage(false);
	myMessages = "";
}

void Vant::setConnection(server ^ ss)
{
	serverConnection = true;
	ss->setConnection(this);
}

void Vant::setConnection(Vant ^ v)
{
	myUAVConnections[v->getID()] = true;

	



}

void Vant::setConnection(Sensor ^ s)
{
	whereIamNow = s->getID();
	connectedWithSensorNow = s->getID();

	mySensorConnections[s->getID()] = true;
	s->setConnection(myID);
}

void Vant::clearConnection(Vant ^ v)
{
	myUAVConnections[v->getID()] = false;
}

void Vant::clearConnection(Sensor ^ s)
{
	if (whereIamNow == s->getID())
		whereIamNow = -1;

	if (connectedWithSensorNow == s->getID())
		connectedWithSensorNow = -1;

	mySensorConnections[s->getID()] = false;
	s->clearConnection(myID);
}

void Vant::clearConnection(server ^ ss)
{
	serverConnection = false;
	ss->clearConnection(this);
}

bool Vant::hasMessage()
{
	if (myMessageIcon->Visible)
		return true;
	else
		return false;
}

bool Vant::getWaiting()
{
	return waiting;
}

void Vant::setWaiting(bool wait)
{
	waiting = wait;
}

bool Vant::isServerConnected()
{
	return serverConnection;
}

Point ^ Vant::getNextRoute(int MaxSensor, int MinDistance)
{
	if (myCounter >= MaxSensor)
	{
		myRWP = myFirstLocation;
		myCounter = 0;
	}
	else
	{
		myRWP = getNearestPoint(myRoute[myCounter]->getCenterLocation(), MinDistance);
		myCounter++;
	}

	return myRWP;
}

Point ^ Vant::getLastRoute(int MaxSensor)
{
	if (myCounter == 0)
		myRoute[MaxSensor - 1]->getCenterLocation();
	else
		return myRoute[myCounter - 1]->getCenterLocation();

	return nullptr;
}

Sensor ^ Vant::getRouteSensor(int index)
{
	if (index == 99)
		return myRoute[myCounter];
	else
		return myRoute[index];
}

String ^ Vant::getMyMessages()
{
	return myMessages;
}

String ^ Vant::getMyLabel()
{
	return myLabel->Text;
}

double Vant::getTotalDistance()
{
	return totalDistance;
}

bool Vant::getIsAtTarget()
{
	return isAtTarget;
}

Point ^ Vant::getLocation()
{
	return myPic->Location;
}

Size ^ Vant::getSize()
{
	return myPic->Size;
}

PictureBox ^ Vant::getPicture()
{
	return myPic;
}

PictureBox ^ Vant::getMessageIcon()
{
	return myMessageIcon;
}

Stopwatch ^ Vant::getMyStopWatch()
{
	return myStopWatch;
}

double Vant::getMyRealSpeed()
{
	if (myStopWatch->IsRunning)
	{
		if (myStopWatch->ElapsedMilliseconds > 1000)
			return myRealSpeed;
		else
			return 42;
	}
	else
		return 42;
}

double Vant::getMyRealSpeed(int scrollValue)
{
	if (myStopWatch->IsRunning && myStopWatch->ElapsedMilliseconds > 1000)
	{
		return myRealSpeed;
	}
	else
	{
	//	std::cout << std::endl << "scrollValue: " << scrollValue;

		if (scrollValue < 70)
			return 65;

		if (scrollValue >= 70 && scrollValue < 90)
			return 55;

		if (scrollValue >= 90 && scrollValue < 110)
			return 43;

		if (scrollValue >= 110 && scrollValue < 130)
			return 32;

		if (scrollValue >= 130 && scrollValue < 150)
			return 29;

		if (scrollValue >= 150 && scrollValue < 170)
			return 25;

		if (scrollValue >= 170 && scrollValue < 190)
			return 21;

		if (scrollValue >= 190 && scrollValue < 210)
			return 19;

		if (scrollValue >= 210 && scrollValue < 230)
			return 18;

		if (scrollValue >= 230)
			return 16;
	}
}

double Vant::getTimeFromToByCoord(Point ^ p1, Point ^ p2)
{
	return Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2)) / myRealSpeed;

}

double Vant::getTimeFromTo(int source, int destination, int readTime, int qSensors, int typeRoute)
{
	int myIndexSource;
	int myIndexDestination;

	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (myRoute[i]->getID() == source)
			myIndexSource = i;
	}

	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (myRoute[i]->getID() == destination)
			myIndexDestination = i;
	}

	double totalTime = 0;
	Point ^ p1;
	Point ^ p2;

	//no needed to round vector;
	if (myIndexSource < myIndexDestination)
	{
		for (int i = myIndexSource; i < myIndexDestination; i++)
		{
			p1 = myRoute[i]->getCenterLocation();
			p2 = myRoute[i + 1]->getCenterLocation();			

			totalTime += readTime + Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2))/myRealSpeed ;
		}

		return totalTime;
	}
	else
	{
		//calculate untill the end, and go back from zero untill one sensor before;
		for (int i = myIndexDestination; i < qSensors; i++)
		{
			p1 = myRoute[i]->getCenterLocation();
			p2 = myRoute[i + 1]->getCenterLocation();

			totalTime += readTime + Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2)) / myRealSpeed;
		}

		for (int i = 0; i < myIndexDestination; i++)
		{
			if (i == 0)
				p1 = myFirstLocation;
			else
			{
				p1 = myRoute[i]->getCenterLocation();
				p2 = myRoute[i + 1]->getCenterLocation();
			}

			totalTime += readTime + Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2)) / myRealSpeed;
		}

		return totalTime;
	}

	return 0;
}

double Vant::getTimeUntillSensor(int sensorID, int readTime, int maxSensors, int route)
{
	double totalTime = 0;
	double totalDistance = 0;
	double myRealSpeed2 = 1;
	Point ^ p1;
	Point ^ p2;
	
	for (int i = 0; i <= maxSensors; i++)
	{
		if(i!=maxSensors)
		{
			if (i == 0)
			{
				p1 = this->getMyFirstLocation();

				switch (route)
				{
					case ROUTE_RED:
						p2 = myRoute[i]->getCenterLocation();
						break;

					case ROUTE_GREEN:
						p2 = myTargets[i];
						break;

					case ROUTE_BLUE:
						p2 = myFly[i];
						break;

					case ROUTE_CYAN:
						p2 = myHibridFly[i];
						break;
				}
			}
			else
			{
				switch (route)
				{
					case ROUTE_RED:
						p2 = myRoute[i]->getCenterLocation();
						p1 = myRoute[i - 1]->getCenterLocation();
						break;

					case ROUTE_GREEN:
						p2 = myTargets[i];
						p1 = myTargets[i - 1];
						break;

					case ROUTE_BLUE:
						p2 = myFly[i];
						p1 = myFly[i - 1];
						break;

					case ROUTE_CYAN:
						p2 = myHibridFly[i];
						p1 = myHibridFly[i - 1];
						break;
				}
			}
		}
		else
		{
			if (isServerConnected())
			{
				switch (route)
				{
					case ROUTE_RED:
						p1 = myRoute[maxSensors - 1]->getCenterLocation();
						break;

					case ROUTE_GREEN:
						p1 = myTargets[maxSensors - 1];
						break;

					case ROUTE_BLUE:
						p1 = myFly[maxSensors - 1];
						break;

					case ROUTE_CYAN:
						p1 = myHibridFly[maxSensors - 1];
						break;
				}

				p2 = this->getMyFirstLocation();
				//totalDistance += Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2));
				//return (1000 * (totalDistance / getMyRealSpeed()) + totalTime);
			}
		}

		totalDistance += Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2));
		
		myRealSpeed2 = getMyRealSpeed();

		//if(totalDistance >= 0)
		totalTime += readTime;

		if (myRoute[i]->getID() == sensorID && i!=maxSensors)
			return (1000 * (totalDistance / myRealSpeed2) + totalTime);
	}

	return 0;
}

double Vant::getRouteTotalTime(int sensorID, int readTime, int maxSensors, int route)
{
	double totalTime = 0;
	double totalDistance = 0;
	Point ^ p1;
	Point ^ p2;

	for (int i = 0; i <= maxSensors; i++)
	{
		if(i!=maxSensors)
		{
			if (i == 0)
			{
				p1 = this->getMyFirstLocation();

				switch (route)
				{
					case ROUTE_RED:
						p2 = myRoute[i]->getCenterLocation();
						break;

					case ROUTE_GREEN:
						p2 = myTargets[i];
						break;

					case ROUTE_BLUE:
						p2 = myFly[i];
						break;

					case ROUTE_CYAN:
						p2 = myHibridFly[i];
						break;
				}
			}
			else
			{
				switch (route)
				{
					case ROUTE_RED:
						p2 = myRoute[i]->getCenterLocation();
						p1 = myRoute[i - 1]->getCenterLocation();
						break;

					case ROUTE_GREEN:
						p2 = myTargets[i];
						p1 = myTargets[i - 1];
						break;

					case ROUTE_BLUE:
						p2 = myFly[i];
						p1 = myFly[i - 1];
						break;

					case ROUTE_CYAN:
						p2 = myHibridFly[i];
						p1 = myHibridFly[i - 1];
						break;
				}

			}
		}
		else
		{
			switch (route)
			{
				case ROUTE_RED:
					p1 = myRoute[maxSensors - 1]->getCenterLocation();
					break;

				case ROUTE_GREEN:
					p1 = myTargets[maxSensors - 1];
					break;

				case ROUTE_BLUE:
					p1 = myFly[maxSensors - 1];
					break;

				case ROUTE_CYAN:
					p1 = myHibridFly[maxSensors - 1];
					break;
			}

			p2 = this->getMyFirstLocation();
		}

		totalDistance += Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2));

		//if(totalDistance > 0)
		totalTime += readTime;
	}

	double routeTotalTime = (1000 * (totalDistance / getMyRealSpeed()) + totalTime);

	if (routeTotalTime > 0)
		return routeTotalTime;
	else
		return totalTime;
}

void Vant::addRouteList(JustID ^ rr)
{
	routeList.Add(rr);
}

void Vant::addRouteList(Point ^ p, int ID)
{
	JustID ^ rr = gcnew JustID();

	rr->setMyLocation(p);
	rr->setMyID(ID);
	rr->setMyTimeSlot(-1);
	rr->setMyOriginalTimeSlot(-1);
	rr->setMyCluster(-1);
	rr->setVisited(false);
	rr->setIsReprogrammed(false);

	routeList.Add(rr);
}

void Vant::clearRouteList()
{
	routeList.Clear();
}

Point ^ Vant::getRouteListByID(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
			return routeList[i]->getMyLocation();
	}

	return nullptr;

}

JustID ^ Vant::getJustIDByID(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
		if (routeList[i]->getMyID() == ID)
			return routeList[i];

	return nullptr;
}

Point ^ Vant::getNextTarget()
{
	if (myCounter == routeList.Count - 1)
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter = 0;
		myRWP = routeList[myCounter]->getMyLocation();

		whereIamNow = routeList[myCounter]->getMyID();
		whereIgoingTo = routeList[myCounter + 1]->getMyID();

		return myRWP;
	}
	else
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter++;
		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		if (myCounter + 1 <= routeList.Count - 1)
			whereIgoingTo = routeList[myCounter + 1]->getMyID();
		else
			whereIgoingTo = routeList[0]->getMyID();

		return myRWP;
	}

}

Point ^ Vant::getNextUnvisitedTarget()
{
	if (myCounter == routeList.Count - 1)
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter = 0;
				 
		while (routeList[myCounter]->getDiscovered())
			myCounter++;

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();
		whereIgoingTo = routeList[myCounter + 1]->getMyID();

		return myRWP;
	}
	else
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter++;

		while (routeList[myCounter]->getDiscovered())
		{
			myCounter++;

			if (myCounter >= routeList.Count)
				myCounter = 0;
		}

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		if (myCounter + 1 <= routeList.Count - 1)
			whereIgoingTo = routeList[myCounter + 1]->getMyID();
		else
			whereIgoingTo = routeList[0]->getMyID();

		return myRWP;
	}
}

int Vant::getNextUnvisitedID()   
{
	if (myCounter == routeList.Count - 1)
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter = 0;

		while (routeList[myCounter]->getDiscovered())
			myCounter++;

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();
		whereIgoingTo = routeList[myCounter + 1]->getMyID();

		return routeList[myCounter]->getMyID();
	}
	else
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter++;

		while (routeList[myCounter]->getDiscovered())
		{
			myCounter++;

			if (myCounter >= routeList.Count)
				myCounter = 0;
		}

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		if (myCounter + 1 <= routeList.Count - 1)
			whereIgoingTo = routeList[myCounter + 1]->getMyID();
		else
			whereIgoingTo = routeList[0]->getMyID();

		return routeList[myCounter]->getMyID();
	}   
}

int Vant::getNextUnvisitedID_withoutDeposit(bool restriction)
{
	if (myCounter == routeList.Count - 1)
	{
		myCounter = 1;

		while (routeList[myCounter]->getDiscovered())
			myCounter++;

		//myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
	else
	{
		myCounter++;

		while (routeList[myCounter]->getDiscovered())
		{
			myCounter++;

			if (myCounter >= routeList.Count)
				myCounter = 1;
		}

		//myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
}


int Vant::getNextUnvisitedID_withoutDeposit()
{
	//	whereIwas = routeList[myCounter]->getMyID();

	//while (routeList[myCounter]->getDiscovered())
	//{
	//	myCounter++;

	//	if (myCounter >= routeList.Count - 1)
	//		myCounter = 1;
	//}

	//myRWP = routeList[myCounter]->getMyLocation();
	//whereIamNow = routeList[myCounter]->getMyID();
	//
	//return routeList[myCounter]->getMyID();

	if (myCounter == routeList.Count - 1)
	{
		myCounter = 1;

		while (routeList[myCounter]->getDiscovered())
			myCounter++;

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
	else
	{
		myCounter++;

		while (routeList[myCounter]->getDiscovered())
		{
			myCounter++;

			if (myCounter >= routeList.Count)
				myCounter = 1;
		}

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
}




JustID ^ Vant::getRouteListByIndex(int index)
{
	return routeList[index];
}

bool Vant::getRouteListStateByIndex(int index)
{
	return routeList[index]->getCheckState();
}

bool Vant::getRouteListStateByID(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
		if (routeList[i]->getMyID() == ID)
			return routeList[i]->getCheckState();

	return false;
}

long Vant::getFlyTime()
{
	return myStopWatch->ElapsedMilliseconds;
}

void Vant::setRouteListStateByIndex(int index, bool state)
{
	routeList[index]->SetCheckState(state);
}

void Vant::setRouteListStateByID(int ID, bool state)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
		{
			routeList[i]->SetCheckState(state);
			break;
		}
	}
}

int Vant::getRouteListCount()
{
	return routeList.Count;
}

int Vant::getWhereIam()
{
	return routeList[myCounter]->getMyID();
}

int Vant::getWhereIGoingTo()
{
	return whereIgoingTo;
}

int Vant::getWhereIwas()
{
	return whereIwas;
}

int Vant::getRouteListIndexByID(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
			return i;
	}

	return -1;
}

void Vant::startMyStopWatch(bool start)
{
	if (start)
		myStopWatch->Restart();
	else
		myStopWatch->Stop();
}

bool Vant::getMyStart()
{
	return myStart;
}

void Vant::setMyStart(bool st)
{
	myStart = st;
}

void Vant::setActualTimeSlot(int ts)
{
	actualTimeSlot = ts;
}

int Vant::getActualTimeSlot()
{
	return actualTimeSlot;
}

void Vant::setRouteListIsDiscovered(int ID, int state, int ts)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if(ID == routeList[i]->getMyID())
		{
			routeList[i]->setDiscovered(state);
			routeList[i]->setMyTimeSlot(ts);
			routeList[i]->setMyOriginalTimeSlot(ts);
			break;
		}
	}
}

bool Vant::getRouteListIsDiscovered(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (ID == routeList[i]->getMyID())
			return routeList[i]->getDiscovered();
	}
}

void Vant::associateTimeSlotOnRouteList(int ID, int timeSlot)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
		{
			routeList[i]->setMyTimeSlot(timeSlot);
			break;
		}
	}
}

int Vant::getAssociatedTimeSlotOnRouteList(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
			return routeList[i]->getMyTimeSlot();
	}
}

int Vant::countDiscoveredSensorsOnRouteList()
{
	int counter = 0;

	for (unsigned int i = 1; i < routeList.Count; i++)
	{
		if (!routeList[i]->getDiscovered())
			counter++;
	}

	return counter;
}

JustID ^ Vant::getRouteListByTimeSlot(int ts)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyOriginalTimeSlot() == ts)
		{
			return routeList[i];
			break;
		}
	}
}

JustID ^ Vant::getRouteListBySensorID(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
		{
			return routeList[i];
			break;
		}
	}
}

int Vant::getIDByTimeSlot(int ts)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyTimeSlot() == ts)
		{
			return routeList[i]->getMyID();
			break;
		}
	}

	return -1;
}


JustID ^ Vant::getRouteListByTimeSlot2(int ts, bool reprogrammed)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyTimeSlot() == ts && routeList[i]->getIsReprogrammed() == reprogrammed)
			return routeList[i];
	}
}

int Vant::getNextIDByTimeSlot(int ts, bool reprogrammed)
{
	whereIwas = routeList[myCounter]->getMyID();
	routeList[myCounter]->setVisited(false);

	if (ts == routeList.Count - 2)
		ts = 0;
	else
		ts++;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		//here was myOriginalTimeSlot(), changed on 14/05/2019;
		if (routeList[i]->getMyTimeSlot() == ts)
		{
			//std::cout << std::endl << "index: " << i <<  " / ID: " << routeList[i]->getMyID() << " / TS: " << routeList[i]->getMyTimeSlot();
			myCounter = i;
			whereIamNow = routeList[myCounter]->getMyID();
			return routeList[i]->getMyID();
		}
	}

	return -1;
}


JustID ^ Vant::getNextTargetByTimeSlot(int ts, bool reprogrammed)
{
	whereIwas = routeList[myCounter]->getMyID();
	routeList[myCounter]->setVisited(false);

	if (ts == routeList.Count - 2)
		ts = 0;
	else
		ts++;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyTimeSlot() == ts && !reprogrammed)
		{
			myCounter = i;
			whereIamNow = routeList[myCounter]->getMyID();

			return routeList[i];
		}
	}
}

JustID ^ Vant::findClosestDistanceToDeposit()
{
	int distance = 99999;
	JustID ^ target = gcnew JustID();

	for (unsigned int i = 1; i < routeList.Count; i++)
	{
		if (getDistanceFromTo(routeList[i]->getMyLocation(), myFirstLocation) < distance)
		{
			distance = getDistanceFromTo(routeList[i]->getMyLocation(), myFirstLocation);
			target = routeList[i];
		}
	}

	return target;
}

bool Vant::getRouteListIsVisited(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
			return routeList[i]->getVisited();
	}

	return false;
}

void Vant::setRouteListIsVisited(int ID, bool state)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
			routeList[i]->setVisited(state);
		else
			routeList[i]->setVisited(!state);
	}
}



void Vant::setTimeSlotDiscovery(bool state)
{
	timeSlotDiscovery = state;
}

bool Vant::getTimeSlotDiscovery()
{
	return timeSlotDiscovery;
}

void Vant::setRouteListIsReprogrammed(int ID, bool state, int newTS)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
		{
			routeList[i]->setIsReprogrammed(state);
			routeList[i]->setMyTimeSlot(newTS);
			break;
		}
	}
}

bool Vant::getRouteListIsReprogrammed(int ID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == ID)
		{
			return routeList[i]->getIsReprogrammed();
		}
	}

	return true;
}


double Vant::getTimeFromTo(Point ^ p1, Point ^ p2)
{
	return 1000*(Convert::ToInt32(Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2))) / getMyRealSpeed());
}

double Vant::getTimeFromToByID(int IDfrom, int IDto, int readTime)
{
	int index1;
	int index2;
	int totalDistance = 0;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == IDfrom)
			index1 = i;

		if (routeList[i]->getMyID() == IDto)
			index2 = i;
	}

	if (index1 < index2)
		totalDistance = getDistanceFromTo(routeList[index1]->getMyLocation(), routeList[index2]->getMyLocation());
	else
	{
		if (index1 > index2)
			totalDistance = getDistanceFromTo(routeList[routeList.Count-1]->getMyLocation(), routeList[0]->getMyLocation());
		else
			totalDistance = 0;
	}

	return 1000 * (totalDistance / getMyRealSpeed()) + readTime;
}

double Vant::getTimeFromToByIndex(int indexFrom, int indexTo, int readTime)     
{
	//here
	int totalDistance = 0;

	if (indexFrom < indexTo)
		totalDistance = getDistanceFromTo(routeList[indexFrom]->getMyLocation(), routeList[indexTo]->getMyLocation());
	else
	{
		if (indexFrom > indexTo)
			totalDistance = getDistanceFromTo(routeList[routeList.Count - 1]->getMyLocation(), routeList[0]->getMyLocation());
		else
			totalDistance = 0;
	}

	return (1000 * (totalDistance / getMyRealSpeed()) + readTime);
}

double Vant::getTimeSlotsFromToByIndex(int indexFrom, int indexTo, int readTime, int timeSlotTime, int scrollSpeed)
{
	int totalDistance = 0;

	if (indexFrom < indexTo)
		totalDistance = getDistanceFromTo(routeList[indexFrom]->getMyLocation(), routeList[indexTo]->getMyLocation());
	else
	{
		if (indexFrom > indexTo)
			totalDistance = getDistanceFromTo(routeList[routeList.Count - 1]->getMyLocation(), routeList[0]->getMyLocation());
		else
			totalDistance = 0;
	}

	//std::cout << std::endl << "from: " << routeList[indexFrom]->getMyID() << " to " << routeList[indexTo]->getMyID() << " will take " << Math::Ceiling((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime) / timeSlotTime) << " timeslots";

	return Math::Ceiling((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime) / timeSlotTime);
}

//double Vant::getTotalTimeSlotsForRoute(int readTime, int timeSlotTime)
//{
//	int totalDistance = 0;
//	int TS = 0;
//
//	for(unsigned int i = 0; i < routeList.Count - 1; i++)
//	{
//		totalDistance = getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i+1]->getMyLocation());
//
//		TS += Math::Round((1000 * (totalDistance / getMyRealSpeed()) + readTime) / timeSlotTime);
//
//		//std::cout << std::endl << "from: " << routeList[i]->getMyID() << " to " << routeList[i+1]->getMyID() << " will take " << Math::Round((1000 * (totalDistance / getMyRealSpeed()) + readTime) / timeSlotTime) << " timeslots";
//	}
//
//	//back to Deposit calculation;
//	totalDistance = getDistanceFromTo(routeList[routeList.Count -1]->getMyLocation(), routeList[0]->getMyLocation());
//	TS += Math::Round((1000 * (totalDistance / getMyRealSpeed()) + readTime) / timeSlotTime);
//
//	//std::cout << std::endl << "from: " << routeList[routeList.Count - 1]->getMyID() << " to " << routeList[0]->getMyID() << " will take " << Math::Round((1000 * (totalDistance / getMyRealSpeed()) + readTime) / timeSlotTime) << " timeslots";
//
//	return TS;
//}

double Vant::getTotalTimeForRoute(int readTime, int scrollSpeed)
{
	int totalDistance = 0;
	int time = 0;

	for (unsigned int i = 0; i < routeList.Count - 1; i++)
	{
		totalDistance = getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i + 1]->getMyLocation());

		time += Math::Round((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime));

		//std::cout << std::endl << "from: " << routeList[i]->getMyID() << " to " << routeList[i + 1]->getMyID() << " will take " << Math::Round((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime));
		//std::cout << std::endl << "realSpeed: " << getMyRealSpeed(scrollSpeed);
		//std::cout << std::endl << "totalDistance: " << totalDistance;
	}

	//back to Deposit calculation;
	totalDistance = getDistanceFromTo(routeList[routeList.Count - 1]->getMyLocation(), routeList[0]->getMyLocation());
	time += Math::Round((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime));

	//std::cout << std::endl << "from: " << routeList[routeList.Count - 1]->getMyID() << " to " << routeList[0]->getMyID() << " will take " << Math::Round((1000 * (totalDistance / getMyRealSpeed(scrollSpeed)) + readTime));
	//std::cout << std::endl << "realSpeed: " << getMyRealSpeed(scrollSpeed);
	//std::cout << std::endl << "totalDistance: " << totalDistance;
	//
	//std::cout << std::endl << "totalTime: " << time;

	return time;
}



double Vant::getTotalTimeFromRouteList(int readTime)
{
	double totalTime = 0;

	for (unsigned int i = 0; i < routeList.Count - 1; i++)
	{
		totalTime += getTimeFromToByIndex(i, i + 1, readTime);
	}

	totalTime += getTimeFromToByIndex(routeList.Count - 1, 0, readTime);

	return totalTime;
}

int Vant::getTimeSlotsToID(int timeSlotTime, int nextID, int scrollSpeed)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == nextID)
			return (1000 * (getDistanceFromTo(getCenterLocation(), routeList[i]->getMyLocation()) / getMyRealSpeed(scrollSpeed)) / timeSlotTime);
	}
}

int Vant::gettTimeSlotsFromDepositUntillHere(int ID, int TSTime, int readTime)
{
	int counter = 0;
	int dist = 0;
	int timeSlots = 0;

	for (unsigned int i = 0; i < routeList.Count - 1; i++)
	{
		dist += getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i + 1]->getMyLocation());
		counter++;

		if (routeList[i+1]->getMyID() == ID)
			break;
	}

	//std::cout << std::endl << "distance from Deposit to " << ID << " is " << dist;

	timeSlots = Math::Ceiling(((1000 * dist / getMyRealSpeed()) + (counter * readTime)) / TSTime);

	//std::cout << std::endl << "timeSlots = " << timeSlots;

	while (timeSlotIsAlreadyUsed(timeSlots))
	{
		timeSlots++;
		//std::cout << std::endl << "#timeSlots = " << timeSlots;
	}

	//std::cout << std::endl << "$timeSlots = " << timeSlots;
	return timeSlots;
}

int Vant::getTimeSlotsFromToByID(int timeSlotTime, int IDfrom, int IDto, int readTime, bool goToDeposit) 
{
	int indexFrom, indexTo;
	int dist = 0;
	int counter = 0;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyID() == IDfrom)
			indexFrom = i;

		if (routeList[i]->getMyID() == IDto)
			indexTo = i;
	}

	if (indexFrom < indexTo)
	{
		for (unsigned int i = indexFrom; i < indexTo; i++)
		{
			dist += getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i + 1]->getMyLocation());
			counter++;
		}
	}
	else
	{
		if (indexFrom > indexTo)
		{
			for (unsigned int i = indexFrom; i < routeList.Count - 1; i++)
			{
				dist += getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i + 1]->getMyLocation());
				counter++;
			}

			for (unsigned int i = 0; i < indexTo; i++)
			{
				dist += getDistanceFromTo(routeList[i]->getMyLocation(), routeList[i + 1]->getMyLocation());
				counter++;
			}
		}
	}

	int timeSlots = Math::Round(((1000 *dist/ getMyRealSpeed()) + counter * readTime) / timeSlotTime);

	return timeSlots;
}




int Vant::getTimeSlotsUntillHere(int timeSlotTime, int here)
{
	int timeSlotsCount = 0;

	for (unsigned int i = 1; i <= routeList.Count; i++)
	{
		timeSlotsCount += Math::Round(1000 * (getDistanceFromTo(routeList[i-1]->getMyLocation(), routeList[i]->getMyLocation()) / getMyRealSpeed()) / timeSlotTime);

		if (here == routeList[i]->getMyID())
		{
			//std::cout << std::endl << "routeList[i]->getMyID(): " << routeList[i-1]->getMyID() << " - count: " << timeSlotsCount;
			return timeSlotsCount;
		}
	}

	return -1;
}



double Vant::getRouteTotalTime_forMicroTimeSlos(bool deposit, int readTime)     
{
	double totalTime = 0;

	for (unsigned int i = 0; i < routeList.Count - 1; i++)
	{
		totalTime += getTimeFromToByIndex(i, i + 1, readTime);
	}

	if(deposit)
		totalTime += getTimeFromToByIndex(routeList.Count - 1, 0, readTime);

	return totalTime;
}

void Vant::reconfigureTimeSlots()
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		routeList[i]->setMyOriginalTimeSlot(routeList[i]->getMyTimeSlot());
	}

	this->clearRestrictionLists();
}

int Vant::countUnprogrammedTimeSlots()
{
	int counter = 0;

	for (unsigned int i = 1; i < routeList.Count - 1; i++)
	{
		if (!routeList[i]->getIsReprogrammed())
			counter++;
	}

	return counter;
}

int Vant::countSensorsOnCluster(int cluster)
{
	int counter = 0;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyCluster() == cluster)
			counter++;
	}

	return counter;
}

int Vant::countDiscoveredSensorsOnCluster(int cluster)
{
	int counter = 0;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyCluster() == cluster)
		{
			if(routeList[i]->getDiscovered())
				counter++;
		}
	}

	return counter;
}

int Vant::getNextCluster(int qSensors)
{
	myCluster++;
	
	if (myCluster > getMaxCluster(qSensors))
		myCluster = 0;

	return myCluster;
}

int Vant::getMyCluster()
{
	if (myCluster == INVALID)
	{
		int bestDistance = 9999;

		for (unsigned int i = 1; i < routeList.Count; i++)
		{
			if (this->getDistanceFrom(routeList[i]->getMyLocation()) <= bestDistance) 
			{
				bestDistance = getDistanceFrom(routeList[i]->getMyLocation());
				myCluster = routeList[i]->getMyCluster();
			}
		}
	}

	return myCluster;
}

int Vant::getMaxCluster(int qSensors)
{
	int max = 0;

	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyCluster() > max)
			max = routeList[i]->getMyCluster();
	}

	return max;
}

int Vant::getNextUnvisitedOnCluster()
{
	//whereIwas = routeList[myCounter]->getMyID();

	//while (routeList[myCounter]->getDiscovered() || (routeList[myCounter]->getMyCluster() != myCluster))
	//{
	//	myCounter++;

	//	if (myCounter >= routeList.Count - 1)
	//		myCounter = 1;
	//}

	//myRWP = routeList[myCounter]->getMyLocation();
	//whereIamNow = routeList[myCounter]->getMyID();

	//return routeList[myCounter]->getMyID();




	if (myCounter == routeList.Count - 1)
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter = 0;

		while ((routeList[myCounter]->getDiscovered()) || (routeList[myCounter]->getMyCluster() != myCluster))
		{
			myCounter++;
		}

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
	else
	{
		whereIwas = routeList[myCounter]->getMyID();
		myCounter++;

		while ((routeList[myCounter]->getDiscovered()) || (routeList[myCounter]->getMyCluster() != myCluster))
		{
			myCounter++;

			if (myCounter >= routeList.Count)
				myCounter = 0;
		}

		myRWP = routeList[myCounter]->getMyLocation();
		whereIamNow = routeList[myCounter]->getMyID();

		return routeList[myCounter]->getMyID();
	}
}


int Vant::getWhereIamNow()
{
	return whereIamNow;
}

void Vant::incrementDistance(int dist)
{
	totalDistance += dist;
}

void Vant::setLabel(bool label)
{
	if (label)
	{
		myLabel->Visible = true;
		myLabel->Location = System::Drawing::Point(getX() + 25, getY() + 5);
	}
	else
	{
		myLabel->Visible = false;
	}
}

void Vant::setXY(int X, int Y)
{
	myPic->Location = System::Drawing::Point(X, Y);

	if (hasMessage())
		myMessageIcon->Location = System::Drawing::Point(getX() + 9, getY() + 15);

	if (myLabel->Visible)
		myLabel->Location = System::Drawing::Point(getX() + 25, getY() + 5);
}


void Vant::setMyDirX(int nDirX)
{
	myDirX = myDirX * nDirX;
}

void Vant::setMyDirY(int nDirY)
{
	myDirY = myDirY * nDirY;
}

Point ^ Vant::getNearestPoint(Point ^ target, int maxDistance)
{
	int distX, distY, myCx, myCy;
	double totalDistance;
	double angle;

	myCx = getcX(); 
	myCy = getcY();

	distX = target->X - myCx;
	distY = target->Y - myCy;

	totalDistance = Math::Round(Math::Sqrt((Math::Pow(distX, 2) + Math::Pow(distY, 2))));

	angle = Math::Atan2(distY, distX);

	Point ^ p = gcnew Point();

	if (totalDistance > maxDistance)
	{
		////p->X = Convert::ToInt32(myCx + (totalDistance - maxDistance + (mySpeed * 2))*Math::Cos(angle));
		////p->Y = Convert::ToInt32(myCy + (totalDistance - maxDistance + (mySpeed * 2))*Math::Sin(angle));

		p->X = Convert::ToInt32(myCx + (totalDistance - (maxDistance - (mySpeed * 2)))*Math::Cos(angle));
		p->Y = Convert::ToInt32(myCy + (totalDistance - (maxDistance - (mySpeed * 2)))*Math::Sin(angle));
	}
	else
	{
		p->X = myCx;
		p->Y = myCy;
	}

	myRWP = p;

	return p;
}

Point Vant::drawNearestPoint(Point ^ target, int maxDistance)
{
	int distX, distY, myCx, myCy;
	double totalDistance;
	double angle;

	myCx = getcX(); 
	myCy = getcY();

	distX = target->X - myCx;
	distY = target->Y - myCy;

	totalDistance = Math::Round(Math::Sqrt((Math::Pow(distX, 2) + Math::Pow(distY, 2))));

	angle = Math::Atan2(distY, distX);

	Point p;

	p.X = Convert::ToInt32(myCx + (totalDistance - maxDistance + (mySpeed * 2))*Math::Cos(angle));
	p.Y = Convert::ToInt32(myCy + (totalDistance - maxDistance + (mySpeed * 2))*Math::Sin(angle));

	return p;
}

void Vant::setMySpeed(int nVel)
{
	mySpeed = nVel;
}

void Vant::RandomStep()
{
	Point ^ oldLocation = myPic->Location;

	myX = myPic->Location.X;
	myY = myPic->Location.Y;
	totalDistance += mySpeed;
	mySteps--;

	myPic->Location = System::Drawing::Point((myX + myDirX * mySpeed), (myY + myDirY * mySpeed));
	
	totalDistance += (Math::Sqrt(Math::Pow(oldLocation->X - myX, 2) + Math::Pow(oldLocation->Y - myY, 2)));
	myRealSpeed = 1000 * (totalDistance / myStopWatch->ElapsedMilliseconds);

	if(hasMessage())
		myMessageIcon->Location = System::Drawing::Point(getX() + 9, getY() + 15);

	if (myLabel->Visible)
		myLabel->Location = System::Drawing::Point(getX() + 25, getY() + 5);
}

void Vant::nextStep(Point ^ target)
{
	float ix, iy, k, distX, distY;
	Point ^ oldLocation;

	distX = target->X - getCenterLocation().X;
	distY = target->Y - getCenterLocation().Y;

	k = Math::Max(Math::Abs(distX), Math::Abs(distY)) / (mySpeed);

	if (!double::IsNaN(k))
	{
		ix = distX / k;
		iy = distY / k;
	}
	else
	{
		ix = 1;
		iy = 1;
	}

	oldLocation = myPic->Location; 

	myPic->Location = System::Drawing::Point(Convert::ToInt32((myX + (ix * mySpeed))), Convert::ToInt32((myY + (iy * mySpeed))));

	totalDistance += Math::Sqrt(Math::Pow(oldLocation->X - myPic->Location.X, 2) + Math::Pow(oldLocation->Y - myPic->Location.Y, 2));

	myRealSpeed = 1000*(totalDistance / myStopWatch->ElapsedMilliseconds);

	if(hasMessage())
		myMessageIcon->Location = System::Drawing::Point(getX() + 9, getY() + 15);

	if (myLabel->Visible)
		myLabel->Location = System::Drawing::Point(getX() + 25, getY() + 5);
}

void Vant::setConnection(int conn, String ^ type)
{
	if (type == "UAV")
		myUAVConnections[conn] = true;
	else
		mySensorConnections[conn] = true;

	setLabel(true);
}

void Vant::clearConnection(int conn, String ^ type)
{
	if (type == "UAV")
		myUAVConnections[conn] = false;
	else
		mySensorConnections[conn] = false;

	setLabel(true);
}

bool Vant::isConnectedWith(int conn, String ^ type)
{
	if (type == "UAV")
		return myUAVConnections[conn];
	else
		return mySensorConnections[conn];
}

void Vant::setMyName(String ^ name)
{
	myName = name;
}

int Vant::isUAVConnected()
{
	int counter = 0;

	for (int i = 0; i < MAX_UAV; i++)
		if (myUAVConnections[i])
			counter++;

	return counter;
}

int Vant::isSensorConnected()
{
	int counter = 0;

	for (int i = 0; i < MAX_SENSOR; i++)
		if (mySensorConnections[i])
			counter++;

	return counter;
}

void Vant::setNewDirection(int dir)
{
	switch (dir)
	{
	case 1: //NE
		myDirX = +1;
		myDirY = -1;
		break;

	case 2: // E
		myDirX = +1;
		myDirY = 0;
		break;

	case 3: //SE
		myDirX = +1;
		myDirY = +1;
		break;

	case 4: //S
		myDirX = 0;
		myDirY = +1;
		break;

	case 5: //SW
		myDirX = -1;
		myDirY = +1;
		break;

	case 6: //W
		myDirX = -1;
		myDirY = 0;
		break;

	case 7: //NW
		myDirX = -1;
		myDirY = -1;
		break;

	case 8: //N
		myDirX = 0;
		myDirY = -1;
		break;
	}
}

void Vant::setRandDirection(int max_steps, bool randSpeed)
{
	Random ^ rand = gcnew Random();
	mySteps = rand->Next(max_steps);

	switch (getMyDirection())
	{
	case 1: //CASE NE
		if (rand->Next(1, 4) >= 3)
			setNewDirection(8);
		else
			setNewDirection(2);
		break;

	case 2: //CASE E
		if (rand->Next(1, 4) >= 3)
			setNewDirection(1);
		else
			setNewDirection(3);
		break;

	case 3: //CASE SE
		if (rand->Next(1, 4) >= 3)
			setNewDirection(2);
		else
			setNewDirection(4);
		break;

	case 4: //CASE S
		if (rand->Next(1, 4) >= 3)
			setNewDirection(3);
		else
			setNewDirection(5);
		break;

	case 5: //CASE SW
		if (rand->Next(1, 4) >= 3)
			setNewDirection(4);
		else
			setNewDirection(6);
		break;

	case 6: //CASE W
		if (rand->Next(1, 4) >= 3)
			setNewDirection(5);
		else
			setNewDirection(7);
		break;

	case 7: // CASE NW
		if (rand->Next(1, 4) >= 3)
			setNewDirection(6);
		else
			setNewDirection(8);
		break;

	case 8: // CASE N
		if (rand->Next(1, 4) >= 3)
			setNewDirection(7);
		else
			setNewDirection(1);
		break;
	}
}

int Vant::getMySteps()
{
	return mySteps;
}

void Vant::setMySteps(int i)
{
	mySteps += i;
}


void Vant::setMyRWP(Point ^ p)
{
	myRWP = p;
}

void Vant::writeMessage(String ^ msg)
{
	myMessages += msg;
}

void Vant::setlastMsgFrom(String ^ i)
{
	lastMsgFrom = i;
}

String ^ Vant::getlastMsgFrom()
{
	return lastMsgFrom;
}

String ^ Vant::getMyName()
{
	return myName;
}

bool Vant::checkCollision(System::Windows::Forms::Panel ^ sa, int distance)
{
	switch (getMyDirection())
	{
	case 1:
		if ((myX >= (sa->Width - distance) || myY <= distance))
		{
			return true;
		}
		else
			return false;

	case 2:
		if (myX >= (sa->Width - distance))
		{
			return true;
		}
		else
			return false;

	case 3:
		if ((myX >= (sa->Width - distance) || myY > sa->Height - distance))
		{
			return true;
		}
		else
			return false;

	case 4:
		if (myY > (sa->Height - distance))
		{
			return true;
		}
		else
			return false;

	case 5:
		if (myX <= distance || myY > sa->Height - distance)
		{
			return true;
		}
		else
			return false;

	case 6:
		if (myX <= distance)
		{
			return true;
		}
		else
			return false;

	case 7:
		if (myX <= distance || myY <= distance)
		{
			return true;

		}
		else
			return false;

	case 8:
		if (myY <= distance)
		{
			return true;
		}
		else
			return false;
	}

	return true;
}

bool Vant::isMyTimerEnabled()
{
	return myTimer->Enabled;
}

//revisado, OK;
int Vant::getMyDirection()
{
	Random ^ rand = gcnew Random();

	if (myDirX == 0 && myDirY == 0)
		return rand->Next(1, 8);
	else
	{
		//NE
		if (myDirX == 1 && myDirY == -1)
			return 1;

		//E
		if (myDirX == 1 && myDirY == 0)
			return 2;

		//SE
		if (myDirX == 1 && myDirY == 1)
			return 3;

		//S
		if (myDirX == 0 && myDirY == 1)
			return 4;

		//SW
		if (myDirX == -1 && myDirY == 1)
			return 5;

		//W
		if (myDirX == -1 && myDirY == 0)
			return 6;

		//NW
		if (myDirX == -1 && myDirY == -1)
			return 7;

		//N
		if (myDirX == 0 && myDirY == -1)
			return 8;
	}

	return 0;
}

int Vant::countMessages()
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

double Vant::getDistanceFrom(System::Drawing::Point ^ p)
{
	return Math::Sqrt((Math::Pow(getcX() - p->X, 2) + Math::Pow(getcY() - p->Y, 2)));
}

double Vant::getDistanceFrom(Vant ^ v)
{
	return Math::Sqrt((Math::Pow(getcX() - v->getcX(), 2) + Math::Pow(getcY() - v->getcY(), 2)));
}

double Vant::getDistanceFromTo(Point ^ p1, Point ^ p2)
{
	return Convert::ToInt32(Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2)));
}

double Vant::getDistanceFromCenter(Point ^ p)
{
	return Math::Sqrt((Math::Pow((getcX()) - p->X, 2) + Math::Pow((getcY()) - p->Y, 2)));
}

bool Vant::isInsideRange(Point ^ target)
{
	if (getDistanceFromCenter(target) < mySpeed*2)
		return true;
	else
		return false;
}

bool Vant::isAtTarget2(Point ^ p)
{
	if (getCenterLocation2() == p)
		return true;
	else
		return false;
}

void Vant::insertRoute(Sensor ^ s, int position)
{
	myRoute[position] = s;
}

void Vant::setFly(Point ^ p)
{
	myFly[myCounter] = p;
	myCounter++;
}

int Vant::getTimeFromDistance(int distance)
{
	if (totalDistance == 0 || myStopWatch->ElapsedMilliseconds == 0)
		return 215;
	else
		return (1000 * (distance / myStopWatch->ElapsedMilliseconds));
}

int Vant::getConnectedWithSensorNow()
{
	return connectedWithSensorNow;
}

void Vant::setLastTarget(Point ^ p)
{
	myLastTarget = p;
}

Point ^ Vant::getLastTarget()
{
	return myLastTarget;
}

Point ^ Vant::getFly(int pos)
{
	if (myFly[pos] == nullptr)
		return myFly[pos-1];
	else
		return myFly[pos];
}
  
Point ^ Vant::getNextFly(int maxSensor)
{
	if (myCounter >= maxSensor)
	{
		myCounter = 0;
		myRWP = myFirstLocation;
	}
	else
	{
		myRWP = myFly[myCounter];
		myCounter++;
	}

	return myRWP;
}

Point ^ Vant::getNextHibridFly(int maxSensor)
{
	if (myCounter >= maxSensor)
	{
		myCounter = 0;
		myRWP = myFirstLocation;
	}
	else
	{
		myRWP = myHibridFly[myCounter];
		myCounter++;
	}

	return myRWP;
}

void Vant::setHibridFly(Point ^ p)
{
	myHibridFly[myCounter] = p;
	myCounter++;
}

Point ^ Vant::getHibridFly(int pos)
{
	if (myHibridFly[pos] == nullptr)
		return myHibridFly[pos - 1];
	else
		return myHibridFly[pos];
}


void Vant::timerTick(System::Object ^ sender, System::EventArgs ^ e)
{
	mySpeed = myOldSpeed;
	//myStopWatch->Start();
	myTimer->Enabled = false;
}


double Vant::getNearestDistance(Point ^ p, int maxDistance)
{
	Point ^ target = getNearestPoint(p, maxDistance);
	return getDistanceFrom(target);
}

void Vant::standBy(int time)
{
	Random ^ rand = gcnew Random();

	if (mySpeed == MIN_SPEED)
		myOldSpeed = 2;
	else
		myOldSpeed = mySpeed;

	//myStopWatch->Stop();

	setMySpeed(MIN_SPEED);
	myTimer->Interval = time;
	myTimer->Enabled = true;

	//switch (rand->Next(4))
	//{
	//	case 0: //up
	//		flyUp();
	//		flyDown();
	//		flyDown();
	//		flyUp();
	//		break;

	//	case 1: //down
	//		flyDown();
	//		flyUp();
	//		flyUp();
	//		flyDown();
	//		break;

	//	case 2: //left
	//		flyLeft();
	//		flyRight();
	//		flyRight();
	//		flyLeft();
	//		break;

	//	case 3: //right
	//		flyRight();
	//		flyLeft();
	//		flyLeft();
	//		flyRight();
	//		break;
	//}
}

void Vant::addTotalDistance(int add)
{
	totalDistance += add;
}

void Vant::setMyTotalDistance(double value)
{
	totalDistance = value;
}

void Vant::setRandomSpeed()
{
	Random ^ rand = gcnew Random();
	mySpeed = rand->Next(MIN_SPEED, MAX_SPEED);

	if (mySpeed == MIN_SPEED)
		standBy(rand->Next(MIN_STOP, MAX_STOP));
}

Point ^ Vant::getMyRWP()
{
	return myRWP;
}

Point Vant::getCenterLocation()
{
	Point p;

	p.X = myPic->Location.X + (myPic->Size.Width / 2);
	p.Y = myPic->Location.Y + (myPic->Size.Height/ 2);

	return p;
}

Point ^ Vant::getCenterLocation2()
{
	Point ^ p = gcnew Point();

	p->X = myPic->Location.X + (myPic->Size.Width / 2);
	p->Y = myPic->Location.Y + (myPic->Size.Height / 2);

	return p;
}

Point ^ Vant::setNewRWP(System::Windows::Forms::Panel ^ sa)
{
	Random ^ rand = gcnew Random();
	Point ^ p = gcnew Point();

	p->X = rand->Next(sa->Width);
	p->Y = rand->Next(sa->Height);

	myRWP = p;

	return p;
}

Point ^ Vant::getMyFirstLocation()
{
	return myFirstLocation;
}

void Vant::setMyFirstLocation(Point ^ p)
{
	myFirstLocation = p;
}

Sensor ^ Vant::getRoute(int position)
{
	return myRoute[position];
}

Point ^ Vant::getTarget(int index)
{
	return myTargets[index];
}

Point ^ Vant::getNextTarget(int MaxSensor)
{
	myCounter++;

	if (myCounter == MaxSensor)
		myCounter = 0;

	return myTargets[myCounter];
}

void Vant::setNewTarget(int index, Point ^ p)
{
	if(index == 99)
		myTargets[myCounter] = p;
	else
		myTargets[index] = p;
}

void Vant::setNewRWP2(System::Windows::Forms::Panel ^ sa)
{
	Random ^ rand = gcnew Random();
	Point ^ p = gcnew Point();

	p->X = rand->Next(sa->Width);

	Thread::Sleep(25);

	p->Y = rand->Next(sa->Height);

	myRWP = p;
}

Label ^ Vant::getmyLabel()
{
	return myLabel;
}

Vant::~Vant() { }

JustID::JustID()
{}

void JustID::setMyID(int ID)
{
	myID = ID;
}

void JustID::setMyLocation(Point ^ p)
{
	myLocation = p;
}

void JustID::SetCheckState(bool state)
{
	checkState = state;
}

void JustID::setVisited(bool state)
{
	isVisited = state;
}

void JustID::setMyCluster(int cluster)
{
	myCluster = cluster;
}

int JustID::getMyCluster()
{
	return myCluster;
}

bool JustID::getVisited()
{
	return isVisited;
}

bool JustID::getCheckState()
{
	return checkState;
}

bool JustID::getDiscovered()
{
	return isDiscovered;
}

void JustID::setDiscovered(bool state)
{
	isDiscovered = state;
}

void JustID::setMyTimeSlot(int ts)
{
	myTimeSlot = ts;
}

void JustID::setIsReprogrammed(bool state)
{
	isReprogrammed = state;
}

bool JustID::getIsReprogrammed()
{
	return isReprogrammed;
}

int JustID::getMyTimeSlot()
{
	return myTimeSlot;
}

int JustID::getMyID()
{
	return myID;
}

int JustID::getMyOriginalTimeSlot()
{
	return myOriginalTimeSlot;
}

int JustID::getTimeSlotsUntillHere()
{
	return timeSlotsUntillHere;
}

void JustID::setTimeSlotsUntillHere(int TS)
{
	timeSlotsUntillHere = TS;
}

void JustID::setMyOriginalTimeSlot(int ts)
{
	myOriginalTimeSlot = ts;
}


Point ^ JustID::getMyLocation()
{
	return myLocation;
}


JustID::~JustID()
{}

bool Vant::isThereRestriction(int TS, int ID)
{
	for(unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if(myRestrictions[i]->getMyTimeSlot() == TS)
		{
			return myRestrictions[i]->findRestriction(ID);
		}
	}
}

bool Vant::isTherePermission(int TS, int ID)
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
		{
			return myRestrictions[i]->findPermission(ID);
		}
	}
}

bool Vant::addRestriction(int TS, int ID)
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
		{
			if (myRestrictions[i]->findPermission(ID))
				myRestrictions[i]->removePermission(ID);
		}
	}

	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if(myRestrictions[i]->getMyTimeSlot() == TS)
		{
			if (!myRestrictions[i]->findRestriction(ID))
			{
				myRestrictions[i]->setNewRestriction(ID);
				return true;
			}
		}
	}

	return false;
}

void Vant::addTimeSlotToRestrictions(int TS, int qSensors)
{
	bool block = true;

	for(unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
			block = false;
	}

	if(block)
	{
		Restrictions ^ rr = gcnew Restrictions();
		rr->setTimeSlot(TS);

		for (unsigned int i = 0; i < qSensors; i++)
		{
			rr->setNewPermission(i);
		}

		myRestrictions.Add(rr);
	}

}

String ^ Vant::getRestrictionsOnTimeSlot(int TS)
{
	String ^ s;

	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if(myRestrictions[i]->getMyTimeSlot() == TS)
		{
			for (unsigned int j = 0; j < myRestrictions[i]->restrictedSensorsCount(); j++)
			{
				s += "S" + myRestrictions[i]->getRestrictedSensorsOnIndex(j).ToString() + " ";
			}
		}
	}

	return s;
}

String ^ Vant::getPermissionOnTimeSlot(int TS)
{
	String ^ s;

	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
		{
			for (unsigned int j = 0; j < myRestrictions[i]->permitedSensorsCount(); j++)
			{
				s += "S" + myRestrictions[i]->getPermissionSensorOnIndex(j).ToString() + " ";
			}
		}
	}

	return s;
}

List<int>^ Vant::getListPermitedSensorsOnTimeSlot(int TS)
{
	List<int> ^ retList = gcnew List<int>();

	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
		{
			for (unsigned int j = 0; j < myRestrictions[i]->permitedSensorsCount(); j++)
			{
				retList->Add(myRestrictions[i]->getPermissionSensorOnIndex(j));
			}
		}
	}

	return retList;
}

List<int>^ Vant::getListUnvisitedTargets()
{
	List<int> ^ retList = gcnew List<int>();

	for (unsigned int i = 1; i < routeList.Count; i++)
	{
		if (!routeList[i]->getDiscovered())
			retList->Add(routeList[i]->getMyID());
	}

	return retList;
}

String ^ Vant::getListUnvisitedTargetsOnString()
{
	String ^ s;

	for (unsigned int i = 1; i < routeList.Count; i++)
	{
		if (!routeList[i]->getDiscovered())
			s += "S" + routeList[i]->getMyID() + " ";
	}

	return s;
}

Restrictions ^ Vant::getRestrictionByIndex(int index)
{
	return myRestrictions[index];
}

void Vant::removeIDfromPermissionLists(int ID)
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		myRestrictions[i]->removePermission(ID);
		
		if(!myRestrictions[i]->findRestriction(ID))
			myRestrictions[i]->setNewRestriction(ID);
	}


}


void Vant::clearRestrictionsOnTimeSlot(int TS)
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
		{
			myRestrictions[i]->clearRestrictedTimeSlots();
		}
	}
}

void Vant::clearRestrictionLists()
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		myRestrictions[i]->clearAllLists();
	}
}

void Vant::clearALLrestrictionsForReset()
{
	myRestrictions.Clear();
}

void Vant::addDecisionCounter()
{
	decisions++;
}

int Vant::getDecisionCounter()
{
	return decisions;
}

int Vant::getNextUndiscoveredIDbyTimeSlot(int actualTS, int qTS)
{
	int nextTS = actualTS;
	whereIwas = whereIamNow;

	while (true)
	{
		if (nextTS + 1 >= qTS)
			nextTS = 0;
		else
			nextTS++;

		for (unsigned int i = 0; i < routeList.Count; i++)
		{
			if (routeList[i]->getMyTimeSlot() == nextTS && routeList[i]->getDiscovered())
				if(getListPermitedSensorsOnTimeSlot(actualTS)->Contains(routeList[i]->getMyID()))
					return routeList[i]->getMyID();
		}
	}
}

int Vant::getNextIDbyTimeSlot(int actualTS, int qTS)
{
	int nextTS;

	nextTS = actualTS;
	whereIwas = whereIamNow;

	while (true)
	{
		if (nextTS + 1 >= qTS - 1)
			nextTS = 0;
		else
			nextTS++;

		for (unsigned int i = 0; i < routeList.Count; i++)
		{
			if (routeList[i]->getMyTimeSlot() == nextTS)
			{
				whereIamNow = routeList[i]->getMyID();
				return whereIamNow;
			}
		}
	}
}

int Vant::getNextIDbyMicroTimeSlot(int actualTS, int qTS, int actualID)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyTimeSlot() == actualTS)
		{
			if (i < routeList.Count - 1)
			{
				return routeList[i + 1]->getMyID();
			}
			else
			{
				return routeList[0]->getMyID();
			}
		}
	}
}

void Vant::copyRoutingParametersFromUAV(Vant ^ v, int qTS)
{
	for(unsigned int i = 0; i < v->getRouteListCount(); i++)
	{
		if(!routeList.Contains(v->getRouteListByIndex(i)))
			routeList.Add(v->getRouteListByIndex(i));
	}

	for(unsigned int i = 0; i < qTS; i++)
	{
		if (!myRestrictions.Contains(v->getRestrictionByIndex(i)))
			myRestrictions.Add(v->getRestrictionByIndex(i));
	}

	myCounter = v->getMyCounter();
}

bool Vant::timeSlotIsAlreadyUsed(int TS)
{
	for (unsigned int i = 0; i < routeList.Count; i++)
	{
		if (routeList[i]->getMyOriginalTimeSlot() == TS)
			return true;
	}

	return false;
}

bool Vant::isTimeSlotProgrammedOnRestrictionList(int TS)
{
	for (unsigned int i = 0; i < myRestrictions.Count; i++)
	{
		if (myRestrictions[i]->getMyTimeSlot() == TS)
			return true;
	}

	return false;
}

bool Vant::isActive()
{
	return active;
}

void Vant::setActive(bool state)
{
	active = state;

	//if (!state)
	//	myStopWatch->Stop();
	//else
	//	myStopWatch->Start();
}


int Vant::getRouteTotalDistance()
{
	return routeTotalDistance;
}

void Vant::setRouteTotalDistance(int dist)
{
	routeTotalDistance = dist;
}

void Vant::addHopCounter()
{
	hops++;
}

int Vant::getHopsCounter()
{
	return hops;
}


void Restrictions::setTimeSlot(int TS)
{
	myTimeSlot = TS;
}

int Restrictions::getMyTimeSlot()
{
	return myTimeSlot;
}

int Restrictions::restrictedSensorsCount()
{
	return restrictedSensors.Count;
}

int Restrictions::permitedSensorsCount()
{
	return permitedSensors.Count;
}

int Restrictions::getRestrictedSensorsOnIndex(int index)
{
	return restrictedSensors[index];
}

int Restrictions::getPermissionSensorOnIndex(int index)
{
	return permitedSensors[index];
}

void Restrictions::setNewRestriction(int ID)
{
	restrictedSensors.Add(ID);
}

void Restrictions::setNewPermission(int ID)
{
	permitedSensors.Add(ID);
}

void Restrictions::clearRestrictedTimeSlots()
{
	restrictedSensors.Clear();
}

Restrictions::~Restrictions()
{
	throw gcnew System::NotImplementedException();
}

bool Restrictions::findRestriction(int ID)
{
	for (unsigned int i = 0; i < restrictedSensors.Count; i++)
	{
		if (restrictedSensors[i] == ID)
			return true;
	}

	return false;
}

bool Restrictions::findPermission(int ID)
{
	for (unsigned int i = 0; i < permitedSensors.Count; i++)
	{
		if (permitedSensors[i] == ID)
			return true;
	}

	return false;
}

bool Restrictions::removePermission(int ID)
{
	for (unsigned int i = 0; i < permitedSensors.Count; i++)
	{
		if (permitedSensors[i] == ID)
		{
			permitedSensors.RemoveAt(i);
			return true;
		}
	}
	
	return false;
}

void Restrictions::clearAllLists()
{
	restrictedSensors.Clear();
	permitedSensors.Clear();
}

