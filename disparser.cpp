#include "disparser.h"

CDisParser::CDisParser(CReaderWriter *reader)
{
    m_reader = reader;
}


void CDisParser::work(QByteArray buffer)
{
    m_buffer = buffer;
    m_SHeader = new SHeader;
}




void CDisParser::collectSections()
{
    for (int i = 0;i<= m_SHeader->recordCount; ++i)
    {
        switch (i) {
        case 1:
            m_DataSection = m_reader->getSections(1);
            break;
        case 2:
            m_CodeSection = m_reader->getSections(2);
            break;
        case 3:
            m_DataTableSection = m_reader->getSections(3);
            break;
        case 4:
            m_CodeTableSection = m_reader-> getSections(4);
            break;
        default:
            break;
        }
    }
}

QVector<SDataToken> CDisParser::getDataTokens()
{
    QDataStream bf (&m_DataTableSection, QIODevice::ReadWrite);
    SDataToken tmp;
    while(!bf.atEnd())
    {
        bf>>tmp.type;
        bf>>tmp.identifierName;
        bf>>tmp.value;
        bf>>tmp.quantity;
        bf>>tmp.line;
        m_SDataTokens.push_back(tmp);
    }
    return m_SDataTokens;
}

QVector<SCodeToken> CDisParser::getCodeTokens()
{
    QDataStream bf (&m_CodeSection, QIODevice::ReadWrite);
    SCodeToken tmp;
    while (!bf.atEnd())
    {
        bf>>tmp.opcode.opcode;
        bf>>tmp.argValue[0];
        bf>>tmp.argValue[1];
        bf>>tmp.argValue[2];

        m_SCodeTokens.push_back(tmp);
    }
    return m_SCodeTokens;
}

void CDisParser::getHeader()
{
    QByteArray data = m_buffer.left(128);
    QDataStream buffer (&data, QIODevice::ReadWrite);

   buffer>>m_SHeader->sSignature;
   buffer>>m_SHeader->nVersion;
   buffer>>m_SHeader->recordCount;
    for (int i = 0; i<=m_SHeader->recordCount; ++i)
    {
        buffer>>static_cast<int>(m_SHeader->recordTable[i].eSectionType);
        buffer>>m_SHeader->recordTable[i].offset;
        buffer>>m_SHeader->recordTable[i].size;
    }

}
bool CDisParser::checkSignature()
{
    if( m_SHeader->sSignature == m_reader->getSignature())

        return true;

    return false;
}

