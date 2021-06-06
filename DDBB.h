#ifndef MYSQL_H_INCLUDED
#define MYSQL_H_INCLUDED
    #include "mysql\mysqlheaders\mysql.h"
#endif // MYSQL_H_INCLUDED

#ifndef DDBB_H_INCLUDED
#define DDBB_H_INCLUDED

//DATA BASE GENERAL FUNCTIONS

MYSQL* DDBB_connection(const char*, const char*, const char*, const char*, unsigned int, const char*, unsigned long);

int _DDBB_insert(MYSQL* , const char*);

MYSQL_RES* _DDBB_request(MYSQL* , const char*);

// INSERTING FUNCTIONS

MYSQL_RES* _check_meter(MYSQL* , meter_device);

MYSQL_RES* _check_gateway(MYSQL* , gateway);

MYSQL_RES* _last_elect_meter(MYSQL*);

MYSQL_RES* _last_water_meter(MYSQL*);

MYSQL_RES* _last_gateway(MYSQL*);

int insert_meter_list(MYSQL* conn, meter_device);

int insert_gateway_list(MYSQL* conn, gateway);

// READING FUNCTIONS

void read_elect_list(MYSQL*);

void read_water_list(MYSQL*);

void read_gateway_list(MYSQL*);

// SEARCHING FUNCTIONS

void search_meter_list(MYSQL* , meter_device, int);

void search_gateway_list(MYSQL* , gateway, int);

#endif // DDBB_H_INCLUDED
