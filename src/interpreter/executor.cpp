#include "executor.h"

void CExecutor::Invalid(CProcessor::SCommand & comand)
{
}

void CExecutor::Nop(CProcessor::SCommand & comand)
{
}

void CExecutor::Break(CProcessor::SCommand & comand)
{
}

void CExecutor::Int(CProcessor::SCommand & comand)
{
}

void CExecutor::Jump(CProcessor::SCommand & comand)
{
}

void CExecutor::Call(CProcessor::SCommand & comand)
{
}

void CExecutor::Ret(CProcessor::SCommand & comand)
{
}

void CExecutor::Iret(CProcessor::SCommand & comand)
{
}

void CExecutor::Sti(CProcessor::SCommand & comand)
{
}

void CExecutor::Cli(CProcessor::SCommand & comand)
{
}

void CExecutor::Stc(CProcessor::SCommand & comand)
{
}

void CExecutor::Clc(CProcessor::SCommand & comand)
{
}

void CExecutor::Assign(CProcessor::SCommand & comand)
{
	std::cout << comand.op.argSize <<  " Assign" << std::endl;
}

void CExecutor::Move(CProcessor::SCommand & comand)
{
}

void CExecutor::Swap(CProcessor::SCommand & comand)
{
}

void CExecutor::Add(CProcessor::SCommand & comand)
{
	std::cout << comand.op.argSize <<  " Add" << std::endl;
}

void CExecutor::Adc(CProcessor::SCommand & comand)
{
}

void CExecutor::Sub(CProcessor::SCommand & comand)
{
}

void CExecutor::Sbb(CProcessor::SCommand & comand)
{
}

void CExecutor::Mul(CProcessor::SCommand & comand)
{
}

void CExecutor::Imul(CProcessor::SCommand & comand)
{
}

void CExecutor::Div(CProcessor::SCommand & comand)
{
}

void CExecutor::Idiv(CProcessor::SCommand & comand)
{
}

void CExecutor::Inc(CProcessor::SCommand & comand)
{
}

void CExecutor::Dec(CProcessor::SCommand & comand)
{
}

void CExecutor::Neg(CProcessor::SCommand & comand)
{
}

void CExecutor::Cmp(CProcessor::SCommand & comand)
{
}

void CExecutor::And(CProcessor::SCommand & comand)
{
}

void CExecutor::Or(CProcessor::SCommand & comand)
{
}

void CExecutor::Xor(CProcessor::SCommand & comand)
{
}

void CExecutor::Nand(CProcessor::SCommand & comand)
{
}

void CExecutor::Nor(CProcessor::SCommand & comand)
{
}

void CExecutor::Not(CProcessor::SCommand & comand)
{
}

void CExecutor::Shr(CProcessor::SCommand & comand)
{
}

void CExecutor::Sar(CProcessor::SCommand & comand)
{
}

void CExecutor::Shl(CProcessor::SCommand & comand)
{
}

void CExecutor::Sal(CProcessor::SCommand & comand)
{
}

void CExecutor::Ror(CProcessor::SCommand & comand)
{
}

void CExecutor::Rcr(CProcessor::SCommand & comand)
{
}

void CExecutor::Rol(CProcessor::SCommand & comand)
{
}

void CExecutor::Rcl(CProcessor::SCommand & comand)
{
}

void CExecutor::Test(CProcessor::SCommand & comand)
{
}

void CExecutor::Load(CProcessor::SCommand & comand)
{
}

void CExecutor::Store(CProcessor::SCommand & comand)
{
}

void CExecutor::Push(CProcessor::SCommand & comand)
{
}

void CExecutor::Pop(CProcessor::SCommand & comand)
{
}

void CExecutor::Pushf(CProcessor::SCommand & comand)
{
}

void CExecutor::Popf(CProcessor::SCommand & comand)
{
}

void CExecutor::Pushsf(CProcessor::SCommand & comand)
{
}

void CExecutor::Popsf(CProcessor::SCommand & comand)
{
}

void CExecutor::In(CProcessor::SCommand & comand)
{
}

void CExecutor::Out(CProcessor::SCommand & comand)
{
}
