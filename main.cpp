#include <iostream>
#include <windows.h>
#include <stdlib.h>

#include "terminal_HMI.h"

//Define parameters for database connection
const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "schneider_app";
unsigned int port = 3306;
const char* unixshocket = NULL;
unsigned long clientflag = 0;

int main()
{
    bool stop = 1;
    int state = 0;

    //Initialize HMI and database connection
    terminal_HMI myHMI(hostname, username, password, database, port, unixshocket, clientflag);

    while(stop){
        switch(state){
        case MAIN_MENU:
            state = myHMI.main_menu();
            break;
        case INSERT_MENU:
            state = myHMI.insert_menu();
            break;
        case LIST_MENU:
            state = myHMI.list_menu();
            break;
        case SEARCH_MENU:
            state = myHMI.search_menu();
            break;
        default:
            printf("| Closing terminal...");
            stop = 0;
            break;
        }
    }

    return 0;
}
