#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include "helpers.h"
#include "vants.h"
#include "Sensor.h"
#include "server.h"
#include "Grafo.h"

namespace uavs {

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
using namespace System::Resources;
using namespace System::Collections::Generic;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using System::Drawing::Image;

/// <summary>
/// Summary for simulator
/// </summary>

public ref class simulator : public System::Windows::Forms::Form
{
public:
	simulator(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~simulator()
	{
		if (components)
		{
			delete components;
		}
	}

private: static array<Vant^>^ myVants = (gcnew array<Vant^>(MAX_UAV));
private: static array<Sensor^>^ mySensors = (gcnew array<Sensor^>(MAX_SENSOR));
private: List<int> randomTimeSlotControl;

		 bool dragAndDrop;
bool init = true;
long percentPicture = 100;
bool UAVdevcision = false;
unsigned int counter = 0;
unsigned int totalDistance = 0;
unsigned int totalNearestDistance = 0;
unsigned int difference = 0;
double calculatedTime = 0;
double routeTotalTime = 0;
double sleepTime = 0;
int simulationCounter = 0;
int whereIam;
int whereIamNow;
int whereIGoingTo;
int whereIwas;
int delayTime;
int nextID, oldID;
int timeSlot, newTimeSlot, futureTimeSlot;
Random ^ rand = gcnew Random();
Point ^ target = gcnew Point();
Point ^ oldTarget = gcnew Point();

private: static List<Point> myGridLocation;
private: static List<bool> myGridControl;
private: static List<int> ^ permitedSensorList;
private: int redRouteON, greenRouteON, blueRouteON, cyanRouteON, checkRoutes;
private: int timeSlotSensorID;
private: TextWriter ^ tw;
private: TextWriter ^ logger;
private: String ^ toLog;
private: String ^ toLog2;
private: String ^ logPath;
private: Stopwatch ^ SystemStopWatch = gcnew Stopwatch();
private: Stopwatch ^ TestStopWatch = gcnew Stopwatch();
private: bool setNewRWP;
private: Point MouseDownLocation;
private: Point returnToOldLocation;
private: int dataGridTimeDiff;
private: int PursueReference;
public:	Graphics ^ graphics;
public:	Pen ^ BluePen;
public:	Pen ^ RedPen;
public:	Pen ^ RedPenRoundAnchor;
public:	Pen ^ GreenPenRoundAnchor;
public:	Pen ^ BluePenRoundAnchor;
public:	Pen ^ CyanPenRoundAnchor;
public: Pen ^ CyanPen;
public: Pen ^ GreenPen;
public:	Pen ^ DashedBluePen;
public:	Pen ^ DashedGreenPen;
public:	Pen ^ DashedRedPen;
public:	StringFormat ^ stringFormat = gcnew StringFormat();
public: SolidBrush ^ RedBrush = gcnew SolidBrush(Color::Red);
public:	SolidBrush ^ GreenBrush = gcnew SolidBrush(Color::Green);
public:	SolidBrush ^ BlackBrush = gcnew SolidBrush(Color::Black);
public:	SolidBrush ^ BlueBrush = gcnew SolidBrush(Color::Blue);
public:	SolidBrush ^ CyanBrush = gcnew SolidBrush(Color::Cyan);
public: System::Drawing::Font ^ drawFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
private: Vant ^ v1;
private: Vant ^ v2;
private: Vant ^ v;
private: Sensor ^ s;
private: Point ^ p;
private: server ^ ss;
private: Point intersection1 = Point(0, 0);
private: Point intersection2 = Point(0, 0);
private: Point tangent1 = Point(0, 0);
private: Point tangent2 = Point(0, 0);
private: Point destIntersection;

private: System::Windows::Forms::Timer^  Timer1sec;
private: System::Windows::Forms::ToolTip^  ttShowInfo;
private: System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
private: System::Windows::Forms::ToolStripContainer^  toolStripContainer2;
private: System::Windows::Forms::ToolStripPanel^  BottomToolStripPanel;
private: System::Windows::Forms::ToolStripPanel^  TopToolStripPanel;
private: System::Windows::Forms::ToolStripPanel^  RightToolStripPanel;
private: System::Windows::Forms::ToolStripPanel^  LeftToolStripPanel;
private: System::Windows::Forms::ToolStripContentPanel^  ContentPanel;
private: System::Windows::Forms::Timer^  TimerSensorLOG;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
private: System::Windows::Forms::GroupBox^  Connections;
private: System::Windows::Forms::DataGridView^  dataGridView;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
public: System::Windows::Forms::Panel^  simulationArea;
private: System::Windows::Forms::SplitContainer^  splitContainer1;
private: System::Windows::Forms::ToolStrip^  toolStrip2;
private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator28;
private: System::Windows::Forms::ToolStripButton^  ts2outputClear;
private: System::Windows::Forms::ToolStripButton^  ts2Copy;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator8;
private: System::Windows::Forms::ToolStripButton^  tsDownCarret;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator29;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator15;
private: System::Windows::Forms::ToolStripButton^  tsScreenshoot;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator30;
private: System::Windows::Forms::ToolStripLabel^  tsSimulationAreaSize2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator14;
private: System::Windows::Forms::ToolStripLabel^  tsTimer2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator31;

private: System::Windows::Forms::ToolStrip^  toolStrip1;
private: System::Windows::Forms::ToolStripButton^  tsPlay;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator12;
private: System::Windows::Forms::ToolStripButton^  tsBreset;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
private: System::Windows::Forms::ToolStripComboBox^  tsMobilityModel;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripButton^  tsUAVposition;
private: System::Windows::Forms::ToolStripButton^  tsInfo;
private: System::Windows::Forms::ToolStripButton^  tsStandBy;
private: System::Windows::Forms::ToolStripButton^  tsDrawPoint;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator16;
private: System::Windows::Forms::ToolStripButton^  tsGridSensor;
private: System::Windows::Forms::ToolStripLabel^  tsMaxSensorsGrid;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator17;
private: System::Windows::Forms::ToolStripButton^  tsShowCluster;
private: System::Windows::Forms::ToolStripButton^  tsDrawCircleSensor;
private: System::Windows::Forms::ToolStripButton^  tsDrawCircleUAV;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator35;
private: System::Windows::Forms::ToolStripButton^  tsShowRoute;
private: System::Windows::Forms::ToolStripButton^  tsRedRoute;
private: System::Windows::Forms::ToolStripButton^  tsGreenRoute;
private: System::Windows::Forms::ToolStripButton^  tsBlueRoute;
private: System::Windows::Forms::ToolStripButton^  tsCyanRoute;
private: System::Windows::Forms::ToolStripButton^  tsRouteInfo;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator11;
private: System::Windows::Forms::ToolStripButton^  tsSleepSensor;
private: System::Windows::Forms::ToolStripButton^  tsBroadcastActivate;
private: System::Windows::Forms::ToolStripButton^  tsFixedTimers;
private: System::Windows::Forms::ToolStripButton^  tsRandSleep;
private: System::Windows::Forms::ToolStripButton^  tsBackToDeposit;



private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator9;
private: System::Windows::Forms::ToolStripButton^  tsUp;
private: System::Windows::Forms::ToolStripButton^  tsDown;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
private: System::Windows::Forms::ToolStripLabel^  tsQuav;
private: System::Windows::Forms::ToolStripButton^  tsUAVSelect;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
private: System::Windows::Forms::ToolStripLabel^  tsQSensor;
private: System::Windows::Forms::ToolStripButton^  tsSensorSelect;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator10;
private: System::Windows::Forms::ToolStripLabel^  tsSpeed;
private: System::Windows::Forms::ToolStripButton^  tsSpeedSelect;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator32;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;










private: System::Windows::Forms::ToolStripButton^  tsDebug;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator34;



private: System::Windows::Forms::ToolStripButton^  tsClosedCircuit;
private: System::Windows::Forms::ToolStripLabel^  tsTSLabel2;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator19;






private: System::Windows::Forms::ToolStripButton^  tsSensorDiscoveredTS;

private: System::Windows::Forms::ToolStripButton^  tsSetTimeSlot;
private: System::Windows::Forms::ToolStripButton^  tsScanForSensors;
private: System::Windows::Forms::ToolStripButton^  tsLOG;
private: System::Windows::Forms::SplitContainer^  splitContainer3;
private: System::Windows::Forms::TextBox^  output;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::CheckBox^  checkBox3;
private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::CheckBox^  checkBox9;
private: System::Windows::Forms::CheckBox^  checkBox10;
private: System::Windows::Forms::CheckBox^  checkBox11;
private: System::Windows::Forms::CheckBox^  checkBox12;
private: System::Windows::Forms::CheckBox^  checkBox5;
private: System::Windows::Forms::CheckBox^  checkBox6;
private: System::Windows::Forms::CheckBox^  checkBox7;
private: System::Windows::Forms::CheckBox^  checkBox8;
private: System::Windows::Forms::CheckBox^  checkBox4;
private: System::Windows::Forms::ToolTip^  ttLOG;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator20;
private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator21;
private: System::Windows::Forms::ToolStripButton^  tsRepeatTimeSlots;
private: System::Windows::Forms::ToolStripLabel^  tsUAVHops;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator22;
private: System::Windows::Forms::ToolStripButton^  tsSetRestriction;
private: System::Windows::Forms::Timer^  nextStepTimer;
private: System::Windows::Forms::ToolStripLabel^  tsUAVSpeedText;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
private: System::Windows::Forms::ToolStripLabel^  tsUAVFlyedDistance;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator13;
private: System::Windows::Forms::ToolStripComboBox^  tsqTimeSlots;


private: System::Windows::Forms::ToolStripButton^  tsMicroTimeSlots;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  SensorTimer;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  TImeSlotColumn;
private: System::Windows::Forms::SplitContainer^  splitContainer2;
private: System::Windows::Forms::NumericUpDown^  numTSTime;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::NumericUpDown^  numBCtimeSlots;
private: System::Windows::Forms::Label^  label12;

private: System::Windows::Forms::NumericUpDown^  readTime;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TrackBar^  tsStepInterval;
private: System::Windows::Forms::NumericUpDown^  numClusterDistance;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::CheckBox^  cbLog;
private: System::Windows::Forms::Button^  bRunSimulation;
private: System::Windows::Forms::NumericUpDown^  numSimulationPause;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::NumericUpDown^  numQtySimulation;
private: System::Windows::Forms::NumericUpDown^  broadcastTime;

private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::NumericUpDown^  numU2DmaxConn;
private: System::Windows::Forms::NumericUpDown^  numV2SmaxConn;
private: System::Windows::Forms::NumericUpDown^  numV2VmaxConn;

private: System::Windows::Forms::NumericUpDown^  numConRangeV2Sever;
private: System::Windows::Forms::CheckBox^  cbUavUav;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::CheckBox^  cbUAVtoServer;
private: System::Windows::Forms::CheckBox^  cbUAVtoSesnor;
private: System::Windows::Forms::NumericUpDown^  SleepingTime;
private: System::Windows::Forms::NumericUpDown^  numConRangeV2V;
private: System::Windows::Forms::NumericUpDown^  numConRangeV2S;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::ToolStripButton^  tsLockReset;
private: System::Windows::Forms::ToolStripLabel^  tsDecision;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator18;
private: System::Windows::Forms::ToolStripButton^  tsSwapUAVs;

private: System::Windows::Forms::NumericUpDown^  numUAVAutonomy;
private: System::Windows::Forms::Label^  labelUAVAutonomy;
private: System::Windows::Forms::Label^  UAVAutonomyLabel;

private: System::Windows::Forms::ToolStripProgressBar^  tsBattery;

private: System::Windows::Forms::ToolStripLabel^  tsSimulationCounter;
private: System::Windows::Forms::ToolStripButton^  tsSound;
private: System::Windows::Forms::NumericUpDown^  numBatteryLevel;


















private: System::ComponentModel::IContainer^  components;
			/// <summary>
			/// Required designer variable.
			/// </summary>


#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(simulator::typeid));
				this->Timer1sec = (gcnew System::Windows::Forms::Timer(this->components));
				this->ttShowInfo = (gcnew System::Windows::Forms::ToolTip(this->components));
				this->tsStepInterval = (gcnew System::Windows::Forms::TrackBar());
				this->numBatteryLevel = (gcnew System::Windows::Forms::NumericUpDown());
				this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->BottomToolStripPanel = (gcnew System::Windows::Forms::ToolStripPanel());
				this->TopToolStripPanel = (gcnew System::Windows::Forms::ToolStripPanel());
				this->RightToolStripPanel = (gcnew System::Windows::Forms::ToolStripPanel());
				this->LeftToolStripPanel = (gcnew System::Windows::Forms::ToolStripPanel());
				this->ContentPanel = (gcnew System::Windows::Forms::ToolStripContentPanel());
				this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
				this->toolStripContainer2 = (gcnew System::Windows::Forms::ToolStripContainer());
				this->TimerSensorLOG = (gcnew System::Windows::Forms::Timer(this->components));
				this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->Connections = (gcnew System::Windows::Forms::GroupBox());
				this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
				this->UAVAutonomyLabel = (gcnew System::Windows::Forms::Label());
				this->numUAVAutonomy = (gcnew System::Windows::Forms::NumericUpDown());
				this->labelUAVAutonomy = (gcnew System::Windows::Forms::Label());
				this->numTSTime = (gcnew System::Windows::Forms::NumericUpDown());
				this->label2 = (gcnew System::Windows::Forms::Label());
				this->numBCtimeSlots = (gcnew System::Windows::Forms::NumericUpDown());
				this->label12 = (gcnew System::Windows::Forms::Label());
				this->readTime = (gcnew System::Windows::Forms::NumericUpDown());
				this->label11 = (gcnew System::Windows::Forms::Label());
				this->label9 = (gcnew System::Windows::Forms::Label());
				this->numClusterDistance = (gcnew System::Windows::Forms::NumericUpDown());
				this->label3 = (gcnew System::Windows::Forms::Label());
				this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				this->cbLog = (gcnew System::Windows::Forms::CheckBox());
				this->bRunSimulation = (gcnew System::Windows::Forms::Button());
				this->numSimulationPause = (gcnew System::Windows::Forms::NumericUpDown());
				this->label8 = (gcnew System::Windows::Forms::Label());
				this->label6 = (gcnew System::Windows::Forms::Label());
				this->numQtySimulation = (gcnew System::Windows::Forms::NumericUpDown());
				this->broadcastTime = (gcnew System::Windows::Forms::NumericUpDown());
				this->label7 = (gcnew System::Windows::Forms::Label());
				this->label5 = (gcnew System::Windows::Forms::Label());
				this->numU2DmaxConn = (gcnew System::Windows::Forms::NumericUpDown());
				this->numV2SmaxConn = (gcnew System::Windows::Forms::NumericUpDown());
				this->numV2VmaxConn = (gcnew System::Windows::Forms::NumericUpDown());
				this->numConRangeV2Sever = (gcnew System::Windows::Forms::NumericUpDown());
				this->cbUavUav = (gcnew System::Windows::Forms::CheckBox());
				this->label4 = (gcnew System::Windows::Forms::Label());
				this->cbUAVtoServer = (gcnew System::Windows::Forms::CheckBox());
				this->cbUAVtoSesnor = (gcnew System::Windows::Forms::CheckBox());
				this->SleepingTime = (gcnew System::Windows::Forms::NumericUpDown());
				this->numConRangeV2V = (gcnew System::Windows::Forms::NumericUpDown());
				this->numConRangeV2S = (gcnew System::Windows::Forms::NumericUpDown());
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
				this->dataID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				this->SensorTimer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				this->TImeSlotColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
				this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				this->simulationArea = (gcnew System::Windows::Forms::Panel());
				this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
				this->toolStrip2 = (gcnew System::Windows::Forms::ToolStrip());
				this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator28 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->ts2outputClear = (gcnew System::Windows::Forms::ToolStripButton());
				this->ts2Copy = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsDownCarret = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator29 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripSeparator21 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsLOG = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsScreenshoot = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator15 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator30 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsSimulationAreaSize2 = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator14 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsTimer2 = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator31 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsTSLabel2 = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator19 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsDecision = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator18 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsUAVHops = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator22 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsUAVFlyedDistance = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsUAVSpeedText = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator13 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsBattery = (gcnew System::Windows::Forms::ToolStripProgressBar());
				this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
				this->output = (gcnew System::Windows::Forms::TextBox());
				this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
				this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				this->tsPlay = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator12 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsBreset = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsLockReset = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsMobilityModel = (gcnew System::Windows::Forms::ToolStripComboBox());
				this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsSwapUAVs = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsBackToDeposit = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsUAVposition = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsInfo = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsStandBy = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsDrawPoint = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator16 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsGridSensor = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsMaxSensorsGrid = (gcnew System::Windows::Forms::ToolStripLabel());
				this->toolStripSeparator17 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsShowCluster = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsDrawCircleSensor = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsDrawCircleUAV = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator35 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsShowRoute = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsRedRoute = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsGreenRoute = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsBlueRoute = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsCyanRoute = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsClosedCircuit = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsRouteInfo = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator11 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsSensorDiscoveredTS = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsScanForSensors = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsSetRestriction = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsRepeatTimeSlots = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsSetTimeSlot = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsSleepSensor = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator20 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsBroadcastActivate = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsFixedTimers = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsRandSleep = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsMicroTimeSlots = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsqTimeSlots = (gcnew System::Windows::Forms::ToolStripComboBox());
				this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripSeparator9 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsUp = (gcnew System::Windows::Forms::ToolStripButton());
				this->tsDown = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsQuav = (gcnew System::Windows::Forms::ToolStripLabel());
				this->tsUAVSelect = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsQSensor = (gcnew System::Windows::Forms::ToolStripLabel());
				this->tsSensorSelect = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator10 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsSpeed = (gcnew System::Windows::Forms::ToolStripLabel());
				this->tsSpeedSelect = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator32 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsDebug = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator34 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->tsSimulationCounter = (gcnew System::Windows::Forms::ToolStripLabel());
				this->tsSound = (gcnew System::Windows::Forms::ToolStripButton());
				this->ttLOG = (gcnew System::Windows::Forms::ToolTip(this->components));
				this->nextStepTimer = (gcnew System::Windows::Forms::Timer(this->components));
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tsStepInterval))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBatteryLevel))->BeginInit();
				this->toolStripContainer1->SuspendLayout();
				this->toolStripContainer2->SuspendLayout();
				this->tabControl1->SuspendLayout();
				this->tabPage3->SuspendLayout();
				this->tableLayoutPanel4->SuspendLayout();
				this->Connections->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->BeginInit();
				this->splitContainer2->Panel1->SuspendLayout();
				this->splitContainer2->Panel2->SuspendLayout();
				this->splitContainer2->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUAVAutonomy))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTSTime))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBCtimeSlots))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->readTime))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numClusterDistance))->BeginInit();
				this->groupBox1->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numSimulationPause))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numQtySimulation))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->broadcastTime))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numU2DmaxConn))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numV2SmaxConn))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numV2VmaxConn))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2Sever))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SleepingTime))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2V))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2S))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
				this->tableLayoutPanel1->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
				this->splitContainer1->Panel1->SuspendLayout();
				this->splitContainer1->Panel2->SuspendLayout();
				this->splitContainer1->SuspendLayout();
				this->toolStrip2->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->BeginInit();
				this->splitContainer3->Panel1->SuspendLayout();
				this->splitContainer3->Panel2->SuspendLayout();
				this->splitContainer3->SuspendLayout();
				this->groupBox2->SuspendLayout();
				this->toolStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// Timer1sec
				// 
				this->Timer1sec->Interval = 500;
				this->Timer1sec->Tick += gcnew System::EventHandler(this, &simulator::timer1sec_Tick);
				// 
				// ttShowInfo
				// 
				this->ttShowInfo->AutomaticDelay = 750;
				this->ttShowInfo->AutoPopDelay = 7500;
				this->ttShowInfo->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				this->ttShowInfo->InitialDelay = 750;
				this->ttShowInfo->ReshowDelay = 1000;
				this->ttShowInfo->ShowAlways = true;
				this->ttShowInfo->ToolTipIcon = System::Windows::Forms::ToolTipIcon::Info;
				this->ttShowInfo->ToolTipTitle = L"Information";
				// 
				// tsStepInterval
				// 
				this->tsStepInterval->LargeChange = 20;
				this->tsStepInterval->Location = System::Drawing::Point(88, 304);
				this->tsStepInterval->Maximum = 250;
				this->tsStepInterval->Minimum = 50;
				this->tsStepInterval->Name = L"tsStepInterval";
				this->tsStepInterval->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
				this->tsStepInterval->Size = System::Drawing::Size(136, 45);
				this->tsStepInterval->SmallChange = 20;
				this->tsStepInterval->TabIndex = 127;
				this->tsStepInterval->TickFrequency = 20;
				this->ttShowInfo->SetToolTip(this->tsStepInterval, L"Timer Interval: ");
				this->tsStepInterval->Value = 150;
				this->tsStepInterval->Scroll += gcnew System::EventHandler(this, &simulator::tbPause_Scroll_1);
				// 
				// numBatteryLevel
				// 
				this->numBatteryLevel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numBatteryLevel->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				this->numBatteryLevel->Location = System::Drawing::Point(178, 136);
				this->numBatteryLevel->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 90, 0, 0, 0 });
				this->numBatteryLevel->Name = L"numBatteryLevel";
				this->numBatteryLevel->Size = System::Drawing::Size(42, 20);
				this->numBatteryLevel->TabIndex = 141;
				this->ttShowInfo->SetToolTip(this->numBatteryLevel, L"Battery Level to Return to Base Station  (RTH)");
				this->numBatteryLevel->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				// 
				// checkBox8
				// 
				this->checkBox8->AutoSize = true;
				this->checkBox8->Checked = true;
				this->checkBox8->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox8->Location = System::Drawing::Point(166, 30);
				this->checkBox8->Name = L"checkBox8";
				this->checkBox8->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox8->Size = System::Drawing::Size(90, 17);
				this->checkBox8->TabIndex = 5;
				this->checkBox8->Text = L"Disc. TS";
				this->ttLOG->SetToolTip(this->checkBox8, L"LOG how many DIscovered Sensors has been found");
				this->checkBox8->UseVisualStyleBackColor = true;
				// 
				// checkBox4
				// 
				this->checkBox4->AutoSize = true;
				this->checkBox4->Checked = true;
				this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox4->Location = System::Drawing::Point(28, 51);
				this->checkBox4->Name = L"checkBox4";
				this->checkBox4->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox4->Size = System::Drawing::Size(90, 17);
				this->checkBox4->TabIndex = 4;
				this->checkBox4->Text = L"TimeSlot";
				this->ttLOG->SetToolTip(this->checkBox4, L"LOG actual time Slots as a reference of time");
				this->checkBox4->UseVisualStyleBackColor = true;
				// 
				// checkBox3
				// 
				this->checkBox3->AutoSize = true;
				this->checkBox3->Checked = true;
				this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox3->Location = System::Drawing::Point(28, 76);
				this->checkBox3->Name = L"checkBox3";
				this->checkBox3->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox3->Size = System::Drawing::Size(138, 17);
				this->checkBox3->TabIndex = 2;
				this->checkBox3->Text = L"UAV Flyed Dist";
				this->ttLOG->SetToolTip(this->checkBox3, L"LOG UAV Flyed distance");
				this->checkBox3->UseVisualStyleBackColor = true;
				// 
				// checkBox2
				// 
				this->checkBox2->AutoSize = true;
				this->checkBox2->Checked = true;
				this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox2->Location = System::Drawing::Point(28, 99);
				this->checkBox2->Name = L"checkBox2";
				this->checkBox2->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox2->Size = System::Drawing::Size(98, 17);
				this->checkBox2->TabIndex = 1;
				this->checkBox2->Text = L"UAV Speed";
				this->ttLOG->SetToolTip(this->checkBox2, L"LOG UAV speed");
				this->checkBox2->UseVisualStyleBackColor = true;
				// 
				// checkBox1
				// 
				this->checkBox1->AutoSize = true;
				this->checkBox1->Checked = true;
				this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox1->Location = System::Drawing::Point(28, 28);
				this->checkBox1->Name = L"checkBox1";
				this->checkBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox1->Size = System::Drawing::Size(82, 17);
				this->checkBox1->TabIndex = 0;
				this->checkBox1->Text = L"Sensors";
				this->ttLOG->SetToolTip(this->checkBox1, L"LOG sensor state broadcast and Sleeping changes");
				this->checkBox1->UseVisualStyleBackColor = true;
				// 
				// BottomToolStripPanel
				// 
				this->BottomToolStripPanel->Location = System::Drawing::Point(0, 0);
				this->BottomToolStripPanel->Name = L"BottomToolStripPanel";
				this->BottomToolStripPanel->Orientation = System::Windows::Forms::Orientation::Horizontal;
				this->BottomToolStripPanel->RowMargin = System::Windows::Forms::Padding(3, 0, 0, 0);
				this->BottomToolStripPanel->Size = System::Drawing::Size(0, 0);
				// 
				// TopToolStripPanel
				// 
				this->TopToolStripPanel->Location = System::Drawing::Point(0, 0);
				this->TopToolStripPanel->Name = L"TopToolStripPanel";
				this->TopToolStripPanel->Orientation = System::Windows::Forms::Orientation::Horizontal;
				this->TopToolStripPanel->RowMargin = System::Windows::Forms::Padding(3, 0, 0, 0);
				this->TopToolStripPanel->Size = System::Drawing::Size(0, 0);
				// 
				// RightToolStripPanel
				// 
				this->RightToolStripPanel->Location = System::Drawing::Point(0, 0);
				this->RightToolStripPanel->Name = L"RightToolStripPanel";
				this->RightToolStripPanel->Orientation = System::Windows::Forms::Orientation::Horizontal;
				this->RightToolStripPanel->RowMargin = System::Windows::Forms::Padding(3, 0, 0, 0);
				this->RightToolStripPanel->Size = System::Drawing::Size(0, 0);
				// 
				// LeftToolStripPanel
				// 
				this->LeftToolStripPanel->Location = System::Drawing::Point(0, 0);
				this->LeftToolStripPanel->Name = L"LeftToolStripPanel";
				this->LeftToolStripPanel->Orientation = System::Windows::Forms::Orientation::Horizontal;
				this->LeftToolStripPanel->RowMargin = System::Windows::Forms::Padding(3, 0, 0, 0);
				this->LeftToolStripPanel->Size = System::Drawing::Size(0, 0);
				// 
				// ContentPanel
				// 
				this->ContentPanel->Size = System::Drawing::Size(1079, 762);
				// 
				// toolStripContainer1
				// 
				// 
				// toolStripContainer1.ContentPanel
				// 
				this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(1476, 802);
				this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->toolStripContainer1->Location = System::Drawing::Point(0, 0);
				this->toolStripContainer1->Name = L"toolStripContainer1";
				this->toolStripContainer1->Size = System::Drawing::Size(1476, 827);
				this->toolStripContainer1->TabIndex = 0;
				this->toolStripContainer1->Text = L"toolStripContainer1";
				// 
				// toolStripContainer2
				// 
				this->toolStripContainer2->BottomToolStripPanelVisible = false;
				// 
				// toolStripContainer2.ContentPanel
				// 
				this->toolStripContainer2->ContentPanel->Size = System::Drawing::Size(1476, 802);
				this->toolStripContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
				this->toolStripContainer2->LeftToolStripPanelVisible = false;
				this->toolStripContainer2->Location = System::Drawing::Point(0, 0);
				this->toolStripContainer2->Name = L"toolStripContainer2";
				this->toolStripContainer2->RightToolStripPanelVisible = false;
				this->toolStripContainer2->Size = System::Drawing::Size(1476, 827);
				this->toolStripContainer2->TabIndex = 0;
				this->toolStripContainer2->Text = L"toolStripContainer2";
				// 
				// TimerSensorLOG
				// 
				this->TimerSensorLOG->Interval = 500;
				this->TimerSensorLOG->Tick += gcnew System::EventHandler(this, &simulator::TimerSensorLOG_Tick);
				// 
				// tabControl1
				// 
				this->tabControl1->Controls->Add(this->tabPage3);
				this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tabControl1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->tabControl1->Location = System::Drawing::Point(0, 0);
				this->tabControl1->Name = L"tabControl1";
				this->tabControl1->SelectedIndex = 0;
				this->tabControl1->Size = System::Drawing::Size(1476, 827);
				this->tabControl1->TabIndex = 12;
				// 
				// tabPage3
				// 
				this->tabPage3->BackColor = System::Drawing::Color::WhiteSmoke;
				this->tabPage3->Controls->Add(this->tableLayoutPanel4);
				this->tabPage3->Controls->Add(this->tableLayoutPanel1);
				this->tabPage3->Controls->Add(this->toolStrip1);
				this->tabPage3->Location = System::Drawing::Point(4, 23);
				this->tabPage3->Name = L"tabPage3";
				this->tabPage3->Padding = System::Windows::Forms::Padding(3);
				this->tabPage3->Size = System::Drawing::Size(1468, 800);
				this->tabPage3->TabIndex = 2;
				this->tabPage3->Text = L"Simulator";
				// 
				// tableLayoutPanel4
				// 
				this->tableLayoutPanel4->ColumnCount = 1;
				this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
				this->tableLayoutPanel4->Controls->Add(this->Connections, 0, 0);
				this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Right;
				this->tableLayoutPanel4->Location = System::Drawing::Point(1230, 28);
				this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				this->tableLayoutPanel4->RowCount = 1;
				this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 52.53682F)));
				this->tableLayoutPanel4->Size = System::Drawing::Size(235, 769);
				this->tableLayoutPanel4->TabIndex = 11;
				// 
				// Connections
				// 
				this->Connections->Controls->Add(this->splitContainer2);
				this->Connections->Dock = System::Windows::Forms::DockStyle::Fill;
				this->Connections->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->Connections->Location = System::Drawing::Point(3, 3);
				this->Connections->Name = L"Connections";
				this->Connections->Size = System::Drawing::Size(229, 763);
				this->Connections->TabIndex = 11;
				this->Connections->TabStop = false;
				this->Connections->Text = L" Configuration ";
				// 
				// splitContainer2
				// 
				this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
				this->splitContainer2->Location = System::Drawing::Point(3, 17);
				this->splitContainer2->Name = L"splitContainer2";
				this->splitContainer2->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// splitContainer2.Panel1
				// 
				this->splitContainer2->Panel1->Controls->Add(this->numBatteryLevel);
				this->splitContainer2->Panel1->Controls->Add(this->UAVAutonomyLabel);
				this->splitContainer2->Panel1->Controls->Add(this->numUAVAutonomy);
				this->splitContainer2->Panel1->Controls->Add(this->labelUAVAutonomy);
				this->splitContainer2->Panel1->Controls->Add(this->numTSTime);
				this->splitContainer2->Panel1->Controls->Add(this->label2);
				this->splitContainer2->Panel1->Controls->Add(this->numBCtimeSlots);
				this->splitContainer2->Panel1->Controls->Add(this->label12);
				this->splitContainer2->Panel1->Controls->Add(this->readTime);
				this->splitContainer2->Panel1->Controls->Add(this->label11);
				this->splitContainer2->Panel1->Controls->Add(this->label9);
				this->splitContainer2->Panel1->Controls->Add(this->tsStepInterval);
				this->splitContainer2->Panel1->Controls->Add(this->numClusterDistance);
				this->splitContainer2->Panel1->Controls->Add(this->label3);
				this->splitContainer2->Panel1->Controls->Add(this->groupBox1);
				this->splitContainer2->Panel1->Controls->Add(this->broadcastTime);
				this->splitContainer2->Panel1->Controls->Add(this->label7);
				this->splitContainer2->Panel1->Controls->Add(this->label5);
				this->splitContainer2->Panel1->Controls->Add(this->numU2DmaxConn);
				this->splitContainer2->Panel1->Controls->Add(this->numV2SmaxConn);
				this->splitContainer2->Panel1->Controls->Add(this->numV2VmaxConn);
				this->splitContainer2->Panel1->Controls->Add(this->numConRangeV2Sever);
				this->splitContainer2->Panel1->Controls->Add(this->cbUavUav);
				this->splitContainer2->Panel1->Controls->Add(this->label4);
				this->splitContainer2->Panel1->Controls->Add(this->cbUAVtoServer);
				this->splitContainer2->Panel1->Controls->Add(this->cbUAVtoSesnor);
				this->splitContainer2->Panel1->Controls->Add(this->SleepingTime);
				this->splitContainer2->Panel1->Controls->Add(this->numConRangeV2V);
				this->splitContainer2->Panel1->Controls->Add(this->numConRangeV2S);
				this->splitContainer2->Panel1->Controls->Add(this->label1);
				// 
				// splitContainer2.Panel2
				// 
				this->splitContainer2->Panel2->Controls->Add(this->dataGridView);
				this->splitContainer2->Size = System::Drawing::Size(223, 743);
				this->splitContainer2->SplitterDistance = 515;
				this->splitContainer2->TabIndex = 103;
				// 
				// UAVAutonomyLabel
				// 
				this->UAVAutonomyLabel->AutoSize = true;
				this->UAVAutonomyLabel->Location = System::Drawing::Point(6, 139);
				this->UAVAutonomyLabel->Name = L"UAVAutonomyLabel";
				this->UAVAutonomyLabel->Size = System::Drawing::Size(103, 14);
				this->UAVAutonomyLabel->TabIndex = 140;
				this->UAVAutonomyLabel->Text = L"Autonomy (s)";
				// 
				// numUAVAutonomy
				// 
				this->numUAVAutonomy->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numUAVAutonomy->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 60, 0, 0, 0 });
				this->numUAVAutonomy->Location = System::Drawing::Point(118, 136);
				this->numUAVAutonomy->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3600, 0, 0, 0 });
				this->numUAVAutonomy->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
				this->numUAVAutonomy->Name = L"numUAVAutonomy";
				this->numUAVAutonomy->Size = System::Drawing::Size(54, 20);
				this->numUAVAutonomy->TabIndex = 138;
				this->numUAVAutonomy->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 600, 0, 0, 0 });
				// 
				// labelUAVAutonomy
				// 
				this->labelUAVAutonomy->AutoSize = true;
				this->labelUAVAutonomy->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->labelUAVAutonomy->Location = System::Drawing::Point(52, 183);
				this->labelUAVAutonomy->Name = L"labelUAVAutonomy";
				this->labelUAVAutonomy->Size = System::Drawing::Size(0, 14);
				this->labelUAVAutonomy->TabIndex = 137;
				// 
				// numTSTime
				// 
				this->numTSTime->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numTSTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				this->numTSTime->Location = System::Drawing::Point(134, 166);
				this->numTSTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3600000, 0, 0, 0 });
				this->numTSTime->Name = L"numTSTime";
				this->numTSTime->Size = System::Drawing::Size(84, 20);
				this->numTSTime->TabIndex = 136;
				this->numTSTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				// 
				// label2
				// 
				this->label2->AutoSize = true;
				this->label2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label2->Location = System::Drawing::Point(5, 169);
				this->label2->Name = L"label2";
				this->label2->Size = System::Drawing::Size(111, 14);
				this->label2->TabIndex = 135;
				this->label2->Text = L"TimeSlot Time";
				// 
				// numBCtimeSlots
				// 
				this->numBCtimeSlots->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numBCtimeSlots->Location = System::Drawing::Point(134, 194);
				this->numBCtimeSlots->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				this->numBCtimeSlots->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				this->numBCtimeSlots->Name = L"numBCtimeSlots";
				this->numBCtimeSlots->Size = System::Drawing::Size(84, 20);
				this->numBCtimeSlots->TabIndex = 133;
				this->numBCtimeSlots->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
				// 
				// label12
				// 
				this->label12->AutoSize = true;
				this->label12->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label12->Location = System::Drawing::Point(5, 197);
				this->label12->Name = L"label12";
				this->label12->Size = System::Drawing::Size(103, 14);
				this->label12->TabIndex = 132;
				this->label12->Text = L"BC TimeSlots";
				// 
				// readTime
				// 
				this->readTime->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->readTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
				this->readTime->Location = System::Drawing::Point(134, 278);
				this->readTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
				this->readTime->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				this->readTime->Name = L"readTime";
				this->readTime->Size = System::Drawing::Size(84, 20);
				this->readTime->TabIndex = 130;
				this->readTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000, 0, 0, 0 });
				// 
				// label11
				// 
				this->label11->AutoSize = true;
				this->label11->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label11->Location = System::Drawing::Point(5, 280);
				this->label11->Name = L"label11";
				this->label11->Size = System::Drawing::Size(79, 14);
				this->label11->TabIndex = 129;
				this->label11->Text = L"Read Time";
				// 
				// label9
				// 
				this->label9->AutoSize = true;
				this->label9->Location = System::Drawing::Point(5, 309);
				this->label9->Name = L"label9";
				this->label9->Size = System::Drawing::Size(87, 28);
				this->label9->TabIndex = 124;
				this->label9->Text = L"UAV Speed \r\n(m/s)";
				this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// numClusterDistance
				// 
				this->numClusterDistance->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
				this->numClusterDistance->Location = System::Drawing::Point(118, 106);
				this->numClusterDistance->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 500, 0, 0, 0 });
				this->numClusterDistance->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
				this->numClusterDistance->Name = L"numClusterDistance";
				this->numClusterDistance->Size = System::Drawing::Size(100, 21);
				this->numClusterDistance->TabIndex = 125;
				this->numClusterDistance->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 300, 0, 0, 0 });
				// 
				// label3
				// 
				this->label3->AutoSize = true;
				this->label3->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label3->Location = System::Drawing::Point(7, 109);
				this->label3->Name = L"label3";
				this->label3->Size = System::Drawing::Size(111, 14);
				this->label3->TabIndex = 126;
				this->label3->Text = L"Cluster Dist.";
				// 
				// groupBox1
				// 
				this->groupBox1->BackColor = System::Drawing::Color::Transparent;
				this->groupBox1->Controls->Add(this->cbLog);
				this->groupBox1->Controls->Add(this->bRunSimulation);
				this->groupBox1->Controls->Add(this->numSimulationPause);
				this->groupBox1->Controls->Add(this->label8);
				this->groupBox1->Controls->Add(this->label6);
				this->groupBox1->Controls->Add(this->numQtySimulation);
				this->groupBox1->Location = System::Drawing::Point(8, 352);
				this->groupBox1->Name = L"groupBox1";
				this->groupBox1->Size = System::Drawing::Size(210, 154);
				this->groupBox1->TabIndex = 122;
				this->groupBox1->TabStop = false;
				this->groupBox1->Text = L"Path Simulator ";
				// 
				// cbLog
				// 
				this->cbLog->AutoSize = true;
				this->cbLog->Checked = true;
				this->cbLog->CheckState = System::Windows::Forms::CheckState::Checked;
				this->cbLog->Location = System::Drawing::Point(8, 80);
				this->cbLog->Name = L"cbLog";
				this->cbLog->Size = System::Drawing::Size(178, 18);
				this->cbLog->TabIndex = 94;
				this->cbLog->Text = L"Save simulation log";
				this->cbLog->UseVisualStyleBackColor = true;
				// 
				// bRunSimulation
				// 
				this->bRunSimulation->BackColor = System::Drawing::Color::Transparent;
				this->bRunSimulation->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->bRunSimulation->Location = System::Drawing::Point(6, 108);
				this->bRunSimulation->Name = L"bRunSimulation";
				this->bRunSimulation->Size = System::Drawing::Size(194, 33);
				this->bRunSimulation->TabIndex = 87;
				this->bRunSimulation->Text = L"Simulate !";
				this->bRunSimulation->UseVisualStyleBackColor = false;
				this->bRunSimulation->Click += gcnew System::EventHandler(this, &simulator::bRunSimulation_Click);
				// 
				// numSimulationPause
				// 
				this->numSimulationPause->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				this->numSimulationPause->Location = System::Drawing::Point(117, 48);
				this->numSimulationPause->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
				this->numSimulationPause->Name = L"numSimulationPause";
				this->numSimulationPause->Size = System::Drawing::Size(85, 21);
				this->numSimulationPause->TabIndex = 91;
				this->numSimulationPause->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				// 
				// label8
				// 
				this->label8->AutoSize = true;
				this->label8->Location = System::Drawing::Point(7, 52);
				this->label8->Name = L"label8";
				this->label8->Size = System::Drawing::Size(87, 14);
				this->label8->TabIndex = 90;
				this->label8->Text = L"Pause (ms)";
				// 
				// label6
				// 
				this->label6->AutoSize = true;
				this->label6->Location = System::Drawing::Point(6, 26);
				this->label6->Name = L"label6";
				this->label6->Size = System::Drawing::Size(95, 14);
				this->label6->TabIndex = 86;
				this->label6->Text = L"Simulations";
				// 
				// numQtySimulation
				// 
				this->numQtySimulation->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
				this->numQtySimulation->Location = System::Drawing::Point(117, 23);
				this->numQtySimulation->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				this->numQtySimulation->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				this->numQtySimulation->Name = L"numQtySimulation";
				this->numQtySimulation->Size = System::Drawing::Size(85, 21);
				this->numQtySimulation->TabIndex = 85;
				this->numQtySimulation->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
				// 
				// broadcastTime
				// 
				this->broadcastTime->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->broadcastTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				this->broadcastTime->Location = System::Drawing::Point(134, 222);
				this->broadcastTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 600000, 0, 0, 0 });
				this->broadcastTime->Name = L"broadcastTime";
				this->broadcastTime->Size = System::Drawing::Size(84, 20);
				this->broadcastTime->TabIndex = 107;
				this->broadcastTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
				// 
				// label7
				// 
				this->label7->AutoSize = true;
				this->label7->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label7->Location = System::Drawing::Point(5, 226);
				this->label7->Name = L"label7";
				this->label7->Size = System::Drawing::Size(63, 14);
				this->label7->TabIndex = 104;
				this->label7->Text = L"BC Time";
				// 
				// label5
				// 
				this->label5->AutoSize = true;
				this->label5->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label5->Location = System::Drawing::Point(166, 6);
				this->label5->Name = L"label5";
				this->label5->Size = System::Drawing::Size(47, 14);
				this->label5->TabIndex = 121;
				this->label5->Text = L"Range";
				// 
				// numU2DmaxConn
				// 
				this->numU2DmaxConn->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numU2DmaxConn->Location = System::Drawing::Point(118, 77);
				this->numU2DmaxConn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				this->numU2DmaxConn->Name = L"numU2DmaxConn";
				this->numU2DmaxConn->Size = System::Drawing::Size(42, 20);
				this->numU2DmaxConn->TabIndex = 120;
				this->numU2DmaxConn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
				// 
				// numV2SmaxConn
				// 
				this->numV2SmaxConn->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numV2SmaxConn->Location = System::Drawing::Point(118, 51);
				this->numV2SmaxConn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				this->numV2SmaxConn->Name = L"numV2SmaxConn";
				this->numV2SmaxConn->Size = System::Drawing::Size(42, 20);
				this->numV2SmaxConn->TabIndex = 119;
				this->numV2SmaxConn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
				// 
				// numV2VmaxConn
				// 
				this->numV2VmaxConn->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numV2VmaxConn->Location = System::Drawing::Point(118, 25);
				this->numV2VmaxConn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
				this->numV2VmaxConn->Name = L"numV2VmaxConn";
				this->numV2VmaxConn->Size = System::Drawing::Size(42, 20);
				this->numV2VmaxConn->TabIndex = 118;
				this->numV2VmaxConn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
				// 
				// numConRangeV2Sever
				// 
				this->numConRangeV2Sever->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numConRangeV2Sever->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
				this->numConRangeV2Sever->Location = System::Drawing::Point(166, 77);
				this->numConRangeV2Sever->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
				this->numConRangeV2Sever->Name = L"numConRangeV2Sever";
				this->numConRangeV2Sever->Size = System::Drawing::Size(52, 20);
				this->numConRangeV2Sever->TabIndex = 115;
				this->numConRangeV2Sever->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
				// 
				// cbUavUav
				// 
				this->cbUavUav->AutoSize = true;
				this->cbUavUav->Checked = true;
				this->cbUavUav->CheckState = System::Windows::Forms::CheckState::Checked;
				this->cbUavUav->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->cbUavUav->Location = System::Drawing::Point(13, 25);
				this->cbUavUav->Name = L"cbUavUav";
				this->cbUavUav->Size = System::Drawing::Size(93, 20);
				this->cbUavUav->TabIndex = 105;
				this->cbUavUav->Text = L"UAV - UAV";
				this->cbUavUav->UseVisualStyleBackColor = true;
				this->cbUavUav->CheckedChanged += gcnew System::EventHandler(this, &simulator::cbUavUav_CheckedChanged);
				// 
				// label4
				// 
				this->label4->AutoSize = true;
				this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label4->Location = System::Drawing::Point(122, 6);
				this->label4->Name = L"label4";
				this->label4->Size = System::Drawing::Size(31, 14);
				this->label4->TabIndex = 111;
				this->label4->Text = L"Max";
				// 
				// cbUAVtoServer
				// 
				this->cbUAVtoServer->AutoSize = true;
				this->cbUAVtoServer->Checked = true;
				this->cbUAVtoServer->CheckState = System::Windows::Forms::CheckState::Checked;
				this->cbUAVtoServer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->cbUAVtoServer->Location = System::Drawing::Point(13, 77);
				this->cbUAVtoServer->Name = L"cbUAVtoServer";
				this->cbUAVtoServer->Size = System::Drawing::Size(105, 20);
				this->cbUAVtoServer->TabIndex = 114;
				this->cbUAVtoServer->Text = L"UAV - Server";
				this->cbUAVtoServer->UseVisualStyleBackColor = true;
				this->cbUAVtoServer->CheckedChanged += gcnew System::EventHandler(this, &simulator::cbUAVtoServer_CheckedChanged_1);
				// 
				// cbUAVtoSesnor
				// 
				this->cbUAVtoSesnor->AutoSize = true;
				this->cbUAVtoSesnor->Checked = true;
				this->cbUAVtoSesnor->CheckState = System::Windows::Forms::CheckState::Checked;
				this->cbUAVtoSesnor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->cbUAVtoSesnor->Location = System::Drawing::Point(13, 51);
				this->cbUAVtoSesnor->Name = L"cbUAVtoSesnor";
				this->cbUAVtoSesnor->Size = System::Drawing::Size(108, 20);
				this->cbUAVtoSesnor->TabIndex = 103;
				this->cbUAVtoSesnor->Text = L"UAV - Sensor";
				this->cbUAVtoSesnor->UseVisualStyleBackColor = true;
				this->cbUAVtoSesnor->CheckedChanged += gcnew System::EventHandler(this, &simulator::cbUAVtoSesnor_CheckedChanged);
				// 
				// SleepingTime
				// 
				this->SleepingTime->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->SleepingTime->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				this->SleepingTime->Location = System::Drawing::Point(134, 248);
				this->SleepingTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3600000, 0, 0, 0 });
				this->SleepingTime->Name = L"SleepingTime";
				this->SleepingTime->Size = System::Drawing::Size(84, 20);
				this->SleepingTime->TabIndex = 106;
				this->SleepingTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30000, 0, 0, 0 });
				// 
				// numConRangeV2V
				// 
				this->numConRangeV2V->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numConRangeV2V->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
				this->numConRangeV2V->Location = System::Drawing::Point(166, 25);
				this->numConRangeV2V->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
				this->numConRangeV2V->Name = L"numConRangeV2V";
				this->numConRangeV2V->Size = System::Drawing::Size(52, 20);
				this->numConRangeV2V->TabIndex = 109;
				this->numConRangeV2V->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
				// 
				// numConRangeV2S
				// 
				this->numConRangeV2S->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->numConRangeV2S->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
				this->numConRangeV2S->Location = System::Drawing::Point(166, 51);
				this->numConRangeV2S->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5000, 0, 0, 0 });
				this->numConRangeV2S->Name = L"numConRangeV2S";
				this->numConRangeV2S->Size = System::Drawing::Size(52, 20);
				this->numConRangeV2S->TabIndex = 108;
				this->numConRangeV2S->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
				this->numConRangeV2S->ValueChanged += gcnew System::EventHandler(this, &simulator::numConRangeV2S_ValueChanged);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->label1->Location = System::Drawing::Point(5, 252);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(87, 14);
				this->label1->TabIndex = 113;
				this->label1->Text = L"Sleep Time";
				// 
				// dataGridView
				// 
				this->dataGridView->AllowUserToAddRows = false;
				this->dataGridView->BackgroundColor = System::Drawing::SystemColors::ControlLight;
				this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
				this->dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
					this->dataID,
						this->SensorTimer, this->TImeSlotColumn
				});
				dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
				dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Window;
				dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::ControlText;
				dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
				dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::ControlText;
				dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
				this->dataGridView->DefaultCellStyle = dataGridViewCellStyle4;
				this->dataGridView->Dock = System::Windows::Forms::DockStyle::Fill;
				this->dataGridView->Location = System::Drawing::Point(0, 0);
				this->dataGridView->Name = L"dataGridView";
				dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
				dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Control;
				dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::WindowText;
				dataGridViewCellStyle5->SelectionBackColor = System::Drawing::Color::Transparent;
				dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
				dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
				this->dataGridView->RowHeadersDefaultCellStyle = dataGridViewCellStyle5;
				this->dataGridView->RowHeadersVisible = false;
				dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
				dataGridViewCellStyle6->BackColor = System::Drawing::Color::White;
				dataGridViewCellStyle6->ForeColor = System::Drawing::Color::Black;
				dataGridViewCellStyle6->SelectionBackColor = System::Drawing::Color::White;
				dataGridViewCellStyle6->SelectionForeColor = System::Drawing::Color::Black;
				this->dataGridView->RowsDefaultCellStyle = dataGridViewCellStyle6;
				this->dataGridView->RowTemplate->DefaultCellStyle->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
				this->dataGridView->Size = System::Drawing::Size(223, 224);
				this->dataGridView->TabIndex = 103;
				// 
				// dataID
				// 
				this->dataID->HeaderText = L"ID";
				this->dataID->Name = L"dataID";
				this->dataID->Width = 35;
				// 
				// SensorTimer
				// 
				this->SensorTimer->HeaderText = L"Timer";
				this->SensorTimer->Name = L"SensorTimer";
				this->SensorTimer->Width = 65;
				// 
				// TImeSlotColumn
				// 
				this->TImeSlotColumn->HeaderText = L"TimeSlot(O/N)";
				this->TImeSlotColumn->Name = L"TImeSlotColumn";
				this->TImeSlotColumn->Width = 110;
				// 
				// tableLayoutPanel1
				// 
				this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					| System::Windows::Forms::AnchorStyles::Left)
					| System::Windows::Forms::AnchorStyles::Right));
				this->tableLayoutPanel1->ColumnCount = 1;
				this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					50)));
				this->tableLayoutPanel1->Controls->Add(this->simulationArea, 0, 0);
				this->tableLayoutPanel1->Controls->Add(this->splitContainer1, 0, 1);
				this->tableLayoutPanel1->Location = System::Drawing::Point(6, 31);
				this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				this->tableLayoutPanel1->RowCount = 2;
				this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 76.43678F)));
				this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 23.56322F)));
				this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				this->tableLayoutPanel1->Size = System::Drawing::Size(1218, 763);
				this->tableLayoutPanel1->TabIndex = 1;
				// 
				// simulationArea
				// 
				this->simulationArea->BackColor = System::Drawing::Color::White;
				this->simulationArea->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
				this->simulationArea->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				this->simulationArea->Cursor = System::Windows::Forms::Cursors::Arrow;
				this->simulationArea->Dock = System::Windows::Forms::DockStyle::Fill;
				this->simulationArea->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->simulationArea->Location = System::Drawing::Point(3, 3);
				this->simulationArea->Name = L"simulationArea";
				this->simulationArea->Padding = System::Windows::Forms::Padding(5);
				this->simulationArea->Size = System::Drawing::Size(1212, 577);
				this->simulationArea->TabIndex = 3;
				this->simulationArea->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &simulator::simulationArea_Paint);
				this->simulationArea->Resize += gcnew System::EventHandler(this, &simulator::simulationArea_Resize);
				// 
				// splitContainer1
				// 
				this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->splitContainer1->IsSplitterFixed = true;
				this->splitContainer1->Location = System::Drawing::Point(3, 586);
				this->splitContainer1->Name = L"splitContainer1";
				this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// splitContainer1.Panel1
				// 
				this->splitContainer1->Panel1->Controls->Add(this->toolStrip2);
				// 
				// splitContainer1.Panel2
				// 
				this->splitContainer1->Panel2->Controls->Add(this->splitContainer3);
				this->splitContainer1->Size = System::Drawing::Size(1212, 174);
				this->splitContainer1->SplitterDistance = 26;
				this->splitContainer1->TabIndex = 4;
				// 
				// toolStrip2
				// 
				this->toolStrip2->AllowItemReorder = true;
				this->toolStrip2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9));
				this->toolStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(28) {
					this->toolStripLabel1,
						this->toolStripSeparator28, this->ts2outputClear, this->ts2Copy, this->toolStripSeparator8, this->tsDownCarret, this->toolStripSeparator29,
						this->toolStripSeparator21, this->tsLOG, this->tsScreenshoot, this->toolStripSeparator15, this->toolStripButton1, this->toolStripSeparator30,
						this->tsSimulationAreaSize2, this->toolStripSeparator14, this->tsTimer2, this->toolStripSeparator31, this->tsTSLabel2, this->toolStripSeparator19,
						this->tsDecision, this->toolStripSeparator18, this->tsUAVHops, this->toolStripSeparator22, this->tsUAVFlyedDistance, this->toolStripSeparator4,
						this->tsUAVSpeedText, this->toolStripSeparator13, this->tsBattery
				});
				this->toolStrip2->Location = System::Drawing::Point(0, 0);
				this->toolStrip2->Name = L"toolStrip2";
				this->toolStrip2->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
				this->toolStrip2->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->toolStrip2->Size = System::Drawing::Size(1212, 25);
				this->toolStrip2->TabIndex = 0;
				this->toolStrip2->Text = L"toolStrip2";
				// 
				// toolStripLabel1
				// 
				this->toolStripLabel1->DoubleClickEnabled = true;
				this->toolStripLabel1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->toolStripLabel1->Name = L"toolStripLabel1";
				this->toolStripLabel1->Size = System::Drawing::Size(55, 22);
				this->toolStripLabel1->Text = L"Output";
				// 
				// toolStripSeparator28
				// 
				this->toolStripSeparator28->Name = L"toolStripSeparator28";
				this->toolStripSeparator28->Size = System::Drawing::Size(6, 25);
				// 
				// ts2outputClear
				// 
				this->ts2outputClear->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->ts2outputClear->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ts2outputClear.Image")));
				this->ts2outputClear->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->ts2outputClear->Name = L"ts2outputClear";
				this->ts2outputClear->Size = System::Drawing::Size(23, 22);
				this->ts2outputClear->Text = L"toolStripButton1";
				this->ts2outputClear->ToolTipText = L"Clear output text";
				this->ts2outputClear->Click += gcnew System::EventHandler(this, &simulator::toolStripButton1_Click);
				// 
				// ts2Copy
				// 
				this->ts2Copy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->ts2Copy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ts2Copy.Image")));
				this->ts2Copy->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->ts2Copy->Name = L"ts2Copy";
				this->ts2Copy->Size = System::Drawing::Size(23, 22);
				this->ts2Copy->Text = L"toolStripButton1";
				this->ts2Copy->ToolTipText = L"Copy Output Text to Clipboard";
				this->ts2Copy->Click += gcnew System::EventHandler(this, &simulator::ts2Copy_Click);
				// 
				// toolStripSeparator8
				// 
				this->toolStripSeparator8->Name = L"toolStripSeparator8";
				this->toolStripSeparator8->Size = System::Drawing::Size(6, 25);
				// 
				// tsDownCarret
				// 
				this->tsDownCarret->Checked = true;
				this->tsDownCarret->CheckOnClick = true;
				this->tsDownCarret->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsDownCarret->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDownCarret->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDownCarret.Image")));
				this->tsDownCarret->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDownCarret->Name = L"tsDownCarret";
				this->tsDownCarret->Size = System::Drawing::Size(23, 22);
				this->tsDownCarret->ToolTipText = L"Autoscroll to last line";
				// 
				// toolStripSeparator29
				// 
				this->toolStripSeparator29->Name = L"toolStripSeparator29";
				this->toolStripSeparator29->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripSeparator21
				// 
				this->toolStripSeparator21->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator21->Name = L"toolStripSeparator21";
				this->toolStripSeparator21->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->toolStripSeparator21->Size = System::Drawing::Size(6, 25);
				// 
				// tsLOG
				// 
				this->tsLOG->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsLOG->Checked = true;
				this->tsLOG->CheckOnClick = true;
				this->tsLOG->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsLOG->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsLOG->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsLOG->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsLOG.Image")));
				this->tsLOG->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsLOG->Name = L"tsLOG";
				this->tsLOG->Size = System::Drawing::Size(23, 22);
				this->tsLOG->Text = L" Log ";
				this->tsLOG->ToolTipText = L"Log to file all Sensors timers";
				this->tsLOG->CheckedChanged += gcnew System::EventHandler(this, &simulator::tsLOG_CheckedChanged);
				this->tsLOG->Click += gcnew System::EventHandler(this, &simulator::tsLOG2_Click);
				// 
				// tsScreenshoot
				// 
				this->tsScreenshoot->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsScreenshoot->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsScreenshoot->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsScreenshoot.Image")));
				this->tsScreenshoot->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsScreenshoot->Name = L"tsScreenshoot";
				this->tsScreenshoot->Size = System::Drawing::Size(23, 22);
				this->tsScreenshoot->ToolTipText = L"Save a screen shot on .png file";
				this->tsScreenshoot->Click += gcnew System::EventHandler(this, &simulator::tsScreenshoot_Click);
				// 
				// toolStripSeparator15
				// 
				this->toolStripSeparator15->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator15->Name = L"toolStripSeparator15";
				this->toolStripSeparator15->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripButton1
				// 
				this->toolStripButton1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->toolStripButton1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
				this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->toolStripButton1->Name = L"toolStripButton1";
				this->toolStripButton1->Size = System::Drawing::Size(23, 22);
				this->toolStripButton1->Text = L"Folder";
				this->toolStripButton1->ToolTipText = L"Open LOG folder";
				this->toolStripButton1->Click += gcnew System::EventHandler(this, &simulator::toolStripButton1_Click_1);
				// 
				// toolStripSeparator30
				// 
				this->toolStripSeparator30->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator30->Name = L"toolStripSeparator30";
				this->toolStripSeparator30->Size = System::Drawing::Size(6, 25);
				// 
				// tsSimulationAreaSize2
				// 
				this->tsSimulationAreaSize2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsSimulationAreaSize2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsSimulationAreaSize2->Name = L"tsSimulationAreaSize2";
				this->tsSimulationAreaSize2->Size = System::Drawing::Size(103, 22);
				this->tsSimulationAreaSize2->Text = L"(wwww, hhhh)";
				// 
				// toolStripSeparator14
				// 
				this->toolStripSeparator14->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator14->Name = L"toolStripSeparator14";
				this->toolStripSeparator14->Size = System::Drawing::Size(6, 25);
				// 
				// tsTimer2
				// 
				this->tsTimer2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsTimer2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsTimer2->Name = L"tsTimer2";
				this->tsTimer2->Size = System::Drawing::Size(79, 22);
				this->tsTimer2->Text = L"00:00.000";
				// 
				// toolStripSeparator31
				// 
				this->toolStripSeparator31->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator31->Name = L"toolStripSeparator31";
				this->toolStripSeparator31->Size = System::Drawing::Size(6, 25);
				// 
				// tsTSLabel2
				// 
				this->tsTSLabel2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsTSLabel2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsTSLabel2->Name = L"tsTSLabel2";
				this->tsTSLabel2->Size = System::Drawing::Size(205, 22);
				this->tsTSLabel2->Text = L"TimeSlot 00/00 - 00/00";
				this->tsTSLabel2->ToolTipText = L"Current TS / Total TS - Sequencial TS / Actual TS Lap";
				// 
				// toolStripSeparator19
				// 
				this->toolStripSeparator19->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator19->Name = L"toolStripSeparator19";
				this->toolStripSeparator19->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->toolStripSeparator19->Size = System::Drawing::Size(6, 25);
				// 
				// tsDecision
				// 
				this->tsDecision->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsDecision->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsDecision->Name = L"tsDecision";
				this->tsDecision->Size = System::Drawing::Size(111, 22);
				this->tsDecision->Text = L"Decisions: 00";
				this->tsDecision->ToolTipText = L"UAV Decisions based on Restriction Lists";
				// 
				// toolStripSeparator18
				// 
				this->toolStripSeparator18->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator18->Name = L"toolStripSeparator18";
				this->toolStripSeparator18->Size = System::Drawing::Size(6, 25);
				// 
				// tsUAVHops
				// 
				this->tsUAVHops->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsUAVHops->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsUAVHops->Name = L"tsUAVHops";
				this->tsUAVHops->Size = System::Drawing::Size(79, 22);
				this->tsUAVHops->Text = L"Hops: 000";
				// 
				// toolStripSeparator22
				// 
				this->toolStripSeparator22->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator22->Name = L"toolStripSeparator22";
				this->toolStripSeparator22->Size = System::Drawing::Size(6, 25);
				// 
				// tsUAVFlyedDistance
				// 
				this->tsUAVFlyedDistance->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsUAVFlyedDistance->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsUAVFlyedDistance->Name = L"tsUAVFlyedDistance";
				this->tsUAVFlyedDistance->Size = System::Drawing::Size(151, 22);
				this->tsUAVFlyedDistance->Text = L"Flyed Dist.: 0000m";
				// 
				// toolStripSeparator4
				// 
				this->toolStripSeparator4->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator4->Name = L"toolStripSeparator4";
				this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
				// 
				// tsUAVSpeedText
				// 
				this->tsUAVSpeedText->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsUAVSpeedText->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsUAVSpeedText->Name = L"tsUAVSpeedText";
				this->tsUAVSpeedText->Size = System::Drawing::Size(111, 22);
				this->tsUAVSpeedText->Text = L"Speed: 00 m/s";
				// 
				// toolStripSeparator13
				// 
				this->toolStripSeparator13->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->toolStripSeparator13->Name = L"toolStripSeparator13";
				this->toolStripSeparator13->Size = System::Drawing::Size(6, 25);
				// 
				// tsBattery
				// 
				this->tsBattery->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
				this->tsBattery->AutoSize = false;
				this->tsBattery->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
					static_cast<System::Int32>(static_cast<System::Byte>(0)));
				this->tsBattery->Name = L"tsBattery";
				this->tsBattery->Size = System::Drawing::Size(40, 15);
				this->tsBattery->Step = 1;
				this->tsBattery->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
				this->tsBattery->ToolTipText = L"UAVs % Battery";
				// 
				// splitContainer3
				// 
				this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
				this->splitContainer3->Location = System::Drawing::Point(0, 0);
				this->splitContainer3->Name = L"splitContainer3";
				// 
				// splitContainer3.Panel1
				// 
				this->splitContainer3->Panel1->Controls->Add(this->output);
				// 
				// splitContainer3.Panel2
				// 
				this->splitContainer3->Panel2->Controls->Add(this->groupBox2);
				this->splitContainer3->Size = System::Drawing::Size(1212, 144);
				this->splitContainer3->SplitterDistance = 754;
				this->splitContainer3->TabIndex = 0;
				// 
				// output
				// 
				this->output->BackColor = System::Drawing::Color::WhiteSmoke;
				this->output->BorderStyle = System::Windows::Forms::BorderStyle::None;
				this->output->Dock = System::Windows::Forms::DockStyle::Fill;
				this->output->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->output->ForeColor = System::Drawing::SystemColors::Desktop;
				this->output->Location = System::Drawing::Point(0, 0);
				this->output->MaxLength = 750;
				this->output->Multiline = true;
				this->output->Name = L"output";
				this->output->ReadOnly = true;
				this->output->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				this->output->Size = System::Drawing::Size(754, 144);
				this->output->TabIndex = 16;
				this->output->TextChanged += gcnew System::EventHandler(this, &simulator::output_TextChanged_1);
				// 
				// groupBox2
				// 
				this->groupBox2->Controls->Add(this->checkBox9);
				this->groupBox2->Controls->Add(this->checkBox10);
				this->groupBox2->Controls->Add(this->checkBox11);
				this->groupBox2->Controls->Add(this->checkBox12);
				this->groupBox2->Controls->Add(this->checkBox5);
				this->groupBox2->Controls->Add(this->checkBox6);
				this->groupBox2->Controls->Add(this->checkBox7);
				this->groupBox2->Controls->Add(this->checkBox8);
				this->groupBox2->Controls->Add(this->checkBox4);
				this->groupBox2->Controls->Add(this->checkBox3);
				this->groupBox2->Controls->Add(this->checkBox2);
				this->groupBox2->Controls->Add(this->checkBox1);
				this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
				this->groupBox2->Location = System::Drawing::Point(0, 0);
				this->groupBox2->Name = L"groupBox2";
				this->groupBox2->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
				this->groupBox2->Size = System::Drawing::Size(454, 144);
				this->groupBox2->TabIndex = 0;
				this->groupBox2->TabStop = false;
				this->groupBox2->Text = L" Log Settings ";
				// 
				// checkBox9
				// 
				this->checkBox9->AutoSize = true;
				this->checkBox9->Checked = true;
				this->checkBox9->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox9->Location = System::Drawing::Point(302, 30);
				this->checkBox9->Name = L"checkBox9";
				this->checkBox9->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox9->Size = System::Drawing::Size(130, 17);
				this->checkBox9->TabIndex = 12;
				this->checkBox9->Text = L"TimeSlot Seq.";
				this->checkBox9->UseVisualStyleBackColor = true;
				// 
				// checkBox10
				// 
				this->checkBox10->AutoSize = true;
				this->checkBox10->Checked = true;
				this->checkBox10->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox10->Location = System::Drawing::Point(302, 53);
				this->checkBox10->Name = L"checkBox10";
				this->checkBox10->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox10->Size = System::Drawing::Size(98, 17);
				this->checkBox10->TabIndex = 11;
				this->checkBox10->Text = L"Decisions";
				this->checkBox10->UseVisualStyleBackColor = true;
				// 
				// checkBox11
				// 
				this->checkBox11->AutoSize = true;
				this->checkBox11->Checked = true;
				this->checkBox11->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox11->Location = System::Drawing::Point(302, 76);
				this->checkBox11->Name = L"checkBox11";
				this->checkBox11->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox11->Size = System::Drawing::Size(74, 17);
				this->checkBox11->TabIndex = 10;
				this->checkBox11->Text = L"UAV ID";
				this->checkBox11->UseVisualStyleBackColor = true;
				// 
				// checkBox12
				// 
				this->checkBox12->AutoSize = true;
				this->checkBox12->Checked = true;
				this->checkBox12->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox12->Location = System::Drawing::Point(302, 99);
				this->checkBox12->Name = L"checkBox12";
				this->checkBox12->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox12->Size = System::Drawing::Size(98, 17);
				this->checkBox12->TabIndex = 9;
				this->checkBox12->Text = L"UAV Coord";
				this->checkBox12->UseVisualStyleBackColor = true;
				// 
				// checkBox5
				// 
				this->checkBox5->AutoSize = true;
				this->checkBox5->Checked = true;
				this->checkBox5->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox5->Location = System::Drawing::Point(166, 52);
				this->checkBox5->Name = L"checkBox5";
				this->checkBox5->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox5->Size = System::Drawing::Size(122, 17);
				this->checkBox5->TabIndex = 8;
				this->checkBox5->Text = L"S. MSGs Lost";
				this->ttLOG->SetToolTip(this->checkBox5, L"Show how many UAV visits the Sensor has lost");
				this->checkBox5->UseVisualStyleBackColor = true;
				// 
				// checkBox6
				// 
				this->checkBox6->AutoSize = true;
				this->checkBox6->Checked = true;
				this->checkBox6->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox6->Location = System::Drawing::Point(166, 76);
				this->checkBox6->Name = L"checkBox6";
				this->checkBox6->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox6->Size = System::Drawing::Size(114, 17);
				this->checkBox6->TabIndex = 7;
				this->checkBox6->Text = L"UAV Connect";
				this->checkBox6->UseVisualStyleBackColor = true;
				// 
				// checkBox7
				// 
				this->checkBox7->AutoSize = true;
				this->checkBox7->Checked = true;
				this->checkBox7->CheckState = System::Windows::Forms::CheckState::Checked;
				this->checkBox7->Location = System::Drawing::Point(166, 99);
				this->checkBox7->Name = L"checkBox7";
				this->checkBox7->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->checkBox7->Size = System::Drawing::Size(90, 17);
				this->checkBox7->TabIndex = 6;
				this->checkBox7->Text = L"UAV Hops";
				this->checkBox7->UseVisualStyleBackColor = true;
				// 
				// toolStrip1
				// 
				this->toolStrip1->AllowItemReorder = true;
				this->toolStrip1->BackColor = System::Drawing::Color::WhiteSmoke;
				this->toolStrip1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(60) {
					this->tsPlay, this->toolStripSeparator12,
						this->tsBreset, this->tsLockReset, this->toolStripSeparator1, this->tsMobilityModel, this->toolStripSeparator2, this->tsSwapUAVs,
						this->tsBackToDeposit, this->tsUAVposition, this->tsInfo, this->tsStandBy, this->tsDrawPoint, this->toolStripSeparator16, this->tsGridSensor,
						this->tsMaxSensorsGrid, this->toolStripSeparator17, this->tsShowCluster, this->tsDrawCircleSensor, this->tsDrawCircleUAV, this->toolStripSeparator35,
						this->tsShowRoute, this->tsRedRoute, this->tsGreenRoute, this->tsBlueRoute, this->tsCyanRoute, this->tsClosedCircuit, this->tsRouteInfo,
						this->toolStripSeparator11, this->tsSensorDiscoveredTS, this->tsScanForSensors, this->tsSetRestriction, this->tsRepeatTimeSlots,
						this->tsSetTimeSlot, this->tsSleepSensor, this->toolStripSeparator20, this->tsBroadcastActivate, this->tsFixedTimers, this->tsRandSleep,
						this->tsMicroTimeSlots, this->tsqTimeSlots, this->toolStripSeparator5, this->toolStripSeparator9, this->tsUp, this->tsDown, this->toolStripSeparator3,
						this->tsQuav, this->tsUAVSelect, this->toolStripSeparator6, this->tsQSensor, this->tsSensorSelect, this->toolStripSeparator10,
						this->tsSpeed, this->tsSpeedSelect, this->toolStripSeparator32, this->toolStripSeparator7, this->tsDebug, this->toolStripSeparator34,
						this->tsSimulationCounter, this->tsSound
				});
				this->toolStrip1->Location = System::Drawing::Point(3, 3);
				this->toolStrip1->Name = L"toolStrip1";
				this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
				this->toolStrip1->Size = System::Drawing::Size(1462, 25);
				this->toolStrip1->TabIndex = 0;
				this->toolStrip1->Text = L"toolStrip1";
				// 
				// tsPlay
				// 
				this->tsPlay->AutoSize = false;
				this->tsPlay->BackColor = System::Drawing::Color::WhiteSmoke;
				this->tsPlay->CheckOnClick = true;
				this->tsPlay->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->tsPlay->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsPlay.Image")));
				this->tsPlay->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsPlay->MergeIndex = 4;
				this->tsPlay->Name = L"tsPlay";
				this->tsPlay->Padding = System::Windows::Forms::Padding(50, 0, 0, 0);
				this->tsPlay->Size = System::Drawing::Size(69, 22);
				this->tsPlay->Text = L"Play";
				this->tsPlay->ToolTipText = L"Start / Stop simulation";
				this->tsPlay->CheckedChanged += gcnew System::EventHandler(this, &simulator::tsPlay_CheckedChanged);
				this->tsPlay->Click += gcnew System::EventHandler(this, &simulator::tsPlay_Click);
				// 
				// toolStripSeparator12
				// 
				this->toolStripSeparator12->Name = L"toolStripSeparator12";
				this->toolStripSeparator12->Size = System::Drawing::Size(6, 25);
				// 
				// tsBreset
				// 
				this->tsBreset->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsBreset.Image")));
				this->tsBreset->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsBreset->Name = L"tsBreset";
				this->tsBreset->Size = System::Drawing::Size(67, 22);
				this->tsBreset->Text = L"Reset";
				this->tsBreset->ToolTipText = L"Reset parameters";
				this->tsBreset->Click += gcnew System::EventHandler(this, &simulator::tsBreset_Click);
				// 
				// tsLockReset
				// 
				this->tsLockReset->CheckOnClick = true;
				this->tsLockReset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsLockReset->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsLockReset.Image")));
				this->tsLockReset->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsLockReset->Name = L"tsLockReset";
				this->tsLockReset->Size = System::Drawing::Size(23, 22);
				this->tsLockReset->Text = L"toolStripButton2";
				this->tsLockReset->ToolTipText = L"Reset only internal atributes, keep the objects on the same place";
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = L"toolStripSeparator1";
				this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
				// 
				// tsMobilityModel
				// 
				this->tsMobilityModel->BackColor = System::Drawing::SystemColors::Window;
				this->tsMobilityModel->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
				this->tsMobilityModel->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10));
				this->tsMobilityModel->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
					L"Random Direction", L"Random Waypoint",
						L"Wait untill Find", L"uTimeSlots", L"uTimeSlots Auto", L"Wait untill Find Auto"
				});
				this->tsMobilityModel->MergeIndex = 6;
				this->tsMobilityModel->Name = L"tsMobilityModel";
				this->tsMobilityModel->Size = System::Drawing::Size(150, 25);
				this->tsMobilityModel->Text = L"uTimeSlots";
				this->tsMobilityModel->ToolTipText = L"Choose a mobility model for simulation";
				this->tsMobilityModel->SelectedIndexChanged += gcnew System::EventHandler(this, &simulator::tsMobilityModel_SelectedIndexChanged_1);
				this->tsMobilityModel->Click += gcnew System::EventHandler(this, &simulator::tsMobilityModel_Click);
				// 
				// toolStripSeparator2
				// 
				this->toolStripSeparator2->Name = L"toolStripSeparator2";
				this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
				// 
				// tsSwapUAVs
				// 
				this->tsSwapUAVs->CheckOnClick = true;
				this->tsSwapUAVs->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSwapUAVs->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSwapUAVs.Image")));
				this->tsSwapUAVs->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSwapUAVs->Name = L"tsSwapUAVs";
				this->tsSwapUAVs->Size = System::Drawing::Size(23, 22);
				this->tsSwapUAVs->Text = L"toolStripButton2";
				this->tsSwapUAVs->ToolTipText = L"Return to Home (RTH) function, when UAVs battery bellow 10%  it retorns to Base S"
					L"tation";
				this->tsSwapUAVs->Click += gcnew System::EventHandler(this, &simulator::tsSwapUAVs_Click);
				// 
				// tsBackToDeposit
				// 
				this->tsBackToDeposit->CheckOnClick = true;
				this->tsBackToDeposit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsBackToDeposit->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsBackToDeposit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsBackToDeposit.Image")));
				this->tsBackToDeposit->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsBackToDeposit->Name = L"tsBackToDeposit";
				this->tsBackToDeposit->Size = System::Drawing::Size(23, 22);
				this->tsBackToDeposit->Text = L"Home";
				this->tsBackToDeposit->ToolTipText = L"Enable UAV to come back to delivery messages to Server";
				this->tsBackToDeposit->Click += gcnew System::EventHandler(this, &simulator::tsHome_Click);
				// 
				// tsUAVposition
				// 
				this->tsUAVposition->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->tsUAVposition->Font = (gcnew System::Drawing::Font(L"Lucida Console", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->tsUAVposition->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsUAVposition.Image")));
				this->tsUAVposition->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsUAVposition->Name = L"tsUAVposition";
				this->tsUAVposition->Size = System::Drawing::Size(23, 22);
				this->tsUAVposition->Text = L"A";
				this->tsUAVposition->ToolTipText = L"Allign UAVs besides Deposit to initial launch.";
				this->tsUAVposition->Click += gcnew System::EventHandler(this, &simulator::tsIUAVposition_Click);
				// 
				// tsInfo
				// 
				this->tsInfo->Checked = true;
				this->tsInfo->CheckOnClick = true;
				this->tsInfo->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsInfo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsInfo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsInfo.Image")));
				this->tsInfo->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsInfo->Name = L"tsInfo";
				this->tsInfo->Size = System::Drawing::Size(23, 22);
				this->tsInfo->Text = L"toolStripButton1";
				this->tsInfo->ToolTipText = L"Show information about elements on simulation area";
				this->tsInfo->Click += gcnew System::EventHandler(this, &simulator::tsInfo_Click);
				// 
				// tsStandBy
				// 
				this->tsStandBy->Checked = true;
				this->tsStandBy->CheckOnClick = true;
				this->tsStandBy->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsStandBy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsStandBy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsStandBy.Image")));
				this->tsStandBy->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsStandBy->Name = L"tsStandBy";
				this->tsStandBy->Size = System::Drawing::Size(23, 22);
				this->tsStandBy->Text = L"toolStripButton2";
				this->tsStandBy->ToolTipText = L"Stop at target WayPoint";
				// 
				// tsDrawPoint
				// 
				this->tsDrawPoint->Checked = true;
				this->tsDrawPoint->CheckOnClick = true;
				this->tsDrawPoint->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsDrawPoint->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDrawPoint->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDrawPoint.Image")));
				this->tsDrawPoint->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDrawPoint->Name = L"tsDrawPoint";
				this->tsDrawPoint->Size = System::Drawing::Size(23, 22);
				this->tsDrawPoint->Text = L"toolStripButton3";
				this->tsDrawPoint->ToolTipText = L"Draw target WayPoint on simulation area";
				// 
				// toolStripSeparator16
				// 
				this->toolStripSeparator16->Name = L"toolStripSeparator16";
				this->toolStripSeparator16->Size = System::Drawing::Size(6, 25);
				// 
				// tsGridSensor
				// 
				this->tsGridSensor->Checked = true;
				this->tsGridSensor->CheckOnClick = true;
				this->tsGridSensor->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsGridSensor->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsGridSensor->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsGridSensor.Image")));
				this->tsGridSensor->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsGridSensor->Name = L"tsGridSensor";
				this->tsGridSensor->Size = System::Drawing::Size(23, 22);
				this->tsGridSensor->Text = L"Allign all Sensors";
				this->tsGridSensor->Click += gcnew System::EventHandler(this, &simulator::tsGridSensor_Click);
				// 
				// tsMaxSensorsGrid
				// 
				this->tsMaxSensorsGrid->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsMaxSensorsGrid->Name = L"tsMaxSensorsGrid";
				this->tsMaxSensorsGrid->Size = System::Drawing::Size(25, 22);
				this->tsMaxSensorsGrid->Text = L"XX";
				this->tsMaxSensorsGrid->ToolTipText = L"Maximum number of Sensors distribuited in this area";
				// 
				// toolStripSeparator17
				// 
				this->toolStripSeparator17->Name = L"toolStripSeparator17";
				this->toolStripSeparator17->Size = System::Drawing::Size(6, 25);
				// 
				// tsShowCluster
				// 
				this->tsShowCluster->CheckOnClick = true;
				this->tsShowCluster->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsShowCluster->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsShowCluster.Image")));
				this->tsShowCluster->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsShowCluster->Name = L"tsShowCluster";
				this->tsShowCluster->Size = System::Drawing::Size(23, 22);
				this->tsShowCluster->Text = L"toolStripButton1";
				this->tsShowCluster->ToolTipText = L"Show Sensors큦 Clusters ID";
				this->tsShowCluster->Click += gcnew System::EventHandler(this, &simulator::tsShowCluster_Click);
				// 
				// tsDrawCircleSensor
				// 
				this->tsDrawCircleSensor->Checked = true;
				this->tsDrawCircleSensor->CheckOnClick = true;
				this->tsDrawCircleSensor->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsDrawCircleSensor->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDrawCircleSensor->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDrawCircleSensor.Image")));
				this->tsDrawCircleSensor->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDrawCircleSensor->Name = L"tsDrawCircleSensor";
				this->tsDrawCircleSensor->Size = System::Drawing::Size(23, 22);
				this->tsDrawCircleSensor->Text = L"toolStripButton1";
				this->tsDrawCircleSensor->ToolTipText = L"Show Sensor큦 cooverage area";
				this->tsDrawCircleSensor->Click += gcnew System::EventHandler(this, &simulator::tsDrawCircle_Click);
				// 
				// tsDrawCircleUAV
				// 
				this->tsDrawCircleUAV->CheckOnClick = true;
				this->tsDrawCircleUAV->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDrawCircleUAV->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDrawCircleUAV.Image")));
				this->tsDrawCircleUAV->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDrawCircleUAV->Name = L"tsDrawCircleUAV";
				this->tsDrawCircleUAV->Size = System::Drawing::Size(23, 22);
				this->tsDrawCircleUAV->Text = L"toolStripButton1";
				this->tsDrawCircleUAV->ToolTipText = L"Show UAV큦 cooverage area";
				this->tsDrawCircleUAV->Click += gcnew System::EventHandler(this, &simulator::tsDrawCircleUAV_Click);
				// 
				// toolStripSeparator35
				// 
				this->toolStripSeparator35->Name = L"toolStripSeparator35";
				this->toolStripSeparator35->Size = System::Drawing::Size(6, 25);
				// 
				// tsShowRoute
				// 
				this->tsShowRoute->CheckOnClick = true;
				this->tsShowRoute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsShowRoute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsShowRoute.Image")));
				this->tsShowRoute->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsShowRoute->Name = L"tsShowRoute";
				this->tsShowRoute->Size = System::Drawing::Size(23, 22);
				this->tsShowRoute->Text = L"toolStripButton1";
				this->tsShowRoute->ToolTipText = L"Click to show UAV큦 route";
				this->tsShowRoute->CheckedChanged += gcnew System::EventHandler(this, &simulator::tsShowRoute_CheckedChanged);
				this->tsShowRoute->Click += gcnew System::EventHandler(this, &simulator::tsShowRoute_Click);
				// 
				// tsRedRoute
				// 
				this->tsRedRoute->CheckOnClick = true;
				this->tsRedRoute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsRedRoute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsRedRoute.Image")));
				this->tsRedRoute->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsRedRoute->Name = L"tsRedRoute";
				this->tsRedRoute->Size = System::Drawing::Size(23, 22);
				this->tsRedRoute->ToolTipText = L"Set UAV큦 path to fly above each Sensor, this is the longest path";
				this->tsRedRoute->Click += gcnew System::EventHandler(this, &simulator::tsRedRoute_Click);
				// 
				// tsGreenRoute
				// 
				this->tsGreenRoute->CheckOnClick = true;
				this->tsGreenRoute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsGreenRoute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsGreenRoute.Image")));
				this->tsGreenRoute->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsGreenRoute->Name = L"tsGreenRoute";
				this->tsGreenRoute->Size = System::Drawing::Size(23, 22);
				this->tsGreenRoute->Text = L"toolStripButton2";
				this->tsGreenRoute->ToolTipText = L"Select this Path to UAV fly based on Nearest Point mobility Model";
				this->tsGreenRoute->Click += gcnew System::EventHandler(this, &simulator::tsGreenRoute_Click);
				// 
				// tsBlueRoute
				// 
				this->tsBlueRoute->CheckOnClick = true;
				this->tsBlueRoute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsBlueRoute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsBlueRoute.Image")));
				this->tsBlueRoute->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsBlueRoute->Name = L"tsBlueRoute";
				this->tsBlueRoute->Size = System::Drawing::Size(23, 22);
				this->tsBlueRoute->Text = L"toolStripButton1";
				this->tsBlueRoute->ToolTipText = L"Select this path to use Kashuba et al. path planning";
				this->tsBlueRoute->Click += gcnew System::EventHandler(this, &simulator::tsBlueRoute_Click);
				// 
				// tsCyanRoute
				// 
				this->tsCyanRoute->CheckOnClick = true;
				this->tsCyanRoute->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsCyanRoute->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsCyanRoute.Image")));
				this->tsCyanRoute->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsCyanRoute->Name = L"tsCyanRoute";
				this->tsCyanRoute->Size = System::Drawing::Size(23, 22);
				this->tsCyanRoute->Text = L"toolStripButton1";
				this->tsCyanRoute->ToolTipText = L"Select this Path to use a combination over Kashuba and Nearest Point path Plannin"
					L"g";
				this->tsCyanRoute->Click += gcnew System::EventHandler(this, &simulator::tsCyanRoute_Click);
				// 
				// tsClosedCircuit
				// 
				this->tsClosedCircuit->CheckOnClick = true;
				this->tsClosedCircuit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsClosedCircuit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsClosedCircuit.Image")));
				this->tsClosedCircuit->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsClosedCircuit->Name = L"tsClosedCircuit";
				this->tsClosedCircuit->Size = System::Drawing::Size(23, 22);
				this->tsClosedCircuit->Text = L"toolStripButton1";
				this->tsClosedCircuit->ToolTipText = L"Click here if you want the UAV returns to the initial Point";
				this->tsClosedCircuit->Click += gcnew System::EventHandler(this, &simulator::tsClosedCircuit_Click);
				// 
				// tsRouteInfo
				// 
				this->tsRouteInfo->CheckOnClick = true;
				this->tsRouteInfo->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsRouteInfo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsRouteInfo.Image")));
				this->tsRouteInfo->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsRouteInfo->Name = L"tsRouteInfo";
				this->tsRouteInfo->Size = System::Drawing::Size(23, 22);
				this->tsRouteInfo->Text = L"toolStripButton1";
				this->tsRouteInfo->Click += gcnew System::EventHandler(this, &simulator::tsRouteInfo_Click);
				// 
				// toolStripSeparator11
				// 
				this->toolStripSeparator11->Name = L"toolStripSeparator11";
				this->toolStripSeparator11->Size = System::Drawing::Size(6, 25);
				// 
				// tsSensorDiscoveredTS
				// 
				this->tsSensorDiscoveredTS->CheckOnClick = true;
				this->tsSensorDiscoveredTS->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSensorDiscoveredTS->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSensorDiscoveredTS.Image")));
				this->tsSensorDiscoveredTS->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSensorDiscoveredTS->Name = L"tsSensorDiscoveredTS";
				this->tsSensorDiscoveredTS->Size = System::Drawing::Size(23, 22);
				this->tsSensorDiscoveredTS->Text = L"toolStripButton1";
				this->tsSensorDiscoveredTS->ToolTipText = L"On TimeSlot disocery process, if actual timeSlot is know the \r\nUAV goes to that S"
					L"ensor, or waits untill next free TimeSlot.\r\n";
				// 
				// tsScanForSensors
				// 
				this->tsScanForSensors->Checked = true;
				this->tsScanForSensors->CheckOnClick = true;
				this->tsScanForSensors->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsScanForSensors->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsScanForSensors->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsScanForSensors.Image")));
				this->tsScanForSensors->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsScanForSensors->Name = L"tsScanForSensors";
				this->tsScanForSensors->Size = System::Drawing::Size(23, 22);
				this->tsScanForSensors->Text = L"toolStripButton1";
				this->tsScanForSensors->ToolTipText = L"Use this resource to scan Sensors out of UAV큦 RouteList";
				this->tsScanForSensors->Click += gcnew System::EventHandler(this, &simulator::tsScanForSensors_Click);
				// 
				// tsSetRestriction
				// 
				this->tsSetRestriction->Checked = true;
				this->tsSetRestriction->CheckOnClick = true;
				this->tsSetRestriction->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsSetRestriction->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSetRestriction->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSetRestriction.Image")));
				this->tsSetRestriction->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSetRestriction->Name = L"tsSetRestriction";
				this->tsSetRestriction->Size = System::Drawing::Size(23, 22);
				this->tsSetRestriction->Text = L"toolStripButton2";
				this->tsSetRestriction->ToolTipText = L"Used to learn restrictions on Sensors for each  TimeSlot";
				// 
				// tsRepeatTimeSlots
				// 
				this->tsRepeatTimeSlots->Checked = true;
				this->tsRepeatTimeSlots->CheckOnClick = true;
				this->tsRepeatTimeSlots->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsRepeatTimeSlots->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsRepeatTimeSlots->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsRepeatTimeSlots.Image")));
				this->tsRepeatTimeSlots->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsRepeatTimeSlots->Name = L"tsRepeatTimeSlots";
				this->tsRepeatTimeSlots->Size = System::Drawing::Size(23, 22);
				this->tsRepeatTimeSlots->Text = L"toolStripButton2";
				this->tsRepeatTimeSlots->ToolTipText = L"Random and Non-Repeated Time Slot to Sensors";
				// 
				// tsSetTimeSlot
				// 
				this->tsSetTimeSlot->Checked = true;
				this->tsSetTimeSlot->CheckOnClick = true;
				this->tsSetTimeSlot->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsSetTimeSlot->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSetTimeSlot->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsSetTimeSlot->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSetTimeSlot.Image")));
				this->tsSetTimeSlot->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSetTimeSlot->Name = L"tsSetTimeSlot";
				this->tsSetTimeSlot->Size = System::Drawing::Size(23, 22);
				this->tsSetTimeSlot->Text = L"Set TS";
				this->tsSetTimeSlot->ToolTipText = L"Permit UAV to reconfigure Sensors TimeSlot";
				this->tsSetTimeSlot->Click += gcnew System::EventHandler(this, &simulator::tsSetTimeSlot_Click);
				// 
				// tsSleepSensor
				// 
				this->tsSleepSensor->Checked = true;
				this->tsSleepSensor->CheckOnClick = true;
				this->tsSleepSensor->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsSleepSensor->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSleepSensor->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSleepSensor.Image")));
				this->tsSleepSensor->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSleepSensor->Name = L"tsSleepSensor";
				this->tsSleepSensor->Size = System::Drawing::Size(23, 22);
				this->tsSleepSensor->Text = L"toolStripButton1";
				this->tsSleepSensor->ToolTipText = L"Permit UAV program Sensor to Sleep";
				// 
				// toolStripSeparator20
				// 
				this->toolStripSeparator20->Name = L"toolStripSeparator20";
				this->toolStripSeparator20->Size = System::Drawing::Size(6, 25);
				// 
				// tsBroadcastActivate
				// 
				this->tsBroadcastActivate->CheckOnClick = true;
				this->tsBroadcastActivate->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsBroadcastActivate->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsBroadcastActivate.Image")));
				this->tsBroadcastActivate->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsBroadcastActivate->Name = L"tsBroadcastActivate";
				this->tsBroadcastActivate->Size = System::Drawing::Size(23, 22);
				this->tsBroadcastActivate->Text = L"toolStripButton1";
				this->tsBroadcastActivate->ToolTipText = L"Set all Sensors with internal Timers on the same Timeslot";
				this->tsBroadcastActivate->Click += gcnew System::EventHandler(this, &simulator::tsBroadcastActivate_Click);
				// 
				// tsFixedTimers
				// 
				this->tsFixedTimers->CheckOnClick = true;
				this->tsFixedTimers->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsFixedTimers->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsFixedTimers.Image")));
				this->tsFixedTimers->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsFixedTimers->Name = L"tsFixedTimers";
				this->tsFixedTimers->Size = System::Drawing::Size(23, 22);
				this->tsFixedTimers->Text = L"toolStripButton1";
				this->tsFixedTimers->ToolTipText = L"Set BC/Sleep fixed timers interval";
				this->tsFixedTimers->Click += gcnew System::EventHandler(this, &simulator::tsFixedTimers_Click);
				// 
				// tsRandSleep
				// 
				this->tsRandSleep->CheckOnClick = true;
				this->tsRandSleep->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsRandSleep->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsRandSleep.Image")));
				this->tsRandSleep->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsRandSleep->Name = L"tsRandSleep";
				this->tsRandSleep->Size = System::Drawing::Size(23, 22);
				this->tsRandSleep->ToolTipText = L"Activate random broadcast timer";
				this->tsRandSleep->Click += gcnew System::EventHandler(this, &simulator::tsRandSleep_Click);
				// 
				// tsMicroTimeSlots
				// 
				this->tsMicroTimeSlots->CheckOnClick = true;
				this->tsMicroTimeSlots->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsMicroTimeSlots->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsMicroTimeSlots.Image")));
				this->tsMicroTimeSlots->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsMicroTimeSlots->Name = L"tsMicroTimeSlots";
				this->tsMicroTimeSlots->Size = System::Drawing::Size(23, 22);
				this->tsMicroTimeSlots->Text = L"Activate Micro Time Slots systems";
				this->tsMicroTimeSlots->Click += gcnew System::EventHandler(this, &simulator::tsMicroTimeSlots_Click);
				// 
				// tsqTimeSlots
				// 
				this->tsqTimeSlots->AutoSize = false;
				this->tsqTimeSlots->BackColor = System::Drawing::Color::White;
				this->tsqTimeSlots->DropDownWidth = 40;
				this->tsqTimeSlots->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
				this->tsqTimeSlots->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
				this->tsqTimeSlots->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"10", L"20", L"30", L"40", L"50", L"100" });
				this->tsqTimeSlots->Name = L"tsqTimeSlots";
				this->tsqTimeSlots->Size = System::Drawing::Size(55, 25);
				this->tsqTimeSlots->Text = L"10";
				this->tsqTimeSlots->ToolTipText = L"Micro Time Slots Quantity";
				this->tsqTimeSlots->TextChanged += gcnew System::EventHandler(this, &simulator::tsqTimeSlots_TextChanged);
				// 
				// toolStripSeparator5
				// 
				this->toolStripSeparator5->Name = L"toolStripSeparator5";
				this->toolStripSeparator5->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripSeparator9
				// 
				this->toolStripSeparator9->Name = L"toolStripSeparator9";
				this->toolStripSeparator9->Size = System::Drawing::Size(6, 25);
				// 
				// tsUp
				// 
				this->tsUp->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsUp.Image")));
				this->tsUp->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsUp->Name = L"tsUp";
				this->tsUp->Size = System::Drawing::Size(23, 22);
				this->tsUp->Text = L"toolStripButton3";
				this->tsUp->ToolTipText = L"Select UAV, Sensor or Speed to add their values";
				this->tsUp->Click += gcnew System::EventHandler(this, &simulator::tsUp_Click);
				// 
				// tsDown
				// 
				this->tsDown->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDown.Image")));
				this->tsDown->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDown->Name = L"tsDown";
				this->tsDown->Size = System::Drawing::Size(23, 22);
				this->tsDown->Text = L"toolStripButton1";
				this->tsDown->ToolTipText = L"Select UAV, Sensor or Speed to subtract their values";
				this->tsDown->Click += gcnew System::EventHandler(this, &simulator::tsDown_Click);
				// 
				// toolStripSeparator3
				// 
				this->toolStripSeparator3->Name = L"toolStripSeparator3";
				this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
				// 
				// tsQuav
				// 
				this->tsQuav->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsQuav->Name = L"tsQuav";
				this->tsQuav->Size = System::Drawing::Size(16, 22);
				this->tsQuav->Text = L"U";
				this->tsQuav->ToolTipText = L"Quantity of UAVs on simulation area";
				// 
				// tsUAVSelect
				// 
				this->tsUAVSelect->CheckOnClick = true;
				this->tsUAVSelect->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsUAVSelect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsUAVSelect.Image")));
				this->tsUAVSelect->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsUAVSelect->Name = L"tsUAVSelect";
				this->tsUAVSelect->Size = System::Drawing::Size(23, 22);
				this->tsUAVSelect->Text = L"toolStripButton2";
				this->tsUAVSelect->ToolTipText = L"Click to select UAV up/down";
				this->tsUAVSelect->Click += gcnew System::EventHandler(this, &simulator::tsUAVSelect_Click);
				// 
				// toolStripSeparator6
				// 
				this->toolStripSeparator6->Name = L"toolStripSeparator6";
				this->toolStripSeparator6->Size = System::Drawing::Size(6, 25);
				// 
				// tsQSensor
				// 
				this->tsQSensor->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsQSensor->Name = L"tsQSensor";
				this->tsQSensor->Size = System::Drawing::Size(16, 22);
				this->tsQSensor->Text = L"S";
				this->tsQSensor->ToolTipText = L"Quantity of Sensors on simulation area";
				// 
				// tsSensorSelect
				// 
				this->tsSensorSelect->Checked = true;
				this->tsSensorSelect->CheckOnClick = true;
				this->tsSensorSelect->CheckState = System::Windows::Forms::CheckState::Checked;
				this->tsSensorSelect->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSensorSelect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSensorSelect.Image")));
				this->tsSensorSelect->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSensorSelect->Name = L"tsSensorSelect";
				this->tsSensorSelect->Size = System::Drawing::Size(23, 22);
				this->tsSensorSelect->Text = L"toolStripButton4";
				this->tsSensorSelect->ToolTipText = L"Click to select Sensor up/down";
				this->tsSensorSelect->Click += gcnew System::EventHandler(this, &simulator::tsSensorSelect_Click);
				// 
				// toolStripSeparator10
				// 
				this->toolStripSeparator10->Name = L"toolStripSeparator10";
				this->toolStripSeparator10->Size = System::Drawing::Size(6, 25);
				// 
				// tsSpeed
				// 
				this->tsSpeed->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold));
				this->tsSpeed->Name = L"tsSpeed";
				this->tsSpeed->Size = System::Drawing::Size(25, 22);
				this->tsSpeed->Text = L"Sp";
				this->tsSpeed->ToolTipText = L"UAV큦 speed";
				// 
				// tsSpeedSelect
				// 
				this->tsSpeedSelect->CheckOnClick = true;
				this->tsSpeedSelect->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSpeedSelect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSpeedSelect.Image")));
				this->tsSpeedSelect->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSpeedSelect->Name = L"tsSpeedSelect";
				this->tsSpeedSelect->Size = System::Drawing::Size(23, 22);
				this->tsSpeedSelect->Text = L"toolStripButton1";
				this->tsSpeedSelect->ToolTipText = L"Click to set UAV큦 speed up/down";
				this->tsSpeedSelect->Click += gcnew System::EventHandler(this, &simulator::tsSpeedSelect_Click);
				// 
				// toolStripSeparator32
				// 
				this->toolStripSeparator32->Name = L"toolStripSeparator32";
				this->toolStripSeparator32->Size = System::Drawing::Size(6, 25);
				// 
				// toolStripSeparator7
				// 
				this->toolStripSeparator7->Name = L"toolStripSeparator7";
				this->toolStripSeparator7->Size = System::Drawing::Size(6, 25);
				// 
				// tsDebug
				// 
				this->tsDebug->CheckOnClick = true;
				this->tsDebug->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsDebug->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsDebug.Image")));
				this->tsDebug->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsDebug->Name = L"tsDebug";
				this->tsDebug->Size = System::Drawing::Size(23, 22);
				this->tsDebug->Text = L"toolStripButton1";
				this->tsDebug->ToolTipText = L"Activate debug information";
				this->tsDebug->Click += gcnew System::EventHandler(this, &simulator::tsDebug_Click);
				// 
				// toolStripSeparator34
				// 
				this->toolStripSeparator34->Name = L"toolStripSeparator34";
				this->toolStripSeparator34->Size = System::Drawing::Size(6, 25);
				// 
				// tsSimulationCounter
				// 
				this->tsSimulationCounter->Name = L"tsSimulationCounter";
				this->tsSimulationCounter->Size = System::Drawing::Size(23, 22);
				this->tsSimulationCounter->Text = L"00";
				// 
				// tsSound
				// 
				this->tsSound->CheckOnClick = true;
				this->tsSound->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->tsSound->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsSound.Image")));
				this->tsSound->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->tsSound->Name = L"tsSound";
				this->tsSound->Size = System::Drawing::Size(23, 22);
				this->tsSound->Text = L"toolStripButton2";
				// 
				// nextStepTimer
				// 
				this->nextStepTimer->Interval = 150;
				this->nextStepTimer->Tick += gcnew System::EventHandler(this, &simulator::nextStepTimer_Tick);
				// 
				// simulator
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->ClientSize = System::Drawing::Size(1476, 827);
				this->Controls->Add(this->tabControl1);
				this->Controls->Add(this->toolStripContainer1);
				this->Controls->Add(this->toolStripContainer2);
				this->DoubleBuffered = true;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				this->MinimizeBox = false;
				this->Name = L"simulator";
				this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				this->Text = L"UAV Simulator";
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &simulator::simulator_FormClosing);
				this->Load += gcnew System::EventHandler(this, &simulator::simulator_Load);
				this->Resize += gcnew System::EventHandler(this, &simulator::simulator_Resize);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tsStepInterval))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBatteryLevel))->EndInit();
				this->toolStripContainer1->ResumeLayout(false);
				this->toolStripContainer1->PerformLayout();
				this->toolStripContainer2->ResumeLayout(false);
				this->toolStripContainer2->PerformLayout();
				this->tabControl1->ResumeLayout(false);
				this->tabPage3->ResumeLayout(false);
				this->tabPage3->PerformLayout();
				this->tableLayoutPanel4->ResumeLayout(false);
				this->Connections->ResumeLayout(false);
				this->splitContainer2->Panel1->ResumeLayout(false);
				this->splitContainer2->Panel1->PerformLayout();
				this->splitContainer2->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer2))->EndInit();
				this->splitContainer2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numUAVAutonomy))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numTSTime))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numBCtimeSlots))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->readTime))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numClusterDistance))->EndInit();
				this->groupBox1->ResumeLayout(false);
				this->groupBox1->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numSimulationPause))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numQtySimulation))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->broadcastTime))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numU2DmaxConn))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numV2SmaxConn))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numV2VmaxConn))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2Sever))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SleepingTime))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2V))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numConRangeV2S))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
				this->tableLayoutPanel1->ResumeLayout(false);
				this->splitContainer1->Panel1->ResumeLayout(false);
				this->splitContainer1->Panel1->PerformLayout();
				this->splitContainer1->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
				this->splitContainer1->ResumeLayout(false);
				this->toolStrip2->ResumeLayout(false);
				this->toolStrip2->PerformLayout();
				this->splitContainer3->Panel1->ResumeLayout(false);
				this->splitContainer3->Panel1->PerformLayout();
				this->splitContainer3->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->EndInit();
				this->splitContainer3->ResumeLayout(false);
				this->groupBox2->ResumeLayout(false);
				this->groupBox2->PerformLayout();
				this->toolStrip1->ResumeLayout(false);
				this->toolStrip1->PerformLayout();
				this->ResumeLayout(false);

			}
