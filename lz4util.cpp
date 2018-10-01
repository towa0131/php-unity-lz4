#include "lz4util.hpp"

using namespace std;

vector<uint8_t> LZ4Decompressor::decompress(vector<uint8_t> &buffer) {

	if (isValied(buffer) == 0) {
		std::vector<uint8_t> emptyData;
		return emptyData;
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

	reader.seekAbs(4);

	decompressedSize = reader.readLInt();
	dataSize = reader.readLInt();
	endPos = dataSize + 16;
	retArray = vector<uint8_t>(decompressedSize);

	reader.seekAbs(16);

	while(true) {
		token = reader.readByte();

		sqSize = token >> 4;
		matchSize = (token & 0x0f) + 4;

		if (sqSize == 15) {
			sqSize += readAdditionalSize(reader);
		}

		retArray = reader.copyBytes(retArray, retCurPos, sqSize);
		retCurPos += sqSize;

		if (reader.getOffset() >= endPos - 1) {
			break;
		}

		offset = reader.readLShort();

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
	if (size == 255) {
		return size + readAdditionalSize(reader);
	} else {
		return size;
	}
}

int LZ4Decompressor::isValied(vector<uint8_t> &buffer) {
	if (buffer.size() > 16) {
		BinaryReader reader(buffer, 8);
		int dataSize = reader.readLInt() + 16;
		if (buffer.size() == dataSize) {
			return 1;
		}
	}

	return 0;
}