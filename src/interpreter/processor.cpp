#include "processor.h"
#include "../compiler/instructions.h"
#include "executor.h"

const std::map<EInstruction, CProcessor::FnCommand> CProcessor::s_mapCommands
{
	{ EInstruction::Invalid, &CProcessor::IExecutor::Invalid },
	{ EInstruction::Nop, &CProcessor::IExecutor::Nop },
	{ EInstruction::Break, &CProcessor::IExecutor::Break },
	{ EInstruction::Int, &CProcessor::IExecutor::Int },
	//{ EInstruction::Jump, &CProcessor::IExecutor::Jump },
	//{ EInstruction::Call, &CProcessor::IExecutor::Call },
	//{ EInstruction::Ret, &CProcessor::IExecutor::Ret },
	//{ EInstruction::Iret, &CProcessor::IExecutor::Iret },
	//{ EInstruction::Sti, &CProcessor::IExecutor::Sti },
	//{ EInstruction::Cli, &CProcessor::IExecutor::Cli },
	//{ EInstruction::Stc, &CProcessor::IExecutor::Stc },
	//{ EInstruction::Clc, &CProcessor::IExecutor::Clc },
	//{ EInstruction::Assign, &CProcessor::IExecutor::Assign },
	//{ EInstruction::Move, &CProcessor::IExecutor::Move },
	//{ EInstruction::Swap, &CProcessor::IExecutor::Swap },
	//{ EInstruction::Add, &CProcessor::IExecutor::Add },
	//{ EInstruction::Adc, &CProcessor::IExecutor::Adc },
	//{ EInstruction::Sub, &CProcessor::IExecutor::Sub },
	//{ EInstruction::Sbb, &CProcessor::IExecutor::Sbb },
	//{ EInstruction::Mul, &CProcessor::IExecutor::Mul },
	//{ EInstruction::Imul, &CProcessor::IExecutor::Imul },
	//{ EInstruction::Div, &CProcessor::IExecutor::Div },
	//{ EInstruction::Idiv, &CProcessor::IExecutor::Idiv },
	//{ EInstruction::Inc, &CProcessor::IExecutor::Inc },
	//{ EInstruction::Dec, &CProcessor::IExecutor::Dec },
	//{ EInstruction::Neg, &CProcessor::IExecutor::Neg },
	//{ EInstruction::Cmp, &CProcessor::IExecutor::Cmp },
	//{ EInstruction::And, &CProcessor::IExecutor::And },
	//{ EInstruction::Or, &CProcessor::IExecutor::Or },
	//{ EInstruction::Xor, &CProcessor::IExecutor::Xor },
	//{ EInstruction::Nand, &CProcessor::IExecutor::Nand },
	//{ EInstruction::Nor, &CProcessor::IExecutor::Nor },
	//{ EInstruction::Not, &CProcessor::IExecutor::Not },
	//{ EInstruction::Shr, &CProcessor::IExecutor::Shr },
	//{ EInstruction::Sar, &CProcessor::IExecutor::Sar },
	//{ EInstruction::Shl, &CProcessor::IExecutor::Shl },
	//{ EInstruction::Sal, &CProcessor::IExecutor::Sal },
	//{ EInstruction::Ror, &CProcessor::IExecutor::Ror },
	//{ EInstruction::Rcr, &CProcessor::IExecutor::Rcr },
	//{ EInstruction::Rol, &CProcessor::IExecutor::Rol },
	//{ EInstruction::Rcl, &CProcessor::IExecutor::Rcl },
	//{ EInstruction::Test, &CProcessor::IExecutor::Test },
	//{ EInstruction::Load, &CProcessor::IExecutor::Load },
	//{ EInstruction::Store, &CProcessor::IExecutor::Store },
	//{ EInstruction::Push, &CProcessor::IExecutor::Push },
	//{ EInstruction::Pop, &CProcessor::IExecutor::Pop },
	//{ EInstruction::Pushf, &CProcessor::IExecutor::Pushf },
	//{ EInstruction::Popf, &CProcessor::IExecutor::Popf },
	//{ EInstruction::Pushsf, &CProcessor::IExecutor::Pushsf },
	//{ EInstruction::Popsf, &CProcessor::IExecutor::Popsf },
	//{ EInstruction::In, &CProcessor::IExecutor::In },
	//{ EInstruction::Out, &CProcessor::IExecutor::Out }
};

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

CProcessor::t_commandType CProcessor::fetch()
{
	return static_cast<uint16>(m_pMemory->operator[](m_nPC));
}

CProcessor::SCommand CProcessor::decode(t_commandType& commandType)
{
	auto it = s_mapCommands.find(static_cast<EInstruction>(commandType.instr));
	if (it != s_mapCommands.end())
	{
		CProcessor::FnCommand fnCommand = it->second;
		SCommand as;
		IExecutor* executor = new CExecutor;
		(executor->*fnCommand)(as);
	}
	return CProcessor::SCommand();
}

void CProcessor::execute(SCommand)
{
	// Todo
}

void CProcessor::Init(CMemoryPtr memory, int PC)
{
	m_pMemory = memory;
}

bool CProcessor::IsRunning()
{
	return m_bIsRunning;
}

void CProcessor::Run()
{
	while (m_bControlFlag)
	{
		m_nIR = fetch();
		m_oCurrentCommandContext = decode(m_nIR);
		execute(m_oCurrentCommandContext);
	}
}
