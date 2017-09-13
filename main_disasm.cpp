#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QDataStream>

#include "disassembly.h"
#include "instructions.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString fileName = "Executable.txt";
    QFile file(fileName);
    QFileInfo f_info (fileName);


       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
       {
           qDebug() << "Cannot open" + f_info.absoluteFilePath() +
               "file doesn't exist";
       }


      QDataStream in(&file);


      CDisassembly disasm;
      disasm.GetHeader(in);

file.close();
     return a.exec();
}
