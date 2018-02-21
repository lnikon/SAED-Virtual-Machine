#include "interpreter.h"

void CInterpreter::Init(QTextStream &input)
{
    Reset();

    m_Memory = new CMemory(1024);

    //m_IOMan = new CIOManager;

    m_Loader = new CLoader;
    m_Loader->Load(input,m_Memory);

    m_CPU = new CCPU;
    m_CPU->Init(m_Memory,1,m_IOMan);

}

void CInterpreter::isValid()
{
 if (m_Memory != nullptr && m_Loader != nullptr
         && m_CPU != nullptr && m_IOMan != nullptr)
 {
     return true;
 }
 return false;
}

void CInterpreter::Run()
{
    if(!m_CPU->isRunning())
    {
        m_CPU->Run();
    }
}

void CInterpreter::Stop()
{

}

void CInterpreter::Reset()
{
    m_CPU = nullptr;
    m_Memory = nullptr;
    m_Loader = nullptr;
    //m_IOMan = nullptr;
}

bool CInterpreter::isRuning()
{
    if (m_CPU->isRunning() && m_CPU != nullptr)
        return true;
    return false;
}
