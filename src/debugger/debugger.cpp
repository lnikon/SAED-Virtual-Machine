#include "debugger.h"

#include <iostream>

CDebugger::CDebugger(CInterpreterPtr pMachine) : m_pCInterpreter(pMachine)
{
}

void CDebugger::getState()
{
	CProcessorPtr proc = m_pCInterpreter->getProcessor();
	CProcessor::SState state = proc->getState();
	
	std::cout << "__________State__________" << std::endl;

}

void CDebugger::Run()
{
	getState();
	std::cin.get();
}
