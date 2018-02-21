#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "memory.h"
#include "loader.h"
#include <QTextStream>
class CInterpreter
{
public:
    CInterpreter();
    ~CInterpreter();

    void Init (QTextStream &input);
    bool isValid();
    void Run();
    void Stop();
    void Reset();
    bool isRuning();

    inline CCPU* getCPU();
    inline CMemory* getMem();


private:
    CCPU* m_CPU;
    CMemory* m_Memory;
    CLoader* m_Loader;
    //CIOManager* m_IOMan;


};

#endif // INTERPRETER_H

