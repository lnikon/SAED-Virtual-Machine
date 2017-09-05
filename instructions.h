#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QHash>

using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;

class CError
{
public:
	explicit CError(QString e) : m_error(e)
	{
	}
	QString what() const 
	{
		return m_error;
	}
private:
	QString m_error;
};

union UOpcode
{
	UOpcode & operator=(const uint16 & val)
	{
		opcode = val;
		return *this;
	}
	uint16 opcode;
	struct
	{
		uint16 instr : 8;
		union
		{
			uint16 argType : 6;
			struct
			{
				uint16 arg1Type : 2;
				uint16 arg2Type : 2;
				uint16 arg3Type : 2;
			};
		};
		uint16 argSize : 2;
	};
};

enum class EArgumentType { Register = 1, AddresRegister, Constant };

enum class EType { Byte, Word, Dword, Qword };
//enum class EType { Byte = 1, Word = 2, Dword = 4, Qword = 8 };

const QHash<QString, EType> HType =
{
	{ "byte", EType::Byte }, { "word", EType::Word },
	{ "dword", EType::Dword }, { "qword", EType::Qword }
};

enum class EInstruction
{
	Nop = 1,
	Break,
	Int,
	Jump,
	Call,
	Ret,
	Iret,
	Sti,
	Cli,
	Stc,
	Clc,
	Assignb,
	Assignw,
	Assign,
	Assignq,
	Moveb,
	Movew,
	Move,
	Moveq,
	Swapb,
	Swapw,
	Swap,
	Swapq,
	Addb,
	Addw,
	Add,
	Addq,
	Adcb,
	Adcw,
	Adc,
	Adcq,
	Subb,
	Subw,
	Sub,
	Subq,
	Sbbb,
	Sbbw,
	Sbb,
	Sbbq,
	Mulb,
	Mulw,
	Mul,
	Mulq,
	Imulb,
	Imulw,
	Imul,
	Imulq,
	Divb,
	Divw,
	Div,
	Divq,
	Idivb,
	Idivw,
	Idiv,
	Idivq,
	Incb,
	Incw,
	Inc,
	Incq,
	Decb,
	Decw,
	Dec,
	Decq,
	Negb,
	Negw,
	Neg,
	Negq,
	Cmpb,
	Cmpw,
	Cmp,
	Cmpq,
	Andb,
	Andw,
	And,
	Andq,
	Orb,
	Orw,
	Or,
	Orq,
	Xorb,
	Xorw,
	Xor,
	Xorq,
	Nandb,
	Nandw,
	Nand,
	Nandq,
	Norb,
	Norw,
	Nor,
	Norq,
	Notb,
	Notw,
	Not,
	Notq,
	Shrb,
	Shrw,
	Shr,
	Shrq,
	Sarb,
	Sarw,
	Sar,
	Sarq,
	Shlb,
	Shlw,
	Shl,
	Shlq,
	Salb,
	Salw,
	Sal,
	Salq,
	Rorb,
	Rorw,
	Ror,
	Rorq,
	Rcrb,
	Rcrw,
	Rcr,
	Rcrq,
	Rolb,
	Rolw,
	Rol,
	Rolq,
	Rclb,
	Rclw,
	Rcl,
	Rclq,
	Testb,
	Testw,
	Test,
	Testq,
	Loadb,
	Loadw,
	Load,
	Loadq,
	Storeb,
	Storew,
	Store,
	Storeq,
	Pushb,
	Pushw,
	Push,
	Pushq,
	Popb,
	Popw,
	Pop,
	Popq,
	Pushf,
	Popf,
	Pushsf,
	Popsf,
	Inb,
	Inw,
	In,
	Inq,
	Outb,
	Outw,
	Out,
	Outq,
};

struct SInstructionParameters
{
	SInstructionParameters() {}
	SInstructionParameters(EInstruction i, int32 a, EType t) :
		instr_code(i), argument_count(a), argument_type(t)
	{
	}

