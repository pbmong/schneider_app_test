/*

*/

#include <iostream>
#include <windows.h>
#include <string.h>

#ifndef MYSQL_H_INCLUDED
#define MYSQL_H_INCLUDED
    #include "mysql\mysqlheaders\mysql.h"
#endif // MYSQL_H_INCLUDED

#ifndef DEVICES_STRUCT_H
#define DEVICES_STRUCT_H
    #include "devices.h"
#endif // DEVICES_STRUCT_H


//DATA BASE GENERAL FUNCTIONS

/*
function DDBB_connection(
    const char* hostname: name of the connection host.
    const char* username: access user name.
    const char* password: access password for the user.
    const char* database: name of the database to access.
    unsigned int port: access port for the connection.
    const char* unixshocket:
    unsigned long clientflag:
)

Description: this function configures a database connection
    thought MySQL library and returns the object database
    connection to be used.

return MYSQL* conn: return of the connection object prepared.

*/
MYSQL* DDBB_connection(const char* hostname, const char* username, const char* password, const char* database,unsigned int port, const char* unixshocket, unsigned long clientflag)
{
    MYSQL* conn;

    //Configure and initialize connection
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixshocket, clientflag);

    return conn;
}

/*
function _DDBB_insert(
    MYSQL* conn: database connection object.
    const char* q: inserting query.
)

Description: this function performs an insertion query to the
    database and receives the response.

return int qstate: variable to check result of the query.
*/
int _DDBB_insert(MYSQL* conn, const char* q)
{
    int qstate = 0;

    //Execute insertion query
    qstate = mysql_query(conn,q);

    return qstate;
}

/*
function _DDBB_request(
    MYSQL* conn: database connection object.
    const char* q: request query.
)

Description: this function performs a request to the database
    and returns all the information received.

return MYSQL_RES* res: structure with the request result.
*/
MYSQL_RES* _DDBB_request(MYSQL* conn, const char* q)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn)
    {
        //Execute request query
        int qstate = mysql_query(conn, q);
        if(!qstate)
        {
            res = mysql_store_result(conn);res;
            int count = mysql_num_fields(res);
        }
    }

    //return query result
    return res;
}

// INSERTING FUNCTIONS

/*
function _check_meter(
    MYSQL* conn: database connection object.
    meter_device device: meter to be looked for in the database.
)

Description: this function checks if the meter already exist
    in the database and returns its data if were.

return MYSQL_RES* res: structure with the request result if were:
*/
MYSQL_RES* _check_meter(MYSQL* conn, meter_device device)
{
    char q1[300];

    //Generate query
    if (device.type == ELECT_METER_DEVICE)
        sprintf(q1,"SELECT * FROM elec_meter_list WHERE sn='%d'",device.sn);
    else if(device.type == WATER_METER_DEVICE)
        sprintf(q1,"SELECT * FROM water_meter_list WHERE sn='%d'",device.sn);

    //Execute request
    return _DDBB_request(conn,q1);
}

/*
function _check_gateway(
    MYSQL* conn: database connection object.
    gateway device: gatewat to be looked for in the database.
)

Description: this function checks if the device already exist
    in the database and returns its data if were.

return MYSQL_RES* res: structure with the request result if were:
*/
MYSQL_RES* _check_gateway(MYSQL* conn, gateway device)
{
    char q1[300];

    //Generate query
    sprintf(q1,"SELECT * FROM gateway_list WHERE sn='%d'",device.sn);

    //Execute request
    return _DDBB_request(conn,q1);
}

/*
function(
    MYSQL* conn: database connection object.
)

Description: this function requests for the last electric
    metering device in the database.

return MYSQL_RES* res: structure with the last device data:
*/
MYSQL_RES* _last_elect_meter(MYSQL* conn)
{
    //Execute electric last meter request
    return _DDBB_request(conn,"SELECT * FROM elec_meter_list order by id desc");
}

/*
function(
    MYSQL* conn: database connection object.
)

Description: this function requests for the last water metering
    device in the database.

return MYSQL_RES* res: structure with the last device data:
*/
MYSQL_RES* _last_water_meter(MYSQL* conn)
{
    //Execute water last meter request
    return _DDBB_request(conn,"SELECT * FROM water_meter_list order by id desc");
}

