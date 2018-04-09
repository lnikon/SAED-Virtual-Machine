#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QTextStream>
#include <QFileInfo>

#include "compiler.h"
#include "../interpreter/interpreter.h"
#include "../debugger/debugger.h"
#include "../disassember/disassembler.h"

int main(int argc, char *argv[])
{
	QCoreApplication aaa(argc, argv);


	CCompiler compiler;
	compiler.work("test.asm", "compiled.txt");

	CDisAssembler disassm;
	disassm.work("compiled.txt", "a.txt");

	CInterpreterPtr pInterpreter = std::make_shared<CInterpreter>();
	IDebuggerPtr pIDebugger = std::make_shared<CDebugger>(pInterpreter);

	pInterpreter->Init("compiled.txt");
	pInterpreter->setDebugger(pIDebugger);
	pInterpreter->Run();

	exit(1);
	return aaa.exec();
}
