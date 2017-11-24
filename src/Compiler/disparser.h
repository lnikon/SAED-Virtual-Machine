#ifndef DISPARSER_H
#define DISPARSER_H

#include "header.h"
#include "tokens.h"
#include <QVector>

class CDisParser
{
public:
	void work(QByteArray buffer);
	QVector<SDataToken> getDataTokens();
	QVector<SCodeToken> getCodeTokens();
	QVector<QString> getDataNames();
private:
	QVector<SDataToken> m_SDataTokens;
	QVector<SCodeToken> m_SCodeTokens;
};




#endif