/*
function(
    MYSQL* conn: database connection object.
)

Description: this function requests for the last gateway in the database.

return MYSQL_RES* res: structure with the last device data:
*/
MYSQL_RES* _last_gateway(MYSQL* conn)
{
    //Execute last gateway request
    return _DDBB_request(conn,"SELECT * FROM gateway_list order by id desc");
}

/*
function insert_meter_list(
    MYSQL* conn: database connection object.
    meter_device device: meter object to be inserted.
)

Description: this function inserts a meter in the database.

return int qstate: variable to check result of the query.
*/
int insert_meter_list(MYSQL* conn, meter_device device)
{
    //Verify that meter doesn´t already exist in database
    MYSQL_RES* res = _check_meter(conn, device);
    MYSQL_ROW row;
    if(row = mysql_fetch_row(res))
        return 2;

    //Get unique id for meter
    if (device.type == ELECT_METER_DEVICE)
        res = _last_elect_meter(conn);
    else if(device.type == WATER_METER_DEVICE)
        res = _last_water_meter(conn);

    if(row = mysql_fetch_row(res))
        device.id = atoi(row[0])+1;
    else
        device.id = 1;

    //Insert meter in DDBB
    char q1[300],q2[100];

    if (device.type == ELECT_METER_DEVICE)
        sprintf(q1,"INSERT INTO elec_meter_list (id,sn,brand,model) VALUES ('%d','%d'",device.id,device.sn);
    else if(device.type == WATER_METER_DEVICE)
        sprintf(q1,"INSERT INTO water_meter_list (id,sn,brand,model) VALUES ('%d','%d'",device.id,device.sn);

    sprintf(q2,",'%s','%s')",device.brand,device.model);
    strcat(q1,q2);

    //Execute insertion query
    return _DDBB_insert(conn,q1);
}

/*
function insert_gateway_list(
    MYSQL* conn: database connection object.
    gateway device: gateway object to be inserted.
)

Description: this function inserts a meter in the database.

return int qstate: variable to check result of the query.
*/
int insert_gateway_list(MYSQL* conn, gateway device)
{
    //Verify that gateway doesn´t already exist
    MYSQL_RES* res = _check_gateway(conn, device);
    MYSQL_ROW row;
    if(row = mysql_fetch_row(res))
        return 2;

    //Get unique id for gateway
    res = _last_gateway(conn);

    if(row = mysql_fetch_row(res)){
        device.id = atoi(row[0])+1;
    }else
        device.id = 1;

    //Insert gateway in DDBB
    char q1[300],q2[100],q3[100];

    sprintf(q1,"INSERT INTO gateway_list (id,sn,brand,model,ip,port) VALUES ('%d','%d'",device.id,device.sn);
    sprintf(q2,",'%s','%s'",device.brand,device.model);
    sprintf(q3,",'%s','%d')",device.ip,device.port);

    strcat(q1,q2);
    strcat(q1,q3);

    //Execute insertion query
    return _DDBB_insert(conn,q1);
}

// READING FUNCTIONS

/*
function read_elect_list(
    MYSQL* conn: database connection object.
)

Description: this function reads all the electric
    metering devices and shows it by the terminal.

return void:
*/

void read_elect_list(MYSQL* conn)
{
    //Execute request query
    MYSQL_RES* res = _DDBB_request(conn,"SELECT * FROM elec_meter_list");

    //Show electric meters information
    int count = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        printf("\n | %-7s | %-10s | %-15s | %-15s |",row[0],row[1],row[2],row[3]);
    }
    return;
}

/*
function read_water_list(
    MYSQL* conn: database connection object.
)

Description: this function reads all the water
    metering devices and shows it by the terminal.

return void:
*/

void read_water_list(MYSQL* conn)
{
    //Execute request query
    MYSQL_RES* res = _DDBB_request(conn,"SELECT * FROM water_meter_list");

    //Show electric meters information
    int count = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        printf("\n | %-7s | %-10s | %-15s | %-15s |",row[0],row[1],row[2],row[3]);
    }
    return;
}

