#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H


class CCodeGenerator
{
public:
	CCodeGenerator();
	void work(QVector<SDataToken>dataTokens, QVector<SCodeToken>codeTokens, QVector<QString> sDataNames, QString sFileTxt);
private:

};




#endif