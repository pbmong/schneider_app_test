#ifndef TERMINAL_HMI_H_INCLUDED
#define TERMINAL_HMI_H_INCLUDED


#include "mysql\mysqlheaders\mysql.h"

#include "devices.h"
#include "DDBB.h"

#define MAIN_MENU 0
#define INSERT_MENU 1
#define LIST_MENU 2
#define SEARCH_MENU 3

using namespace std;

class terminal_HMI
{
private:

    MYSQL* HMI_conn;

public:
    terminal_HMI(const char*, const char*, const char*, const char*, unsigned int, const char*, unsigned long);

    int main_menu();
    int insert_menu();
    int insert_meter_menu(int);
    int insert_gateway_menu();
    int list_menu();
    int search_menu();
    int search_meter_menu(int);
    int search_gateway_menu();
    int check_ip(char []);
};

/*
constructor terminal_HMI(
    const char* hostname: name of the connection host.
    const char* username: access user name.
    const char* password: access password for the user.
    const char* database: name of the database to access.
    unsigned int port: access port for the connection.
    const char* unixshocket:
    unsigned long clientflag:
)

Description: the terminal_HMI constructor configures the
    connection object of the class thought DDBB library.
*/
terminal_HMI::terminal_HMI(const char* hostname, const char* username, const char* password, const char* database, unsigned int port, const char* unixshocket, unsigned long clientflag)
{
    //Configure database connection with the passed arguments.
    HMI_conn= DDBB_connection(hostname, username, password, database, port, unixshocket, clientflag);

}

