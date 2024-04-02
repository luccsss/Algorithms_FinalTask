#pragma once
#include "CControladora.h"

namespace EXAMENFINAL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	private:
		int seg;
		bool unavez;
	private:
		Bitmap^ img;
	private:
		Graphics^ g;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ cronometro;
	private: System::Windows::Forms::TextBox^ textBox1;

	private:
		CControladora* obj;
	public:
		Juego(void)
		{
			seg = 0;
			unavez = true;
			InitializeComponent();
			srand(time(NULL));
			g = this->CreateGraphics();
			obj = new CControladora(ClientRectangle.Width, ClientRectangle.Height);
			img = gcnew Bitmap("Imagenes//fondo1.png");

			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
				delete g;
				delete obj;
				delete img;
			}
		}

	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->cronometro = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// cronometro
			// 
			this->cronometro->Interval = 1000;
			this->cronometro->Tick += gcnew System::EventHandler(this, &Juego::timer2_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(1053, 10);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(76, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Juego::textBox1_TextChanged);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1292, 730);
			this->Controls->Add(this->textBox1);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Juego::Juego_FormClosing);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Juego_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::Juego_KeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		BufferedGraphics^ buffi = BufferedGraphicsManager::Current->Allocate(g, this->ClientRectangle);
		buffi->Graphics->DrawImage(img, this->ClientRectangle, this->ClientRectangle, GraphicsUnit::Pixel);
		obj->dibujarhero1(buffi->Graphics);

		obj->animacionrayo(buffi->Graphics);
		obj->animacionaliado(buffi->Graphics);
		obj->animacionDragon(buffi->Graphics);
		obj->animacionvidas(buffi->Graphics);

		obj->colisiones_dragon_hero(buffi->Graphics);
		obj->colisiones_rayo_dragon(buffi->Graphics);
		obj->colisiones_aliado_dragon(buffi->Graphics);

		textBox1->Text = "Puntos: " + obj->getpuntos();

		if (seg == 5) {
			obj->setVisibleHero2(2); cronometro->Enabled = false;
			obj->superpoder(2);
			unavez = false;
		}
		//Eliminar
		obj->eliminar(buffi->Graphics);
		//eliminar
		buffi->Render(g);
		delete buffi;
		// perder
		if (obj->terminar()) {
			timer1->Enabled = false;
			MessageBox::Show("TERMINO EL JUEGO");
			this->Close();
		}
		// ganar
		if (obj->ganar()) {
			timer1->Enabled = false;
			MessageBox::Show("FELICIDADES! HAS GANADO");
			this->Close();
		}
	}		

	private: System::Void Juego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::W:
			obj->moverhero1(g, 'W'); break;
		case Keys::S:
			obj->moverhero1(g, 'S'); break;
		case Keys::A:
			obj->moverhero1(g, 'A'); break;
		case Keys::D:
			obj->moverhero1(g, 'D'); break;
		case Keys::P:
			if (unavez) {
				obj->setVisibleHero2(1);
				cronometro->Enabled = true;
				obj->superpoder(1);

			}
			break;
		case Keys::Space:
			if (cronometro->Enabled==true)
			{
				obj->agregaraliado();			
				break;
			}
			else
			{
				obj->agregarrayo();
				break;
			}
		default:
			break;
		}
	}
	private: System::Void Juego_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		timer1->Enabled = false;
	}

	private: System::Void Juego_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		obj->moverhero1(g, 'N');
	}
	private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
		seg++;
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
