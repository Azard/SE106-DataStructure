#ifndef DB_H
#define DB_H

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

#define FILE_PATH "data.idx"

#define HASH_SEED 701
#define HASH_OFFSET 16
#define HASH_BUCKET 4
#define HASH_UNIT_LEN 8
#define HASH_MASK unsigned(-1) >> 1

#define DAT_HEAD_LEN 16

using namespace std;


/* Data Base System Class */
class DB
{
public:
    /* public method */
    DB();
    bool db_open(const char* pathname);
    bool db_close();
    void db_refresh();
    int db_dat_alloc(int size);
    int db_idx_alloc(int size);
    bool db_link_idx_key(int key_pos, string key_name);
    void db_dat_write_int(int pos, int value);
    void db_dat_write_string(int pos, string input, int length);
    int db_dat_read_int(int pos);
    string db_dat_read_string(int pos, int length);


    int db_idx_get_1st_4byte(int pos);
    int db_idx_get_2nd_4byte(int pos);
    void db_idx_write_1st_4byte(int pos, int value);
    void db_idx_write_2nd_4byte(int pos, int value);
    int db_hashCode(string key);

private:
    /* private variable*/
    string path_dat;
    string path_idx;
    fstream idx;
    fstream dat;
};



#endif // DB_H
