#include"myLexer.h"

void SDataToken::set(QString& name, uint s, uint l)
{
	QString tempName;
	for (auto i : name)
	{
		if (i != '[')
			tempName += i;
		else
			break;
	}
	dataName = tempName;
	size = s;
	value.reserve(size);
	line = l;
}

void myLexer::start(QTextStream& in)
{
	State state = State::initial;
	State nextState;
	State prevState;
	char c;
	QString buffer;

	while (!in.atEnd())
	{
		in >> c;

		if (isDelimiter(c))
		{
			if (!buffer.isEmpty())
			{
				switch (state)
				{
					// ==============================================================
				case myLexer::State::initial:
					if (buffer == ".data")
					{
						state = State::dataType;
					}
					else
					{
						if (buffer == ".code")
						{
							state = State::codeInst;
						}
						else
						{
							throw Error("unknown command: ", buffer, line);
						}
					}
					break;
					// ==============================================================
				case myLexer::State::dataType:
					if (HTypeTable.contains(buffer))
					{
						m_dataToken.push_back(SDataToken(buffer, line));
						state = State::dataName;
					}
					else
					{
						if (buffer == ".code")
						{
							state = State::codeInst;
						}
						else
						{
							throw Error("unknown type: ", buffer, line);
						}
					}
					break;
					// =====================================================================================================
				case myLexer::State::dataName:
				{
					int check = checkDataName(buffer);
					QString tempName = makeName(buffer);
					if (isVariable(buffer)) throw Error("variable name already initialized: ", tempName, line);
					switch (check)
					{
						// if name started by number, or name is contain only number
					case 0: throw Error("wrong name of value: ", buffer, line); break;
						// single value, not an array (don't contain '[' and ']')
					case 1:
						m_dataToken.last().set(buffer, 1, line); // array, that have only one value
						prevState = state;
						state = State::dataEqual;
						nextState = State::dataValue;
						break;
						// array without size, ex. "name[]"
					case 2:
						m_dataToken.last().set(buffer, 0, line); // '0' for make difference between array with and without size
						prevState = state;
						state = State::dataEqual;
						nextState = State::dataArray;
						break;
						// array with size
					default:
						m_dataToken.last().set(buffer, check - 3, line);
						prevState = state;
						state = State::dataEqual;
						nextState = State::dataArray;
						break;
					}
					break;
				}
				// =====================================================================================================
				case myLexer::State::dataEqual: // symbol '='
					if (buffer != '=')
					{
						if (m_dataToken.last().size == 0)
							throw Error("the variable has not size: ", m_dataToken.last().dataName, line);
						if (HTypeTable.contains(buffer)) // if the buffer is the type name
						{
							m_dataToken.push_back(SDataToken(buffer, line));
							state = State::dataName;
							if (nextState == State::dataValue)
							{
								buffer = "0";
								setNumber(buffer); // default initiation
							}
						}
						else if (buffer == ".code") {
							state = State::codeInst;
						}
						else
							throw Error("wrong syntax: ", buffer, line);
					}
					else
					{
						state = nextState;
					}
					break;
					// =====================================================================================================
				case myLexer::State::dataValue:
					setNumber(buffer);
					state = State::dataType;
					break;
					// =====================================================================================================
				case myLexer::State::dataArray:
					if (m_dataToken.last().size == 0 || m_dataToken.last().size > m_dataToken.last().value.size())
					{
						setNumber(buffer);
					}
					else
					{
						throw Error("segmentation fault: too more arguments for: ", m_dataToken.last().dataName, line);
					}
					break;
					// =====================================================================================================
				case myLexer::State::codeInst:
					if (!HInstTable.contains(buffer))
					{
						throw Error("undefined instruction: ", buffer, line);
					}
					m_codeToken.push_back(SCodeToken(buffer, line));
					state = State::codeArgument;
					break;
					// =====================================================================================================
				case myLexer::State::codeArgument:

					if (m_codeToken.last().argName.size() < 3) {
						if (checkSymbols(buffer))
						{
							throw Error("wrong syntax of name: ", buffer, line);
						}
						else if (isRegister(buffer))
						{
							m_codeToken.last().argName.push_back(qMakePair(buffer, EArgumentType::Register));
						}
						else if (isNumber(buffer))
						{
							m_codeToken.last().argName.push_back(qMakePair(buffer, EArgumentType::Constant));
						}
						else if (isVariable(buffer))
						{
							m_codeToken.last().argName.push_back(qMakePair(buffer, EArgumentType::Data));
						}
						else
						{
							throw Error("undefined variable: ", buffer, line);
						}
					}
					else
					{
						throw Error("segmentation fault: too more arguments for: ", m_codeToken.last().instName, line);
					}

					break;
					// =====================================================================================================
				case myLexer::State::comment:
					if (c == '\n')
					{
						state = nextState;
					}
					break;
				}
				buffer.clear();
			}
			if (c == ';')
			{
				nextState = state;
				state = State::comment;
				buffer = "comment";
			}
			if (c == '\n')
			{
				++line;
				if (state == State::dataArray)
				{
					state = State::dataType;
					if (m_dataToken.last().size == 0)
					{
						m_dataToken.last().size = m_dataToken.last().value.size();
					}
				}
				if (state == State::codeArgument)
				{
					state = State::codeInst;
				}
			}
		}
		else
		{
			buffer += c;
		}
	}

}

