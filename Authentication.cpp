#include "Authentication.h"
#include <iostream>
#include <stdlib.h> // For system() and exit()
#include <unistd.h> // For sleep()

using namespace std;

void login() {
    string username;
    string password;
    int tries = 3;
    bool success = false;
    while(tries && !success){
        cout << "Enter Username" << endl;
        cin >> username;
        cout << "Enter Password" << endl;
        cin >> password;

        if(username == "admin" && password == "admin"){
            system("cls || clear"); // Clears the console screen, compatible with both Windows and Unix
            cout << "You have got access. \n";
            success = true;
        }
        else{
            tries--;
            system("cls || clear"); // Clears the console screen, compatible with both Windows and Unix
            cout << "Wrong Authentication" << endl;
            if(tries == 0){
                system("cls || clear"); // Clears the console screen, compatible with both Windows and Unix
                cout << "Failed to authenticate" << endl;
                sleep(3); // Waits for 3 seconds before exiting
                exit(0); // Exits the program after 3 failed login attempts
            }
        }
    }
}