#pragma endregion

private: System::Void tsPlay_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (tsPlay->Checked)
	{
		tsPlay->Image = Image::FromFile("Images\\Rstop.png");
		tsPlay->Text = "Stop";
	}
	else
	{
		tsPlay->Image = Image::FromFile("Images\\Gplay.png");
		tsPlay->Text = "Play";
	}
}

private: System::Void _simulationPlayButton(int state)
{
	if(tsPlay->Checked)
		tsPlay->Checked = state;
	else
		tsPlay->Checked = !state;

	v = gcnew Vant();
	s = gcnew Sensor();

	v = myVants[0];
	v->setActive(true);

	//check if there are a lot of buttons checked;
	checkRoutes = redRouteON + greenRouteON + blueRouteON + cyanRouteON;

	if (checkRoutes == 1 || checkRoutes == 2 || checkRoutes == 4 || checkRoutes == 8)
	{
		if (tsPlay->Checked)
		{
			_activatetsMicroTimeSlots(true);

			if(cbLog->Checked)
				_LOGactivate(true);

			splitContainer3->Panel2Collapsed = true;

			if (!SystemStopWatch->IsRunning)
				SystemStopWatch->Start();

			if (!Timer1sec->Enabled)
				Timer1sec->Start();

			for (unsigned int i = 0; i < qUAVs; i++)
			{
				myVants[i]->setInit(true);
				myVants[i]->setMyRWP(nullptr);
				myVants[0]->getMyStopWatch()->Start();
				myVants[i]->setMyCounter(0);
			}

			splitContainer2->Panel1->Enabled = false;
			tsqTimeSlots->Enabled = false;

			output->Text += _getTimeCRLF() + "Simulation Started";

			nextStepTimer->Interval = tsStepInterval->Value;
			nextStepTimer->Start();
		}
		else
		{
			nextStepTimer->Stop();

			output->Text += _getTimeCRLF() + "Simulation stopped at : " + SystemStopWatch->Elapsed.ToString() + "ms";

			if (SystemStopWatch->IsRunning)
				SystemStopWatch->Stop();

			if (Timer1sec->Enabled)
				Timer1sec->Stop();

			splitContainer2->Panel1->Enabled = true;
			tsqTimeSlots->Enabled = true;

			_activateTSbuttonRandomSleep(false);

			if (tsLOG->Checked)
			{
				tsLOG->Checked = false;
				_LOGactivate(true);
				splitContainer3->Panel2Collapsed = true;
			}

			for (unsigned int i = 0; i < qUAVs; i++)
				myVants[i]->getMyStopWatch()->Stop();

			for (unsigned int i = 0; i < qSensors; i++)
				mySensors[i]->setMyTimers1(0, 0);

			simulationArea->Refresh();
		}
	}
	else
	{
		output->Text += _getTimeCRLF() + "Select only one route please ...";
		tsPlay->Checked = false;
	}
}


