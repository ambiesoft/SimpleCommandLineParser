// TestApp.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#using "C:\\Linkout\\Topener\\SimpleCommandLineParser.dll"

using namespace System;
using namespace Ambiesoft;

int main(array<System::String ^> ^args)
{
	SimpleCommandLineParser^ parser = gcnew SimpleCommandLineParser(args);
	parser->addOption("h", ARGUMENT_TYPE::MUSTNOT);
	parser->addOption("?", ARGUMENT_TYPE::MUSTNOT);
	parser->addOption("ok", ARGUMENT_TYPE::MUST);

	parser->Parse();

	Console::WriteLine(parser->DebugOutput());

    return 0;
}
