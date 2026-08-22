#pragma once

#include "BLOOD_BANK.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace msclr::interop;
public ref class MainForm : public System::Windows::Forms::Form
{
public:
    MainForm(void)
    {
        InitializeComponent();
        this->Load += gcnew EventHandler(this, &MainForm::MainForm_Load);
    }

protected:
    ~MainForm()
    {
        if (components)
        {
            delete components;
        }
    }

private:
    System::ComponentModel::Container^ components;

    // ===================== CONTROLS =====================
    ComboBox^ comboAddType;
    DateTimePicker^ dateExpiration;
    Button^ btnAddBlood;

    TextBox^ txtHospital;
    ComboBox^ comboRequestType;
    Button^ btnRequestBlood;

    DataGridView^ gridInventory;
private: System::Windows::Forms::Label^ label1;
       DataGridView^ gridLogs;

#pragma region Windows Form Designer generated code
    void InitializeComponent(void)
    {
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->SuspendLayout();
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(0, 0);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(35, 13);
        this->label1->TabIndex = 0;
        this->label1->Text = L"label1";
        // 
        // MainForm
        // 
        this->ClientSize = System::Drawing::Size(1546, 645);
        this->Controls->Add(this->label1);
        this->Name = L"MainForm";
        this->ResumeLayout(false);
        this->PerformLayout();

    }
#pragma endregion

    // ===================== HELPERS =====================
    string toStd(String^ s)
    {
        return marshal_as<string>(s);
    }

    // ===================== EVENTS =====================
    void MainForm_Load(Object^ sender, EventArgs^ e)
    {
        cli::array<String^>^ bloodTypes = gcnew cli::array<String^>{
            "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
        };

        comboAddType->Items->AddRange(bloodTypes);
        comboRequestType->Items->AddRange(bloodTypes);

        comboAddType->SelectedIndex = 0;
        comboRequestType->SelectedIndex = 0;

        refreshInventory();
        refreshLogs();
    }

    void btnAddBlood_Click(Object^ sender, EventArgs^ e)
    {
        string type = toStd(comboAddType->Text);
        string exp = toStd(dateExpiration->Text);

        string result = addBlood(type, exp);

        MessageBox::Show(gcnew String(result.c_str()));
        refreshInventory();
    }

    void btnRequestBlood_Click(Object^ sender, EventArgs^ e)
    {
        string hospital = toStd(txtHospital->Text);
        string reqType = toStd(comboRequestType->Text);

        string result = requestBlood(hospital, reqType);

        MessageBox::Show(gcnew String(result.c_str()));
        refreshInventory();
        refreshLogs();
    }

    // ===================== REFRESH =====================
    void refreshInventory()
    {
        gridInventory->Rows->Clear();

        auto data = getInventoryData();
        for (auto& item : data)
        {
            gridInventory->Rows->Add(
                gcnew String(item.first.c_str()),
                item.second
            );
        }
    }

    void refreshLogs()
    {
        gridLogs->Rows->Clear();

        auto data = getLogs();
        for (auto& l : data)
        {
            gridLogs->Rows->Add(
                gcnew String(l.hospital.c_str()),
                gcnew String(l.requested.c_str()),
                gcnew String(l.allocated.c_str()),
                l.unitID,
                gcnew String(l.reason.c_str())
            );
        }
    }
};

