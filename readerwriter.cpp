#include "readerwriter.h"

CReaderWriter::CReaderWriter() :
m_nVersion(1), m_sSignature("SAED/VirtualMachine/ExeFile"), m_nHeaderSize(128)
{
}
void CReaderWriter::addSection(QByteArray buf)
{
	m_buffer.append(buf);
	addSectionToHeader(m_SHeader.recordCount, buf);
	++m_SHeader.recordCount;
}
void CReaderWriter::addSectionToHeader(int i, QByteArray buf)
{
	m_SHeader.recordTable.push_back(SHeaderTable(static_cast<ESectionType>(i), getOffset(i), buf.size()));
}

int CReaderWriter::getOffset(int i)
{
	int offset = m_nHeaderSize;
	while (i)
	{
		offset += m_SHeader.recordTable[i - 1].offset;
		--i;
	}
	return offset;
}

void CReaderWriter::write(QString filename)
{

	QFile file(filename);
	file.resize(0);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QDataStream out(&file);
	
	//write header section in .exe file
	createHeader();

	QByteArray headerBuffer;
	headerBuffer.append(m_SHeader.sSignature);
	headerBuffer.append(m_SHeader.nVersion);
	headerBuffer.append(m_SHeader.recordCount);
	out << headerBuffer;
	//out << m_SHeader.sSignature;
	//out << m_SHeader.nVersion;
	//out << m_SHeader.recordCount;
	int header_size = sizeof m_sSignature + sizeof m_nVersion + sizeof m_SHeader.recordCount;
	for (int i = 0; i < m_SHeader.recordCount; i++)
	{
		out << static_cast<int32>(m_SHeader.recordTable[i].eSectionType);
		out << m_SHeader.recordTable[i].offset;
		out << m_SHeader.recordTable[i].size;

		header_size += sizeof(int32) + sizeof m_SHeader.recordTable[i].offset + sizeof m_SHeader.recordTable[i].size;
	}

	// allign before m_headerSize bytes for DataSection
	while (header_size != m_nHeaderSize)
	{
		out << static_cast<char>(0);
		++header_size;
	}

	out << m_buffer;

	file.close();
}

void CReaderWriter::createHeader()
{
	m_SHeader.sSignature = m_sSignature;
	m_SHeader.nVersion = m_nVersion;
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
QString CReaderWriter::getSignature() const
{
	return m_sSignature;
}
int32 CReaderWriter::getVersion() const
{
	return m_nVersion;
}
int32 CReaderWriter::getHeaderSize() const
{
	return m_nHeaderSize;
}