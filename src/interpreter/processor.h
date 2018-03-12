#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "i_o_manager.h"
#include "../compiler/instructions.h"

class CProcessor
{

	static constexpr uint32 cui32AddressRegisterPoolSize = 8;
	static constexpr uint32 cui32GeneralPurposeRegistersSize = 32;
	
public:

	bool IsRunning() {}
	void Run() {}
	void Stop() {}
	void Init(CMemory* memory, int PC, CIOManager* IOMan) {}

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
	uint32 m_nPC;

	uint32 m_aui32AR[cui32AddressRegisterPoolSize];
	uint8 maui8GPR[cui32GeneralPurposeRegistersSize];
};

#endif // !PROCESSOR_H
