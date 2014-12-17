#include <iostream>
#include <string>
#include <fstream>
#include "cmd_inter.h"
#include "db.h"

using namespace std;
int main()
{

    DB db;
    db.db_open(FILE_PATH);
    db.db_close();
    Cmd_Inter cmd_inter(&db);


    /* 运行测试的话，注释掉第一行，接触注释对应的测试函数，具体测试内容参见cmd_inter.cpp */
    cmd_inter.start();
    //cmd_inter.test_01();
    //cmd_inter.test_02();
    //cmd_inter.test_03();
    //cmd_inter.test_04();

    return 0;
}