private: System::Void tsPlay_Click(System::Object^  sender, System::EventArgs^  e)
{
	_simulationPlayButton(true);
}

private: System::Void nextStepTimer_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	switch (tsMobilityModel->SelectedIndex)
	{
		case 0: //Random Direction;
		{
			if (v->getcX() <= DIST_FROM_CENTER || (v->getcX() >= simulationArea->Width - DIST_FROM_CENTER))
				v->setMyDirX(-1);

			if (v->getcY() <= DIST_FROM_CENTER || (v->getcY() >= simulationArea->Height - DIST_FROM_CENTER))
				v->setMyDirY(-1);

			if (v->getMySteps() <= 0)
				v->setRandDirection(MAX_STEPS, false);
			else
				v->RandomStep();

			break;
		}
		case 1: //Random Waypoint
		{
			if (v->getInit())
			{
				//v = myVants[i];
				v->setNewRWP2(simulationArea);

				output->Text += _getTimeCRLF() + " ID [" + v->getID() + "] Way Point placed at (" + v->getMyRWP()->X + ", " + v->getMyRWP()->Y + ") at " + SystemStopWatch->ElapsedMilliseconds + "ms";

				v->setMySpeed(Speed);

				if (tsStandBy->Checked)
					v->standBy(Convert::ToInt32(readTime->Text));

				v->setInit(false);
			}

			if (v->isInsideRange(v->getMyRWP()))
				v->setInit(true);
			else
				v->nextStep(v->getMyRWP());

			break;
		}
		case 2: //Wait untill Find
		{
			if (v->getInit())
			{
				whereIamNow = v->getConnectedWithSensorNow();

				if (!_DiscoveredAllSensors())
				{
					if (_actualTimeSlotIsFree(tsRepeatTimeSlots->Checked))
					{
						if (whereIamNow != INVALID)
						{
							if (!v->getRouteListIsDiscovered(whereIamNow))
							{
								s = mySensors[whereIamNow];
								s->setDiscovered(true);

								v->setRouteListIsDiscovered(whereIamNow, true, s->getMyTimeSlot());

								output->Text += _getTimeCRLF();
								output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Discovered Sensor ID[" + whereIamNow + "] broadcasting on TimeSlot " + v->getAssociatedTimeSlotOnRouteList(whereIamNow).ToString("00");

								if (tsSetRestriction->Checked)
									v->removeIDfromPermissionLists(whereIamNow);

								if (tsStandBy->Checked)
									v->standBy(Convert::ToInt32(readTime->Text));

								if (tsSetTimeSlot->Checked)
								{
									newTimeSlot = v->getRouteListBySensorID(s->getID())->getTimeSlotsUntillHere();

									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: SensorID[" + s->getID() + "] is now reprogrammed from TimeSlot " + s->getMyTimeSlot().ToString("00") + " to " + newTimeSlot.ToString("00");
									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countUnprogrammedTimeSlots() + " Sensors to reprogram ...";
									output->Text += _getTimeCRLF();

									s->setMyMicroTimeSlotTimers_toSleep(newTimeSlot, timeSlotTime, qTimeSlots, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(numBCtimeSlots->Value), Convert::ToInt32(readTime->Value));
									v->setRouteListIsReprogrammed(whereIamNow, true, newTimeSlot);
								}
								else
								{
									if (tsSleepSensor->Checked)
										s->setSensorToSleepOnTimeSlot();
								}
							}
						}

						if (v->countDiscoveredSensorsOnRouteList() >= 1)
						{
							if (tsShowCluster->Checked)
							{
								int cluster = v->getMyCluster();

								if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
								{
									cluster = v->getNextCluster(qSensors);
									nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedOnCluster();
							}
							else
								nextID = v->getNextUnvisitedID();

							if (nextID == qSensors) //is Deposit;
							{
								if (tsBackToDeposit->Checked)
									target = v->getRouteListByIndex(0)->getMyLocation();
								else
								{
									nextID = v->getNextUnvisitedID();
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
								}
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							v->addHopCounter();
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Changing to navigation based on TimeSlots !";

							if (tsSetTimeSlot->Checked)
							{
								v->reconfigureTimeSlots();
								output->Text += "\r\n" + _getTimeCRLF() + "UAV[" + v->getID() + "]: All timeSlots were reconfigurated on Sensors !" + CRLF;
								nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

								v->setRouteListIsVisited(nextID, false);

								if (!tsBackToDeposit->Checked)
									tsBackToDeposit->Checked = true;
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #";
							output->Text += _getTimeCRLF() + " Simulation Area: " + simulationArea->Width + "x" + simulationArea->Height + " = " + simulationArea->Width*simulationArea->Height + " m^2";
							output->Text += _getTimeCRLF() + " UAV: Flyed Distance: " + v->getTotalDistance().ToString("000.00") + "m";
							output->Text += _getTimeCRLF() + " UAV: Total Hops: : " + v->getHopsCounter();
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff");
							output->Text += _getTimeCRLF() + " Sensors on Simulation: " + qSensors;
							output->Text += _getTimeCRLF() + " TimeSlots: " + qTimeSlots;
							output->Text += _getTimeCRLF() + " TimeSlotsCount: " + _getMicroTimeSlotsTotalCount();
							output->Text += _getTimeCRLF() + " UAV Decisions: " + v->getDecisionCounter();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #" + CRLF;

							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My new target is SensorID[" + s->getID() + "] at " + _getStringFromCoordinates(target);
						}
					}
					else
					{
						if (!tsSensorDiscoveredTS->Checked)
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: TimeSlot " + _getActualTimeSlot() + " is BUSY TO FLY, ... waiting ! ";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot!";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countDiscoveredSensorsOnRouteList() + " Sensors to visit ...";
							output->Text += _getTimeCRLF();
							v->standBy(CHECK_INTERVAL);
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot, let큦 go !";
							target = v->getNearestPoint(mySensors[timeSlotSensorID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							v->standBy(CHECK_INTERVAL);
						}
					}
				}
				else
				{
					if (whereIamNow != INVALID)
					{
						if (v->getConnectedWithSensorNow() == nextID)
						{
							s = mySensors[nextID];

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));

							if (tsSleepSensor->Checked)
								s->setSensorToSleepOnTimeSlot();

							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

							if (tsBackToDeposit->Checked)
							{
								if (nextID == v->findClosestDistanceToDeposit()->getMyID())
									target = v->getMyFirstLocation();
								else
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

							if (futureTimeSlot > qTimeSlots - 1)
								futureTimeSlot = futureTimeSlot - (qTimeSlots);

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately on SensorID[" + mySensors[nextID]->getID() + "] at timeSlot " + futureTimeSlot.ToString("00");

							v->addHopCounter();
						}
						else
						{
							v->standBy(CHECK_INTERVAL);
						}
					}
					else
					{
						if (v->isInsideRange(v->getMyFirstLocation()))
						{
							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);
							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Messages delivered !";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Flying to SensorID[" + mySensors[nextID]->getID() + "] now.";

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));
						}
					}
				}

				v->setMyRWP(target);
				v->setInit(false);
			}

			if (v->isInsideRange(target))
			{
				if (v->isConnectedWith(nextID, "Sensor") || _DiscoveredAllSensors())
					v->setInit(true);
				else
					v->standBy(CHECK_INTERVAL);
			}
			else
			{
				v->nextStep(target);

				if (tsScanForSensors->Checked)
				{
					if (v->getConnectedWithSensorNow() != INVALID)
					{
						whereIamNow = v->getConnectedWithSensorNow();

						if (!v->getRouteListBySensorID(whereIamNow)->getDiscovered())
							v->setInit(true);

						if (!v->getRouteListBySensorID(whereIamNow)->getVisited() && _DiscoveredAllSensors())
							v->setInit(true);
					}
				}
			}

			break;

		}
		case 3: //uTimeSlots
		{
			if (v->getInit())
			{
				whereIamNow = v->getConnectedWithSensorNow();
				whereIam = v->getWhereIam();

				if (!_DiscoveredAllSensors())
				{
					if (_actualTimeSlotIsFree(tsRepeatTimeSlots->Checked))
					{
						if (whereIamNow != INVALID)
						{
							if (!v->getRouteListIsDiscovered(whereIamNow))
							{
								s = mySensors[whereIamNow];
								s->setDiscovered(true);

								v->setRouteListIsDiscovered(whereIamNow, true, s->getMyTimeSlot());

								output->Text += _getTimeCRLF_();
								output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Discovered Sensor ID[" + whereIamNow + "] broadcasting on TimeSlot " + v->getAssociatedTimeSlotOnRouteList(whereIamNow).ToString("00");

								if (tsSetRestriction->Checked)
									v->removeIDfromPermissionLists(whereIamNow);

								if (tsStandBy->Checked)
									v->standBy(Convert::ToInt32(readTime->Value));

								if (tsSetTimeSlot->Checked)  
								{
									newTimeSlot = v->getRouteListBySensorID(s->getID())->getTimeSlotsUntillHere();

									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: SensorID[" + s->getID() + "] is now reprogrammed from TimeSlot " + s->getMyTimeSlot().ToString("00") + " to " + newTimeSlot.ToString("00");

									if (tsSetRestriction->Checked)
									{
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on this TimeSlot are: " + v->getRestrictionsOnTimeSlot(_getActualMicroTimeSlot());
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on this TimeSlot are: " + v->getPermissionOnTimeSlot(_getActualMicroTimeSlot());
									}

									s->setMyMicroTimeSlotTimers_toSleep(newTimeSlot, timeSlotTime, qTimeSlots, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(numBCtimeSlots->Value), Convert::ToInt32(readTime->Value));
									v->setRouteListIsReprogrammed(whereIamNow, true, newTimeSlot);
								}
								else
								{
									if (tsSleepSensor->Checked)
										s->setSensorToSleepOnTimeSlot();
								}
							}
						}
						else
						{
							if (tsSetRestriction->Checked)
							{
								whereIam = v->getWhereIam();

								if (whereIam != qSensors)
								{
									if (v->isSensorConnected() == 0)
									{
										if (v->addRestriction(_getActualMicroTimeSlot(), whereIam))
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restriction set on SensorID[" + whereIam + "] for timeSlot " + _getActualMicroTimeSlot().ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on this TimeSlot are: " + v->getRestrictionsOnTimeSlot(_getActualMicroTimeSlot());
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on this TimeSlot are: " + v->getPermissionOnTimeSlot(_getActualMicroTimeSlot());
										}
										else
										{
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I already have restriction set on SensorID[" + whereIam + "] to timeSlot " + _getActualMicroTimeSlot().ToString("00");
											v->standBy(CHECK_INTERVAL);
										}
									}
								}
							}
						}

						if (v->countDiscoveredSensorsOnRouteList() >= 1)
						{
							oldTarget = target;
							oldID = nextID;

							if (tsSetRestriction->Checked)
							{
								if (tsShowCluster->Checked)
								{
									int cluster = v->getMyCluster();

									if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
									{
										cluster = v->getNextCluster(qSensors);
										nextID = v->getNextUnvisitedOnCluster();
									}
									else
										nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedID_withoutDeposit(true);

								futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

								if (futureTimeSlot > qTimeSlots - 1)
									futureTimeSlot = futureTimeSlot - (qTimeSlots);

								permitedSensorList = v->getListPermitedSensorsOnTimeSlot(futureTimeSlot);

								if(v->countDiscoveredSensorsOnRouteList() > 1)
								{
									if (permitedSensorList->Contains(nextID))
									{
										if (v->countDiscoveredSensorsOnRouteList() >= 1)
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately at SensorID[" + nextID + "] on timeSlot " + futureTimeSlot.ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on TimeSlot " + futureTimeSlot.ToString("00") + " are: " + v->getRestrictionsOnTimeSlot(futureTimeSlot);;
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on TimeSlot " + futureTimeSlot.ToString("00") + " are: " + v->getPermissionOnTimeSlot(futureTimeSlot);
										}
									}
									else
									{
										permitedSensorList = v->getListUnvisitedTargets();

										UAVdevcision = false;

										if (permitedSensorList->Count > 0 && futureTimeSlot <= qTimeSlots)
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + nextID + "] is not permited on timeSlot " + futureTimeSlot.ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Checking unDiscovered Targets are: " + v->getListUnvisitedTargetsOnString();

											for (unsigned int i = 0; i < permitedSensorList->Count; i++)
											{
												futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, permitedSensorList[i], Convert::ToInt32(tsStepInterval->Value));

												if (futureTimeSlot > qTimeSlots - 1)
													futureTimeSlot = futureTimeSlot - (qTimeSlots);

												if (!v->isThereRestriction(futureTimeSlot, permitedSensorList[i]))
												{
													v->addDecisionCounter();
													nextID = permitedSensorList[i];
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + nextID + "] is permited on timeSlot " + futureTimeSlot.ToString("00");
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I made a decision ...";
													UAVdevcision = true;
													break;
												}
												else
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + permitedSensorList[i] + "] is restricted on timeSlot " + futureTimeSlot.ToString("00");
											}

											if (!UAVdevcision)
											{
												nextID = oldID;
												v->standBy(CHECK_INTERVAL);
												output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I have no place to go, ... I will wait here !";
												//v->addDecisionCounter();
											}

										}
										else
											v->standBy(CHECK_INTERVAL);
									}
								}
								else
								{
									if (whereIam == nextID)
										v->standBy(CHECK_INTERVAL);
									else
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My last target is Sensor[" + nextID + "]";
								}

							}
							else
							{
								if (tsShowCluster->Checked)
								{
									int cluster = v->getMyCluster();

									if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
									{
										cluster = v->getNextCluster(qSensors);
										nextID = v->getNextUnvisitedOnCluster();
									}
									else
										nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedID_withoutDeposit(true);
							}

							if (nextID == qSensors) //is Deposit;
							{
								if (tsBackToDeposit->Checked)
									target = v->getRouteListByIndex(0)->getMyLocation();
								else
								{
									nextID = v->getNextUnvisitedID();
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
								}
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							if (oldID != nextID)
								v->addHopCounter();	
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Changing to navigation based on TimeSlots !";

							if (tsSetTimeSlot->Checked)
							{
								v->reconfigureTimeSlots();
								output->Text += "\r\n" + _getTimeCRLF() + "UAV[" + v->getID() + "]: All timeSlots were reconfigurated on Sensors !" + CRLF;
								nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

								futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

								if (futureTimeSlot > qTimeSlots - 1)
									futureTimeSlot = futureTimeSlot - (qTimeSlots);

								if (v->getRouteListBySensorID(nextID)->getMyTimeSlot() + Convert::ToInt32(numBCtimeSlots->Value) > futureTimeSlot)
								{
									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: will not arrive at time, so I changed target from " + nextID + " to ";
									nextID = v->getNextIDbyTimeSlot(_getNextMicroTimeSlot(), qTimeSlots);
									output->Text += nextID;
								}

								v->setRouteListIsVisited(nextID, false);
								
								if(!tsBackToDeposit->Checked)
									tsBackToDeposit->Checked = true;
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #";

							for(unsigned int i = 0; i < qUAVs;i++)
							{
								output->Text += _getTimeCRLF_();
								output->Text += _getTimeCRLF() + " UAV: ID: " + myVants[i]->getID();
								output->Text += _getTimeCRLF() + " UAV: Flyed Distance: " + myVants[i]->getTotalDistance().ToString("000.00") + " m";
								output->Text += _getTimeCRLF() + " UAV: Fly Time: " + myVants[i]->getMyStopWatch()->ElapsedMilliseconds + " ms";
								output->Text += _getTimeCRLF() + " UAV: Total Hops: " + myVants[i]->getHopsCounter();
								output->Text += _getTimeCRLF() + " UAV: Total Decisions: " + myVants[i]->getDecisionCounter();
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + " Simulation Area: " + simulationArea->Width + "x" + simulationArea->Height + " = " + simulationArea->Width*simulationArea->Height + " m^2";
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff");
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->ElapsedMilliseconds;
							output->Text += _getTimeCRLF() + " Sensors on Simulation: " + qSensors;
							output->Text += _getTimeCRLF() + " TimeSlots: " + qTimeSlots;
							output->Text += _getTimeCRLF() + " TimeSlotTime: " + timeSlotTime;
							output->Text += _getTimeCRLF() + " TimeSlotsCount: " + _getMicroTimeSlotsTotalCount();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #" + CRLF;

							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My new target is SensorID[" + s->getID() + "] at " + _getStringFromCoordinates(target);
						}
					}
					else
					{
						output->Text += _getTimeCRLF_();

						if (!tsSensorDiscoveredTS->Checked)
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: TimeSlot " + _getActualMicroTimeSlot().ToString("00") + " is BUSY TO FLY, ... waiting ! ";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot!";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countDiscoveredSensorsOnRouteList() + " Sensors to visit ...";
							v->standBy(CHECK_INTERVAL);
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot, let큦 go !";
							target = v->getNearestPoint(mySensors[timeSlotSensorID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							v->standBy(CHECK_INTERVAL);
						}
					}
				}
				else
				{
					if(whereIamNow != INVALID)
					{
						if(v->getConnectedWithSensorNow() == nextID)
						{
							s = mySensors[nextID];

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));

							if (tsSleepSensor->Checked)
								s->setSensorToSleepOnTimeSlot();

							//v->setRouteListIsVisited(s->getID(), false);

							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

							if (tsBackToDeposit->Checked)
							{
								if (nextID == v->findClosestDistanceToDeposit()->getMyID())
									target = v->getMyFirstLocation();
								else
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							
							futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

							if (futureTimeSlot > qTimeSlots - 1)
								futureTimeSlot = futureTimeSlot - (qTimeSlots);

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately on SensorID[" + mySensors[nextID]->getID() + "] at timeSlot " + futureTimeSlot.ToString("00");

							v->addHopCounter();
						}
						else
						{
							v->standBy(CHECK_INTERVAL);
						}
					}
					else
					{
						if (v->isInsideRange(v->getMyFirstLocation()))
						{
							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);
							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Messages delivered !";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Flying to SensorID[" + mySensors[nextID]->getID() + "] now.";

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));
						}
					}
				}

				v->setMyRWP(target);
				v->setInit(false);
			}

			if (v->isInsideRange(target))
				v->setInit(true);
			else
			{
				v->nextStep(target);

				if (tsScanForSensors->Checked)
				{
					if (v->getConnectedWithSensorNow() != INVALID)
					{
						whereIamNow = v->getConnectedWithSensorNow();

						if (!v->getRouteListBySensorID(whereIamNow)->getDiscovered())
							v->setInit(true);

						if (!v->getRouteListBySensorID(whereIamNow)->getVisited() && _DiscoveredAllSensors())
							v->setInit(true);
					}
				}
			}

			break;
		}
		case 4: //uTimeSlots Auto
		{
			if (v->getInit())
			{
				whereIamNow = v->getConnectedWithSensorNow();
				whereIam = v->getWhereIam();

				if (!_DiscoveredAllSensors())
				{
					if (_actualTimeSlotIsFree(tsRepeatTimeSlots->Checked))
					{
						if (whereIamNow != INVALID)
						{
							if (!v->getRouteListIsDiscovered(whereIamNow))
							{
								s = mySensors[whereIamNow];
								s->setDiscovered(true);

								v->setRouteListIsDiscovered(whereIamNow, true, s->getMyTimeSlot());

								output->Text += _getTimeCRLF_();
								output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Discovered Sensor ID[" + whereIamNow + "] broadcasting on TimeSlot " + v->getAssociatedTimeSlotOnRouteList(whereIamNow).ToString("00");

								if (tsSetRestriction->Checked)
									v->removeIDfromPermissionLists(whereIamNow);

								if (tsStandBy->Checked)
									v->standBy(Convert::ToInt32(readTime->Value));

								if (tsSetTimeSlot->Checked)
								{
									newTimeSlot = v->getRouteListBySensorID(s->getID())->getTimeSlotsUntillHere();

									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: SensorID[" + s->getID() + "] is now reprogrammed from TimeSlot " + s->getMyTimeSlot().ToString("00") + " to " + newTimeSlot.ToString("00");

									if (tsSetRestriction->Checked)
									{
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on this TimeSlot are: " + v->getRestrictionsOnTimeSlot(_getActualMicroTimeSlot());
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on this TimeSlot are: " + v->getPermissionOnTimeSlot(_getActualMicroTimeSlot());
									}

									s->setMyMicroTimeSlotTimers_toSleep(newTimeSlot, timeSlotTime, qTimeSlots, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(numBCtimeSlots->Value), Convert::ToInt32(readTime->Value));
									v->setRouteListIsReprogrammed(whereIamNow, true, newTimeSlot);
								}
								else
								{
									if (tsSleepSensor->Checked)
										s->setSensorToSleepOnTimeSlot();
								}
							}
						}
						else
						{
							if (tsSetRestriction->Checked)
							{
								whereIam = v->getWhereIam();

								if (whereIam != qSensors)
								{
									if (v->isSensorConnected() == 0)
									{
										if (v->addRestriction(_getActualMicroTimeSlot(), whereIam))
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restriction set on SensorID[" + whereIam + "] for timeSlot " + _getActualMicroTimeSlot().ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on this TimeSlot are: " + v->getRestrictionsOnTimeSlot(_getActualMicroTimeSlot());
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on this TimeSlot are: " + v->getPermissionOnTimeSlot(_getActualMicroTimeSlot());
										}
										else
										{
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I already have restriction set on SensorID[" + whereIam + "] to timeSlot " + _getActualMicroTimeSlot().ToString("00");
											v->standBy(CHECK_INTERVAL);
										}
									}
								}
							}
						}

						if (v->countDiscoveredSensorsOnRouteList() >= 1)
						{
							oldTarget = target;
							oldID = nextID;

							if (tsSetRestriction->Checked)
							{
								if (tsShowCluster->Checked)
								{
									int cluster = v->getMyCluster();

									if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
									{
										cluster = v->getNextCluster(qSensors);
										nextID = v->getNextUnvisitedOnCluster();
									}
									else
										nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedID_withoutDeposit(true);

								futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

								if (futureTimeSlot > qTimeSlots - 1)
									futureTimeSlot = futureTimeSlot - (qTimeSlots);

								permitedSensorList = v->getListPermitedSensorsOnTimeSlot(futureTimeSlot);

								if (v->countDiscoveredSensorsOnRouteList() > 1)
								{
									if (permitedSensorList->Contains(nextID))
									{
										if (v->countDiscoveredSensorsOnRouteList() >= 1)
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately at SensorID[" + nextID + "] on timeSlot " + futureTimeSlot.ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Restricted Sensors on TimeSlot " + futureTimeSlot.ToString("00") + " are: " + v->getRestrictionsOnTimeSlot(futureTimeSlot);;
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Permited Sensors on TimeSlot " + futureTimeSlot.ToString("00") + " are: " + v->getPermissionOnTimeSlot(futureTimeSlot);
										}
									}
									else
									{
										permitedSensorList = v->getListUnvisitedTargets();

										UAVdevcision = false;

										if (permitedSensorList->Count > 0 && futureTimeSlot <= qTimeSlots)
										{
											output->Text += _getTimeCRLF_();
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + nextID + "] is not permited on timeSlot " + futureTimeSlot.ToString("00");
											output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Checking unDiscovered Targets are: " + v->getListUnvisitedTargetsOnString();

											for (unsigned int i = 0; i < permitedSensorList->Count; i++)
											{
												futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, permitedSensorList[i], Convert::ToInt32(tsStepInterval->Value));

												if (futureTimeSlot > qTimeSlots - 1)
													futureTimeSlot = futureTimeSlot - (qTimeSlots);

												if (!v->isThereRestriction(futureTimeSlot, permitedSensorList[i]))
												{
													v->addDecisionCounter();
													nextID = permitedSensorList[i];
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + nextID + "] is permited on timeSlot " + futureTimeSlot.ToString("00");
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I made a decision ...";
													UAVdevcision = true;
													break;
												}
												else
													output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Sensor[" + permitedSensorList[i] + "] is restricted on timeSlot " + futureTimeSlot.ToString("00");
											}

											if (!UAVdevcision)
											{
												nextID = oldID;
												v->standBy(CHECK_INTERVAL);
												output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I have no place to go, ... I will wait here !";
												//v->addDecisionCounter();
											}

										}
										else
											v->standBy(CHECK_INTERVAL);
									}
								}
								else
								{
									if (whereIam == nextID)
										v->standBy(CHECK_INTERVAL);
									else
										output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My last target is Sensor[" + nextID + "]";
								}

							}
							else
							{
								if (tsShowCluster->Checked)
								{
									int cluster = v->getMyCluster();

									if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
									{
										cluster = v->getNextCluster(qSensors);
										nextID = v->getNextUnvisitedOnCluster();
									}
									else
										nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedID_withoutDeposit(true);
							}

							if (nextID == qSensors) //is Deposit;
							{
								if (tsBackToDeposit->Checked)
									target = v->getRouteListByIndex(0)->getMyLocation();
								else
								{
									nextID = v->getNextUnvisitedID();
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
								}
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							if (oldID != nextID)
								v->addHopCounter();
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Changing to navigation based on TimeSlots !";

							if (tsSetTimeSlot->Checked)
							{
								v->reconfigureTimeSlots();
								output->Text += "\r\n" + _getTimeCRLF() + "UAV[" + v->getID() + "]: All timeSlots were reconfigurated on Sensors !" + CRLF;
								nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

								futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

								if (futureTimeSlot > qTimeSlots - 1)
									futureTimeSlot = futureTimeSlot - (qTimeSlots);

								if (v->getRouteListBySensorID(nextID)->getMyTimeSlot() + Convert::ToInt32(numBCtimeSlots->Value) > futureTimeSlot)
								{
									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: will not arrive at time, so I changed target from " + nextID + " to ";
									nextID = v->getNextIDbyTimeSlot(_getNextMicroTimeSlot(), qTimeSlots);
									output->Text += nextID;
								}

								v->setRouteListIsVisited(nextID, false);

								if (!tsBackToDeposit->Checked)
									tsBackToDeposit->Checked = true;
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #";

							for (unsigned int i = 0; i < qUAVs; i++)
							{
								output->Text += _getTimeCRLF_();
								output->Text += _getTimeCRLF() + " UAV: ID: " + myVants[i]->getID();
								output->Text += _getTimeCRLF() + " UAV: Flyed Distance: " + myVants[i]->getTotalDistance().ToString("000.00") + " m";
								output->Text += _getTimeCRLF() + " UAV: Fly Time: " + myVants[i]->getMyStopWatch()->ElapsedMilliseconds + " ms";
								output->Text += _getTimeCRLF() + " UAV: Total Hops: " + myVants[i]->getHopsCounter();
								output->Text += _getTimeCRLF() + " UAV: Total Decisions: " + myVants[i]->getDecisionCounter();
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + " Simulation Area: " + simulationArea->Width + "x" + simulationArea->Height + " = " + simulationArea->Width*simulationArea->Height + " m^2";
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff");
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->ElapsedMilliseconds;
							output->Text += _getTimeCRLF() + " Sensors on Simulation: " + qSensors;
							output->Text += _getTimeCRLF() + " TimeSlots: " + qTimeSlots;
							output->Text += _getTimeCRLF() + " TimeSlotTime: " + timeSlotTime;
							output->Text += _getTimeCRLF() + " TimeSlotsCount: " + _getMicroTimeSlotsTotalCount();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #" + CRLF;

							if (simulationCounter == 0)
							{
								logger = gcnew StreamWriter("log\\S" + qSensors + "_ResumeLog_" + _getDateTime() + ".csv", true);

								toLog = "index;UAVs;Distance;FlyTime;Hops;Decisions;Speed;SystemTime;SensorsOnSimulation;TimeSlots;TimeSlotTime;BCTime;TimeSlotsCount;routeTotalDistance";

								logger->WriteLine(toLog);

								toLog = simulationCounter + ";";

								int counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter++;
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter += myVants[i]->getTotalDistance();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getFlyTime() > 0)
										counter += myVants[i]->getFlyTime();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getHopsCounter() > 0)
										counter += myVants[i]->getHopsCounter();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getDecisionCounter() > 0)
										counter += myVants[i]->getDecisionCounter();
								}

								toLog += counter + ";";

								toLog += myVants[0]->getMyRealSpeed() + ";";
								toLog += SystemStopWatch->ElapsedMilliseconds + ";";
								toLog += qSensors + ";";
								toLog += qTimeSlots + ";";
								toLog += timeSlotTime + ";";
								toLog += (numBCtimeSlots->Value * timeSlotTime) + ";";
								toLog += _getMicroTimeSlotsTotalCount() + ";";
								toLog += v->getRouteTotalDistance() + ";";
							}
							else
							{
								toLog = simulationCounter + ";";

								int counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter++;
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter += myVants[i]->getTotalDistance();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getFlyTime() > 0)
										counter += myVants[i]->getFlyTime();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getHopsCounter() > 0)
										counter += myVants[i]->getHopsCounter();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getDecisionCounter() > 0)
										counter += myVants[i]->getDecisionCounter();
								}

								toLog += counter + ";";

								toLog += myVants[0]->getMyRealSpeed() + ";";
								toLog += SystemStopWatch->ElapsedMilliseconds + ";";
								toLog += qSensors + ";";
								toLog += qTimeSlots + ";";
								toLog += timeSlotTime + ";";
								toLog += (numBCtimeSlots->Value * timeSlotTime) + ";";
								toLog += _getMicroTimeSlotsTotalCount() + ";";
								toLog += v->getRouteTotalDistance() + ";";
							}

							logger->WriteLine(toLog);
							logger->Flush();

							simulationCounter++;

							tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");

							if (simulationCounter >= numQtySimulation->Value)
							{
								logger->Close();
								//simulationCounter = 0;

								tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");
								
								_simulationPlayButton(false);
								Thread::Sleep(Convert::ToInt32(numSimulationPause->Value));

								_ResetScenarioForFinalSimulation(qUAVs, qSensors);
							}
							else
							{
								tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");
								_simulationPlayButton(false);

								Thread::Sleep(Convert::ToInt32(numSimulationPause->Value));

								_ResetScenarioForFinalSimulation(qUAVs, qSensors);
							}

							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My new target is SensorID[" + s->getID() + "] at " + _getStringFromCoordinates(target);
						}
					}
					else
					{
						output->Text += _getTimeCRLF_();

						if (!tsSensorDiscoveredTS->Checked)
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: TimeSlot " + _getActualMicroTimeSlot().ToString("00") + " is BUSY TO FLY, ... waiting ! ";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot!";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countDiscoveredSensorsOnRouteList() + " Sensors to visit ...";
							v->standBy(CHECK_INTERVAL);
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot, let큦 go !";
							target = v->getNearestPoint(mySensors[timeSlotSensorID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							v->standBy(CHECK_INTERVAL);
						}
					}
				}
				else
				{
					if (whereIamNow != INVALID)
					{
						if (v->getConnectedWithSensorNow() == nextID)
						{
							s = mySensors[nextID];

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));

							if (tsSleepSensor->Checked)
								s->setSensorToSleepOnTimeSlot();

							//v->setRouteListIsVisited(s->getID(), false);

							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

							if (tsBackToDeposit->Checked)
							{
								if (nextID == v->findClosestDistanceToDeposit()->getMyID())
									target = v->getMyFirstLocation();
								else
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

							if (futureTimeSlot > qTimeSlots - 1)
								futureTimeSlot = futureTimeSlot - (qTimeSlots);

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately on SensorID[" + mySensors[nextID]->getID() + "] at timeSlot " + futureTimeSlot.ToString("00");

							v->addHopCounter();
						}
						else
						{
							v->standBy(CHECK_INTERVAL);
						}
					}
					else
					{
						if (v->isInsideRange(v->getMyFirstLocation()))
						{
							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);
							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Messages delivered !";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Flying to SensorID[" + mySensors[nextID]->getID() + "] now.";

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));
						}
					}
				}

				v->setMyRWP(target);
				v->setInit(false);
			}

			if (v->isInsideRange(target))
				v->setInit(true);
			else
			{
				v->nextStep(target);

				if (tsScanForSensors->Checked)
				{
					if (v->getConnectedWithSensorNow() != INVALID)
					{
						whereIamNow = v->getConnectedWithSensorNow();

						if (!v->getRouteListBySensorID(whereIamNow)->getDiscovered())
							v->setInit(true);

						if (!v->getRouteListBySensorID(whereIamNow)->getVisited() && _DiscoveredAllSensors())
							v->setInit(true);
					}
				}
			}

			break;
		}
		case 5: //Wait untill Find Auto
		{
			if (v->getInit())
			{
				whereIamNow = v->getConnectedWithSensorNow();

				if (!_DiscoveredAllSensors())
				{
					if (_actualTimeSlotIsFree(tsRepeatTimeSlots->Checked))
					{
						if (whereIamNow != INVALID)
						{
							if (!v->getRouteListIsDiscovered(whereIamNow))
							{
								s = mySensors[whereIamNow];
								s->setDiscovered(true);

								v->setRouteListIsDiscovered(whereIamNow, true, s->getMyTimeSlot());

								output->Text += _getTimeCRLF();
								output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Discovered Sensor ID[" + whereIamNow + "] broadcasting on TimeSlot " + v->getAssociatedTimeSlotOnRouteList(whereIamNow).ToString("00");

								if (tsSetRestriction->Checked)
									v->removeIDfromPermissionLists(whereIamNow);

								if (tsStandBy->Checked)
									v->standBy(Convert::ToInt32(readTime->Text));

								if (tsSetTimeSlot->Checked)
								{
									newTimeSlot = v->getRouteListBySensorID(s->getID())->getTimeSlotsUntillHere();

									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: SensorID[" + s->getID() + "] is now reprogrammed from TimeSlot " + s->getMyTimeSlot().ToString("00") + " to " + newTimeSlot.ToString("00");
									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countUnprogrammedTimeSlots() + " Sensors to reprogram ...";
									output->Text += _getTimeCRLF();

									s->setMyMicroTimeSlotTimers_toSleep(newTimeSlot, timeSlotTime, qTimeSlots, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(numBCtimeSlots->Value), Convert::ToInt32(readTime->Value));
									v->setRouteListIsReprogrammed(whereIamNow, true, newTimeSlot);
								}
								else
								{
									if (tsSleepSensor->Checked)
										s->setSensorToSleepOnTimeSlot();
								}
							}
						}

						if (v->countDiscoveredSensorsOnRouteList() >= 1)
						{
							if (tsShowCluster->Checked)
							{
								int cluster = v->getMyCluster();

								if (v->countDiscoveredSensorsOnCluster(cluster) >= v->countSensorsOnCluster(cluster) || (v->countSensorsOnCluster(cluster) <= 0))
								{
									cluster = v->getNextCluster(qSensors);
									nextID = v->getNextUnvisitedOnCluster();
								}
								else
									nextID = v->getNextUnvisitedOnCluster();
							}
							else
								nextID = v->getNextUnvisitedID();

							if (nextID == qSensors) //is Deposit;
							{
								if (tsBackToDeposit->Checked)
									target = v->getRouteListByIndex(0)->getMyLocation();
								else
								{
									nextID = v->getNextUnvisitedID();
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
								}
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							v->addHopCounter();
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Changing to navigation based on TimeSlots !";

							if (tsSetTimeSlot->Checked)
							{
								v->reconfigureTimeSlots();
								output->Text += "\r\n" + _getTimeCRLF() + "UAV[" + v->getID() + "]: All timeSlots were reconfigurated on Sensors !" + CRLF;
								//nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

								//futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

/*								if (futureTimeSlot > qTimeSlots - 1)
									futureTimeSlot = futureTimeSlot - (qTimeSlots);

								if (v->getRouteListBySensorID(nextID)->getMyTimeSlot() + Convert::ToInt32(numBCtimeSlots->Value) > futureTimeSlot)
								{
									output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: will not arrive at time, so I changed target from " + nextID + " to ";
									nextID = v->getNextIDbyTimeSlot(_getNextMicroTimeSlot(), qTimeSlots);
									output->Text += nextID;
								}

								v->setRouteListIsVisited(nextID, false);

								if (!tsBackToDeposit->Checked)
									tsBackToDeposit->Checked = true;
*/
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #";

							for (unsigned int i = 0; i < qUAVs; i++)
							{
								output->Text += _getTimeCRLF_();
								output->Text += _getTimeCRLF() + " UAV: ID: " + myVants[i]->getID();
								output->Text += _getTimeCRLF() + " UAV: Flyed Distance: " + myVants[i]->getTotalDistance().ToString("000.00") + " m";
								output->Text += _getTimeCRLF() + " UAV: Fly Time: " + myVants[i]->getMyStopWatch()->ElapsedMilliseconds + " ms";
								output->Text += _getTimeCRLF() + " UAV: Total Hops: " + myVants[i]->getHopsCounter();
								output->Text += _getTimeCRLF() + " UAV: Total Decisions: " + myVants[i]->getDecisionCounter();
							}

							output->Text += _getTimeCRLF_();
							output->Text += _getTimeCRLF() + " Simulation Area: " + simulationArea->Width + "x" + simulationArea->Height + " = " + simulationArea->Width*simulationArea->Height + " m^2";
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff");
							output->Text += _getTimeCRLF() + " System Time: " + SystemStopWatch->ElapsedMilliseconds;
							output->Text += _getTimeCRLF() + " Sensors on Simulation: " + qSensors;
							output->Text += _getTimeCRLF() + " TimeSlots: " + qTimeSlots;
							output->Text += _getTimeCRLF() + " TimeSlotTime: " + timeSlotTime;
							output->Text += _getTimeCRLF() + " TimeSlotsCount: " + _getMicroTimeSlotsTotalCount();
							output->Text += _getTimeCRLF() + "# ------------------------------------------------------------ #" + CRLF;

							if (simulationCounter == 0)
							{
								logger = gcnew StreamWriter("log\\S" + qSensors + "_ResumeLog_" + _getDateTime() + ".csv", true);

								toLog = "index;UAVs;Distance;FlyTime;Hops;Decisions;Speed;SystemTime;SensorsOnSimulation;TimeSlots;TimeSlotTime;BCTime;TimeSlotsCount;routeTotalDistance";

								logger->WriteLine(toLog);

								toLog = simulationCounter + ";";

								int counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter++;
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter += myVants[i]->getTotalDistance();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getFlyTime() > 0)
										counter += myVants[i]->getFlyTime();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getHopsCounter() > 0)
										counter += myVants[i]->getHopsCounter();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getDecisionCounter() > 0)
										counter += myVants[i]->getDecisionCounter();
								}

								toLog += counter + ";";

								toLog += myVants[0]->getMyRealSpeed() + ";";
								toLog += SystemStopWatch->ElapsedMilliseconds + ";";
								toLog += qSensors + ";";
								toLog += qTimeSlots + ";";
								toLog += timeSlotTime + ";";
								toLog += (numBCtimeSlots->Value * timeSlotTime) + ";";
								toLog += _getMicroTimeSlotsTotalCount() + ";";
								toLog += v->getRouteTotalDistance() + ";";
							}
							else
							{
								toLog = simulationCounter + ";";

								int counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter++;
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getTotalDistance() > 0)
										counter += myVants[i]->getTotalDistance();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getFlyTime() > 0)
										counter += myVants[i]->getFlyTime();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getHopsCounter() > 0)
										counter += myVants[i]->getHopsCounter();
								}

								toLog += counter + ";";
								counter = 0;

								for (unsigned int i = 0; i < qUAVs; i++)
								{
									if (myVants[i]->getDecisionCounter() > 0)
										counter += myVants[i]->getDecisionCounter();
								}

								toLog += counter + ";";

								toLog += myVants[0]->getMyRealSpeed() + ";";
								toLog += SystemStopWatch->ElapsedMilliseconds + ";";
								toLog += qSensors + ";";
								toLog += qTimeSlots + ";";
								toLog += timeSlotTime + ";";
								toLog += (numBCtimeSlots->Value * timeSlotTime) + ";";
								toLog += _getMicroTimeSlotsTotalCount() + ";";
								toLog += v->getRouteTotalDistance() + ";";
							}

							logger->WriteLine(toLog);
							logger->Flush();

							simulationCounter++;

							tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");

							if (simulationCounter >= numQtySimulation->Value)
							{
								logger->Close();
								//simulationCounter = 0;

								tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");

								_simulationPlayButton(false);
								Thread::Sleep(Convert::ToInt32(numSimulationPause->Value));

								_ResetScenarioForFinalSimulation(1, qSensors);
							}
							else
							{
								tsSimulationCounter->Text = simulationCounter.ToString("00") + "/" + numQtySimulation->Value.ToString("000");
								_simulationPlayButton(false);

								Thread::Sleep(Convert::ToInt32(numSimulationPause->Value));

								_ResetScenarioForFinalSimulation(1, qSensors);
							}

							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: My new target is SensorID[" + s->getID() + "] at " + _getStringFromCoordinates(target);
						}
					}
					else
					{
						if (!tsSensorDiscoveredTS->Checked)
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: TimeSlot " + _getActualTimeSlot() + " is BUSY TO FLY, ... waiting ! ";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot!";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Still left " + v->countDiscoveredSensorsOnRouteList() + " Sensors to visit ...";
							output->Text += _getTimeCRLF();
							v->standBy(CHECK_INTERVAL);
						}
						else
						{
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I know SensorID[" + timeSlotSensorID + "] is broadcasting at this TimeSlot, let큦 go !";
							target = v->getNearestPoint(mySensors[timeSlotSensorID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							v->standBy(CHECK_INTERVAL);
						}
					}
				}
				else
				{
					if (whereIamNow != INVALID)
					{
						if (v->getConnectedWithSensorNow() == nextID)
						{
							s = mySensors[nextID];

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));

							if (tsSleepSensor->Checked)
								s->setSensorToSleepOnTimeSlot();

							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);

							if (tsBackToDeposit->Checked)
							{
								if (nextID == v->findClosestDistanceToDeposit()->getMyID())
									target = v->getMyFirstLocation();
								else
									target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));
							}
							else
								target = v->getNearestPoint(mySensors[nextID]->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							futureTimeSlot = _getActualMicroTimeSlot() + v->getTimeSlotsToID(timeSlotTime, nextID, Convert::ToInt32(tsStepInterval->Value));

							if (futureTimeSlot > qTimeSlots - 1)
								futureTimeSlot = futureTimeSlot - (qTimeSlots);

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: I will arrive approximately on SensorID[" + mySensors[nextID]->getID() + "] at timeSlot " + futureTimeSlot.ToString("00");

							v->addHopCounter();
						}
						else
						{
							v->standBy(CHECK_INTERVAL);
						}
					}
					else
					{
						if (v->isInsideRange(v->getMyFirstLocation()))
						{
							nextID = v->getNextIDbyTimeSlot(_getActualMicroTimeSlot(), qTimeSlots);
							s = mySensors[nextID];
							target = v->getNearestPoint(s->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value));

							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Messages delivered !";
							output->Text += _getTimeCRLF() + "UAV[" + v->getID() + "]: Flying to SensorID[" + mySensors[nextID]->getID() + "] now.";

							if (tsStandBy->Checked)
								v->standBy(Convert::ToInt32(readTime->Text));
						}
					}
				}

				v->setMyRWP(target);
				v->setInit(false);
			}

			if (v->isInsideRange(target))
			{
				if (v->isConnectedWith(nextID, "Sensor") || _DiscoveredAllSensors())
					v->setInit(true);
				else
					v->standBy(CHECK_INTERVAL);
			}
			else
			{
				v->nextStep(target);

				if (tsScanForSensors->Checked)
				{
					if (v->getConnectedWithSensorNow() != INVALID)
					{
						whereIamNow = v->getConnectedWithSensorNow();

						if (!v->getRouteListBySensorID(whereIamNow)->getDiscovered())
							v->setInit(true);

						if (!v->getRouteListBySensorID(whereIamNow)->getVisited() && _DiscoveredAllSensors())
							v->setInit(true);
					}
				}
			}

			break;
		}
	}

	if (tsSwapUAVs->Checked)
	{
		target = v->getMyFirstLocation();
		v->setMyRWP(target);

		if ((v->isInsideRange(target)))
		{
			int actualUAV, nextUAV;
				
			actualUAV = v->getID();
			nextUAV = actualUAV + 1;    

			if (nextUAV >= qUAVs)
			{
				nQUAVs = nextUAV+1;
				createNode(nQUAVs, "uav");

				//create a new UAV;
				myVants[nextUAV]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (myVants[nextUAV]->getID() + 1) * 35);
				myVants[nextUAV]->setMyFirstLocation(myVants[nextUAV]->getCenterLocation());
				
				myVants[nextUAV]->copyRoutingParametersFromUAV(myVants[actualUAV], qTimeSlots);

				myVants[actualUAV]->setActive(false);
				myVants[actualUAV]->getMyStopWatch()->Stop();

				output->Text += _getTimeCRLF() + "UAV[" + nextUAV + "]: Routing and Restriction Data successfully received from UAV[" + actualUAV + "] !!!" + CRLF;

				v = myVants[nextUAV];
				v->getMyStopWatch()->Start();
				v->setActive(true);
				target = v->getRouteListByID(nextID);
			}
			else
			{
				myVants[nextUAV]->copyRoutingParametersFromUAV(myVants[actualUAV], qTimeSlots);
				myVants[actualUAV]->setActive(false);
				myVants[actualUAV]->getMyStopWatch()->Stop();

				output->Text += _getTimeCRLF() + "UAV[" + nextUAV + "]: Routing and Restriction Data successfully received from UAV[" + actualUAV + "] !!!" + CRLF;

				v = myVants[nextUAV];

				v->getMyStopWatch()->Start();
				v->setActive(true);
				target = v->getRouteListByID(nextID);
			}

			tsSwapUAVs->Checked = false;
		}

		v->setInit(false);
		v->setMyRWP(target);
	}

	simulationArea->Refresh();
}

