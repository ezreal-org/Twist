#pragma once
#include "addStu.h"
#include "stuList.h"
#include "stuList_c4.h"
#include "HelpInfo.h"
#include "updatePasswd.h"
#include "memberInfo.h"
#include "staticticChart.h"

namespace ManagementSystemV5 {

#pragma once
		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Collections;
		using namespace System::Windows::Forms;
		using namespace System::Data;
		using namespace System::Drawing;

		/// <summary>
		/// adFormNew ժҪ
		/// </summary>
		public ref class adIndexForm_v4 : public System::Windows::Forms::Form
		{
		public:
			adIndexForm_v4(LoginInfo^ login)
			{
				InitializeComponent();
				//
				//TODO:  �ڴ˴���ӹ��캯������
				//
				//this->name = name;
				this->thisLogin = login;
				timer1->Start();
				this->IsMdiContainer = TRUE;
				this->StartPosition = FormStartPosition::CenterScreen;
			}

		protected:
			/// <summary>
			/// ������������ʹ�õ���Դ��
			/// </summary>
			~adIndexForm_v4()
			{
				if (components)
				{
					delete components;
				}
			}
		private: String^ name;
		private: System::Windows::Forms::MenuStrip^  stuMana;
		protected:
		private: System::Windows::Forms::ToolStripMenuItem^  ѧ������ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ����ע��ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ѧ������ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ����ѧ��ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  �޸�ѧ����ϢToolStripMenuItem;
		private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		private: System::Windows::Forms::ToolStripMenuItem^  ����˵��ToolStripMenuItem;
		private: System::Windows::Forms::StatusStrip^  statusStrip1;
		private: System::Windows::Forms::ToolStripStatusLabel^  NowData;
		private: System::Windows::Forms::ToolStripMenuItem^  ��Ϣ����ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  �޸�����ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ��ѯ������ϢToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ������Ϣ����ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ������Ϣ����ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  ����ϵͳToolStripMenuItem;
		private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel2;
		private: System::Windows::Forms::ToolStripStatusLabel^  NowTime;
		private: System::Windows::Forms::Timer^  timer1;
		private: System::Windows::Forms::Label^  label1;
		private: System::ComponentModel::IContainer^  components;
		private: System::Windows::Forms::ToolStripMenuItem^  ѧ��ͳ��ToolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  ����ͳ��ToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  ʡ�ݷֲ�ToolStripMenuItem;
		private: LoginInfo ^thisLogin;
		private:
			/// <summary>
			/// ����������������
			/// </summary>


#pragma region Windows Form Designer generated code
			/// <summary>
			/// �����֧������ķ��� - ��Ҫ�޸�
			/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
			/// </summary>
			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				this->stuMana = (gcnew System::Windows::Forms::MenuStrip());
				this->��Ϣ����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->�޸�����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->��ѯ������ϢToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ѧ������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->����ע��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ѧ������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->����ѧ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->�޸�ѧ����ϢToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->����˵��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ѧ��ͳ��ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->����ͳ��ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->ʡ�ݷֲ�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->������Ϣ����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->������Ϣ����ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->����ϵͳToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				this->NowData = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->NowTime = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				this->label1 = (gcnew System::Windows::Forms::Label());
				this->stuMana->SuspendLayout();
				this->statusStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// stuMana
				// 
				this->stuMana->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12));
				this->stuMana->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
				this->stuMana->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					this->��Ϣ����ToolStripMenuItem,
						this->ѧ������ToolStripMenuItem, this->ѧ��ͳ��ToolStripMenuItem1, this->������Ϣ����ToolStripMenuItem
				});
				this->stuMana->Location = System::Drawing::Point(0, 0);
				this->stuMana->Name = L"stuMana";
				this->stuMana->Size = System::Drawing::Size(714, 29);
				this->stuMana->TabIndex = 0;
				this->stuMana->Text = L"menuStrip1";
				// 
				// ��Ϣ����ToolStripMenuItem
				// 
				this->��Ϣ����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					this->�޸�����ToolStripMenuItem,
						this->��ѯ������ϢToolStripMenuItem
				});
				this->��Ϣ����ToolStripMenuItem->Name = L"��Ϣ����ToolStripMenuItem";
				this->��Ϣ����ToolStripMenuItem->Size = System::Drawing::Size(86, 25);
				this->��Ϣ����ToolStripMenuItem->Text = L"��Ϣ����";
				// 
				// �޸�����ToolStripMenuItem
				// 
				this->�޸�����ToolStripMenuItem->Name = L"�޸�����ToolStripMenuItem";
				this->�޸�����ToolStripMenuItem->Size = System::Drawing::Size(176, 26);
				this->�޸�����ToolStripMenuItem->Text = L"�޸�����";
				this->�޸�����ToolStripMenuItem->Click += gcnew System::EventHandler(this, &adIndexForm_v4::�޸�����ToolStripMenuItem_Click);
				// 
				// ��ѯ������ϢToolStripMenuItem
				// 
				this->��ѯ������ϢToolStripMenuItem->Name = L"��ѯ������ϢToolStripMenuItem";
				this->��ѯ������ϢToolStripMenuItem->Size = System::Drawing::Size(176, 26);
				this->��ѯ������ϢToolStripMenuItem->Text = L"��ѯ������Ϣ";
				// 
				// ѧ������ToolStripMenuItem
				// 
				this->ѧ������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					this->����ע��ToolStripMenuItem,
						this->ѧ������ToolStripMenuItem, this->toolStripSeparator1, this->����˵��ToolStripMenuItem
				});
				this->ѧ������ToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Regular,
					System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
				this->ѧ������ToolStripMenuItem->Name = L"ѧ������ToolStripMenuItem";
				this->ѧ������ToolStripMenuItem->Size = System::Drawing::Size(86, 25);
				this->ѧ������ToolStripMenuItem->Text = L"ѧ������";
				// 
				// ����ע��ToolStripMenuItem
				// 
				this->����ע��ToolStripMenuItem->Name = L"����ע��ToolStripMenuItem";
				this->����ע��ToolStripMenuItem->Size = System::Drawing::Size(144, 26);
				this->����ע��ToolStripMenuItem->Text = L"����ע��";
				this->����ע��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &adIndexForm_v4::����ע��ToolStripMenuItem_Click);
				// 
				// ѧ������ToolStripMenuItem
				// 
				this->ѧ������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					this->����ѧ��ToolStripMenuItem,
						this->�޸�ѧ����ϢToolStripMenuItem
				});
				this->ѧ������ToolStripMenuItem->Name = L"ѧ������ToolStripMenuItem";
				this->ѧ������ToolStripMenuItem->Size = System::Drawing::Size(144, 26);
				this->ѧ������ToolStripMenuItem->Text = L"ѧ������";
				// 
				// ����ѧ��ToolStripMenuItem
				// 
				this->����ѧ��ToolStripMenuItem->Name = L"����ѧ��ToolStripMenuItem";
				this->����ѧ��ToolStripMenuItem->Size = System::Drawing::Size(176, 26);
				this->����ѧ��ToolStripMenuItem->Text = L"����ѧ��";
				this->����ѧ��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &adIndexForm_v4::����ѧ��ToolStripMenuItem_Click);
				// 
				// �޸�ѧ����ϢToolStripMenuItem
				// 
				this->�޸�ѧ����ϢToolStripMenuItem->Name = L"�޸�ѧ����ϢToolStripMenuItem";
				this->�޸�ѧ����ϢToolStripMenuItem->Size = System::Drawing::Size(176, 26);
				this->�޸�ѧ����ϢToolStripMenuItem->Text = L"�޸�ѧ����Ϣ";
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = L"toolStripSeparator1";
				this->toolStripSeparator1->Size = System::Drawing::Size(141, 6);
				// 
				// ����˵��ToolStripMenuItem
				// 
				this->����˵��ToolStripMenuItem->Name = L"����˵��ToolStripMenuItem";
				this->����˵��ToolStripMenuItem->Size = System::Drawing::Size(144, 26);
				this->����˵��ToolStripMenuItem->Text = L"����˵��";
				// 
				// ѧ��ͳ��ToolStripMenuItem1
				// 
				this->ѧ��ͳ��ToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					this->����ͳ��ToolStripMenuItem,
						this->ʡ�ݷֲ�ToolStripMenuItem
				});
				this->ѧ��ͳ��ToolStripMenuItem1->Name = L"ѧ��ͳ��ToolStripMenuItem1";
				this->ѧ��ͳ��ToolStripMenuItem1->Size = System::Drawing::Size(86, 25);
				this->ѧ��ͳ��ToolStripMenuItem1->Text = L"ѧ��ͳ��";
				// 
				// ����ͳ��ToolStripMenuItem
				// 
				this->����ͳ��ToolStripMenuItem->Name = L"����ͳ��ToolStripMenuItem";
				this->����ͳ��ToolStripMenuItem->Size = System::Drawing::Size(152, 26);
				this->����ͳ��ToolStripMenuItem->Text = L"���շֲ�";
				this->����ͳ��ToolStripMenuItem->Click += gcnew System::EventHandler(this, &adIndexForm_v4::����ͳ��ToolStripMenuItem_Click);
				// 
				// ʡ�ݷֲ�ToolStripMenuItem
				// 
				this->ʡ�ݷֲ�ToolStripMenuItem->Name = L"ʡ�ݷֲ�ToolStripMenuItem";
				this->ʡ�ݷֲ�ToolStripMenuItem->Size = System::Drawing::Size(144, 26);
				this->ʡ�ݷֲ�ToolStripMenuItem->Text = L"ʡ�ݷֲ�";
				// 
				// ������Ϣ����ToolStripMenuItem
				// 
				this->������Ϣ����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					this->������Ϣ����ToolStripMenuItem1,
						this->����ϵͳToolStripMenuItem
				});
				this->������Ϣ����ToolStripMenuItem->Name = L"������Ϣ����ToolStripMenuItem";
				this->������Ϣ����ToolStripMenuItem->Size = System::Drawing::Size(54, 25);
				this->������Ϣ����ToolStripMenuItem->Text = L"����";
				// 
				// ������Ϣ����ToolStripMenuItem1
				// 
				this->������Ϣ����ToolStripMenuItem1->Name = L"������Ϣ����ToolStripMenuItem1";
				this->������Ϣ����ToolStripMenuItem1->Size = System::Drawing::Size(176, 26);
				this->������Ϣ����ToolStripMenuItem1->Text = L"������Ϣ����";
				// 
				// ����ϵͳToolStripMenuItem
				// 
				this->����ϵͳToolStripMenuItem->Name = L"����ϵͳToolStripMenuItem";
				this->����ϵͳToolStripMenuItem->Size = System::Drawing::Size(176, 26);
				this->����ϵͳToolStripMenuItem->Text = L"����ϵͳ";
				this->����ϵͳToolStripMenuItem->Click += gcnew System::EventHandler(this, &adIndexForm_v4::����ϵͳToolStripMenuItem_Click);
				// 
				// statusStrip1
				// 
				this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					this->NowData, this->toolStripStatusLabel2,
						this->NowTime
				});
				this->statusStrip1->Location = System::Drawing::Point(0, 295);
				this->statusStrip1->Name = L"statusStrip1";
				this->statusStrip1->Size = System::Drawing::Size(714, 22);
				this->statusStrip1->TabIndex = 1;
				this->statusStrip1->Text = L"statusStrip1";
				this->statusStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &adIndexForm_v4::statusStrip1_ItemClicked);
				// 
				// NowData
				// 
				this->NowData->Name = L"NowData";
				this->NowData->Size = System::Drawing::Size(32, 17);
				this->NowData->Text = L"����";
				this->NowData->Click += gcnew System::EventHandler(this, &adIndexForm_v4::toolStripStatusLabel1_Click);
				// 
				// toolStripStatusLabel2
				// 
				this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
				this->toolStripStatusLabel2->Size = System::Drawing::Size(0, 17);
				// 
				// NowTime
				// 
				this->NowTime->Name = L"NowTime";
				this->NowTime->Size = System::Drawing::Size(32, 17);
				this->NowTime->Text = L"ʱ��";
				// 
				// timer1
				// 
				this->timer1->Tick += gcnew System::EventHandler(this, &adIndexForm_v4::timer1_Tick);
				// 
				// label1
				// 
				this->label1->AutoSize = true;
				this->label1->Font = (gcnew System::Drawing::Font(L"��Բ", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(134)));
				this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
					static_cast<System::Int32>(static_cast<System::Byte>(64)));
				this->label1->Location = System::Drawing::Point(557, 9);
				this->label1->Name = L"label1";
				this->label1->Size = System::Drawing::Size(0, 19);
				this->label1->TabIndex = 2;
				// 
				// adIndexForm_v4
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(714, 317);
				this->Controls->Add(this->label1);
				this->Controls->Add(this->statusStrip1);
				this->Controls->Add(this->stuMana);
				this->IsMdiContainer = true;
				this->MainMenuStrip = this->stuMana;
				this->MaximizeBox = false;
				this->MinimizeBox = false;
				this->Name = L"adIndexForm_v4";
				this->ShowIcon = false;
				this->Text = L"�������ϵͳ";
				this->Load += gcnew System::EventHandler(this, &adIndexForm_v4::adIndexForm_v4_Load);
				this->stuMana->ResumeLayout(false);
				this->stuMana->PerformLayout();
				this->statusStrip1->ResumeLayout(false);
				this->statusStrip1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion
		private: System::Void toolStripStatusLabel1_Click(System::Object^  sender, System::EventArgs^  e) {
		}
		private: System::Void statusStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
		}
		private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			DateTime monment = DateTime::Now;
			int year = monment.Year;
			int mon = monment.Month;
			int date = monment.Day;

			int h = monment.Hour;
			int m = monment.Minute;
			int s = monment.Second;

			String ^ dateStr = "��ǰʱ�䣺" + year.ToString() + "-" + mon.ToString() + "-" + date.ToString() + "  ";
			String ^ timeStr = (h % 12).ToString() + ":" + m.ToString() + ":" + s.ToString();
			this->NowData->Text = dateStr;
			this->NowTime->Text = timeStr;
		}
		private: System::Void ����ϵͳToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			HelpInfo ^help = gcnew HelpInfo();
			help->StartPosition = FormStartPosition::CenterScreen;
			help->Name = "help";
			help->Show();
		}
