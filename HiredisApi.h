#pragma once
#include <iostream>
#include <hiredis/hiredis.h>
#include <list>

using namespace std;

struct RedisInfo{
    string info_ip;
    unsigned short info_port;
};

class HiredisApi
{
public: HiredisApi();
    ~HiredisApi();
    int hiredis_Api();
    void hiRedis_delKey(string key);
    void hiredis_getValue(string key);
    void hiredis_setData(string key,string val);
    void hiredis_couter(string key="counter");
    void hiredis_setBinary(string key,string val);
    void hiredis_createSList(string key,list<string> &sList);
    list<string> hiredis_getSList(string key);
private:
    // 初始化hiredis
    void initHiredis();
private:
    RedisInfo m_info;
    redisContext *c = NULL;
public:
    redisReply *reply = NULL;


};

