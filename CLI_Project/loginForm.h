#pragma once

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// loginForm 摘要
	/// </summary>
	public ref class loginForm : public System::Windows::Forms::Form
	{
	public:
		loginForm(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~loginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  loginPanel;
	private: System::Windows::Forms::Label^  welLabel;
	protected:


	protected:



	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  loginGroupBox;

	private: System::Windows::Forms::RadioButton^  stuRadio;

	private: System::Windows::Forms::RadioButton^  teaRadio;

	private: System::Windows::Forms::RadioButton^  admRadio;

	private: System::Windows::Forms::TextBox^  psBox;

	private: System::Windows::Forms::TextBox^  AccBox;
	private: System::Windows::Forms::Label^  psLabel;
	private: System::Windows::Forms::Label^  accLabel;





	private: System::Windows::Forms::PictureBox^  schLogo;
	private: System::Windows::Forms::LinkLabel^  tecSupportLink;




	protected:


	protected:














	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(loginForm::typeid));
			this->loginPanel = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->loginGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stuRadio = (gcnew System::Windows::Forms::RadioButton());
			this->teaRadio = (gcnew System::Windows::Forms::RadioButton());
			this->admRadio = (gcnew System::Windows::Forms::RadioButton());
			this->psBox = (gcnew System::Windows::Forms::TextBox());
			this->AccBox = (gcnew System::Windows::Forms::TextBox());
			this->psLabel = (gcnew System::Windows::Forms::Label());
			this->accLabel = (gcnew System::Windows::Forms::Label());
			this->welLabel = (gcnew System::Windows::Forms::Label());
			this->schLogo = (gcnew System::Windows::Forms::PictureBox());
			this->tecSupportLink = (gcnew System::Windows::Forms::LinkLabel());
			this->loginPanel->SuspendLayout();
			this->loginGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->schLogo))->BeginInit();
			this->SuspendLayout();
			// 
			// loginPanel
			// 
			this->loginPanel->BackColor = System::Drawing::SystemColors::Window;
			resources->ApplyResources(this->loginPanel, L"loginPanel");
			this->loginPanel->Controls->Add(this->button1);
			this->loginPanel->Controls->Add(this->loginGroupBox);
			this->loginPanel->Controls->Add(this->welLabel);
			this->loginPanel->Name = L"loginPanel";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			resources->ApplyResources(this->button1, L"button1");
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button1->Name = L"button1";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &loginForm::button1_Click);
			// 
			// loginGroupBox
			// 
			this->loginGroupBox->Controls->Add(this->stuRadio);
			this->loginGroupBox->Controls->Add(this->teaRadio);
			this->loginGroupBox->Controls->Add(this->admRadio);
			this->loginGroupBox->Controls->Add(this->psBox);
			this->loginGroupBox->Controls->Add(this->AccBox);
			this->loginGroupBox->Controls->Add(this->psLabel);
			this->loginGroupBox->Controls->Add(this->accLabel);
			resources->ApplyResources(this->loginGroupBox, L"loginGroupBox");
			this->loginGroupBox->ForeColor = System::Drawing::Color::Gray;
			this->loginGroupBox->Name = L"loginGroupBox";
			this->loginGroupBox->TabStop = false;
			// 
			// stuRadio
			// 
			resources->ApplyResources(this->stuRadio, L"stuRadio");
			this->stuRadio->Name = L"stuRadio";
			this->stuRadio->TabStop = true;
			this->stuRadio->UseVisualStyleBackColor = true;
			// 
			// teaRadio
			// 
			resources->ApplyResources(this->teaRadio, L"teaRadio");
			this->teaRadio->Name = L"teaRadio";
			this->teaRadio->TabStop = true;
			this->teaRadio->UseVisualStyleBackColor = true;
			this->teaRadio->CheckedChanged += gcnew System::EventHandler(this, &loginForm::radioButton2_CheckedChanged);
			// 
			// admRadio
			// 
			resources->ApplyResources(this->admRadio, L"admRadio");
			this->admRadio->Name = L"admRadio";
			this->admRadio->TabStop = true;
			this->admRadio->UseVisualStyleBackColor = true;
			// 
			// psBox
			// 
			resources->ApplyResources(this->psBox, L"psBox");
			this->psBox->Name = L"psBox";
			// 
			// AccBox
			// 
			resources->ApplyResources(this->AccBox, L"AccBox");
			this->AccBox->Name = L"AccBox";
			// 
			// psLabel
			// 
			resources->ApplyResources(this->psLabel, L"psLabel");
			this->psLabel->Name = L"psLabel";
			// 
			// accLabel
			// 
			resources->ApplyResources(this->accLabel, L"accLabel");
			this->accLabel->Name = L"accLabel";
			// 
			// welLabel
			// 
			resources->ApplyResources(this->welLabel, L"welLabel");
			this->welLabel->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->welLabel->Name = L"welLabel";
			this->welLabel->Click += gcnew System::EventHandler(this, &loginForm::label1_Click);
			// 
			// schLogo
			// 
			resources->ApplyResources(this->schLogo, L"schLogo");
			this->schLogo->Name = L"schLogo";
			this->schLogo->TabStop = false;
			// 
			// tecSupportLink
			// 
			resources->ApplyResources(this->tecSupportLink, L"tecSupportLink");
			this->tecSupportLink->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->tecSupportLink->LinkBehavior = System::Windows::Forms::LinkBehavior::NeverUnderline;
			this->tecSupportLink->LinkColor = System::Drawing::Color::Black;
			this->tecSupportLink->Name = L"tecSupportLink";
			this->tecSupportLink->TabStop = true;
			this->tecSupportLink->VisitedLinkColor = System::Drawing::Color::Gray;
			this->tecSupportLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &loginForm::linkLabel1_LinkClicked);
			// 
			// loginForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->Controls->Add(this->tecSupportLink);
			this->Controls->Add(this->schLogo);
			this->Controls->Add(this->loginPanel);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"loginForm";
			this->ShowIcon = false;
			this->Load += gcnew System::EventHandler(this, &loginForm::loginForm_Load);
			this->loginPanel->ResumeLayout(false);
			this->loginPanel->PerformLayout();
			this->loginGroupBox->ResumeLayout(false);
			this->loginGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->schLogo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void 打开ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show("hello");
	}
	private: System::Void loginForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
		try {
			Diagnostics::Process::Start("http://www.scut.edu.cn");
		}
		catch (Exception ^ ex) {
			MessageBox::Show("some error exists");
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^accStr = AccBox->Text;
		String ^psStr = psBox->Text;



		//使用文件或者数据库验证账户密码
		if (accStr->Equals("sa") && psStr->Equals("123")) {
			MessageBox::Show("welcome to this system ");
		}
		else {
			MessageBox::Show("There are some wrongs in your account or password!");
		}
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}

