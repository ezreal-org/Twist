#pragma once
#include "addStu.h"
#include "stuList.h"
#include "stuList_c4.h"

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// adIndexForm 晡猁
	/// </summary>
	public ref class adIndexForm : public System::Windows::Forms::Form
	{
	public:
		adIndexForm(String^ loginName)
		{
			this->loginName = loginName;
			InitializeComponent();
			//
			//TODO:  婓森揭氝樓凳婖滲杅測鎢
			//
		}

	protected:
		/// <summary>
		/// ?燴垀衄淏婓妏蚚腔訧埭﹝
		/// </summary>
		~adIndexForm()
		{
			if (components)
			{
			//	delete components;
			}
		}
	private: System::Windows::Forms::Label^  welLabel;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: String^ loginName;
	protected:

	protected:

	private:
		/// <summary>
		/// 斛剒腔扢數?曹講﹝
		/// </summary>
		System::ComponentModel::Container ^components;


		//暮翹絞?腔蚚誧
	public:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 扢數?盓厥垀剒腔源楊 - 祥猁党蜊
		/// 妏蚚測鎢晤憮?党蜊森源楊腔囀?﹝
		/// </summary>
		void InitializeComponent(void)
		{
			this->welLabel = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// welLabel
			// 
			this->welLabel->AutoSize = true;
			this->welLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->welLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->welLabel->Location = System::Drawing::Point(22, 13);
			this->welLabel->Name = L"welLabel";
			this->welLabel->Size = System::Drawing::Size(48, 24);
			this->welLabel->TabIndex = 0;
			this->welLabel->Text = L"欢迎";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(26, 72);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 36);
			this->button1->TabIndex = 1;
			this->button1->Text = L"添加学生";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &adIndexForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->button2->Location = System::Drawing::Point(26, 149);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(142, 35);
			this->button2->TabIndex = 2;
			this->button2->Text = L"班级管理";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &adIndexForm::button2_Click);
			// 
			// adIndexForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(732, 350);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->welLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"adIndexForm";
			this->ShowIcon = false;
			this->Text = L"教务管理系统";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &adIndexForm::adIndexForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &adIndexForm::adIndexForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		addStu ^adone = gcnew addStu();
		adone->Show();
	}
	private: System::Void adIndexForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		Application::OpenForms["loginForm1"]->Close();

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		if (Application::OpenForms["stuList"] == nullptr) {
			//stuList ^showList = gcnew stuList();
			//showList->Show();
			stuList_c4 ^list_c4 = gcnew stuList_c4();
			list_c4->Show();
		}
		else {
			//窗体已经存在， 应该把它显示出来，而不是从新定义一个

			Application::OpenForms["stuList"]->Show();

		}


	}
	
private: System::Void adIndexForm_Load(System::Object^  sender, System::EventArgs^  e) {
	this->welLabel->Text = "欢迎 "+loginName;
}
};
}
