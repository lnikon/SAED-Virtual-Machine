#include"rw.h"

CRW::CRW() {
		m_sSignature = "SAED/VirtualMachine/ExeFile";
		m_nVersion = 5;
		m_nSectionCount = 0;
	}

void CRW::write(QString path) {
	QFile file(path);
	file.open(QIODevice::ReadWrite);
	QTextStream out(&file);
	out << m_sSignature << " " << m_nVersion << " " << m_nSectionCount << " ";
	for (int32 i = 0; i < m_nSectionCount; ++i) {
		out << (int32)m_vSectionsType[i] << " ";
	}
	for (int32 i = 0; i < m_nSectionCount; ++i) {
		out << m_Buffer[i].size() << " ";
	}
	for (int32 i = 0; i < m_nSectionCount; ++i) {
		for (uint32 j = 0; j < m_Buffer[i].size(); ++j) {
			out << m_Buffer[i][j];
		}
	}
	file.close();
}

void CRW::addSection(ESectionType type, const QByteArray& aData) {
	m_nSectionCount++;
	m_vSectionsType.push_back(type);
	m_Buffer.push_back(aData);
	m_vSectionsSize.push_back(aData.size());
}

bool CRW::read(QString path) { // test version
	m_Buffer.clear();
	m_nSectionCount = 0;
	QFile file(path);
	file.open(QIODevice::ReadWrite);
	QTextStream in(&file);
	QString signature;
	in >> signature;
	if (m_sSignature != signature) return false;
	in >> m_nVersion;
	in >> m_nSectionCount;

	for (int i = 0; i < m_nSectionCount; ++i) {
		unsigned int sectionType;
		in >> sectionType;
		m_vSectionsType.push_back((ESectionType)sectionType);
	}
	for (int i = 0; i < m_nSectionCount; ++i) {
		int32 sectionSize;
		in >> sectionSize;
		m_vSectionsSize.push_back(sectionSize);		
	}
	char c; // current symbol
	in >> c;
	for (int i = 0; i < m_nSectionCount; ++i) {
		QByteArray section;
		for (int j = 0; j < m_vSectionsSize[i]; ++j) {
			in >> c;
			section += c;
		}
		m_Buffer.push_back(section);
	}
	file.close();
	return true;
}

QByteArray CRW::getSection(ESectionType type) {
	for (uint32 i = 0; i < m_vSectionsType.size(); ++i) {
		if (m_vSectionsType[i] == type) {
			return m_Buffer[i];
		}
	}
	QByteArray temp;
	return temp;
}

uint32 CRW::getSectionCount() { return m_nSectionCount; }

ESectionType CRW::getSectionType(uint index) {
	return m_vSectionsType[index];	
}

void CRW::print() {
	cout << "------------------------------------------------\n";
	cout << "   signature:     " << m_sSignature.toStdString() << endl;
	cout << "   version:       " << m_nVersion << endl;
	cout << "   section count: " << m_nSectionCount << endl << endl;

	for (int i = 0; i < m_nSectionCount; ++i) {
		cout << "------------------------------------------------\n\t\tsection: " << i + 1 << endl << endl;
		switch (m_vSectionsType[i])
		{
		case ESectionType::Data: cout << "   type: data" << endl; break;
		case ESectionType::Code: cout << "   type: code" << endl; break;
		case ESectionType::DataSymbol: cout << "   type: data symbol" << endl; break;
		case ESectionType::CodeSymbol: cout << "   type: code symbol" << endl; break;
		}
		cout << "   size: " << m_vSectionsSize[i] << endl;
		cout << "   data: " << m_Buffer[i].data() << endl;
		cout << endl;
	}
	cout << "------------------------------------------------\n\n";

}