/*
method main_menu()

Description: this method shows the main menu of de terminal HMI.
    Main menu has four options:
    1. Insert new device: includes a new device in the database.
    2. Read devices table: shows the list of a kind of device.
    3. Search device: looks for a device in the database.
    4. Exit: close the application.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::main_menu()
{
    int action = 0;

    printf("\n +------------- SCHNEIDER DEVICES MANAGER ------------------+\n");
    printf(" |                       Main Menu                          |\n");
    printf(" | 1. Insert new device                                     |\n");
    printf(" | 2. Read devices table                                    |\n");
    printf(" | 3. Search device                                         |\n");
    printf(" | 4. Exit                                                  |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What do you want to do [1, 2, 3 or 4]: ");

    char value[81]={'\0'};

    //Read value to be inserted
    cin.getline(value,80);
    action = atoi(value);

    //Check value inserted
    while(action < 1 | action > 4){

        //Read new value to be inserted
        printf(" | Please, insert an acceptable value [1, 2, 3 or 4]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    return action;
}

/*
method insert_menu()

Description: this method allows user to include a new device in
    the database.
    Insertion menu has four options:
    1. Electrical meters: includes an electrical meter.
    2. Water meter: includes a water meter.
    3. Gateway: includes a gateway
    4. (Back to main menu):.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::insert_menu()
{
    printf("\n +------------- SCHNEIDER DEVICES MANAGER ------------------+\n");
    printf(" |                     Insertion Menu                       |\n");
    printf(" | 1. Electrical meter                                      |\n");
    printf(" | 2. Water meter                                           |\n");
    printf(" | 3. Gateway                                               |\n");
    printf(" | 4. (Back to Main Menu)                                   |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What devices do you want to insert [1, 2, 3 or 4]: ");

    int action = 0;
    char value[81]={'\0'};

    //Read value to be inserted
    cin.getline(value,80);
    action = atoi(value);

    //Check value inserted
    while(action < 1 | action > 4){

        //Read new value to be inserted
        printf("| Please, insert an acceptable value [1, 2, 3 or 4]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    switch(action)
    {
        case 1:
            //Go to electric meter insertion menu
            this->insert_meter_menu(ELECT_METER_DEVICE);
            break;
        case 2:
            //Go to water meter insertion menu
            this->insert_meter_menu(WATER_METER_DEVICE);
            break;
        case 3:
            //Go to gateway insertion menu
            this->insert_gateway_menu();
            break;
        default:
            break;
    }

    return 0;
}

/*
method insert_meter_menu(
    int type_dev: variable to indicate kind of device to
        be inserted.
)

Description: this method requests to user the information of
    the new meter to be included in the database.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::insert_meter_menu(int type_dev)
{
    meter_device device;

    //Include meter type in device object
    if(type_dev == ELECT_METER_DEVICE)
        device.type = ELECT_METER_DEVICE;
    else
        device.type = WATER_METER_DEVICE;

    char inc_s[81]={'\0'};

    //Read SN of the device
    printf(" | Insert the SN of the device (max lenght 9 digits): ");
    cin.getline(inc_s,81);
    device.sn=atoi(inc_s);
    //Check SN value
    while((device.sn < 1)|(device.sn > 9999999))
    {
        //Read new SN for the device
        printf(" | Please, insert an acceptable SN (max lenght 9 digits) : ");
        cin.getline(inc_s,81);
        device.sn=atoi(inc_s);
    }

    //Read brand of the device
    printf(" | Insert the brand of the device (max lenght 15): ");
    cin.getline(device.brand,81);
    //Check if brand is empty
    if(strlen(device.brand) == 0)
        //If were, complete with default value
        sprintf(device.brand,"unknown");
    else if(strlen(device.brand) > 15)
    {
        //Read brand of the device
        printf(" | Insert a valid brand for the device (max lenght 15): ");
        cin.getline(device.brand,81);
        //Check if brand is empty
        if(strlen(device.brand) == 0)
            //If were, complete with default value
            sprintf(device.brand,"unknown");
    }

    //Read model of the device
    printf(" | Insert the model of the device (max lenght 15): ");
    cin.getline(device.model,81);
    //Check if mode is empty
    if(strlen(device.model) == 0)
        //If were, complete with default value
        sprintf(device.model,"unknown");
    else if(strlen(device.model) > 15)
    {
        //Read model of the device
        printf(" | Insert a valid model for the device (max lenght 15): ");
        cin.getline(device.model,81);
        //Check if model is empty
        if(strlen(device.model) == 0)
            //If were, complete with default value
            sprintf(device.model,"unknown");
    }

    //Execute insertion query and check query result
    int resutl = insert_meter_list(HMI_conn, device);
    if(resutl == 0)
        //Inform that insertion was executed correctly
        printf(" | Result: Device inserted correctly\n");
    else if (resutl == 2)
        //If device already exist
        printf(" | Result: DEVICE ALREADY EXIST\n");
    else
        //General error
        printf(" | Result: DEVICE INSERTION ERROR\n");

    return 0;
}

/*
method insert_gateway_menu()

Description: this method requests to user the information of
    the new gateway to be included in the database.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::insert_gateway_menu()
{
    gateway device;
    char inc_s[81]={'\0'};

    //Read SN of the device
    printf(" | Insert the SN of the device (max lenght 9): ");
    cin.getline(inc_s,81);
    device.sn=atoi(inc_s);
    //Check SN value
    while((device.sn < 1)|(device.sn > 9999999))
    {
        //Read new SN for the device
        printf(" | Please, insert an acceptable SN (max lenght 9 digits) : ");
        cin.getline(inc_s,81);
        device.sn=atoi(inc_s);
    }

    //Read brand of the device
    printf(" | Insert the brand of the device (max lenght 9): ");
    cin.getline(device.brand,81);
    //Check if brand is empty
    if(strlen(device.brand) == 0)
        //If were, complete with default value
        sprintf(device.brand,"unknown");
    else if(strlen(device.brand) > 15)
    {
        //Read brand of the device
        printf(" | Insert a valid brand for the device (max lenght 15): ");
        cin.getline(device.brand,81);
        //Check if brand is empty
        if(strlen(device.brand) == 0)
            //If were, complete with default value
            sprintf(device.brand,"unknown");
    }

    //Read model of the device
    printf(" | Insert the model of the device (max lenght 9): ");
    cin.getline(device.model,81);
    //Check if model is empty
    if(strlen(device.model) == 0)
        //If were, complete with default value
        sprintf(device.model,"unknown");
    else if(strlen(device.model) > 15)
    {
        //Read model of the device
        printf(" | Insert a valid model for the device (max lenght 15): ");
        cin.getline(device.model,81);
        //Check if model is empty
        if(strlen(device.model) == 0)
            //If were, complete with default value
            sprintf(device.model,"unknown");
    }

    //Read IP of the device
    printf(" | Insert the IP of the device: ");
    cin.getline(inc_s,81);
    //Verify that ip format is correct
    while(!(this->check_ip(inc_s)))
    {
        //Read new IP for the device
        printf(" | Insert a valid IP of the device: ");
        cin.getline(inc_s,81);
    }
    strcpy(device.ip,inc_s);

    //Read Port of the device
    printf(" | Insert the PORT of the device (max lenght 4): ");
    cin.getline(inc_s,81);
    device.port=atoi(inc_s);
    //Check Port value
    while((device.port < 1)|(device.port > 9999))
    {
        //Read new Port for the device
        printf(" | Please, insert an acceptable PORT (max lenght 4 digits) : ");
        cin.getline(inc_s,81);
        device.port=atoi(inc_s);
    }

    //Execute gateway insertion query and check query result
    int resutl = insert_gateway_list(HMI_conn, device);
    if(resutl == 0)
        //Inform that insertion was executed correctly
        printf(" | Result: Device inserted correctly\n");
    else if (resutl == 2)
        //If device already exist
        printf(" | Result: DEVICE ALREADY EXIST\n");
    else
        //General error
        printf(" | Result: DEVICE INSERTION ERROR\n");

    return 0;
}

/*
method list_menu()

Description: this method allows user to see all the information
    stored in the database about devices.
    Devices list menu has four options:
    1. Electrical meters: shows electrical meters.
    2. Water meter: shows water meters.
    3. Gateway: shows gateways.
    4. (Back to main menu):.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::list_menu()
{
    int action = 0;

    printf("\n +-------------- SCHNEIDER DEVICES MANAGER -----------------+\n");
    printf(" |                   Devices List Menu                      |\n");
    printf(" | 1. Electricity meters                                    |\n");
    printf(" | 2. Water meters                                          |\n");
    printf(" | 3. Gateway                                               |\n");
    printf(" | 4. (Back to Main Menu)                                   |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What devices do you want to see [1, 2, 3 or 4]: ");

    char value[81]={'\0'};

    //Read value to be inserted
    cin.getline(value,80);
    action = atoi(value);

    //Check value inserted
    while(action < 1 | action > 4){

        //Read new value to be inserted
        printf(" | Please, insert an acceptable value [1, 2, 3 or 4]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    //Show selected list
    switch(action)
    {
        case 1:

            //Show electric meters table
            printf("\n +----------------------------------------------------------+\n");
            printf(" |                  Electric Meters List                    |\n");
            printf(" +----------------------------------------------------------+\n");
            printf(" |    ID   |     SN     |      Brand      |      Model      |\n");
            printf(" +----------------------------------------------------------+");
            read_elect_list(HMI_conn);
            printf(" \n +----------------------------------------------------------+");
            break;
        case 2:

            //Show water meters table
            printf("\n +----------------------------------------------------------+\n");
            printf(" |                    Water Meters List                     |\n");
            printf(" +----------------------------------------------------------+\n");
            printf(" |    ID   |     SN     |      Brand      |      Model      |\n");
            printf(" +----------------------------------------------------------+");
            read_water_list(HMI_conn);
            printf(" \n +----------------------------------------------------------+");
            break;
        case 3:

            //Show gateway table
            printf("\n +-----------------------------------------------------------------------------------+\n");
            printf(" |                                  Gateway List                                     |\n");
            printf(" +-----------------------------------------------------------------------------------+\n");
            printf(" |    ID   |     SN     |      Brand      |      Model      |        IP       | PORT |\n");
            printf(" +-----------------------------------------------------------------------------------+");
            read_gateway_list(HMI_conn);
            printf(" \n +-----------------------------------------------------------------------------------+");
            break;
        default:
            break;
    }

    return 0;
}

/*
method search_menu()

Description: this method allows user to look for a device in
    the database.
    Searching menu has four options:
    1. Electrical meters: looks for electrical meter.
    2. Water meter: looks for water meter.
    3. Gateway: looks for gateway.
    4. (Back to main menu):.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::search_menu()
{

    printf("\n +------------ SCHNEIDER DEVICES MANAGER -------------------+\n");
    printf(" |                    Searching Menu                        |\n");
    printf(" | 1. Electricity meters                                    |\n");
    printf(" | 2. Water meters                                          |\n");
    printf(" | 3. Gateway                                               |\n");
    printf(" | 4. (Back to Main Menu)                                   |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What devices do you want to search [1, 2, 3 or 4]: ");

    int action = 0;
    char value[81]={'\0'};

    //Read value to select searching key
    cin.getline(value,80);
    action = atoi(value);

    //Check inserted value
    while(action < 1 | action > 4){

        //Read new value searching key
        printf(" | Please, insert an acceptable value [1, 2, 3 or 4]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    //Depending on searching key selected
    switch(action)
    {
        case 1:
            //Go to electric meter searching menu
            this->search_meter_menu(ELECT_METER_DEVICE);
            break;
        case 2:
            //Go to water meter searching menu
            this->search_meter_menu(WATER_METER_DEVICE);
            break;
        case 3:
            //Go to gateway searching menu
            this->search_gateway_menu();
            break;
        default:
            break;
    }

    return 0;
}

/*
method search_meter_menu(
    int type_dev: variable to indicate kind of device to
        be inserted.
)

Description: this method allows user to look for a meter in
    the database, by selecting the searching key.
    Meter searching menu has four options:
    1. SN: looks for a device by SN.
    2. Brand: looks for a device by brand.
    3. Model: looks for a device by model.
    4. (Back to main menu):.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::search_meter_menu(int type_dev)
{

    meter_device device;
    device.sn = 0;

    //Include meter type in device object
    if(type_dev == ELECT_METER_DEVICE)
        device.type = ELECT_METER_DEVICE;
    else
        device.type = WATER_METER_DEVICE;

    printf("\n +------------ SCHNEIDER DEVICES MANAGER -------------------+\n");
    printf(" |                 Meter Searching Menu                     |\n");
    printf(" | 1. SN                                                    |\n");
    printf(" | 2. Brand                                                 |\n");
    printf(" | 3. Model                                                 |\n");
    printf(" | 4. (Back to Main Menu)                                   |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What key searching do you want to use [1, 2, 3 or 4]: ");

    int action = 0;
    char value[81]={'\0'};

    //Read value to select searching key
    cin.getline(value,80);
    action = atoi(value);

    //Check inserted value
    while(action < 1 | action > 4){
        //Read new value to select searching key
        printf(" | Please, insert an acceptable value [1, 2, 3 or 4]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    //Depending on searching key selected
    switch(action)
    {
        case 1:
            //Read SN of the device
            printf(" | Insert the SN of the device (max lenght 9 digits): ");
            cin.getline(value,9);
            device.sn = atoi(value);

            //Check SN value
            while((device.sn < 1)|(device.sn > 9999999))
            {
                //Read new SN for the device
                printf(" | Please, insert an acceptable SN (max lenght 9 digits) : ");
                cin.getline(value,9);
                device.sn=atoi(value);
            }

            //Go to meter searching menu with SN key
            search_meter_list(HMI_conn, device, 1);

            break;
        case 2:
            //Read brand of the device
            printf(" | Insert the brand of the device (max lenght 15): ");
            cin.getline(device.brand,15);

            //Check if brand is empty
            if(strlen(device.brand) == 0)
                //If were, complete with default value
                sprintf(device.brand,"unknown");

            //Go to meter searching menu with brand key
            search_meter_list(HMI_conn, device, 2);

            break;
        case 3:
            //Read model of the device
            printf(" | Insert the model of the device (max lenght 15): ");
            cin.getline(device.model,15);

            //Check if model is empty
            if(strlen(device.model) == 0)
                //If were, complete with default value
                sprintf(device.model,"unknown");

            //Go to meter searching menu with model key
            search_meter_list(HMI_conn, device, 3);

            break;
        default:
            break;
    }

    return 0;
}

/*
method search_gateway_menu()

Description: this method allows user to look for a meter in
    the database, by selecting the searching key.
    Meter searching menu has four options:
    1. SN: looks for a device by SN.
    2. Brand: looks for a device by brand.
    3. Model: looks for a device by model.
    4. IP: looks for a device by IP.
    5. Port: looks for a device by Port.
    6. (Back to main menu):.

return int action: return the next action to perform in HMI.
*/
int terminal_HMI::search_gateway_menu()
{

    gateway device;
    device.sn = 0;

    printf("\n +------------ SCHNEIDER DEVICES MANAGER -------------------+\n");
    printf(" |                Gateway Searching Menu                    |\n");
    printf(" | 1. SN                                                    |\n");
    printf(" | 2. Brand                                                 |\n");
    printf(" | 3. Model                                                 |\n");
    printf(" | 4. IP                                                    |\n");
    printf(" | 5. Port                                                  |\n");
    printf(" | 6. (Back to Main Menu)                                   |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" | What key searching do you want to use [1, 2, 3, 4, 5 or 6]: ");

    int action = 0;
    char value[81]={'\0'};

    //Read value to select searching key
    cin.getline(value,80);
    action = atoi(value);

    //Check inserted value
    while(action < 1 | action > 6){
        //Read new value to select searching key
        printf(" | Please, insert an acceptable value [1, 2, 3, 4, 5 or 6]: ");
        cin.getline(value,80);
        action = atoi(value);
    }

    switch(action)
    {
        case 1:
            //Read SN of the device
            printf(" | Insert the SN of the device (max lenght 9 digits): ");
            cin.getline(value,81);
            device.sn = atoi(value);

            //Check SN value
            while((device.sn < 1)|(device.sn > 9999999))
            {
                //Read new SN for the device
                printf(" | Please, insert an acceptable SN (max lenght 9 digits) : ");
                cin.getline(value,81);
                device.sn=atoi(value);
            }

            //Go to gateway searching menu with SN key
            search_gateway_list(HMI_conn, device, 1);

            break;
        case 2:
            printf(" | Insert the brand of the device (max lenght 15): ");
            cin.getline(device.brand,81);

            //Check if brand is empty
            if(strlen(device.brand) == 0)
            {
                printf("unknown\n");
                //If were, complete with default value
                sprintf(device.brand,"unknown");
            }

            //Go to gateway searching menu with brand key
            search_gateway_list(HMI_conn, device, 2);

            break;
        case 3:
            printf(" | Insert the model of the device (max lenght 15): ");
            cin.getline(device.model,81);

            //Check if brand is empty
            if(strlen(device.model) == 0)
                //If were, complete with default value
                sprintf(device.model,"unknown");

            //Go to gateway searching menu with model key
            search_gateway_list(HMI_conn, device, 3);

            break;
        case 4:
            //Read IP of the device
            printf(" | Insert the IP of the device: ");
            cin.getline(value,81);

            //Verify that IP format is correct
            while(!(this->check_ip(value)))
            {
                //Read new IP of the device
                printf(" | Insert a valid IP of the device: ");
                cin.getline(value,81);
            }
            strcpy(device.ip,value);

            //Go to gateway searching menu with IP key
            search_gateway_list(HMI_conn, device, 4);

            break;
        case 5:
            //Read Port of the device
            printf(" | Insert the Port of the device (max lenght 4): ");
            cin.getline(value,81);
            device.port=atoi(value);

            //Check Port value
            while((device.port < 1)|(device.port > 9999))
            {
                //Read new Port for the device
                printf(" | Please, insert an acceptable Port (max lenght 4 digits) : ");
                cin.getline(value,81);
                device.port=atoi(value);
            }

            //Go to gateway searching menu with Port key
            search_gateway_list(HMI_conn, device, 5);

            break;
        default:
            break;
    }

    return 0;
}

/*
method check_ip(
    char ip[]: ip to be checked.
)

Description: this method verifies that the ip provided has
    the correct format.

return int check: return the checking process result.
*/
int terminal_HMI::check_ip(char ip[])
{
    int dots[3], j=0;
    char subip[4];

    //Identify dots formats
    for (int i=0;i<15;i++)
    {
        //If char is a dot
        if(ip[i]=='.')
        {
            //Save dot index
            dots[j]=i;
            j++;
        }
    }

    //If there are more or less than 3 dots
    if(j != 3)
        //return format error
        return 0;

    //If there is no number between any dot
    if((dots[0]>=dots[1]) | (dots[1]>=dots[2]) | (dots[2]>=dots[3]) | (dots[0] == 0))
        //return format error
        return 0;

    int value = 0;

    //If first number is higher than 255 or has an alphanumeric digit
    subip[0] = '\0';subip[1]='\0';subip[2]='\0';
    strncpy(subip,ip + 0,dots[0]);
    value = atoi(subip);
    if((value == 0) | (value > 255))
        return 0;

    //If second number is higher than 255 or has an alphanumeric digit
    subip[0]='\0';subip[1]='\0';subip[2]='\0';
    strncpy(subip,ip + dots[0] + 1,dots[1]-dots[0]-1);
    value = atoi(subip);
    if((value == 0) | (value > 255))
        return 0;

    //If third number is higher than 255 or has an alphanumeric digit
    subip[0]='\0';subip[1]='\0';subip[2]='\0';
    strncpy(subip,ip + dots[1] + 1,dots[2]-dots[1]-1);
    value = atoi(subip);
    if((value == 0) | (value > 255))
        return 0;

    //If fourth number is higher than 255 or has an alphanumeric digit
    subip[0]='\0';subip[1]='\0';subip[2]='\0';
    strncpy(subip,ip + dots[2] + 1,strlen(ip)-dots[2]-1);
    value = atoi(subip);
    if((value == 0) | (value > 255))
        return 0;

    return 1;
}

#endif // TERMINAL_HMI_H_INCLUDED
