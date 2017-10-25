#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include "readerwriter.h"
#include "disparser.h"
#include "codegenerator.h"


class CDisassembler
{
public:
	CDisassembler();
	void work(QString sFileExe, QString sFileTxt);
private:
	CReaderWriter* m_reader;
	CDisParser* m_disParser;
	CCodeGenerator* m_codeGenerator;
};



#endif