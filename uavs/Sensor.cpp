#include "Sensor.h"

#include <stdlib.h>
#include <iostream>

Sensor::Sensor()
{
}

Sensor::~Sensor()
{
}

Sensor::Sensor(int ID, System::Windows::Forms::Panel ^ sa)
{
	myID = ID;
	myState = true;
	visited = false;
	onGrid = false;
	timerAdjusted = false;
	discovered = false;
	blocked = false;
	timeSlotReprogrammed = false;

	Random ^ rand = gcnew Random();
	Point p;

	myCluster = 0;
	myCounter = 0;
	lostUAVcounter = 0;

	myTimeSlot = -1;
	myOriginalTimeSlot = -1;

	myDelay = 1;
	myBCTime = 0;
	mySleepingTime = 0;

	myTimer = gcnew System::Windows::Forms::Timer;
	myTimer->Tick += gcnew System::EventHandler(this, &Sensor::timerTick);
	myTimer->Interval = myDelay;
	myTimer->Enabled = false;

	myPic = gcnew System::Windows::Forms::PictureBox();
	myPic->Tag = "S" + myID.ToString();
	myPic->Image = Image::FromFile("Images\\s1bc.png");

	myPic->SizeMode = PictureBoxSizeMode::AutoSize;

	p.X = rand->Next(myPic->Size.Width, sa->Width - myPic->Size.Width);
	Thread::Sleep(50);
	p.Y = rand->Next(myPic->Size.Height, sa->Height - myPic->Size.Height);

	myPic->Location = p;

	myLabel->Text = myID.ToString();
	myLabel->Location = System::Drawing::Point(p.X + 15, p.Y + 10);
	myLabel->Visible = true;
	myLabel->AutoSize = true;
	myLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

	System::Drawing::Drawing2D::GraphicsPath ^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddEllipse(0, 0, myPic->Width, myPic->Height);
	Region ^ rg = gcnew Region(gp);
	myPic->Region = rg;
	myName = "S" + myID.ToString();
	lastMsgFrom = myName;

	myMessageIcon = gcnew PictureBox();
	myMessageIcon->Image = Image::FromFile("Images\\message.png");
	myMessageIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
	myMessageIcon->Size = System::Drawing::Size(12, 12);
	myMessageIcon->Tag = "m" + myID.ToString();
	myMessages = "";

	setMyState(true);
	setLabel(true);

	sa->Controls->Add(myLabel);
	sa->Controls->Add(myPic);
	sa->Controls->Add(myMessageIcon);
}

Sensor::Sensor(int ID, System::Windows::Forms::Panel ^ sa, Point ^ initLocation)
{
	myID = ID;
	myState = true;
	visited = false;
	discovered = false;
	blocked = false;
	timeSlotReprogrammed = false;

	Random ^ rand = gcnew Random();
	Point p;

	myCluster = 0;
	myCounter = 0;
	lostUAVcounter = 0;

	myTimeSlot = -1;
	myOriginalTimeSlot = -1;

	myDelay = 1;
	myBCTime = 0;
	mySleepingTime = 0;

	myTimer = gcnew System::Windows::Forms::Timer;
	myTimer->Tick += gcnew System::EventHandler(this, &Sensor::timerTick);
	myTimer->Enabled = false;

	myPic = gcnew System::Windows::Forms::PictureBox();
	myPic->Tag = "S" + myID.ToString();
	myPic->Image = Image::FromFile("Images\\s1bc.png");

	myPic->SizeMode = PictureBoxSizeMode::AutoSize;
	myPic->Location = (Point) initLocation;

	myLabel->Text = myID.ToString();
	myLabel->Location = System::Drawing::Point(p.X + 15, p.Y + 10);
	myLabel->Visible = true;
	myLabel->AutoSize = true;
	myLabel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 7, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));

	System::Drawing::Drawing2D::GraphicsPath ^ gp = gcnew System::Drawing::Drawing2D::GraphicsPath();
	gp->AddEllipse(0, 0, myPic->Width, myPic->Height);
	Region ^ rg = gcnew Region(gp);
	myPic->Region = rg;
	myName = "S" + myID.ToString();
	lastMsgFrom = myName;

	myMessageIcon = gcnew PictureBox();
	myMessageIcon->Image = Image::FromFile("Images\\message.png");
	myMessageIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
	myMessageIcon->Size = System::Drawing::Size(12, 12);
	myMessageIcon->Tag = "m" + myID.ToString();
	myMessages = "";

	setMyState(true);
	setLabel(true);

	sa->Controls->Add(myLabel);
	sa->Controls->Add(myPic);
	sa->Controls->Add(myMessageIcon);
}


