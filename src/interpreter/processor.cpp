#include "processor.h"
#include "../compiler/instructions.h"
#include "executor.h"
#include "../debugger/debugger.h"

#include <utility>
#include <QHash>
#include <intrin.h>

const std::unordered_map<EInstruction, CProcessor::SCommandDefinition> CProcessor::s_mapCommands
{
	{ EInstruction::Invalid, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Invalid} },
	{ EInstruction::Nop, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Nop} },
	{ EInstruction::End, CProcessor::SCommandDefinition{&CProcessor::IExecutor::End} },
	{ EInstruction::Break, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Break} },
	{ EInstruction::Int, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Int} },
	{ EInstruction::Jump, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Jump} },
	{ EInstruction::Call, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Call} },
	{ EInstruction::Ret, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Ret} },
	{ EInstruction::Iret, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Iret} },
	{ EInstruction::Sti, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Sti} },
	{ EInstruction::Cli, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Cli} },
	{ EInstruction::Stc, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Stc} },
	{ EInstruction::Clc, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Clc} },
	{ EInstruction::Assign, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Assign} },
	{ EInstruction::Move, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Move} },
	{ EInstruction::Swap, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Swap} },
	{ EInstruction::Add, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Add} },
	{ EInstruction::Adc, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Adc} },
	{ EInstruction::Sub, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Sub} },
	{ EInstruction::Sbb, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Sbb} },
	{ EInstruction::Mul, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Mul} },
	{ EInstruction::Imul, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Imul} },
	{ EInstruction::Div, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Div} },
	{ EInstruction::Idiv, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Idiv} },
	{ EInstruction::Inc, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Inc} },
	{ EInstruction::Dec, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Dec} },
	{ EInstruction::Neg, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Neg} },
	{ EInstruction::Cmp, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Cmp} },
	{ EInstruction::And, CProcessor::SCommandDefinition{&CProcessor::IExecutor::And} },
	{ EInstruction::Or, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Or} },
	{ EInstruction::Xor, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Xor} },
	{ EInstruction::Nand, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Nand} },
	{ EInstruction::Nor, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Nor} },
	{ EInstruction::Not, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Not} },
	{ EInstruction::Shr, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Shr} },
	{ EInstruction::Sar, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Sar} },
	{ EInstruction::Shl, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Shl} },
	{ EInstruction::Sal, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Sal} },
	{ EInstruction::Ror, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Ror} },
	{ EInstruction::Rcr, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Rcr} },
	{ EInstruction::Rol, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Rol} },
	{ EInstruction::Rcl, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Rcl} },
	{ EInstruction::Test, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Test} },
	{ EInstruction::Load, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Load} },
	{ EInstruction::Store, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Store} },
	{ EInstruction::Push, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Push} },
	{ EInstruction::Pop, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Pop} },
	{ EInstruction::Pushf, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Pushf} },
	{ EInstruction::Popf, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Popf} },
	{ EInstruction::Pushsf, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Pushsf} },
	{ EInstruction::Popsf, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Popsf} },
	{ EInstruction::In, CProcessor::SCommandDefinition{&CProcessor::IExecutor::In} },
	{ EInstruction::Out, CProcessor::SCommandDefinition{&CProcessor::IExecutor::Out} }
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
	return _byteswap_ushort(m_pMemory->at<uint16>(m_oState.m_nPC));
}

CProcessor::SCommand CProcessor::decode(t_commandType& commandType)
{
	auto it = s_mapCommands.find(static_cast<EInstruction>(commandType.instr));
	SCommand as;
	if (it != s_mapCommands.end())
	{
		std::cout << int(it->first) << std::endl;
		CProcessor::FnCommand fnCommand = it->second.pFnCommand;
		as.command = fnCommand;
		as.op = commandType;
		m_oState.m_nPC += 2;
		if (as.op.arg1Type != 0) // 0 for EArgumentType::None
		{
			as.argValue.push_back(static_cast<uint32>(_byteswap_ulong(m_pMemory->at<uint32>(m_oState.m_nPC +=  4))));
		}
		if (as.op.arg2Type != 0)
		{
			as.argValue.push_back(static_cast<uint32>(_byteswap_ulong(m_pMemory->at<uint32>(m_oState.m_nPC += 4))));
		}
		if (as.op.arg3Type != 0)
		{
			as.argValue.push_back(static_cast<uint32>(_byteswap_ulong(m_pMemory->at<uint32>(m_oState.m_nPC += 4))));
		}
	}
	return as;
}

void CProcessor::execute(SCommand command)
{
	IExecutor* executor = new CExecutor;
	(executor->*command.command)(m_oState, command);
}

void CProcessor::Init(CMemoryPtr memory, int PC)
{
	m_pMemory = memory;
	m_oState.m_nPC = PC;
}

bool CProcessor::IsRunning()
{
	return m_bIsRunning;
}

void CProcessor::Run()
{
	//m_oState.m_fFlags.setTrap(true);
	while (m_oState.m_bControlFlag)
	{
		if (m_oState.m_fFlags.getTrap())
		{
			m_pIDebugger->Run();
		}
		m_oState.m_nIR = fetch();
		m_oCurrentCommandContext = decode(m_oState.m_nIR);
		m_oState.m_nPC += 4;
		execute(m_oCurrentCommandContext);
	}
}

void CProcessor::Stop()
{
	m_oState.m_bControlFlag = false;
}

void CProcessor::AttachDebugger(IDebuggerPtr pDebugger)
{
	if (pDebugger == nullptr)
	{
		// throw exception
	}
	m_pIDebugger = pDebugger;
	//m_oState.m_fFlags.setTrap(true);
}

void CProcessor::DetachDebugger()
{
	m_pIDebugger = nullptr;
}

CProcessor::SState const & CProcessor::getState() const
{
	return m_oState;
}

CProcessor::SCommandDefinition::SCommandDefinition(FnCommand fn) : pFnCommand(fn)
{
}