private: System::Void simulationArea_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
	graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBilinear;
	graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::HighQuality;

	if (cbUavUav->Checked)
	{
		for (unsigned int i = 0; i < qUAVs; i++)
		{
			v1 = myVants[i];

			if (tsDrawPoint->Checked && v1->getMyRWP() != nullptr)
				graphics->DrawEllipse(gcnew Pen(Color::Black, 2), (int)v1->getMyRWP()->X, (int)v1->getMyRWP()->Y, 2, 2);

			if (tsDrawCircleUAV->Checked)
				graphics->DrawEllipse(DashedBluePen, v1->getCenterLocation().X - Convert::ToInt32(numConRangeV2V->Value), v1->getCenterLocation().Y - Convert::ToInt32(numConRangeV2V->Value), Convert::ToInt32(numConRangeV2V->Value) * 2, Convert::ToInt32(numConRangeV2V->Value) * 2);

			for (unsigned int j = 0; j < qUAVs; j++)
			{
				v2 = myVants[j];

				if (i != j && _getDistanceFrom(v1->getCenterLocation(), v2->getCenterLocation()) < Convert::ToInt32(numConRangeV2V->Value))
				{
					v1->setConnection(v2);

					graphics->DrawLine(RedPen, v1->drawNearestPoint(v2->getCenterLocation(), DIST_FROM_CENTER), v2->drawNearestPoint(v1->getCenterLocation(), DIST_FROM_CENTER));

					if (v1->hasMessage())
					{
						if (v1->getDistanceFrom(ss->getCenterLocation()) > v2->getDistanceFrom(ss->getCenterLocation()))
							v1->sendMessage(v2, false);
					}
				}
				else
					v1->clearConnection(v2);
			}
		}
	}

	if (cbUAVtoServer->Checked)
	{
		for (unsigned int i = 0; i < qUAVs; i++)
		{
			v1 = myVants[i];

			if (_getDistanceFrom(v1->getCenterLocation(), ss->getCenterLocation()) < Convert::ToInt32(numConRangeV2Sever->Value))
			{
				v1->setConnection(ss);

				if (v1->hasMessage())
					v1->sendMessage(ss);

				graphics->DrawLine(GreenPen, v1->drawNearestPoint(ss->getAntennaLocation(), DIST_FROM_CENTER), ss->getNearestPoint2(v1->getCenterLocation(), DIST_FROM_CENTER));
			}
			else
				v1->clearConnection(ss);
		}
	}

	if (cbUAVtoSesnor->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			s = mySensors[i];

			for (unsigned int j = 0; j < qUAVs; j++)
			{
				v1 = myVants[j];

				if ((_getDistanceFrom(v1->getCenterLocation(), s->getCenterLocation()) - v1->getSpeed()*2)  <= 5 + Convert::ToInt32(numConRangeV2S->Value) && s->getMyState())
				{
					v1->setConnection(s);

					if (s->hasMessage()) 
						s->sendMessage(v1);

					if (v1->getDistanceFrom(s->getCenterLocation()) > DIST_FROM_CENTER)
						graphics->DrawLine(BluePen, v1->drawNearestPoint(s->getCenterLocation(), DIST_FROM_CENTER), s->getNearestPoint(v1->getCenterLocation(), DIST_FROM_CENTER));
				}
				else
					v1->clearConnection(s);
			}

			if (tsDrawCircleSensor->Checked )
			{
				if (s->getMyState())
				{
					if(s->getDiscovered())
						graphics->DrawEllipse(DashedGreenPen, s->getCenterLocation().X - Convert::ToInt32(numConRangeV2S->Value), s->getCenterLocation().Y - Convert::ToInt32(numConRangeV2S->Value), Convert::ToInt32(numConRangeV2S->Value) * 2, Convert::ToInt32(numConRangeV2S->Value) * 2);
					else
						graphics->DrawEllipse(DashedRedPen, s->getCenterLocation().X - Convert::ToInt32(numConRangeV2S->Value), s->getCenterLocation().Y - Convert::ToInt32(numConRangeV2S->Value), Convert::ToInt32(numConRangeV2S->Value) * 2, Convert::ToInt32(numConRangeV2S->Value) * 2);
				}
			}
		}
	}

	if (tsShowRoute->Checked)
	{
		v1 = myVants[0];

		int redDistance = 0;
		int greenDistance = 0;
		int blueDistance = 0;
		int cyanDistance = 0;

		for (unsigned int i = 1; i < _getActiveSensors(); i++)
		{
			if (v1->getMyFirstLocation() != nullptr && v1->getTarget(i) != nullptr && v1->getFly(i) != nullptr && v1->getFly(i-1) != nullptr && v1->getHibridFly(i) != nullptr)
			{
				if (i == 1)
				{
					if(tsRedRoute->Checked)
					{
						redDistance += _getDistanceFrom(v1->getCenterLocation(), v1->getRoute(i - 1)->getCenterLocation());
						graphics->DrawLine(RedPenRoundAnchor, (Point)v1->getCenterLocation(), v1->getRoute(i - 1)->getCenterLocation());
							
						if(tsRouteInfo->Checked)
							graphics->DrawString(redDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getRoute(i - 1)->getCenterLocation()), drawFont, RedBrush, (float)v1->getRoute(i - 1)->getLocation()->X + 30, (float)v1->getRoute(i - 1)->getLocation()->Y, stringFormat);
					}

					if(tsGreenRoute->Checked)
					{
						greenDistance += _getDistanceFrom(v1->getCenterLocation(), v1->getTarget(i - 1));
						graphics->DrawLine(GreenPenRoundAnchor, (Point)v1->getCenterLocation(), (Point)v1->getTarget(i - 1));
							
						if (tsRouteInfo->Checked)
							graphics->DrawString(greenDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getTarget(i - 1)), drawFont, GreenBrush, (Point)v1->getTarget(i - 1), stringFormat);

					}

					if(tsBlueRoute->Checked)
					{
						blueDistance += _getDistanceFrom(v1->getCenterLocation(), v1->getFly(i - 1));
						graphics->DrawLine(BluePenRoundAnchor, (Point)v1->getCenterLocation(), (Point)v1->getFly(i - 1));
							
						if (tsRouteInfo->Checked)
							graphics->DrawString(blueDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getFly(i - 1)), drawFont, BlueBrush, (Point)v1->getFly(i - 1), stringFormat);
					}

					if (tsCyanRoute->Checked)
					{
						cyanDistance = _getDistanceFrom(v1->getCenterLocation(), v1->getHibridFly(i - 1));
						graphics->DrawLine(CyanPenRoundAnchor, (Point)v1->getCenterLocation(), (Point)v1->getHibridFly(i - 1));

						if (tsRouteInfo->Checked)
							graphics->DrawString(cyanDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getFly(i - 1)), drawFont, CyanBrush, (Point)v1->getFly(i - 1), stringFormat);

					}
				}

				if(tsClosedCircuit->Checked)
				{
					if (i == (_getActiveSensors() - 1))
					{
						if (tsRedRoute->Checked)
							graphics->DrawLine(RedPenRoundAnchor, v1->getRoute(i)->getCenterLocation(), (Point)v1->getMyFirstLocation());

						if (tsGreenRoute->Checked)
							graphics->DrawLine(GreenPenRoundAnchor, (Point)v1->getTarget(i), (Point)v1->getMyFirstLocation());

						if (tsBlueRoute->Checked)
							graphics->DrawLine(BluePenRoundAnchor,(Point)v1->getFly(i), (Point)v1->getMyFirstLocation());

						if (tsCyanRoute->Checked)
							graphics->DrawLine(CyanPenRoundAnchor, (Point)v1->getHibridFly(i), (Point)v1->getMyFirstLocation());
					}
				}

				if(tsRedRoute->Checked)
				{
					redDistance += _getDistanceFrom(v1->getRoute(i - 1)->getCenterLocation(), v1->getRoute(i)->getCenterLocation());
					graphics->DrawLine(RedPenRoundAnchor, (Point)v1->getRoute(i - 1)->getCenterLocation(), v1->getRoute(i)->getCenterLocation());
						
					if (tsRouteInfo->Checked)
						graphics->DrawString(redDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getRoute(i)->getCenterLocation()), drawFont, RedBrush, (float)v1->getRoute(i)->getLocation()->X + 30, (float)v1->getRoute(i)->getLocation()->Y, stringFormat);
				}

				if (tsGreenRoute->Checked)
				{
					greenDistance += _getDistanceFrom(v1->getTarget(i - 1), v1->getTarget(i));
					graphics->DrawLine(GreenPenRoundAnchor, (Point)v1->getTarget(i - 1), (Point)v1->getTarget(i));
						
					if (tsRouteInfo->Checked)
						graphics->DrawString(greenDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getTarget(i)), drawFont, GreenBrush, (Point)v1->getTarget(i), stringFormat);
				}

				if (tsBlueRoute->Checked)
				{
					blueDistance += _getDistanceFrom(v1->getFly(i - 1), v1->getFly(i));
					graphics->DrawLine(BluePenRoundAnchor, (Point)v1->getFly(i - 1), (Point)v1->getFly(i));
						
					if (tsRouteInfo->Checked)
						graphics->DrawString(blueDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getFly(i)), drawFont, BlueBrush, (Point)v1->getFly(i), stringFormat);
				}

				if (tsCyanRoute->Checked)
				{
					cyanDistance = _getDistanceFrom(v1->getHibridFly(i - 1), v1->getHibridFly(i));
					graphics->DrawLine(CyanPenRoundAnchor, (Point)v1->getHibridFly(i - 1), (Point)v1->getHibridFly(i));

					if (tsRouteInfo->Checked)
						graphics->DrawString(cyanDistance.ToString() + "\r\n" + _getStringFromCoordinates(v1->getHibridFly(i)), drawFont, CyanBrush, (Point)v1->getHibridFly(i), stringFormat);
				}

			}
		}
	}
	
}