void Sensor::timerTick(System::Object ^ sender, System::EventArgs ^ e)
{
	if(!blocked)
	{
		if (myTimer->Interval == myReadTime)
		{
			myTimer->Interval = mySleepingTime;
			myStopwatch->Restart();
			this->setMyState(false);
		}
		else
		{
			if (myTimer->Interval == myBCTime && getMyState())
			{
				myTimer->Interval = mySleepingTime;
				myStopwatch->Restart();
				this->setMyState(false);
			}
			else
			{
				myTimer->Interval = myBCTime;
				myStopwatch->Restart();
				this->setMyState(true);
			}
		}
	}
	else
	{
		if (myTimer->Interval == myReadTime)
		{
			myTimer->Interval = mySleepingTime;
			this->setMyState(false);
			myStopwatch->Restart();

			if (myReadTime != myOriginalReadTime)
				myReadTime = myOriginalReadTime;
		}
		else
		{
			if (myTimer->Interval == mySleepingTime)
			{
				if (myBCTime > 0)
					myTimer->Interval = myBCTime;
				else
					myTimer->Interval = 1;

				myStopwatch->Restart();
				this->setMyState(true);

				if (mySleepingTime != myOriginalSleepingTime)
					mySleepingTime = myOriginalSleepingTime;
			}
			else
			{
				if (myTimer->Interval == myBCTime)
				{
					myTimer->Interval = mySleepingTime;
					myStopwatch->Restart();
					this->setMyState(false);

					if (myBCTime != myOriginalBCTime)
						myBCTime = myOriginalBCTime;
				}
			}
		}
	}
}

void Sensor::setSensorToSleepOnTimeSlot()
{
	timeDifference = 0;
	blocked = true;

	if (myReadTime != myOriginalReadTime)
		myReadTime = myOriginalReadTime;

	if (mySleepingTime != myOriginalSleepingTime)
		mySleepingTime = myOriginalSleepingTime;

	timeDifference = this->getBCleftTime();

	if (timeDifference <= 1)
		timeDifference = 1;

	if (timeDifference > myReadTime)
		mySleepingTime += (timeDifference - myReadTime);
	else
		myReadTime = timeDifference;

	myTimer->Interval = myReadTime;
	myTimer->Start();
}

bool Sensor::isTimeSlotReprogrammed()
{
	return timeSlotReprogrammed;
}

void Sensor::setMyTimeSlot(int ts, int qSensors)
{
	//blocked = true;
	myTimeSlot = ts;
	myOriginalTimeSlot = ts;
	//myDelay = (1000 * myTimeSlot*qSensors) + 1;

	//myStopwatch->Restart();
	//myTimer->Interval = myDelay;
	//myTimer->Enabled = true;
	//myTimer->Start();
	//this->setMyState(false);
}


void Sensor::setTImeSlotReprogrammed(bool state)
{
	timeSlotReprogrammed = state;
}

void Sensor::setMyTimeSlotTimers(int BCTime, int SleepTime, int timeSlot, int qSensors)
{
	myBCTime = BCTime;
	myOriginalBCTime = BCTime;
	myOriginalSleepingTime = SleepTime;
	
	mySleepingTime = SleepTime;
	myTimeSlot = timeSlot;

	myDelay = (1000 * myTimeSlot*qSensors) + 1;

	if (myBCTime == 0 && mySleepingTime == 0)
	{
		myStopwatch->Stop();
		myTimer->Enabled = false;
		myTimer->Stop();
		this->setMyState(true);
	}
	else
	{
		myStopwatch->Restart();
		myTimer->Interval = myDelay;
		myTimer->Enabled = true;
		myTimer->Start();
		this->setMyState(false);
	}
}

