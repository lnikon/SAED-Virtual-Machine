#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "i_o_manager.h"
#include "../compiler/instructions.h"

#include <memory>
#include <functional>
#include <unordered_map>

#include <QVarLengthArray>

class IDebugger
{
public:
	virtual void Run() = 0;
};

using IDebuggerPtr = std::shared_ptr<IDebugger>;

class CProcessor
{
	class IExecutor;
	struct SCommand;
	using t_commandType = UOpcode;
	static constexpr uint32 cui32AddressRegisterPoolSize = 8;
	static constexpr uint32 cui32GeneralPurposeRegistersSize = 32;

	friend class IExecutor;

public:
	CProcessor() = default;

	CProcessor(CProcessor const&) = delete;
	CProcessor(CProcessor &&) = delete;
	void operator=(CProcessor const&) = delete;
	void operator=(CProcessor &&) = delete;

public:
	bool IsRunning();
	void Run();
	void Stop();

private:
	bool m_bIsRunning = false;

public: // Debugger
	void AttachDebugger(IDebuggerPtr pDebugger);
	void DetachDebugger();

public:
	class CFlags
	{
	public:
		enum
		{
			eMask_CF = 0x0001,
			eMask_PF = 0x0002,
			eMask_ZF = 0x0004,
			eMask_SF = 0x0008,
			eMask_OF = 0x0010,
			eMask_TF = 0x0080,
		};

		CFlags();

		bool getTrap() const;
		bool getCarry() const;
		bool getParity() const;
		bool getZero() const;
		bool getSign() const;
		bool getOverflow() const;
		uint16 getFlags() const;

		void setTrap(bool);
		void setCarry(bool);
		void setParity(bool);
		void setZero(bool);
		void setSign(bool);
		void setOverflow(bool);
		void setFlags(uint16);

		bool IsEqual() const;
		bool IsNotEqual() const;
		bool IsAbove() const;
		bool IsAboveOrEqual() const;
		bool IsBelow() const;
		bool IsBelowOrEqual() const;
		bool IsGreat() const;
		bool IsGreatOrEqual() const;
		bool IsLow() const;
		bool IsLowOrEqual() const;
		bool IsOverflow() const;
		bool IsNotOverflow() const;
		bool IsSigned() const;
		bool IsNotSigned() const;
		bool IsParity() const;
		bool IsNotParity() const;

	private:
		uint16 m_ui16Value;
	};

public:

	struct SState
	{
		uint32 m_nPC;
		t_commandType m_nIR;

		uint32 m_nSP;
		uint32 m_nSF;

		CFlags m_fFlags;

		uint32 m_aui32AR[cui32AddressRegisterPoolSize];
		uint8 m_aui8GPR[cui32GeneralPurposeRegistersSize];

		bool m_bControlFlag = true;
	};

	SState const& getState() const;

	using FnCommand = void (IExecutor::*)(CProcessor::SState&, CProcessor::SCommand&);

	struct SCommand
	{
		FnCommand command;
		UOpcode op;
		QVarLengthArray<uint32, 3> argValue;
	};

	class IExecutor
	{
	public:
		IExecutor() = default;
		virtual ~IExecutor() = default;

