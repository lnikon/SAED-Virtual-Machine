#include <QtCore/QCoreApplication>

#include "Machine.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	CMachine machine;

	return a.exec();
}
