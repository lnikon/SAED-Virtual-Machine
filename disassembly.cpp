#include "disassembly.h"

CDisassembly::CDisassembly()
{

}


void CDisassembly :: GetHeader(QDataStream &in)
{

      in>>m_ob.signature;
      in>> m_ob.version;
      in>>m_ob.recordCount;

      for (int i = 0; i < m_ob.recordCount; ++i)
      {
          in>> m_ob.arrayTable[i].type;
          in>> m_ob.arrayTable[i].offset;
          in>> m_ob.arrayTable[i].size;
      }


}


bool CDisassembly :: CheckSignature()
{
     if (m_ob.signature == signature)
     {
         return true;
     }
     else
     {
         return false;
     }
}


void  CDisassembly :: GetDataOut(QFile &file, QDataStream &in)
{

    file.seek(signature.size()+sizeof(int)+sizeof(int));

    for(int i = 0; i < m_ob.arrayTable[0].size; ++i )
    {
        int typ;
        in>>typ;

        switch (typ)
        {
        case 0:
            dataOut[i].type="byte";
            in>>dataOut[i].ident;
            break;
        case 1:
            dataOut[i].type="word";
            in>>dataOut[i].ident;
            break;
        case 2:
            dataOut[i].type="dword";
            in>>dataOut[i].ident;
            break;
        case 3:
            dataOut[i].type="qword";
            in>>dataOut[i].ident;
            break;

        }

        file.seek(m_ob.arrayTable[0].offset);
        for(int i = 0; i < m_ob.arrayTable[0].size; ++i )
        {


        }


    }


}

void CDisassembly:: GetCodeOut(QDataStream & in)
{

}