void Sensor::setMyMicroTimeSlotTimers_toSleep(int newTS, int microTStime, int qTimeSlots, int sleepTime, int BCTime, int BCtimeSlots, int readTime)
{
	int diffTimeSlot;
	diffTimeSlot = 0;

	timeSlotReprogrammed = true;
	blocked = true;
	
	myOriginalTimeSlot = myTimeSlot;

	myBCTime = BCTime;
	mySleepingTime = sleepTime;
	myReadTime = readTime;

	if (newTS != myTimeSlot)
	{
		if (newTS > myTimeSlot)
			diffTimeSlot = newTS - (myTimeSlot + BCtimeSlots);
		else
			diffTimeSlot = qTimeSlots - (myTimeSlot + BCtimeSlots) + newTS;
	}
	else
		diffTimeSlot = qTimeSlots - BCtimeSlots;

	myTimeSlot = newTS;

	if(diffTimeSlot > 0)
	{
		mySleepingTime = Math::Abs(diffTimeSlot * microTStime) + 1;
		timeDifference = this->getBCleftTime();

		if (timeDifference <= 1)
			timeDifference = 1;

		if (timeDifference > myReadTime)
			mySleepingTime += (timeDifference - myReadTime);
		else
			myReadTime = timeDifference;

		myTimer->Interval = myReadTime;

	}
	else
	{
		timeDifference = this->getBCleftTime();

		if (BCtimeSlots > 1)
		{
			if (timeDifference > microTStime + readTime)
			{
				if (timeDifference > myReadTime + microTStime)
					mySleepingTime = timeDifference - myReadTime - microTStime;
				else
					myReadTime = timeDifference;
			}
			else
			{
				if (timeDifference > myReadTime)
					mySleepingTime = timeDifference - myReadTime;
				else
					myReadTime = timeDifference;
			}
		}
		else
		{
			if (timeDifference > myReadTime)
				mySleepingTime = timeDifference - myReadTime;
			else
				myReadTime = timeDifference;
		}

		myTimer->Interval = myReadTime;
	}

	myTimer->Start();
}

void Sensor::setMyMicroTimeSlotTimers(int myTS, int microTStime, int sleepTime, int BCTime)
{
	//inserted for microTimeSlots;
	myTimeSlot = myTS;
	
	myBCTime = BCTime;
	myOriginalBCTime = BCTime;
	
	mySleepingTime = sleepTime;
	myOriginalSleepingTime = sleepTime;
	
	myDelay = (myTS * microTStime) + 1;
	blocked = false;

	if (myBCTime == 0 && mySleepingTime == 0)
	{
		myStopwatch->Stop();
		myTimer->Enabled = false;
		myTimer->Stop();
		this->setMyState(true);
	}
	else
	{
		myStopwatch->Restart();
		myTimer->Interval = myDelay;
		myTimer->Enabled = true;
		myTimer->Start();
		this->setMyState(false);
	}

}

void Sensor::setMyTimeSlotTimers2(int BCTime, int SleepTime, int readTime, int timeSlot, int qSensors)
{
	int diffTimeSlot;
	diffTimeSlot = 0;
	
	timeSlotReprogrammed = true;
	blocked = true;

	myBCTime = BCTime;
	mySleepingTime = SleepTime;
	myReadTime = readTime;

	if (timeSlot != myTimeSlot)
	{
		if (timeSlot > myTimeSlot)
			diffTimeSlot = timeSlot - myTimeSlot - 1;
		else
			diffTimeSlot = (qSensors - myTimeSlot - 1) + timeSlot;
	}
	else
		diffTimeSlot = qSensors - 1;
	
	myTimeSlot = timeSlot;

	mySleepingTime = (diffTimeSlot * (1000 * qSensors)) + 1;

	timeDifference = this->getBCleftTime();

	if (timeDifference <= 1)
		timeDifference = 1;

	if (timeDifference > myReadTime)
		mySleepingTime += (timeDifference - myReadTime);
	else
		myReadTime = timeDifference;

	myTimer->Interval = myReadTime;
	myTimer->Start();
}


