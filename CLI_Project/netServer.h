#pragma once
#include "jayce.h"
#include "followForm.h"
namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net::Sockets;
	using namespace System::Net;
	using namespace System::Text;
	/// <summary>
	/// netServer 摘要
	/// </summary>

	public ref class netServer : public System::Windows::Forms::Form
	{
	public:
		ref class ClientEntry
		{
		public:
			String^ name;
			Socket^ sockClient;
			int flag;			//为了后期扩展，flag设置为int型
			ClientEntry^ next;
		};
		netServer(void)
		{
			InitializeComponent();
			pClientEntryHead = nullptr;
			pClientEntryTail = nullptr;
			pthis = this;
			timeCx = 0;
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~netServer()
		{
			if (components)
			{
				delete components;
			}
			if(server!=nullptr)
				server->Stop();
			if(acceptThread!=nullptr && acceptThread->IsAlive)
				acceptThread->Abort();
			printf("clear serverThread.... totel %d \n", clientCx);
			//all client thread clean

			if (recvThread->IsAlive)
				recvThread->Abort();

			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				p->sockClient->Close();
			}
			if (keepAlive != nullptr && keepAlive->IsAlive)
				keepAlive->Abort();
			if (timeThread != nullptr && timeThread->IsAlive)
				timeThread->Abort();
			
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: Thread^ acceptThread;
	private: Thread^ keepAlive;
	private: Thread^ recvThread;
	private: Thread^ timeThread;
	//private: static SOCKET sockSrv;
			 //纯CLI/C++版本
	private: static TcpListener^ server;

	private: static int clientCx;
	private: int timeCx;
	private: static ClientEntry^ pClientEntryHead;
	private: static ClientEntry^ pClientEntryTail;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: static netServer^ pthis;
	private: System::Windows::Forms::Button^  btn_c1;
	private: System::Windows::Forms::Button^  btn_c3;
	private: System::Windows::Forms::Button^  btn_c2;
	private: System::Windows::Forms::Button^  btn_all;
	private: System::Windows::Forms::Label^  label1;

	protected:

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->btn_c1 = (gcnew System::Windows::Forms::Button());
			this->btn_c3 = (gcnew System::Windows::Forms::Button());
			this->btn_c2 = (gcnew System::Windows::Forms::Button());
			this->btn_all = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(324, 197);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(154, 242);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"RUN";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &netServer::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(261, 242);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Send";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &netServer::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(154, 215);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(182, 21);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &netServer::textBox2_TextChanged);
			// 
			// btn_c1
			// 
			this->btn_c1->FlatAppearance->BorderSize = 0;
			this->btn_c1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c1->Location = System::Drawing::Point(12, 215);
			this->btn_c1->Name = L"btn_c1";
			this->btn_c1->Size = System::Drawing::Size(37, 23);
			this->btn_c1->TabIndex = 3;
			this->btn_c1->UseVisualStyleBackColor = true;
			this->btn_c1->Click += gcnew System::EventHandler(this, &netServer::btn_c1_Click);
			// 
			// btn_c3
			// 
			this->btn_c3->FlatAppearance->BorderSize = 0;
			this->btn_c3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c3->Location = System::Drawing::Point(12, 244);
			this->btn_c3->Name = L"btn_c3";
			this->btn_c3->Size = System::Drawing::Size(37, 23);
			this->btn_c3->TabIndex = 3;
			this->btn_c3->UseVisualStyleBackColor = true;
			this->btn_c3->Click += gcnew System::EventHandler(this, &netServer::btn_c3_Click);
			// 
			// btn_c2
			// 
			this->btn_c2->FlatAppearance->BorderSize = 0;
			this->btn_c2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_c2->Location = System::Drawing::Point(69, 215);
			this->btn_c2->Name = L"btn_c2";
			this->btn_c2->Size = System::Drawing::Size(37, 23);
			this->btn_c2->TabIndex = 3;
			this->btn_c2->UseVisualStyleBackColor = true;
			this->btn_c2->Click += gcnew System::EventHandler(this, &netServer::btn_c2_Click);
			// 
			// btn_all
			// 
			this->btn_all->FlatAppearance->BorderSize = 0;
			this->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_all->Location = System::Drawing::Point(69, 244);
			this->btn_all->Name = L"btn_all";
			this->btn_all->Size = System::Drawing::Size(37, 23);
			this->btn_all->TabIndex = 3;
			this->btn_all->UseVisualStyleBackColor = true;
			this->btn_all->Click += gcnew System::EventHandler(this, &netServer::btn_all_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(400, 117);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"label1";
			// 
			// netServer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(354, 274);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btn_all);
			this->Controls->Add(this->btn_c2);
			this->Controls->Add(this->btn_c3);
			this->Controls->Add(this->btn_c1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"netServer";
			this->Text = L"netServer";
			this->Load += gcnew System::EventHandler(this, &netServer::netServer_Load);
			this->LocationChanged += gcnew System::EventHandler(this, &netServer::netServer_LocationChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		static void clientEntryClean()
		{
			char disp[50];
			string dispStr;
			if(clientCx>0)
			{
				ClientEntry^ pre, ^p;
				pre = p = pClientEntryHead;
				while ( p != nullptr)
				{
					if (p->flag == 0) //当前结点需要删除
					{
						if (p == pClientEntryHead)
						{
							sprintf(disp,"%s may die...........\r\n",p->name);
							dispStr = disp;
							pthis->textBox1->Text += gcnew String(dispStr.c_str());
							pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
							pthis->textBox1->ScrollToCaret();
							pClientEntryHead = p->next;
							pre = p;
							p = p->next;
							delete pre;
							pre = p;
							clientCx--;
						}
						else
						{
							sprintf(disp, "%s may die...........\r\n", p->name);
							dispStr = disp;
							pthis->textBox1->Text += gcnew String(dispStr.c_str());
							pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
							pthis->textBox1->ScrollToCaret();
							pre->next = p->next;
							delete p;
							p = pre->next;
							clientCx--;
						}
					
					}
					else //不需删除当前结点
					{
						pre = p;
						p = p->next;
					}
				}
				pClientEntryTail = pre; //最后更新尾节点
			}
		}
	
		static void IsAlive(Object^ arg)
		{
			char recvBuf[50];
			String^ strSend = gcnew String("");
			cli::array<Byte>^ msg = gcnew cli::array<Byte>(50);
			while (1)
			{
				//为每个客户创建一个接受线程
				if (clientCx > 0)
				{
					EnterCriticalSection(&g_CriticalSection);
					for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
					{
						p->flag = 0;
					}
					strSend = "1K#";
					Array::Clear(msg, 0, msg->Length);
					msg = Encoding::UTF8->GetBytes(strSend);
					for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
					{
						try{
							p->sockClient->Send(msg);
						}
						catch(SocketException^){
							continue;
						}
					}
					LeaveCriticalSection(&g_CriticalSection);

				}
				Sleep(2000);//2000毫秒

				//清理疑似死去的client
				EnterCriticalSection(&g_CriticalSection);
				clientEntryClean();
				LeaveCriticalSection(&g_CriticalSection);
			}
		}

		static void TimeThread(Object^ arg)
		{
			while(1)
			{
			if (pthis->timeCx < 1)
			{
				pthis->timeCx = 0;
				pthis->Text = "netServer";
				pthis->ClientSize = System::Drawing::Size(370, 313);
			}
			pthis->timeCx--;
			Sleep(1000);
			}
		}
		//为每个客户创建一个接受线程;有了Available检查，就不需要为每个Client建立一个线程了
		static void RecvThread(Object^ arg) //多个接收线程公用这个函数，唯一不变的是每个线程在不同的sock上等待信息
		{
			char recvBuf[50];
			string recvStr = "";
			String^ str;
			cli::array<Byte>^ bytes = gcnew cli::array<Byte>(50);
			while(1)
			{
				for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
				{
					char name[20];
					sprintf(name, "%s", p->name);
					try {
						if (p->sockClient->Available)
						{
							Array::Clear(bytes, 0, bytes->Length);
							if (p->sockClient->Receive(bytes) < 0)
							{
								return;
							}
							p->flag = 1;
							str = Encoding::UTF8->GetString(bytes);
							sprintf(recvBuf, "%s", str);
							printf("recv   %s from client %s : \n", recvBuf + 1, name);  //第一位作为标识位，区分不同类信息
							if (recvBuf[0] != '0' && recvBuf[0] != '1') //仅显示非控制消息, 0 NAME包，1表示心跳包
							{
								char disp[50];
								sprintf(disp, "%s: %s ...\r\n", name, recvBuf + 1);
								recvStr = disp;
								pthis->textBox1->Text += gcnew String(recvStr.c_str());
								pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
								pthis->textBox1->ScrollToCaret();
							}
						}
					}
					catch (SocketException^)
					{
						continue;
					}
				}
				
			Sleep(100);//2000毫秒
			}
		}
		
		static void AcceptThread(Object^ arg)
		{
			Int32 port = 1234;
			IPAddress^ localAdd = IPAddress::Parse("127.0.0.1");
			server = gcnew TcpListener(localAdd, 1234);
			server->Start();
			string str = "";
			String^ strMsg = gcnew String("");
			Socket^ sockClient= gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			cli::array<Byte>^ msg = gcnew cli::array<Byte>(50);
			printf("server-------acceptThread run.... \n");
			while(server!=nullptr)
			{ 
				try
				{
					sockClient = server->AcceptSocket();
					strMsg = "0N#";
					msg = Encoding::UTF8->GetBytes(strMsg);
					sockClient->Send(msg);
					//协商得到client name
					cli::array<Byte>^ bytes = gcnew cli::array<Byte>(50);
					Array::Clear(bytes, 0, bytes->Length);
					if (sockClient->Receive(bytes) > 0)
					{
						EnterCriticalSection(&g_CriticalSection);  //成员属性线程同步测试
						 //add client entry
						clientCx++;
						ClientEntry ^ce = gcnew ClientEntry();
							ce->name = Encoding::UTF8->GetString(bytes);
						ce->name = ce->name->Substring(1); //第0位为类型标识
						ce->flag = 1;
						ce->sockClient = sockClient;
						ce->next = nullptr;
						if (pClientEntryHead == nullptr)
						{
							pClientEntryHead = ce;
							pClientEntryTail = ce;
						}
						else
						{
							pClientEntryTail->next = ce;
							pClientEntryTail = ce;
						}
						char temp[50];
						sprintf(temp, "%s", ce->name);
						if (strcmp(temp, "c1") == 0)
						{
							pthis->btn_c1->Visible = true;
							pthis->btn_c1->Text = ce->name;
							pthis->btn_c1->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
							pthis->btn_all->Text = "all";
							pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						}
						else if (strcmp(temp, "c2") == 0)
						{
							pthis->btn_c2->Text = ce->name;
							pthis->btn_c2->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
							pthis->btn_all->Text = "all";
							pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						}
						else if (strcmp(temp, "c3") == 0)
						{
							pthis->btn_c3->Text = ce->name;
							pthis->btn_c3->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
							pthis->btn_all->Text = "all";
							pthis->btn_all->FlatStyle = System::Windows::Forms::FlatStyle::Standard;
						}
						sprintf(temp, "User(%s),connected....\r\n", ce->name);
						str = temp;
						pthis->textBox1->Text += gcnew String(str.c_str());
						pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
						pthis->textBox1->ScrollToCaret();
						LeaveCriticalSection(&g_CriticalSection);
					}	
				}
				catch (SocketException^)
				{
					continue;
				}
			Sleep(200);//2000毫秒
			}
		}

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->button1->Enabled = false;
		clientCx = 0;
		acceptThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::AcceptThread));//带参静态成员线程函数
		acceptThread->Start(0);
		keepAlive = gcnew Thread(gcnew ParameterizedThreadStart(netServer::IsAlive));//带参静态成员线程函数
		keepAlive->Start(this);
		recvThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::RecvThread));//带参静态成员线程函数
		recvThread->Start(0);
	}

			

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		
		char peerName[20];
		char eachName[20];
		string dispStr = "";
		if (!(this->textBox2->Text->Contains("@")))
		{
			sprintf(eachName, "2%s", this->textBox2->Text);
			dispStr = "Server to all: ";
			dispStr += eachName + 1;
			dispStr += "\r\n";
			this->textBox1->Text += gcnew String(dispStr.c_str());
			this->textBox1->SelectionStart = this->textBox1->Text->Length;
			this->textBox1->ScrollToCaret();
			String^ sendStr = gcnew String("");

			sendStr = "2";
			sendStr += this->textBox2->Text->ToString();
			sendStr += "#";
			cli::array<Byte> ^msg = gcnew cli::array<Byte>(50);
			msg = Encoding::UTF8->GetBytes(sendStr);
			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				try {
					//MessageBox::Show(Encoding::UTF8->GetString(msg) + "--Server 发前");
					p->sockClient->Send(msg);
				}
				catch (SocketException^){
					continue;
				}
				
			}
		}
		else
		{
			sprintf(peerName, "%s", this->textBox2->Text->Substring(1, 2));
			String^ sendStr = gcnew String("");
			sendStr = this->textBox2->Text->Substring(3);
			sendStr += "#";
			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				sprintf(eachName, "%s", p->name);
				if (strcmp(eachName, peerName) == 0)
				{
					sprintf(eachName, "2%s", this->textBox2->Text->Substring(3));
						p->sockClient->Send(Encoding::UTF8->GetBytes(sendStr));

					sprintf(eachName, "Server to %s:  %s...\r\n", p->name, this->textBox2->Text->Substring(4));
					dispStr = eachName;
					this->textBox1->Text += gcnew String(dispStr.c_str());
					this->textBox1->SelectionStart = this->textBox1->Text->Length;
					this->textBox1->ScrollToCaret();
					return;
				}

			}
		}
		
		this->textBox2->Text = "";
	}

