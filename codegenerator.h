#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "disparser.h"
#include <QVector>
#include <qfile.h>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include "instructions.h"



class CCodeGenerator
{
public:
    CCodeGenerator() {}
    void work(QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens,  QString sFileTxt);
};

#endif