private: System::Void simulator_Load(System::Object^  sender, System::EventArgs^  e)
{
	v = myVants[0];

	qUAVs = 0;
	qSensors = 0;
	nQUAVs = 1;
	nQSensors = 10;
	Speed = 2;
	activeSensors = qSensors;
	dragAndDrop = false;

	graphics = simulationArea->CreateGraphics();
	splitContainer3->Panel2Collapsed = true;

	BluePen = gcnew Pen(Color::CornflowerBlue, 1.5);
	RedPen = gcnew Pen(Color::OrangeRed, 1.5);
	GreenPen = gcnew Pen(Color::ForestGreen, 1.5);
	CyanPen = gcnew Pen(Color::FromArgb(0, 255, 255), 1.5);

	GreenPenRoundAnchor = gcnew Pen(Color::ForestGreen, 1.5);
	RedPenRoundAnchor = gcnew Pen(Color::Red, 0.5);
	BluePenRoundAnchor = gcnew Pen(Color::Blue, 0.5);
	CyanPenRoundAnchor = gcnew Pen(Color::FromArgb(0,255,255), 0.5);

	DashedRedPen = gcnew Pen(Color::Red, 0.5);
	DashedGreenPen = gcnew Pen(Color::Green, 0.5);
	DashedBluePen = gcnew Pen(Color::Blue, 0.5);

	array<Single>^ myDashPattern = { 4.0f, 4.0f };

	DashedRedPen->DashPattern = myDashPattern;
	DashedGreenPen->DashPattern = myDashPattern;
	DashedBluePen->DashPattern = myDashPattern;

	RedPen->StartCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
	RedPen->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;

	BluePen->StartCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
	BluePen->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;

	GreenPen->StartCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;
	GreenPen->EndCap = System::Drawing::Drawing2D::LineCap::ArrowAnchor;

	GreenPenRoundAnchor->StartCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;
	GreenPenRoundAnchor->EndCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;

	BluePenRoundAnchor->StartCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;
	BluePenRoundAnchor->EndCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;

	RedPenRoundAnchor->StartCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;
	RedPenRoundAnchor->EndCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;

	CyanPenRoundAnchor->StartCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;
	CyanPenRoundAnchor->EndCap = System::Drawing::Drawing2D::LineCap::RoundAnchor;

	v1 = gcnew Vant();
	v2 = gcnew Vant();
	ss = gcnew server();
	s = gcnew Sensor();

	createNode(1, "server");
	createNode(nQSensors, "sensor");
	createNode(nQUAVs, "uav");

	cbUavUav->Checked = true;
	cbUAVtoSesnor->Checked = true;
	tsDrawPoint->Checked = true;

	tsSimulationAreaSize2->Text = "(" + simulationArea->Width + ", " + simulationArea->Height + ")";

	tsQuav->Text = nQUAVs.ToString();
	tsQSensor->Text = nQSensors.ToString();
	tsSpeed->Text = Speed.ToString();

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
		myVants[i]->setMyFirstLocation(myVants[i]->getCenterLocation());
		myVants[i]->setMyTotalDistance(0);
	}

	_updateGrid(qSensors);
	_updateRoutes(-1);

	output->SelectionStart = output->TextLength;
	output->ScrollToCaret();
}

