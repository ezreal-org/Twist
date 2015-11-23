#pragma once
#include"jayce.h"



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
	using namespace Runtime::InteropServices;
	/// <summary>
	/// netClient 摘要
	/// </summary>
	public ref class netClient : public System::Windows::Forms::Form
	{
	public:
		netClient(void)
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
		~netClient()
		{
			if (sockClient != nullptr)
				sockClient->Close();
			if (recvThread != nullptr && recvThread->IsAlive)
				recvThread->Abort();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: Thread^ recvThread;
	private: System::Windows::Forms::TextBox^  textBox2;
	private:	Socket^ sockClient;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(107, 117);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Send";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &netClient::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(170, 72);
			this->textBox1->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 117);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Connect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &netClient::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 90);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(170, 21);
			this->textBox2->TabIndex = 3;
			// 
			// netClient
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(193, 156);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"netClient";
			this->Text = L"netClient";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		//定义线程  
		//静态成员函数方法
		static void ReceiveThreadRun(Object^ arg)
		{
			printf("client-----recvThread created success....\n");
			netClient^ pthis = (netClient^)arg;
			char sendBuf[50];
			char recvBuf[50];
			char disp[50];
			string dispStr = "";
			String^ str = gcnew String("");
			while(1)
			{
				try {
					str = "";
					while (!str->Contains("#"))
					{
						cli::array<Byte>^ bytes = gcnew cli::array<Byte>(50);
						Array::Clear(bytes, 0, bytes->Length);
						pthis->sockClient->Receive(bytes);
						str += Encoding::UTF8->GetString(bytes);
					}
				}
				catch (SocketException^)
				{
					return;
				}
				str = str->Replace("#","");
				//被这个sprintf坑大发了
				//sprintf(recvBuf, "%s", str);
				
				char *tp = (char*)(Marshal::StringToHGlobalAnsi(str)).ToPointer();//String->char*
				strcpy(recvBuf, tp);
				if (strcmp(recvBuf, "1K") == 0)
				{	
					str = "0";
					str += pthis->Name;
					cli::array<Byte>^ replyArray = gcnew cli::array<Byte>(50);
					Array::Clear(replyArray, 0, replyArray->Length);
					replyArray = Encoding::UTF8->GetBytes(str);
					pthis->sockClient->Send(replyArray);
				}
				else if (strcmp(recvBuf, "0N") == 0)
				{ 
					str = "0";
					str += pthis->Name;
					cli::array<Byte>^ replyArray = gcnew cli::array<Byte>(50);
					Array::Clear(replyArray, 0, replyArray->Length);
					replyArray = Encoding::UTF8->GetBytes(str);
					pthis->sockClient->Send(replyArray);
				}
				else
				{
					//测试显示中文字符占三个字节
					pthis->textBox1->Text += "server: ";
					pthis->textBox1->Text += str->Substring(1);
					pthis->textBox1->Text += "\r\n";
					pthis->textBox1->SelectionStart = pthis->textBox1->Text->Length;
					pthis->textBox1->ScrollToCaret();
					
				}
				
			}		
		}

#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->button2->Enabled = false;
		Int32 port = 1234;
		IPAddress^ ipAdderess = IPAddress::Parse("127.0.0.1");
		IPEndPoint^ remoteEP = gcnew IPEndPoint(ipAdderess, port);

		sockClient = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		sockClient->Connect(remoteEP);
		//create receive Thread
		recvThread = gcnew Thread(gcnew ParameterizedThreadStart(netClient::ReceiveThreadRun));//带参静态成员线程函数
		recvThread->Start(this);
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		char sendBuf[50];
		String^ sendStr = gcnew String("");
		sendStr = "2";
		sendStr += this->textBox2->Text->ToString();
		this->sockClient->Send(Encoding::UTF8->GetBytes(sendStr));
		this->textBox1->Text += ("me: " + this->textBox2->Text + "\r\n");
		this->textBox2->Text = "";
		this->textBox1->SelectionStart = this->textBox1->Text->Length;
		this->textBox1->ScrollToCaret();
	}
};
}
