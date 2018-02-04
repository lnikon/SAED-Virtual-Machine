#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QByteArray>
#include "rw.h" // read-writer


class CLoader {
public:
    // memory has 3 section,
    // first  is data  section (from 0 to nDataSize)
    // second is code  section (from nDataSize to (memory.size() - nStackSize))
    // last   is stack section (from the end of memory to (memory.size() - nStackSize))
    struct SMemory{
        QByteArray aMemory;
        uint32 nDataSize;
        uint32 nIPPosition;// <-- ??? it is same as nDataSize
        uint32 nStackSize;
    };

    CLoader(); // default constructor

    void load(const QString& filePath); // load

    SMemory& getMemory();

    void setStackSize(uint32 stackSize); // as default stack size is 128 bytes

private:
    SMemory m_Memory;
    uint32 m_nStackSize;
};

#endif // LOADER_H