private: System::Void _ResetScenario(int Vants, int Sensors)
{
	tsInfo->Checked = true;
	tsShowRoute->Checked = false;

	cbUAVtoSesnor->Checked = true;
	cbUavUav->Checked = true;
	cbUAVtoServer->Checked = true;
	setNewRWP = true;

	Speed = 2;

	tsSpeed->Text = Speed.ToString();
	nextStepTimer->Interval = tsStepInterval->Value;
	tsqTimeSlots->Text = "10";

	numConRangeV2S->Value = 100;
	numConRangeV2V->Value = 100;
	numConRangeV2Sever->Value = 100;

	tsMobilityModel->Enabled = true;
	tsDrawPoint->Checked = true;

	SystemStopWatch->Reset();
	tsTimer2->Text = SystemStopWatch->Elapsed.ToString();

	tsBroadcastActivate->Checked = false;

	output->Clear();
	output->Text += _getTimeCRLF() + "Reset !";

	nQUAVs = Vants;
	nQSensors = Sensors;

	tsPlay->Checked = false;
	tsPlay->Image = Image::FromFile("Images\\Gplay.png");
	tsPlay->Text = "Play";
	tsDrawPoint->Checked = true;
	tsStandBy->Checked = true;

	//if RESET button is clicked;
	if (nQUAVs == 3 && nQSensors == 6)
		simulator::Size = System::Drawing::Size(1185, 788);

	tsSimulationAreaSize2->Text = "(" + simulationArea->Width + ", " + simulationArea->Height + ")";

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		simulationArea->Controls->Remove(myVants[i]->getPicture());
		simulationArea->Controls->Remove(myVants[i]->getMessageIcon());
		simulationArea->Controls->Remove(myVants[i]->getmyLabel());
	}

	for (unsigned int i = 0; i<qSensors; i++)
	{
		simulationArea->Controls->Remove(mySensors[i]->getPicture());
		simulationArea->Controls->Remove(mySensors[i]->getMessageIcon());
		simulationArea->Controls->Remove(mySensors[i]->getmyLabel());
		dataGridView->Rows->RemoveAt(qSensors - i - 1);
	}

	simulationArea->Controls->Clear();

	qUAVs = 0;
	qSensors = 0;

	nQUAVs = Vants;
	nQSensors = Sensors;

	createNode(nQSensors, "sensor");
	createNode(nQUAVs, "uav");
	createNode(1, "server");

	ss->reset(simulationArea);
	tsUAVSelect->Checked = true;
	tsSensorSelect->Checked = false;
	tsSpeedSelect->Checked = false;
	tsSpeedSelect->Enabled = true;

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
		myVants[i]->setMyFirstLocation(myVants[i]->getCenterLocation());
		myVants[i]->setMyTotalDistance(0);
	}
	if (tsDownCarret->Checked)
	{
		output->SelectionStart = output->TextLength;
		output->ScrollToCaret();
	}

	tsUAVSpeedText->Text = "UAV Speed: " + myVants[0]->getSpeed().ToString("00") + "m/s";
	tsUAVFlyedDistance->Text = "UAV Flyed Dist.: " + myVants[0]->getTotalDistance().ToString("0000") + "m";
	tsUAVHops->Text = "UAV Hops: " + myVants[0]->getHopsCounter().ToString("000");

	_LOGactivate(false);
	splitContainer3->Panel2Collapsed = true;

	_updateGrid(qSensors);
	_updateRoutes(-1);
}

private: System::Void _ResetScenarioForSimulation(int Vants, int Sensors)
{
	tsInfo->Checked = true;
	setNewRWP = true;

	Speed = 2;

	tsSpeed->Text = Speed.ToString();
	tsMobilityModel->Enabled = true;
	tsDrawPoint->Checked = true;
	SystemStopWatch->Reset();
	tsTimer2->Text = SystemStopWatch->Elapsed.ToString();
	nextStepTimer->Interval = tsStepInterval->Value;
	tsqTimeSlots->Text = "10";

	List<Point> saveLocations;
	List<int> saveTimeSlots;

	if (tsLockReset->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			if(mySensors[i]->getMyOriginalTimeSlot() >= 0)
				saveTimeSlots.Add(mySensors[i]->getMyOriginalTimeSlot());
			else
				saveTimeSlots.Add(mySensors[i]->getMyTimeSlot());
			
			saveLocations.Add((Point) mySensors[i]->getLocation());
		}
	}

	nQUAVs = Vants;
	nQSensors = Sensors;

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		simulationArea->Controls->Remove(myVants[i]->getPicture());
		simulationArea->Controls->Remove(myVants[i]->getMessageIcon());
		simulationArea->Controls->Remove(myVants[i]->getmyLabel());
	}

	for (unsigned int i = 0; i<qSensors; i++)
	{
		simulationArea->Controls->Remove(mySensors[i]->getPicture());
		simulationArea->Controls->Remove(mySensors[i]->getMessageIcon());
		simulationArea->Controls->Remove(mySensors[i]->getmyLabel());
		dataGridView->Rows->RemoveAt(qSensors - i - 1);
	}

	simulationArea->Controls->Clear();
	output->Clear();

	qUAVs = 0;
	qSensors = 0;

	nQUAVs = Vants;
	nQSensors = Sensors;

	createNode(nQSensors, "sensor");
	createNode(nQUAVs, "uav");
	createNode(1, "server");

	if (tsLockReset->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			if (saveTimeSlots[i] >= 0)
				dataGridView->Rows[i]->Cells[2]->Value = saveTimeSlots[i].ToString("00");
			else
				dataGridView->Rows[i]->Cells[2]->Value = "";

			mySensors[i]->setXY(saveLocations[i].X, saveLocations[i].Y);
		}
	}

	ss->reset(simulationArea);

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
		myVants[i]->setMyFirstLocation(myVants[i]->getCenterLocation());
		myVants[i]->setMyTotalDistance(0);
	}
	_updateGrid(qSensors);
	_updateRoutes(-1);

	if (tsDownCarret->Checked)
	{
		output->SelectionStart = output->TextLength;
		output->ScrollToCaret();
	}

	_LOGactivate(false);
	splitContainer3->Panel2Collapsed = true;

	tsUAVSpeedText->Text = "UAV Speed: " + myVants[0]->getSpeed().ToString("00") + "m/s";
	tsUAVFlyedDistance->Text = "UAV Flyed Dist.: " + myVants[0]->getTotalDistance().ToString("0000") + "m";
	tsUAVHops->Text = "UAV Hops: " + myVants[0]->getHopsCounter().ToString("000");
}

private: System::Void _ResetScenarioForFinalSimulation(int Vants, int Sensors)
{
	tsInfo->Checked = true;
	setNewRWP = true;

	Speed = 2;

	tsSpeed->Text = Speed.ToString();
	tsMobilityModel->Enabled = true;
	tsDrawPoint->Checked = true;
	SystemStopWatch->Reset();
	tsTimer2->Text = SystemStopWatch->Elapsed.ToString();
	nextStepTimer->Interval = tsStepInterval->Value;
	tsqTimeSlots->Text = "10";

	nQUAVs = Vants;
	nQSensors = Sensors;

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		simulationArea->Controls->Remove(myVants[i]->getPicture());
		simulationArea->Controls->Remove(myVants[i]->getMessageIcon());
		simulationArea->Controls->Remove(myVants[i]->getmyLabel());
	}

	for (unsigned int i = 0; i<qSensors; i++)
	{
		simulationArea->Controls->Remove(mySensors[i]->getPicture());
		simulationArea->Controls->Remove(mySensors[i]->getMessageIcon());
		simulationArea->Controls->Remove(mySensors[i]->getmyLabel());
		dataGridView->Rows->RemoveAt(qSensors - i - 1);
	}

	simulationArea->Controls->Clear();

	output->Clear();

	qUAVs = 0;
	qSensors = 0;

	nQUAVs = Vants;
	nQSensors = Sensors;

	createNode(nQSensors, "sensor");
	createNode(nQUAVs, "uav");
	createNode(1, "server");

	ss->reset(simulationArea);

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
		myVants[i]->setMyFirstLocation(myVants[i]->getCenterLocation());
		myVants[i]->setMyTotalDistance(0);
	}

	_updateGrid(qSensors);
	_updateRoutes(-1);

	if(tsSound->Checked)
		Console::Beep(450, 250);

	if (!tsLOG->Checked)
	{
		tsLOG->Checked = true;
		splitContainer3->Panel2Collapsed = true;
	}

	_simulationPlayButton(false);
}


private: System::Void simulator_ResizeEnd(System::Object^  sender, System::EventArgs^  e)
{
	output->Text += _getTimeCRLF() + "Simulation Area resized to (w: " + simulationArea->Width + " x h: " + simulationArea->Height + ")";
	graphics = simulationArea->CreateGraphics();
	simulationArea->Refresh();
}

private: System::Void cbTrackUAVs_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (cbLog->Checked)
	{
		logPath = "log\\log_" + _getDateTime() + ".csv";
		tw = gcnew StreamWriter(logPath, true);
		output->Text += _getTimeCRLF() + "Log activated. ";
	}
	else
	{
		output->Text += _getTimeCRLF() + "Log deactivated.";
		tw->Flush();
		tw->Close();
		output->Text += _getTimeCRLF() + "Log saved on path " + System::IO::Directory::GetCurrentDirectory() + logPath;
	}
}

private: System::Void _updateLinks(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void _mouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	PictureBox ^ pic = (PictureBox^)sender;

	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		MouseDownLocation = e->Location;
		returnToOldLocation = MouseDownLocation;

		if (_getTypeFromPicture(pic) == "UAV")
		{
			if (myVants[_getIDFromPicture(pic)]->getSpeed() != 0)
			{
				myVants[_getIDFromPicture(pic)]->setOldSpeed(myVants[_getIDFromPicture(pic)]->getSpeed());
				myVants[_getIDFromPicture(pic)]->setMySpeed(0);
			}
			else
			{
				myVants[_getIDFromPicture(pic)]->setOldSpeed(1);
				myVants[_getIDFromPicture(pic)]->setMySpeed(0);
			}
		}
	}

	if (e->Button == System::Windows::Forms::MouseButtons::Right && _getTypeFromPicture(pic) == "Sensor")
	{
		String ^ type = _getTypeFromPicture(pic);
		Sensor ^ s = mySensors[_getIDFromPicture(pic)];

		if (type == "Sensor" && !s->getMyState())
			s->setMyState(true);
		else
			s->setMyState(false);
	}
}

private: System::Void _mouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	PictureBox ^ pic = (PictureBox^)sender;

	if (e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		pic->Left = e->X + pic->Left - MouseDownLocation.X;
		pic->Top = e->Y + pic->Top - MouseDownLocation.Y;
	}

	//update Message큦 Icon on UAVs/Sensor picture while drag and drop them;
	if (_getTypeFromPicture(pic) == "UAV" && myVants[_getIDFromPicture(pic)]->hasMessage())
		myVants[_getIDFromPicture(pic)]->showMessage(true);

	if (_getTypeFromPicture(pic) == "Sensor" && mySensors[_getIDFromPicture(pic)]->hasMessage())
		mySensors[_getIDFromPicture(pic)]->getMessageIcon()->Location = System::Drawing::Point(mySensors[_getIDFromPicture(pic)]->getX() + 2, mySensors[_getIDFromPicture(pic)]->getY() + 17);

	if (_getTypeFromPicture(pic) == "Server" && ss->hasMessage())
		ss->showMessage(true);

	if (tsInfo->Checked && _getTypeFromPicture(pic) == "UAV")
		myVants[_getIDFromPicture(pic)]->setLabel(true);

	if (_getTypeFromPicture(pic) == "Sensor")
		mySensors[_getIDFromPicture(pic)]->setLabel(true);

	if (tsGridSensor->Checked)
		_updateGrid(qSensors);

	if (!tsPlay->Checked)
		simulationArea->Refresh();
}

private: System::Void _mouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	PictureBox ^ pic = (PictureBox^)sender;

	if (e->Button == System::Windows::Forms::MouseButtons::Left)
		output->Text += _getTimeCRLF() + _getTypeFromPicture(pic) + " ID[" + _getIDFromPicture(pic) + "] moved to (" + pic->Location.X + ", " + pic->Location.Y + ")";

	if (!tsPlay->Checked)
		simulationArea->Refresh();

	if (_getTypeFromPicture(pic) == "UAV")
		myVants[_getIDFromPicture(pic)]->setMySpeed(myVants[_getIDFromPicture(pic)]->getOldSpeed());

	if (tsShowRoute->Checked)
		_updateRoutes(-1);
	
	if (_getTypeFromPicture(pic) == "Sensor" && e->Button == System::Windows::Forms::MouseButtons::Left)
	{
		if (tsGridSensor->Checked)
		{
			Point p = pic->Location;
			mySensors[_getIDFromPicture(pic)]->setXY(_getNearestGridLocation(p).X, _getNearestGridLocation(p).Y);
			_updateGrid(qSensors);
		}
		else
			mySensors[_getIDFromPicture(pic)]->setOnGrid(false);

		if (tsShowCluster->Checked)
			_updateClusters(tsShowCluster->Checked);
	}
}

private: System::Void createNode(unsigned int q, String ^ type)
{
	if (type == "uav")
	{
		if (qUAVs<q)
		{
			Random rand;

			for (unsigned int i = qUAVs; i < q; i++)
			{
				myVants[i] = gcnew Vant(i, simulationArea);
				myVants[i]->getPicture()->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseDown);
				myVants[i]->getPicture()->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseMove);
				myVants[i]->getPicture()->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseUp);
				myVants[i]->getPicture()->MouseHover += gcnew System::EventHandler(this, &simulator::_mouseHover);
				myVants[i]->getMessageIcon()->Click += gcnew System::EventHandler(this, &simulator::_messageClick);
				myVants[i]->getPicture()->Cursor = System::Windows::Forms::Cursors::Hand;
				
				if(tsDebug->Checked)
					output->Text += _getTimeCRLF() + " - UAV ID[" + i + "] placed at coordinates (" + myVants[i]->getX() + ", " + myVants[i]->getY() + ")";

				myVants[i]->setMySpeed(Speed);

				if (tsPlay->Checked)
					myVants[i]->getMyStopWatch()->Start();

				myVants[i]->setRandDirection(MAX_STEPS, false);
				myVants[i]->getPicture()->BringToFront();
				myVants[i]->getMessageIcon()->BringToFront();

				Thread::Sleep(25);
			}
		}
		else
		{
			for (unsigned int i = qUAVs - 1; i >= q; i--)
			{
				simulationArea->Controls->Remove(myVants[i]->getPicture());
				simulationArea->Controls->Remove(myVants[i]->getMessageIcon());
				simulationArea->Controls->Remove(myVants[i]->getmyLabel());

				if (tsDebug->Checked)
					output->Text += _getTimeCRLF() + " - UAV ID[" + i + "] removed at coordinates (" + myVants[i]->getX() + ", " + myVants[i]->getY() + ")" ;
			}
		}

		qUAVs = nQUAVs;
		tsQuav->Text = qUAVs.ToString();

	} //end "uav";

	if (type == "sensor")
	{
		if (qSensors < q)
		{
			for (unsigned int i = qSensors; i < q; i++)
			{
				if (tsGridSensor->Checked)
				{
					_updateGrid(i);
					mySensors[i] = gcnew Sensor(i, simulationArea, _getGridPoint());
				}
				else
					mySensors[i] = gcnew Sensor(i, simulationArea);

				mySensors[i]->getPicture()->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseDown);
				mySensors[i]->getPicture()->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseMove);
				mySensors[i]->getPicture()->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseUp);
				mySensors[i]->getPicture()->MouseHover += gcnew System::EventHandler(this, &simulator::_mouseHover);
				mySensors[i]->getMessageIcon()->Click += gcnew System::EventHandler(this, &simulator::_messageClick);
				mySensors[i]->getPicture()->Cursor = System::Windows::Forms::Cursors::Hand;
				dataGridView->Rows->Add(mySensors[i]->getMyName(), "", "");

				Thread::Sleep(25);
			}
		}
		else
		{
			for (unsigned int i = qSensors - 1; i >= q; i--)
			{
				simulationArea->Controls->Remove(mySensors[i]->getPicture());
				simulationArea->Controls->Remove(mySensors[i]->getMessageIcon());
				simulationArea->Controls->Remove(mySensors[i]->getmyLabel());
				dataGridView->Rows->RemoveAt(i);
			}
		}

		qSensors = nQSensors;
		tsQSensor->Text = qSensors.ToString();

	} // end "sensors";

	if (type == "server")
	{
		ss = gcnew server(simulationArea);
		ss->getPicture()->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseDown);
		ss->getPicture()->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseMove);
		ss->getPicture()->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &simulator::_mouseUp);
		ss->getPicture()->MouseHover += gcnew System::EventHandler(this, &simulator::_mouseHover);
		ss->getPicture()->Cursor = System::Windows::Forms::Cursors::Hand;
		ss->getMessageIcon()->Click += gcnew System::EventHandler(this, &simulator::_messageClick);
		
		Thread::Sleep(25);
	}

	simulationArea->Refresh();
}

private: System::Void timerBDtotalTime_Tick(System::Object^  sender, System::EventArgs^  e)
{
}

private: System::Void simulator_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	tsMobilityModel->Enabled = true;
	SystemStopWatch->Stop();
	output->Text += _getTimeCRLF() + "Simulation time: " + SystemStopWatch->Elapsed.ToString();
	output->Text += _getTimeCRLF() + "Simulation stopped";
}

private: System::Void refreshPanel_Tick(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void _messageClick(System::Object^  sender, System::EventArgs^  e)
{
	PictureBox ^ pic = (PictureBox^)sender;
	int index = _getIDFromPicture(pic);
	String ^ type = _getTypeFromPicture(pic);

	if (type == "Message UAV")
	{
		if (myVants[index]->getMyMessages() != "")
		{
			output->Text += _getTimeCRLF() + "UAV ID[" + index.ToString() + "]: " + myVants[index]->getMyMessages();
			output->Text += _getTimeCRLF() + "UAV ID[" + index.ToString() + "]: " + myVants[index]->countMessages() + " Messages received";
		}
		else
			output->Text += _getTimeCRLF() + "UAV ID[" + index.ToString() + "]: empty";
	}

	if (type == "Message Sensor")
	{
		if (mySensors[index]->getMyMessages() != "")
		{
			output->Text += _getTimeCRLF() + "Sensor ID[" + index.ToString() + "]:" + mySensors[index]->getMyMessages();
		}
		else
			output->Text += _getTimeCRLF() + "sensor ID[" + index.ToString() + "]: empty";
	}

	if (type == "Message Server")
	{
		if (ss->getMyMessages() != "")
		{
			output->Text += _getTimeCRLF() + "Server ID[0]: " + ss->getMyMessages();
			output->Text += _getTimeCRLF() + "Server ID[0]: " + ss->countMessages() + " Messages received";
		}
		else
			output->Text += _getTimeCRLF() + "Server ID[0]: empty";
	}
}

private: System::Void tsInfo_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsInfo->Checked)
	{
		for (unsigned int i = 0; i < qUAVs; i++)
			myVants[i]->setLabel(true);

		for (unsigned int i = 0; i < qSensors; i++)
			mySensors[i]->setLabel(true);

		output->Text += _getTimeCRLF() + "Show Info enabled";
		ss->setLabel(true);
	}
	else
	{
		for (unsigned int i = 0; i < qUAVs; i++)
			myVants[i]->setLabel(false);

		for (unsigned int i = 0; i < qSensors; i++)
			mySensors[i]->setLabel(false);

		output->Text += _getTimeCRLF() + "Show Info disabled";
		ss->setLabel(false);
	}

	simulationArea->Refresh();
}

private: System::Void tsTrackUAVs_Click(System::Object^  sender, System::EventArgs^  e)
{
}

private: System::Void output_TextChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	if (tsDownCarret->Checked)
	{
		output->SelectionStart = output->TextLength;
		output->ScrollToCaret();
	}
}

private: System::Void tsRandSpeed_Click(System::Object^  sender, System::EventArgs^  e)
{
}

private: System::Void simulationArea_Resize(System::Object^  sender, System::EventArgs^  e)
{
	tsSimulationAreaSize2->Text = "(" + simulationArea->ClientRectangle.Width + ", " + simulationArea->ClientRectangle.Height + ")";

	for (unsigned int i = 0; i<qUAVs; i++)
	{
		v = myVants[i];

		if (v->getX() > simulationArea->Width - v->getPicture()->Width)
			v->setXY(simulationArea->Width - v->getSize()->Width, v->getY());

		if (v->getY() > simulationArea->Height - v->getPicture()->Size.Height)
			v->setXY(v->getX(), simulationArea->Height - v->getSize()->Height);
	}

	for (unsigned int i = 0; i<qSensors; i++)
	{
		s = mySensors[i];

		if (s->getX() > simulationArea->Width - s->getPicture()->Width)
			s->setXY(simulationArea->Width - s->getSize()->Width, s->getY());

		if (s->getY() > simulationArea->Height - s->getPicture()->Size.Height)
			s->setXY(s->getX(), simulationArea->Height - s->getSize()->Height);
	}

	if (ss->getX() > simulationArea->Width - ss->getPicture()->Width)
		ss->setXY(simulationArea->Width - ss->getSize()->Width, ss->getY());

	if (ss->getY() > simulationArea->Height - ss->getPicture()->Size.Height)
		ss->setXY(ss->getX(), simulationArea->Height - ss->getSize()->Height);
}

private: System::Void tsUAVSelect_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsSensorSelect->Checked)
		tsSensorSelect->Checked = false;

	if (tsSpeedSelect->Checked)
		tsSpeedSelect->Checked = false;

}
private: System::Void tsSensorSelect_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsUAVSelect->Checked)
		tsUAVSelect->Checked = false;

	if (tsSpeedSelect->Checked)
		tsSpeedSelect->Checked = false;

}

private: System::Void tsSpeedSelect_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsUAVSelect->Checked)
		tsUAVSelect->Checked = false;

	if (tsSensorSelect->Checked)
		tsSensorSelect->Checked = false;
}

private: System::Void tsClearOutput_Click_1(System::Object^  sender, System::EventArgs^  e) 
{
	output->Clear();
	output->Text += _getTimeCRLF() + "Output text cleared ... ";
}


private: System::Void simulator_Resize(System::Object^  sender, System::EventArgs^  e) 
{
	graphics = simulationArea->CreateGraphics();
	_updateGrid(qSensors);
	simulationArea->Refresh();
}

private: System::Void tsDown_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsUAVSelect->Checked)
	{
		if (qUAVs - 1 > 0)
		{
			nQUAVs = qUAVs - 1;
			createNode(nQUAVs, "uav");
		}
	}

	if (tsSensorSelect->Checked)
	{
		if (qSensors - 1 > 0)
		{
			nQSensors = qSensors - 1;
			createNode(nQSensors, "sensor");
		}
		else
		{
			output->Text += _getTimeCRLF() + "Select at least ONE sensor node ... ";
		}
	}

	if (tsSpeedSelect->Checked)
	{
		if (Speed > 0)
		{
			Speed--;

			for (unsigned int i = 0; i < qUAVs; i++)
			{
				v = myVants[i];
				v->resetSpeed();
				v->setMySpeed(Speed);
				output->Text += _getTimeCRLF() + "UAV[" + i + "] set with Speed: " + v->getSpeed();
			}

			tsSpeed->Text = Speed.ToString();
		}
	}

	_updateRoutes(-1);

	if (!tsSensorSelect->Checked && !tsUAVSelect->Checked && !tsSpeedSelect->Checked)
		output->Text += _getTimeCRLF() + "Select at least an UAV, Sensor or Speed ...";
}

private: System::Void tsUp_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsUAVSelect->Checked)
	{
		if (qUAVs < MAX_UAV)
		{
			nQUAVs = qUAVs + 1;
			createNode(nQUAVs, "uav");

			for (unsigned int i = 0; i<qUAVs; i++)
			{
				myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
				myVants[i]->setMyTotalDistance(0);
			}
		}
	}

	if (tsSensorSelect->Checked)
	{
		if(!tsGridSensor->Checked)
		{
			if (qSensors<MAX_SENSOR)
			{
				nQSensors = qSensors + 1;
				createNode(nQSensors, "sensor");
			}
		}
		else
		{
			if (qSensors < myGridLocation.Count && qSensors < MAX_SENSOR)
			{
				nQSensors = qSensors + 1;
				createNode(nQSensors, "sensor");
			}

			_updateGrid(qSensors);
		}
	}

	if (tsSpeedSelect->Checked)
	{
		if (Speed < MAX_SPEED)
		{
			Speed++;

			for (unsigned int i = 0; i < qUAVs; i++)
			{
				v = myVants[i];
				v->resetSpeed();
				v->setMySpeed(Speed);
				output->Text += _getTimeCRLF() + "UAV[" + i + "] set with Speed: " + v->getSpeed();
			}

			tsSpeed->Text = Speed.ToString();
		}
	}

	_updateRoutes(-1);

	if (!tsSensorSelect->Checked && !tsUAVSelect->Checked && !tsSpeedSelect->Checked)
		output->Text += _getTimeCRLF() + "Select at least an UAV, Sensor or Speed ...";
}



private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e)
{
	output->Clear();
	output->Text += _getTimeCRLF() + "Output text cleared ... ";
}

private: System::Void ts2Copy_Click(System::Object^  sender, System::EventArgs^  e)
{
	output->SelectAll();
	output->Copy();
	output->Text += _getTimeCRLF() + "Output text copied successfully to clipboard ... ";
}

private: System::Void cbUavUav_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	if (cbUavUav->Checked)
	{
		output->Text += _getTimeCRLF() + "Connection between UAV to UAV enabled ...";
	}
	else
	{
		for (unsigned int i = 0; i<qUAVs; i++)
		{
			v1 = myVants[i];

			for (unsigned int j = 0; j < qUAVs; j++)
			{
				v1->clearConnection(myVants[j]);
			}
		}

		output->Text += _getTimeCRLF() + "Connection between UAV to UAV disabled ...";
	}

	simulationArea->Refresh();

}

private: System::Void cbUAVtoSesnor_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	if (cbUAVtoSesnor->Checked)
	{
		output->Text += _getTimeCRLF() + "Connection between UAV and Sensor enabled ...";
	}
	else
	{
		for (unsigned int i = 0; i<qSensors; i++)
		{
			s = mySensors[i];

			for (unsigned int j = 0; j<qUAVs; j++)
			{
				myVants[j]->clearConnection(s);
			}
		}

		output->Text += _getTimeCRLF() + "Connection between UAV and Sensor disabled ...";
	}

	simulationArea->Refresh();

}

private: System::Void cbUAVtoServer_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (cbUAVtoServer->Checked)
		output->Text += _getTimeCRLF() + "Connection between UAV and Server enabled ...";
	else
		output->Text += _getTimeCRLF() + "Connection between UAV and Server disabled ...";

	simulationArea->Refresh();
}

private: System::Void numConRangeV2V_ValueChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	output->Text += _getTimeCRLF() + "Range UAV-UAV changed to: " + numConRangeV2V->Value.ToString();
	simulationArea->Refresh();
}

private: System::Void numConRangeV2S_ValueChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	output->Text += _getTimeCRLF() + "Range UAV-Sensor changed to: " + numConRangeV2S->Value.ToString();
	
	if (tsGridSensor->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			_updateGrid(qSensors);
			s = mySensors[i];
			s->setXY(_getNearestGridLocation(s->getLocation()).X, _getNearestGridLocation(s->getLocation()).Y);
		}
	}

	_updateRoutes(-1);
}

private: System::Void tsMobilityModel_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	for (unsigned int i = 0; i < qUAVs; i++)
	{
		myVants[i]->setInit(true);
		myVants[i]->setMyRWP(nullptr);
	}

	Random ^ rand;

	switch (tsMobilityModel->SelectedIndex)
	{
		case 0: //Random Walk
			setNewRWP = true;
			break;

		case 1: //Random Waypoint
			setNewRWP = true;
			break;

		case 2: //Sensor NearPoint
			setNewRWP = true;
			break;

		case 3: //Scanning;
			setNewRWP = true;
			break;

		case 4: //Circular model;
			setNewRWP = true;
			break;

		case 5://Infinite loop
			setNewRWP = true;
			break;

		case 6: //Joystick
			setNewRWP = true;
			break;

		case 7: //Route UAV[0]

			rand = gcnew Random();
			setNewRWP = true;
			break;

		case 8: //Gauss-Markov
			setNewRWP = true;
			break;

		case 9://TimerWalk
			setNewRWP = true;
			break;

		case 10: //pursue
			rand = gcnew Random();
			PursueReference = rand->Next(Convert::ToInt32(qUAVs));
			output->Text += _getTimeCRLF() + "ID[" + PursueReference + "] as reference ";
			setNewRWP = true;
			break;
		}
}

