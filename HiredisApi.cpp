#include "HiredisApi.h"
list<string> HiredisApi::hiredis_getSList(string key)
{
    list<string> varl;
    int j;
    reply =(redisReply*) redisCommand(c,"LRANGE %s 0 -1",key.c_str());
    if (reply->type == REDIS_REPLY_ARRAY) {
        int num = reply->elements;
        for (j = 0; j < num; j++) {
            varl.push_back(string(reply->element[j]->str));
        }
    }
    return varl;
}

void HiredisApi::hiRedis_delKey(string key)
{
    /* Create a list of numbers, from 0 to 9 */
    reply =(redisReply*) redisCommand(c,"DEL %s",key.c_str());
    freeReplyObject(reply);
}

void HiredisApi::hiredis_createSList(string key,list<string> &sList)
{
    hiRedis_delKey(key);
    for(auto it = sList.begin();it != sList.end(); it++)
        reply =(redisReply*) redisCommand(c,"LPUSH %s %s", key.c_str(),(*it).c_str());
}


void HiredisApi::hiredis_setBinary(string key,string val)
{
    /* Set a key using binary safe API */
    reply =(redisReply*) redisCommand(c,"SET %b %b", key.c_str(), (size_t) key.size(), val.c_str(), (size_t) val.size());
}

void HiredisApi::hiredis_couter(string key/*="counter"*/)
{
    reply =(redisReply*) redisCommand(c,"INCR %s",key.c_str());
}

void HiredisApi::hiredis_getValue(string key)
{
    reply =(redisReply*) redisCommand(c,"GET %s",key.c_str());
}

void  HiredisApi::hiredis_setData(string key,string val)
{
    /* Set a key */
    reply =(redisReply*) redisCommand(c,"SET %s %s", key.c_str(), val.c_str());
}


#if 0
    /* Set a key */
    reply =(redisReply*) redisCommand(c,"SET %s %s", "foo", "hello world");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    /* Try a GET and two INCR */
    reply =(redisReply*) redisCommand(c,"GET foo");
    printf("GET foo: %s\n", reply->str);
    freeReplyObject(reply);

    /* again ... */
    reply =(redisReply*) redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    /* Set a key using binary safe API */
    reply =(redisReply*) redisCommand(c,"SET %b %b", "bar", (size_t) 3, "hello", (size_t) 5);
    printf("SET (binary API): %s\n", reply->str);
    freeReplyObject(reply);

    /* Create a list of numbers, from 0 to 9 */
    reply =(redisReply*) redisCommand(c,"DEL mylist");
    freeReplyObject(reply);

    unsigned int j;
    for (j = 0; j < 10; j++) {
        char buf[64];
        snprintf(buf,64,"%u",j);
        reply =(redisReply*) redisCommand(c,"LPUSH mylist element-%s", buf);
        freeReplyObject(reply);
    }
    /* Let's check what we have inside the list */
    reply =(redisReply*) redisCommand(c,"LRANGE %s 0 -1",key.c_str());
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (j = 0; j < reply->elements; j++) {
            printf("%u) %s\n", j, reply->element[j]->str);
        }
    }

    /* Disconnects and frees the context */
    redisFree(c);

#endif


HiredisApi::~HiredisApi()
{
    if(reply != NULL)
    freeReplyObject(reply);
    if(c != NULL)
    redisFree(c);
}
HiredisApi::HiredisApi()
{
    m_info.info_ip = "127.0.0.1";
    m_info.info_port = 6379;
    // 初始化hiredis;
    initHiredis();
}


void HiredisApi::initHiredis()
{
    const char *hostname = const_cast<char*>(m_info.info_ip.c_str());
    int port = m_info.info_port;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
    /* PING server */
    reply =(redisReply*) redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

}

