#include "interpreter.h"
#include "../compiler/readerwriter.h"

CInterpreter::CInterpreter()
{
}

CInterpreter::~CInterpreter()
{
}

void CInterpreter::Init(QString const& inputFileName)
{
	Reset();

	m_pMemory = std::make_shared<CMemory>();
	m_Loader = new CLoader;

	CReaderWriter RW(inputFileName);

	CLoader::SInfo info = m_Loader->load(m_pMemory, RW);

	m_pProcessor = std::make_shared<CProcessor>();
	m_pProcessor->Init(m_pMemory, info.codeIndex);


}

bool CInterpreter::isValid()
{
	if (m_pMemory != nullptr && m_Loader != nullptr
		&& m_pProcessor != nullptr)
	{
		return true;
	}
	return false;
}

void CInterpreter::Run()
{
	if (!m_pProcessor->IsRunning())
	{
		m_pProcessor->Run();
	}
}

void CInterpreter::Stop()
{

}

void CInterpreter::Reset()
{
	m_pProcessor = nullptr;
	m_pMemory = nullptr;
	m_Loader = nullptr;
	//m_IOMan = nullptr;
}

bool CInterpreter::isRuning()
{
	if (m_pProcessor != nullptr && m_pProcessor->IsRunning())
	{
		return true;
	}
	return false;
}

void CInterpreter::setDebugger(IDebuggerPtr pIDebugger)
{
	m_pIDebugger = pIDebugger;

	if (m_pProcessor != nullptr)
	{
		if (m_pIDebugger != nullptr)
		{
			m_pProcessor->AttachDebugger(m_pIDebugger);
		}
		else
		{
			m_pProcessor->DetachDebugger();
		}
	}
}

CProcessorPtr CInterpreter::getProcessor()
{
	return m_pProcessor;
}

CMemoryPtr CInterpreter::getMemory()
{
	return m_pMemory;
}
