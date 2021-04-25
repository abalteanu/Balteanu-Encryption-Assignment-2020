 /*****************************************************************************
 *	Name:     Ana Balteanu                                                    *
 *	Date:     9/19/2020                                                       *
 *                                                                            *
 *	Description: Reads a keyword and a message to encode from a file, and     *
 *  prints out the keyword and encrypted message                              *
 *                                                                            *
 *****************************************************************************/

/* RETURNS
if return 1: Unable to open a file
if return 2: Message or keyword have a char that is lowercase
if return 3: Keyword or message are too long(longer than 6 or 60 chars)
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

//prototyping
void removeSpaces (char * word);
void removeSpecChar (char * word);
int checkFiles (ifstream& File);
int checkInput(int length, char * word);

int main() {

    ifstream dataFile("Input2.txt");
    ofstream outputFile;
    outputFile.open("output.txt");
    if (checkFiles(dataFile) == 1){
        return 1;
    }

    if (!outputFile.is_open() ) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    char keyword[7] = "";
    char code[61] = "";

    //reading key from file
    dataFile >> keyword;
    cout << keyword << endl;
    //reading word to be encoded from file
    while(!dataFile.eof()) {
        dataFile >> code[strlen(code)];
    }

    //makes sure that message and keyword are to standard
    if(checkInput(6, keyword) == 2 || checkInput(60, code) == 2 ){
        cout << "Message and keyword need to be in all uppercase letters";
        return 2;
    } else if(checkInput(6, keyword) == 3 || checkInput(60, code) == 3 ){
        cout << "Keyword or Message is too long." << endl;
        return 3;
    }
    removeSpaces(code);
    removeSpecChar(code);
    removeSpaces(keyword);
    removeSpecChar(keyword);

    //encrypting code
    for (int i = 0; i < strlen(code); i++) {
        code[i] = (code[i] - 65 + keyword[i % strlen(keyword)] - 65) % 26 + 65;
        cout << code[i];
    }

    return 0;
}

void removeSpaces (char * word){
    //This function removes any spaces in a line
    if (word == NULL){
        return;
    }

    int n = 0;  //temp counter
    for(int i = 0; i < strlen(word); ++i){
        if (word[i] != ' '){
            word[n++] = word[i];  //keeping track of non-space locations, keeping everything but spaces in output
        }

    }
    word[n] = '\0';
}

void removeSpecChar (char * word){
    //This function removes any characters other than the alphabet from the text
    if (word == NULL){
        return;
    }

    int n = 0;  //temp counter
    for(int i = 0; i < strlen(word); ++i){
        if ((word[i] >= 'a' && word[i]<='z') || (word[i] >= 'A' && word[i]<='Z')){
            word[n++] = word[i];  //keeping track of non-space locations, keeping everything but special chars in output
        }
    }

    word[n] = '\0';
}

int checkFiles (ifstream& File){
    //checking if files can open for reading
    if (!File.is_open() ) {
        cout << "Unable to open file" << endl;
        return 1;
    }else {
        return 0;
    }
}

int checkInput(int length, char * word){
    //function checks if input is up to standards (does not hit max length or have any lowercase chars)
    if (strlen(word) <= length){
        for (int i = 0; i < strlen(word); i++){
            //checking if word is lowercase, and if not turning it into uppercase
            if (islower(word[i])) {
                //message has char that is lowercase
                return 2;
            }
            return 0;
        }
    } else {
        //message is too long
        return 3;
    }
}
