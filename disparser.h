#ifndef DISPARSER_H
#define DISPARSER_H

#include "header.h"
#include "tokens.h"
#include "readerwriter.h"
#include <QVector>
#include <QByteArray>
#include <QDataStream>

class CDisParser
{
public:
    CDisParser(CReaderWriter* reader);


    void collectSections();
    void work(QByteArray buffer);

    void getHeader();
    bool checkSignature();
    QVector<SDataToken> getDataTokens();
    QVector<SCodeToken> getCodeTokens();

private:
    QVector<SDataToken> m_SDataTokens;
    QVector<SCodeToken> m_SCodeTokens;

    QByteArray m_DataSection;
    QByteArray m_CodeSection;
    QByteArray m_DataTableSection;
    QByteArray m_CodeTableSection;


    SHeader* m_SHeader;
    CReaderWriter* m_reader;
    QByteArray m_buffer;
};




#endif
