#include "lexer.h"

void CLexer::work(QTextStream & in)
{
	EState state = EState::Init;
	EState n_state = EState::Init;
	QString buffer;
	m_line = 1;
	while (!in.atEnd())
	{
		QChar ch;
		in >> ch;
		if (ch == '\n')
		{
			++m_line;
		}

		if (ch == ';')
		{
			n_state = state;
			state = EState::Comment;
		}

		if (isDelimiter(ch))
		{
			if (buffer == ".code")
			{
				state = EState::CodeCommand;
				n_state = EState::CodeArgument;
				buffer.clear();
			}
			if (buffer.isEmpty())
			{
				continue;
			}
			switch (state)
			{
			case EState::Init:
				if (buffer == ".data")
				{
					state = EState::DataType;
					buffer.clear();
				}
				break;
			case EState::CodeCommand:
				checkCommand(buffer);
				if (m_argCount)
				{
					state = EState::CodeArgument;
				}
				break;
			case EState::CodeArgument:
				checkArgument(buffer);
				if (m_argCount)
				{
					state = EState::CodeArgument;
				}
				else
				{
					state = EState::CodeCommand;
				}
				break;
			case EState::DataType:
				checkType(buffer);
				//state = EState::Space;
				state = EState::DataIdentifier;
				break;
			case EState::DataIdentifier:
				checkIdentifier(buffer);
				state = EState::DataValue;
				break;
			case EState::DataValue:
				checkValue(buffer);
				state = EState::Init;
				break;
			case EState::Comment:
				if (ch == '\n')
				{
					state = n_state;
				}
				break;
			case EState::Space:

				break;
			case EState::Attribute: break;
			case EState::Comma: break;
			}
			buffer.clear();
		}
		else
		{
			buffer += ch;
		}
	}
}

QVector<SDataToken> CLexer::getData() const
{
	return m_dataTokens;
}

QVector<SCodeToken> CLexer::getCode() const
{
	return m_codeTokens;
}

bool CLexer::isDigit(const QString & token)
{
	for (int i = 0; i < token.size(); i++)
	{
		if (!token[i].isDigit())
		{
			return false;
		}
	}
	return true;
}

void CLexer::checkCommand(const QString & command)
{
	if (inst.contains(command))
	{
		m_codeTokens.push_back(SCodeToken(command, m_line));
		m_argCount = inst[command].argument_count;
		m_codeTokens.last().opcode.instr = static_cast<uint16>(inst[command].instr_code);
		m_codeTokens.last().opcode.argSize = static_cast<uint16>(inst[command].argument_type);
	}
	else
	{
		throw CError(command + " command on line " + QString::number(m_line) + " not found" );
	}
}

void CLexer::checkArgument(const QString & argument)
{
	m_argCount--;
	if (isRegister(argument))
	{
		m_codeTokens.last().opcode.arg1Type = static_cast<uint16>(EArgumentType::Register);
		m_codeTokens.last().argValue.push_back(getRegNumber(argument));

	}
	else if (m_data.contains(argument))
	{
		m_codeTokens.last().opcode.arg2Type = static_cast<uint16>(EArgumentType::Constant);
		m_codeTokens.last().argValue.push_back(argument.toInt());
	}
	else if (isDigit(argument))
	{
		m_codeTokens.last().opcode.arg3Type = static_cast<uint16>(EArgumentType::Constant);
		m_codeTokens.last().argValue.push_back(argument.toInt());
	}
	else
	{
		throw CError(argument + " on line " + QString::number(m_line) + " can't be used as argument");
	}
}

void CLexer::checkIdentifier(const QString & identifier)
{
	if (isRegister(identifier) || inst.contains(identifier) || HType.contains(identifier) || m_data.contains(identifier))
	{
		throw CError(identifier + " on line " + QString::number(m_line) + " can't be used as identifier");
	}
	
	m_dataTokens.last().identifierName = identifier;
}

 // isn't ready
void CLexer::checkValue(const QString & value)
{
	if (isDigit(value))
	{
		switch (m_dataTokens.last().type)
		{
		case EType::Byte:
		{
			uint8 val = value.toInt();
			m_dataTokens.last().value = val;
			break;
		}
		case EType::Word:
			m_dataTokens.last().value = value.toShort();
			break;
		case EType::Dword:
			m_dataTokens.last().value = value.toInt();
			break;
		case EType::Qword:
			m_dataTokens.last().value = value.toLongLong();
			break;
		default:;
		}
	}
	else
	{
		throw CError("not a number");
	}
}

bool CLexer::isRegister(const QString & token)
{
	if (!isDigit(token.right(token.size() - 1)))
	{
		return false;
	}

	if (token.size() <= 1)
	{
		return false;
	}

	int reg_num = token.right(token.size() - 1).toInt();

	if ((token[0] == 'r') && (reg_num >= 0 && reg_num <= 1023))
	{
		return true;
	}
	else if ((token[0] == 'a') && (reg_num >= 0 && reg_num <= 3))
	{
		return true;
	}

	return false;
}

void CLexer::checkType(const QString& type_string)
{
	if (HType.contains(type_string))
	{
		m_dataTokens.push_back(SDataToken(HType[type_string], m_line));
	}
	else
	{
		throw CError(type_string + " on line " + QString::number(m_line) + "can't be used as type");
	}
}

 uint32 CLexer::getRegNumber(const QString & token)
{
	 int reg_num = token.right(token.size() - 1).toInt();

	 if ((token[0] == 'r') && (reg_num >= 0 && reg_num <= 1023))
	 {
		 return reg_num + 9;
	 }
	 else if ((token[0] == 'a') && (reg_num >= 0 && reg_num <= 3))
	 {
		 return reg_num;
	 }
	 else if (token== "IP")
	 {
		 return 4;
	 }
	 else if (token == "TR")
	 {
		 return 5;
	 }
	 else if (token== "SP")
	 {
		 return 6;
	 }
	 else if (token == "SF")
	 {
		 return 7;
	 }
	 else if (token == "FLAGS")
	 {
		 return 8;
	 }
}

bool CLexer::isDelimiter(QChar ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',' || ch == '=' || ch == ';')
	{
		return true;
	}
	return false;
}