private: System::Void �޸�����ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//updatePasswd ^reset = gcnew updatePasswd(this->name);
	updatePasswd ^reset = gcnew updatePasswd(this->thisLogin);
	reset->Name = "resetPasswd";
	reset->MdiParent = this;
	reset->StartPosition = FormStartPosition::CenterParent;
	reset->WindowState = FormWindowState::Maximized;
	reset->Show();
}
private: System::Void ����ע��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	addStu ^ add = gcnew addStu();
	add->Name = "addStu";
	add->MdiParent = this;
	add->StartPosition = FormStartPosition::CenterParent;
	add->WindowState = FormWindowState::Maximized;
	add->Show();
}
private: System::Void ����ѧ��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	stuList_c4 ^list = gcnew stuList_c4();
	list->Name = "stuList";
	list->MdiParent = this;
	list->StartPosition = FormStartPosition::CenterParent;
	list->WindowState = FormWindowState::Maximized;
	list->Show();
}
private: System::Void adIndexForm_v4_Load(System::Object^  sender, System::EventArgs^  e) {
	this->label1->Text = "�� ӭ ";
	this->label1->Text += this->thisLogin->getName();

}
private: System::Void ����ͳ��ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	staticticChart ^chart = gcnew staticticChart();
	chart->Name = "chart";
	chart->StartPosition = FormStartPosition::CenterScreen;
	chart->Show();
}
};

}
