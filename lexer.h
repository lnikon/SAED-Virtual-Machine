#ifndef LEXER_H
#define LEXER_H

#include <QVarLengthArray>
#include <QVariant>
#include <QDebug>
#include <QDataStream>
#include "instructions.h"

struct SDataToken
{
	SDataToken()
	{
	}
	SDataToken(EType t, uint32 l)
		: type(t), line(l)
	{
	}

	EType type;
	QString identifierName;
	QVariant value;

	uint32 line;
};

struct SCodeToken
{
	SCodeToken()
	{
	}
	SCodeToken(const QString& n, uint32 l)
		:instructionName(n), line(l)
	{
	}

	QString instructionName;

	QVarLengthArray<uint32, 3> argValue;

	UOpcode opcode;
	uint32 line;
};

class CLexer
{
public:
	explicit CLexer()
	{
	}
	void work(QTextStream& in);
	QVector<SDataToken> getData() const;
	QVector<SCodeToken> getCode() const;

private:
	bool isDigit(const QString &);
	bool isRegister(const QString &);

	void checkCommand(const QString& command);
	void checkArgument(const QString& argument);
	void checkIdentifier(const QString& identifier);
	void checkValue(const QString& value);
	bool isDelimiter(QChar ch);
	void checkType(const QString& type_string);

	uint32 getRegNumber(const QString & argument);

	uint32 m_line = 1;
	int32 m_argCount = 0;
	QVector<SDataToken> m_dataTokens;
	QVector<SCodeToken> m_codeTokens;
	QSet<QString> m_data;

	enum class EState
	{
		Init, CodeCommand, CodeArgument, DataType, DataIdentifier,
		DataValue, Comment, Space, Attribute, Comma
	};
};

#endif // !LEXER_H
