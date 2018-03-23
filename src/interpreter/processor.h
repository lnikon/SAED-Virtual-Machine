#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "i_o_manager.h"
#include "../compiler/instructions.h"

#include <memory>
#include <map>

#include <QVarLengthArray>

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

public:
	struct SCommand
	{
		UOpcode op;
		QVarLengthArray<uint32, 3> argValue;
	};

	class IExecutor
	{
	public:
		IExecutor() = default;
		virtual ~IExecutor() = default;

		virtual void Invalid(SCommand& comand) = 0;
		virtual void Nop(SCommand& comand) = 0;
		virtual void Break(SCommand& comand) = 0;
		virtual void Int(SCommand& comand) = 0;
		virtual void Jump(SCommand& comand) = 0;
		virtual void Call(SCommand& comand) = 0;
		virtual void Ret(SCommand& comand) = 0;
		virtual void Iret(SCommand& comand) = 0;
		virtual void Sti(SCommand& comand) = 0;
		virtual void Cli(SCommand& comand) = 0;
		virtual void Stc(SCommand& comand) = 0;
		virtual void Clc(SCommand& comand) = 0;
		virtual void Assign(SCommand& comand) = 0;
		virtual void Move(SCommand& comand) = 0;
		virtual void Swap(SCommand& comand) = 0;
		virtual void Add(SCommand& comand) = 0;
		virtual void Adc(SCommand& comand) = 0;
		virtual void Sub(SCommand& comand) = 0;
		virtual void Sbb(SCommand& comand) = 0;
		virtual void Mul(SCommand& comand) = 0;
		virtual void Imul(SCommand& comand) = 0;
		virtual void Div(SCommand& comand) = 0;
		virtual void Idiv(SCommand& comand) = 0;
		virtual void Inc(SCommand& comand) = 0;
		virtual void Dec(SCommand& comand) = 0;
		virtual void Neg(SCommand& comand) = 0;
		virtual void Cmp(SCommand& comand) = 0;
		virtual void And(SCommand& comand) = 0;
		virtual void Or(SCommand& comand) = 0;
		virtual void Xor(SCommand& comand) = 0;
		virtual void Nand(SCommand& comand) = 0;
		virtual void Nor(SCommand& comand) = 0;
		virtual void Not(SCommand& comand) = 0;
		virtual void Shr(SCommand& comand) = 0;
		virtual void Sar(SCommand& comand) = 0;
		virtual void Shl(SCommand& comand) = 0;
		virtual void Sal(SCommand& comand) = 0;
		virtual void Ror(SCommand& comand) = 0;
		virtual void Rcr(SCommand& comand) = 0;
		virtual void Rol(SCommand& comand) = 0;
		virtual void Rcl(SCommand& comand) = 0;
		virtual void Test(SCommand& comand) = 0;
		virtual void Load(SCommand& comand) = 0;
		virtual void Store(SCommand& comand) = 0;
		virtual void Push(SCommand& comand) = 0;
		virtual void Pop(SCommand& comand) = 0;
		virtual void Pushf(SCommand& comand) = 0;
		virtual void Popf(SCommand& comand) = 0;
		virtual void Pushsf(SCommand& comand) = 0;
		virtual void Popsf(SCommand& comand) = 0;
		virtual void In(SCommand& comand) = 0;
		virtual void Out(SCommand& comand) = 0;
	};
	typedef void (IExecutor::* FnCommand)(SCommand&);

public:
	t_commandType fetch();
	SCommand decode(t_commandType&);
	void execute(SCommand);

public:
	void Init(CMemoryPtr memory, int PC);

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

		inline CFlags();

		inline bool getTrap() const;
		inline bool getCarry() const;
		inline bool getParity() const;
		inline bool getZero() const;
		inline bool getSign() const;
		inline bool getOverflow() const;
		inline uint16 getFlags() const;

		inline void setTrap(bool);
		inline void setCarry(bool);
		inline void setParity(bool);
		inline void setZero(bool);
		inline void setSign(bool);
		inline void setOverflow(bool);
		inline void setFlags(uint16);

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

private:
	t_commandType m_nIR;
	SCommand m_oCurrentCommandContext;
	
	uint32 m_nPC;

	uint32 m_nSP;
	uint32 m_nSF;

	CMemoryPtr m_pMemory;

	uint32 m_aui32AR[cui32AddressRegisterPoolSize];
	uint8 m_aui8GPR[cui32GeneralPurposeRegistersSize];

	bool m_bControlFlag = true;

	static const std::map<EInstruction, CProcessor::FnCommand> s_mapCommands;
};

using CProcessorPtr = std::shared_ptr<CProcessor>;

#endif // !PROCESSOR_H
