#ifndef _myLexer_h_
#define _myLexer_h_

#include"instructions.h"
#include<QVariant>
#include<QVector>
#include<QTextStream>

struct SDataToken
{
	SDataToken() {};
	SDataToken(QString& t, uint l) : type(HTypeTable[t]), line(l) {}

	void set(QString& name, uint s, uint l);
	EDataType type; // byte, word, dword, qword
	QString dataName;
	QVector<QVariant> value;
	uint size; // count of array ellementes, '0' if array size is not set yet
	uint line;
};

struct SCodeToken
{
	SCodeToken() {};
	SCodeToken(QString name, uint32 l) : instName(name), line(l) {}

	QString instName; // instructionName
	QVarLengthArray<QPair<QString, EArgumentType>, 3> argName; // <argName, type>
	uint32 line;
};

struct Error
{
	QString messege;
	QString value;
	uint line;
	Error(QString m, QString v, uint l) : messege(m), value(v), line(l) {}
	QString getError()
	{
		QString error = "error. [" + QString::number(line) + "]: " + messege + value;
		return error;
	}	
};

class myLexer
{
public:
	myLexer() {}
	void start(QTextStream& in);

private: // members
	enum class State
	{
		initial, // wait for first command 
		dataType, // wait for data type
		dataName,
		dataEqual, // wait for symbol '='
		dataValue, // wait for single value after '='
		dataArray, // wait for array values 
		codeInst, // wait for code instruction
		codeArgument,
		comment
	};
	QVector<SDataToken> m_dataToken;
	QVector<SCodeToken> m_codeToken;
	int line = {1};

private: // functions
	QVector<SDataToken> getDataTokens() const {
		return m_dataToken;
	}
	QVector<SCodeToken> getCodeTokens() const {
		return m_codeToken;
	}
	bool isDelimiter(char c);
	int checkDataName(QString& buffer); // return 0 - invalid name
										// return 1 - single value
										// return 2 - array without size
										// return other value - array size + 3
	
	void setNumber(QString& buffer); // m_dataTocen.value.last() = number;
	QString makeName(QString& buffer); // ex. buffer = "name[20]", return "name"
	bool isRegsiter(QString& buffer); // return true if buffer is register
	bool isNumber(QString& buffer);
	bool isVariable(QString& buffer);
};


#endif // !_myLexer_h_
