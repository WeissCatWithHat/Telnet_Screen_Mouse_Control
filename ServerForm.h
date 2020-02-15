#pragma once

namespace TelnetServer {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ServerForm 的摘要
	/// </summary>
	public ref class ServerForm : public System::Windows::Forms::Form
	{
	public:
		ServerForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~ServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Runtime::Remoting::Channels::Http::HttpChannel^ httpchannel;
			 RemoteControl^ remotecontrol;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 443);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 26);
			this->button1->TabIndex = 0;
			this->button1->Text = L"連結";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ServerForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(93, 443);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(472, 25);
			this->textBox1->TabIndex = 1;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ServerForm::timer1_Tick);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(576, 425);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ServerForm::desktopPicture_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ServerForm::desktopPicture_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ServerForm::desktopPicture_MouseUp);
			// 
			// ServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(576, 478);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"ServerForm";
			this->Text = L"ServerForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		bool connected;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			String^ remotehost = textBox1->Text;
		try {
				
				
				httpchannel = gcnew System::Runtime::Remoting::Channels::Http::HttpChannel();		
				System::Runtime::Remoting::Channels::ChannelServices::RegisterChannel(httpchannel, false);
				String^ url = "http://" + remotehost + ":8080/RemoteSlave";	
				remotecontrol = safe_cast<RemoteControl^>(System::Activator::GetObject(RemoteControl::typeid, url));
				this->connected = true;
				timer1->Enabled = true;
				this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				//this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				//this->WindowState = System::Windows::Forms::FormWindowState::Maximized;

				button1->Text = "斷開";
		}
		catch (Exception^ ex) {
			System::Runtime::Remoting::Channels::ChannelServices::UnregisterChannel(httpchannel);
		}
		

	}
	

	 private: System::Void desktopPicture_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 if (connected == true)
					 remotecontrol->MouseButtonCall(true, e->Button == System::Windows::Forms::MouseButtons::Left, e->X, e->Y);
			 }

	private: System::Void desktopPicture_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 if (connected == true)
		  remotecontrol->MouseButtonCall(false, e->Button == System::Windows::Forms::MouseButtons::Left, e->X, e->Y);
			}

	private: System::Void desktopPicture_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	    if (connected == true)
		  remotecontrol->MoveMouse(e->X, e->Y);
		  }

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		try
		{	
			array<Byte>^ buffer = remotecontrol->GetDesktopBuffer();
			System::IO::MemoryStream^ memStream = gcnew MemoryStream(buffer);
			pictureBox1->Image = System::Drawing::Image::FromStream(memStream);
		
		}
		catch (Exception^ ex)
		{
			connected = false;
			//System::Runtime::Remoting::Channels::ChannelServices::UnregisterChannel(httpchannel);
		}
	
	}
};
}
