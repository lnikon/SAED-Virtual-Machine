#ifndef READERWRITER_H
#define READERWRITER_H

#include "lexer.h"
#include "instructions.h"
#include "header.h"

#include <QTextStream>
#include <QVector>
#include <qdebug.h>
#include <QDataStream>
#include <QFileInfo>


class CReaderWriter
{
public:
	CReaderWriter();
		
	// methods fpr access to the file content	
	int getSectionCount() const;
	QString getSectionName(int nIndex) const;
	QByteArray getSection(int nIndex) const;
	QByteArray getSection(QString const& sName) const;

	// Adds specifed section toi the executable file
	void addSection(QString const& sName, QByteArray const& aData);

	// Writes files to the disk with specified path
	void write(QString filename);
	// Reads file from the disk
	void read(QString sFileExe);
	
private:		
		void createHeader();
		QByteArray writeHeader(QString signature, int32 version);
		void addSectionToHeader(int i, QByteArray buf);
		int getOffset(int i);

private:
	int32 m_headerSize;
	int32 m_nVersion;
	QString m_sSignature;
	SHeader m_SHeader;
	QVector< QPair<QString, QByteArray> > m_aSections;
};




#endif