bool myLexer::isDelimiter(char c)
{
	return (c == ' ' || c == ',' || c == '\n' || c == '\t' || c == ';');
}

int myLexer::checkDataName(QString& buffer)
{
	if (buffer[0].isDigit()) return 0; // name can't start with number	
	int count = 0; // count '[' and ']'
	for (int i(0); i < buffer.size(); ++i) { // check symphols
		if (!buffer[i].isDigit() && !buffer[0].isLetter() && buffer[i] != '[' && buffer[i] != ']')
			return 0;
		else if (buffer[i] == '[') ++count;
		else if (buffer[i] == ']') --count;
	}
	if (count != 0) return 0; // when count of symbol '[' and count of symbol ']' is not equal
	QString name = makeName(buffer);
	if (name == buffer) return 1; // name is single array, without size
	if (buffer[buffer.size() - 1] != ']') return 0; // last symbol is not ']'
	if (buffer.size() - name.size() == 2) return 2; // array witout size, ex. name[]
	QString value; // for save value between '[' and ']' symbols	
	for (int i(name.size()); i < buffer.size() - 1; ++i) value += buffer[i];	
	if (!isNumber(value)) return 0;
	return value.toInt() + 3; // when array has a size 
}

//int myLexer::checkDataName(QString& buffer)
//{
//	if (buffer[0].isDigit()) return 0; // name can't start with number
//	for (int i(0); i < buffer.size(); ++i)
//		if (buffer[i].isDigit() || buffer[i] == '[')
//			return 0; // wrong name
//		else
//			break;
//
//	if (buffer[buffer.size() - 1] == ']')
//	{
//		for (int i(0); i < buffer.size() - 1; ++i)
//		{
//			if (buffer[i] == '[')
//			{
//				if (buffer.size() - i == 2)
//				{
//					return 2; // array without size
//				}
//				else
//				{
//					QString number;
//					for (int j = i + 1; j < buffer.size() - 1; ++j)
//						number += buffer[j];
//					for (int j(0); j < number.size(); ++j)
//						if (!number[j].isDigit())
//							return 0; // worng name
//					return number.toInt() + 3; // array with size
//				}
//			}
//		}
//	}
//	return 1; // siple name, array with one value, size = 1
//}

void myLexer::setNumber(QString& buffer)
{
	for (int i(0); i < buffer.size(); ++i)
		if (!buffer[i].isDigit())
			throw Error("value is not a number: ", buffer, line);
	switch (m_dataToken.last().type)
	{
	case EDataType::Byte:
		m_dataToken.last().value.push_back(buffer.toShort()); // ? there is not type equal 8 bit
		break;
	case EDataType::Word:
		m_dataToken.last().value.push_back(buffer.toShort());
		break;
	case EDataType::Dword:
		m_dataToken.last().value.push_back(buffer.toInt());
		break;
	case EDataType::Qword:
		m_dataToken.last().value.push_back(buffer.toLongLong());
		break;
	}
}

QString myLexer::makeName(QString& buffer)
{
	QString name;
	for (auto i : buffer)
	{
		if (i != '[')
			name += i;
		else
			break;
	}
	return name;
}

bool myLexer::isRegister(QString& buffer)
{
	if (buffer[0] != 'R' || buffer[1] != '[' || buffer[buffer.size() - 1] != ']' || buffer.size() < 4) return false;
	QString argument; 
	for (int i(2); i < buffer.size() - 1; ++i)
		argument += buffer[i];
	if (isNumber(argument)) return true;
	else if (isVariable(argument)) return true;
	else if (isRegister(argument)) return true;
	return false;
}
bool myLexer::isNumber(QString& buffer)
{
	for (int i(0); i < buffer.size(); ++i)
		if (!buffer[i].isDigit())
			return false;
	return true;
}
bool myLexer::isVariable(QString& buffer)
{
	QString name = makeName(buffer);
	if (name == buffer) { 
		for (int i(0); i < m_dataToken.size(); ++i)
			if (m_dataToken[i].dataName == name)
				return true; // single name
	}
	else
	{
		if (buffer[buffer.size() - 1] != ']') return false; // last symbol is not ']'
		if (buffer.size() - name.size() == 2) return false; // array witout size, ex. name[]
		for (int i(0); i < m_dataToken.size(); ++i)
			if (m_dataToken[i].dataName == name) {
				QString value; // for save value between '[' and ']' symbols	
				for (int i(name.size() + 1); i < buffer.size() - 1; ++i)
					value += buffer[i];
				if (isVariable(value)) return true;
				else if (isRegister(value)) return true;
				else if (isNumber(value)) return true;
			}
		return false;
	}
	
}

bool myLexer::checkSymbols(QString& buffer)
{
	int count = 0; // count '[' and ']'
	for (int i(0); i < buffer.size(); ++i) { // check symphols
		if (!buffer[i].isDigit() && !buffer[0].isLetter() && buffer[i] != '[' && buffer[i] != ']')
			return 0; 
		else if (buffer[i] == '[') ++count;
		else if (buffer[i] == ']') --count;
	}
	return count != 0; // false when count of symbol '[' and count of symbol ']' is not equal
}
