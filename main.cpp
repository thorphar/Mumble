#include <iostream>
#include <fstream>
#include "decode.h"
#include "md5.h"
#include "encode.h"

void MessageDecode();

using namespace std;

string GetPassword(){
    string password;
    cout << "Please enter your password: ";
    getline(cin,password);
    password = md5(password);
    return password;
}
void displayTitle(){
    ifstream in("/Users/thorphar/ClionProjects/PasswordWorkingVersion/title.txt");
    if(!in) {
        cout << "Cannot open input file.\n";
    }
    char str[255];
    while(in) {
        in.getline(str, 255);  // delim defaults to '\n'
        if(in) cout << str << endl;
    }
    in.close();
}
void displayLoading(){
    ifstream in("/Users/thorphar/ClionProjects/PasswordWorkingVersion/loading.txt");
    if(!in) {
        cout << "Cannot open input file.\n";
    }
    char str[255];
    while(in) {
        in.getline(str, 255);  // delim defaults to '\n'
        if(in) cout << str << endl;
    }
    in.close();
}

void MessageConvert(){
    displayLoading();
    string picfilename;
    string textfilename;
    string text;
    bool menucorrect = false;
    string menuoption;

    Encode NewEn;


    string password;
    password = GetPassword();
    while (menucorrect == false) {
        cout << "Please enter the name of the file you would like to encode your text onto." << endl;
        picfilename = NewEn.SetFileName();
        if (picfilename == "ERROR"){
            cout << "Please try again" << endl;
            menucorrect = false;
        }
        else{menucorrect = true;}
    }

    menucorrect = false;

    while (menucorrect == false) {
        // Menu for type of encoding
        //cout << string(50, '\n'); // Clearing the screen
        cout << "Please pick one of the following options." << endl;
        cout << "1. Encode from text file (.txt extension only)" << endl;
        cout << "2. Encode from text you enter on the console" << endl;
        cout << "q. EXIT" << endl;
        cout << ": ";
        cin >> menuoption;
        cin.clear();
        if (menuoption == "1") {
            cout << "Please enter the name of the text file you would to encode." << endl;
            textfilename = NewEn.SetFileName();
            if (textfilename == "ERROR"){
                cout << "Please try again" << endl;
                menucorrect = false;
            }
            else {text = NewEn.ReadTextInputFile(textfilename);
                menucorrect = true;}
        }
        else if (menuoption == "2") {
            text = NewEn.GetMessage();
            menucorrect = true;
        }
        else if (menuoption == "q"){
            break;
        }
        else{
            cout << "No correct option was picked!!" << endl;
            menucorrect = false;
        } // no correct option was picked}
    }

    string passtext = password + text;
    NewEn.EncodeText(picfilename,passtext);
    cout << "Please enter the password to decode the encoded picture. " <<endl;
    cout << ": " ;
    string attempt;
    getline(cin,attempt);
    // cin.ignore();
    Decode NewDe;
    if (NewDe.TestPassword(attempt,"/Users/thorphar/ClionProjects/PasswordWorkingVersion/encodedimage.bmp") == true) {
        cout << "\nPassword Correct" << endl;
        if (NewDe.DecodeText("/Users/thorphar/ClionProjects/PasswordWorkingVersion/encodedimage.bmp") == text) {
            cout << "\nMessage was tested against start version and they matched" << endl;
        }
        else {
            cout << "\nMajor error was caught on the exported encoded image" << endl;
        }
    }
    else{
        cout << "\nYou got the password wrong" << endl;
    }
}
void MessageDecode() {
    string filename;
    displayLoading();
    filename = "/Users/thorphar/ClionProjects/PasswordWorkingVersion/encodedimage.bmp";
    cout << "Please enter the password to decode the encoded picture. " <<endl;
    cout << ": " ;
    string attempt;
    getline(cin,attempt);
    // cin.ignore();
    Decode NewDe1;
    if (NewDe1.TestPassword(attempt,filename) == true) {
        cout << "\nPassword Correct" << endl;
        NewDe1.DecodeText(filename);
    }
    else{
        cout << "\nYou got the password wrong" << endl;
    }
}

int main() {

    bool menuchoice = false;

    while (menuchoice == false){
        displayTitle();
        cout << "\n\nPlease press.." << endl;
        cout << "1 -> Encoding a messgae into a picture" << endl;
        cout << "2 -> Decoding a message from a picture" << endl;
        cout << "q -> Quit" << endl;
        cout << "\n: " ;
        string input;
        getline(cin,input);
        if (input == "1"){
            MessageConvert();
            cout << "\nPress any key to continue..." << endl;
            cin.ignore();
        }
        else if (input == "2"){
            MessageDecode();
            cout << "\nPress any key to continue..." << endl;
            cin.ignore();
        }
        else if (input == "q"){
            menuchoice = true;
        }
        else {cout << "Invalid input has been entered!!\n\n" << endl;}
     }


    return 0;
}

