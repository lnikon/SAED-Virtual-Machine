#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <QTextStream>
#include <QVector>
#include <qdebug.h>
#include "instructions.h"
#include <QDataStream>
#include <QFileInfo>

using uint16 = unsigned short;

enum ESctionType {
	Data, Code, SymbolTable, DebugInfo
};

struct SHeaderTable{
	SHeaderTable(ESctionType tt, int oo, int ss) : type(tt), offset(oo), size(ss)
	{
	}
	ESctionType type;
	int offset;
	int size;
};

struct SHeader{
	SHeader(QString ss, int vv) :signature(ss), version(vv)
	{
	}
	QString signature;
	int version;
	int recordCount;
	QVector<SHeaderTable> arrayTable;
};

class CParser
{
public:
	CParser(QDataStream& out, QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens);
	void work(QString fileName);

private:
	void writeHeader(QDataStream&);
	SHeader createHeader();
	void writeDataTokens(QDataStream&);
	void writeCodeTokens(QDataStream&);
	uint16 getArgCode(QString argName);
private:
//	SHeader m_SHeader;
	QVector<SDataToken> m_dataTokens;
	QVector<SCodeToken> m_codeTokens;
	QHash<QString, int> m_nameGrammar;
	QDataStream m_out;
	
};




#endif