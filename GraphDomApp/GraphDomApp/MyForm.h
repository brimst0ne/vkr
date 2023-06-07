#pragma once

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
                  this->dataGridView1->Size = System::Drawing::Size(721, 406);
                  this->dataGridView1->TabIndex = 3;
                  //
                  // pictureBox1
                  //
                  this->pictureBox1->Location = System::Drawing::Point(739, 12);
                  this->pictureBox1->Name = L"pictureBox1";
                  this->pictureBox1->Size = System::Drawing::Size(700, 619);
                  this->pictureBox1->TabIndex = 4;
                  this->pictureBox1->TabStop = false;
                  //
                  // MyForm
                  //
                  this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                  this->AutoScaleMode =
                      System::Windows::Forms::AutoScaleMode::Font;
                  this->ClientSize = System::Drawing::Size(1449, 638);
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
                    dataGridView1->Columns->Add(
                        gcnew DataGridViewTextBoxColumn());
                    dataGridView1->Rows->Add();
                  }

                  // Задание заголовков столбцов и строк
                  for (int i = 0; i < number; i++) {
                    dataGridView1->Columns[i]->HeaderText = (i + 1).ToString();
                    dataGridView1->Rows[i]->HeaderCell->Value =
                        (i + 1).ToString();
                  }
                  OpenFileDialog ^ openFileDialog = gcnew OpenFileDialog();
                  openFileDialog->Filter = "PNG Files (*.png)|*.png";
                  openFileDialog->Title = "Выберите изображение PNG";

                  if (openFileDialog->ShowDialog() ==
                      System::Windows::Forms::DialogResult::OK) {
                    String ^ imagePath = openFileDialog->FileName;
                    Image ^ image = Image::FromFile(imagePath);
                    pictureBox1->Image = image;
                  }

                  button1->Text = "Matrix created!";
                  
								}

               private:

         };
         }
