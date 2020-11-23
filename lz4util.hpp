#include <iostream>
#include <vector>

using namespace std;

class BinaryReader {
private:
    vector<uint8_t> buffer;
    int offset;
public:
    BinaryReader(vector<uint8_t>&);
    BinaryReader(vector<uint8_t>&, int);
    int readByte();
    int readInt16();
    int readInt32();
    vector<uint8_t>& copy(vector<uint8_t>&, int&, int&);
    void setOffset(int);
    int getOffset();
};

class LZ4Decompressor {
public:
    vector<uint8_t> decompress(vector<uint8_t> &buffer);
    bool isValied(vector<uint8_t> &buffer);
    int readAdditionalSize(BinaryReader &reader);
};
