#include "processor.h"

#pragma region flag_impl
CProcessor::CFlags::CFlags()
	: m_ui16Value(0)
{
}

bool CProcessor::CFlags::getTrap() const
{
	return (m_ui16Value & uint16(eMask_TF)) != 0;
}

bool CProcessor::CFlags::getCarry() const
{
	return (m_ui16Value & uint16(eMask_CF)) != 0;
}

bool CProcessor::CFlags::getParity() const
{
	return (m_ui16Value & uint16(eMask_PF)) != 0;
}

bool CProcessor::CFlags::getZero() const
{
	return (m_ui16Value & uint16(eMask_ZF)) != 0;
}

bool CProcessor::CFlags::getSign() const
{
	return (m_ui16Value & uint16(eMask_SF)) != 0;
}

bool CProcessor::CFlags::getOverflow() const
{
	return (m_ui16Value & uint16(eMask_OF)) != 0;
}

uint16 CProcessor::CFlags::getFlags() const
{
	return (m_ui16Value & uint16(0x007F));
}

void CProcessor::CFlags::setTrap(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_TF)) : (m_ui16Value & ~uint16(eMask_TF));
}

void CProcessor::CFlags::setCarry(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_CF)) : (m_ui16Value & ~uint16(eMask_CF));
}

void CProcessor::CFlags::setParity(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_PF)) : (m_ui16Value & ~uint16(eMask_PF));
}

void CProcessor::CFlags::setZero(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_ZF)) : (m_ui16Value & ~uint16(eMask_ZF));
}

void CProcessor::CFlags::setSign(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_SF)) : (m_ui16Value & ~uint16(eMask_SF));
}

void CProcessor::CFlags::setOverflow(bool b)
{
	m_ui16Value = b ? (m_ui16Value | uint16(eMask_OF)) : (m_ui16Value & ~uint16(eMask_OF));
}

void CProcessor::CFlags::setFlags(uint16 ui16Value)
{
	m_ui16Value = (ui16Value & uint16(0x007F)) | (m_ui16Value & uint16(0XFF80));
}

bool CProcessor::CFlags::IsEqual() const
{
	return (getZero() == true);
}

bool CProcessor::CFlags::IsNotEqual() const
{
	return (getZero() == false);
}

bool CProcessor::CFlags::IsAbove() const
{
	return (getCarry() == false && getZero() == false);
}

bool CProcessor::CFlags::IsAboveOrEqual() const
{
	return (getCarry() == false);
}

bool CProcessor::CFlags::IsBelow() const
{
	return (getCarry() == true);
}

bool CProcessor::CFlags::IsBelowOrEqual() const
{
	return (getCarry() == true || getZero() == true);
}

bool CProcessor::CFlags::IsGreat() const
{
	return (getZero() == false && getSign() == getOverflow());
}

bool CProcessor::CFlags::IsGreatOrEqual() const
{
	return (getSign() == getOverflow());
}

bool CProcessor::CFlags::IsLow() const
{
	return (getSign() != getOverflow());
}

bool CProcessor::CFlags::IsLowOrEqual() const
{
	return (getZero() == true && getSign() != getOverflow());
}

bool CProcessor::CFlags::IsOverflow() const
{
	return (getOverflow() == true);
}

bool CProcessor::CFlags::IsNotOverflow() const
{
	return (getOverflow() == false);
}

bool CProcessor::CFlags::IsSigned() const
{
	return (getSign() == true);
}

bool CProcessor::CFlags::IsNotSigned() const
{
	return (getSign() == false);
}

bool CProcessor::CFlags::IsParity() const
{
	return (getParity() == true);
}

bool CProcessor::CFlags::IsNotParity() const
{
	return (getParity() == false);
}

#pragma endregion


void CProcessor::fetch()
{
	m_nIR = static_cast<uint16>(m_pMemory->operator[](m_nPC));
}

void CProcessor::decode()
{
	
}

void CProcessor::Init(CMemoryPtr memory, int PC)
{
	m_pMemory = memory;
}
