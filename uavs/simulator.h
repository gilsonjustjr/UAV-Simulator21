#pragma once

#include "helpers.h"

bool runProgram = true;
int qUAVs = 1;
int qSensors = 0;

namespace uavs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::Panel^  simulationArea;
	protected:
	private: System::Windows::Forms::TextBox^  output;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  bRunSimulator;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  qSensorsNumeric;
	private: System::Windows::Forms::NumericUpDown^  qUAVsNumeric;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::CheckBox^  cbUAVinfo;

	private: static array<System::Windows::Forms::PictureBox^>^ uavs = (gcnew array<System::Windows::Forms::PictureBox^>(64));
	private: static array<System::Windows::Forms::PictureBox^>^ sensors = (gcnew array<System::Windows::Forms::PictureBox^>(64));

	private: System::Windows::Forms::GroupBox^  groupBox2;




	private: System::Windows::Forms::Label^  labelUAV;
	private: System::Windows::Forms::CheckBox^  cbTrackUAVs;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  outTrackUAVs;
	private: System::Windows::Forms::CheckBox^  cbBackGround;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  lVelocity;
	private: System::Windows::Forms::NumericUpDown^  VeloUAV;


	private: System::ComponentModel::IContainer^  components;






	private:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(simulator::typeid));
			this->simulationArea = (gcnew System::Windows::Forms::Panel());
			this->labelUAV = (gcnew System::Windows::Forms::Label());
			this->output = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lVelocity = (gcnew System::Windows::Forms::Label());
			this->VeloUAV = (gcnew System::Windows::Forms::NumericUpDown());
			this->cbBackGround = (gcnew System::Windows::Forms::CheckBox());
			this->cbTrackUAVs = (gcnew System::Windows::Forms::CheckBox());
			this->cbUAVinfo = (gcnew System::Windows::Forms::CheckBox());
			this->qSensorsNumeric = (gcnew System::Windows::Forms::NumericUpDown());
			this->qUAVsNumeric = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->bRunSimulator = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->outTrackUAVs = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->simulationArea->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VeloUAV))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qSensorsNumeric))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qUAVsNumeric))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// simulationArea
			// 
			this->simulationArea->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->simulationArea->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->simulationArea->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->simulationArea->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->simulationArea->Controls->Add(this->labelUAV);
			this->simulationArea->Location = System::Drawing::Point(12, 12);
			this->simulationArea->Name = L"simulationArea";
			this->simulationArea->Size = System::Drawing::Size(853, 515);
			this->simulationArea->TabIndex = 0;
			this->simulationArea->SizeChanged += gcnew System::EventHandler(this, &simulator::simulationArea_SizeChanged);
			this->simulationArea->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &simulator::simulationArea_Paint);
			// 
			// labelUAV
			// 
			this->labelUAV->AutoSize = true;
			this->labelUAV->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelUAV->Location = System::Drawing::Point(148, 165);
			this->labelUAV->Name = L"labelUAV";
			this->labelUAV->Size = System::Drawing::Size(0, 13);
			this->labelUAV->TabIndex = 2;
			// 
			// output
			// 
			this->output->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->output->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->output->Font = (gcnew System::Drawing::Font(L"Lucida Console", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->output->ForeColor = System::Drawing::SystemColors::InfoText;
			this->output->Location = System::Drawing::Point(6, 19);
			this->output->Multiline = true;
			this->output->Name = L"output";
			this->output->ReadOnly = true;
			this->output->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->output->Size = System::Drawing::Size(659, 131);
			this->output->TabIndex = 1;
			this->output->TextChanged += gcnew System::EventHandler(this, &simulator::output_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->lVelocity);
			this->groupBox1->Controls->Add(this->VeloUAV);
			this->groupBox1->Controls->Add(this->cbBackGround);
			this->groupBox1->Controls->Add(this->cbTrackUAVs);
			this->groupBox1->Controls->Add(this->cbUAVinfo);
			this->groupBox1->Controls->Add(this->qSensorsNumeric);
			this->groupBox1->Controls->Add(this->qUAVsNumeric);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(872, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(176, 515);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L" Config ";
			// 
			// lVelocity
			// 
			this->lVelocity->AutoSize = true;
			this->lVelocity->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lVelocity->Location = System::Drawing::Point(15, 132);
			this->lVelocity->Name = L"lVelocity";
			this->lVelocity->Size = System::Drawing::Size(133, 14);
			this->lVelocity->TabIndex = 7;
			this->lVelocity->Text = L"Velocity (m/s)";
			// 
			// VeloUAV
			// 
			this->VeloUAV->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->VeloUAV->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->VeloUAV->Location = System::Drawing::Point(18, 149);
			this->VeloUAV->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->VeloUAV->Name = L"VeloUAV";
			this->VeloUAV->Size = System::Drawing::Size(141, 21);
			this->VeloUAV->TabIndex = 6;
			this->VeloUAV->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->VeloUAV->ValueChanged += gcnew System::EventHandler(this, &simulator::VeloUAV_ValueChanged);
			// 
			// cbBackGround
			// 
			this->cbBackGround->AutoSize = true;
			this->cbBackGround->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbBackGround->Location = System::Drawing::Point(18, 301);
			this->cbBackGround->Name = L"cbBackGround";
			this->cbBackGround->Size = System::Drawing::Size(154, 18);
			this->cbBackGround->TabIndex = 5;
			this->cbBackGround->Text = L"Background Image";
			this->cbBackGround->UseVisualStyleBackColor = true;
			this->cbBackGround->CheckedChanged += gcnew System::EventHandler(this, &simulator::checkBox1_CheckedChanged);
			// 
			// cbTrackUAVs
			// 
			this->cbTrackUAVs->AutoSize = true;
			this->cbTrackUAVs->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbTrackUAVs->Location = System::Drawing::Point(18, 277);
			this->cbTrackUAVs->Name = L"cbTrackUAVs";
			this->cbTrackUAVs->Size = System::Drawing::Size(106, 18);
			this->cbTrackUAVs->TabIndex = 4;
			this->cbTrackUAVs->Text = L"Track UAVs";
			this->cbTrackUAVs->UseVisualStyleBackColor = true;
			this->cbTrackUAVs->CheckedChanged += gcnew System::EventHandler(this, &simulator::cbTrackUAVs_CheckedChanged);
			// 
			// cbUAVinfo
			// 
			this->cbUAVinfo->AutoSize = true;
			this->cbUAVinfo->Checked = true;
			this->cbUAVinfo->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbUAVinfo->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbUAVinfo->Location = System::Drawing::Point(18, 253);
			this->cbUAVinfo->Name = L"cbUAVinfo";
			this->cbUAVinfo->Size = System::Drawing::Size(138, 18);
			this->cbUAVinfo->TabIndex = 3;
			this->cbUAVinfo->Text = L"Show UAVs Info";
			this->cbUAVinfo->UseVisualStyleBackColor = true;
			this->cbUAVinfo->CheckedChanged += gcnew System::EventHandler(this, &simulator::cbUAVinfo_CheckedChanged);
			// 
			// qSensorsNumeric
			// 
			this->qSensorsNumeric->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->qSensorsNumeric->Location = System::Drawing::Point(18, 205);
			this->qSensorsNumeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9, 0, 0, 0 });
			this->qSensorsNumeric->Name = L"qSensorsNumeric";
			this->qSensorsNumeric->Size = System::Drawing::Size(141, 21);
			this->qSensorsNumeric->TabIndex = 2;
			this->qSensorsNumeric->ValueChanged += gcnew System::EventHandler(this, &simulator::qSensorsNumeric_ValueChanged);
			// 
			// qUAVsNumeric
			// 
			this->qUAVsNumeric->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->qUAVsNumeric->Location = System::Drawing::Point(18, 96);
			this->qUAVsNumeric->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 63, 0, 0, 0 });
			this->qUAVsNumeric->Name = L"qUAVsNumeric";
			this->qUAVsNumeric->Size = System::Drawing::Size(141, 21);
			this->qUAVsNumeric->TabIndex = 2;
			this->qUAVsNumeric->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->qUAVsNumeric->ValueChanged += gcnew System::EventHandler(this, &simulator::qUAVsNumeric_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(15, 188);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(70, 14);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Sensors";
			this->label4->Click += gcnew System::EventHandler(this, &simulator::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(15, 79);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(43, 14);
			this->label3->TabIndex = 1;
			this->label3->Text = L"UAVs";
			this->label3->Click += gcnew System::EventHandler(this, &simulator::label2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(15, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 14);
			this->label2->TabIndex = 1;
			this->label2->Text = L"lAreaSize";
			this->label2->Click += gcnew System::EventHandler(this, &simulator::label2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(15, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(142, 14);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Simulation Area";
			// 
			// bRunSimulator
			// 
			this->bRunSimulator->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->bRunSimulator->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bRunSimulator->Location = System::Drawing::Point(872, 654);
			this->bRunSimulator->Name = L"bRunSimulator";
			this->bRunSimulator->Size = System::Drawing::Size(176, 36);
			this->bRunSimulator->TabIndex = 3;
			this->bRunSimulator->Text = L"Start Simulation";
			this->bRunSimulator->UseVisualStyleBackColor = true;
			this->bRunSimulator->Click += gcnew System::EventHandler(this, &simulator::button1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->output);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(13, 534);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(671, 156);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L" Output ";
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox3->Controls->Add(this->outTrackUAVs);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(690, 534);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(175, 156);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"UAV´s (ID;X;Y)";
			// 
			// outTrackUAVs
			// 
			this->outTrackUAVs->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outTrackUAVs->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outTrackUAVs->Location = System::Drawing::Point(7, 23);
			this->outTrackUAVs->Multiline = true;
			this->outTrackUAVs->Name = L"outTrackUAVs";
			this->outTrackUAVs->ReadOnly = true;
			this->outTrackUAVs->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->outTrackUAVs->Size = System::Drawing::Size(162, 127);
			this->outTrackUAVs->TabIndex = 0;
			this->outTrackUAVs->TextChanged += gcnew System::EventHandler(this, &simulator::outTrackUAVs_TextChanged);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &simulator::timer1_Tick);
			// 
			// simulator
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1060, 702);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->bRunSimulator);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->simulationArea);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximumSize = System::Drawing::Size(1076, 857);
			this->MinimumSize = System::Drawing::Size(876, 657);
			this->Name = L"simulator";
			this->Text = L"UAV Simulator";
			this->Load += gcnew System::EventHandler(this, &simulator::simulator_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &simulator::simulator_ResizeEnd);
			this->simulationArea->ResumeLayout(false);
			this->simulationArea->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->VeloUAV))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qSensorsNumeric))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->qUAVsNumeric))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		int dirX[63];
		int dirY[63];

		for (int i = 0; i < qUAVs; i++)
		{
			dirX[i] = Convert::ToInt32(VeloUAV->Value / 10);
			dirY[i] = Convert::ToInt32(VeloUAV->Value / 10);
		}
		
		if (runProgram == true)
		{
			timer1->Start();
			timer1->Interval = 200;
			timer1->Enabled = true;
			VeloUAV->Enabled = false;

			bRunSimulator->Text = "Stop Simulation" + CRLF;
			output->Text += _getTime() + "Simulation Started" + CRLF;

			runProgram = false;

			while (runProgram == false)
			{
				for (int i = 0; i < qUAVs; i++)
				{
					if (uavs[i]->Location.X < (simulationArea->Width - uavs[i]->Size.Width))
						dirX[i] *= -1;
					if (uavs[i]->Location.X > 0)
						dirX[i] *= -1;
					if (uavs[i]->Location.Y > (simulationArea->Height - uavs[i]->Size.Height))
						dirY[i] *= -1;
					if (uavs[i]->Location.Y < 0)
						dirY[i] *= -1;

					uavs[i]->Location = System::Drawing::Point(uavs[i]->Location.X + dirX[i], uavs[i]->Location.Y + dirY[i]);
	
					if (cbTrackUAVs->Checked)
					{
					}
				}

				if (cbUAVinfo->Checked)
				{
					labelUAV->Visible = true;
					labelUAV->Text = "(" + uavs[0]->Location.X + ", " + uavs[0]->Location.Y + ")";
					labelUAV->Location = System::Drawing::Point(uavs[0]->Location.X + uavs[0]->Size.Width, uavs[0]->Location.Y);
				}
				else
					labelUAV->Visible = false;

				Application::DoEvents();
				simulationArea->Refresh();
			}
		}
		else
		{
			if (runProgram == false)
			{
				bRunSimulator->Text = "Start Simulation" + CRLF;
				runProgram = true;
				output->Text += _getTime() + "Simulation Stopped" + CRLF;
				VeloUAV->Enabled = true;
				timer1->Stop();
				timer1->Enabled = false;
			}
		}

	}

	private: System::Void simulator_Load(System::Object^  sender, System::EventArgs^  e) {
		
		label2->Text = "(w: " + simulationArea->Width + " x h: " + simulationArea->Height + ")";

		System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox();

		Random^ randObj = gcnew Random; 

		for (unsigned int i = 0; i< qUAVsNumeric->Value; i++)
		{
			uavs[i] = gcnew System::Windows::Forms::PictureBox();
			uavs[i]->Image = Image::FromFile("uav.png");
			uavs[i]->Size = System::Drawing::Size(41, 40);
			uavs[i]->Location = System::Drawing::Point(randObj->Next(1, simulationArea->Width), randObj->Next(1, simulationArea->Height));
			simulationArea->Controls->Add(uavs[i]);
		}

		labelUAV->Location = System::Drawing::Point(uavs[0]->Location.X + uavs[0]->Size.Width, uavs[0]->Location.Y);
		labelUAV->Text = "(" + uavs[0]->Location.X + ", " + uavs[0]->Location.Y + ")";
		labelUAV->Visible = true;
		output->Text += _getTime() + "Show UAV Info enabled" + CRLF;


	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void simulationArea_SizeChanged(System::Object^  sender, System::EventArgs^  e) {

		System::Windows::Forms::PictureBox^ p;

		for(int i=0; i<qUAVs; i++)
		{
			p = uavs[i];

			if (p->Location.X > simulationArea->Width - p->Size.Width)
				p->Location = System::Drawing::Point(simulationArea->Width - p->Size.Width, p->Location.Y);

			if (p->Location.Y > simulationArea->Height - p->Size.Height)
				p->Location = System::Drawing::Point(p->Location.X, simulationArea->Height - p->Size.Height);
		}

		labelUAV->Location = System::Drawing::Point(uavs[0]->Location.X + uavs[0]->Size.Width, uavs[0]->Location.Y);
		labelUAV->Text = "(" + uavs[0]->Location.X + ", " + uavs[0]->Location.Y + ")";

	}
	private: System::Void cbUAVinfo_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

		if (cbUAVinfo->Checked == true)
		{
			labelUAV->Location = System::Drawing::Point(uavs[0]->Location.X + uavs[0]->Size.Width, uavs[0]->Location.Y);
			labelUAV->Text = "(" + uavs[0]->Location.X + ", " + uavs[0]->Location.Y + ")";
			labelUAV->Visible = true;
			output->Text += _getTime() + "Show UAV Info enabled" + CRLF;
		}
		else
		{
			labelUAV->Visible = false;
			output->Text += _getTime() + "Show UAV Info disabled" + CRLF;
		}
	}
	private: System::Void simulator_ResizeEnd(System::Object^  sender, System::EventArgs^  e)
	{
		label2->Text = "(w: " + simulationArea->Width + " x h: " + simulationArea->Height + ")";
		output->Text += _getTime() + "Simulation Area resized to (w: " + simulationArea->Width + " x h: " + simulationArea->Height + ")" + CRLF;

	}
	private: System::Void simulationArea_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}

	private: System::Void output_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		output->SelectionStart = output->TextLength;
		output->ScrollToCaret();
	}

	private: System::Void qUAVsNumeric_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		
		for (int i=0;i<=qUAVs;i++)
			simulationArea->Controls->Remove(uavs[i]);

		labelUAV->Visible = false;
		simulationArea->Refresh();

		Random^ randObj = gcnew Random;

		output->Text += _getTime() + "Simulation set to " + qUAVsNumeric->Value.ToString() + " UAVs" + CRLF;
		System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox();

		for(unsigned int i = 0; i < qUAVsNumeric->Value; i++)
		{
			uavs[i] = gcnew System::Windows::Forms::PictureBox();
			uavs[i]->Image = Image::FromFile("uav.png");
			uavs[i]->Size = System::Drawing::Size(41, 40);
			uavs[i]->Location = System::Drawing::Point(randObj->Next(1, simulationArea->Width - uavs[i]->Width), randObj->Next(1, simulationArea->Height - uavs[i]->Height));
			simulationArea->Controls->Add(uavs[i]);
		}

		qUAVs = Convert::ToInt32(qUAVsNumeric->Value);
	}

	public: System::Void qSensorsNumeric_ValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		for (int i = 0; i <= qSensors; i++)
			simulationArea->Controls->Remove(sensors[i]);

		qSensors = Convert::ToInt32(qSensorsNumeric->Value);

		if(qSensors>0)
		{
			System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox();

			for (int i = 0; i < qSensors; i++)
			{
				sensors[i] = gcnew System::Windows::Forms::PictureBox();
				sensors[i]->Image = Image::FromFile("sensor.png");
				sensors[i]->Size = System::Drawing::Size(41, 40);
				sensors[i]->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
				sensors[i]->BackColor = System::Drawing::Color::Transparent;
				simulationArea->Controls->Add(sensors[i]);
			}

			switch (Convert::ToInt32(qSensorsNumeric->Value))
			{
				case 1:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width / 2), Math::Round(simulationArea->Height / 2));
					break;

				case 2:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.2), Math::Round(simulationArea->Height / 2));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.8), Math::Round(simulationArea->Height / 2));
					break;

				case 3:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height / 2));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.50), Math::Round(simulationArea->Height / 2));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height / 2));
					break;

				case 4:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.25));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.75));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.25));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.75));
					break;

				case 5:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.20));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.80));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.20));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.80));
					sensors[4]->Location = System::Drawing::Point(Math::Round(simulationArea->Width / 2), Math::Round(simulationArea->Height / 2));
					break;

				case 6:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.25));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.50), Math::Round(simulationArea->Height*0.25));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.25));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.75));
					sensors[4]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.50), Math::Round(simulationArea->Height*0.75));
					sensors[5]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.75));
					break;

				case 7:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.25));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.50), Math::Round(simulationArea->Height*0.25));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.25));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.25), Math::Round(simulationArea->Height*0.75));
					sensors[4]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.50), Math::Round(simulationArea->Height*0.75));
					sensors[5]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.75), Math::Round(simulationArea->Height*0.75));
					sensors[6]->Location = System::Drawing::Point(Math::Round(simulationArea->Width / 2), Math::Round(simulationArea->Height / 2));
					break;

				case 8:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.20));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.40));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.60));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.80));
					sensors[4]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.20));
					sensors[5]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.40));
					sensors[6]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.60));
					sensors[7]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.80));
					break;

				case 9:
					sensors[0]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.20));
					sensors[1]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.40));
					sensors[2]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.60));
					sensors[3]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.20), Math::Round(simulationArea->Height*0.80));
					sensors[4]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.20));
					sensors[5]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.40));
					sensors[6]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.60));
					sensors[7]->Location = System::Drawing::Point(Math::Round(simulationArea->Width*0.80), Math::Round(simulationArea->Height*0.80));
					sensors[8]->Location = System::Drawing::Point(Math::Round(simulationArea->Width / 2), Math::Round(simulationArea->Height / 2));
					break;

			}

			output->Text += _getTime() + "Simulation set to " + qSensorsNumeric->Value.ToString() + " Sensors" + CRLF;
			simulationArea->Refresh();
		}
		
	}

	private: System::Void bCopy_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		output->SelectAll();
		output->Copy();
		output->Text += _getTime() + "Output text to clipboard OK" + CRLF;
	}
			 
	
	private: System::Void outTrackUAVs_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		outTrackUAVs->SelectionStart = outTrackUAVs->TextLength;
		outTrackUAVs->ScrollToCaret();
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (cbBackGround->Checked)
			simulationArea->BackgroundImage = Image::FromFile("background.png");
		else
			simulationArea->BackgroundImage = nullptr;

	}
	private: System::Void cbTrackUAVs_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}



private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

	if (cbTrackUAVs->Checked)
	{
		for (int i = 0; i < qUAVs; i++)
			outTrackUAVs->Text += i + ";" + uavs[i]->Location.X + ";" + uavs[i]->Location.Y + CRLF;
	}

}
private: System::Void VeloUAV_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	output->Text += _getTime() + "Velocity changed to " + VeloUAV->Value + " m/s" + CRLF;
}
}; //não mexer abaixo disso !!! }; }
} //não mexer abaixo disso !!! }; }
