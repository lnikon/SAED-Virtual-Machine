#include <QtCore/QCoreApplication>
#include"rw.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//=====[ How to write ]=====
	//
	//   1) add sections
	//   2) write in file
	//
	//==========================


	// some data sections
	QByteArray data = "data-data-data data data";
	QByteArray code = "code-code-code code";
	QByteArray codeSymbol = "some code symbol";

	CRW writer; // create object to write
	// add data section to write
	writer.addSection(ESectionType::Code, code);
	writer.addSection(ESectionType::Data, data);
	writer.addSection(ESectionType::CodeSymbol, codeSymbol);

	writer.write("a.out"); // write sections
	
   //=====[ How to read ]=====
   //
   //   1) read file
   //   2) get sections
   //
   //=========================

	CRW reader; // create object to reader
	reader.read("a.out"); // read sections
	reader.print(); // print, just for see
	
	QByteArray section; // creat temprery section
	//get sections
	section = reader.getSection(ESectionType::Data); 
	cout << "data section: " << section.data() << endl;

	section = reader.getSection(ESectionType::Code);
	cout << "code section: " << section.data() << endl;

	section = reader.getSection(ESectionType::CodeSymbol);
	cout << "code symbol : " << section.data() << endl;

	writer.getSectionType(7);

	return a.exec();
}
