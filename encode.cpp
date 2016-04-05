#include "encode.h"


Encode::Encode(){
        cout<< "Welcome to the encoder" <<endl;
}

bool Encode::GetFileName(){
    cout << "-> ";
    cin >> filename;
    cout << "Testing file useablity" << endl;
    if(FileOpen()){ cout << "Successfully Opened!!" << endl; return true;}
    else {cout << "***The File couldn't be opened successfully***\nThis could be due to incorrect input\nOr.. Wrong file location" << endl;
          return false;}

}

string Encode::SetFileName() {
    if (GetFileName()) return filename;
    else {cout << "Error in setting filename" << endl; return "ERROR";}
}

bool Encode::EncodeText(string picturefilename, string text){
    streampos size;
    char * filecontents;
    int sizeofinput = text.size();
    filecontents = new char [sizeofinput+1];
    std::cout <<"Char Length : " <<sizeofinput << " REMEMBER THIS !!!" << std::endl;
    int temp[sizeofinput];
    string * binout;
    binout = new string [sizeofinput+3];
    for(int w = 0; w < sizeofinput; w++){
        temp[w] = text[w];
    }
    int stepper =0;
    for(int w = 0; w< sizeofinput+1 ;w++){
        if(w == 32){
            binout [w] = "00000011";// end of password
            w++;
            binout[w] = bitset<8>(temp[stepper]).to_string();
            stepper ++;
        }
        else {
            binout[w] = bitset<8>(temp[stepper]).to_string();
            stepper ++;
        }
       // std::cout << "BINARY: " <<binout[w] << " ASCII Dec VALUE: "<< temp[w] << " Eng Letter: " << text[w] << std::endl;
    }
    binout[stepper+1] = "00000100"; //end of text/message transmission

    ifstream file(filename, ios::binary | ios::in | ios::ate);
    if (!file.is_open()){
        std::cout << "ERROR OPENING FILE" << std::endl;
    }
    else{
        size = file.tellg();
        std::cout <<"Current File Size : " << size << std::endl;
        filecontents = new char [size];
        file.seekg(0, ios::beg);
        file.read(filecontents, size);
        file.close();
        int lettercounter = 0;
        int binarycounter = 0;
        std::cout << size << std::endl;
        std::cout << "1" << std::endl;

//CHECK FOR TEXT SIZE AGAINST POSSIBLE PIC
        if (sizeofinput > (size/18)){
            cout << "Picture is not large enough to store the inputted text " << endl;
            cout << "Please reduce the text inputtted or increase the size of the image" << endl;
        }
// End OF CHECK
        for (int e = 100 ; e < size ; e++) {
//std::cout << bitset< 8 > (filecontents[e]);
//cout << (filecontents[e] & 1) << endl;
            if (binarycounter < 8) {
                if (binout[lettercounter][binarycounter] == '1' && (filecontents[e] & 1) == 1) {
                    // NO need to do anything as bit is what we want
                    //std::cout << "No NEED" << std::endl;
                    binarycounter++;
                }
                else if (binout[lettercounter][binarycounter] == '1' && (filecontents[e] & 1) == 0) {
                    filecontents[e]++;

                    binarycounter++;
                    //std::cout << "Change Occured" << std::endl;
                }
                else if (binout[lettercounter][binarycounter] == '0' && (filecontents[e] & 1) == 0) {
                    //std::cout << "No Need" << std::endl;

                    binarycounter++;
                }
                else if (binout[lettercounter][binarycounter] == '0' && (filecontents[e] & 1) == 1) {
                    filecontents[e]--;
                    binarycounter++;

                    //std::cout << "Change Occurred" << std::endl;
                }
            }
            else if (lettercounter < sizeofinput+2) {
                binarycounter = 0;
                lettercounter++;
                e = e + 10;
            }
            else {
                std::cout << "Ran out of text" << std::endl;
            }
        }

    }
    // START OF OUTPUT
    ofstream output;
    output.open("/Users/thorphar/ClionProjects/PasswordWorkingVersion/encodedimage.bmp");
    for (int e = 0; e < size ;e++){
        output << filecontents[e];
    }
    output.close();
// End OF OUTPUT



        delete[] filecontents;

        return true;
}

bool Encode::FileOpen() {
    fstream file(filename, ios::binary | ios::in | ios::ate);
    if (file.is_open()) {
        file.close(); // Close file to allow for further access when another method is called
        return true; // File was open successfully and the file is ready to be used and opened again
    }
    else {
        file.close(); // Close file to allow for further access when another method is called
        return false;
    }
}

string Encode::GetMessage() {
    string ENTRY;
    cin.ignore();
    std::cout << "Please enter message: ";
    getline(cin,ENTRY);
    return ENTRY;
}

string Encode::ReadTextInputFile(string filename) {
    string output;
    string line;
    ifstream openedfile (filename);
    if (openedfile.is_open())
    {
        while ( getline (openedfile,line) )
        {
            output += line;
            output += "\n";
        }
        openedfile.close();
    }
    return output;
}
