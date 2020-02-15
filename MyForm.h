#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>


namespace TelnetClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows;
	using namespace System::Runtime::Remoting;
	using namespace System::Runtime::Remoting::Channels;
	using namespace System::Runtime::Remoting::Channels::Http;

	/// <summary>
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(267, 67);
			this->ControlBox = false;
			this->Name = L"MyForm";
			this->Opacity = 0;
			this->ShowInTaskbar = false;
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		
		HttpChannel^ httpchannel;
		try {
			
			httpchannel = gcnew System::Runtime::Remoting::Channels::Http::HttpChannel(8080);
			System::Runtime::Remoting::Channels::ChannelServices::RegisterChannel(httpchannel, false);
			System::Runtime::Remoting::WellKnownServiceTypeEntry^ entry = gcnew WellKnownServiceTypeEntry(RemoteControl::typeid, "RemoteSlave", WellKnownObjectMode::SingleCall);
			System::Runtime::Remoting::RemotingConfiguration::RegisterWellKnownServiceType(entry);
			
		}
		catch (Exception^ ex) {
			//System::Runtime::Remoting::Channels::ChannelServices::UnregisterChannel(httpchannel);
		}
	}
	};
}
