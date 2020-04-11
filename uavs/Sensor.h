#pragma once

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "vants.h"
#include "server.h"

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
using namespace System::Collections::Generic;

#define MAX_UAV 10
#define MAX_SENSOR 20
#define INVALID -1

ref class Vant;

ref class Sensor
{
private:
	PictureBox ^ myPic;
	PictureBox ^ myMessageIcon;
	Label ^ myLabel = gcnew Label();
	String ^ myMessages;
	String ^ myName;
	String ^ lastMsgFrom;
	array<bool> ^ myUAVConnections = (gcnew array<bool>(MAX_UAV));
	Point ^ bestLocation;
	Stopwatch ^ myStopwatch = gcnew Stopwatch();
	System::Windows::Forms::Timer ^ myTimer;
	int myDelay;
	int myTimeSlot, myOriginalTimeSlot;
	int myBCTime;
	int myOriginalSleepingTime;
	int myOriginalReadTime;
	int myOriginalBCTime;
	int timeDifference;
	int mySleepingTime;
	int myReadTime;	
	int myBlockedTime;
	int myCluster;
	int myX, myY;
	int myID;
	int myCounter;
	int lostUAVcounter;
	bool timeSlotReprogrammed;
	bool blocked;
	bool timerAdjusted;
	bool myState;
	bool visited;
	bool onGrid;
	bool discovered;
public:
	Sensor();
	Sensor(int ID, System::Windows::Forms::Panel ^ sa);
	Sensor(int ID, System::Windows::Forms::Panel ^ sa, Point ^ initLocation);

	void Sensor::timerTick(System::Object ^ sender, System::EventArgs ^ e);
	void setMyTimers1(int BCTime, int SleepTime);
	void setMyTimers2(int delay, int BCTime, int SleepTime);
	void setMyTimers3(int readTime, int BCTime, int SleepTime, bool adjusted);
	void setMyTimeSlotTimers(int BCTime, int SleepTime, int Delay, int qSensors);
	void setMyMicroTimeSlotTimers_toSleep(int newTS, int microTStime, int qTimeSlots, int sleepTime, int BCTime, int BCtimeSlots, int readTime);
	void setMyMicroTimeSlotTimers(int myTS, int microTStime, int sleepTime, int reeadTime);
	void setMyTimeSlotTimers2(int BCTime, int SleepTime, int readTime, int timeSlot, int qSensors);

	void setMyDelay(int delay, int BCTime, int SleepTime);
	void startMyTimers();
	bool isMyTimerEnabled();

	int getMyDelay();
	int getMyBCTime();
	int getMySleepingTime();

	bool wasAdjusted();

	bool isOnGrid();
	void setOnGrid(bool set);
	int getID();
	int getX();
	int getY();
	int getcX();
	int getcY();
	void setMyLabelText(String ^ text);
	void setLostUAVcounter();
	int getLostUAVcounter();
	bool hasCluster();
	bool hasMessage();
	void showMessage(bool state);
	int isUAVConnected();
	int countMessages();
	bool getMyState();
	bool getVisit();
	void setVisit(bool v);
	void clearAllConnections();
	void getDataFromSensor();
	void setMyState(bool s);
	void setMyStateForTimer(bool s);
	int getMyOriginalTimeSlot();
	void setXY(int X, int Y);
	void setLabel(bool label);
	void setConnection(int conn);
	void clearConnection(int conn);
	bool isConnectedWith(int conn);
	double getDistanceFrom(System::Drawing::Point ^ p);
	void sendMessage(Vant ^ v);
	void copyMessage(Vant ^ v);
	void setMyName(String ^ name);
	double getNearestDistance(Point ^ p, int maxDistance);
	double getDistanceFromCenter(Point ^ p);
	bool isIntersectionWith(Point ^ center, int radius);
	int getMyCluster();
	void setMyCluster(int cluster, bool showLabel);
	Stopwatch ^ getMyStopWatch();
	Point getNearestPoint(Point ^ target, int maxDistance);
	String ^ getLastMsgFrom();
	String ^ getMyName();
	Point ^ getLocation();
	Point getCenterLocation();
	Point ^ getCenterLocation2();
	int getMyTimnerInterval();
	int getMyReadTime();
	long long getMyStopWatchElapsedTime();
	
	int getMyTimeSlot();
	void setMyTimeSlot(int ts, int qSensors);
	bool getDiscovered();
	void setDiscovered(bool status);
	void setMyBCTime(int time);
	void setMyReadingTime(int time);
	double getBCleftTime();

	void setSensorToSleepOnTimeSlot();
	bool isTimeSlotReprogrammed();
	void setTImeSlotReprogrammed(bool state);

	Point getBaseLocation();
	void setBestLocation(Point ^ p);
	Point ^ getBestLocation();
	
	Size ^ getSize();
	String ^ getMyLabel();
	Label ^ getmyLabel();
	String ^ getMyMessages();
	String ^ getMyOldNewTimeSlots();
	PictureBox^ getPicture();
	PictureBox^ getMessageIcon();
	void reset();
	virtual ~Sensor();
};

#endif