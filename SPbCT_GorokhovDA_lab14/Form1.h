#pragma once

#include <string>
#include <vector>

// Класс для описания позиции фигуры на доске
class point {
public:
	point(int _x = 0, int _y = 0) {
		x = _x;
		y = _y;
	}

	int x;
	int y;

	// Перегрузка операции присваивания
	point& operator=(const point p) {
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
};

// Основной класс для описания шахматной фигуры
class chess_piece {
public:
	chess_piece() {
		position = point(0, 0);
		type_name = "";
	}

	chess_piece(point pos, std::string _type_name) {
		position = pos;
		type_name = _type_name;
	}

	point position;

	// Метод для перемещения фигуры
	void move(point new_pos) {
		position = new_pos;
	}

	// Виртуальный метод для получения позиций, которые может съесть фигура
	virtual std::vector<point> get_points_to_eat() {
		std::vector<point> tmp;
		throw;
		return tmp;
	}
protected:
	std::string type_name;
};

// Унаследованный от шахматной фигуры класс фигуры коня
class hourse : public chess_piece {
public:
	hourse(point pos) : chess_piece(pos, "hourse") {}

	std::vector<point> get_points_to_eat() {
		int x = position.x;
		int y = position.y;

		std::vector<point> possible_eats;

		if (x + 1 < 8 && y - 2 < 8 && x + 1 >= 0 && y - 2 >= 0) possible_eats.push_back(point(x + 1, y - 2));
		if (x - 1 < 8 && y - 2 < 8 && x - 1 >= 0 && y - 2 >= 0) possible_eats.push_back(point(x - 1, y - 2));
		if (x + 1 < 8 && y + 2 < 8 && x + 1 >= 0 && y + 2 >= 0) possible_eats.push_back(point(x + 1, y + 2));
		if (x - 1 < 8 && y + 2 < 8 && x - 1 >= 0 && y + 2 >= 0) possible_eats.push_back(point(x - 1, y + 2));

		if (x - 2 < 8 && y + 1 < 8 && x - 2 >= 0 && y + 1 >= 0) possible_eats.push_back(point(x - 2, y + 1));
		if (x - 2 < 8 && y - 1 < 8 && x - 2 >= 0 && y - 1 >= 0) possible_eats.push_back(point(x - 2, y - 1));
		if (x + 2 < 8 && y + 1 < 8 && x + 2 >= 0 && y + 1 >= 0) possible_eats.push_back(point(x + 2, y + 1));
		if (x + 2 < 8 && y - 1 < 8 && x + 2 >= 0 && y - 1 >= 0) possible_eats.push_back(point(x + 2, y - 1));

		return possible_eats;
	}
};

// Унаследованный от шахматной фигуры класс фигуры пешки
class pawn : public chess_piece {
public:
	pawn(point pos) : chess_piece(pos, "pawn") {}

	std::vector<point> get_points_to_eat() {
		int x = position.x;
		int y = position.y;

		std::vector<point> possible_eats;

		if (x + 1 < 8 && y - 1 < 8 && x + 1 >= 0 && y - 1 >= 0) possible_eats.push_back(point(x + 1, y - 1));
		if (x + 1 < 8 && y + 1 < 8 && x + 1 >= 0 && y + 1 >= 0) possible_eats.push_back(point(x + 1, y + 1));

		return possible_eats;
	}
};

// Унаследованный от шахматной фигуры класс фигуры ферзя
class queen : public chess_piece {
public:
	queen(point pos) : chess_piece(pos, "queen") {}

	std::vector<point> get_points_to_eat() {
		int x = position.x;
		int y = position.y;

		std::vector<point> possible_eats;

		while (x++ < 8) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;

		while (x-- >= 0) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;

		while (y++ < 8) {
			possible_eats.push_back(point(x, y));
		}
		y = position.y;

		while (y-- >= 0) {
			possible_eats.push_back(point(x, y));
		}
		y = position.y;

		while (x++ < 8 && y++ < 8) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;
		y = position.y;

		while (x-- >= 0 && y-- >= 0) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;
		y = position.y;

		while (x-- >= 0 && y++ < 8) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;
		y = position.y;

		while (x++ < 8 && y-- >= 0) {
			possible_eats.push_back(point(x, y));
		}
		x = position.x;
		y = position.y;

		return possible_eats;
	}
};

// Класс шахматной доски
class chess_board {
public:
	chess_board() {
	}

