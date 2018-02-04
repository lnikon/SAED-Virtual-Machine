#include "loader.h"

CLoader::CLoader() {
    m_nStackSize = 128; // <-- ??? stack size
}

void CLoader::load(const QString& filePath) {
    CRW reader;
    reader.read(filePath);
    QByteArray code = reader.getSection(ESectionType::Code);
    QByteArray data = reader.getSection(ESectionType::Data);
    QByteArray stack(m_nStackSize, '.');

    m_Memory.aMemory.clear();
    m_Memory.aMemory += data;
    m_Memory.aMemory += code;
    m_Memory.aMemory += stack;

    m_Memory.nDataSize   = data.size();
    m_Memory.nIPPosition = data.size();
    m_Memory.nStackSize  = m_nStackSize;
}

CLoader::SMemory& CLoader::getMemory() {
    return m_Memory;
}

void CLoader::setStackSize(uint32 stackSize) {
    m_nStackSize = stackSize;
}
