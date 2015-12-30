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
	using namespace System::Drawing::Drawing2D;
	/// <summary>
	/// staticticChart 摘要
	/// </summary>
	public ref class staticticChart : public System::Windows::Forms::Form
	{
	public:
		staticticChart(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//


			array<Color > ^temp = { Color::Aqua ,Color::LightSalmon,Color::LightSeaGreen,Color::LightSlateGray,Color::Lime,Color::Magenta,
			Color::Blue, Color::Maroon,Color::MediumAquamarine,Color::MediumOrchid,Color::MediumPurple,Color::Chartreuse,Color::Brown,
			Color::Olive,Color::Crimson,Color::DarkSalmon,Color::DarkSlateBlue,Color::DarkTurquoise ,Color::PaleVioletRed,Color::Gray,
			Color::LawnGreen,Color::LightBlue,Color::Violet ,Color::SkyBlue,Color::SandyBrown ,Color::Indigo };
			this->colorArray = temp;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~staticticChart()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:array<Color> ^colorArray;
	protected:array<int> ^statictcArray;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(167, 46);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(500, 351);
			this->panel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(36, 97);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"直方图";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &staticticChart::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(32, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(129, 19);
			this->label1->TabIndex = 2;
			this->label1->Text = L"学生信息统计";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(36, 188);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"折线图";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &staticticChart::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(36, 273);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"扇形图";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &staticticChart::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(36, 351);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"清空";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &staticticChart::button4_Click);
			// 
			// staticticChart
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(702, 430);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Name = L"staticticChart";
			this->Text = L"staticticChart";
			this->Load += gcnew System::EventHandler(this, &staticticChart::staticticChart_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//直方图
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		cleanAll();
		//int a[12] = { 50,32,80,98,10,24,56,98,70,50,45,60 };
		int a[12];
		for (int i = 0; i < statictcArray->Length; i++)
		{
			a[i] = statictcArray[i];
		}
		Pen ^rectPen = gcnew Pen(Color::Black, 1.5f);
		SolidBrush ^rectBrush = gcnew SolidBrush(Color::LightBlue);

		Graphics ^mg = getXY();
		for (int i = 0; i <12; i++) {
			rectPen->Color = getRamColor(i);
			rectBrush->Color = getRamColor(i);
			mg->FillRectangle(rectBrush, 50 + (i + 1) * 30, 36 + 2.2*(120 - a[i]), 30, 264 - 2.2*(120 - a[i])); //填充颜色
			mg->DrawRectangle(rectPen, 50 + (i + 1) * 30, 36 + 2.2*(120 - a[i]), 30, 264 - 2.2*(120 - a[i]));   //描边；
		}
		getXY();

		delete rectPen;
		delete rectBrush;
	}

			 //折线图；
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		cleanAll();
		//折线图，需要知道每个点的中心
		//int a[12] = { 50,32,80,98,10,24,56,98,70,50,45,60 };
		int a[12];
		for (int i = 0; i < statictcArray->Length; i++)
		{
			a[i] = statictcArray[i];
		}
		double y = 36 + (120 - a[0])*2.2;

		Point current = Point(105, y);
		Pen ^linePen = gcnew Pen(getRamColor(15), 3.0f);
		Graphics ^mg = getXY();
		for (int i = 1; i < 12; i++) {
			Point point = Point(65 + (i + 1) * 30, 36 + 2.2*(120 - a[i]));
			mg->DrawLine(linePen, current, point);
			current = point;
		}

		delete linePen;
	}

			 //清空按钮
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		cleanAll();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		//第一步，清空
		cleanAll();
		//从数据库得到数据；，假设为数组a
		//int a[12] = { 50,32,80,98,10,24,56,98,70,50,45,60 };
		int a[12];
		for (int i = 0; i < statictcArray->Length;i++)
		{
			a[i] = statictcArray[i];
		}
		double b[12];
		int sum = 0;
		for (int i = 0; i < 12; i++) {
			sum += a[i];
		}
		for (int i = 0; i < 12; i++) {
			b[i] = a[i] * 330 * 1.0 / sum;
		}

		Graphics ^my = this->panel1->CreateGraphics();
		Pen ^piePen = gcnew Pen(Color::Brown, 2.0f);
		SolidBrush ^pieBrush = gcnew SolidBrush(Color::Brown);
		Drawing::Font ^strFont = gcnew Drawing::Font("隶书", 12);
		SolidBrush ^strBrush = gcnew SolidBrush(Color::Red);
		double current = 0;
		for (int i = 0; i < 12; i++) {
			double x = a[i] * 1.0 / sum;
			String ^s = x.ToString("P");
			String ^ str = (i+1) + " - " + (i + 2) + " :" + s;
			piePen->Color = getRamColor(i);
			pieBrush->Color = getRamColor(i);
			strBrush->Color = getRamColor(i);

			my->DrawPie(piePen, 50, 50, 250, 200, current, b[i]);
			my->FillPie(pieBrush, 50, 50, 250, 200, current, b[i]);
			my->DrawString(str, strFont, strBrush, 350, 50 + i * 25);
			current += b[i] + 3;
		}
		delete piePen;
		delete pieBrush;
	}

	private:Graphics ^ getXY() {  //画出XY轴，使用比较多次，所以单独写一个函数；
		Pen ^ XYPen = gcnew Pen(Color::Red, 2.0f);
		XYPen->LineJoin = Drawing2D::LineJoin::Miter;
		//pen->EndCap = LineCap::ArrowAnchor; //此句话用户画坐标轴的箭头，但是由于效果不好，我们手动添加；
		Graphics ^mg = this->panel1->CreateGraphics();
		Drawing::Font ^font = gcnew Drawing::Font("宋体", 8);
		SolidBrush ^fontBrush = gcnew SolidBrush(Color::Red);

		//坐标刻度点：
		for (int i = 1; i <= 12; i++) {
			String ^s1 = "" + i * 10;
			String ^s2 = "" + i;
			mg->DrawLine(XYPen, 48, 20 + i * 22, 52, 20 + i * 22);
			mg->DrawLine(XYPen, 50 + i * 30, 298, 50 + i * 30, 302);
			mg->DrawString(s2, font, fontBrush, 60 + i * 30, 301);
			mg->DrawString(s1, font, fontBrush, 30, 300 - i * 22);
		}
		//xy坐标
		mg->DrawLine(XYPen, 50, 300, 50, 10);
		mg->DrawLine(XYPen, 450, 300, 50, 300);
		//手动添加箭头；
		mg->DrawLine(XYPen, 50, 10, 45, 15);
		mg->DrawLine(XYPen, 50, 10, 55, 15);
		mg->DrawLine(XYPen, 450, 300, 445, 295);
		mg->DrawLine(XYPen, 450, 300, 445, 305);

		delete XYPen;
		return mg;
	}


			public
	private:void cleanAll() {
				Graphics ^my = getXY();
				Color color = BackColor;
				my->Clear(color);
			}

	private:Color getRamColor(int i) {
		Random ^t = gcnew Random(i);
		int r = t->Next() % 26;
		return colorArray[r];
	}
#pragma endregion

		array<int>^ getAllStuBirthMonth()
		{
			Storage storage1;
			SchoolMember *pm;
			char id[20];
			int year, month, day;
			string str;
			array<String ^> ^list = storage1.readAllStuSummaryInfo();
			array<int>^ birthYearList = gcnew array<int>(list->Length);
			int index = 0;
			for each (String ^a in list)
			{
				sprintf(id, "%s", a);
				pm = storage1.readSchoolMemberInfoDB(id);
				pm->getBirthday(year,month,day);
				birthYearList[index++]=month;
			}
			return birthYearList;
		}
	private: System::Void staticticChart_Load(System::Object^  sender, System::EventArgs^  e) {
		array<int>^ birthMonth = getAllStuBirthMonth();
		//array<int>^ birthMonth = {11,11,11,12,11,11,12};
		statictcArray = gcnew array<int>(12);

		for each(int month in birthMonth)
		{
			statictcArray[month-1]++;
		}
	}
};
}