private: System::Void _mouseHover(System::Object^ sender, System::EventArgs^  e)
{
	PictureBox ^ pic = (PictureBox^)sender;
	int index = _getIDFromPicture(pic);
	String ^ type = _getTypeFromPicture(pic);
	String ^ str;
	Vant ^ v;
	Sensor ^ s;

	if (type == "UAV")
		v = myVants[index];

	if (type == "Sensor")
		s = mySensors[index];

	str = type + " ID[" + index.ToString() + "]" + CRLF;
	str += "Coord: (" + (pic->Location.X + (pic->Width / 2)) + ", " + (pic->Location.Y + (pic->Height / 2)) + ")" + CRLF;

	if (type == "UAV")
	{
		if (tsShowRoute->Checked)
		{
			str += "MyRoute: " + v->getMyName() + " ";

			for (unsigned int i = 0; i < _getActiveSensors(); i++)
				str += v->getRoute(i)->getMyName() + " ";

			str += CRLF;
		}

		str += "Flyed Distance: " + v->getTotalDistance().ToString("0000.00") + CRLF;
		str += "Speed: " + v->getSpeed() + CRLF;
		str += "Fly Time: " + v->getFlyTime() + "ms" + CRLF;

		if (v->getFlyTime() > 1000)
			str += "Av. Speed: " + v->getMyRealSpeed().ToString("000.00") + CRLF;

		str += "Messages: " + v->countMessages() + CRLF;
		str += "Connected with: ";

		for (unsigned int i = 0; i < qUAVs; i++)
			if (v->isConnectedWith(i, "UAV"))
				str += "U" + i + " ";

		for (unsigned int i = 0; i < qSensors; i++)
			if (v->isConnectedWith(i, "Sensor"))
				str += "S" + i + " ";

		if (v->isServerConnected())
			str += "Deposit ";
	}

	if (type == "Sensor")
	{
		str += "State: ";

		if (s->getMyState())
		{
			str += "Broadcasting ... " + CRLF;
		}
		else
			str += "Sleeping ... " + CRLF;

		str += "Connected with: ";

		if (type == "Sensor")
		{
			for (unsigned int i = 0; i < qUAVs; i++)
				if (s->isConnectedWith(i))
					str += "U" + i + " ";
		}

		str += "\r\nCluster: " + s->getMyCluster();
		str += "\r\nMissed UAV's: " + s->getLostUAVcounter();
		str += "\r\nmyDelay: " + s->getMyDelay() + "ms";
		str += "\r\nisDiscovered: " + s->getDiscovered();
	}

	if (type == "Server")
	{
		str += "Connections: " + ss->getMyCounter() + CRLF;
		str += "Messages: " + ss->countMessages() + CRLF;
		str += "Connected with: ";

		for (unsigned int i = 0; i < qUAVs; i++)
			if (ss->isConnectedWith(i))
				str += "U" + i + " ";
	}

	if (tsDebug->Checked)
	{
		str += "\r\nDistance from: " + CRLF;

		if (type == "UAV")
		{
			for (unsigned int i = 0; i < qUAVs; i++)
				if (i != index)
					str += "U" + i + "=" + Math::Round(v->getDistanceFrom(myVants[i]->getCenterLocation())).ToString() + " ";

			for (unsigned int i = 0; i < qSensors; i++)
				str += "S" + i + "=" + Math::Round(v->getDistanceFrom(mySensors[i]->getCenterLocation())).ToString() + " ";

			str += "Deposit: " + v->getDistanceFrom(ss->getCenterLocation()).ToString(".00");
			str += "\r\nmyOldSpeed: " + v->getOldSpeed();
			str += "\r\nmySteps: " + v->getMySteps();
			str += "\r\nUAVConnected: " + v->isUAVConnected();
			str += "\r\nSensorConnect: " + v->isSensorConnected();
			str += "\r\nLastConectionID: " + v->getlastMsgFrom();
			str += "\r\nmyName: " + v->getMyName();
			str += "\r\nmyCounter: " + v->getMyCounter();
			str += "\r\nwhereIamNow: " + v->getWhereIamNow();
			str += "\r\nFirstLocation: " + _getStringFromCoordinates(v->getMyFirstLocation());
			str += "\r\nActualTimeSlot: " + v->getActualTimeSlot();
			str += "\r\nHasMessage: " + v->hasMessage() + CRLF;
		}

		if (type == "Sensor")
		{
			for (unsigned int i = 0; i < qSensors; i++)
				if (i != index)
					str += "S" + i + "=" + Math::Round(s->getDistanceFrom(mySensors[i]->getCenterLocation())).ToString() + " ";

			for (unsigned int i = 0; i < qUAVs; i++)
				str += "U" + i + "=" + Math::Round(s->getDistanceFrom(myVants[i]->getCenterLocation())).ToString() + " ";

			str += "\r\nLastConectionID: " + s->getLastMsgFrom();
			str += "\r\nmyName: " + s->getMyName();
			str += "\r\nHasMessage: " + s->hasMessage();
			str += "\r\nVisited: " + s->getVisit();
		}
	}

	ttShowInfo->Show(str, pic);
}

private: System::Void broadcastTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	broadcastTime->Maximum = SleepingTime->Value;

	if (broadcastTime->Value >= SleepingTime->Value)
		broadcastTime->Maximum = SleepingTime->Value;
}

private: System::Void SleepingTime_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	broadcastTime->Maximum = SleepingTime->Value;

	if (SleepingTime->Value < broadcastTime->Value)
		broadcastTime->Value = SleepingTime->Value;
}

private: System::Void numV2VmaxConn_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void numV2SmaxConn_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void numU2DmaxConn_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void tsScen2x10_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(2, 10);
}
private: System::Void tsScen3x12_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(3, 12);
}
private: System::Void tsScen4x12_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(4, 12);
}
private: System::Void tsScen3x15_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(3, 15);
}
private: System::Void tsScen5x15_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(5, 30);
}

private: System::Void tsBreset_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenarioForSimulation(qUAVs, qSensors);
}

private: System::Void testScenario1X7ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	_ResetScenario(1, 7);
	simulator::Size = System::Drawing::Size(1185, 990);
	numConRangeV2S->Value = 75;

	mySensors[0]->setXY(39, 206);
	mySensors[1]->setXY(204, 259);
	mySensors[2]->setXY(488, 19);
	mySensors[3]->setXY(696, 105);
	mySensors[4]->setXY(812, 277);
	mySensors[5]->setXY(613, 632);
	mySensors[6]->setXY(399, 600);
	myVants[0]->setXY(3, 7);
}

private: System::Void tsDrawCircle_Click(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void tsMobilityModel_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void tsIUAVposition_Click(System::Object^  sender, System::EventArgs^  e)
{
	for (unsigned int i = 0; i<qUAVs; i++)
	{
		myVants[i]->setXY(ss->getCenterLocation().X - 25, ss->getCenterLocation().Y - (i + 1) * 35);
		myVants[i]->setMyTotalDistance(0);
	}

	_updateRoutes(-2);
}

private: System::Void _updateRoutes(int counter)
{
	unsigned int loopCounter;
	double bestDistance;
	double blueDistance;
	double redDistance;
	double greenDistance;
	double cyanDistance;

	v = myVants[0];

	for (unsigned int i = 0; i < qSensors; i++)
		mySensors[i]->setVisit(false);

	loopCounter = 0;
	redDistance = 0;
	blueDistance = 0;
	greenDistance = 0;
	cyanDistance = 0;

	bestDistance = 99999;

	while (loopCounter < _getActiveSensors())
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			s = mySensors[i];

			if (s->getMyState())
			{
				if (loopCounter == 0)
				{
					if (v->getDistanceFrom(s->getCenterLocation()) < bestDistance && !s->getVisit())
					{
						bestDistance = v->getDistanceFrom(s->getCenterLocation());
						v->insertRoute(s, loopCounter);
					}
				}
				else
				{
					if ((s->getID() != v->getRoute(loopCounter - 1)->getID()) && !s->getVisit())
					{
						if (v->getRoute(loopCounter - 1)->getDistanceFrom(s->getCenterLocation()) < bestDistance)
						{
							bestDistance = v->getRoute(loopCounter - 1)->getDistanceFrom(s->getCenterLocation());
							v->insertRoute(s, loopCounter);
						}
					}
				}
			}
		}

		if (loopCounter == 0)
		{
			v->setNewTarget(loopCounter, _getNearestPointFromTo(v->getMyFirstLocation(), v->getRoute(loopCounter)->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value)));
			redDistance = v->getDistanceFrom(v->getRoute(loopCounter)->getCenterLocation());
			greenDistance = v->getDistanceFrom(v->getTarget(loopCounter));
		}
		else
		{
			v->setNewTarget(loopCounter, _getNearestPointFromTo(v->getTarget(loopCounter - 1), v->getRoute(loopCounter)->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value)));
			redDistance += _getDistanceFrom(v->getRoute(loopCounter - 1)->getCenterLocation(), v->getRoute(loopCounter)->getCenterLocation());
			greenDistance += _getDistanceFrom(v->getTarget(loopCounter - 1), v->getTarget(loopCounter));

			if (loopCounter == (_getActiveSensors() - 1) && tsClosedCircuit->Checked)
			{
				redDistance += _getDistanceFrom(v->getRoute(loopCounter)->getCenterLocation(), v->getMyFirstLocation());
				greenDistance += _getDistanceFrom(v->getTarget(loopCounter), v->getMyFirstLocation());
			}
		}

		v->getRoute(loopCounter)->setVisit(true);
		bestDistance = 99999;
		loopCounter++;
	}

	myVants[0]->setMyCounter(0);

	for (unsigned int i = 0; i < _getActiveSensors(); i++)
	{
		v = myVants[0];

		if (i == 0)
		{
			if (_getDistanceFrom(v->getCenterLocation(), v->getRoute(i)->getCenterLocation()) > Convert::ToInt32(numConRangeV2S->Value))
			{
				if (FindTangents(v->getRoute(i)->getCenterLocation(), (float)(numConRangeV2S->Value), v->getCenterLocation()))
				{
					if (_getDistanceFrom(tangent1, v->getRoute(i + 1)->getCenterLocation()) < _getDistanceFrom(tangent2, v->getRoute(i + 1)->getCenterLocation()))
						v->setFly(tangent1);
					else
						v->setFly(tangent2);
				}
			}
			else
			{
				v->setFly(v->getCenterLocation());
			}

			blueDistance += _getDistanceFrom(v->getCenterLocation(), v->getFly(i));
		}
		else
		{
			if (i < _getActiveSensors() - 1)
			{
				Point midPoint = Point((v->getRoute(i)->getCenterLocation().X + v->getRoute(i + 1)->getCenterLocation().X) / 2,
					(v->getRoute(i)->getCenterLocation().Y + v->getRoute(i + 1)->getCenterLocation().Y) / 2);

				if (FindLineCircleIntersections(v->getRoute(i)->getCenterLocation(), Convert::ToInt32(numConRangeV2S->Value), (Point)v->getRoute(i - 1)->getCenterLocation(), midPoint) == 2)
					v->setFly(intersection1);
				else
				{
					if (FindTangents(v->getRoute(i)->getCenterLocation(), (float)(numConRangeV2S->Value), (Point)v->getRoute(i - 1)->getCenterLocation()))
					{
						if (_getDistanceFrom(tangent1, v->getRoute(i + 1)->getCenterLocation()) < _getDistanceFrom(tangent2, v->getRoute(i + 1)->getCenterLocation()))
							v->setFly(tangent1);
						else
							v->setFly(tangent2);
					}
				}
			}
			else
				v->setFly(v->getRoute(i)->getCenterLocation());

			if (tsClosedCircuit->Checked && i == (_getActiveSensors() -1))
				blueDistance += _getDistanceFrom(v->getFly(i), v->getMyFirstLocation());

			blueDistance += _getDistanceFrom(v->getFly(i), v->getFly(i - 1));
		}
	}

	myVants[0]->setMyCounter(0);

	v = myVants[0];

	for (unsigned int i = 0; i < _getActiveSensors(); i++)
	{
		if (i == 0)
		{
			if (_getDistanceFrom(v->getMyFirstLocation(), v->getFly(i + 1)) <= _getDistanceFrom(v->getMyFirstLocation(), v->getTarget(i + 1)))
				v->setHibridFly(v->getFly(i));
			else
				v->setHibridFly(v->getTarget(i));

			cyanDistance += _getDistanceFrom(v->getMyFirstLocation(), v->getHibridFly(i));

		}
		else
		{
			if (i < _getActiveSensors() - 1)
			{
				if (_getDistanceFrom(v->getFly(i), v->getFly(i + 1)) <= _getDistanceFrom(v->getTarget(i), v->getTarget(i + 1)))
					v->setHibridFly(v->getFly(i));
				else
					v->setHibridFly(v->getTarget(i));
			}
			else
			{
				if (_getDistanceFrom(v->getHibridFly(i - 1), v->getFly(i)) >= _getDistanceFrom(v->getHibridFly(i - 1), v->getTarget(i)))
					v->setHibridFly(v->getTarget(i));
				else
					v->setHibridFly(v->getFly(i));
			}

			if (tsClosedCircuit->Checked && i == (_getActiveSensors() - 1))
				cyanDistance += _getDistanceFrom(v->getHibridFly(i), v->getMyFirstLocation());

			cyanDistance += _getDistanceFrom(v->getHibridFly(i - 1), v->getHibridFly(i));
		}
	}

	output->Text += "\r\n";

	if (counter >= -1)
	{
		if (counter >= 0)
			output->Text += _getTimeCRLF() + "### Simulation: " + counter;
		else
			output->Text += _getTimeCRLF() + "### Simulation";

		output->Text += _getTimeCRLF() + "### MyRoute: " + v->getMyName() + " ";

		for (unsigned int i = 0; i < _getActiveSensors(); i++)
		{
			output->Text += v->getRoute(i)->getMyName() + " ";

			if (tsClosedCircuit->Checked && i == _getActiveSensors() -1)
				output->Text += "U0";
		}

		output->Text += _getTimeCRLF() + "### Red Distance  : " + redDistance.ToString(".00");
		output->Text += _getTimeCRLF() + "### Green Distance: " + greenDistance.ToString(".00");
		output->Text += _getTimeCRLF() + "### Blue Distance : " + blueDistance.ToString(".00");
		output->Text += _getTimeCRLF() + "### Cyan Distance : " + cyanDistance.ToString(".00");
		output->Text += _getTimeCRLF() + "### Sensor Range  : " + Convert::ToInt32(numConRangeV2S->Value);
		output->Text += _getTimeCRLF() + "### Total Sensors : " + qSensors + CRLF;
	}

	v = myVants[0];
	v->clearRouteList();

	JustID ^ rr = gcnew JustID();

	v->addRouteList(v->getMyFirstLocation(), qSensors);

	for (unsigned int i = 0; i < _getActiveSensors(); i++)
	{
		rr->setMyID(v->getRoute(i)->getID());

		if (tsRedRoute->Checked)
			rr->setMyLocation(v->getRoute(i)->getCenterLocation());

		if (tsGreenRoute->Checked)
			rr->setMyLocation(v->getTarget(i));

		if (tsBlueRoute->Checked)
			rr->setMyLocation(v->getFly(i));

		if (tsCyanRoute->Checked)
			rr->setMyLocation(v->getHibridFly(i));

		v->addRouteList(rr->getMyLocation(), rr->getMyID());
	}

	for (unsigned int i = 0; i < qUAVs; i++)
	{
		if (tsRedRoute->Checked)
			myVants[i]->setRouteTotalDistance(redDistance);

		if (tsGreenRoute->Checked)
			myVants[i]->setRouteTotalDistance(greenDistance);

		if (tsBlueRoute->Checked)
			myVants[i]->setRouteTotalDistance(blueDistance);

		if (tsCyanRoute->Checked)
			myVants[i]->setRouteTotalDistance(cyanDistance);
	}

	if(tsShowCluster->Checked)
		_updateClusters(tsShowCluster->Checked);

	simulationArea->Refresh();
}


private: System::Void bRunSimulation_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (cbLog->Checked)
	{
		tw = gcnew StreamWriter("log\\Simulation_" + _getDateTime() + "_S" + qSensors.ToString() + "_R" + numConRangeV2S->Value.ToString() + ".csv", true);

		toLog = "Simulation;"
			+ "fromRED;"
			+ "fromRED(X);"
			+ "fromRED(Y);"
			+ "to; "
			+ "toRED(X);"
			+ "toRED(Y); "
			+ "fromGREEN(X); "
			+ "fromGREEN(Y); "
			+ "toGREEN(X); "
			+ "toGREEN(Y);"
			+ "fromBlue(X);"
			+ "fromBlue(Y);"
			+ "toBlue(X);"
			+ "toBlue(Y);"
			+ "fromCyan(X);"
			+ "fromCyan(Y);"
			+ "toCyan(X);"
			+ "toCyan(Y);"
			+ "RedDistance;"
			+ "GreenDistance;"
			+ "BlueDistance;"
			+ "CyanDistance;"
			+ "SensorRange;"
			+ "QtySensor;"
			+ "whoWins;";     

		tw->WriteLine(toLog);
		output->Text += _getTimeCRLF() + "Log activated. ";
	}

	for (int simulationNumber = 0; simulationNumber < Convert::ToInt32(numQtySimulation->Value); simulationNumber++)
	{
		_updateRoutes(simulationNumber);

		v = myVants[0];
		v->setMyCounter(0);

		int redDistance = 0;
		int greenDistance = 0;
		int blueDistance = 0;
		int cyanDistance = 0;

		for (unsigned int i = 1; i < _getActiveSensors(); i++)
		{
			if (i == 1)
			{
				redDistance += _getDistanceFrom(v->getMyFirstLocation(), v->getRoute(i - 1)->getCenterLocation());
				greenDistance += _getDistanceFrom(v->getMyFirstLocation(), v->getTarget(i - 1));
				blueDistance += _getDistanceFrom(v->getMyFirstLocation(), v->getFly(i - 1));
				cyanDistance += _getDistanceFrom(v->getMyFirstLocation(), v->getHibridFly(i - 1));

				toLog = simulationNumber + ";" + v->getMyName() + _getStringFromCoordinatesToLog(v->getCenterLocation())
					+ v->getRoute(i - 1)->getMyName() + _getStringFromCoordinatesToLog2(v->getRoute(i - 1)->getCenterLocation())
					+ _getStringFromCoordinatesToLog2(v->getCenterLocation()) + _getStringFromCoordinatesToLog2(v->getTarget(i - 1))
					+ _getStringFromCoordinatesToLog2(v->getCenterLocation()) + _getStringFromCoordinatesToLog2(v->getFly(i - 1))
					+ _getStringFromCoordinatesToLog2(v->getCenterLocation()) + _getStringFromCoordinatesToLog2(v->getHibridFly(i - 1)) + ";";

				if (cbLog->Checked)
				{
					tw->WriteLine(toLog);
					tw->Flush();
				}
			}

			redDistance += _getDistanceFrom((Point)v->getRoute(i - 1)->getCenterLocation(), v->getRoute(i)->getCenterLocation());
			greenDistance += _getDistanceFrom(v->getTarget(i - 1), v->getTarget(i));
			blueDistance += _getDistanceFrom(v->getFly(i - 1), v->getFly(i));
			cyanDistance += _getDistanceFrom(v->getHibridFly(i - 1), v->getHibridFly(i));

			toLog = simulationNumber + ";" + v->getRoute(i - 1)->getMyName() + _getStringFromCoordinatesToLog(v->getRoute(i - 1)->getCenterLocation())
				+ v->getRoute(i)->getMyName() + _getStringFromCoordinatesToLog2(v->getRoute(i)->getCenterLocation())
				+ _getStringFromCoordinatesToLog2(v->getTarget(i - 1)) + _getStringFromCoordinatesToLog2(v->getTarget(i))
				+ _getStringFromCoordinatesToLog2(v->getFly(i - 1)) + _getStringFromCoordinatesToLog2(v->getFly(i))
				+ _getStringFromCoordinatesToLog2(v->getHibridFly(i - 1)) + _getStringFromCoordinatesToLog2(v->getHibridFly(i)) + ";";

			if (cbLog->Checked)
			{
				tw->WriteLine(toLog);
				tw->Flush();
			}

			if (i == (_getActiveSensors() - 1) && tsClosedCircuit->Checked)
			{
				redDistance += _getDistanceFrom(v->getRoute(i)->getCenterLocation(), v->getMyFirstLocation());
				greenDistance += _getDistanceFrom(v->getTarget(i), v->getMyFirstLocation());
				blueDistance += _getDistanceFrom(v->getFly(i), v->getMyFirstLocation());
				cyanDistance += _getDistanceFrom(v->getHibridFly(i), v->getMyFirstLocation());

				toLog = simulationNumber + ";" + v->getRoute(i)->getMyName() + _getStringFromCoordinatesToLog(v->getRoute(i)->getCenterLocation())
					+ v->getMyName() + _getStringFromCoordinatesToLog2(v->getMyFirstLocation())
					+ _getStringFromCoordinatesToLog2(v->getTarget(i)) + _getStringFromCoordinatesToLog2(v->getMyFirstLocation())
					+ _getStringFromCoordinatesToLog2(v->getFly(i)) + _getStringFromCoordinatesToLog2(v->getMyFirstLocation())
					+ _getStringFromCoordinatesToLog2(v->getHibridFly(i)) + _getStringFromCoordinatesToLog2(v->getMyFirstLocation()) + ";";

				if (cbLog->Checked)
				{
					tw->WriteLine(toLog);
					tw->Flush();
				}
			}
		}

		if (cbLog->Checked)
		{
			toLog = ";;;;;;;;;;;;;;;;;;;" + redDistance + ";" + greenDistance + ";" + blueDistance + ";" + cyanDistance + ";" + Convert::ToInt32(numConRangeV2S->Value) + ";" + qSensors;

			if (tsCyanRoute->Checked)
			{
				if (blueDistance < greenDistance && blueDistance < cyanDistance)
					toLog += ";blueDistance;";
				else
				{
					if (greenDistance < blueDistance && greenDistance < cyanDistance)
						toLog += ";greenDistance;";
					else
						toLog += ";cyanDistance;";
				}
			}
			else
			{
				if (blueDistance < greenDistance)
					toLog += ";blueDistance";
				else
					toLog += ";greenDistance";
			}

			tw->WriteLine(toLog);
			tw->Flush();
		}

		Thread::Sleep(Convert::ToInt32(numSimulationPause->Value));
		Application::DoEvents();

		if (Convert::ToInt32(numQtySimulation->Value > 1))
			_ResetScenarioForSimulation(qUAVs, qSensors);
	}

	if (cbLog->Checked)
	{
		tw->Flush();
		tw->Close();
		cbLog->Checked = false;
		output->Text += _getTimeCRLF() + "Log deactivated.";
		output->Text += _getTimeCRLF() + "Log saved on path " + System::IO::Directory::GetCurrentDirectory() + logPath + "\\log\\";
	}
}
private: System::Void tsDrawCircleUAV_Click(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}

private: System::Void tsShowRoute_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	if (tsShowRoute->Checked)
		_updateRoutes(-1);

	simulationArea->Refresh();
}

private: System::UInt32 _getActiveSensors()
{
	activeSensors = 0;

	for (unsigned int i = 0; i < qSensors; i++)
	{
		activeSensors++;
	}

	return activeSensors;
}

private: System::Void tsScreenshoot_Click(System::Object^  sender, System::EventArgs^  e)
{
	Bitmap ^ printscreen = gcnew Bitmap(simulationArea->Bounds.Width, simulationArea->Bounds.Height);
	Graphics ^ graphics = Graphics::FromImage(printscreen);
	String ^ path = ".\\log\\PrintScreen_" + _getDateTime() + ".jpg";

	graphics->CopyFromScreen(this->Bounds.X + 20, this->Bounds.Y + 85, 0, 0, simulationArea->Bounds.Size);
	printscreen->Save(path, ImageFormat::Jpeg);

	output->Text += _getTimeCRLF() + "Screenshot from SimulationArea was saved as " + path;
}

private: System::Void bClusterAlg_Click(System::Object^  sender, System::EventArgs^  e)
{
	_updateClusters(tsShowCluster->Checked);
}

private: System::Void tsFixedTimers_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Int32 _getActualTimeSlot()
{
	return Math::Ceiling(((SystemStopWatch->ElapsedMilliseconds / 1000) / qSensors) % qSensors);
}

private: System::Int32 _getActualMicroTimeSlot()
{
	return Math::Ceiling(((SystemStopWatch->ElapsedMilliseconds) / timeSlotTime) % qTimeSlots);
}

private: System::Int32 _getNextMicroTimeSlot()
{
	if (_getActualMicroTimeSlot() + 1 > qTimeSlots - 1)
		return 0;
	else
		return (_getActualMicroTimeSlot() + 1);


	return Math::Ceiling((((SystemStopWatch->ElapsedMilliseconds) / timeSlotTime) + timeSlotTime) % qTimeSlots);
}

private: System::Int32 _getMicroTimeSlotsTotalCount()
{
	return Math::Ceiling(((SystemStopWatch->ElapsedMilliseconds ) / timeSlotTime));
}


private: System::Int32 _getMicroTimeSlotLaps()
{
	return Math::Ceiling(_getMicroTimeSlotsTotalCount() / qTimeSlots);
}


private: System::Int32 _getTimeSlotLaps()
{
	return Math::Ceiling(((SystemStopWatch->ElapsedMilliseconds / 1000) / qSensors) / qSensors);
}

private: System::Int32 _getTimeSlotsTotalCount()
{
	return Math::Ceiling(((SystemStopWatch->ElapsedMilliseconds / 1000) / qSensors));
}

private: System::Int32 _getNextTimeSlot()
{
	return Math::Ceiling(( ((SystemStopWatch->ElapsedMilliseconds / 1000) + qSensors) / qSensors) % qSensors);
}

private: System::Void tsClosedCircuit_Click(System::Object^  sender, System::EventArgs^  e)
{
	_updateRoutes(0);
}

private: System::Void cbUAVtoSesnor_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}
private: System::Void cbUavUav_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}
private: System::Void cbUAVtoServer_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();
}
private: System::Void numConRangeV2S_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	_updateGrid(qSensors);
	_updateRoutes(0);
}

private: System::UInt32 _getClusteredSensors()
{
	int counter = 0;

	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (mySensors[i]->getMyCluster() >= 0)
			counter++;
	}

	return counter;
}

private: System::UInt32 _countSensorsInCluster(int cluster)
{
	unsigned int counter = 0;

	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (mySensors[i]->getMyCluster() == cluster)
			counter++;
	}

	return counter;
}


private: System::Void _updateClusters(bool state)
{
	int actualCluster = 0;
	Sensor ^ s1;
	Sensor ^ s2;
	v = myVants[0];

	for (unsigned int i = 0; i < qSensors; i++)
	{
		mySensors[i]->setMyCluster(-1, state);
	}

	while (_getClusteredSensors() < qSensors)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			s1 = mySensors[i];

			for (unsigned int j = 0; j < qSensors; j++)
			{
				s2 = mySensors[j];

				if (i!=j)
				{
					if(_getDistanceFrom(s1->getCenterLocation(), s2->getCenterLocation()) <= Convert::ToInt32(numClusterDistance->Value))
					{
						if (!s1->hasCluster() && !s2->hasCluster())
						{
							s1->setMyCluster(actualCluster, state);
							s2->setMyCluster(actualCluster, state);
							output->Text += _getTimeCRLF() + "S" + s1->getID() + " has been assigned to cluster " + s1->getMyCluster();
							output->Text += _getTimeCRLF() + "S" + s2->getID() + " has been assigned to cluster " + s2->getMyCluster();
							actualCluster++;
						}
						else 
						{
							if (s1->hasCluster() && !s2->hasCluster())
							{
								s2->setMyCluster(s1->getMyCluster(), state);
								output->Text += _getTimeCRLF() + "S" + s2->getID() + " has been assigned to cluster " + s2->getMyCluster();
							}
							else
							{
								if (s2->hasCluster() && !s1->hasCluster())
								{
									s1->setMyCluster(s2->getMyCluster(), state);
									output->Text += _getTimeCRLF() + "S" + s1->getID() + " has been assigned to cluster " + s1->getMyCluster();
								}
								else
								{
									if (s1->hasCluster() && s2->hasCluster())
									{
										if(s1->getMyCluster() != s2->getMyCluster())
										{
											if (_countSensorsInCluster(s1->getMyCluster()) >= _countSensorsInCluster(s2->getMyCluster()))
											{
												output->Text += _getTimeCRLF() + "S" + s2->getID() + " has been assigned to cluster " + s1->getMyCluster();
												s2->setMyCluster(s1->getMyCluster(), state);
											}
											else
											{
												output->Text += _getTimeCRLF() + "S" + s1->getID() + " has been assigned to cluster " + s2->getMyCluster();
												s1->setMyCluster(s2->getMyCluster(), state);
											}
										}
									}
								}
							}
						}
					}
				}
			}

			if (!s1->hasCluster())
			{
				output->Text += _getTimeCRLF() + "Sensor " + s1->getID() + " is isolated, ... assigning it to a NEW CLUSTER " + actualCluster;
				s1->setMyCluster(actualCluster, state);
				actualCluster++;
			}
		}
	}

	for (unsigned int i = 0; i < qSensors; i++)
	{
		s = mySensors[i];
		v->getRouteListBySensorID(s->getID())->setMyCluster(s->getMyCluster());
	}

	output->Text += _getTimeCRLF() + "Clusters updated ... "; 

}

private: System::Boolean _isThereIntersection(Point ^ p, int radius)
{
	for (unsigned int i = 0; i < qSensors; i++)
		if (mySensors[i]->isIntersectionWith(p, radius))
			return true;

	return false;
}

private: Point _getMidPoint(unsigned int cluster)
{
	unsigned int qty = 0;
	float sumX = 0;
	float sumY = 0;	

	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (mySensors[i]->getMyCluster() == cluster)
		{
			sumX += mySensors[i]->getCenterLocation().X;
			sumY += mySensors[i]->getCenterLocation().Y;
			qty++;
		}
	}

	if (qty > 0)
		return Point(sumX / qty, sumY / qty);
	else
		return Point(0, 0);
}

private: Point _getMidPoint2(Point ^ p1, Point ^ p2)
{
	return Point ((p1->X + p2->X) / 2, (p1->Y + p2->Y) / 2);
}

private: System::Void tsDebug_Click(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();
}

private: System::Void numClusterDistance_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
{
	_updateClusters(tsShowCluster->Checked);
}

private: System::Void tsShowCluster_Click(System::Object^  sender, System::EventArgs^  e) 
{
	_updateClusters(tsShowCluster->Checked);
}

private: System::UInt32 FindLineCircleIntersections(Point Circle, float radius, PointF point1, PointF point2)
{
	float dx, dy, A, B, C, det, t;

	dx = point2.X - point1.X;
	dy = point2.Y - point1.Y;

	A = dx * dx + dy * dy;
	B = 2 * (dx * (point1.X - Circle.X) + dy * (point1.Y - Circle.Y));
	C = (point1.X - Circle.X) * (point1.X - Circle.X) + (point1.Y - Circle.Y) * (point1.Y - Circle.Y) - radius * radius;

	det = B * B - 4 * A * C;

	if ((A <= 0.0000001) || (det < 0))
	{
		intersection1 = Point(float::NaN, float::NaN);
		intersection2 = Point(float::NaN, float::NaN);
		
		return 0;
	}
	else if (det == 0)
	{
		t = -B / (2 * A);
		intersection1 = Point(point1.X + t * dx, point1.Y + t * dy);
		intersection2 = Point(float::NaN, float::NaN);
		return 1;
	}
	else
	{
		t = (float)((-B - Math::Sqrt(det)) / (2 * A));
		intersection1 = Point(point1.X + t * dx, point1.Y + t * dy);

		t = (float)((-B + Math::Sqrt(det)) / (2 * A));
		intersection2 = Point(point1.X + t * dx, point1.Y + t * dy);

		return 2;
	}
}

