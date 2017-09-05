#include <QtCore/QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QTextStream>
#include <QFileInfo>

#include "lexer.h"
#include "instructions.h"

int main(int argc, char *argv[])
{
	QCoreApplication aaa(argc, argv);

	const QString filename = "test.asm";
	QFile fin(filename);
	QFileInfo f_info(fin);

	if (f_info.completeSuffix() != "asm")
	{
		//terminate
	}

	if (!fin.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Cannot open" << f_info.absoluteFilePath() <<
			"file doesn't exist";
	}

	QTextStream input(&fin);
	try
	{
		CLexer lexer;

		lexer.work(input);

		QVector<SCodeToken> o = lexer.getCode();

		QVector<SDataToken> k = lexer.getData();
		for (const auto aa : k)
		{
			qDebug() << aa.identifierName << " line data" << aa.line;
		}

		for (auto a : o)
		{
			qDebug() << a.instructionName << " line code" << a.line;
			qDebug() << a.opcode.instr;
			for (const auto i : a.argValue)
			{
				qDebug() << i;
			}
		}
	}
	catch (CError& e)
	{
		qDebug() << e.what();
	}



	exit(1);
	return aaa.exec();
}
