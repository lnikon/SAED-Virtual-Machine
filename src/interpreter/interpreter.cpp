#include "interpreter.h"

CInterpreter::CInterpreter() : m_pIOMan(*new CIOManager)
{
}

CInterpreter::~CInterpreter()
{
}

void CInterpreter::Init(QTextStream &input)
{
	Reset();

	m_pMemory = std::make_shared<CMemory>();

	//m_Loader = new CLoader;
	//m_Loader->load(input, m_Memory);

	m_pProcessor = std::make_unique<CProcessor>();
	m_pProcessor->Init(m_pMemory, 1);

}

bool CInterpreter::isValid()
{
	if (m_pMemory != nullptr /*&& m_Loader != nullptr*/
		&& m_pProcessor != nullptr && &m_pIOMan != nullptr)
	{
		return true;
	}
	return false;
}

void CInterpreter::Run()
{
	/*if (!m_CPU->isRunning())
	{
		m_CPU->Run();
	}*/
}

void CInterpreter::Stop()
{

}

void CInterpreter::Reset()
{
	m_pProcessor = nullptr;
	m_pMemory = nullptr;
	//m_Loader = nullptr;
	//m_IOMan = nullptr;
}

bool CInterpreter::isRuning()
{
	//if (m_CPU->isRunning() && m_CPU != nullptr)
	//	return true;
	return false;
}
