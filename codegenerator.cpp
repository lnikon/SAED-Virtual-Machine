#include "codegenerator.h"

CCodeGenerator::CCodeGenerator()
{
}

void CCodeGenerator::work(QVector<SDataToken> v_dt, QVector<SCodeToken> v_ct,
		QVector<int> symbolTable, QString filename)
{
	QFile file(filename);
	file.resize(0);
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream out(&file);

	QVector<QString> ds = generateData(v_dt);
	QVector<QString> cs = generateCode(v_dt, v_ct, symbolTable);

	QVector<QString> all = ds + cs;

	for (int i = 0; i < all.size(); ++i)
	{
		qDebug() << "all[" << i << "] = " << all[i];
		out << all[i];
		out << "\n";
	}


	//for (int i = 0; i < v_ct.size(); ++i)
	//{
	//	int count = v_ct[i].argValue.size();
	//	for (int j = 0; j < count; ++j)
	//	{
	//		qDebug() << "v_ct[i].argValue[j] = " << v_ct[i].argValue[j];
	//	}
	//	EType t = static_cast<EType>(v_ct[i].opcode.argSize);
	//	qDebug() << "static_cast<EType>(v_ct[i].opcode.argSize) = " << v_ct[i].opcode.argSize;
	//	
	//	qDebug() << "" << "v_ct[i].opcode.instr = " << v_ct[i].opcode.instr;
	//	qDebug() << "" << "v_ct[i].opcode.arg1Type = " << v_ct[i].opcode.arg1Type;
	//	qDebug() << "" << "v_ct[i].opcode.arg2Type = " << v_ct[i].opcode.arg2Type;
	//	qDebug() << "" << "v_ct[i].opcode.arg3Type = " << v_ct[i].opcode.arg3Type;
	//	qDebug() << "" << "v_ct[i].line = " << v_ct[i].line; 
	//	EInstruction ins = static_cast<EInstruction>(v_ct[i].opcode.instr);
	//	SInstructionParameters sParam (ins, count, t);
	//	qDebug() << "instruction = " << inst.key(sParam);
	//}
}

QVector<QString> CCodeGenerator::generateData(QVector<SDataToken> v_dt)
{
	QVector<QString> dataSection;

	for (int i = 0; i < v_dt.size(); ++i)
	{
		QString line;
		line.append(getType(v_dt[i].type));
		line.append(" ");
		line.append(v_dt[i].identifierName);
		line.append(" = ");
		QDataStream out(&v_dt[i].value, QIODevice::ReadOnly);
		int size = v_dt[i].value.size();
		if (size == 1)
		{
			qint8 val;
			out >> val;
			line.append(QString::number(val));
		}
		else if (size == 2)
		{
			int16 val;
			out >> val;
			line.append(QString::number(val));
		}
		else if (size == 4)
		{
			int32 val;
			out >> val;
			line.append(QString::number(val));
		}
		else if (size == 8)
		{
			int64 val;
			out >> val;
			line.append(QString::number(val));
		}
		qDebug() << "line = " << line;
		dataSection.append(line);
	}

	//for (int i = 0; i < dataSection.size(); ++i)
	//{
	//	qDebug() << dataSection[i];
	//}

	return dataSection;
}
QVector<QString> CCodeGenerator::generateCode(QVector<SDataToken> v_dt, QVector<SCodeToken> v_ct, QVector<int> symbolTable)
{
	QVector<QString> codeSection;

	for (int i = 0; i < v_ct.size(); ++i)
	{
		QString line;
		int count = v_ct[i].argValue.size();
		EInstruction ins = static_cast<EInstruction>(v_ct[i].opcode.instr);
		EType t = static_cast<EType>(v_ct[i].opcode.argSize);
		SInstructionParameters sParam(ins, count, t);

		line.append(inst.key(sParam));
		QVector<QString> args = getArguments(v_dt, v_ct[i], symbolTable);
		for (int j = 0; j < args.size(); ++j)
		{
			line.append(" ");
			line.append(args[j]);
		}
		qDebug() << "line = " << line;
		codeSection.append(line);
	
		/*qDebug() << "static_cast<EType>(v_ct[i].opcode.argSize) = " << v_ct[i].opcode.argSize;

		qDebug() << "" << "v_ct[i].opcode.instr = " << v_ct[i].opcode.instr;
		qDebug() << "" << "v_ct[i].opcode.arg1Type = " << v_ct[i].opcode.arg1Type;
		qDebug() << "" << "v_ct[i].opcode.arg2Type = " << v_ct[i].opcode.arg2Type;
		qDebug() << "" << "v_ct[i].opcode.arg3Type = " << v_ct[i].opcode.arg3Type;
		qDebug() << "" << "v_ct[i].line = " << v_ct[i].line; */
	}
	return codeSection;
}

QVector<QString> CCodeGenerator::getArguments(QVector<SDataToken> v_dt, SCodeToken ct, QVector<int> symbolTable)
{
	QVector<QString> args;

//	qDebug() << "ct.argValue.size() = " << ct.argValue.size();
	QString arg1;
	QString arg2;
	QString arg3;

//	qDebug() << "ct.opcode.opcode = " << ct.opcode.instr;


	for (int i = 0; i < ct.argValue.size(); ++i)
	{
		uint32 arg = ct.argValue[i];
		qDebug() << "ct.argValue[i] = " << ct.argValue[i];
		int type;
		if (i == 0)
		{
			type = ct.opcode.arg1Type;
		}
		else if (i == 1)
		{
			type = ct.opcode.arg2Type;
		}
		else if (i == 2)
		{
			type = ct.opcode.arg3Type;
		}
		if (type == static_cast<int>(EArgumentType::Register))
		{
			QString arg;
			arg.append("r");
			arg.append(QString::number(ct.argValue[i] - 9));
			args.append(arg);
			qDebug() << "arg = " << arg;
		}
		else if (type == static_cast<int>(EArgumentType::Constant))
		{
			QString arg;
			arg.append(QString::number(ct.argValue[i]));
			qDebug() << "arg = " << arg;
			args.append(arg);
		}
		else if (type == static_cast<int>(EArgumentType::Data))
		{
			int indexInExe = ct.argValue[i];
			int indexInSymbolTable = symbolTable.indexOf(indexInExe);
			QString arg = v_dt[indexInSymbolTable].identifierName;
			qDebug() << "arg = " << arg;
			args.append(arg);
		}
		else if (type == static_cast<int>(EArgumentType::None))
		{
		}
	}

	return args;
}
QString CCodeGenerator::getType(EType t)
{
	//	QString sType;
	if (t == EType::Byte)
	{
		return "byte";
	}
	else if (t == EType::Word)
	{
		return "word";
	}
	else if (t == EType::Dword)
	{
		return "dword";
	}
	else if (t == EType::Qword)
	{
		return "qword";
	}
	else
	{
		return "?";
	}
}











