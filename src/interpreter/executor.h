#pragma once

#include "processor.h"

class CExecutor : public CProcessor::IExecutor
{
public:

	void Invalid(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Nop(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void End(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Break(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Int(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Jump(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Call(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Ret(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Iret(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Sti(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Cli(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Stc(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Clc(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Assign(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Move(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Swap(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Add(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Adc(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Sub(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Sbb(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Mul(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Imul(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Div(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Idiv(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Inc(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Dec(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Neg(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Cmp(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void And(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Or(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Xor(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Nand(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Nor(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Not(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Shr(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Sar(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Shl(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Sal(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Ror(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Rcr(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Rol(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Rcl(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Test(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Load(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Store(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Push(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Pop(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Pushf(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Popf(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Pushsf(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Popsf(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void In(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
	void Out(CProcessor::SState& machineState, CProcessor::SCommand& comand) override;
};
