#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "tokens.h"
#include "readerwriter.h"

class CCodeGenerator
{
public:
	CCodeGenerator();
	void work(QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens, 
		QVector<int> symbolTable, QString filename);

private:
	QVector<QString> generateData(QVector<SDataToken> v_dt);
	QVector<QString> generateCode(QVector<SDataToken> v_dt, QVector<SCodeToken> v_ct, QVector<int> symbolTable);

	QString getType(EType t);
	QVector<QString> getArguments(QVector<SDataToken> v_dt, SCodeToken ct, QVector<int> symbolTable);
};






#endif