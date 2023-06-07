#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread] void main(array<String ^> ^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  GraphDomApp::MyForm form;
  Application::Run(% form);
}