void Sensor::setMyTimers1(int BCTime, int SleepTime)
{
	myBCTime = BCTime;
	mySleepingTime = SleepTime;
	blocked = false;

	if (myBCTime == 0 && mySleepingTime == 0)
	{
		myTimer->Enabled = false;
		myTimer->Stop();
		myStopwatch->Stop();
		this->setMyState(true);
	}
	else
	{
		myTimer->Interval = myBCTime;
		myTimer->Enabled = true;
		myTimer->Start();
		myStopwatch->Restart();
		this->setMyState(true);
	}
}

void Sensor::setMyTimers2(int delay, int BCTime, int SleepTime)
{
	//inserted for microTimeSlots;
	myTimeSlot = delay;

	myBCTime = BCTime;
	mySleepingTime = SleepTime;
	myDelay = (delay*1000)+1;
	blocked = false;

	if (myBCTime == 0 && mySleepingTime == 0)
	{
		myStopwatch->Stop();
		myTimer->Enabled = false;
		myTimer->Stop();
		this->setMyState(true);
	}
	else
	{
		myStopwatch->Restart();
		myTimer->Interval = myDelay;
		myTimer->Enabled = true;
		myTimer->Start();
		this->setMyState(false);
	}
}

void Sensor::setMyTimers3(int readTime, int BCTime, int SleepTime, bool adjusted)
{
	myBCTime = BCTime;
	mySleepingTime = SleepTime;
	myReadTime = readTime;
	blocked = false;

	myStopwatch->Restart();

	myTimer->Interval = myReadTime;
	myTimer->Enabled = true;
	myTimer->Start();

	timerAdjusted = adjusted;
}




void Sensor::setMyDelay(int delay, int BCTime, int SleepTime)
{
	myBCTime = BCTime;
	mySleepingTime = SleepTime;
	myDelay = (delay) + 1;
		
	myTimer->Interval = myDelay;
	this->setMyState(false);
}

void Sensor::startMyTimers()
{
	myTimer->Enabled = true;
	myTimer->Start();
}

bool Sensor::isMyTimerEnabled()
{
	return myTimer->Enabled;
}

int Sensor::getMyDelay()
{
	return myDelay;
}

int Sensor::getMyBCTime()
{
	return myBCTime;
}

int Sensor::getMySleepingTime()
{
	return mySleepingTime;
}

bool Sensor::wasAdjusted()
{
	return timerAdjusted;
}

bool Sensor::isOnGrid()
{
	return onGrid;
}

void Sensor::setOnGrid(bool set)
{
	onGrid = set;
}

int Sensor::getID()
{
	return myID;
}

int Sensor::getX()
{
	myX = myPic->Location.X;
	return myX;
}

int Sensor::getY()
{
	myY = myPic->Location.Y;
	return myY;
}

int Sensor::getcX()
{
	return (myPic->Location.X + (myPic->Size.Width / 2));
}

int Sensor::getcY()
{
	return (myPic->Location.Y + (myPic->Size.Height / 2));
}

void Sensor::setMyLabelText(String ^ text)
{
	myLabel->Text = text;
}

void Sensor::setLostUAVcounter()
{
	lostUAVcounter++;
}

int Sensor::getLostUAVcounter()
{
	return lostUAVcounter;
}

bool Sensor::hasCluster()
{
	if (myCluster == -1)
		return false;
	else
		return true;
}

bool Sensor::hasMessage()
{
	if (myMessageIcon->Visible)
		return true;
	else
		return false;
}

void Sensor::showMessage(bool state)
{
	if (state)
	{
		myMessageIcon->Visible = true;
		myMessageIcon->Location = System::Drawing::Point(myPic->Location.X + 2, myPic->Location.Y + 17);
		getDataFromSensor();
	}
	else
	{
		myMessageIcon->Visible = false;
		myMessages = "";
	}
}

int Sensor::isUAVConnected()
{
	int counter = 0;
	for (int i = 0; i < MAX_UAV; i++)
		if (myUAVConnections[i])
			counter++;

	return counter;
}

int Sensor::countMessages()
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

bool Sensor::getMyState()
{
	return myState;
}

bool Sensor::getVisit()
{
	return visited;
}

