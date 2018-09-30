#include "lz4util.hpp"

using namespace std;

vector<uint8_t> LZ4Decompressor::decompress(vector<uint8_t> &array) {

	if (isValied(array) == 0) {
		std::vector<uint8_t> emptyData;
		return emptyData;
	}

	BinaryReader r(array);
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

	r.seekAbs(4);
	decompressedSize = r.readIntLE();
	dataSize = r.readIntLE();
	endPos = dataSize + 16;
	retArray = vector<uint8_t>(decompressedSize);

	r.seekAbs(16);

	while(true) {
		token = r.readByte();

		sqSize = token >> 4;
		matchSize = (token & 0x0f) + 4;

		if (sqSize == 15) {
			sqSize += readAdditionalSize(r);
		}

		retArray = r.copyBytes(retArray, retCurPos, sqSize);
		retCurPos += sqSize;

		if (r.getPos() >= endPos - 1) {
			break;
		}

		offset = r.readShortLE();

		if (matchSize == 19) {
			matchSize += readAdditionalSize(r);
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

int LZ4Decompressor::isValied(vector<uint8_t> &array) {
	if (array.size() > 16) {
		BinaryReader r(array);
		r.seekAbs(8);
		int dataSize = r.readIntLE() + 16;
		cout << array.size() << endl;
		cout << dataSize << endl;
		if (array.size() == dataSize) {
			return 1;
		}
	}

	return 0;
}