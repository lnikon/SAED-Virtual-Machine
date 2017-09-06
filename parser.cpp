#include "parser.h"

CParser::CParser(QDataStream& out, QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens) :
												m_out(out), m_dataTokens(dataTokens), m_codeTokens(codeTokens) 
{
}

void CParser::work(QString fileName)
{
	writeHeader(m_out);

	if (!m_dataTokens.isEmpty())
	{
		writeDataTokens(m_out);
	}
	writeCodeTokens(m_out);
}

SHeader CParser::createHeader()
{
	QString signature = "SAED/VirtualMachine/ExeFile";
	int version = 1;
	int offset = sizeof signature + sizeof(int);

	SHeader header(signature, version);

	if (!m_dataTokens.isEmpty())
	{
		SHeaderTable headerTable(ESctionType::Data, offset, m_dataTokens.size());
		header.arrayTable.push_back(headerTable);
		offset += m_dataTokens.size();
	}

	{
		SHeaderTable headerTable(ESctionType::Code, offset, m_codeTokens.size());
		header.arrayTable.push_back(headerTable);
		offset += m_codeTokens.size();
	}

	if (!m_dataTokens.isEmpty())
	{
		SHeaderTable headerTable(ESctionType::SymbolTable, offset, m_dataTokens.size());
		header.arrayTable.push_back(headerTable);
		offset += m_dataTokens.size();
	}
	/*Then When writng the debugger, will write the debugInfo section too*/
	/*
	{
	SHeaderTable headerTable(ESctionType::DebugInfo, offset, m_dataTokens.size());
	header.arrayTable.push_back(headerTable);
	offset += m_dataTokens.size();
	}
	*/

	header.recordCount = header.arrayTable.size();

}
void CParser::writeHeader(QDataStream& out)
{
	SHeader header = createHeader();

	out << header.signature;
	out << header.version;
	out << header.recordCount;

	for (int i = 0; i < header.recordCount; ++i)
	{
		out << header.arrayTable[i].type;
		out << header.arrayTable[i].offset;
		out << header.arrayTable[i].size;
	}
}

void CParser::writeCodeTokens(QDataStream& out)
{
	for (int i = 0; i < m_codeTokens.size(); i++)
	{
		out << m_codeTokens[i].opcode;

		QString instructionName = m_codeTokens[i].name;
		int count = inst[instructionName].argument_count;
		for (int j = 0; j < count; ++j)
		{
			out << m_codeTokens[i].arg_value[j];
		}
		
	}
}

void CParser::writeDataTokens(QDataStream& out)
{
	int name = 5;
	for (QVector<SDataToken>::iterator it = m_dataTokens.begin(); it != m_dataTokens.end(); ++it)
	{
		//write it.size
		out << static_cast<int>((*it).size);
		//write name
		out << name;
		m_nameGrammar[(*it).name] = name;
		if (!(*it).value.isNull())
		{
			//write it.value
			out << (*it).value;
			name += 4;
		}
		name += 4;
	}
}