/*
function read_gateway_list(
    MYSQL* conn: database connection object.
)

Description: this function reads all the gateways
    and shows it by the terminal.

return void:
*/

void read_gateway_list(MYSQL* conn)
{
    //Execute request query
    MYSQL_RES* res = _DDBB_request(conn,"SELECT * FROM gateway_list");

    //Show electric meters information
    int count = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        printf("\n | %-7s | %-10s | %-15s | %-15s | %-15s | %-4s |",row[0],row[1],row[2],row[3],row[4],row[5]);
    }
    return;
}

// SEARCHING FUNCTIONS

/*
function search_meter_list(
    MYSQL* conn: database connection object.
    meter_device device: meter to be searched in the database.
    int key: searching key selected for the request.
)

Description: this function looks for a meter device in the
    device and shows its information by the terminal.

return :
*/

void search_meter_list(MYSQL* conn, meter_device device,int key)
{
    char q[300],meter_list[30];

    //Check type of meter
    if (device.type == ELECT_METER_DEVICE)
        sprintf(meter_list,"elec_meter_list");
    else if(device.type == WATER_METER_DEVICE)
        sprintf(meter_list,"water_meter_list");

    //Generate query depending on searching key
    switch(key){
    case 1:
        sprintf(q,"SELECT * FROM %s WHERE sn='%d'",meter_list,device.sn);
        break;
    case 2:
        sprintf(q,"SELECT * FROM %s WHERE brand='%s'",meter_list,device.brand);
        break;
    case 3:
        sprintf(q,"SELECT * FROM %s WHERE model='%s'",meter_list,device.model);
        break;
    default:
        sprintf(q,"SELECT * FROM elec_meter_list");
        break;
    }

    //Execute request query
    MYSQL_RES* res = _DDBB_request(conn,q);

    //Show meters information
    printf("\n +----------------------------------------------------------+\n");
    printf(" |                      Meters List                         |\n");
    printf(" +----------------------------------------------------------+\n");
    printf(" |    ID   |     SN     |      Brand      |      Model      |\n");
    printf(" +----------------------------------------------------------+");

    int count = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        printf("\n | %-7s | %-10s | %-15s | %-15s |",row[0],row[1],row[2],row[3]);
    }
    printf("\n +----------------------------------------------------------+\n");

    return;
}

/*
function search_gateway_list(
    MYSQL* conn: database connection object.
    gateway device: gateway to be searched in the database.
    int key: searching key selected for the request.
)

Description: this function looks for a meter device in the
    device and shows its information by the terminal.

return :
*/
void search_gateway_list(MYSQL* conn, gateway device,int key)
{
    char q[300];

    //Generate query depending on searching key
    switch(key){
    case 1:
        sprintf(q,"SELECT * FROM gateway_list WHERE sn='%d'",device.sn);
        break;
    case 2:
        sprintf(q,"SELECT * FROM gateway_list WHERE brand='%s'",device.brand);
        break;
    case 3:
        sprintf(q,"SELECT * FROM gateway_list WHERE model='%s'",device.model);
        break;
    case 4:
        sprintf(q,"SELECT * FROM gateway_list WHERE ip='%s'",device.ip);
        break;
    case 5:
        sprintf(q,"SELECT * FROM gateway_list WHERE port='%d'",device.port);
        break;
    default:
        sprintf(q,"SELECT * FROM gateway_list");
        break;
    }

    //Execute request query
    MYSQL_RES* res = _DDBB_request(conn,q);

    //Show meters information
    printf("\n +-----------------------------------------------------------------------------------+\n");
    printf(" |                                  Gateway List                                     |\n");
    printf(" +-----------------------------------------------------------------------------------+\n");
    printf(" |    ID   |     SN     |      Brand      |      Model      |        IP       | PORT |\n");
    printf(" +-----------------------------------------------------------------------------------+");

    int count = mysql_num_fields(res);
    MYSQL_ROW row;
    while(row = mysql_fetch_row(res)){
        printf("\n | %-7s | %-10s | %-15s | %-15s | %-15s | %-4s |",row[0],row[1],row[2],row[3],row[4],row[5]);
    }
     printf("\n +-----------------------------------------------------------------------------------+\n");

    return;
}
