#pragma once

#ifndef __VANTS_H__
#define __VANTS_H__

#include "Sensor.h"
#include "Server.h"

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
#define MAX_SPEED 4
#define MIN_SPEED 0
#define MIN_STOP 100
#define MAX_STOP 2000
#define ROUTE_EMPTY 0
#define ROUTE_RED 1
#define ROUTE_GREEN 2
#define ROUTE_BLUE 4
#define ROUTE_CYAN 8

ref class Sensor;
ref class server;

ref class Restrictions
{
private:
	int myTimeSlot;
	List <int> restrictedSensors;
	List <int> permitedSensors;
public:
	void setTimeSlot(int TS);
	int getMyTimeSlot();
	int restrictedSensorsCount();
	int permitedSensorsCount();
	int getRestrictedSensorsOnIndex(int index);
	int getPermissionSensorOnIndex(int index);
	void setNewRestriction(int ID);
	void setNewPermission(int ID);
	void clearRestrictedTimeSlots();
	bool findRestriction(int ID);
	bool findPermission(int ID);
	bool removePermission(int ID);
	void clearAllLists();
	virtual ~Restrictions();
};

ref class JustID : Restrictions
{
private: 
	int myID;
	int myTimeSlot;
	int myOriginalTimeSlot;
	int myCluster;
	int timeSlotsUntillHere;
	bool checkState;
	bool isVisited;
	bool isDiscovered;
	bool isReprogrammed;
	Point ^ myLocation;
public:
	JustID();
	void setMyID(int ID);
	void setMyLocation(Point ^ p);
	void SetCheckState(bool state);
	void setVisited(bool state);
	void setMyCluster(int cluster);
	int getMyCluster();
	bool getVisited();
	bool getCheckState();
	bool getDiscovered();
	void setDiscovered(bool state);
	void setMyTimeSlot(int ts);
	void setIsReprogrammed(bool state);
	bool getIsReprogrammed();
	int getMyTimeSlot();
	int getMyID();
	int getMyOriginalTimeSlot();
	
	int getTimeSlotsUntillHere();
	void setTimeSlotsUntillHere(int TS);

	void setMyOriginalTimeSlot(int ts);
	Point ^ getMyLocation();
	virtual ~JustID();
};

