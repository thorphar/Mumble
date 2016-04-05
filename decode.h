#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "md5.h"
using namespace std;




class Decode {
private:
    string filename;
    string MessageToEncode;
    bool FileOpen();
public:
        bool TestPassword(string attempt,string decodefilename);

    string DecodeText(string decodefilename);
};