void Sensor::setVisit(bool v)
{
	visited = v;
}


void Sensor::clearAllConnections()
{
	for (int i = 0; i<MAX_UAV; i++)
		myUAVConnections[i] = false;
}

Size ^ Sensor::getSize()
{
	return myPic->Size;
}

String ^ Sensor::getMyLabel()
{
	return myLabel->Text;
}

Label ^ Sensor::getmyLabel()
{
	return myLabel;
}

void Sensor::getDataFromSensor()
{
	Random ^ rand = gcnew Random();
	DateTime^ dt = DateTime::Now;
	myCounter++;

	myMessages = "\r\n" + myID.ToString() + ";" +
				 myCounter.ToString() + ";" + 
				 DateTime::Now.ToString("yyyyMMdd_HHmmss") + ";" + 
				 getX() + ";" + 
				 getY() + ";" + 
				 rand->Next(1, 10) + ";" + 
				 rand->Next(1, 20) + ";" + 
				 rand->Next(1, 30);
}

String ^ Sensor::getMyMessages()
{
	return myMessages;
}

String ^ Sensor::getMyOldNewTimeSlots()
{
	if(myOriginalTimeSlot != -1 && myTimeSlot != -1)
		return myOriginalTimeSlot.ToString("00") + "/" + myTimeSlot.ToString("00");
	else
	{
		String ^ s;

		if (myOriginalTimeSlot != -1)
			s += myOriginalTimeSlot.ToString("00");

		if(myTimeSlot != -1)
		{
			if(myOriginalTimeSlot != -1)
				s += "/" + myTimeSlot.ToString("00");
			else
				s += myTimeSlot.ToString("00");
		}

		return s;
	}
}

Point ^ Sensor::getLocation()
{
	return myPic->Location;
}

Point ^ Sensor::getCenterLocation2()
{
	Point ^ p = gcnew Point();

	p->X = myPic->Location.X + (myPic->Size.Width / 2);
	p->Y = myPic->Location.Y + (myPic->Size.Height / 2);

	return p;
}

int Sensor::getMyTimnerInterval()
{
	return myTimer->Interval;
}

int Sensor::getMyReadTime()
{
	return myReadTime;
}

long long Sensor::getMyStopWatchElapsedTime()
{
	return myStopwatch->ElapsedMilliseconds;
}

int Sensor::getMyTimeSlot()
{
	return myTimeSlot;
}



bool Sensor::getDiscovered()
{
	return discovered;
}

void Sensor::setDiscovered(bool status)
{
	discovered = status;
}

void Sensor::setMyBCTime(int time)
{
	myBCTime = time;
}

void Sensor::setMyReadingTime(int time)
{
	myOriginalReadTime = time;
	myReadTime = time;
}

double Sensor::getBCleftTime()
{
	if (myState)
		return myBCTime - myStopwatch->ElapsedMilliseconds;
	else
		return 0;
}


Point Sensor::getCenterLocation()
{
	Point p;

	p.X = myPic->Location.X + (myPic->Size.Width / 2);
	p.Y = myPic->Location.Y + (myPic->Size.Height / 2);
	
	return p;
}

Point Sensor::getBaseLocation()
{
	Point p;
	p.X = myPic->Location.X + (myPic->Size.Width / 2);
	p.Y = myPic->Location.Y + (2*myPic->Size.Height/3);
	return p;
}

void Sensor::setBestLocation(Point ^ p)
{
	bestLocation = p;
}

Point ^ Sensor::getBestLocation()
{
	return bestLocation;
}


void Sensor::setMyState(bool s)
{
	myState = s;
	Random ^ rand = gcnew Random();

	if (s)
	{
		myPic->Image = Image::FromFile("Images\\s1bc.png");
		myMessageIcon->Visible = true;
		myMessageIcon->Location = System::Drawing::Point(myPic->Location.X + 2, myPic->Location.Y + 17);
		getDataFromSensor();
	}
	else
	{
		myPic->Image = Image::FromFile("Images\\s1sleep.png");
		
		if (myMessages->ToString() != "")
			lostUAVcounter++;
		
		clearAllConnections();
		showMessage(false);
		myMessages = "";
		lastMsgFrom = myName;
	}
}
void Sensor::setMyStateForTimer(bool s)
{
	myState = s;
	myPic->Image = Image::FromFile("Images\\s1bc.png");

}

