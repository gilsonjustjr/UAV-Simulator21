#ifndef __HELPERS_H__
#define __HELPERS_H__

#pragma once

#define CRLF "\r\n";
#define MAX_UAV 10
#define MAX_SENSOR 20
#define MAX_STEPS 250
#define DIST_FROM_CENTER 15
#define MAX_SPEED 9
#define ROUTE_EMPTY 0
#define ROUTE_RED 1
#define ROUTE_GREEN 2
#define ROUTE_BLUE 4
#define CHECK_INTERVAL 2000

bool runProgram = true;
unsigned int qUAVs = 1;
unsigned int qSensors = 0;
unsigned int qTimeSlots = 0;
unsigned int timeSlotTime = 1;
unsigned int nQSensors, nQUAVs, activeSensors;
unsigned int Speed;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

Point ^ _getNearestPointFromTo(Point ^ src, Point ^ dst, double maxDistance)
{
	int distX, distY, myCx, myCy;
	double totalDistance;
	double angle;

	myCx = src->X;
	myCy = src->Y;

	distX = dst->X - myCx;
	distY = dst->Y - myCy;

	totalDistance = Math::Round(Math::Sqrt((Math::Pow(distX, 2) + Math::Pow(distY, 2))));

	angle = Math::Atan2(distY, distX);

	Point ^ p = gcnew Point();

	if (totalDistance > maxDistance)
	{
		p->X = Convert::ToInt32(myCx + (totalDistance - maxDistance*0.97)*Math::Cos(angle));
		p->Y = Convert::ToInt32(myCy + (totalDistance - maxDistance*0.97)*Math::Sin(angle));
	}
	else
	{
		p->X = myCx;
		p->Y = myCy;
	}

	return p;
}


int _getDistanceFrom(Point ^ p1, Point ^ p2)
{
	if (p1 != nullptr && p2 != nullptr)
		return Convert::ToInt32(Math::Sqrt(Math::Pow(p2->X - p1->X, 2) + Math::Pow(p2->Y - p1->Y, 2)));
	else
		return -1;
}


String ^ _getStringFromCoordinates(Point ^ p)
{
	if (p != nullptr)
		return "(" + p->X + ", " + p->Y + ")";
	else
		return "";

}

String ^ _getStringFromCoordinatesToLog(Point ^ p)
{
	return ";" + p->X + ";" + p->Y + ";";

}


String ^ _getStringFromCoordinatesToLog3(Point ^ p)
{
	return p->X + ";" + p->Y + ";";

}

String ^ _getStringFromCoordinatesToLog2(Point ^ p)
{
	return ";" + p->X + ";" + p->Y;

}

String ^ _getActualTimeStamp()
{
	return "";
}


String ^ _getDateTime()
{
	DateTime^ dt = DateTime::Now;
	return DateTime::Now.ToString("yyyyMMdd_HHmmss");
}

int _getIDFromPicture(PictureBox ^ p)
{
	return Convert::ToInt32(p->Tag->ToString()->Substring(1));
}

String ^ _getTypeFromPicture(PictureBox ^ p)
{
	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "S")
		return "Sensor";

	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "U")
		return "UAV";

	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "M")
		return "Message UAV";

	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "m")
		return "Message Sensor";

	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "s")
		return "Server";

	if (p->Tag->ToString()->ToCharArray()[0].ToString() == "e")
		return "Message Server";

	return nullptr;
}

int _getIDfromName(String ^ name)
{
	if (name != "")
		return Convert::ToInt32(name->ToCharArray()[1].ToString());
	else
		return 0;
}


int _getFieldFromLine(String ^ s, int f)
{
	int p1 = 0;
	int p2 = 0;

	switch (f)
	{
		case 1:
			p1 = s->IndexOf(';', p2);
			return Convert::ToInt32(s->Substring(p2, p1));
			break;

		case 2:
			p1 = s->IndexOf(';', p2);
			p2 = s->IndexOf(';', p1 + 1);
			return Convert::ToInt32(s->Substring(p1 + 1, p2 - p1 - 1));
			break;

		case 3:
			p1 = s->IndexOf(';', p2);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			return Convert::ToInt32(s->Substring(p2 + 1, p1 - p2 - 1));
			break;

		case 4:
			p1 = s->IndexOf(';', p2);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			p2 = s->IndexOf(';', p1 + 1);
			return Convert::ToInt32(s->Substring(p1 + 1, p2 - p1 - 1));
			break;

		case 5:
			p1 = s->IndexOf(';', p2);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			return Convert::ToInt32(s->Substring(p2 + 1, p1 - p2 - 1));
			break;

		case 6:
			p1 = s->IndexOf(';', p2);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			p2 = s->IndexOf(';', p1 + 1);
			p1 = s->IndexOf(';', p2 + 1);
			return Convert::ToInt32(s->Substring(p1 + 1, s->Length - p1 - 1));
			break;
		default:
			return 0;
			break;
	}
}

double _getAngleRadians(Point ^ p1, Point ^ target)
{
	int dx = target->X - p1->X;
	int dy = target->Y - p1->Y;

	double angle = Math::Atan2(dy, dx);

	if (angle >= 0)
		return angle;
	else
		return angle + 2*Math::PI;
}

double _getAngleDegrees(Point ^ p1, Point ^ target)
{
	int dx = target->X - p1->X;
	int dy = target->Y - p1->Y;

	double angle = Math::Atan2(dy, dx)*(float)(180 / Math::PI);

	if (angle >= 0)
		return angle;
	else
		return angle + 360;
}


//law of cosines;
double _getBisectorAngle(Point ^ A, Point ^ B, Point ^ C)
{
	return  0.5*(Math::Acos((Math::Pow(_getDistanceFrom(A, B), 2) + Math::Pow(_getDistanceFrom(A, C), 2) - Math::Pow(_getDistanceFrom(B, C), 2)) / (2 * _getDistanceFrom(A, C)*_getDistanceFrom(A, B))));// *(180 / Math::PI);
}

int getAngleABC(Point a, Point b, Point c)
{
	Point ab = Point(b.X - a.X, b.Y - a.Y);
	Point cb = Point(b.X - c.X, b.Y - c.Y);

	int dot = ab.X * cb.X + ab.Y * cb.Y;
	int cross = ab.X * cb.Y - ab.Y * cb.X;

	double alpha = atan2(cross, dot);

	return Convert::ToInt32(floor(alpha));
}

#endif

