#include <QCoreApplication>
#include <QDebug>

#include "rw.h"
#include "loader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CLoader loader; // creat object

    loader.load("out.txt"); // load file

    CLoader::SMemory memory = loader.getMemory(); // get struct of memory

    // print to show the result
    qDebug() << "ip poristin: " << memory.nIPPosition << endl;
    qDebug() << "dataSize:    " << memory.nDataSize   << endl;
    qDebug() << "stackSize:   " << memory.nStackSize  << endl;
    qDebug() << "memory:      " << memory.aMemory     << endl;

    qDebug() << "done" << endl; // end :)

    return a.exec();
}