	EInstruction instr_code;
	int32 argument_count;
	EType argument_type;
};

const QHash<QString, SInstructionParameters> inst =
{
	{ "nop", SInstructionParameters(EInstruction::Nop, 0, EType::Dword) },
	{ "break", SInstructionParameters(EInstruction::Break, 1, EType::Dword) },
	{ "int", SInstructionParameters(EInstruction::Int, 1, EType::Dword) },
	{ "jump", SInstructionParameters(EInstruction::Jump, 1, EType::Dword) },
	{ "call", SInstructionParameters(EInstruction::Call, 1, EType::Dword) },
	{ "ret", SInstructionParameters(EInstruction::Ret, 0, EType::Dword) },
	{ "iret", SInstructionParameters(EInstruction::Iret, 0, EType::Dword) },
	{ "sti", SInstructionParameters(EInstruction::Sti, 1, EType::Dword) },
	{ "cli", SInstructionParameters(EInstruction::Cli, 1, EType::Dword) },
	{ "stc", SInstructionParameters(EInstruction::Stc, 1, EType::Dword) },
	{ "clc", SInstructionParameters(EInstruction::Clc, 1, EType::Dword) },
	{ "assignb", SInstructionParameters(EInstruction::Assignb, 2, EType::Byte) },
	{ "assignw", SInstructionParameters(EInstruction::Assignw, 2, EType::Word) },
	{ "assign", SInstructionParameters(EInstruction::Assign, 2, EType::Dword) },
	{ "assignq", SInstructionParameters(EInstruction::Assignq, 2, EType::Qword) },
	{ "moveb", SInstructionParameters(EInstruction::Moveb, 2, EType::Byte) },
	{ "movew", SInstructionParameters(EInstruction::Movew, 2, EType::Word) },
	{ "move", SInstructionParameters(EInstruction::Move, 2, EType::Dword) },
	{ "moveq", SInstructionParameters(EInstruction::Moveq, 2, EType::Qword) },
	{ "swapb", SInstructionParameters(EInstruction::Swapb, 2, EType::Byte) },
	{ "swapw", SInstructionParameters(EInstruction::Swapw, 2, EType::Word) },
	{ "swap", SInstructionParameters(EInstruction::Swap, 2, EType::Dword) },
	{ "swapq", SInstructionParameters(EInstruction::Swapq, 2, EType::Qword) },
	{ "addb", SInstructionParameters(EInstruction::Addb, 3, EType::Byte) },
	{ "addw", SInstructionParameters(EInstruction::Addw, 3, EType::Word) },
	{ "add", SInstructionParameters(EInstruction::Add, 3, EType::Dword) },
	{ "addq", SInstructionParameters(EInstruction::Addq, 3, EType::Qword) },
	{ "adcb", SInstructionParameters(EInstruction::Adcb, 3, EType::Byte) },
	{ "adcw", SInstructionParameters(EInstruction::Adcw, 3, EType::Word) },
	{ "adc", SInstructionParameters(EInstruction::Adc, 3, EType::Dword) },
	{ "adcq", SInstructionParameters(EInstruction::Adcq, 3, EType::Qword) },
	{ "subb", SInstructionParameters(EInstruction::Subb, 3, EType::Byte) },
	{ "subw", SInstructionParameters(EInstruction::Subw, 3, EType::Word) },
	{ "sub", SInstructionParameters(EInstruction::Sub, 3, EType::Dword) },
	{ "subq", SInstructionParameters(EInstruction::Subq, 3, EType::Qword) },
	{ "sbbb", SInstructionParameters(EInstruction::Sbbb, 3, EType::Byte) },
	{ "sbbw", SInstructionParameters(EInstruction::Sbbw, 3, EType::Word) },
	{ "sbb", SInstructionParameters(EInstruction::Sbb, 3, EType::Dword) },
	{ "sbbq", SInstructionParameters(EInstruction::Sbbq, 3, EType::Qword) },
	{ "mulb", SInstructionParameters(EInstruction::Mulb, 3, EType::Byte) },
	{ "mulw", SInstructionParameters(EInstruction::Mulw, 3, EType::Word) },
	{ "mul", SInstructionParameters(EInstruction::Mul, 3, EType::Dword) },
	{ "mulq", SInstructionParameters(EInstruction::Mulq, 3, EType::Qword) },
	{ "imulb", SInstructionParameters(EInstruction::Imulb, 3, EType::Byte) },
	{ "imulw", SInstructionParameters(EInstruction::Imulw, 3, EType::Word) },
	{ "imul", SInstructionParameters(EInstruction::Imul, 3, EType::Dword) },
	{ "imulq", SInstructionParameters(EInstruction::Imulq, 3, EType::Qword) },
	{ "divb", SInstructionParameters(EInstruction::Divb, 3, EType::Byte) },
	{ "divw", SInstructionParameters(EInstruction::Divw, 3, EType::Word) },
	{ "div", SInstructionParameters(EInstruction::Div, 3, EType::Dword) },
	{ "divq", SInstructionParameters(EInstruction::Divq, 3, EType::Qword) },
	{ "idivb", SInstructionParameters(EInstruction::Idivb, 3, EType::Byte) },
	{ "idivw", SInstructionParameters(EInstruction::Idivw, 3, EType::Word) },
	{ "idiv", SInstructionParameters(EInstruction::Idiv, 3, EType::Dword) },
	{ "idivq", SInstructionParameters(EInstruction::Idivq, 3, EType::Qword) },
	{ "incb", SInstructionParameters(EInstruction::Incb, 1, EType::Byte) },
	{ "incw", SInstructionParameters(EInstruction::Incw, 1, EType::Word) },
	{ "inc", SInstructionParameters(EInstruction::Inc, 1, EType::Dword) },
	{ "incq", SInstructionParameters(EInstruction::Incq, 1, EType::Qword) },
	{ "decb", SInstructionParameters(EInstruction::Decb, 1, EType::Byte) },
	{ "decw", SInstructionParameters(EInstruction::Decw, 1, EType::Word) },
	{ "dec", SInstructionParameters(EInstruction::Dec, 1, EType::Dword) },
	{ "decq", SInstructionParameters(EInstruction::Decq, 1, EType::Qword) },
	{ "negb", SInstructionParameters(EInstruction::Negb, 1, EType::Byte) },
	{ "negw", SInstructionParameters(EInstruction::Negw, 1, EType::Word) },
	{ "neg", SInstructionParameters(EInstruction::Neg, 1, EType::Dword) },
	{ "negq", SInstructionParameters(EInstruction::Negq, 1, EType::Qword) },
	{ "cmpb", SInstructionParameters(EInstruction::Cmpb, 2, EType::Byte) },
	{ "cmpw", SInstructionParameters(EInstruction::Cmpw, 2, EType::Word) },
	{ "cmp", SInstructionParameters(EInstruction::Cmp, 2, EType::Dword) },
	{ "cmpq", SInstructionParameters(EInstruction::Cmpq, 2, EType::Qword) },
	{ "andb", SInstructionParameters(EInstruction::Andb, 3, EType::Byte) },
	{ "andw", SInstructionParameters(EInstruction::Andw, 3, EType::Word) },
	{ "and", SInstructionParameters(EInstruction::And, 3, EType::Dword) },
	{ "andq", SInstructionParameters(EInstruction::Andq, 3, EType::Qword) },
	{ "orb", SInstructionParameters(EInstruction::Orb, 3, EType::Dword) },
	{ "orw", SInstructionParameters(EInstruction::Orw, 3, EType::Word) },
	{ "or", SInstructionParameters(EInstruction::Or, 3, EType::Dword) },
	{ "orq", SInstructionParameters(EInstruction::Orq, 3, EType::Qword) },
	{ "xorb", SInstructionParameters(EInstruction::Xorb, 3, EType::Byte) },
	{ "xorw", SInstructionParameters(EInstruction::Xorw, 3, EType::Word) },
	{ "xor", SInstructionParameters(EInstruction::Xor, 3, EType::Dword) },
	{ "xorq", SInstructionParameters(EInstruction::Xorq, 3, EType::Qword) },
	{ "nandb", SInstructionParameters(EInstruction::Nandb, 3, EType::Byte) },
	{ "nandw", SInstructionParameters(EInstruction::Nandw, 3, EType::Word) },
	{ "nand", SInstructionParameters(EInstruction::Nand, 3, EType::Dword) },
	{ "nandq", SInstructionParameters(EInstruction::Nandq, 3, EType::Qword) },
	{ "norb", SInstructionParameters(EInstruction::Norb, 3, EType::Byte) },
	{ "norw", SInstructionParameters(EInstruction::Norw, 3, EType::Word) },
	{ "nor", SInstructionParameters(EInstruction::Nor, 3, EType::Dword) },
	{ "norq", SInstructionParameters(EInstruction::Norq, 3, EType::Qword) },
	{ "notb", SInstructionParameters(EInstruction::Notb, 1, EType::Byte) },
	{ "notw", SInstructionParameters(EInstruction::Notw, 1, EType::Word) },
	{ "not", SInstructionParameters(EInstruction::Not, 1, EType::Dword) },
	{ "notq", SInstructionParameters(EInstruction::Notq, 1, EType::Qword) },
	{ "shrb", SInstructionParameters(EInstruction::Shrb, 2, EType::Byte) },
	{ "shrw", SInstructionParameters(EInstruction::Shrw, 2, EType::Word) },
	{ "shr", SInstructionParameters(EInstruction::Shr, 2, EType::Dword) },
	{ "shrq", SInstructionParameters(EInstruction::Shrq, 2, EType::Qword) },
	{ "sarb", SInstructionParameters(EInstruction::Sarb, 2, EType::Byte) },
	{ "sarw", SInstructionParameters(EInstruction::Sarw, 2, EType::Word) },
	{ "sar", SInstructionParameters(EInstruction::Sar, 2, EType::Dword) },
	{ "sarq", SInstructionParameters(EInstruction::Sarq, 2, EType::Qword) },
	{ "shlb", SInstructionParameters(EInstruction::Shlb, 2, EType::Byte) },
	{ "shlw", SInstructionParameters(EInstruction::Shlw, 2, EType::Word) },
	{ "shl", SInstructionParameters(EInstruction::Shl, 2, EType::Dword) },
	{ "shlq", SInstructionParameters(EInstruction::Shlq, 2, EType::Qword) },
	{ "salb", SInstructionParameters(EInstruction::Salb, 2, EType::Byte) },
	{ "salw", SInstructionParameters(EInstruction::Salw, 2, EType::Word) },
	{ "sal", SInstructionParameters(EInstruction::Sal, 2, EType::Dword) },
	{ "salq", SInstructionParameters(EInstruction::Salq, 2, EType::Qword) },
	{ "rorb", SInstructionParameters(EInstruction::Rorb, 2, EType::Byte) },
	{ "rorw", SInstructionParameters(EInstruction::Rorw, 2, EType::Word) },
	{ "ror", SInstructionParameters(EInstruction::Ror, 2, EType::Dword) },
	{ "rorq", SInstructionParameters(EInstruction::Rorq, 2, EType::Qword) },
	{ "rcrb", SInstructionParameters(EInstruction::Rcrb, 2, EType::Byte) },
	{ "rcrw", SInstructionParameters(EInstruction::Rcrw, 2, EType::Word) },
	{ "rcr", SInstructionParameters(EInstruction::Rcr, 2, EType::Dword) },
	{ "rcrq", SInstructionParameters(EInstruction::Rcrq, 2, EType::Qword) },
	{ "rolb", SInstructionParameters(EInstruction::Rolb, 2, EType::Byte) },
	{ "rolw", SInstructionParameters(EInstruction::Rolw, 2, EType::Word) },
	{ "rol", SInstructionParameters(EInstruction::Rol, 2, EType::Dword) },
	{ "rolq", SInstructionParameters(EInstruction::Rolq, 2, EType::Qword) },
	{ "rclb", SInstructionParameters(EInstruction::Rclb, 2, EType::Byte) },
	{ "rclw", SInstructionParameters(EInstruction::Rclw, 2, EType::Word) },
	{ "rcl", SInstructionParameters(EInstruction::Rcl, 2, EType::Dword) },
	{ "rclq", SInstructionParameters(EInstruction::Rclq, 2, EType::Qword) },
	{ "testb", SInstructionParameters(EInstruction::Testb, 2, EType::Byte) },
	{ "testw", SInstructionParameters(EInstruction::Testw, 2, EType::Word) },
	{ "test", SInstructionParameters(EInstruction::Test, 2, EType::Dword) },
	{ "testq", SInstructionParameters(EInstruction::Testq, 2, EType::Qword) },
	{ "loadb", SInstructionParameters(EInstruction::Loadb, 2, EType::Byte) },
	{ "loadw", SInstructionParameters(EInstruction::Loadw, 2, EType::Word) },
	{ "load", SInstructionParameters(EInstruction::Load, 2, EType::Dword) },
	{ "loadq", SInstructionParameters(EInstruction::Loadq, 2, EType::Qword) },
	{ "storeb", SInstructionParameters(EInstruction::Storeb, 2, EType::Byte) },
	{ "storew", SInstructionParameters(EInstruction::Storew, 2, EType::Word) },
	{ "store", SInstructionParameters(EInstruction::Store, 2, EType::Dword) },
	{ "storeq", SInstructionParameters(EInstruction::Storeq, 2, EType::Qword) },
	{ "pushb", SInstructionParameters(EInstruction::Pushb, 1, EType::Byte) },
	{ "pushw", SInstructionParameters(EInstruction::Pushw, 1, EType::Word) },
	{ "push", SInstructionParameters(EInstruction::Push, 1, EType::Dword) },
	{ "pushq", SInstructionParameters(EInstruction::Pushq, 1, EType::Qword) },
	{ "popb", SInstructionParameters(EInstruction::Popb, 1, EType::Byte) },
	{ "popw", SInstructionParameters(EInstruction::Popw, 1, EType::Word) },
	{ "pop", SInstructionParameters(EInstruction::Pop, 1, EType::Dword) },
	{ "popq", SInstructionParameters(EInstruction::Popq, 1, EType::Qword) },
	{ "pushf", SInstructionParameters(EInstruction::Pushf, 0, EType::Dword) },
	{ "popf", SInstructionParameters(EInstruction::Popf, 0, EType::Dword) },
	{ "pushsf", SInstructionParameters(EInstruction::Pushsf, 0, EType::Dword) },
	{ "popsf", SInstructionParameters(EInstruction::Popsf, 0, EType::Dword) },
	{ "inb", SInstructionParameters(EInstruction::Inb, 2, EType::Dword) },
	{ "inw", SInstructionParameters(EInstruction::Inw, 2, EType::Word) },
	{ "in", SInstructionParameters(EInstruction::In, 2, EType::Dword) },
	{ "inq", SInstructionParameters(EInstruction::Inq, 2, EType::Qword) },
	{ "outb", SInstructionParameters(EInstruction::Outb, 2, EType::Byte) },
	{ "outw", SInstructionParameters(EInstruction::Outw, 2, EType::Word) },
	{ "out", SInstructionParameters(EInstruction::Out, 2, EType::Dword) },
	{ "outq", SInstructionParameters(EInstruction::Outq, 2, EType::Qword) },
};

#endif // !INSTRUCTIONS_H
