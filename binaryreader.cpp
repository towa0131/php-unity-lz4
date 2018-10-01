#include "lz4util.hpp"

using namespace std;

BinaryReader::BinaryReader(vector<uint8_t> &vector) {
	buffer = vector;
	offset = 0;
}

BinaryReader::BinaryReader(vector<uint8_t> &vector, int pos) {
	buffer = vector;
	offset = pos;
}

int BinaryReader::readByte() {
	offset++;
	return buffer[offset - 1];
}

int BinaryReader::readLShort() {
	offset += 2;
	return buffer[offset - 2] + (buffer[offset - 1] << 8);
}

int BinaryReader::readLInt() {
	offset += 4;
	return buffer[offset - 4] + (buffer[offset - 3] << 8) + (buffer[offset - 2] << 16) + (buffer[offset - 1] << 24);
}

vector<uint8_t>& BinaryReader::copyBytes(vector<uint8_t> &dst, int &distance, int &size) {
	offset += size;
	copy(buffer.begin() + offset - size, buffer.begin() + offset, dst.begin() + distance);
	return dst;
}

void BinaryReader::seekAbs(int pos) {
	offset = pos;
}

void BinaryReader::seekRel(int diff) {
	offset += diff;
}

vector<uint8_t> BinaryReader::getBuffer(){
	return buffer;
}

int BinaryReader::getOffset() {
	return offset;
}