ref class Vant : JustID 
{
private:
	int myID;
	int myX, myY;
	int myDirX, myDirY;
	int mySpeed, myOldSpeed;
	int mySteps;
	int myCounter;
	int whereIamNow;
	int whereIwas;
	int whereIgoingTo;
	int routeListControl;
	int actualTimeSlot;
	int connectedWithSensorNow;
	int myCluster;
	int hops;
	int decisions;
	bool active;
	bool myInit, myStart;
	bool serverConnection;
	bool isAtTarget;
	bool timeSlotDiscovery;
	bool waiting;
	int routeTotalDistance;
	Label ^ myLabel = gcnew Label();
	String ^ myName;
	String ^ lastMsgFrom;

	array<bool> ^ myUAVConnections = (gcnew array<bool>(MAX_UAV));
	array<bool> ^ mySensorConnections = (gcnew array<bool>(MAX_SENSOR));
	array<Sensor^> ^ myRoute = gcnew array<Sensor^>(MAX_SENSOR);
	array<Point^> ^ myTargets = gcnew array<Point^>(MAX_SENSOR);
	array<Point^> ^ myFly = gcnew array<Point^>(MAX_SENSOR);
	array<Point^> ^ myHibridFly = gcnew array<Point^>(MAX_SENSOR);

	List<JustID^> routeList;
	List<Restrictions^> myRestrictions;

	PictureBox^ myPic;
	PictureBox ^ myMessageIcon;
	String ^ myMessages;
	System::Windows::Forms::Timer ^ myTimer;
	Stopwatch ^ myStopWatch;
	Point ^ myRWP;
	Point ^ myFirstLocation;
	Point ^ myLastTarget;
	double myRealSpeed;
	double totalDistance;
public:
	Vant();
	Vant(int ID, System::Windows::Forms::Panel^ sa);
	int getID();
	int getX();
	int getY();
	int getcY();
	int getcX();
	int getSpeed();
	int getOldSpeed();
	void setOldSpeed(int oSpeed);
	void resetSpeed();
	void setInit(bool state);
	bool getInit();
	int getMyCounter();
	void setMyCounter(int c);
	void showMessage(bool state);
	bool hasMessage();
	bool getWaiting();
	void setWaiting(bool wait);
	bool isServerConnected();
	double getTotalDistance();
	bool getIsAtTarget();
	void incrementDistance(int dist);
	void setLabel(bool label);
	void setXY(int X, int Y);
	void setMyDirX(int nDirX);
	void setMyDirY(int nDirY);
	void setMySpeed(int nVel);
	void RandomStep();
	void setConnection(int conn, String ^ type);
	void clearConnection(int conn, String ^ type);
	bool isConnectedWith(int conn, String ^ type);
	void setNewDirection(int dir);
	void setRandDirection(int max_steps, bool randSpeed);
	void nextStep(Point ^ p);
	void setMySteps(int i);
	void setRandomSpeed();
	void setMyRWP(Point ^ p);
	void sendMessage(Vant ^ v, bool remember);
	void copyMessage(Vant ^v);
	void sendMessage(server ^ ss);
	void setConnection(server ^ ss);
	void setConnection(Vant ^ v);
	void setConnection(Sensor ^ s);
	void clearConnection(Vant ^ v);
	void clearConnection(Sensor ^s);
	void clearConnection(server ^ss);
	void writeMessage(String ^ msg);
	void setlastMsgFrom(String ^ i);
	void standBy(int time);
	void addTotalDistance(int add);
	void setMyTotalDistance(double value);
	String ^ getlastMsgFrom();
	String ^ getMyName();
	void setMyName(String ^ name);
	int isUAVConnected();
	int isSensorConnected();
	int getMySteps();
	int getMyDirection();
	int countMessages();
	int getWhereIamNow();
	bool checkCollision(System::Windows::Forms::Panel^ sa, int distance);
	bool isMyTimerEnabled();
	double getDistanceFrom(System::Drawing::Point ^ p);
	double getDistanceFrom(Vant ^ v);
	double getDistanceFromTo(Point ^ p1, Point ^ p2);
	double getDistanceFromCenter(Point ^ p);
	bool isInsideRange(Point ^ p);
	bool isAtTarget2(Point ^ p);
	void insertRoute(Sensor ^ s, int position);
	void setFly(Point ^ p);
	int getTimeFromDistance(int distance);
	int getConnectedWithSensorNow();
	void setLastTarget(Point ^ p);
	Point ^ getLastTarget();
	Point ^ getFly(int pos);
	Point ^ getNextFly(int maxSensor);
	Point ^ getNextHibridFly(int maxSensor);
	void setHibridFly(Point ^ p);
	Point ^ getHibridFly(int pos);
	void timerTick(System::Object^  sender, System::EventArgs^  e);
	double getNearestDistance(Point ^ p, int maxDistance);
	Point ^ getNextRoute(int MaxSensor, int MinDistance);
	Point ^ getLastRoute(int MaxSensor);
	Sensor ^ getRouteSensor(int index);
	String ^ getMyMessages();
	String ^ getMyLabel();
	Label ^ getmyLabel();
	Point ^ getNearestPoint(Point ^ target, int maxDistance);
	Point drawNearestPoint(Point ^ target, int maxDistance);
	Point ^ getMyRWP();
	Point getCenterLocation();
	Point ^ getCenterLocation2();
	Point ^ setNewRWP(System::Windows::Forms::Panel^ sa);
	Point ^ getMyFirstLocation();
	void setMyFirstLocation(Point ^ p);
	Sensor ^ getRoute(int position);
	Point ^ getTarget(int index);
	Point ^ getNextTarget(int MaxSensor);
	void setNewTarget(int index, Point ^ p);
	void  setNewRWP2(System::Windows::Forms::Panel^ sa);
	Point ^ getLocation();
	Size ^ getSize();
	PictureBox^ getPicture();
	PictureBox ^ getMessageIcon();
	Stopwatch ^ getMyStopWatch();
	double getMyRealSpeed();
	double getMyRealSpeed(int scrollValue);
	double getTimeFromToByCoord(Point ^ p1, Point ^ p2);
	double getTimeUntillSensor(int sensorID, int readTime, int maxSensors, int route);
	double getRouteTotalTime(int sensorID, int readTime, int maxSensors, int route);
	void addRouteList(JustID ^ rr);
	void addRouteList(Point ^ p, int ID);
	void clearRouteList();
	Point ^ getRouteListByID(int ID);
	Point ^ getNextTarget();
	Point ^ getNextUnvisitedTarget();
	int getNextUnvisitedID();
	int getNextUnvisitedID_withoutDeposit(bool restriction);
	int getNextUnvisitedID_withoutDeposit();
	bool getRouteListStateByIndex(int index);
	void setRouteListStateByIndex(int index, bool state);
	void setRouteListStateByID(int ID, bool state);
	bool getRouteListStateByID(int ID);
	long getFlyTime();
	int getRouteListCount();
	int getWhereIam();
	int getWhereIGoingTo();
	int getWhereIwas();
	int getRouteListIndexByID(int ID);
	void startMyStopWatch(bool start);
	bool getMyStart();
	void setMyStart(bool st);
	void setActualTimeSlot(int ts);
	int getActualTimeSlot();
	void setRouteListIsDiscovered(int ID, int state, int ts);
	bool getRouteListIsDiscovered(int ID);
	void associateTimeSlotOnRouteList(int ID, int timeSlot);
	int getAssociatedTimeSlotOnRouteList(int ID);
	int countDiscoveredSensorsOnRouteList();
	int getIDByTimeSlot(int ts);
	JustID ^ getRouteListByTimeSlot(int ts);
	JustID ^ getRouteListBySensorID(int ID);
	JustID ^ getRouteListByTimeSlot2(int ts, bool reprogrammed);
	JustID ^ getNextTargetByTimeSlot(int ts, bool reprogrammed);
	JustID ^ findClosestDistanceToDeposit();
	JustID ^ getRouteListByIndex(int index);
	JustID ^ getJustIDByID(int ID);
	int getNextIDByTimeSlot(int ts, bool reprogrammed);
	bool getRouteListIsVisited(int ID);
	void setRouteListIsVisited(int ID, bool state);
	void setTimeSlotDiscovery(bool state);
	bool getTimeSlotDiscovery();
	void setRouteListIsReprogrammed(int ID, bool state, int newTS);
	bool getRouteListIsReprogrammed(int ID);
	double getTimeFromTo(int source, int destination, int readTime, int qSensors, int typeRoute);
	double getTimeFromTo(Point ^ p1, Point ^ p2);
	double getTimeFromToByID(int IDfrom, int IDto, int readTime);
	double getTimeFromToByIndex(int indexFrom, int indexTo, int readTime);
	double getTimeSlotsFromToByIndex(int indexFrom, int indexTo, int readTime, int timeSlotTime, int scrollSpeed);
	//double getTotalTimeSlotsForRoute(int readTime, int timeSlotTime);
	double getTotalTimeForRoute(int readTime, int scrollSpeed);
	double getTotalTimeFromRouteList(int readTime);
	int getTimeSlotsToID(int timeSlotTime, int nextID, int scrollSpeed);
	int gettTimeSlotsFromDepositUntillHere(int ID, int TSTime, int readTime);
	int getTimeSlotsFromToByID(int timeSlotTime, int IDfrom, int IDto, int readTime, bool goToDeposit);
	int getTimeSlotsUntillHere(int timeSlotTime, int here);

	double getRouteTotalTime_forMicroTimeSlos(bool deposit, int readTime);

	void reconfigureTimeSlots();
	int countUnprogrammedTimeSlots();

	int countSensorsOnCluster(int cluster);
	int countDiscoveredSensorsOnCluster(int cluster);
	int getNextCluster(int qSensors);
	int getMyCluster();
	int getMaxCluster(int qSensors);
	int getNextUnvisitedOnCluster();

	bool isThereRestriction(int TS, int ID);
	bool isTherePermission(int TS, int ID);
	bool addRestriction(int TS, int ID);
	void addTimeSlotToRestrictions(int TS, int qSensors);
	String ^ getRestrictionsOnTimeSlot(int TS);
	String ^ getPermissionOnTimeSlot(int TS);
	List<int> ^ getListPermitedSensorsOnTimeSlot(int TS);
	List<int> ^ getListUnvisitedTargets();
	String ^ getListUnvisitedTargetsOnString();

	Restrictions ^ getRestrictionByIndex(int index);

	void removeIDfromPermissionLists(int ID);
	void clearRestrictionsOnTimeSlot(int TS);
	void clearRestrictionLists();
	void clearALLrestrictionsForReset();
	void addDecisionCounter();
	int getDecisionCounter();
		
	int getNextUndiscoveredIDbyTimeSlot(int actualTS, int qTS);
	int getNextIDbyTimeSlot(int actualTS, int qTS);
	int getNextIDbyMicroTimeSlot(int actualTS, int qTS, int actualID);

	void copyRoutingParametersFromUAV(Vant ^ v, int qTS);

	bool timeSlotIsAlreadyUsed(int TS);
	bool isTimeSlotProgrammedOnRestrictionList(int TS);

	bool isActive();
	void setActive(bool state);

	int getRouteTotalDistance();
	void setRouteTotalDistance(int dist);

	void addHopCounter();
	int getHopsCounter();
	virtual ~Vant();
};

#endif