	~chess_board() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				content[i][j].erase();
			}
		}
	}

	std::string content[8][8];

	// Метод для инициализации хранилища
	void init() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				content[i][j] = "";
			}
		}
	}

	// Метод для добавления фигуры на доску
	void add(point pos, std::string type_name) {
		content[pos.x][pos.y] = type_name;
	}

	// Метод для удаления фигуры с доски
	void remove(point pos) {
		content[pos.x][pos.y] = "";
	}

	// Метод для вычисления возможных к съедению фигур.
	// На вход получает позицию фигуры, которая будет ходить
	std::vector<point> check_eats(point pos) {
		std::string chess_piece_desc = content[pos.x][pos.y];

		std::vector<point> points_to_eat;

		if (chess_piece_desc == "hourse") {
			hourse figure = hourse(pos);
			points_to_eat = figure.get_points_to_eat();
		} else if (chess_piece_desc == "pawn") {
			pawn figure = pawn(pos);
			points_to_eat = figure.get_points_to_eat();
		} else if (chess_piece_desc == "queen") {
			queen figure = queen(pos);
			points_to_eat = figure.get_points_to_eat();
		}

		std::vector<point> eats;
		for (int i = 0; i < points_to_eat.size(); i++) {
			int x = points_to_eat[i].x;
			int y = points_to_eat[i].y;

			std::string selected_type_name = content[x][y];
			if (selected_type_name != "") {
				point pos = point(x, y);

				eats.push_back(pos);
			}
		}

		return eats;
	}
};

// Инициализация и определение глобальной переменной для хранения шахмотной доски
chess_board chess_board_ins = chess_board();

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		// Инициализация формы
		Form1(void)
		{
			InitializeComponent();
			
			// Инициализация шахматной доски
			chess_board_ins.init();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ A;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ B;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ C;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ D;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ E;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ F;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ H;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ G;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Label^ label2;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->A = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->B = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->C = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->D = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->E = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->F = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->H = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->G = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(437, 622);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(673, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Вычислить фигуры, которые может съесть выделенная фигура";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {
				this->A, this->B,
					this->C, this->D, this->E, this->F, this->H, this->G
			});
			this->dataGridView1->Location = System::Drawing::Point(464, 6);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(661, 438);
			this->dataGridView1->TabIndex = 1;
			// 
			// A
			// 
			this->A->HeaderText = L"A";
			this->A->MinimumWidth = 6;
			this->A->Name = L"A";
			this->A->ReadOnly = true;
			this->A->Width = 75;
			// 
			// B
			// 
			this->B->HeaderText = L"B";
			this->B->MinimumWidth = 6;
			this->B->Name = L"B";
			this->B->ReadOnly = true;
			this->B->Width = 75;
			// 
			// C
			// 
			this->C->HeaderText = L"C";
			this->C->MinimumWidth = 6;
			this->C->Name = L"C";
			this->C->ReadOnly = true;
			this->C->Width = 75;
			// 
			// D
			// 
			this->D->HeaderText = L"D";
			this->D->MinimumWidth = 6;
			this->D->Name = L"D";
			this->D->ReadOnly = true;
			this->D->Width = 75;
			// 
			// E
			// 
			this->E->HeaderText = L"E";
			this->E->MinimumWidth = 6;
			this->E->Name = L"E";
			this->E->ReadOnly = true;
			this->E->Width = 75;
			// 
			// F
			// 
			this->F->HeaderText = L"F";
			this->F->MinimumWidth = 6;
			this->F->Name = L"F";
			this->F->ReadOnly = true;
			this->F->Width = 75;
			// 
			// H
			// 
			this->H->HeaderText = L"H";
			this->H->MinimumWidth = 6;
			this->H->Name = L"H";
			this->H->ReadOnly = true;
			this->H->Width = 75;
			// 
			// G
			// 
			this->G->HeaderText = L"G";
			this->G->MinimumWidth = 6;
			this->G->Name = L"G";
			this->G->ReadOnly = true;
			this->G->Width = 75;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(35, 373);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(217, 41);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Создать доску";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(35, 496);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(217, 41);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Добавить коня";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Location = System::Drawing::Point(35, 543);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(217, 41);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Добавить пешку";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->Location = System::Drawing::Point(35, 590);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(217, 41);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Добавить ферзя";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(30, 452);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(450, 25);
			this->label1->TabIndex = 6;
			this->label1->Text = L"В выделенную клетку можно добавить фигуру";
			// 
			// button6
			// 
			this->button6->Enabled = false;
			this->button6->Location = System::Drawing::Point(35, 637);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(217, 36);
			this->button6->TabIndex = 7;
			this->button6->Text = L"Удалить фигуру";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(572, 559);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(426, 25);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Конь = hourse; пешка = pawn; ферзь = queen";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1529, 700);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form1";
			this->Text = L"Лабораторная работа №14";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// Описание функции-обработчика клика по кнопке создания доски
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	for (int i = 0; i < 8; i++) {
		this->dataGridView1->Rows->Add();
		this->dataGridView1->Rows[i]->HeaderCell->Value = (i + 1).ToString();
	}

		this->button2->Enabled = false;

		this->button1->Enabled = true;
		this->button3->Enabled = true;
		this->button4->Enabled = true;
		this->button5->Enabled = true;
		this->button6->Enabled = true;
	}

