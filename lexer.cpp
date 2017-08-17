#include "lexer.h"

Lexer::Lexer(QTextStream & in)
{
	State state = State::init;
	State n_state = State::init;
	QString buffer;
	line_ = 1;
	while (!in.atEnd())
	{
		QChar ch;
		in >> ch;

		if (ch == ';')
		{
			n_state = state;
			state = State::comment;
		}

		if (buffer == ".data")
		{
			state = State::data_type;
			buffer.clear();
		}
		else if (buffer == ".code")
		{
			state = State::code_command;
			buffer.clear();
		}
		else
		if (isDelimiter(ch))
		{
			if (buffer.isEmpty())
			{
				continue;
			}
			switch (state)
			{
				case State::init:
					break;
				case State::code_command:
					checkCommand(buffer);
					if (argCount_)
					{
						state = State::code_argument;
					}
					break;
				case State::code_argument:
					checkArgument(buffer);
					if (argCount_)
					{
						state = State::code_argument;
					}
					else
					{
						state = State::code_command;
					}
					break;
				case State::data_type:
					checkType(buffer);
					state = State::data_identifier;
					break;
				case State::data_identifier:
					checkIdentifier(buffer);
					state = State::data_value;
					break;
				case State::data_value:
					checkValue(buffer);
					state = State::data_type;
					break;
				case State::comment:
					if (ch == '\n')
					{
						state = n_state;
					}
					break;
			}
			buffer.clear();
		}
		else
		{
			buffer += ch;
		}
		if (ch == '\n')
		{
			++line_;
		}
	}

}

QVector<DataToken> Lexer::dataOut() const
{
	return data_tokens_;
}

QVector<CodeToken> Lexer::codeOut() const
{
	return code_tokens_;
}

bool Lexer::isDigit(const QString & token)
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

void Lexer::checkCommand(const QString & command)
{
	if (inst.contains(command))
	{
		code_tokens_.push_back(CodeToken(command, inst[command].argument_type, line_));
		argCount_ = inst[command].argument_count;
	}
}

void Lexer::checkArgument(const QString & argument)
{
	argCount_--;
	if (isRegister(argument))
	{
		code_tokens_.last().arg_type.push_back(ArgumentType::R);
		code_tokens_.last().arg_vlaue.push_back(argument);

	}
	else if (data_.contains(argument))
	{
		code_tokens_.last().arg_type.push_back(ArgumentType::C);
		code_tokens_.last().arg_vlaue.push_back(argument);
	}
	else if (isDigit(argument))
	{
		code_tokens_.last().arg_type.push_back(ArgumentType::C);
		code_tokens_.last().arg_vlaue.push_back(argument);
	}
}

void Lexer::checkIdentifier(const QString & identifier)
{
	//if (!isRegister(identifier))
	{
		data_tokens_.last().name = identifier;
	}
}

void Lexer::checkValue(const QString & value)
{
	if (isDigit(value))
	{
		switch (data_tokens_.last().size)
		{
			case Type::BYTE:
			{
				uint8 val = value.toInt();
				data_tokens_.last().value = val;
				break;
			}
			case Type::WORD:
				data_tokens_.last().value = value.toShort();
				break;
			case Type::DWORD:
				data_tokens_.last().value = value.toInt();
				break;
			case Type::QWORD:
				data_tokens_.last().value = value.toLongLong();
				break;
			default:;
		}
	}
}

bool Lexer::isRegister(const QString & token)
{
	if (!isDigit(token.right(token.size() - 1)))
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

void Lexer::checkType(const QString& type_string)
{
	if (HType.contains(type_string))
	{
		data_tokens_.push_back(DataToken(HType[type_string], line_));
	}
}

bool Lexer::isDelimiter(QChar ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',' || ch == '=' || ch == ';')
	{
		return true;
	}
	return false;
}
