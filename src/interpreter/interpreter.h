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

    void Run();
    void Stop();
    void Reset();

    bool isValid();
    bool isRuning();

	inline CProcessorPtr getCPU() {}
	inline CMemoryPtr getMem() {}

private:
    CProcessorPtr m_pProcessor;
    CMemoryPtr m_pMemory;
    //CLoader* m_Loader;

	//is this ok
    CIOManager& m_pIOMan;

};

#endif // INTERPRETER_H

