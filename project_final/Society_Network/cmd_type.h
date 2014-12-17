#ifndef CMD_TYPE_H
#define CMD_TYPE_H

/* This class is use for passing command */

#include <string>
using namespace std;

// 1: help -h
// 10: login
enum Command_Operate{help=1, quit=2, reg=3, cls=4, infor=5,change=6, del=7,
                     follow=8, unfollow = 9, flist=10, bflist=11, cd=12, speak=13, ls=14, lsi=15,
                     spfind=16, recommand=17, login=20, logout=21};

//
enum Command_Data{};

class Cmd_Type
{
private:
    bool valid;             // is this instruction array valid ?
    int command_operate;    // command 1st argv
    string command_data;    // command 2nd argv

public:
    Cmd_Type();
    void init();
    void set_valid(bool);
    bool is_valid();
    bool is_empty();
    void add_operate(int _command_operate);
    void add_data(string _command_data);
    int get_operate();
    string get_data();
};

#endif // CMD_TYPE_H
