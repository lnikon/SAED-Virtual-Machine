#ifndef DISASSEMBLY_H
#define DISASSEMBLY_H

#include <QTextStream>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <QString>
#include "instructions.h"

QString signature = "SAED/VirtualMachine/ExeFile";
int signatureSize = signature.size();

enum class ESectionType
{
    Data, Code, DataTable, CodeTable
};
struct SHeaderTable{
    SHeaderTable()
    {
    }
    SHeaderTable(ESectionType tt, int oo, int ss) : type(tt), offset(oo), size(ss)
    {
    }
    ESectionType type;
    int offset;
    int size;
};
struct SHeader{
    SHeader()
    {
    }
    SHeader(QString ss, int vv) :signature(ss), version(vv)
    {
    }
    QString signature;
    int version;
    int recordCount;
    QVector<SHeaderTable> arrayTable;
};
struct DataToken
{
    QString type;
    QString ident;
    QVariant value;

};

struct CodeToken
{
    QString type;
    QString instName;
    ArgumentType argType;
    QVariant value;
};

class CDisassembly
{
public:

    CDisassembly();
    QVector<DataToken> dataOut;
    QVector<CodeToken> codeOut;

     void GetHeader(QDataStream & );
private:

       SHeader m_ob;


    bool CheckSignature();

    void GetDataOut(QFile &, QDataStream & );
    void GetCodeOut(QDataStream & );


};

#endif // DISASSEMBLY_H
