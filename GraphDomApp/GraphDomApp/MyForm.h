#pragma once

#include "utils.h"
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
                  this->button1->Location = System::Drawing::Point(34, 536);
                  this->button1->Name = L"button1";
                  this->button1->Size = System::Drawing::Size(155, 71);
                  this->button1->TabIndex = 0;
                  this->button1->Text = L"Create matrix";
                  this->button1->UseVisualStyleBackColor = true;
                  this->button1->Click +=
                      gcnew System::EventHandler(this, &MyForm::button1_Click);
                  //
                  // textBox1
                  //
                  this->textBox1->Location = System::Drawing::Point(34, 493);
                  this->textBox1->Name = L"textBox1";
                  this->textBox1->Size = System::Drawing::Size(155, 20);
                  this->textBox1->TabIndex = 1;
                  this->textBox1->Text = L"3";
                  //
                  // label1
                  //
                  this->label1->AutoSize = true;
                  this->label1->Location = System::Drawing::Point(31, 462);
                  this->label1->Name = L"label1";
                  this->label1->Size = System::Drawing::Size(158, 13);
                  this->label1->TabIndex = 2;
                  this->label1->Text = L"Number of vertices in the graph:";
                  //
                  // dataGridView1
                  //
                  this->dataGridView1->ColumnHeadersHeightSizeMode =
                      System::Windows::Forms::
                          DataGridViewColumnHeadersHeightSizeMode::AutoSize;
                  this->dataGridView1->Location =
                      System::Drawing::Point(12, 12);
                  this->dataGridView1->Name = L"dataGridView1";
                  this->dataGridView1->RowHeadersWidth = 51;
                  this->dataGridView1->Size = System::Drawing::Size(721, 406);
                  this->dataGridView1->TabIndex = 3;
                  //
                  // pictureBox1
                  //
                  this->pictureBox1->Location = System::Drawing::Point(739, 12);
                  this->pictureBox1->Name = L"pictureBox1";
                  this->pictureBox1->Size = System::Drawing::Size(792, 758);
                  this->pictureBox1->TabIndex = 4;
                  this->pictureBox1->TabStop = false;
                  //
                  // label2
                  //
                  this->label2->AutoSize = true;
                  this->label2->Location = System::Drawing::Point(248, 462);
                  this->label2->Margin =
                      System::Windows::Forms::Padding(2, 0, 2, 0);
                  this->label2->Name = L"label2";
                  this->label2->Size = System::Drawing::Size(99, 13);
                  this->label2->TabIndex = 5;
                  this->label2->Text = L"Enter the desired k:";
                  //
                  // textBox2
                  //
                  this->textBox2->Location = System::Drawing::Point(250, 493);
                  this->textBox2->Margin =
                      System::Windows::Forms::Padding(2, 2, 2, 2);
                  this->textBox2->Name = L"textBox2";
                  this->textBox2->Size = System::Drawing::Size(98, 20);
                  this->textBox2->TabIndex = 6;
                  this->textBox2->Text = L"1";
                  //
                  // button2
                  //
                  this->button2->Location = System::Drawing::Point(234, 536);
                  this->button2->Margin =
                      System::Windows::Forms::Padding(2, 2, 2, 2);
                  this->button2->Name = L"button2";
                  this->button2->Size = System::Drawing::Size(131, 71);
                  this->button2->TabIndex = 7;
                  this->button2->Text = L"Calculate";
                  this->button2->UseVisualStyleBackColor = true;
                  this->button2->Click +=
                      gcnew System::EventHandler(this, &MyForm::button2_Click);
                  //
                  // label3
                  //
                  this->label3->AutoSize = true;
                  this->label3->Location = System::Drawing::Point(432, 462);
                  this->label3->Margin =
                      System::Windows::Forms::Padding(2, 0, 2, 0);
                  this->label3->Name = L"label3";
                  this->label3->Size = System::Drawing::Size(132, 13);
                  this->label3->TabIndex = 8;
                  this->label3->Text = L"Enter the desired filename:";
                  //
                  // textBox3
                  //
                  this->textBox3->Location = System::Drawing::Point(434, 493);
                  this->textBox3->Margin =
                      System::Windows::Forms::Padding(2, 2, 2, 2);
                  this->textBox3->Name = L"textBox3";
                  this->textBox3->Size = System::Drawing::Size(132, 20);
                  this->textBox3->TabIndex = 9;
                  this->textBox3->Text = L"MyGraph";
                  //
                  // button3
                  //
                  this->button3->Location = System::Drawing::Point(434, 536);
                  this->button3->Margin =
                      System::Windows::Forms::Padding(2, 2, 2, 2);
                  this->button3->Name = L"button3";
                  this->button3->Size = System::Drawing::Size(131, 71);
                  this->button3->TabIndex = 10;
                  this->button3->Text = L"Open Image";
                  this->button3->UseVisualStyleBackColor = true;
                  this->button3->Click +=
                      gcnew System::EventHandler(this, &MyForm::button3_Click);
                  //
                  // MyForm
                  //
                  this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                  this->AutoScaleMode =
                      System::Windows::Forms::AutoScaleMode::Font;
                  this->ClientSize = System::Drawing::Size(1543, 781);
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

                 // Вывод матрицы смежности на консоль (для проверки)
                 for (int i = 0; i < size; i++) {
                   for (int j = 0; j < size; j++) {
                     std::cout << adjacencyMatrix[i][j] << " ";
                   }
                   std::cout << std::endl;
                 }

                 //adjacencyMatrix = BA_graph(30, 2);

                 msclr::interop::marshal_context context;
                 std::string str = context.marshal_as<std::string>(textBox3->Text);
                 int k = System::Convert::ToInt32(textBox2->Text);

                 /*vector<int> domSet =
                     HEU1(adjacencyMatrix, adjacencyMatrix.size(), k);
                 generateGraphvizFile(adjacencyMatrix, str, domSet);*/
                 //vector<int> partition = splitGraphNew(adjacencyMatrix);
                 vector<int> domSet;
                 /*if (k == 1) {
                   domSet = HEU1(adjacencyMatrix, adjacencyMatrix.size(), k);
                 } else {
                   domSet = romanKDomSet(adjacencyMatrix, k);
                 }*/
                 domSet = romanKDomSet(adjacencyMatrix, k);
                 
                 generateGraphvizFile(adjacencyMatrix, str, domSet);
                 //vector<int> partition;
                 //graphCut(adjacencyMatrix, partition);
                 //branchAndBoundGraphPartitioning(adjacencyMatrix, partition);
                 //generatePartitionGraphvizFile(adjacencyMatrix, str, partition);
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
         };
         }
