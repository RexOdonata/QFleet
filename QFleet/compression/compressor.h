#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "LZ4/lz4file.h"

#include <QByteArray>
#include <QString>

class compressor
{
public:

    compressor() = delete;

    static bool writeCompressedFile(QByteArray&, QString);


private:

    char * compressedData = NULL;

    static void deleteTempfile();

};

#endif
