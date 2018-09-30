#include "lz4util.hpp"

using namespace std;

BinaryReader::BinaryReader(vector<uint8_t> &array) {
	ary = array;
	curPos = 0;
}

int BinaryReader::readByte() {
	curPos++;
	return ary[curPos - 1];
}

int BinaryReader::readShortLE() {
	curPos += 2;
	return ary[curPos - 2] + (ary[curPos - 1] << 8);
}

int BinaryReader::readIntLE() {
	curPos += 4;
	return ary[curPos - 4] + (ary[curPos - 3] << 8) + (ary[curPos - 2] << 16) + (ary[curPos - 1] << 24);
}

vector<uint8_t>& BinaryReader::copyBytes(vector<uint8_t> &dst, int &offset, int &size) {
	curPos += size;
	copy(ary.begin() + curPos - size, ary.begin() + curPos, dst.begin() + offset);
	return dst;
}

void BinaryReader::seekAbs(int pos) {
	curPos = pos;
}

void BinaryReader::seekRel(int diff) {
	curPos += diff;
}

int BinaryReader::getPos() {
	return curPos;
}