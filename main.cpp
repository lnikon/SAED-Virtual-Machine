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

	QString FILENAME = "test.asm";
	QFile fin(FILENAME);
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

	Lexer lex(input);

	return aaa.exec();
}