		virtual void Invalid(SState& machineState, SCommand& comand) = 0;
		virtual void Nop(SState& machineState, SCommand& comand) = 0;
		virtual void End(SState& machineState, SCommand& comand) = 0;
		virtual void Break(SState& machineState, SCommand& comand) = 0;
		virtual void Int(SState& machineState, SCommand& comand) = 0;
		virtual void Jump(SState& machineState, SCommand& comand) = 0;
		virtual void Call(SState& machineState, SCommand& comand) = 0;
		virtual void Ret(SState& machineState, SCommand& comand) = 0;
		virtual void Iret(SState& machineState, SCommand& comand) = 0;
		virtual void Sti(SState& machineState, SCommand& comand) = 0;
		virtual void Cli(SState& machineState, SCommand& comand) = 0;
		virtual void Stc(SState& machineState, SCommand& comand) = 0;
		virtual void Clc(SState& machineState, SCommand& comand) = 0;
		virtual void Assign(SState& machineState, SCommand& comand) = 0;
		virtual void Move(SState& machineState, SCommand& comand) = 0;
		virtual void Swap(SState& machineState, SCommand& comand) = 0;
		virtual void Add(SState& machineState, SCommand& comand) = 0;
		virtual void Adc(SState& machineState, SCommand& comand) = 0;
		virtual void Sub(SState& machineState, SCommand& comand) = 0;
		virtual void Sbb(SState& machineState, SCommand& comand) = 0;
		virtual void Mul(SState& machineState, SCommand& comand) = 0;
		virtual void Imul(SState& machineState, SCommand& comand) = 0;
		virtual void Div(SState& machineState, SCommand& comand) = 0;
		virtual void Idiv(SState& machineState, SCommand& comand) = 0;
		virtual void Inc(SState& machineState, SCommand& comand) = 0;
		virtual void Dec(SState& machineState, SCommand& comand) = 0;
		virtual void Neg(SState& machineState, SCommand& comand) = 0;
		virtual void Cmp(SState& machineState, SCommand& comand) = 0;
		virtual void And(SState& machineState, SCommand& comand) = 0;
		virtual void Or(SState& machineState, SCommand& comand) = 0;
		virtual void Xor(SState& machineState, SCommand& comand) = 0;
		virtual void Nand(SState& machineState, SCommand& comand) = 0;
		virtual void Nor(SState& machineState, SCommand& comand) = 0;
		virtual void Not(SState& machineState, SCommand& comand) = 0;
		virtual void Shr(SState& machineState, SCommand& comand) = 0;
		virtual void Sar(SState& machineState, SCommand& comand) = 0;
		virtual void Shl(SState& machineState, SCommand& comand) = 0;
		virtual void Sal(SState& machineState, SCommand& comand) = 0;
		virtual void Ror(SState& machineState, SCommand& comand) = 0;
		virtual void Rcr(SState& machineState, SCommand& comand) = 0;
		virtual void Rol(SState& machineState, SCommand& comand) = 0;
		virtual void Rcl(SState& machineState, SCommand& comand) = 0;
		virtual void Test(SState& machineState, SCommand& comand) = 0;
		virtual void Load(SState& machineState, SCommand& comand) = 0;
		virtual void Store(SState& machineState, SCommand& comand) = 0;
		virtual void Push(SState& machineState, SCommand& comand) = 0;
		virtual void Pop(SState& machineState, SCommand& comand) = 0;
		virtual void Pushf(SState& machineState, SCommand& comand) = 0;
		virtual void Popf(SState& machineState, SCommand& comand) = 0;
		virtual void Pushsf(SState& machineState, SCommand& comand) = 0;
		virtual void Popsf(SState& machineState, SCommand& comand) = 0;
		virtual void In(SState& machineState, SCommand& comand) = 0;
		virtual void Out(SState& machineState, SCommand& comand) = 0;
	};
	using IExecutorPtr = std::shared_ptr<IExecutor>;

public:
	t_commandType fetch();
	SCommand decode(t_commandType&);
	void execute(SCommand);

public:
	void Init(CMemoryPtr memory, int PC);

	struct SCommandDefinition
	{
		SCommandDefinition(FnCommand fn);
		FnCommand pFnCommand;
	};

private:
	SCommand m_oCurrentCommandContext;

	CMemoryPtr m_pMemory; 
	IExecutorPtr m_pIExecutor;

	IDebuggerPtr m_pIDebugger;

	SState m_oState;


	static const std::unordered_map<EInstruction, CProcessor::SCommandDefinition> s_mapCommands;
};

using CProcessorPtr = std::shared_ptr<CProcessor>;

#endif // !PROCESSOR_H
