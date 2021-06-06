#ifndef STRUCT_DEF_H_INCLUDED
#define STRUCT_DEF_H_INCLUDED

#define WATER_METER_DEVICE 001
#define ELECT_METER_DEVICE 002


struct meter_device
{
    uint8_t type;
    uint32_t id;
    uint32_t sn;
    char brand[64];
    char model[64];
}typedef meter_device;

struct gateway
{
    uint32_t id;
    uint32_t sn;
    char brand[64];
    char model[64];
    char ip[16];
    uint16_t port;
}typedef gateway;

#endif // STRUCT_DEF_H_INCLUDED
