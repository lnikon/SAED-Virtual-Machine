#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "tokens.h"
#include "instructions.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QVarLengthArray>

class CCodeGenerator
{
public:
	CCodeGenerator()
	{
	}
	void work(QVector<SDataToken>dataTokens, QVector<SCodeToken>codeTokens, QHash<QString, int32> symbolTable, QString sFileTxt);
private:
	void writeDataSection(QTextStream& out);
	void writeCodeSection(QTextStream& out);

	QString getDataType(EType t);
	QString getOpcode(UOpcode opc);
	int32 getArgumentCount(QString instruction);
	QVector<QString> getArgumentNames(UOpcode opc, QVarLengthArray<uint32, 3> arr);
	QString getArgumentName(EArgumentType type, uint32 arg);
private:
	QVector<SDataToken> m_dataTokens;
	QVector<SCodeToken> m_codeTokens;
	QHash<QString, int32> m_symbolTable;
};




#endif