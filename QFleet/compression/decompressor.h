#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "LZ4/lz4.h"

#include <QByteArray>
#include <QString>

class decompressor
{
public:
    decompressor() = delete;

    static bool readCompressedFile(const QString, QByteArray&);
private:


};

#endif // DECOMPRESSOR_H
