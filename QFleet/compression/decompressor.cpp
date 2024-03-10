#include "decompressor.h"

#include "constants.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>

#include <algorithm>

#include <stdio.h>

#include <lz4file.h>

bool decompressor::readCompressedFile(QByteArray& dest, const QString fn)
{
    FILE * readPtr = NULL;

    // open file for binary read
    std::string sfn = fn.toStdString();

    readPtr = fopen(sfn.c_str(), "rb");
    if (readPtr == NULL)
    {
        qCritical()<<"Read File Open Failed";
        exit(1);
    }

    LZ4_readFile_t * lz4Read;
    LZ4F_errorCode_t r = LZ4F_OK_NoError;

    r= LZ4F_readOpen(&lz4Read, readPtr);
    if (LZ4F_isError(r))
    {
        qCritical()<<"LZ4f Read File Open Failed";
        exit(1);
    }


    std::vector<char> buffer(CHUNKSIZE,0);
    std::vector<char> outData;
    outData.reserve(CHUNKSIZE);

    while (true)
    {
        r = LZ4F_read(lz4Read, buffer.data(), CHUNKSIZE);

        if (LZ4F_isError(r))
        {
            qCritical()<<QString("LZ4f rear error %1").arg(LZ4F_getErrorName(r));
            exit(1);
        }

        if (r == 0)
            break;

        outData.insert(outData.end(), buffer.begin(), buffer.end());
        memset(buffer.data(), 0, CHUNKSIZE);
    }

    // get an iterator to the first 0 element at the end of the file in case of overchunking
    auto lItr = getMismatch(outData);

    // shrink to trim
    outData.resize(lItr-outData.begin());


    r = LZ4F_readClose(lz4Read);
    if (LZ4F_isError(r))
    {
        qCritical()<<QString("LZ4f rear close error %1").arg(LZ4F_getErrorName(r));
        exit(1);
    }

    fclose(readPtr);

    // copy results back to the ref passed in, I sure hope this is a deep copy
    dest = QByteArray(outData.data(), outData.size());


    return true;
}

std::vector<char>::iterator decompressor::getMismatch(std::vector<char>& data)
{
    std::vector<char> emptyVec(data.size(),0);

    // first output is from first range, 2nd from 2nd
    auto last = std::mismatch(data.rbegin(), data.rend(), emptyVec.rbegin(), emptyVec.rend());

    auto lrItr = last.first;

    auto lItr = lrItr.base();

    qInfo()<<QString("trimming last chunk at %1").arg(lItr-data.begin());

    return lItr;
}
