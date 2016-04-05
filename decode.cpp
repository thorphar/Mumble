#include "decode.h"

string Decode::DecodeText(string decodefilename) {

    streampos size;
    string outputstring;

    char * memblock;
    int lettercount = 0;
    int wordcount = 0;
    ifstream file (decodefilename, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (727, ios::beg);
        file.read (memblock, size);
        file.close();
        string data;
        for (int i = 0; i < size; i++){
            if(lettercount < 8){
                // std::cout << bitset<8>(memblock[i]) << std::endl;
                int LSB = memblock[i] & 1;
                //  std::cout << LSB << std::endl;
                if (LSB == 1) {data.append("1");}
                else { data.append("0");}
                lettercount ++;
            }
            else {lettercount = 0; wordcount ++; i=i+10;}
        }


        //std::cout << data << std::endl; // SHOWRAWDATA
        int output = 0;
        //std::cout << "ENCODED MESSAGE: ";
        for (int a =0 ; a < size ; a++){
            if (data[a] == '1'){
                output = output + 128;
            }
            a++;
            if (data[a] == '1'){
                output = output + 64;
            }
            a++;
            if (data[a] == '1'){
                output = output + 32;
            }
            a++;
            if (data[a] == '1'){
                output = output + 16;
            }
            a++;
            if (data[a] == '1'){
                output = output + 8;
            }
            a++;
            if (data[a] == '1'){
                output = output + 4;
            }
            a++;
            if (data[a] == '1'){
                output = output + 2;
            }
            a++;
            if (data[a] == '1'){
                output = output + 1;
            }

            if (output == 4) {
              //  cout << "\n\nFOUND END OF SENTENCE ASCII CODE" << endl;
                break;
            }


            else {
                char W = static_cast<char>(output);
                outputstring = outputstring + W;
                //std::cout << W; // Display Decoded message character by character
                output = 0;
            }
        }
       // std::cout << "\n" << std::endl;

        delete[] memblock;
    }
    else cout << "Unable to open file";
    cout << outputstring;

    return outputstring;

}

bool Decode::TestPassword(string attempt,string decodefilename) {
    streampos size;
    string outputstring;

    char * memblock;
    int lettercount = 0;
    int wordcount = 0;
    ifstream file (decodefilename, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        string data;
        for (int i = 100; i < size ; i++){
            if(lettercount < 8){
                // std::cout << bitset<8>(memblock[i]) << std::endl;
                int LSB = memblock[i] & 1;
                //  std::cout << LSB << std::endl;
                if (LSB == 1) {data.append("1");}
                else { data.append("0");}
                lettercount ++;
            }
            else {lettercount = 0; wordcount ++; i=i+10;}
        }


        //std::cout << data << std::endl; // SHOWRAWDATA
        int output = 0;
     //   std::cout << "ENCODED MESSAGE: ";
        for (int a =0 ; a < size ; a++){
            if (data[a] == '1'){
                output = output + 128;
            }
            a++;
            if (data[a] == '1'){
                output = output + 64;
            }
            a++;
            if (data[a] == '1'){
                output = output + 32;
            }
            a++;
            if (data[a] == '1'){
                output = output + 16;
            }
            a++;
            if (data[a] == '1'){
                output = output + 8;
            }
            a++;
            if (data[a] == '1'){
                output = output + 4;
            }
            a++;
            if (data[a] == '1'){
                output = output + 2;
            }
            a++;
            if (data[a] == '1'){
                output = output + 1;
            }

            if (output == 3){
               // cout << "\n\nFOUND END OF Password String ASCII CODE" << endl;
                break;
            }
            else {
                char W = static_cast<char>(output);
                outputstring = outputstring + W;
                // std::cout << W; // Display Decoded message character by character
                output = 0;
            }
        }
       // std::cout << "\n" << std::endl;

        delete[] memblock;
    }
    else cout << "Unable to open file";

    if (outputstring == md5(attempt)){
        return true;
    }
    else {

        return false;
    }
}
