#ifndef LEXER_H
#define LEXER_H

#include <QTextStream>
#include <QVector>
#include <qdebug.h>
#include "instructions.h"
#include <qfile.h>

struct DataToken
{
	DataToken() {}
	DataToken(Type t, uint32 l) : size(t), line(l) {}
	Type size;
	QString name;
	QVariant value;

	uint32 line;
};

struct CodeToken
{
	CodeToken() {}
	CodeToken(const QString& n, const Type& t, uint32 l) : name(n), size(t), line(l) {}
	Type size;
	QString name;

	QVector<ArgumentType> arg_type;
	QVector<QString> arg_vlaue;
	//ArgumentType arg1_type;
	//ArgumentType arg2_type;
	//ArgumentType arg3_type;

	//QVariant arg1_value;
	//QVariant arg2_value;
	//QVariant arg3_value;

	uint32 line;
};

class Lexer
{
public:
	explicit Lexer(QTextStream & in);
	QVector<DataToken> dataOut() const;
	QVector<CodeToken> codeOut() const;
private:
	bool isDigit(const QString &);
	bool isRegister(const QString &);

	void checkCommand(const QString& command);
	void checkArgument(const QString& argument);
	void checkIdentifier(const QString& identifier);
	void checkValue(const QString& value);
	bool isDelimiter(QChar ch);
	void checkType(const QString& type_string);

	uint32 line_ = 1;
	int32 argCount_;
	QVector<DataToken> data_tokens_;
	QVector<CodeToken> code_tokens_;
	QSet<QString> data_;

	enum class State { init, code_command, code_argument, data_type, data_identifier, data_value, comment };
};

#endif // !LEXER_H
