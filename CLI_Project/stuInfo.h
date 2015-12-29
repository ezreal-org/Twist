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

	/// <summary>
	/// stuInfo 摘要
	/// </summary>
	public ref class stuInfo : public System::Windows::Forms::Form
	{
	public:
		stuInfo(LoginInfo ^login)
		{
			this->thisLogin = login;
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~stuInfo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  showInfoPanel;
	protected:
	public: System::Windows::Forms::TabControl^  tabControl1;
	private:
	private: System::Windows::Forms::TabPage^  basicInfo;
	public:
	private: System::Windows::Forms::PictureBox^  photo;
	private: System::Windows::Forms::Button^  lookButton;
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
	private: System::Windows::Forms::TabPage^  addInfo;
	private: System::Windows::Forms::RichTextBox^  noteText;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::CheckBox^  isTalent;
	private: System::Windows::Forms::MaskedTextBox^  IDMaskedTextBox;
	private: System::Windows::Forms::Label^  label6;
	private: LoginInfo^ thisLogin;
	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->showInfoPanel = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->basicInfo = (gcnew System::Windows::Forms::TabPage());
			this->photo = (gcnew System::Windows::Forms::PictureBox());
			this->lookButton = (gcnew System::Windows::Forms::Button());
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
			this->addInfo = (gcnew System::Windows::Forms::TabPage());
			this->noteText = (gcnew System::Windows::Forms::RichTextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->isTalent = (gcnew System::Windows::Forms::CheckBox());
			this->IDMaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->showInfoPanel->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->basicInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->photo))->BeginInit();
			this->addInfo->SuspendLayout();
			this->SuspendLayout();
			// 
			// showInfoPanel
			// 
			this->showInfoPanel->Controls->Add(this->tabControl1);
			this->showInfoPanel->Location = System::Drawing::Point(18, 4);
			this->showInfoPanel->Name = L"showInfoPanel";
			this->showInfoPanel->Size = System::Drawing::Size(610, 192);
			this->showInfoPanel->TabIndex = 3;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->basicInfo);
			this->tabControl1->Controls->Add(this->addInfo);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tabControl1->Location = System::Drawing::Point(3, 14);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(585, 173);
			this->tabControl1->TabIndex = 1;
			// 
			// basicInfo
			// 
			this->basicInfo->Controls->Add(this->photo);
			this->basicInfo->Controls->Add(this->lookButton);
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
			this->basicInfo->Size = System::Drawing::Size(577, 143);
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
			// lookButton
			// 
			this->lookButton->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lookButton->Location = System::Drawing::Point(374, 95);
			this->lookButton->Name = L"lookButton";
			this->lookButton->Size = System::Drawing::Size(75, 31);
			this->lookButton->TabIndex = 22;
			this->lookButton->Text = L"浏 览";
			this->lookButton->UseVisualStyleBackColor = true;
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
			this->addInfo->Size = System::Drawing::Size(577, 143);
			this->addInfo->TabIndex = 1;
			this->addInfo->Text = L"附加信息";
			this->addInfo->UseVisualStyleBackColor = true;
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
			// 
			// stuInfo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(644, 214);
			this->Controls->Add(this->showInfoPanel);
			this->Name = L"stuInfo";
			this->Text = L"个人信息";
			this->Load += gcnew System::EventHandler(this, &stuInfo::stuInfo_Load);
			this->showInfoPanel->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->basicInfo->ResumeLayout(false);
			this->basicInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->photo))->EndInit();
			this->addInfo->ResumeLayout(false);
			this->addInfo->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void stuInfo_Load(System::Object^  sender, System::EventArgs^  e) {
		bool status = false;
		this->nameTbox->Enabled = status;
		this->birthPicker->Enabled = status;
		this->genderCombo->Enabled = status;
		this->noTbox->Enabled = status;
		this->picTbox->Enabled = status;
		this->lookButton->Enabled = status;
		this->IDMaskedTextBox->Enabled = status;
		this->isTalent->Enabled = status;
		this->noteText->Enabled = status;

		
		SchoolMember* pm1;
		Storage storage1;
		char id[20];
		sprintf(id, "%s",this->thisLogin->getId() );
		//pm1 = storage1.readSchoolMemberInfo(path);
		pm1 = storage1.readSchoolMemberInfoDB(id);
		//更新panel中的个人信息,用string中转
		string str = pm1->getName(); //姓名
		this->nameTbox->Text = gcnew String(str.c_str());
		str = pm1->getPicpath(); //图片路径
		this->picTbox->Text = gcnew String(str.c_str());
		str = pm1->getExtraInfo(); //附加信息
		this->noteText->Text = gcnew String(str.c_str());
		str = pm1->getId();   //学号
		this->noTbox->Text = gcnew String(str.c_str());
		str = pm1->getIdNumber();  //身份证号
		this->IDMaskedTextBox->Text = gcnew String(str.c_str());
		//日期
		char birBuf[5]; //string没有重载+int，用sprint函数用birBuf中转
		int year, month, day;
		pm1->getBirthday(year, month, day);
		sprintf(birBuf, "%d", year);
		str = birBuf;
		str += "年";
		sprintf(birBuf, "%d", month);
		str += birBuf;
		str += "月";
		sprintf(birBuf, "%d", day);
		str += birBuf;
		str += "日";
		this->birthPicker->Text = gcnew String(str.c_str());
		this->isTalent->Checked = pm1->getIsTalent(); //是否特长
		this->genderCombo->SelectedIndex = pm1->getSex(); //性别
		
	}
};
}
