#ifndef _rw_h
#define _rw_h_

#include<QString>
#include<QVector>
#include<QByteArray>
#include<QFile>
#include<QTextStream>

#include<iostream> // for function print

using namespace std; // I know, it is bad idea :)

#include"instructions.h"

enum class ESectionType { Data, Code, DataSymbol, CodeSymbol };

class CRW
{
public:
	CRW();

	void write(QString path);

	// return false if there is not file, or file has wrong signature or version 
	bool read(QString path); 

	void addSection(ESectionType type, const QByteArray& aData);
	
	// if there is not section for including type, function will return empty section
	QByteArray getSection(ESectionType type);
	
	uint32 getSectionCount();

	// warning, if include index more than section count, will be something bad :)
	ESectionType getSectionType(uint index);

	void print(); // :)

private:
	QString m_sSignature;
	uint32 m_nVersion;
	uint32 m_nSectionCount;
	QVector<ESectionType> m_vSectionsType;
	QVector<int32> m_vSectionsSize;
	QVector<QByteArray> m_Buffer;
};

#endif // !_rw_h