// Описание функции-обработчика клика по кнопке добавления коня
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	auto selected_cell = this->dataGridView1->SelectedCells[0];

	selected_cell->Value = "Конь";

	point selected_pos = point(selected_cell->ColumnIndex, selected_cell->RowIndex);

	chess_board_ins.add(selected_pos, "hourse");
}

// Описание функции-обработчика клика по кнопке добавления пешки
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	auto selected_cell = this->dataGridView1->SelectedCells[0];

	selected_cell->Value = "Пешка";

	point selected_pos = point(selected_cell->ColumnIndex, selected_cell->RowIndex);

	chess_board_ins.add(selected_pos, "pawn");
}

// Описание функции-обработчика клика по кнопке добавления ферзя
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	auto selected_cell = this->dataGridView1->SelectedCells[0];

	selected_cell->Value = "Ферзь";

	point selected_pos = point(selected_cell->ColumnIndex, selected_cell->RowIndex);

	chess_board_ins.add(selected_pos, "queen");
}

// Описание функции-обработчика клика по кнопке вычисления фигур, которые можно съесть
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	auto selected_cell = this->dataGridView1->SelectedCells[0];

	if (!selected_cell->Value || selected_cell->Value == "") {
		String^ message = "В выбранной клетке нет фигуры";
		String^ title = "Ошибка!";

		MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		point selected_pos = point(selected_cell->ColumnIndex, selected_cell->RowIndex);

		std::vector<point> eats = chess_board_ins.check_eats(selected_pos);

		String^ message = "Выбранная фигура может съесть фигур: " + eats.size();
		String^ title = "Успех!";

		String^ ix_to_char = "ABCDEFGH";

		for (int i = 0; i < eats.size(); i++) {
			point pos_to_eat = eats[i];

			message += "\n";
			message += gcnew String(chess_board_ins.content[pos_to_eat.x][pos_to_eat.y].data());
			message += " с позицией " + ix_to_char[pos_to_eat.x] + " " + (pos_to_eat.y + 1);
		}

		MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}

// Описание функции-обработчика клика по кнопке удаления фигуры
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	auto selected_cell = this->dataGridView1->SelectedCells[0];

	selected_cell->Value = "";

	point selected_pos = point(selected_cell->ColumnIndex, selected_cell->RowIndex);

	chess_board_ins.remove(selected_pos);
}
};
}
