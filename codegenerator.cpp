#include "codegenerator.h"

void CCodeGenerator::work(QVector<SDataToken>dataTokens, QVector<SCodeToken>codeTokens, QHash<QString, int32> dataNames, QString sFileTxt)
{	
	QFile file(sFileTxt);
	file.resize(0);
	file.open(QIODevice::ReadWrite | QIODevice::Append);
	QTextStream out(&file);

	m_dataTokens = dataTokens;
	m_codeTokens = codeTokens;
	writeDataSection(out);
	writeCodeSection(out);
	file.close();
}

void CCodeGenerator::writeDataSection(QTextStream& out)
{
	for (int i = 0; i < m_dataTokens.size(); ++i)
	{
		out << getDataType(m_dataTokens[i].type);
		out << m_dataTokens[i].identifierName;
		out << static_cast<QString>( m_dataTokens[i].value);
	}
}
QString CCodeGenerator::getDataType(EType t)
{
	if (t == EType::Byte)
		return "byte";
	else if (t == EType::Word)
		return "word";
	else if (t == EType::Dword)
		return "dword";
	else 
		return "qword";
}
void CCodeGenerator::writeCodeSection(QTextStream& out)
{
	for (int i = 0; i < m_codeTokens.size(); ++i)
	{
		QString sOpcode = getOpcode(m_codeTokens[i].opcode);
		out << sOpcode;
//		int32 argCount = getArgumentCount(sOpcode);
		
		QVarLengthArray<uint32, 3> arr = m_codeTokens[i].argValue;
		int32 argCount = getArgumentCount(sOpcode);
		for (int j = 0; j < argCount; ++j)
		{
			QVector<QString> args = getArgumentNames(m_codeTokens[i].opcode, arr);
			out << " " << args[0] << " " << args[1] << " "<< args[2] << '\n';
		}

	}
}

QVector<QString> CCodeGenerator::getArgumentNames(UOpcode opc, QVarLengthArray<uint32, 3> arr)
{
	EArgumentType a1type = static_cast<EArgumentType>(opc.arg1Type);
	EArgumentType a2type = static_cast<EArgumentType>(opc.arg2Type);
	EArgumentType a3type = static_cast<EArgumentType>(opc.arg3Type);

	QVector<QString> args;
	args.push_back(getArgumentName(a1type, arr[0]));
	args.push_back(getArgumentName(a2type, arr[1]));
	args.push_back(getArgumentName(a2type, arr[2]));
	return args;
}

QString CCodeGenerator::getArgumentName(EArgumentType type, uint32 arg)
{
	QString strArg;
	if (type == EArgumentType::Register)
	{
		strArg.append("R");
		strArg += QString::number(arg);
	}
	else if (type == EArgumentType::Constant)
	{
		strArg += QString::number(arg);
	}
	else if (type == EArgumentType::Data)
	{
		strArg += m_symbolTable.key(arg);
	}
	else 
	{
		strArg = "";
	}
	return strArg;
}


QString CCodeGenerator::getOpcode(UOpcode opc)
{
	int32 instruction = opc.instr;
	int32 argType = opc.argSize;

	QString sInstruction;
	QHash<QString, SInstructionParameters>::const_iterator it = inst.begin();
	for (; it != inst.end(); ++it)
	{
		if ((static_cast<EInstruction>(instruction) == it->instrCode) && (static_cast<EType>(argType) == it->argumentType))
		{
			sInstruction = it.key();
			break;
		}
	}
	return sInstruction;
}

int32 CCodeGenerator::getArgumentCount(QString instruction)
{
	return inst[instruction].argumentCount;
}