private: System::Void btn_c1_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c1->Enabled = false;
	this->btn_c2->Enabled = true;
	this->btn_c3->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c1 ";

}
private: System::Void btn_c2_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c2->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c3->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c2 ";
}
private: System::Void btn_c3_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c3->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c2->Enabled = true;
	this->btn_all->Enabled = true;
	this->textBox2->Text = "@c3 ";
}
private: System::Void btn_all_Click(System::Object^  sender, System::EventArgs^  e) {
	this->btn_all->Enabled = false;
	this->btn_c1->Enabled = true;
	this->btn_c2->Enabled = true;
	this->btn_c3->Enabled = true;
	this->textBox2->Text = "";
}
private: System::Void netServer_Load(System::Object^  sender, System::EventArgs^  e) {
	this->btn_c1->Visible = false;
	timeThread = gcnew Thread(gcnew ParameterizedThreadStart(netServer::TimeThread));//带参静态成员线程函数
	timeThread->Start(0);
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	timeCx = 1; //1秒没输入则提示没有输入
	this->Text = "正在输入...";
	this->ClientSize = System::Drawing::Size(543, 313);
	this->label1->Text = "收到反馈信息！";
}

private: System::Void netServer_LocationChanged(System::Object^  sender, System::EventArgs^  e) {
	static bool firstCall = true;
	if (firstCall)
	{
		followForm^ fF = gcnew followForm();
		fF->Name = "fF";
		fF->Text = "fF";
		fF->Location = Point(this->Location.X - fF->Size.Width + 10, this->Location.Y);
		fF->StartPosition = FormStartPosition::Manual;
		fF->Show();
		fF->Visible = false;
		firstCall = false;
		return;
	}
	bool needShow;
	if (this->Text == "netServer")
		needShow = false;
	else
		needShow = true;
	if (needShow)
	{
		Application::OpenForms["fF"]->Location = Point(this->Location.X - 300 + 10, this->Location.Y);
		Application::OpenForms["fF"]->Visible = true;
	}
	else
		Application::OpenForms["fF"]->Visible = false;
}
};

	

}

