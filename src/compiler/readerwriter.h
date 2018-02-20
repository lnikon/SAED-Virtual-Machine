#ifndef READERWRITER_H
#define READERWRITER_H

#include <QTextStream>
#include <QVector>
#include <qdebug.h>
#include <QDataStream>
#include <QFileInfo>
#include <QString>

#include "lexer.h"
#include "instructions.h"
#include "header.h"

class CReaderWriter
{
public:
	CReaderWriter();

	void addSection(QByteArray buf, ESectionType sectionType);
	void write(QString filename);

	QByteArray read(QString sFileExe);

private:
	void createHeader();
	QByteArray writeHeader(QString signature, int32 version);
	int getOffset(int i);

	void printMSectionSizes();
	void testHeader();
	void testTheExeFile(QString filename);

private:
	QMap<ESectionType, QByteArray> m_MSectionSizes;

private:
	int32 m_headerSize;
	int32 m_nVersion;
	QString m_sSignature;
	SHeader m_SHeader;
	QByteArray m_buffer;
};

#endif