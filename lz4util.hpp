#include <iostream>
#include <vector>

using namespace std;

class BinaryReader {
private:
	vector<uint8_t> ary;
	int curPos;
public:
	BinaryReader(vector<uint8_t> &array);
	int readByte();
	int readShortLE();
	int readIntLE();
	vector<uint8_t>& copyBytes(vector<uint8_t> &dst, int &offset, int &size);
	void seekAbs(int pos);
	void seekRel(int diff);
	int getPos();
};

class LZ4Decompressor {
public:
	vector<uint8_t> decompress(vector<uint8_t> &array);
	int isValied(vector<uint8_t> &array);
	int readAdditionalSize(BinaryReader &reader);
};