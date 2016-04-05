#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>


using namespace std;


class Encode {
private:
    string filename;
    string MessageToEncode;
    bool FileOpen();
public:
    Encode();
    bool GetFileName();
    string GetMessage();
    string SetFileName();
    string ReadTextInputFile(string filename);

    bool EncodeText(string picturefilename, string text);
};