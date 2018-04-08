#include "executor.h"

void CExecutor::Invalid(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Nop(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::End(CProcessor::SState & machineState, CProcessor::SCommand & comand)
{
	machineState.m_bControlFlag = false;
}

void CExecutor::Break(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
	machineState.m_fFlags.setTrap(true);
}

void CExecutor::Int(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Jump(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Call(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Ret(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Iret(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Sti(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Cli(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Stc(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Clc(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Assign(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Move(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Swap(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Add(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Adc(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Sub(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Sbb(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Mul(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Imul(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Div(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Idiv(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Inc(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Dec(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Neg(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Cmp(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::And(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Or(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Xor(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Nand(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Nor(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Not(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Shr(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Sar(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Shl(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Sal(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Ror(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Rcr(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Rol(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Rcl(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Test(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Load(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Store(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Push(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Pop(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Pushf(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Popf(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Pushsf(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Popsf(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::In(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}

void CExecutor::Out(CProcessor::SState& machineState, CProcessor::SCommand& comand)
{
}
