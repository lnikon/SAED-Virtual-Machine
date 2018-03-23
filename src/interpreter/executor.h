#pragma once

#include "processor.h"

class CExecutor : public CProcessor::IExecutor
{
public:

	void Invalid(CProcessor::SCommand& comand) override;
	void Nop(CProcessor::SCommand& comand) override;
	void Break(CProcessor::SCommand& comand) override;
	void Int(CProcessor::SCommand& comand) override;
	void Jump(CProcessor::SCommand& comand) override;
	void Call(CProcessor::SCommand& comand) override;
	void Ret(CProcessor::SCommand& comand) override;
	void Iret(CProcessor::SCommand& comand) override;
	void Sti(CProcessor::SCommand& comand) override;
	void Cli(CProcessor::SCommand& comand) override;
	void Stc(CProcessor::SCommand& comand) override;
	void Clc(CProcessor::SCommand& comand) override;
	void Assign(CProcessor::SCommand& comand) override;
	void Move(CProcessor::SCommand& comand) override;
	void Swap(CProcessor::SCommand& comand) override;
	void Add(CProcessor::SCommand& comand) override;
	void Adc(CProcessor::SCommand& comand) override;
	void Sub(CProcessor::SCommand& comand) override;
	void Sbb(CProcessor::SCommand& comand) override;
	void Mul(CProcessor::SCommand& comand) override;
	void Imul(CProcessor::SCommand& comand) override;
	void Div(CProcessor::SCommand& comand) override;
	void Idiv(CProcessor::SCommand& comand) override;
	void Inc(CProcessor::SCommand& comand) override;
	void Dec(CProcessor::SCommand& comand) override;
	void Neg(CProcessor::SCommand& comand) override;
	void Cmp(CProcessor::SCommand& comand) override;
	void And(CProcessor::SCommand& comand) override;
	void Or(CProcessor::SCommand& comand) override;
	void Xor(CProcessor::SCommand& comand) override;
	void Nand(CProcessor::SCommand& comand) override;
	void Nor(CProcessor::SCommand& comand) override;
	void Not(CProcessor::SCommand& comand) override;
	void Shr(CProcessor::SCommand& comand) override;
	void Sar(CProcessor::SCommand& comand) override;
	void Shl(CProcessor::SCommand& comand) override;
	void Sal(CProcessor::SCommand& comand) override;
	void Ror(CProcessor::SCommand& comand) override;
	void Rcr(CProcessor::SCommand& comand) override;
	void Rol(CProcessor::SCommand& comand) override;
	void Rcl(CProcessor::SCommand& comand) override;
	void Test(CProcessor::SCommand& comand) override;
	void Load(CProcessor::SCommand& comand) override;
	void Store(CProcessor::SCommand& comand) override;
	void Push(CProcessor::SCommand& comand) override;
	void Pop(CProcessor::SCommand& comand) override;
	void Pushf(CProcessor::SCommand& comand) override;
	void Popf(CProcessor::SCommand& comand) override;
	void Pushsf(CProcessor::SCommand& comand) override;
	void Popsf(CProcessor::SCommand& comand) override;
	void In(CProcessor::SCommand& comand) override;
	void Out(CProcessor::SCommand& comand) override;
};
