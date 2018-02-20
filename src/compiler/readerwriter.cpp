#include "readerwriter.h"

CReaderWriter::CReaderWriter() :
	m_nVersion(1), m_sSignature("SAED/VirtualMachine/ExeFile"), m_headerSize(128)
{
}

void CReaderWriter::addSection(QByteArray section, ESectionType sectionType)
{
	qDebug() << "RW::addSection Start\n\n";

	if (section.size() == 0)
	{
		return;
	}
	else
	{
		qDebug() << static_cast<int>(sectionType) << section.size();
		m_MSectionSizes[sectionType] = section;
	}
	qDebug() << "\n\nend of addSection";
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
	qDebug() << "RW::write Start\n\n";

	for (auto e : m_MSectionSizes.keys())
	{
		qDebug() << static_cast<int>(e) << "," << m_MSectionSizes.value(e).size() << '\n';
	}

	createHeader();
	testHeader();

	/////////////////Filling the exe file

	QFile file(filename);
	file.resize(0);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QDataStream out(&file);

	int zero = 0;

	int actualHeaderSize = 0;

	out << m_SHeader.sSignature;
	out << m_SHeader.nVersion;
	out << m_SHeader.recordCount;

	actualHeaderSize += sizeof m_SHeader.sSignature + sizeof m_SHeader.nVersion + sizeof m_SHeader.recordCount;

	for (int i = 0; i < m_SHeader.recordCount; ++i)
	{
		out << static_cast<int>(m_SHeader.recordTable[i].eSectionType);
		out << m_SHeader.recordTable[i].offset;
		out << m_SHeader.recordTable[i].size;
		actualHeaderSize += sizeof(int) + sizeof m_SHeader.recordTable[i].offset + sizeof m_SHeader.recordTable[i].size;
	}

	qDebug() << "actualHeaderSize = " << actualHeaderSize;

	int zeroCount = m_headerSize - actualHeaderSize;
	while (zeroCount)
	{
		out << zero;
		--zeroCount;
	}

	for (auto e : m_MSectionSizes.keys())
	{
		out << m_MSectionSizes.value(e);
		int remZeroCount = m_headerSize - m_MSectionSizes.value(e).size();
		for (int i = 0; i < remZeroCount; ++i)
		{
			out << zero;
		}
	}
	file.close();

	testTheExeFile(filename);

	qDebug() << "\n\nend of RW::write";

}

void CReaderWriter::testTheExeFile(QString filename)
{
	qDebug() << "testTheExeFile Start\n\n";

	QFile file(filename);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray from;
	QDataStream in(&file);

	QByteArray output;
	in >> output;

	for (int pos = 0; pos < output.size(); ++pos)
	{
		qDebug() << pos << static_cast<int>(output[pos]);
	}

	qDebug() << "\n\nend of testTheExeFile";

	file.close();
}

void CReaderWriter::createHeader()
{
	qDebug() << "RW::createHeader Start\n\n";
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
	qDebug() << "\n\nend of RW::createHeader";
}

void CReaderWriter::testHeader()
{
	qDebug() << "RW::testHeader Start\n\n";

	qDebug() << "signature = " << m_SHeader.sSignature;
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
