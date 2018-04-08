#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QTextStream>
#include <QFileInfo>

#include "compiler.h"
#include "../interpreter/interpreter.h"
#include "disassembler.h"

int main(int argc, char *argv[])
{
	QCoreApplication aaa(argc, argv);


	CCompiler compiler;
	compiler.work("test.asm", "compiled.txt");

	CDisAssembler disassm;
	disassm.work("compiled.txt", "a.txt");

	CInterpreter interpreter;

	interpreter.Init("compiled.txt");
	interpreter.Run();

	exit(1);
	return aaa.exec();
}
