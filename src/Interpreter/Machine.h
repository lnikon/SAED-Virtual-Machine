#ifndef MACHINE_H
#define MACHINE_H

#include "Controller.h"
#include "CPU.h"
#include "IOManager.h"
#include "Loader.h"
#include "RAM.h"
#include "RW.h"

class CMachine
{
public:

private:
	CController* m_controller;
	CCPU* m_CPU;
	CIOManager* m_IOManager;
	CLoader* m_loader;
	CRAM* m_RAM;


};
#endif // !MACHINE_H
