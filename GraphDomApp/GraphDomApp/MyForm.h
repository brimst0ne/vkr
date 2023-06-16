#pragma once

#include "utils.h"
#include <ctime>
#include <msclr/marshal_cppstd.h>

namespace GraphDomApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

               private:
                System::Windows::Forms::Button ^ button1;

               private:
                System::Windows::Forms::TextBox ^ textBox1;

               private:
                System::Windows::Forms::Label ^ label1;

               private:
                System::Windows::Forms::DataGridView ^ dataGridView1;

               private:
                System::Windows::Forms::PictureBox ^ pictureBox1;

               private:
                System::Windows::Forms::Label ^ label2;

               private:
                System::Windows::Forms::TextBox ^ textBox2;

               private:
                System::Windows::Forms::Button ^ button2;

               private:
                System::Windows::Forms::Label ^ label3;

               private:
                System::Windows::Forms::TextBox ^ textBox3;

               private:
                System::Windows::Forms::Button ^ button3;

               private:
                System::Windows::Forms::TextBox ^ textBox4;

               private:
                System::Windows::Forms::TextBox ^ textBox5;

               private:
                System::Windows::Forms::Label ^ label4;

               private:
                System::Windows::Forms::Label ^ label5;

               private:
                System::Windows::Forms::Button ^ button4;

               private:
                System::Windows::Forms::Label ^ label6;

               private:
                System::Windows::Forms::Label ^ label7;

               private:
                System::Windows::Forms::TextBox ^ textBox6;

               private:
                System::Windows::Forms::TextBox ^ textBox7;

               private:


               protected: 

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
                  this->button1 = (gcnew System::Windows::Forms::Button());
                  this->textBox1 = (gcnew System::Windows::Forms::TextBox());
                  this->label1 = (gcnew System::Windows::Forms::Label());
                  this->dataGridView1 =
                      (gcnew System::Windows::Forms::DataGridView());
                  this->pictureBox1 =
                      (gcnew System::Windows::Forms::PictureBox());
                  this->label2 = (gcnew System::Windows::Forms::Label());
                  this->textBox2 = (gcnew System::Windows::Forms::TextBox());
                  this->button2 = (gcnew System::Windows::Forms::Button());
                  this->label3 = (gcnew System::Windows::Forms::Label());
                  this->textBox3 = (gcnew System::Windows::Forms::TextBox());
                  this->button3 = (gcnew System::Windows::Forms::Button());
                  this->textBox4 = (gcnew System::Windows::Forms::TextBox());
                  this->textBox5 = (gcnew System::Windows::Forms::TextBox());
                  this->label4 = (gcnew System::Windows::Forms::Label());
                  this->label5 = (gcnew System::Windows::Forms::Label());
                  this->button4 = (gcnew System::Windows::Forms::Button());
                  this->label6 = (gcnew System::Windows::Forms::Label());
                  this->label7 = (gcnew System::Windows::Forms::Label());
                  this->textBox6 = (gcnew System::Windows::Forms::TextBox());
                  this->textBox7 = (gcnew System::Windows::Forms::TextBox());
                  (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                       this->dataGridView1))
                      ->BeginInit();
                  (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                       this->pictureBox1))
                      ->BeginInit();
                  this->SuspendLayout();
                  //
                  // button1
                  //
                  this->button1->Location = System::Drawing::Point(45, 660);
                  this->button1->Margin = System::Windows::Forms::Padding(4);
                  this->button1->Name = L"button1";
                  this->button1->Size = System::Drawing::Size(207, 87);
                  this->button1->TabIndex = 0;
                  this->button1->Text = L"Create matrix";
                  this->button1->UseVisualStyleBackColor = true;
                  this->button1->Click +=
                      gcnew System::EventHandler(this, &MyForm::button1_Click);
                  //
                  // textBox1
                  //
                  this->textBox1->Location = System::Drawing::Point(45, 607);
                  this->textBox1->Margin = System::Windows::Forms::Padding(4);
                  this->textBox1->Name = L"textBox1";
                  this->textBox1->Size = System::Drawing::Size(205, 22);
                  this->textBox1->TabIndex = 1;
                  this->textBox1->Text = L"3";
                  //
                  // label1
                  //
                  this->label1->AutoSize = true;
                  this->label1->Location = System::Drawing::Point(41, 569);
                  this->label1->Margin =
                      System::Windows::Forms::Padding(4, 0, 4, 0);
                  this->label1->Name = L"label1";
                  this->label1->Size = System::Drawing::Size(211, 17);
                  this->label1->TabIndex = 2;
                  this->label1->Text = L"Number of vertices in the graph:";
                  //
                  // dataGridView1
                  //
                  this->dataGridView1->ColumnHeadersHeightSizeMode =
                      System::Windows::Forms::
                          DataGridViewColumnHeadersHeightSizeMode::AutoSize;
                  this->dataGridView1->Location =
                      System::Drawing::Point(16, 15);
                  this->dataGridView1->Margin =
                      System::Windows::Forms::Padding(4);
                  this->dataGridView1->Name = L"dataGridView1";
                  this->dataGridView1->RowHeadersWidth = 51;
                  this->dataGridView1->Size = System::Drawing::Size(961, 500);
                  this->dataGridView1->TabIndex = 3;
                  //
                  // pictureBox1
                  //
                  this->pictureBox1->Location = System::Drawing::Point(985, 15);
                  this->pictureBox1->Margin =
                      System::Windows::Forms::Padding(4);
                  this->pictureBox1->Name = L"pictureBox1";
                  this->pictureBox1->Size = System::Drawing::Size(1056, 933);
                  this->pictureBox1->TabIndex = 4;
                  this->pictureBox1->TabStop = false;
                  //
                  // label2
                  //
                  this->label2->AutoSize = true;
                  this->label2->Location = System::Drawing::Point(331, 569);
                  this->label2->Name = L"label2";
                  this->label2->Size = System::Drawing::Size(132, 17);
                  this->label2->TabIndex = 5;
                  this->label2->Text = L"Enter the desired k:";
                  //
                  // textBox2
                  //
                  this->textBox2->Location = System::Drawing::Point(333, 607);
                  this->textBox2->Margin =
                      System::Windows::Forms::Padding(3, 2, 3, 2);
                  this->textBox2->Name = L"textBox2";
                  this->textBox2->Size = System::Drawing::Size(129, 22);
                  this->textBox2->TabIndex = 6;
                  this->textBox2->Text = L"1";
                  //
                  // button2
                  //
                  this->button2->Location = System::Drawing::Point(312, 660);
                  this->button2->Margin =
                      System::Windows::Forms::Padding(3, 2, 3, 2);
                  this->button2->Name = L"button2";
                  this->button2->Size = System::Drawing::Size(175, 87);
                  this->button2->TabIndex = 7;
                  this->button2->Text = L"Calculate with HEU1";
                  this->button2->UseVisualStyleBackColor = true;
                  this->button2->Click +=
                      gcnew System::EventHandler(this, &MyForm::button2_Click);
                  //
                  // label3
                  //
                  this->label3->AutoSize = true;
                  this->label3->Location = System::Drawing::Point(576, 569);
                  this->label3->Name = L"label3";
                  this->label3->Size = System::Drawing::Size(178, 17);
                  this->label3->TabIndex = 8;
                  this->label3->Text = L"Enter the desired filename:";
                  //
                  // textBox3
                  //
                  this->textBox3->Location = System::Drawing::Point(579, 607);
                  this->textBox3->Margin =
                      System::Windows::Forms::Padding(3, 2, 3, 2);
                  this->textBox3->Name = L"textBox3";
                  this->textBox3->Size = System::Drawing::Size(175, 22);
                  this->textBox3->TabIndex = 9;
                  this->textBox3->Text = L"MyGraph";
                  //
                  // button3
                  //
                  this->button3->Location = System::Drawing::Point(579, 660);
                  this->button3->Margin =
                      System::Windows::Forms::Padding(3, 2, 3, 2);
                  this->button3->Name = L"button3";
                  this->button3->Size = System::Drawing::Size(175, 87);
                  this->button3->TabIndex = 10;
                  this->button3->Text = L"Open Image";
                  this->button3->UseVisualStyleBackColor = true;
                  this->button3->Click +=
                      gcnew System::EventHandler(this, &MyForm::button3_Click);
                  //
                  // textBox4
                  //
                  this->textBox4->Location = System::Drawing::Point(312, 806);
                  this->textBox4->Name = L"textBox4";
                  this->textBox4->Size = System::Drawing::Size(73, 22);
                  this->textBox4->TabIndex = 11;
                  this->textBox4->Text = L"1";
                  //
                  // textBox5
                  //
                  this->textBox5->Location = System::Drawing::Point(411, 806);
                  this->textBox5->Name = L"textBox5";
                  this->textBox5->Size = System::Drawing::Size(76, 22);
                  this->textBox5->TabIndex = 12;
                  this->textBox5->Text = L"0";
                  //
                  // label4
                  //
                  this->label4->AutoSize = true;
                  this->label4->Location = System::Drawing::Point(309, 774);
                  this->label4->Name = L"label4";
                  this->label4->Size = System::Drawing::Size(47, 17);
                  this->label4->TabIndex = 13;
                  this->label4->Text = L"alpha:";
                  //
                  // label5
                  //
                  this->label5->AutoSize = true;
                  this->label5->Location = System::Drawing::Point(408, 774);
                  this->label5->Name = L"label5";
                  this->label5->Size = System::Drawing::Size(69, 17);
                  this->label5->TabIndex = 14;
                  this->label5->Text = L"loop time:";
                  //
                  // button4
                  //
                  this->button4->Location = System::Drawing::Point(312, 851);
                  this->button4->Name = L"button4";
                  this->button4->Size = System::Drawing::Size(175, 97);
                  this->button4->TabIndex = 15;
                  this->button4->Text = L"Calculate with HEU2";
                  this->button4->UseVisualStyleBackColor = true;
                  this->button4->Click +=
                      gcnew System::EventHandler(this, &MyForm::button4_Click);
                  //
                  // label6
                  //
                  this->label6->AutoSize = true;
                  this->label6->Location = System::Drawing::Point(576, 773);
                  this->label6->Name = L"label6";
                  this->label6->Size = System::Drawing::Size(112, 17);
                  this->label6->TabIndex = 16;
                  this->label6->Text = L"HEU1 work time:";
                  //
                  // label7
                  //
                  this->label7->AutoSize = true;
                  this->label7->Location = System::Drawing::Point(576, 816);
                  this->label7->Name = L"label7";
                  this->label7->Size = System::Drawing::Size(112, 17);
                  this->label7->TabIndex = 17;
                  this->label7->Text = L"HEU2 work time:";
                  //
                  // textBox6
                  //
                  this->textBox6->Location = System::Drawing::Point(704, 773);
                  this->textBox6->Name = L"textBox6";
                  this->textBox6->Size = System::Drawing::Size(100, 22);
                  this->textBox6->TabIndex = 18;
                  //
                  // textBox7
                  //
                  this->textBox7->Location = System::Drawing::Point(704, 816);
                  this->textBox7->Name = L"textBox7";
                  this->textBox7->Size = System::Drawing::Size(100, 22);
                  this->textBox7->TabIndex = 19;
                  //
                  // MyForm
                  //
                  this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
                  this->AutoScaleMode =
                      System::Windows::Forms::AutoScaleMode::Font;
                  this->ClientSize = System::Drawing::Size(1924, 961);
                  this->Controls->Add(this->textBox7);
                  this->Controls->Add(this->textBox6);
                  this->Controls->Add(this->label7);
                  this->Controls->Add(this->label6);
                  this->Controls->Add(this->button4);
                  this->Controls->Add(this->label5);
                  this->Controls->Add(this->label4);
                  this->Controls->Add(this->textBox5);
                  this->Controls->Add(this->textBox4);
                  this->Controls->Add(this->button3);
                  this->Controls->Add(this->textBox3);
                  this->Controls->Add(this->label3);
                  this->Controls->Add(this->button2);
                  this->Controls->Add(this->textBox2);
                  this->Controls->Add(this->label2);
                  this->Controls->Add(this->pictureBox1);
                  this->Controls->Add(this->dataGridView1);
                  this->Controls->Add(this->label1);
                  this->Controls->Add(this->textBox1);
                  this->Controls->Add(this->button1);
                  this->Margin = System::Windows::Forms::Padding(4);
                  this->Name = L"MyForm";
                  this->Text = L"MyForm";
                  (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                       this->dataGridView1))
                      ->EndInit();
                  (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                       this->pictureBox1))
                      ->EndInit();
                  this->ResumeLayout(false);
                  this->PerformLayout();
                }
