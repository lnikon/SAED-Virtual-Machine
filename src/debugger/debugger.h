#pragma once

#include "../interpreter/interpreter.h"

#include <memory>

class CDebugger : public IDebugger
{
public:

	CDebugger(CInterpreterPtr pMachine);

	CDebugger(CDebugger const&) = delete;
	CDebugger(CDebugger&&) = delete;
	void operator=(CDebugger const&) = delete;
	void operator=(CDebugger&&) = delete;

	void getState();


public:
	void Run() override;

private:
	CInterpreterPtr	 m_pCInterpreter;

};