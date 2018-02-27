#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "memory.h"
#include "loader.h"
#include "processor.h"

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

	inline CProcessor* getCPU() {}
	inline CMemory* getMem() {}


private:
    CProcessor* m_CPU;
    CMemory* m_Memory;
    //CLoader* m_Loader;
    CIOManager* m_IOMan;

};

#endif // INTERPRETER_H

