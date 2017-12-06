#include "disassembler.h"

CDisassembler::CDisassembler()
{
	m_reader = new CReaderWriter();
	m_disParser = new CDisParser();
	m_codeGenerator = new CCodeGenerator();
}

void CDisassembler::work(QString sFileExe, QString sFileTxt)
{
	QByteArray buffer = m_reader->read(sFileExe);

	m_disParser->work(m_reader, buffer);
//	QVector<SDataToken> dataTokens = m_disParser->getDataTokens();//first must be filled SDataTokens, sDataNames
//	QVector<SCodeToken> codeTokens = m_disParser->getCodeTokens();
//	QHash<QString, int32> sDataNames = m_disParser->getDataNames();

//	m_codeGenerator -> work(dataTokens, codeTokens, sDataNames, sFileTxt);
}