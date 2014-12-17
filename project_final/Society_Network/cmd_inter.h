#ifndef CMD_INTER_H
#define CMD_INTER_H

//改 ID_LENGTH 记得改 DB::db_find_key
#define USER_ID_LENGTH 15
#define USER_EXIST_LENGTH  1
#define USER_PASSWORD_LENGTH 32
#define USER_NAME_LENGTH 16
#define USER_SEX_LENGTH 4
#define USER_BIRTHYEAR_LENGTH 4
#define USER_BIRTHMONTH_LENGTH 4
#define USER_BIRTHDAY_LENGTH 4
#define USER_HOMETOWN_LENGTH 32
#define USER_PHONE_LENGTH 16
#define USER_FOLLOW_POINTER 4
#define USER_BE_FOLLOW_POINTER 4
#define USER_SPEAK_HEAD 4
#define USER_SPEAK_TAIL 4

#define USER_SUM_LENGTH USER_ID_LENGTH+USER_EXIST_LENGTH+USER_PASSWORD_LENGTH+USER_NAME_LENGTH+USER_SEX_LENGTH+USER_BIRTHYEAR_LENGTH+USER_BIRTHMONTH_LENGTH+USER_BIRTHDAY_LENGTH+USER_HOMETOWN_LENGTH+USER_PHONE_LENGTH+USER_FOLLOW_POINTER+USER_BE_FOLLOW_POINTER+USER_SPEAK_HEAD+USER_SPEAK_TAIL

#define MES_EXIST_LENGTH 4
#define MES_PRE_LENGTH 4
#define MES_BACK_LENGTH 4
#define MES_TIME_LENGTH 24
#define MES_NAME_LENGTH 16
#define MES_ORIGIN_LENGTH 4
#define MES_BE_TRANS_TIMES_LENGTH 4
#define MES_BE_TRANS_POINTER 4
#define MES_BODY_LENGTH 280

#define MES_SUM_LENGTH MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH + MES_BE_TRANS_POINTER + MES_BODY_LENGTH

#define ONCE_MAX_MESSAGE 5

/* This class use for command line interaction */

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <sstream>
#include "cmd_type.h"
#include "db.h"
using namespace std;

class Cmd_Inter
{
private:
    string input;       // line input string
    Cmd_Type cmd_type;  // save analysed input command
    DB* db;             // database object
    int id_pos;         // 登陆的账号的 key_pos
    string id_name;     // 登陆的账号的 ID
    int cd_pos;         // 查看的账号的 pos
    string cd_name;     // 查看的账号的 ID

    void run();         // circle run this command interaction
    void getInput();    // get input after ">"
    void execute();     // call really execute instruction

    // really execute instruction
    void exe_help();
    void exe_quit();
    void exe_register();
    void exe_login();
    void exe_cls();
    void exe_infor();
    void exe_change();
    void exe_del();
    void exe_follow();
    void exe_unfollow();
    void exe_flist();
    void exe_bflist();
    void exe_cd();
    void exe_speak();
    void exe_ls();
    void exe_lsi();
    void exe_logout();
    void exe_spfind();
    void exe_recommand();

    // private help function
    void write_id(int begin_pos, string id);
    void write_exist(int begin_pos, string exist);
    void write_password(int begin_pos, string password);
    void write_name(int begin_pos, string name);
    void write_sex(int begin_pos, int sex);
    void write_birth_year(int begin_pos, int year);
    void write_birth_month(int begin_pos, int month);
    void write_birth_day(int begin_pos, int day);
    void write_hometown(int begin_pos, string hometown);
    void write_phone(int begin_pos, string phone);
    void write_follow(int begin_pos, string id);
    void write_be_follow(int begin_pos, string id);
    void write_speak_head(int begin_pos, int val);
    void write_speak_tail(int begin_pos, int val);
    int write_message(int begin_pos, string message);
    void write_mes_exist(int mes_pos, int val);
    void write_mes_pre(int mes_pos, int val);
    void write_mes_back(int mes_pos, int val);
    void write_mes_time(int mes_pos);
    void write_mes_name(int mes_pos, string name);
    void write_mes_origin(int mes_pos, int val);
    void write_mes_trans_times(int mes_pos, int val);
    void write_mes_trans_pointer(int mes_pos, int val);
    void write_mes_body(int mes_pos, string message);


    string get_id(int begin_pos);
    string get_exist(int begin_pos);
    string get_password(int begin_pos);
    string get_name(int begin_pos);
    int get_sex(int begin_pos);
    int get_year(int begin_pos);
    int get_month(int begin_pos);
    int get_day(int begin_pos);
    string get_hometown(int begin_pos);
    string get_phone(int begin_pos);
    int get_follow_pointer(int begin_pos);
    int get_be_follow_pointer(int begin_pos);
    int get_speak_head_pointer(int begin_pos);
    int get_speak_tail_pointer(int begin_pos);


    int get_mes_exist(int mes_pos);
    int get_mes_pre_pointer(int mes_pos);
    int get_mes_back_pointer(int mes_pos);
    vector<int> get_mes_time(int mes_pos);
    string get_mes_name(int mes_pos);
    int get_mes_origin(int mes_pos);
    int get_mes_trans_times(int mes_pos);
    int get_mes_trans_pointer(int mes_pos);
    string get_mes_body(int mes_pos);


    vector<int> get_one_s_message(int begin_pos); //返回消息们的头指针
    bool time_compare_left_pre_than_right(vector<int>& left, vector<int>& right);
    void sort_message(vector<int>& save_message_pointer); //根据时间排序
    void trans_message(int ori_mes_pos); //转发
    void delete_message(int mes_pos); //迭代删除，包括被转发的
    void fold_message(vector<int>& save_message_pointer); // 折叠消息

    int find_key(string key_name);
    vector<int> get_all_id_pos();



public:
    Cmd_Inter(DB* input_db);
    void start();

    void test_01();
    void test_02();
    void test_03();
    void test_04();
};

#endif // CMD_INTER_H
