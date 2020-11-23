#include "lz4util.hpp"

using namespace std;

vector<uint8_t> LZ4Decompressor::decompress(vector<uint8_t> &buffer) {

    if (!isValied(buffer)) {
        std::vector<uint8_t> empty;
        return empty;
    }

    BinaryReader reader(buffer);
    vector<uint8_t> retArray;
    int dataSize = 0;
    int decompressedSize = 0;

    int token = 0;
    int sqSize = 0;
    int matchSize = 0;
    int litPos = 0;
    int offset = 0;
    int retCurPos = 0;
    int endPos = 0;

    reader.setOffset(4);

    decompressedSize = reader.readInt32();
    dataSize = reader.readInt32();
    endPos = dataSize + 16;
    retArray = vector<uint8_t>(decompressedSize);

    reader.setOffset(16);

    while(true) {
        token = reader.readByte();

        sqSize = token >> 4;
        matchSize = (token & 0x0f) + 4;

        if (sqSize == 15) {
            sqSize += readAdditionalSize(reader);
        }

        retArray = reader.copy(retArray, retCurPos, sqSize);
        retCurPos += sqSize;

        if (reader.getOffset() >= endPos - 1) {
            break;
        }

        offset = reader.readInt16();

        if (matchSize == 19) {
            matchSize += readAdditionalSize(reader);
        }

        if (matchSize > offset) {
            int matchPos = retCurPos - offset;
            while(true) {
                copy(retArray.begin() + matchPos, retArray.begin() + matchPos + offset, retArray.begin() + retCurPos);
                retCurPos += offset;
                matchSize -= offset;
                if (matchSize < offset) {
                    break;
                }
            }
        }
        copy(retArray.begin() + retCurPos - offset, retArray.begin() + retCurPos - offset + matchSize, retArray.begin() + retCurPos);
        retCurPos += matchSize;
    }

    return retArray;
}

int LZ4Decompressor::readAdditionalSize(BinaryReader &reader) {
    uint8_t size = reader.readByte();
    return (size == 255) ? size + readAdditionalSize(reader) : size;
}

bool LZ4Decompressor::isValied(vector<uint8_t> &buffer) {
    if (buffer.size() > 16) {
        BinaryReader reader(buffer, 8);
        int dataSize = reader.readInt32() + 16;
        return (buffer.size() == dataSize);
    }

    return false;
}
