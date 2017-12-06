#ifndef DISPARSER_H
#define DISPARSER_H

#include "header.h"
#include "tokens.h"
#include "readerwriter.h"
#include <QVector>

class CDisParser
{
public:
	CDisParser()
	{
	}
	void work(CReaderWriter* reader, QByteArray buffer);
	void getHeader();
	QVector<SDataToken> getDataTokens();
	QVector<SCodeToken> getCodeTokens();
	QHash<QString, int32> getDataNames();

private:
	void readDataTableSection();

private:
	QVector<SDataToken> m_SDataTokens;
	QVector<SCodeToken> m_SCodeTokens;
	QHash<QString, int32> m_DataNames;
	SHeader m_SHeader;
	QByteArray m_buffer;
	CReaderWriter* m_reader;
};




#endif