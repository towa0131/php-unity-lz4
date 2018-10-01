#include <iostream>
#include <vector>

using namespace std;

class BinaryReader {
private:
	vector<uint8_t> buffer;
	int offset;
public:
	BinaryReader(vector<uint8_t> &vector);
	BinaryReader(vector<uint8_t> &vector, int pos);
	int readByte();
	int readLShort();
	int readLInt();
	vector<uint8_t>& copyBytes(vector<uint8_t> &dst, int &distance, int &size);
	void seekAbs(int pos);
	void seekRel(int diff);
	vector<uint8_t> getBuffer();
	int getOffset();
};

class LZ4Decompressor {
public:
	vector<uint8_t> decompress(vector<uint8_t> &buffer);
	int isValied(vector<uint8_t> &buffer);
	int readAdditionalSize(BinaryReader &reader);
};