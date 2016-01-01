#pragma once
#include "jayce.h"

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// feedbackAdmin 摘要
	/// </summary>
	public ref class feedbackAdmin : public System::Windows::Forms::Form
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

		feedbackAdmin(void)
		{
			InitializeComponent();
			pClientEntryHead = nullptr;
			pClientEntryTail = nullptr;
			server = nullptr;
			acceptThread = nullptr;
			recvThread = nullptr;
			keepAlive = nullptr;

			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~feedbackAdmin()
		{
			if (components)
			{
				delete components;
			}
			if (server != nullptr)
				server->Stop();
			if (acceptThread != nullptr && acceptThread->IsAlive)
				acceptThread->Abort();
			printf("clear serverThread.... totel %d \n", clientCx);
			//all client thread clean

			if (recvThread != nullptr && recvThread->IsAlive)
				recvThread->Abort();

			for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
			{
				p->sockClient->Close();
			}
			if (keepAlive != nullptr && keepAlive->IsAlive)
				keepAlive->Abort();
			
		}
	private: System::Windows::Forms::TextBox^  tb_history;
	protected:
	private: System::Windows::Forms::TextBox^  tb_send;
	private: System::Windows::Forms::Button^  btn_send;
	private: Thread^ acceptThread;
	private: Thread^ keepAlive;
	private: Thread^ recvThread;
	private: TcpListener^ server;
	private: int clientCx;
	private:  ClientEntry^ pClientEntryHead;
	private:  ClientEntry^ pClientEntryTail;
	private: System::Windows::Forms::ListBox^  listBox1;
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
			this->tb_history = (gcnew System::Windows::Forms::TextBox());
			this->tb_send = (gcnew System::Windows::Forms::TextBox());
			this->btn_send = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// tb_history
			// 
			this->tb_history->Enabled = false;
			this->tb_history->Location = System::Drawing::Point(12, 12);
			this->tb_history->Multiline = true;
			this->tb_history->Name = L"tb_history";
			this->tb_history->ReadOnly = true;
			this->tb_history->Size = System::Drawing::Size(283, 113);
			this->tb_history->TabIndex = 0;
			// 
			// tb_send
			// 
			this->tb_send->Location = System::Drawing::Point(12, 141);
			this->tb_send->Name = L"tb_send";
			this->tb_send->Size = System::Drawing::Size(182, 21);
			this->tb_send->TabIndex = 4;
			this->tb_send->TextChanged += gcnew System::EventHandler(this, &feedbackAdmin::tb_send_TextChanged);
			// 
			// btn_send
			// 
			this->btn_send->Location = System::Drawing::Point(220, 141);
			this->btn_send->Name = L"btn_send";
			this->btn_send->Size = System::Drawing::Size(75, 23);
			this->btn_send->TabIndex = 3;
			this->btn_send->Text = L"发送";
			this->btn_send->UseVisualStyleBackColor = true;
			this->btn_send->Click += gcnew System::EventHandler(this, &feedbackAdmin::btn_send_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(30, 169);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(59, 88);
			this->listBox1->TabIndex = 5;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &feedbackAdmin::listBox1_SelectedIndexChanged);
			// 
			// feedbackAdmin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(312, 180);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->tb_send);
			this->Controls->Add(this->btn_send);
			this->Controls->Add(this->tb_history);
			this->Name = L"feedbackAdmin";
			this->Text = L"feedbackAdmin";
			this->Load += gcnew System::EventHandler(this, &feedbackAdmin::feedbackAdmin_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		static void clientEntryClean(feedbackAdmin ^pthis)
		{
			char disp[50];
			string dispStr;
			if (pthis->clientCx>0)
			{
				ClientEntry^ pre, ^p;
				pre = p = pthis->pClientEntryHead;
				while (p != nullptr)
				{
					if (p->flag == 0) //当前结点需要删除
					{
						if (p == pthis->pClientEntryHead)
						{
							sprintf(disp, "%s may die...........\r\n", p->name);
							dispStr = disp;
							pthis->tb_history->Text += gcnew String(dispStr.c_str());
							pthis->tb_history->SelectionStart = pthis->tb_history->Text->Length;
							pthis->tb_history->ScrollToCaret();
							pthis->pClientEntryHead = p->next;
							pre = p;
							p = p->next;
							delete pre;
							pre = p;
							pthis->clientCx--;
						}
						else
						{
							sprintf(disp, "%s may die...........\r\n", p->name);
							dispStr = disp;
							pthis->tb_history->Text += gcnew String(dispStr.c_str());
							pthis->tb_history->SelectionStart = pthis->tb_history->Text->Length;
							pthis->tb_history->ScrollToCaret();
							pre->next = p->next;
							delete p;
							p = pre->next;
							pthis->clientCx--;
						}

					}
					else //不需删除当前结点
					{
						pre = p;
						p = p->next;
					}
				}
				pthis->pClientEntryTail = pre; //最后更新尾节点
			}
		}

		static void IsAlive(Object^ arg)
		{
			feedbackAdmin ^pthis = (feedbackAdmin^)(arg);
			char recvBuf[50];
			String^ strSend = gcnew String("");
			cli::array<Byte>^ msg = gcnew cli::array<Byte>(50);
			while (1)
			{
				if (pthis->clientCx > 0)
				{
					EnterCriticalSection(&g_CriticalSection);
					for (ClientEntry^ p = pthis->pClientEntryHead; p != nullptr; p = p->next)
					{
						p->flag = 0;
					}
					strSend = "1K#";
					Array::Clear(msg, 0, msg->Length);
					msg = Encoding::UTF8->GetBytes(strSend);
					for (ClientEntry^ p = pthis->pClientEntryHead; p != nullptr; p = p->next)
					{
						try {
							p->sockClient->Send(msg);
						}
						catch (SocketException^) {
							continue;
						}
					}
					LeaveCriticalSection(&g_CriticalSection);

				}
				Sleep(2000);//2000毫秒

							//清理疑似死去的client
				EnterCriticalSection(&g_CriticalSection);
				clientEntryClean(pthis);
				LeaveCriticalSection(&g_CriticalSection);
			}
		}

		//为每个客户创建一个接受线程;有了Available检查，就不需要为每个Client建立一个线程了
		static void RecvThread(Object^ arg) //多个接收线程公用这个函数，唯一不变的是每个线程在不同的sock上等待信息
		{
			feedbackAdmin ^pthis = (feedbackAdmin^)(arg);
			char recvBuf[50];
			string recvStr = "";
			String^ str;
			cli::array<Byte>^ bytes = gcnew cli::array<Byte>(50);
			while (1)
			{
				for (ClientEntry^ p = pthis->pClientEntryHead; p != nullptr; p = p->next)
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
							if (recvBuf[0] != '1') //仅显示非控制消息,1表示心跳包
							{
								char disp[50];
								sprintf(disp, "%s: %s ...\r\n", name, recvBuf + 1);
								recvStr = disp;
								pthis->tb_history->Text += gcnew String(recvStr.c_str());
								pthis->tb_history->SelectionStart = pthis->tb_history->Text->Length;
								pthis->tb_history->ScrollToCaret();
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
			feedbackAdmin ^pthis = (feedbackAdmin^)(arg);
			Int32 port = 1234;
			IPAddress^ localAdd = IPAddress::Parse("127.0.0.1");
			pthis->server = gcnew TcpListener(localAdd, 1234);
			pthis->server->Start();
			string str = "";
			String^ strMsg = gcnew String("");
			Socket^ sockClient = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			cli::array<Byte>^ msg = gcnew cli::array<Byte>(50);
			printf("server-------acceptThread run.... \n");
			while (pthis->server != nullptr)
			{
				try
				{
					sockClient = pthis->server->AcceptSocket();
					//协商得到client name，client连接后会主动发送NAME
					cli::array<Byte>^ bytes = gcnew cli::array<Byte>(50);
					Array::Clear(bytes, 0, bytes->Length);
					if (sockClient->Receive(bytes) > 0)
					{
						EnterCriticalSection(&g_CriticalSection);  //成员属性线程同步测试
						 //add client entry
						pthis->clientCx++;
						ClientEntry ^ce = gcnew ClientEntry();
						ce->name = Encoding::UTF8->GetString(bytes);
						ce->name = ce->name->Substring(1); //第0位为类型标识
						ce->flag = 1;
						ce->sockClient = sockClient;
						ce->next = nullptr;
						if (pthis->pClientEntryHead == nullptr) //维护客户端链表
						{
							pthis->pClientEntryHead = ce;
							pthis->pClientEntryTail = ce;
						}
						else
						{
							pthis->pClientEntryTail->next = ce;
							pthis->pClientEntryTail = ce;
						}
						char temp[50];
						sprintf(temp, "%s", ce->name);
						sprintf(temp, "User(%s),connected....\r\n", ce->name);
						str = temp;
						pthis->tb_history->Text += gcnew String(str.c_str());
						pthis->tb_history->SelectionStart = pthis->tb_history->Text->Length;
						pthis->tb_history->ScrollToCaret();
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

	private: System::Void feedbackAdmin_Load(System::Object^  sender, System::EventArgs^  e) {
		clientCx = 0;
		acceptThread = gcnew Thread(gcnew ParameterizedThreadStart(feedbackAdmin::AcceptThread));//带参静态成员线程函数
		acceptThread->Start(this);
		keepAlive = gcnew Thread(gcnew ParameterizedThreadStart(feedbackAdmin::IsAlive));//带参静态成员线程函数
		keepAlive->Start(this);
		recvThread = gcnew Thread(gcnew ParameterizedThreadStart(feedbackAdmin::RecvThread));//带参静态成员线程函数
		recvThread->Start(this);
		this->listBox1->Hide();
	}
private: System::Void btn_send_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!(this->tb_send->Text->Contains("@")))
	{
		this->tb_history->Text += ("server to all: " + this->tb_send->Text + "\r\n");
		this->tb_history->SelectionStart = this->tb_history->Text->Length;
		this->tb_history->ScrollToCaret();

		String^ sendStr = gcnew String("");
		sendStr = "2";
		sendStr += this->tb_send->Text->ToString();
		sendStr += "#";
		this->tb_send->Text = "";
		for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
		{
			try {
				p->sockClient->Send(Encoding::UTF8->GetBytes(sendStr));
			}
			catch (SocketException^) {
				continue;
			}

		}
	}
	else
	{
		char peerName[20];
		char thisName[20];
		int indexOfBlank = this->tb_send->Text->IndexOf(" ");
		sprintf(peerName, "%s", this->tb_send->Text->Substring(1, indexOfBlank-1));
		String^ sendStr = gcnew String("2");
		sendStr += this->tb_send->Text->Substring(indexOfBlank+1);
		sendStr += "#";
		for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
		{
			sprintf(thisName, "%s", p->name);
			if (strcmp(thisName, peerName) == 0)
			{
				p->sockClient->Send(Encoding::UTF8->GetBytes(sendStr));
				this->tb_history->Text += ("Server to "+ p->name);
				this->tb_history->Text += ":";
				this->tb_history->Text += (this->tb_send->Text->Substring(indexOfBlank+1) + "\r\n");
				this->tb_history->SelectionStart = this->tb_history->Text->Length;
				this->tb_history->ScrollToCaret();
				this->tb_send->Text = "";
				return;
			}

		}
	}
}
private: System::Void tb_send_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (this->tb_send->Text == "@")
	{
		this->listBox1->Items->Clear();
		for (ClientEntry^ p = pClientEntryHead; p != nullptr; p = p->next)
		{
			this->listBox1->Items->Add(p->name);
		}
		this->listBox1->Show();
	}
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	this->tb_send->Text += this->listBox1->SelectedItem->ToString();
	this->tb_send->Text += " ";
	this->listBox1->Hide();
}
};
}
