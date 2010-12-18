// TestApp.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace Ambiesoft;

int main(array<System::String ^> ^args)
{
	SimpleCommandLineParser^ parser = gcnew SimpleCommandLineParser(args);
	parser->addOption("h", ARGUMENT_TYPE::MUSTNOT, "Show Help");
	parser->addOption("?", ARGUMENT_TYPE::MUSTNOT, "Show Help");
	parser->addOption("ok", ARGUMENT_TYPE::MUST, "OK");
	parser->addOption("b", ARGUMENT_TYPE::BOTH, "どっちでもいいよ");

	parser->Parse();

	Console::WriteLine(parser->DebugOutput());

	MessageBox::Show(parser->HelpString);
    return 0;
}
