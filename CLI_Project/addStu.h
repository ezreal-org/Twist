#pragma once
#include "storage.h"
#include "memberInfo.h"

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Runtime::InteropServices;
	/// <summary>
	/// addStu 晡猁
	/// </summary>
	public ref class addStu : public System::Windows::Forms::Form
	{
	public:
		addStu(void)
		{
			InitializeComponent();
			//
			//TODO:  婓森揭氝樓凳婖滲杅測鎢
			//
		}

	protected:
		/// <summary>
		/// ?燴垀衄淏婓妏蚚腔訧埭﹝
		/// </summary>
		~addStu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabPage^  addInfo;
	protected:
	private: System::Windows::Forms::RichTextBox^  noteText;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  isTalent;
	private: System::Windows::Forms::MaskedTextBox^  IDMaskedTextBox;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TabPage^  basicInfo;
	private: System::Windows::Forms::PictureBox^  photo;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  picTbox;
	private: System::Windows::Forms::TextBox^  noTbox;
	private: System::Windows::Forms::TextBox^  nameTbox;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  genderCombo;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::DateTimePicker^  birthPicker;
	private: System::Windows::Forms::Label^  label1;
	public: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::OpenFileDialog^  picBrower;

	private:
		/// <summary>
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// </summary>
		void InitializeComponent(void)
		{
			this->addInfo = (gcnew System::Windows::Forms::TabPage());
			this->noteText = (gcnew System::Windows::Forms::RichTextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->isTalent = (gcnew System::Windows::Forms::CheckBox());
			this->IDMaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->basicInfo = (gcnew System::Windows::Forms::TabPage());
			this->photo = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->picTbox = (gcnew System::Windows::Forms::TextBox());
			this->noTbox = (gcnew System::Windows::Forms::TextBox());
			this->nameTbox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->genderCombo = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->birthPicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->picBrower = (gcnew System::Windows::Forms::OpenFileDialog());
			this->addInfo->SuspendLayout();
			this->basicInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->photo))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// addInfo
			// 
			this->addInfo->Controls->Add(this->noteText);
			this->addInfo->Controls->Add(this->label7);
			this->addInfo->Controls->Add(this->isTalent);
			this->addInfo->Controls->Add(this->IDMaskedTextBox);
			this->addInfo->Controls->Add(this->label6);
			this->addInfo->Location = System::Drawing::Point(4, 26);
			this->addInfo->Name = L"addInfo";
			this->addInfo->Padding = System::Windows::Forms::Padding(3);
			this->addInfo->Size = System::Drawing::Size(577, 135);
			this->addInfo->TabIndex = 1;
			this->addInfo->Text = L"附加信息";
			this->addInfo->UseVisualStyleBackColor = true;
			this->addInfo->Click += gcnew System::EventHandler(this, &addStu::addInfo_Click);
			// 
			// noteText
			// 
			this->noteText->Location = System::Drawing::Point(87, 41);
			this->noteText->Name = L"noteText";
			this->noteText->Size = System::Drawing::Size(465, 88);
			this->noteText->TabIndex = 4;
			this->noteText->Text = L"";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(9, 58);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 16);
			this->label7->TabIndex = 3;
			this->label7->Text = L"备注信息";
			// 
			// isTalent
			// 
			this->isTalent->AutoSize = true;
			this->isTalent->Location = System::Drawing::Point(317, 11);
			this->isTalent->Name = L"isTalent";
			this->isTalent->Size = System::Drawing::Size(107, 20);
			this->isTalent->TabIndex = 2;
			this->isTalent->Text = L"是否特长生";
			this->isTalent->UseVisualStyleBackColor = true;
			// 
			// IDMaskedTextBox
			// 
			this->IDMaskedTextBox->Location = System::Drawing::Point(100, 6);
			this->IDMaskedTextBox->Mask = L"000000-00000000-000A";
			this->IDMaskedTextBox->Name = L"IDMaskedTextBox";
			this->IDMaskedTextBox->Size = System::Drawing::Size(173, 26);
			this->IDMaskedTextBox->TabIndex = 1;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 15);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(72, 16);
			this->label6->TabIndex = 0;
			this->label6->Text = L"身份证号";
			this->label6->Click += gcnew System::EventHandler(this, &addStu::label6_Click);
			// 
			// basicInfo
			// 
			this->basicInfo->Controls->Add(this->photo);
			this->basicInfo->Controls->Add(this->button1);
			this->basicInfo->Controls->Add(this->picTbox);
			this->basicInfo->Controls->Add(this->noTbox);
			this->basicInfo->Controls->Add(this->nameTbox);
			this->basicInfo->Controls->Add(this->label5);
			this->basicInfo->Controls->Add(this->label4);
			this->basicInfo->Controls->Add(this->genderCombo);
			this->basicInfo->Controls->Add(this->label3);
			this->basicInfo->Controls->Add(this->label2);
			this->basicInfo->Controls->Add(this->birthPicker);
			this->basicInfo->Controls->Add(this->label1);
			this->basicInfo->Location = System::Drawing::Point(4, 26);
			this->basicInfo->Name = L"basicInfo";
			this->basicInfo->Padding = System::Windows::Forms::Padding(3);
			this->basicInfo->Size = System::Drawing::Size(577, 135);
			this->basicInfo->TabIndex = 0;
			this->basicInfo->Text = L"基本信息";
			this->basicInfo->UseVisualStyleBackColor = true;
			// 
			// photo
			// 
			this->photo->Location = System::Drawing::Point(475, 15);
			this->photo->Name = L"photo";
			this->photo->Size = System::Drawing::Size(89, 103);
			this->photo->TabIndex = 23;
			this->photo->TabStop = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(374, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 31);
			this->button1->TabIndex = 22;
			this->button1->Text = L"浏 览";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &addStu::button1_Click);
			// 
			// picTbox
			// 
			this->picTbox->Location = System::Drawing::Point(94, 95);
			this->picTbox->Name = L"picTbox";
			this->picTbox->Size = System::Drawing::Size(262, 26);
			this->picTbox->TabIndex = 21;
			// 
			// noTbox
			// 
			this->noTbox->Location = System::Drawing::Point(308, 53);
			this->noTbox->Name = L"noTbox";
			this->noTbox->Size = System::Drawing::Size(152, 26);
			this->noTbox->TabIndex = 19;
			// 
			// nameTbox
			// 
			this->nameTbox->Location = System::Drawing::Point(60, 15);
			this->nameTbox->Name = L"nameTbox";
			this->nameTbox->Size = System::Drawing::Size(123, 26);
			this->nameTbox->TabIndex = 13;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 98);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(72, 16);
			this->label5->TabIndex = 20;
			this->label5->Text = L"头像信息";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(250, 59);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 16);
			this->label4->TabIndex = 18;
			this->label4->Text = L"学号";
			// 
			// genderCombo
			// 
			this->genderCombo->FormattingEnabled = true;
			this->genderCombo->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"男", L"女" });
			this->genderCombo->Location = System::Drawing::Point(60, 53);
			this->genderCombo->Name = L"genderCombo";
			this->genderCombo->Size = System::Drawing::Size(121, 24);
			this->genderCombo->TabIndex = 17;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 59);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 16);
			this->label3->TabIndex = 16;
			this->label3->Text = L"性别";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(214, 18);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 16);
			this->label2->TabIndex = 15;
			this->label2->Text = L"出身日期";
			// 
			// birthPicker
			// 
			this->birthPicker->Location = System::Drawing::Point(308, 14);
			this->birthPicker->Name = L"birthPicker";
			this->birthPicker->Size = System::Drawing::Size(152, 26);
			this->birthPicker->TabIndex = 14;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 16);
			this->label1->TabIndex = 12;
			this->label1->Text = L"姓名";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->basicInfo);
			this->tabControl1->Controls->Add(this->addInfo);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(585, 165);
			this->tabControl1->TabIndex = 0;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(143, 186);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"重 置";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &addStu::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(297, 186);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"确 定";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &addStu::button3_Click);
			// 
			// picBrower
			// 
			this->picBrower->FileName = L"openFileDialog1";
			// 
			// addStu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(608, 221);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->tabControl1);
			this->Name = L"addStu";
			this->Text = L"学生注册";
			this->addInfo->ResumeLayout(false);
			this->addInfo->PerformLayout();
			this->basicInfo->ResumeLayout(false);
			this->basicInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->photo))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void addInfo_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//笭离陓洘
		this->nameTbox->Text = "";
		this->noTbox->Text = "";
		this->picTbox->Text = "";
		this->IDMaskedTextBox->Text = "";
		this->isTalent->Checked = false;
		this->noteText->Text = "";
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//粟堤 恅璃銡擬遺
		//恁寁芞?綴ㄛ奻換ㄛ?綴涴硐芛砉峈蜆繚噤˙
		picBrower->ShowDialog();
		picTbox->Text = picBrower->FileName;
		photo->ImageLocation = picTbox->Text;

	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		//枑蝠垀衄杅擂迡恅紫ㄛ?綴悵湔
		String ^name = nameTbox->Text;
		String ^birthStr = birthPicker->Text;
		int  gender = genderCombo->SelectedIndex;
		String ^ stuNo = noTbox->Text;
		String ^picPath = picTbox->Text;
		String ^idNo = IDMaskedTextBox->Text;
		idNo = idNo->Replace("-", "");
		String ^noteStr = noteText->Text;
		bool isTal = isTalent->Checked;
		int year, month, day;

		DateTime t;
		t = DateTime::Parse(birthStr);

		year = Convert::ToInt16(t.Year.ToString());
		month = Convert::ToInt16(t.Month.ToString());
		day = Convert::ToInt16(t.Day.ToString());

		Storage storage1;
		SchoolMember* pm1 = new SchoolMember();
		pm1->setId((char*)(Marshal::StringToHGlobalAnsi(stuNo)).ToPointer());
		pm1->setName((char*)(Marshal::StringToHGlobalAnsi(name)).ToPointer());
		pm1->setSex(gender);
		pm1->setBirthday(year, month, day);
		pm1->setIdNumber((char*)(Marshal::StringToHGlobalAnsi(idNo)).ToPointer());
		pm1->setExtraInfo((char*)(Marshal::StringToHGlobalAnsi(noteStr)).ToPointer());
		pm1->setIsTalent(isTal);
		pm1->setPicpath((char*)(Marshal::StringToHGlobalAnsi(picPath)).ToPointer());
		//storage1.writeSchoolMemberInfo(pm1);
		storage1.writeSchoolMemberInfoDB(pm1);
		delete pm1;


	}
	private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void button2_Click_2(System::Object^  sender, System::EventArgs^  e) {
	}


	};
}
