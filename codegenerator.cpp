#include "codegenerator.h"

void CCodeGenerator::work(QVector<SDataToken> dataTokens, QVector<SCodeToken> codeTokens,  QString sFileTxt)
{
    QFile file (fileName);
    file.open(QIODevice::WriteOnly |QIODevice::Append);
    QDataStream out(&file);

    if(dataTokens.size())

    {
        out<<".data"<<endl;
        for(int i=0; i<dataTokens.size();++i)
        {
           switch(dataTokens[i].type){
           case 0:
           {
               out<<"byte"<<dataTokens[i].identifierName<<"="<<dataTokens[i].value<<endl;
               break;
           }
           case 1:
           {
               out<<"word"<<dataTokens[i].identifierName<<"="<<dataTokens[i].value<<endl;
               break;
           }
           case 2:
           {
               out<<"dword"<<dataTokens[i].identifierName<<"="<<dataTokens[i].value<<endl;
               break;
           }
           case 3:
           {
               out<<"qword"<<dataTokens[i].identifierName<<"="<<dataTokens[i].value<<endl;
           }

           }

        }
    }
    if(codeTokens.size())
    {
        out<<".code"<<endl;
        for(int i = 0; i<codeTokens.size(); ++i)
        {
            //uint16 _intsr = codeTokens[i].opcode.instr;
            out<<"instr="<<codeTokens[i].opcode.instr;
            out<<"argType1"<<codeTokens[i].opcode.arg1Type;
            out<<"argType2"<<codeTokens[i].opcode.arg1Type;
            out<<"argType3"<<codeTokens[i].opcode.arg1Type;
            out<<"argSize"<<codeTokens[i].opcode.argSize;
            out<<"argValue1"<<codeTokens[i].argValue[0];
            out<<"argValue2"<<codeTokens[i].argValue[1];
            out<<"argValue3"<<codeTokens[i].argValue[2]<<endl;
        }
    }
}
