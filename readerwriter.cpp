#include "readerwriter.h"

CReaderWriter::CReaderWriter() :
	m_nVersion(1), m_sSignature("SAED/VirtualMachine/ExeFile"), m_headerSize(128)
{
}
void CReaderWriter::addSection(QByteArray section, ESectionType sectionType)
{

	if (section.size() == 0)
	{
		return;
	}
	else
	{
		m_MSectionSizes[sectionType] = section;
	}
}
int CReaderWriter::getOffset(int i)
{
	int offset = m_headerSize;
	while (i)
	{
		offset += m_SHeader.recordTable[i - 1].offset;
		--i;
	}
	return offset;
}
void CReaderWriter::write(QString filename)
{
	createHeader();
	testHeader();

	/////////////////Filling the exe file

	QFile file(filename);
	file.resize(0);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QDataStream out(&file);

	uint8 zero = 0;
	/////fill header
	QChar ch;
	for (int i = 0; i < m_SHeader.sSignature.size(); ++i)
	{
		ch = static_cast<QChar>(m_SHeader.sSignature[i]);
		out << ch;
	}
	out << m_SHeader.nVersion;
	out << m_SHeader.recordCount;

	for (int i = 0; i < m_SHeader.recordCount; ++i)
	{
		out << static_cast<int>(m_SHeader.recordTable[i].eSectionType);
		out << m_SHeader.recordTable[i].offset;
		out << m_SHeader.recordTable[i].size;
	}

	int currPos = file.pos();
	while (currPos < m_headerSize)
	{
		out << zero;
		currPos++;
	}

	////////header is filled
	///////filling .exe file sections
	int secIndex = 2;						///secIndex = 1 for header (usage:	find exact number of zeros to be filled between .ex  file's sections)
	for (auto e : m_MSectionSizes.keys())
	{
		for (int j = 0; j < m_MSectionSizes.value(e).size(); ++j)
		{
			out << static_cast<uint8>(m_MSectionSizes.value(e)[j]);
		}

		currPos = file.pos();
		while (currPos < m_headerSize * secIndex)
		{
			out << zero;
			currPos++;
		}
		++secIndex;
	}
	file.close();

	testTheExeFile(filename);
	SHeader h = readHeader(filename);

}
SHeader CReaderWriter::readHeader(QString filename)
{
	qDebug() << "\n\nreadHeader Start\n\n";
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray output = file.readAll();
	QDataStream in(&file);

	SHeader readHeader;

	char ch;
	int i = 1;
	for (; i < m_sSignature.size() * 2; i += 2)		//as the sizeof qbytearray[i] = 16 bytes
	{
		ch = static_cast<char>(output[i]);
		readHeader.sSignature += ch;
	}
	std::cout << "readHeader.sSignature = " << readHeader.sSignature << std::endl;
	std::cout << "readHeader.sSignature.size = " << readHeader.sSignature.size() << std::endl;

	file.seek(54);
	in >> readHeader.nVersion;
	qDebug() << "readHeader.nVersion = " << readHeader.nVersion;

	file.seek(58);
	in >> readHeader.recordCount;
	qDebug() << "readHeader.recordCount = " << readHeader.recordCount;

	for (int k = 0; k < readHeader.recordCount; k++)
	{
		SHeaderTable hdt;
		int sectype;
		in >> sectype;
		hdt.eSectionType = static_cast<ESectionType>(sectype);
		in >> hdt.offset;
		in >> hdt.size;
		readHeader.recordTable.push_back(hdt);
		qDebug() << "hdt = " << static_cast<int>(hdt.eSectionType) << " " << hdt.offset << " " << hdt.size;
	}

	qDebug() << "\n\nend of testTheExeFile";
	return readHeader;
}		//OK		
void CReaderWriter::testTheExeFile(QString filename)
{
	qDebug() << "\n\ntestTheExeFile Start\n\n";

	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray output = file.readAll();
	QDataStream in(&file);


	for (int pos = 0; pos < output.size(); ++pos)
	{
		qDebug() << pos << static_cast<int>(output[pos]);
	}
	qDebug() << "\n\nend of testTheExeFile";

	file.close();
}
void CReaderWriter::createHeader()
{
	m_SHeader.sSignature = m_sSignature;
	m_SHeader.nVersion = m_nVersion;
	m_SHeader.recordCount = m_MSectionSizes.size();

	int currPos = m_headerSize;

	for (auto e : m_MSectionSizes.keys())
	{
		SHeaderTable section;
		section.eSectionType = e;
		section.size = m_MSectionSizes.value(e).size();
		section.offset = currPos;
		m_SHeader.recordTable.push_back(section);
		currPos += m_headerSize;
	}
}
void CReaderWriter::testHeader()
{
	qDebug() << "RW::testHeader Start\n\n";

	//	qDebug() << "signature = " << m_SHeader.sSignature;
	std::cout << "m_SHeader.sSignature = " << m_SHeader.sSignature;
	qDebug() << "version = " << m_SHeader.nVersion;
	qDebug() << "recordCount = " << m_SHeader.recordCount;
	for (int i = 0; i < m_SHeader.recordTable.size(); ++i)
	{
		qDebug() << "sectionType = " << static_cast<int>(m_SHeader.recordTable[i].eSectionType);
		qDebug() << "offset  = " << m_SHeader.recordTable[i].offset;
		qDebug() << "size  = " << m_SHeader.recordTable[i].size;
	}

	qDebug() << "\n\nend of RW::testHeader";
}
QVector<SDataToken> CReaderWriter::readDataTableSection(SHeader h, QString filename)
{
	qDebug() << "\n\nraedData Start\n\n";

	qDebug() << "h.recordTable[0].offset = " << h.recordTable[0].offset;
	qDebug() << "h.recordTable[2].offset = " << h.recordTable[2].offset;
	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray output = file.readAll();
	QDataStream in(&file);

	file.seek(h.recordTable[2].offset);
	int secSize;
	//	in >> secSize;
	secSize = h.recordTable[static_cast<int>(ESectionType::DataTable)].size;
	qDebug() << "secSize = " << secSize;

	QVector<SDataToken> VDTokens;

	int currPos = file.pos();
	for (int p = currPos; p < currPos + secSize;)
	{
		SDataToken dt;
		//	uint8 dataType;
		int dataType;

		in >> dataType;
		dt.type = static_cast<EType>(dataType);
		qDebug() << "dataType = " << dataType;

		//		uint8 idNameSize;
		int idNameSize;
		in >> idNameSize;
		std::string idName;
		uint8 ch;
		for (int j = 0; j < idNameSize; ++j)
		{
			in >> ch;
			idName += ch;
		}
		dt.identifierName = QString::fromStdString(idName);
		qDebug() << "idName = " << dt.identifierName;
		int l;
		in >> l;
		dt.line = l;
		qDebug() << "line = " << dt.line;
		VDTokens.push_back(dt);
		p = file.pos();
	}
	file.close();
	return VDTokens;
	qDebug() << "\n\nend of readData";
}
QVector<SDataToken> CReaderWriter::readDataSection(SHeader h, QVector<SDataToken> VDT, QString filename)
{
	qDebug() << "\n\nreadDataSection Start\n\n";

	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray output = file.readAll();
	QDataStream in(&file);

	file.seek(h.recordTable[0].offset + 4);
	qDebug() << "pos = " << file.pos();
	for (int i = 0; i < VDT.size(); ++i)
	{
		if (VDT[i].type == EType::Byte)
		{
			uint8 val;
			in >> val;
			qDebug() << "val = " << val;
			qDebug() << "pos = " << file.pos();
			for (int j = 0; j != sizeof(val); ++j)
			{
				VDT[i].value.append((char)(val&(0xFF << i) >> i));
				qDebug() << "value[i]" << static_cast<int>(VDT[i].value[j]);
			}
		}
		if (VDT[i].type == EType::Word)
		{
			uint16 val;
			in >> val;
			qDebug() << "val = " << val;
			qDebug() << "pos = " << file.pos();
			for (int j = 0; j != sizeof(val); ++j)
			{
				VDT[i].value.append((char)(val&(0xFF << i) >> i));
				qDebug() << "value[i]" << static_cast<int>(VDT[i].value[j]);
			}
		}
		if (VDT[i].type == EType::Dword)
		{
			uint32 val;
			in >> val;
			qDebug() << "val = " << val;
			qDebug() << "pos = " << file.pos();
			for (int j = 0; j != sizeof(val); ++j)
			{
				VDT[i].value.append((char)(val&(0xFF << i) >> i));
				qDebug() << "value[i]" << static_cast<int>(VDT[i].value[j]);
			}
		}
		if (VDT[i].type == EType::Qword)
		{
			uint64 val;
			in >> val;
			qDebug() << "val = " << val;
			qDebug() << "pos = " << file.pos();
			for (int j = 0; j != sizeof(val); ++j)
			{
				VDT[i].value.append((char)(val&(0xFF << i) >> i));
				qDebug() << "value[i]" << static_cast<int>(VDT[i].value[j]);
			}
		}
	}
	file.close();
	qDebug() << "\n\nend of readDataSection\n\n";
	return VDT;
}
void CReaderWriter::readCodeSection(SHeader h, QString filename)
{
	qDebug() << "\n\nreadCodeSection Start\n\n";

	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray output = file.readAll();
	QDataStream in(&file);

	file.seek(h.recordTable[1].offset);
	int secSize;
	secSize = h.recordTable[static_cast<int>(ESectionType::Code)].size;
	//	in >> secSize;



	QVector <SCodeToken> VCT;
	int currPos = file.pos();
	for (int pos = currPos; pos < currPos + secSize;)
	{
		SCodeToken sct;
		uint16 opcode;
		in >> opcode;
		sct.opcode.opcode = opcode;
		//	VCT[i].opcode.opcode = opcode;
		qDebug() << "opcode = " << opcode;

		int count = HInstCount[opcode];
		qDebug() << "count = " << count;
		for (int i = 0; i < count; ++i)
		{
			uint32 arg;
			in >> arg;
			sct.argValue.append(arg);
			//		VCT[i].argValue.append(arg);
			qDebug() << "arg = " << arg;
		}

		//	uint8 l;
		//	in >> l;
		//	sct.line = l;
		////	VCT[i].line = l;
		//	qDebug() << "VCT[i].line = " << sct.line;
		VCT.push_back(sct);
		pos = file.pos();
	}
	file.close();
	qDebug() << "\n\nend of readCodeSection\n\n";
}
QByteArray CReaderWriter::read(QString sFileExe)
{
	QFile file(sFileExe);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Cannot open";
	}
	QDataStream in(&file);
	QByteArray output;
	in >> output;
	return output;
}


