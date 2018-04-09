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

    void Init(QString const& inputFileName);

    void Run();
    void Stop();
    void Reset();

    bool isValid();
    bool isRuning();

	void setDebugger(IDebuggerPtr pIDebugger);

	CProcessorPtr getProcessor();
	CMemoryPtr getMemory();

private:
    CProcessorPtr m_pProcessor;
    CMemoryPtr m_pMemory;

	IDebuggerPtr m_pIDebugger;

    CLoader* m_Loader;
    CIOManager m_IOMan;

};

using CInterpreterPtr = std::shared_ptr<CInterpreter>;

#endif // INTERPRETER_H
