#include <iostream>
#include "HiredisApi.h"
#include <list>

using namespace std;

int main()
{

    HiredisApi hiRedis;
    hiRedis.hiredis_getValue("xiaozhaozhao");
    cout<<string(hiRedis.reply->str)<<endl;

    list<string> temp = hiRedis.hiredis_getSList("xiaopengyou");
    for (auto it=temp.begin();it!= temp.end();it++)
    {
     cout<<*it<<endl;   
    }
    return 0;
}

