#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H


#include <QByteArray>
#include <QString>

#include <vector>

class decompressor
{
public:
    decompressor() = delete;

    static bool readCompressedFile(QByteArray&, const QString);
private:

    static std::vector<char>::iterator getMismatch(std::vector<char>&);
};

#endif // DECOMPRESSOR_H
