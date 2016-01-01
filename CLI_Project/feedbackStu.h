#pragma once
#include"jayce.h"

namespace ManagementSystemV5 {

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
	/// feedbackStu 摘要
	/// </summary>
	public ref class feedbackStu : public System::Windows::Forms::Form
	{
	public:
		feedbackStu(void)
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
		~feedbackStu()
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
	private: System::Windows::Forms::TextBox^  tb_send;
	private: System::Windows::Forms::Button^  btn_send;
	private: System::Windows::Forms::TextBox^  tb_history;
	private:  Thread  ^recvThread;
	private:  Socket  ^sockClient;
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
			this->tb_send = (gcnew System::Windows::Forms::TextBox());
			this->btn_send = (gcnew System::Windows::Forms::Button());
			this->tb_history = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// tb_send
			// 
			this->tb_send->Location = System::Drawing::Point(12, 141);
			this->tb_send->Name = L"tb_send";
			this->tb_send->Size = System::Drawing::Size(182, 21);
			this->tb_send->TabIndex = 7;
			// 
			// btn_send
			// 
			this->btn_send->Location = System::Drawing::Point(220, 141);
			this->btn_send->Name = L"btn_send";
			this->btn_send->Size = System::Drawing::Size(75, 23);
			this->btn_send->TabIndex = 6;
			this->btn_send->Text = L"发送";
			this->btn_send->UseVisualStyleBackColor = true;
			this->btn_send->Click += gcnew System::EventHandler(this, &feedbackStu::btn_send_Click);
			// 
			// tb_history
			// 
			this->tb_history->Enabled = false;
			this->tb_history->Location = System::Drawing::Point(12, 12);
			this->tb_history->Multiline = true;
			this->tb_history->Name = L"tb_history";
			this->tb_history->ReadOnly = true;
			this->tb_history->Size = System::Drawing::Size(283, 113);
			this->tb_history->TabIndex = 5;
			// 
			// feedbackStu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(310, 179);
			this->Controls->Add(this->tb_send);
			this->Controls->Add(this->btn_send);
			this->Controls->Add(this->tb_history);
			this->Name = L"feedbackStu";
			this->Text = L"feedbackStu";
			this->Load += gcnew System::EventHandler(this, &feedbackStu::feedbackStu_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//定义线程  
		//静态成员函数方法
		static void ReceiveThreadRun(Object^ arg)
		{
			printf("client-----recvThread created success....\n");
			feedbackStu^ pthis = (feedbackStu^)arg;
			char sendBuf[50];
			char recvBuf[50];
			char disp[50];
			string dispStr = "";
			String^ str = gcnew String("");
			while (1)
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
				str = str->Replace("#", "");
				sprintf(recvBuf, "%s", str);
				if (strcmp(recvBuf, "1K") == 0)
				{
					str = "1";
					str += pthis->Name;
					cli::array<Byte>^ replyArray = gcnew cli::array<Byte>(50);
					Array::Clear(replyArray, 0, replyArray->Length);
					replyArray = Encoding::UTF8->GetBytes(str);
					pthis->sockClient->Send(replyArray);
				}
				else
				{
					//测试显示中文字符占三个字节
					pthis->tb_history->Text += "server: ";
					pthis->tb_history->Text += str->Substring(1);
					pthis->tb_history->Text += "\r\n";
					pthis->tb_history->SelectionStart = pthis->tb_history->Text->Length;
					pthis->tb_history->ScrollToCaret();

				}

			}
		}

		//connect
	private: System::Void feedbackStu_Load(System::Object^  sender, System::EventArgs^  e) {
		Int32 port = 1234;
		IPAddress^ ipAdderess = IPAddress::Parse("127.0.0.1");
		IPEndPoint^ remoteEP = gcnew IPEndPoint(ipAdderess, port);
		sockClient = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		sockClient->Connect(remoteEP);
		String ^str = "0";  //发送自己名字
		str += this->Name;
		cli::array<Byte>^ nameBuf = gcnew cli::array<Byte>(50);
		Array::Clear(nameBuf, 0, nameBuf->Length);
		nameBuf = Encoding::UTF8->GetBytes(str);
		this->sockClient->Send(nameBuf);
		//create receive Thread
		recvThread = gcnew Thread(gcnew ParameterizedThreadStart(feedbackStu::ReceiveThreadRun));//带参静态成员线程函数
		recvThread->Start(this);
	}
	private: System::Void btn_send_Click(System::Object^  sender, System::EventArgs^  e) {
	
		String^ sendStr = gcnew String("");
		sendStr = "2";
		sendStr += this->tb_send->Text->ToString();
		this->sockClient->Send(Encoding::UTF8->GetBytes(sendStr));
		this->tb_history->Text += ("me: " + this->tb_send->Text + "\r\n");
		this->tb_send->Text = "";
		this->tb_history->SelectionStart = this->tb_history->Text->Length;
		this->tb_history->ScrollToCaret();
	}
};
}
