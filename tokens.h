#ifndef TOKENS_H
#define TOKENS_H
#include "instructions.h"

struct SDataToken
{
	SDataToken() : type(), quantity(0), line(0)
	{
	}

	SDataToken(EType t, uint32 l) : type(t), quantity(0), line(l)
	{
	}

	SDataToken(EType t, QString n, QByteArray v, uint32 l):
		type(t), identifierName(n), value(v), line(l)
	{
	}

	EType type;
	
	QString identifierName;
	QByteArray value;
	uint32 quantity;
	uint32 line;
};


//QVector<QString> arrData;

struct SCodeToken
{
	SCodeToken() : line(1)
	{
	}

	explicit SCodeToken(uint32 l) : line(l)
	{
	}

	SCodeToken(UOpcode op, QVarLengthArray<uint32, 3> args):
		opcode(op), argValue(args)
	{
	}

	//QString instructionName;

	QVarLengthArray<uint32, 3> argValue;

	UOpcode opcode;
	uint32 line;
};

//DataTable returned by QHash<QString, uint32> CLexer::getDataTable() function

#endif // !TOKENS_H