#ifndef _Loader_h_
#define _Loader_h_

#include "Ram.h"
#include "parser.h"
#include <QTextStream>
#include <QDataStream>
#include <string>

using namespace std;

class CLoader
{
public:
	CLoader() {};
	void work(CRam& ram, QDataStream& in);
private:
	QString m_sSignature = "SAED/VirtualMachine/ExeFile";
private:
	bool checkSignature(QDataStream& in);
	int getInt(QDataStream& in);
};

#endif // !_Loader_h_

