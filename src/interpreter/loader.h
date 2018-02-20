#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QByteArray>
//#include "rw.h" // read-writer
#include "memory.h"
#include "../compiler/instructions.h"

class CLoader {
public:
    uint32 load(const QString& filePath, CMemory& memory); // load
};

#endif // LOADER_H
