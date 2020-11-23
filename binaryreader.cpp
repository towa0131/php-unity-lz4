#include "lz4util.hpp"

using namespace std;

BinaryReader::BinaryReader(vector<uint8_t> &vector) : BinaryReader(vector, 0) {

}

BinaryReader::BinaryReader(vector<uint8_t> &vector, int pos) {
    buffer = vector;
    offset = pos;
}

int BinaryReader::readByte() {
    return buffer[offset++];
}

int BinaryReader::readInt16() {
    return buffer[offset++] | (buffer[offset++] << 8);
}

int BinaryReader::readInt32() {
    return buffer[offset++] | (buffer[offset++] << 8) | (buffer[offset++] << 16) | (buffer[offset++] << 24);
}

vector<uint8_t>& BinaryReader::copy(vector<uint8_t> &vec, int &dist, int &size) {
    std::copy(buffer.begin() + offset, buffer.begin() + offset + size, vec.begin() + dist);
    offset += size;
    return vec;
}

void BinaryReader::setOffset(int pos) {
    offset = pos;
}

int BinaryReader::getOffset() {
    return offset;
}
