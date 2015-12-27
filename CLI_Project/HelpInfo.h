#pragma once

namespace ManagementSystemV5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// HelpInfo 摘要
	/// </summary>
	public ref class HelpInfo : public System::Windows::Forms::Form
	{
	public:
		HelpInfo(void)
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
		~HelpInfo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  infoTree;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
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
			System::Windows::Forms::TreeNode^  treeNode9 = (gcnew System::Windows::Forms::TreeNode(L"研发环境"));
			System::Windows::Forms::TreeNode^  treeNode10 = (gcnew System::Windows::Forms::TreeNode(L"开发工具"));
			System::Windows::Forms::TreeNode^  treeNode11 = (gcnew System::Windows::Forms::TreeNode(L"系统说明", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode9,
					treeNode10
			}));
			System::Windows::Forms::TreeNode^  treeNode12 = (gcnew System::Windows::Forms::TreeNode(L"系统角色"));
			System::Windows::Forms::TreeNode^  treeNode13 = (gcnew System::Windows::Forms::TreeNode(L"功能详解"));
			System::Windows::Forms::TreeNode^  treeNode14 = (gcnew System::Windows::Forms::TreeNode(L"系统功能介绍", gcnew cli::array< System::Windows::Forms::TreeNode^  >(2) {
				treeNode12,
					treeNode13
			}));
			System::Windows::Forms::TreeNode^  treeNode15 = (gcnew System::Windows::Forms::TreeNode(L"联系我们"));
			System::Windows::Forms::TreeNode^  treeNode16 = (gcnew System::Windows::Forms::TreeNode(L"目录", gcnew cli::array< System::Windows::Forms::TreeNode^  >(3) {
				treeNode11,
					treeNode14, treeNode15
			}));
			this->infoTree = (gcnew System::Windows::Forms::TreeView());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// infoTree
			// 
			this->infoTree->Font = (gcnew System::Drawing::Font(L"楷体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->infoTree->ItemHeight = 25;
			this->infoTree->Location = System::Drawing::Point(19, 9);
			this->infoTree->Margin = System::Windows::Forms::Padding(10);
			this->infoTree->Name = L"infoTree";
			treeNode9->Name = L"cpOne_1";
			treeNode9->Text = L"研发环境";
			treeNode10->Name = L"cpOne_2";
			treeNode10->Text = L"开发工具";
			treeNode11->Name = L"cpOne";
			treeNode11->Text = L"系统说明";
			treeNode12->Name = L"cpTwo_1";
			treeNode12->Text = L"系统角色";
			treeNode13->Name = L"cpTwo_2";
			treeNode13->Text = L"功能详解";
			treeNode14->Name = L"cpTwo";
			treeNode14->Text = L"系统功能介绍";
			treeNode15->Name = L"cpThree";
			treeNode15->Text = L"联系我们";
			treeNode16->Name = L"root";
			treeNode16->Text = L"目录";
			this->infoTree->Nodes->AddRange(gcnew cli::array< System::Windows::Forms::TreeNode^  >(1) { treeNode16 });
			this->infoTree->Size = System::Drawing::Size(161, 301);
			this->infoTree->TabIndex = 0;
			this->infoTree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &HelpInfo::infoTree_AfterSelect);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(194, 9);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(475, 301);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &HelpInfo::richTextBox1_TextChanged);
			// 
			// HelpInfo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(681, 322);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->infoTree);
			this->Name = L"HelpInfo";
			this->Text = L"帮助信息";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void infoTree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
		//从文件中展示出文本信息；
	}
	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
