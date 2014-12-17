#include "db.h"

DB::DB()
{;}

/* Open .idx and .dat*/
bool DB::db_open(const char* pathname)
{

    path_idx = path_dat = pathname;
    path_dat.resize(path_dat.length()-3);
    path_dat.append("dat");
    // 为了在文件不存在时创建
    idx.open(path_idx.c_str(), ios_base::binary|ios_base::in|ios_base::out|ios_base::app);
    dat.open(path_dat.c_str(), ios_base::binary|ios_base::in|ios_base::out|ios_base::app);
    idx.close();
    dat.close();
    // 能够在后面添加空字符的模式
    idx.open(path_idx.c_str(), ios_base::binary|ios_base::in|ios_base::out);
    dat.open(path_dat.c_str(), ios_base::binary|ios_base::in|ios_base::out);
    // Test is valid file, if not, init it
    char is_idx[4];
    idx.seekp(0, ios_base::end);
    if (idx.tellp() > 4)
    {
        idx.seekp(0);
        idx.read(is_idx, 4);
    }
    idx.seekp(0, ios_base::end);
    if (idx.tellp() < 4 || strcmp(is_idx, "idx"))
    {   // head error, init .idx file
        cout << "Init idx file" << endl;
        idx.seekp(0);
        char temp_idx_head[] = "idx";
        idx.write(temp_idx_head, 4);
        int temp_hash_offset = HASH_OFFSET;
        int temp_hash_bucket = HASH_BUCKET;
        int temp_hash_unit_len = HASH_UNIT_LEN;
        idx.write(reinterpret_cast<char*>(&temp_hash_offset), 4);
        idx.write(reinterpret_cast<char*>(&temp_hash_bucket), 4);
        idx.write(reinterpret_cast<char*>(&temp_hash_unit_len), 4);
        db_idx_alloc(HASH_BUCKET * HASH_UNIT_LEN);
        dat.seekp(0);
        char temp_dat_head[] = "dat";
        dat.write(temp_dat_head, 4);
        dat.seekp(DAT_HEAD_LEN - 1);
        dat.put('\0');
        idx.close();
    }
    return true;    // open success
}


/* Close .idx and .dat */
bool DB::db_close()
{
    idx.close();
    dat.close();
    return true;    // close success
}

/* Refresh Disk */
void DB::db_refresh()
{
    db_close();
    db_open(FILE_PATH);
}



/*
 * In .dat, alloc a size to use
 * return alloc's begin pos
 */
int DB::db_dat_alloc(int size)
{
    dat.seekp(0, ios_base::end);
    int pos_begin = dat.tellp();
    dat.seekp(pos_begin + size - 1);
    dat.put('\0');
    return pos_begin;
}

/*
 * In. idx, alloc a size to use
 * return alloc's begin pos
 */
int DB::db_idx_alloc(int size)
{
    idx.seekp(0, ios_base::end);
    int pos_begin = idx.tellp();
    idx.seekp(pos_begin + size - 1);
    idx.put('\0');
    return pos_begin;
}

/*
 * input data key pos and key name, write key name and link idx to it,
 * return success(true) or fail(false)
 */
bool DB::db_link_idx_key(int key_pos, string key_name)
{
    // 先保证了没有重复的key_name
    int bucket_pos = db_hashCode(key_name) * HASH_UNIT_LEN + HASH_OFFSET;
    int temp_value_1 = db_idx_get_1st_4byte(bucket_pos);
    int temp_value_2 = db_idx_get_2nd_4byte(bucket_pos);
    if (temp_value_1 == 0)
    {
        db_idx_write_1st_4byte(bucket_pos, key_pos);
        return true;
    }
    else
    {
        while(true)
        {
            if (temp_value_2 == 0)
            {
                int save_pos = bucket_pos;
                bucket_pos = db_idx_alloc(HASH_UNIT_LEN);
                db_idx_write_1st_4byte(bucket_pos, key_pos);
                db_idx_write_2nd_4byte(save_pos, bucket_pos);
                return true;
            }
            else
            {
                bucket_pos = temp_value_2;
                temp_value_2 = db_idx_get_2nd_4byte(bucket_pos);
            }
        }
    }
}

/* write to .dat */
void DB::db_dat_write_int(int pos, int value)
{
    dat.seekp(pos);
    dat.write(reinterpret_cast<char*>(&value), 4);
    dat.seekp(pos);
}

void DB::db_dat_write_string(int pos, string input, int length)
{
    dat.seekp(pos);
    string temp_input = input + '\0';
    dat.write(temp_input.c_str(), length);
    dat.seekp(pos);
}

/* read in .dat*/
int DB::db_dat_read_int(int pos)
{
    dat.seekp(pos);
    int value = 0;
    dat.read(reinterpret_cast<char*>(&value), 4);
    dat.seekp(pos);
    return value;
}

string DB::db_dat_read_string(int pos, int length)
{
    dat.seekp(pos);
    char temp_string[length];
    dat.read(temp_string, length);
    dat.seekp(pos);
    string return_str(temp_string);
    if (return_str.length() > length)
        return return_str.substr(0, length);
    else
        return return_str;
}



/* get byte in .idx */
int DB::db_idx_get_1st_4byte(int pos)
{
    idx.seekp(pos);
    int value = 0;
    idx.read(reinterpret_cast<char*>(&value), 4);
    idx.seekp(pos);
    return value;
}

int DB::db_idx_get_2nd_4byte(int pos)
{
    idx.seekp(pos+4);
    int value = 0;
    idx.read(reinterpret_cast<char*>(&value), 4);
    idx.seekp(pos);
    return value;
}

/* write by int .idx */
void DB::db_idx_write_1st_4byte(int pos, int value)
{
    idx.seekp(pos);
    idx.write(reinterpret_cast<char*>(&value), 4);
    idx.seekp(pos);
}

void DB::db_idx_write_2nd_4byte(int pos, int value)
{
    idx.seekp(pos + 4);
    idx.write(reinterpret_cast<char*>(&value), 4);
    idx.seekp(pos);
}


/* get hash value */
int DB::db_hashCode(string key)
{
    int hash = 0;
    for (unsigned int i = 0; i < key.length(); ++i)
        hash += (HASH_SEED << i) * int(key[i]) * (i+1);
    return (hash & HASH_MASK) % HASH_BUCKET;
}