private: System::Boolean FindTangents(PointF center, float radius, PointF external_point)//
{
	double dx = center.X - external_point.X;
	double dy = center.Y - external_point.Y;
	double D_squared = dx * dx + dy * dy;
	
	if (D_squared < radius * radius)
	{
		Point pt1 = Point(-1, -1);
		Point pt2 = Point(-1, -1);
		return false;
	}

	double L = Math::Sqrt(D_squared - radius * radius);

	FindCircleCircleIntersections(center.X, center.Y, radius, external_point.X, external_point.Y, (float)L);

	return true;
}

private: System::Int32 FindCircleCircleIntersections(
	float cx0, float cy0, float radius0,
	float cx1, float cy1, float radius1)
{
	float dx = cx0 - cx1;
	float dy = cy0 - cy1;
	double dist = Math::Sqrt(dx * dx + dy * dy);

	if (dist > radius0 + radius1)
	{
		tangent1 = Point(float::NaN, float::NaN);
		tangent2 = Point(float::NaN, float::NaN);
		return 0;
	}
	else if (dist < Math::Abs(radius0 - radius1))
	{
		tangent1 = Point(float::NaN, float::NaN);
		tangent2 = Point(float::NaN, float::NaN);
		return 0;
	}
	else if ((dist == 0) && (radius0 == radius1))
	{
		tangent1 = Point(float::NaN, float::NaN);
		tangent2 = Point(float::NaN, float::NaN);
		return 0;
	}
	else
	{
		double a = (radius0 * radius0 - radius1 * radius1 + dist * dist) / (2 * dist);
		double h = Math::Sqrt(radius0 * radius0 - a * a);

		double cx2 = cx0 + a * (cx1 - cx0) / dist;
		double cy2 = cy0 + a * (cy1 - cy0) / dist;

		tangent1 = Point(
			(float)(cx2 + h * (cy1 - cy0) / dist),
			(float)(cy2 - h * (cx1 - cx0) / dist));
		tangent2= Point(
			(float)(cx2 - h * (cy1 - cy0) / dist),
			(float)(cy2 + h * (cx1 - cx0) / dist));

		if (dist == radius0 + radius1) return 1;
		return 2;
	}
}

private: System::Void tsGridSensor_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsGridSensor->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			_updateGrid(qSensors);
			s = mySensors[i];
			
			if(!s->isOnGrid())
				s->setXY(_getNearestGridLocation(s->getLocation()).X, _getNearestGridLocation(s->getLocation()).Y);
		}

		tsMaxSensorsGrid->Visible = true;
		tsMaxSensorsGrid->Text = myGridLocation.Count.ToString("00");
	}
	else
	{
		output->Text += _getTimeCRLF() + "Sensors alligment disabled ... ";
		tsMaxSensorsGrid->Visible = false;

	}
	simulationArea->Refresh();
}

private: System::Void _updateGrid(int totalSensors)
{
	int hor = (simulationArea->Width / (Math::Sqrt(3) * Convert::ToInt32(numConRangeV2S->Value)));
	int ver = (simulationArea->Height / Convert::ToInt32(numConRangeV2S->Value));

	Point p;                 

	//delete all points, and re-map area;
	myGridLocation.Clear();
	myGridControl.Clear();

	for (int i = 0; i <= hor; i++)
	{
		for (int j = 0; j <= ver; j++)
		{
			if (j % 2 == 0 && i % 2 == 0)
			{
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.Y = j * Convert::ToInt32(numConRangeV2S->Value);
				myGridLocation.Add(p);
			}

			if (j % 2 != 0 && i % 2 != 0)
			{
				p.X = i * Convert::ToInt32(numConRangeV2S->Value) * Math::Sqrt(3);
				p.Y = j * Convert::ToInt32(numConRangeV2S->Value);
				myGridLocation.Add(p);
			}
		}
	} 
	   
	for (unsigned int i = 0; i < myGridLocation.Count; i++)
		myGridControl.Add(true);

	//set the points that already have a sensor as FALSE;
	for (unsigned int i = 0; i < myGridLocation.Count; i++)
	{
		for (unsigned int j = 0; j < totalSensors; j++)
		{
			if (myGridLocation[i].Equals(mySensors[j]->getLocation()))
			{
				myGridControl[i] = false;
				mySensors[j]->setOnGrid(true);
			}
		}
	}

	tsMaxSensorsGrid->Text = myGridLocation.Count.ToString("00");
	simulationArea->Refresh();
}

private: Point _getGridPoint()
{
	int index;
	Random ^ rand = gcnew Random();
	index = rand->Next(myGridLocation.Count);

	while (myGridControl[index] == false)
		index = rand->Next(myGridLocation.Count);

	return myGridLocation[index]; 
}

private: Point _getNearestGridLocation(Point ^ p)
{
	int bestDistance = 9999;
	Point bestPosition;

	for (unsigned int i = 0; i < myGridLocation.Count; i++)
	{
		if ((_getDistanceFrom(p, myGridLocation[i]) < bestDistance) && myGridControl[i])
		{
			bestDistance = _getDistanceFrom(p, myGridLocation[i]);
			bestPosition = myGridLocation[i];
		}
	}

	return bestPosition;
}

private: System::Void _myDebug(String ^ debug)
{
	output->Text += _getTimeCRLF() + debug;
}

private: System::Void tsRedRoute_Click(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();
	
	if (tsRedRoute->Checked)
		redRouteON = ROUTE_RED;
	else
		redRouteON = ROUTE_EMPTY;

	_updateRoutes(-2);

	if(tsRedRoute->Checked)
		output->Text += _getTimeCRLF() + "RedRoute (DD) Path Planning Selected";
	else
		output->Text += _getTimeCRLF() + "RedRoute (DD) Path Planning unSelected";

}
private: System::Void tsGreenRoute_Click(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();
	
	if (tsGreenRoute->Checked)
		greenRouteON = ROUTE_GREEN;
	else
		greenRouteON = ROUTE_EMPTY;

	_updateRoutes(-2);

	if (tsGreenRoute->Checked)
		output->Text += _getTimeCRLF() + "NearestPoint (DDNN) Path Planning Selected";
	else
		output->Text += _getTimeCRLF() + "NearestPoint (DDNN) Path Planning unSelected";

}
private: System::Void tsBlueRoute_Click(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();

	if (tsBlueRoute->Checked)
		blueRouteON = ROUTE_BLUE;
	else
		blueRouteON = ROUTE_EMPTY;

	_updateRoutes(-2);

	if (tsBlueRoute->Checked)
		output->Text += _getTimeCRLF() + "BlueRoute (Kashuba) Path Planning Selected";
	else
		output->Text += _getTimeCRLF() + "BlueRoute (Kashuba) Path Planning unSelected";

}

private: System::Void tsCyanRoute_Click(System::Object^  sender, System::EventArgs^  e)
{
	simulationArea->Refresh();

	if (tsCyanRoute->Checked)
		cyanRouteON = ROUTE_CYAN;
	else
		cyanRouteON = ROUTE_EMPTY;

	_updateRoutes(-2);

	if (tsCyanRoute->Checked)
		output->Text += _getTimeCRLF() + "Cyan (Hybrid) Path Planning Selected";
	else
		output->Text += _getTimeCRLF() + "Cyan (Hybrid) Path Planning unSelected";
}

private: System::Void tsRouteInfo_Click(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();
}

private: System::Void tbPause_Scroll_1(System::Object^  sender, System::EventArgs^  e)
{
	nextStepTimer->Interval = tsStepInterval->Value;
	tsUAVSpeedText->Text = "UAV Speed: " + myVants[0]->getMyRealSpeed(tsStepInterval->Value).ToString("00") + "m/s";
	output->Text += _getTimeCRLF() + "UAV Speed changed to: " + myVants[0]->getMyRealSpeed(tsStepInterval->Value).ToString("00") + "m/s"; // -stepTimerValue: " + tsStepInterval->Value;
}

private: System::Void _LOGactivate(bool start)
{
	if(start)
	{
		if (tsLOG->Checked)
		{
			tw = gcnew StreamWriter("log\\S" + qSensors.ToString("00") + "_Simulation_" + simulationCounter.ToString("00") + "_" + _getDateTime() + ".csv", true);

			toLog2 = "Time;";

			if (checkBox4->Checked)
				toLog2 += "Actual TS;";

			if(checkBox1->Checked)
			{
				for (unsigned int i = 0; i < qSensors; i++)
				{
					toLog2 += mySensors[i]->getMyName() + "_Up/Down;";
				}
			}

			if (checkBox2->Checked)
				toLog2 += "UAV Speed;";

			if (checkBox3->Checked)
				toLog2 += "UAV Dist;";

			if (checkBox8->Checked)
				toLog2 += "TS Pend.;";

			if (checkBox5->Checked)
			{
				for (unsigned int i = 0; i < qSensors; i++)
				{
					toLog2 += mySensors[i]->getMyName() + "_LostUAVmsg;";
				}
			}

			if (checkBox6->Checked)
				toLog2 += "UAV Connection;";

			if (checkBox7->Checked)
				toLog2 += "UAV Hops;";

			if (checkBox9->Checked)
				toLog2 += "TimeSlotSeq;";

			if (checkBox10->Checked)
				toLog2 += "Decisions;";

			if (checkBox11->Checked)
				toLog2 += "UAV ID;";

			if (checkBox12->Checked)
			{
				toLog2 += "UAVwhereIamNow;";
				toLog2 += "UAV_X;UAV_Y;";
			}

			//basic data from scenario;
			toLog2 += "Width;" + simulationArea->Size.Width +
					 ";Height;" + simulationArea->Size.Height + 
					 ";qTimeSlots;" + qTimeSlots + 
					 ";timeSlotTime;" + timeSlotTime + 
					 ";qSensors;" + qSensors + ";";

			tw->WriteLine(toLog2);
			TimerSensorLOG->Start();
		}
		else
		{
			TimerSensorLOG->Stop();
			tw->Close();
		}
	}
}

private: System::Void TimerSensorLOG_Tick(System::Object^  sender, System::EventArgs^  e)
{
	tw->Flush();

	toLog2 = _getTimeToLog() + ";";

	if (checkBox4->Checked)
		toLog2 += _getActualTimeSlot() + ";";

	if(checkBox1->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			if (mySensors[i]->getMyState())
				toLog2 += "1;";
			else
				toLog2 += "0;";
		}
	}

	if (checkBox2->Checked)
		toLog2 += v->getSpeed() + ";";

	if (checkBox3->Checked)
		toLog2 += v->getTotalDistance() + ";";

	if (checkBox8->Checked)
		toLog2 += v->countDiscoveredSensorsOnRouteList() + ";";

	if (checkBox5->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			toLog2 += mySensors[i]->getLostUAVcounter() + ";";
		}
	}

	if (checkBox6->Checked)
		toLog2 += v->getConnectedWithSensorNow() + ";";

	if (checkBox7->Checked)
		toLog2 += v->getHopsCounter() + ";";

	if (checkBox9->Checked)
		toLog2 += _getMicroTimeSlotsTotalCount() + ";";

	if (checkBox10->Checked)
		toLog2 += v->getDecisionCounter() +";";

	if (checkBox11->Checked)
		toLog2 += v->getID() + ";";

	if (checkBox12->Checked)
	{
		toLog2 += v->getWhereIamNow() + ";";
		toLog2 += _getStringFromCoordinatesToLog3(v->getCenterLocation());
	}

	tw->WriteLine(toLog2);
}

private: System::Void tsLOG2_Click(System::Object^  sender, System::EventArgs^  e)
{
	_LOGactivate(false);

	if (tsLOG->Checked)
	{
		splitContainer3->Panel2Collapsed = false;
		output->Text += _getTimeCRLF() + "LOG Activated !!!";
	}
	else
	{
		splitContainer3->Panel2Collapsed = true;
		output->Text += _getTimeCRLF() + "LOG Deactivated !!!";
	}
}

private: System::Void tsBroadcastActivate_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (tsBroadcastActivate->Checked)
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			mySensors[i]->setMyTimeSlotTimers(Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(SleepingTime->Value), 0, qSensors);
		}

		if (tsLOG->Checked)
			TimerSensorLOG->Start();

		Timer1sec->Start();
		SystemStopWatch->Restart();

		output->Text += _getTimeCRLF() + "Broadcast timer activated in " + broadcastTime->Value.ToString() + "/" + SleepingTime->Value.ToString() + " s";

	}
	else
	{
		for (unsigned int i = 0; i < qSensors; i++)
		{
			mySensors[i]->setMyTimeSlotTimers(0, 0, 0, qSensors);
		}

		if (tsLOG->Checked)
		{
			TimerSensorLOG->Stop();
			tsLOG->Checked = false;
			tw->Close();
		}

		Timer1sec->Stop();
		SystemStopWatch->Reset();

		output->Text += _getTimeCRLF() + "Broadcast timer deactivated";
		SystemStopWatch->Stop();
	}

	simulationArea->Refresh();
}

private: System::Void _activateTSbuttonRandomSleep(bool state)
{
	tsRandSleep->Checked = state;

	if (tsRandSleep->Checked)
	{
		Timer1sec->Start();
		SystemStopWatch->Restart();

		if (tsLOG->Checked)
			TimerSensorLOG->Start();

		randomTimeSlotControl.Clear();

		broadcastTime->Value = qSensors * 1000;
		SleepingTime->Value = qSensors * 1000 * (qSensors - 1);
		 
		if (Convert::ToInt32(readTime->Value) >= Convert::ToInt32(broadcastTime->Value) * 0.75)
			readTime->Value = Convert::ToInt32(broadcastTime->Value) / 2;

		for (unsigned int i = 0; i < qSensors; i++)
		{
			s = mySensors[i];
			s->setMyReadingTime(Convert::ToInt32(readTime->Value));

			if (dataGridView->Rows[i]->Cells[2]->Value == "")
			{
				s->setMyTimeSlotTimers(Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(SleepingTime->Value), _getRandomTimeSlot(), qSensors);
				output->Text += _getTimeCRLF() + "Sensor[" + s->getID() + "] is programmed with RANDOM (" + s->getMyTimeSlot().ToString("00") + ") TimeSlot !";
				myVants[0]->addTimeSlotToRestrictions(s->getMyTimeSlot(), qSensors);
			}
			else
			{
				if (Convert::ToInt32(dataGridView->Rows[i]->Cells[2]->Value) < qSensors)
				{
					s->setMyTimeSlotTimers(Convert::ToInt32(broadcastTime->Value), Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(dataGridView->Rows[i]->Cells[2]->Value), qSensors);
					output->Text += _getTimeCRLF() + "Sensor[" + s->getID() + "] is programmed with provided TimeSlot " + dataGridView->Rows[i]->Cells[2]->Value;
				}
				else
					output->Text += _getTimeCRLF() + "Invalid data informed to SensorID[" + s->getID() + "] to timeSlot ";
			}
		}

		output->Text += _getTimeCRLF() + "Random TimeSlot activated for each Sensor ... ";
		output->Text += _getTimeCRLF() + "Bradcast Timer adjusted to " + broadcastTime->Value.ToString("0.00") + " ms";
	}
	else
	{
		Timer1sec->Stop();
		SystemStopWatch->Reset();

		for (unsigned int i = 0; i < qSensors; i++)
			mySensors[i]->setMyTimers1(0, 0);

		if (tsLOG->Checked)
		{
			TimerSensorLOG->Stop();
			tsLOG->Checked = false;
			tw->Close();
		}

		output->Text += _getTimeCRLF() + "Broadcast timer deactivated";
	}

	simulationArea->Refresh();
}

private: System::Void _activatetsMicroTimeSlots(bool state)
{
	tsMicroTimeSlots->Checked = state;    
	int TStotal, totalTime, TScounter;

	TScounter = 0;

	if (tsMicroTimeSlots->Checked)
	{
		Timer1sec->Start();
		SystemStopWatch->Restart();

		qTimeSlots = Convert::ToInt32(tsqTimeSlots->Text);
		totalTime = v->getTotalTimeForRoute(Convert::ToInt32(readTime->Value), Convert::ToInt32(tsStepInterval->Value));

		output->Text += _getTimeCRLF() + "totalTime: " + totalTime;

		timeSlotTime = totalTime / qTimeSlots;

		output->Text += _getTimeCRLF() + "timeSlotTime: " + timeSlotTime;

		numTSTime->Value = timeSlotTime;

		for (unsigned int i = 1; i <= v->getRouteListCount() - 1; i++)
		{
			TScounter += v->getTimeSlotsFromToByIndex(i - 1, i, Convert::ToInt32(readTime->Value), timeSlotTime, Convert::ToInt32(tsStepInterval->Value));

			if(tsDebug->Checked)
			{
				output->Text += _getTimeCRLF() + "From " + v->getRouteListByIndex(i - 1)->getMyID() + " to " + v->getRouteListByIndex(i)->getMyID() + " will take " + v->getTimeSlotsFromToByIndex(i - 1, i, Convert::ToInt32(readTime->Value), timeSlotTime, Convert::ToInt32(tsStepInterval->Value)) + " timeSlots";
				output->Text += " --> SensorID[" + v->getRouteListByIndex(i)->getMyID() + "] will be on timeSlot " + TScounter.ToString("00");
			}

			v->getRouteListByIndex(i)->setTimeSlotsUntillHere(TScounter);

			if (i == v->getRouteListCount() - 1)
			{
				TScounter += v->getTimeSlotsFromToByIndex(v->getRouteListCount() - 1, 0, Convert::ToInt32(readTime->Value), timeSlotTime, Convert::ToInt32(tsStepInterval->Value));
				
				if(tsDebug->Checked)
					output->Text += _getTimeCRLF() + "From " + v->getRouteListByIndex(v->getRouteListCount() - 1)->getMyID() + " to " + v->getRouteListByIndex(0)->getMyID() + " will take " + v->getTimeSlotsFromToByIndex(v->getRouteListCount() - 1, 0, Convert::ToInt32(readTime->Value), timeSlotTime, Convert::ToInt32(tsStepInterval->Value)) + " timeSlots";
			}
		}

		TStotal = TScounter; 
		
		if (TStotal > qTimeSlots)
		{
			qTimeSlots = TStotal;
			tsqTimeSlots->Text = TStotal.ToString();
		}

		if (tsLOG->Checked)
			TimerSensorLOG->Start();

		randomTimeSlotControl.Clear();
		v->clearALLrestrictionsForReset();

		broadcastTime->Value = Convert::ToInt32(numBCtimeSlots->Value)*timeSlotTime;
		
		SleepingTime->Value = Math::Abs((timeSlotTime * qTimeSlots) - broadcastTime->Value);

		for (unsigned int i = 0; i < qSensors; i++)
		{
			s = mySensors[i];
			s->setMyReadingTime(Convert::ToInt32(readTime->Value));

			if (dataGridView->Rows[i]->Cells[2]->Value == "")
			{
				s->setMyMicroTimeSlotTimers(_getRandomTimeSlot(), timeSlotTime, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value));
			}
			else
			{
				if (Convert::ToInt32(dataGridView->Rows[i]->Cells[2]->Value) < qTimeSlots)
				{
					s->setMyMicroTimeSlotTimers(Convert::ToInt32(dataGridView->Rows[i]->Cells[2]->Value), timeSlotTime, Convert::ToInt32(SleepingTime->Value), Convert::ToInt32(broadcastTime->Value));
					output->Text += _getTimeCRLF() + "Sensor[" + s->getID() + "] is programmed with provided uTimeSlot " + s->getMyTimeSlot().ToString("00");

					randomTimeSlotControl.Add(s->getMyTimeSlot());
				}
				else
					output->Text += _getTimeCRLF() + "Invalid data informed to SensorID[" + s->getID() + "] to timeSlot ";
			}

			v->addTimeSlotToRestrictions(s->getMyTimeSlot(), qSensors);
		}

		for (unsigned int i = 0; i < qTimeSlots; i++)
		{
			if (!randomTimeSlotControl.Contains(i))
				v->addTimeSlotToRestrictions(i, qSensors);
		}

		output->Text += CRLF;
		output->Text += _getTimeCRLF() + "Route Total Time is: " + (timeSlotTime*qTimeSlots).ToString("0000.00") + " ms";
		output->Text += _getTimeCRLF() + "TimeSlots: " + qTimeSlots;
		output->Text += _getTimeCRLF() + "TimeSlot Time: " + timeSlotTime.ToString("0000") + " ms";
		output->Text += _getTimeCRLF() + "To reprogramm all Sensors will be necessary " + TStotal.ToString("00") + " timeSlots";
		output->Text += _getTimeCRLF() + "Random TimeSlot activated for each Sensor ... ";
		output->Text += CRLF;
	}
	else
	{
		Timer1sec->Stop();
		SystemStopWatch->Reset();

		for (unsigned int i = 0; i < qSensors; i++)
			mySensors[i]->setMyTimers1(0, 0);

		if (tsLOG->Checked)
		{
			TimerSensorLOG->Stop();
			tsLOG->Checked = false;
			tw->Close();
		}

		output->Text += _getTimeCRLF() + "Broadcast timer deactivated";
	}

	simulationArea->Refresh();
}

private: System::Void tsMicroTimeSlots_Click(System::Object^  sender, System::EventArgs^  e)
{
	if(tsMicroTimeSlots->Checked)
		_activatetsMicroTimeSlots(true);
	else
		_activatetsMicroTimeSlots(false);
}

private: System::Void tsRandSleep_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if(tsRandSleep->Checked)
		_activateTSbuttonRandomSleep(true);
	else
		_activateTSbuttonRandomSleep(false);
}

private: System::Int32 _getRandomTimeSlot()
{
	Random ^ rand = gcnew Random();
	int myRand;
	
	if (tsMicroTimeSlots->Checked)
		myRand = rand->Next(qTimeSlots);

	if (tsRandSleep->Checked)
		myRand = rand->Next(qSensors);

	if(tsRepeatTimeSlots->Checked)
	{
		while(randomTimeSlotControl.Contains(myRand))
		{
			if (tsMicroTimeSlots->Checked)
				myRand = rand->Next(qTimeSlots);

			if (tsRandSleep->Checked)
				myRand = rand->Next(qSensors);
		}

		randomTimeSlotControl.Add(myRand);
	}

	Thread::Sleep(50);

	return myRand;
}

private: System::Int32 _Dijkstra_MinimumDistance(array<int>^ distance, array<bool>^ shortestPathTreeSet, int verticesCount)
{
	int min = Int32::MaxValue;
	int minIndex;

	for (int i = 0; i < verticesCount; i++)
	{
		if (shortestPathTreeSet[i] == false && distance[i] <= min)
		{
			min = distance[i];
			minIndex = i;
		}
	}

	return minIndex;
}

private: System::Void _Dijkstra_Print(array<int>^ distance, int verticesCount)
{
	output->Text += _getTimeCRLF() + "Index - Distance from Source";

	for (int i = 0; i < verticesCount; i++)
		output->Text += _getTimeCRLF() + "  " + i + "  \t  " + distance[i];
}

private: System::Void _Dijkstra_Alg(array<int, 2>^ graph, int source, int verticesCount)
{
	array<int>^ distance = gcnew array<int>(verticesCount);
	array<bool>^ shortestPathTreeSet = gcnew array<bool>(verticesCount);

	for (int i = 0; i < verticesCount; i++)
	{
		distance[i] = Int32::MaxValue;
		shortestPathTreeSet[i] = false;
	}

	distance[source] = 0;

	for (int count = 0; count < verticesCount - 1; count++)
	{
		int u = _Dijkstra_MinimumDistance(distance, shortestPathTreeSet, verticesCount);
		shortestPathTreeSet[count] = true;

		for (int v = 0; v < verticesCount; ++v)
		{
			if (!shortestPathTreeSet[v] && Convert::ToBoolean(graph[u, v]) && distance[u] != Int32::MaxValue && distance[u] + graph[u, v] < distance[v])
				distance[v] = distance[u] + graph[u, v];
		}
	}

	_Dijkstra_Print(distance, verticesCount);
}


private: System::Void timer1sec_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	simulationArea->Refresh();     

	percentPicture = 100 - 100 * Convert::ToDouble((v->getFlyTime() / 1000) / numUAVAutonomy->Value);

	if(percentPicture <= numBatteryLevel->Value)
		tsSwapUAVs->Checked = true;
	else
		tsSwapUAVs->Checked = false;

	if(percentPicture>0)
		tsBattery->Value = percentPicture;

	tsTimer2->Text = SystemStopWatch->Elapsed.ToString("mm':'ss':'fff");
	
	//UPDATE UAV큦 PANNEL INFORMATION;
	if(v->getSpeed() == MIN_SPEED)
		tsUAVSpeedText->Text = "Speed: " + v->getSpeed().ToString("00") + "m/s";
	else
		tsUAVSpeedText->Text = "Speed: " + v->getMyRealSpeed().ToString("00") + "m/s";

	tsUAVFlyedDistance->Text = "Flyed Dist.: " + v->getTotalDistance().ToString("0000") + "m";
	tsUAVHops->Text = "Hops: " + v->getHopsCounter().ToString("000");

	if (tsMicroTimeSlots->Checked)
		tsTSLabel2->Text = "TimeSlot " + _getActualMicroTimeSlot().ToString("00") + "/" + (qTimeSlots - 1).ToString("00") + " - " + _getMicroTimeSlotsTotalCount().ToString("00") + "/" + _getMicroTimeSlotLaps().ToString("00");

	if(tsRandSleep->Checked)
		tsTSLabel2->Text = "TimeSlot " + _getActualTimeSlot().ToString("00") + "/" + (v->getRouteListCount() - 2).ToString("00") + " - " + _getTimeSlotsTotalCount().ToString("00") + "/" + _getTimeSlotLaps().ToString("00");

	tsDecision->Text = "Decisions: " + v->getDecisionCounter().ToString("00");

	//update gridView큦 information;
	for (unsigned int i = 0; i < qSensors; i++)   
	{
		s = mySensors[i];

		if (s->getMyTimnerInterval() != s->getMyBCTime() && s->isMyTimerEnabled())
		{
			if (s->getMyTimnerInterval() == s->getMySleepingTime())
				dataGridTimeDiff = s->getMySleepingTime() - s->getMyStopWatch()->ElapsedMilliseconds;
			else
			{
				if(s->getMyTimnerInterval() == s->getMyDelay())
					dataGridTimeDiff = s->getMyDelay() - s->getMyStopWatch()->ElapsedMilliseconds;
				else  
					dataGridTimeDiff = s->getMyReadTime() - s->getMyStopWatch()->ElapsedMilliseconds;
			}

			if (dataGridTimeDiff > Convert::ToInt32(readTime->Value))
			{
				dataGridView->Rows[i]->SetValues(s->getMyName(), dataGridTimeDiff, s->getMyOldNewTimeSlots());
				dataGridView->Rows[i]->Cells[1]->Style->BackColor = Color::White;
			}
			else
			{
				if (dataGridTimeDiff >= 0)
				{
					dataGridView->Rows[i]->SetValues(s->getMyName(), dataGridTimeDiff, s->getMyOldNewTimeSlots());
					dataGridView->Rows[i]->Cells[1]->Style->BackColor = Color::FromArgb(255, 255, 224);
				}
			}
		}
		else   
		{
			dataGridTimeDiff = s->getMyBCTime() - s->getMyStopWatch()->ElapsedMilliseconds;

			if(s->getMyState())
				dataGridView->Rows[i]->Cells[1]->Style->BackColor = Color::FromArgb(240, 255, 240);
			else
				dataGridView->Rows[i]->Cells[1]->Style->BackColor = Color::White;

			dataGridView->Rows[i]->SetValues(s->getMyName(), dataGridTimeDiff, s->getMyOldNewTimeSlots());
		}

		if(!_allSensorsReprogrammed())
		{
			if (s->isTimeSlotReprogrammed())
				dataGridView->Rows[i]->Cells[2]->Style->BackColor = Color::Azure;
		}
		else
			dataGridView->Rows[i]->Cells[2]->Style->BackColor = Color::White;

		dataGridView->CurrentCell->Selected = false;
	}
}

private: System::Boolean _DiscoveredAllSensors()
{
	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (!mySensors[i]->getDiscovered())
		{
			timeSlotSensorID = mySensors[i]->getID();
			return false;
		}
	}

	return true;
}

private: System::Boolean _allSensorsReprogrammed()
{
	for (unsigned int i = 0; i < qSensors; i++)
	{
		if (!mySensors[i]->isTimeSlotReprogrammed())
			return false;
	}

	return true;
}

private: System::Boolean _actualTimeSlotIsFree(bool random)
{
	if (v->isSensorConnected() > 0)
		return true;

	for (unsigned int i = 0; i < v->getRouteListCount(); i++)
	{
		if (tsMicroTimeSlots->Checked)
		{
			if (v->getRouteListByIndex(i)->getMyOriginalTimeSlot() == _getActualMicroTimeSlot())
			{
				if (random)
				{
					timeSlotSensorID = v->getRouteListByIndex(i)->getMyID();
					return false;
				}
			}
		}
		else
		{
			if (v->getRouteListByIndex(i)->getMyOriginalTimeSlot() == _getActualTimeSlot())
			{
				if (random)
				{
					timeSlotSensorID = v->getRouteListByIndex(i)->getMyID();
					return false;
				}
			}
		}
	}

	return true;
}

private: System::Int32 _getNextIforMyTimeSlot()
{
	for (unsigned int i = 0; i < v->getRouteListCount(); i++)
	{
		if (v->getRouteListByIndex(i)->getMyTimeSlot() == _getActualTimeSlot())
		{
			if (i == v->getRouteListCount() - 1)
				return v->getRouteListByIndex(0)->getMyID();
			else
				return v->getRouteListByIndex(i + 1)->getMyID();
		}
	}
}

private: System::String ^ _getTimeCRLF()
{
	if (tsMicroTimeSlots->Checked)
		return "\r\n" + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff") + " / TS: " + _getActualMicroTimeSlot().ToString("00") + " - ";
	else
		return "\r\n" + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff") + " / TS: " + _getActualTimeSlot().ToString("00") + " - ";
}

private: System::String ^ _getTimeCRLF_()
{
	if (tsMicroTimeSlots->Checked)
		return "\r\n" + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff") + " / TS: " + _getActualMicroTimeSlot().ToString("00");
	else
		return "\r\n" + SystemStopWatch->Elapsed.ToString("mm':'ss':'fff") + " / TS: " + _getActualTimeSlot().ToString("00");
}

private: System::String ^ _getTimeToLog()
{
	return SystemStopWatch->ElapsedMilliseconds.ToString();
}

private: System::Void tsSetTimeSlot_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsSetTimeSlot->Checked)
		output->Text += _getTimeCRLF() + "UAV will program Sensors timeSlot based on it own routeList.";
	else
		output->Text += _getTimeCRLF() + "UAV will not programm Sensors timeslots, it will keep the Random timeSlot on them, and just follow it.";
}

private: System::Void tsHome_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsBackToDeposit->Checked)
		output->Text += _getTimeCRLF() + "UAV will return to Deposit to delivery the colected messages when it is near from Deposit";
	else
		output->Text += _getTimeCRLF() + "UAV will not return to Deposit to delivery the colected messages.";
}

private: System::Void tsScanForSensors_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsScanForSensors->Checked)
		output->Text += _getTimeCRLF() + "UAV will fly scanning for Sensor큦 activity even when it is not above any target";
	else
		output->Text += _getTimeCRLF() + "UAV will only scan for Sensor큦 activity when it reaches the programmed target";

}

private: System::Void tsLOG_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	if (tsLOG->Checked)
		splitContainer3->Panel2Collapsed = false;
	else
		splitContainer3->Panel2Collapsed = true;
}

private: System::Void toolStripButton1_Click_1(System::Object^  sender, System::EventArgs^  e) 
{
	System::Diagnostics::Process::Start(".\\log");
}


private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) 
{
}

private: System::Void tsqTimeSlots_TextChanged(System::Object^  sender, System::EventArgs^  e) 
{
	qTimeSlots = Convert::ToInt32(tsqTimeSlots->Text);
	output->Text += _getTimeCRLF() + "TimeSlots: " + qTimeSlots;
}

private: System::Void tsSwapUAVs_Click(System::Object^  sender, System::EventArgs^  e) 
{

}
private: System::Void cbUAVAutonomy_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
}
private: System::Void tsShowRoute_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}

