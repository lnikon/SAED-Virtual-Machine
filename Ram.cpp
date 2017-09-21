#include"Ram.h"

CRam::CRam(unsigned int size)
{
	m_uiSize = size;
	m_ucMemory = new unsigned char[size];
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

void CRam::resize(unsigned int size)
{
	unsigned char* newMemory = new unsigned char(size);
	for (int i(0); i < m_uiSize && i < size; ++i)
	{
		newMemory[i] = m_ucMemory[i];
	}
	m_uiSize = size;
	delete[] m_ucMemory;
	m_ucMemory = newMemory;
}

void CRam::reserve(unsigned int size)
{
	resize(size + m_uiSize);
}