#pragma endregion
               private:
                System::Void button1_Click(System::Object ^ sender,
                                           System::EventArgs ^ e) {

                  int number = System::Convert::ToInt32(textBox1->Text);

                  dataGridView1->Columns->Clear();
                  dataGridView1->Rows->Clear();
                  for (int i = 0; i < number; i++) {
                    DataGridViewTextBoxColumn ^ column =
                        gcnew DataGridViewTextBoxColumn();
                    column->Width = 30;
                    dataGridView1->Columns->Add(column);
                    dataGridView1->Rows->Add();
                  }

                  // Задание заголовков столбцов и строк
                  for (int i = 0; i < number; i++) {
                    dataGridView1->Columns[i]->HeaderText = (i + 1).ToString();
                    dataGridView1->Rows[i]->HeaderCell->Value =
                        (i + 1).ToString();
                  }
                  

                  button1->Text = "Matrix created!";
                  
								}

              private:
               System::Void button2_Click(System::Object ^ sender,
                                     System::EventArgs ^ e) {
                 
                 // Получение размера матрицы смежности
                 int size = dataGridView1->RowCount - 1;

                 // Создание матрицы смежности
                 std::vector<std::vector<int>> adjacencyMatrix(
                     size, std::vector<int>(size));

                 // Заполнение матрицы смежности данными из DataGridView
                 for (int i = 0; i < size; i++) {
                   for (int j = 0; j < size; j++) {
                     DataGridViewCell ^ cell = dataGridView1->Rows[i]->Cells[j];
                     if (cell->Value != nullptr) {
                       int value;
                       if (Int32::TryParse(cell->Value->ToString(), value)) {
                         adjacencyMatrix[i][j] = value;
                       }
                     }
                   }
                 }

                 msclr::interop::marshal_context context;
                 std::string str = context.marshal_as<std::string>(textBox3->Text);  //Для получения строки
                 int k = System::Convert::ToInt32(textBox2->Text);

                 vector<int> domSet;
                 vector<int> weights(adjacencyMatrix.size(), 0);

                 double start = 0;
                 start = clock();
                 domSet = romanKDomSetHEU1(adjacencyMatrix, k, weights);
                 double time = (clock() - start) / 1000.0;
                 textBox6->Text = time.ToString();
                 
                 generateWeightsGraphvizFile(adjacencyMatrix, str, domSet, weights);
               }

              private:
               System::Void button3_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
                 OpenFileDialog ^ openFileDialog = gcnew OpenFileDialog();
                 openFileDialog->Filter = "PNG Files (*.png)|*.png";
                 openFileDialog->Title = "Выберите изображение PNG";

                 if (openFileDialog->ShowDialog() ==
                     System::Windows::Forms::DialogResult::OK) {
                   String ^ imagePath = openFileDialog->FileName;
                   Image ^ image = Image::FromFile(imagePath);
                   pictureBox1->Image = image;
                 }
               }

              private:
               System::Void button4_Click(System::Object ^ sender,
                                          System::EventArgs ^ e) {
                 // Получение размера матрицы смежности
                 int size = dataGridView1->RowCount - 1;

                 // Создание матрицы смежности
                 std::vector<std::vector<int>> adjacencyMatrix(
                     size, std::vector<int>(size));

                 // Заполнение матрицы смежности данными из DataGridView
                 for (int i = 0; i < size; i++) {
                   for (int j = 0; j < size; j++) {
                     DataGridViewCell ^ cell = dataGridView1->Rows[i]->Cells[j];
                     if (cell->Value != nullptr) {
                       int value;
                       if (Int32::TryParse(cell->Value->ToString(), value)) {
                         adjacencyMatrix[i][j] = value;
                       }
                     }
                   }
                 }

                 msclr::interop::marshal_context context;
                 std::string str = context.marshal_as<std::string>(
                     textBox3->Text);  //Для получения строки
                 int k = System::Convert::ToInt32(textBox2->Text);
                 int alpha = System::Convert::ToInt32(textBox4->Text);
                 double loopTime = System::Convert::ToDouble(textBox5->Text);

                 vector<int> domSet;
                 vector<int> weights(adjacencyMatrix.size(), 0);

                 double start = 0;
                 start = clock();
                 domSet = romanKDomSetHEU2(adjacencyMatrix, k, weights, alpha, loopTime);
                 double time = (clock() - start) / 1000.0;
                 textBox7->Text = time.ToString();

                 generateWeightsGraphvizFile(adjacencyMatrix, str, domSet,
                                             weights);
               }
         };
         }