int Sensor::getMyOriginalTimeSlot()
{
	return myOriginalTimeSlot;
}

void Sensor::setXY(int X, int Y)
{
	myPic->Location = System::Drawing::Point(X, Y);

	if(hasMessage())
		myMessageIcon->Location = System::Drawing::Point(myPic->Location.X + 2, myPic->Location.Y + 17);

	myLabel->Location = System::Drawing::Point(getX() + 15, getY() + 10);
}

void Sensor::setLabel(bool label)
{
	if (label)
	{
		myLabel->Visible = true;
		myLabel->Location = System::Drawing::Point(getX() + 15, getY() + 10);
	}
	else
	{
		myLabel->Visible = false;
	}
}

PictureBox ^ Sensor::getPicture()
{
	return myPic;
}

PictureBox ^ Sensor::getMessageIcon()
{
	return myMessageIcon;
}


double Sensor::getDistanceFrom(System::Drawing::Point ^ p)
{
	return Math::Round(Math::Sqrt((Math::Pow(getcX() - p->X, 2) + Math::Pow(getcY()- p->Y, 2))));
}

void Sensor::sendMessage(Vant ^ v)
{
	v->writeMessage(myMessages);
	v->showMessage(true);
	v->setlastMsgFrom(myName);

	this->showMessage(false);
	lastMsgFrom = v->getMyName();
}

void Sensor::copyMessage(Vant ^ v)
{
	if(v->getlastMsgFrom() != myName || lastMsgFrom != v->getMyName())
	{
		v->showMessage(true);
		v->writeMessage(myMessages);
		v->setlastMsgFrom(myName);
		lastMsgFrom = v->getMyName();
	}
}

String ^ Sensor::getLastMsgFrom()
{
	return lastMsgFrom;
}

String ^ Sensor::getMyName()
{
	return myName;
}

void Sensor::setMyName(String ^ name)
{
	myName = name;
}

double Sensor::getNearestDistance(Point ^ p, int maxDistance)
{
	Point ^ pp;
	pp = getNearestPoint(p, maxDistance);
	
	return getDistanceFrom(pp);
}

double Sensor::getDistanceFromCenter(Point ^ p)
{
	return Math::Sqrt((Math::Pow((getcX()) - p->X, 2) + Math::Pow((getcY()) - p->Y, 2)));
}

bool Sensor::isIntersectionWith(Point ^ center, int radius)
{
	if (this->getDistanceFrom(center) > (radius * 2))
		return false;
	else
		return true;
}

int Sensor::getMyCluster()
{
	return myCluster;
}

void Sensor::setMyCluster(int cluster, bool showLabel)
{
	myCluster = cluster;

	if (showLabel && myCluster >= 0)
		myLabel->Text = (myID + "(" + myCluster + ")");
	else
		myLabel->Text = myID.ToString();

}

Stopwatch ^ Sensor::getMyStopWatch()
{
	return myStopwatch;
}

Point Sensor::getNearestPoint(Point ^ target, int maxDistance)
{
	int distX, distY, myCx, myCy;
	double totalDistance, angle;

	myCx = getBaseLocation().X;
	myCy = getBaseLocation().Y;

	distX = target->X - myCx;
	distY = target->Y - myCy;

	totalDistance = Math::Round(Math::Sqrt((Math::Pow(distX, 2) + Math::Pow(distY, 2))));

	angle = Math::Atan2(distY, distX);

	Point p;

	p.X = Convert::ToInt32(myCx + (totalDistance - maxDistance)*Math::Cos(angle));
	p.Y = Convert::ToInt32(myCy + (totalDistance - maxDistance)*Math::Sin(angle));

	return p;
}

void Sensor::setConnection(int conn)
{
	myUAVConnections[conn] = true;
}

void Sensor::clearConnection(int conn)
{
	myUAVConnections[conn] = false;
}

bool Sensor::isConnectedWith(int conn)
{
	return myUAVConnections[conn];
}


void Sensor::reset()
{

}
