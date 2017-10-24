#include"Ram.h"

CRam::CRam()
{
	m_uiSize = 4096;
	m_ucMemory = new unsigned char[m_uiSize];
}

CRam::CRam(unsigned int size)
{
	m_uiSize = size;
	m_ucMemory = new unsigned char[m_uiSize];
}

CRam::~CRam()
{
	delete[] m_ucMemory;
}

unsigned int CRam::getSize()
{
	return m_uiSize;
}

unsigned int CRam::getIP()
{
	return m_uiIP;
}

void CRam::setIP(unsigned int newIP)
{
	m_uiIP = newIP;
}

unsigned char& CRam::operator[](unsigned int position) 
{
	return m_ucMemory[position];
}
