#pragma once
#include "adIndexForm.h" //引入管理员以及学院端的首页窗体文件
#include "adIndexForm_v4.h"

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// LoginForm 摘要
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::Panel^  loginPanel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  stuRadio;

	private: System::Windows::Forms::RadioButton^  adRadio;

	private: System::Windows::Forms::TextBox^  psTbox;

	private: System::Windows::Forms::TextBox^  accTbox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::LinkLabel^  supLink;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->loginPanel = (gcnew System::Windows::Forms::Panel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->stuRadio = (gcnew System::Windows::Forms::RadioButton());
			this->adRadio = (gcnew System::Windows::Forms::RadioButton());
			this->psTbox = (gcnew System::Windows::Forms::TextBox());
			this->accTbox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->supLink = (gcnew System::Windows::Forms::LinkLabel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->loginPanel->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(293, 293);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// loginPanel
			// 
			this->loginPanel->Controls->Add(this->groupBox1);
			this->loginPanel->Controls->Add(this->label1);
			this->loginPanel->Location = System::Drawing::Point(336, 12);
			this->loginPanel->Name = L"loginPanel";
			this->loginPanel->Size = System::Drawing::Size(322, 219);
			this->loginPanel->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->stuRadio);
			this->groupBox1->Controls->Add(this->adRadio);
			this->groupBox1->Controls->Add(this->psTbox);
			this->groupBox1->Controls->Add(this->accTbox);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->groupBox1->Location = System::Drawing::Point(29, 46);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(273, 169);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"请登录";
			// 
			// stuRadio
			// 
			this->stuRadio->AutoSize = true;
			this->stuRadio->Location = System::Drawing::Point(155, 127);
			this->stuRadio->Name = L"stuRadio";
			this->stuRadio->Size = System::Drawing::Size(67, 23);
			this->stuRadio->TabIndex = 5;
			this->stuRadio->TabStop = true;
			this->stuRadio->Text = L"学生";
			this->stuRadio->UseVisualStyleBackColor = true;
			// 
			// adRadio
			// 
			this->adRadio->AutoSize = true;
			this->adRadio->Location = System::Drawing::Point(41, 127);
			this->adRadio->Name = L"adRadio";
			this->adRadio->Size = System::Drawing::Size(87, 23);
			this->adRadio->TabIndex = 4;
			this->adRadio->TabStop = true;
			this->adRadio->Text = L"管理员";
			this->adRadio->UseVisualStyleBackColor = true;
			// 
			// psTbox
			// 
			this->psTbox->Location = System::Drawing::Point(72, 86);
			this->psTbox->Name = L"psTbox";
			this->psTbox->Size = System::Drawing::Size(182, 29);
			this->psTbox->TabIndex = 3;
			this->psTbox->UseSystemPasswordChar = true;
			// 
			// accTbox
			// 
			this->accTbox->Location = System::Drawing::Point(72, 40);
			this->accTbox->Name = L"accTbox";
			this->accTbox->Size = System::Drawing::Size(182, 29);
			this->accTbox->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 89);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(59, 19);
			this->label3->TabIndex = 1;
			this->label3->Text = L"密 码";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 19);
			this->label2->TabIndex = 0;
			this->label2->Text = L"账 号";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"楷体", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::Gray;
			this->label1->Location = System::Drawing::Point(25, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(185, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"欢迎使用本系统";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"楷体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(382, 237);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(237, 41);
			this->button1->TabIndex = 2;
			this->button1->Text = L"登  录";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoginForm::button1_Click);
			// 
			// supLink
			// 
			this->supLink->ActiveLinkColor = System::Drawing::Color::Black;
			this->supLink->AutoSize = true;
			this->supLink->LinkBehavior = System::Windows::Forms::LinkBehavior::NeverUnderline;
			this->supLink->LinkColor = System::Drawing::Color::Black;
			this->supLink->Location = System::Drawing::Point(263, 300);
			this->supLink->Name = L"supLink";
			this->supLink->Size = System::Drawing::Size(137, 12);
			this->supLink->TabIndex = 3;
			this->supLink->TabStop = true;
			this->supLink->Text = L"技术支持: 华南理工大学";
			this->supLink->VisitedLinkColor = System::Drawing::Color::Black;
			this->supLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &LoginForm::supLink_LinkClicked);
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(670, 317);
			this->Controls->Add(this->supLink);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->loginPanel);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->ShowIcon = false;
			this->Text = L"教务管理系统";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->loginPanel->ResumeLayout(false);
			this->loginPanel->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		//验证用户的登录信息
		String ^accStr = accTbox->Text;
		String  ^psStr = psTbox->Text;
		char name[20];
		char passwd[20];
		sprintf(name, "%s", accStr);
		sprintf(passwd, "%s", psStr);
		Storage storage1;
		if (adRadio->Checked) {
			//MessageBox::Show("欢迎教师登录");
			if (storage1.login(0, name, passwd)) {
				//生成新窗口
				adIndexForm_v4 ^ ad = gcnew adIndexForm_v4(accTbox->Text);
				this->Visible = false;
				ad->Show();
				//Application::OpenForms["adIndexForm"]

			}
			else {
				MessageBox::Show("账户名或者密码错误，请查账");
			}
		}
		if (stuRadio->Checked) {
			MessageBox::Show("学生你好，欢迎登陆");
			//查询数据库，进行登陆
		}
	}
	private: System::Void supLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
		try {
			Diagnostics::Process::Start("http://202.38.194.240:8000/cs/szdw/js/xn/17bvfdd0eicq1.xhtml");
		}
		catch (Win32Exception ^) {
			MessageBox::Show("some error exists");
		}
	}
	};
}
