#include "cmd_inter.h"

Cmd_Inter::Cmd_Inter(DB* input_db)
{
    db = input_db;
    db->db_open(FILE_PATH);
    id_pos = 0;
    id_name = "";
    cd_pos = 0;
    cd_name = "";
}

/*  This function show welcome interface and use run function */
void Cmd_Inter::start()
{
    cout << endl;
    cout << "                   ***********************************\n";
    cout << "                   *** Welcome to New Social World ***\n";
    cout << "                   ***********************************\n";
    cout << "                                                            Powered by Azard\n\n";
    cout << "input h for help\n\n";

    run();
}

/*  This function is main loop */
void Cmd_Inter::run()
{
    while(true)
    {
        db->db_refresh();
        getInput();     // analyse input and splite save into cmd_type
        if (cmd_type.is_empty())
            ;
        else if (!cmd_type.is_valid())
            cout << "invalid input\n";
        execute();
    }
}

/*  This function get input and analyse
 *  set cmd_type and let execute function read it
 */
void Cmd_Inter::getInput()
{
    cin.sync();
    cout << endl << id_name << "> ";
    if (cd_pos != 0)
        cout << cd_name << "> ";
    cmd_type.init();
    getline(cin, input);
    vector<string> split_input; // save splited input string
    // Split input string, save in vector<string>::split_input
    int start_pos = 0;
    int end_pos = 0;
    while(true)
    {
        start_pos = input.find_first_not_of(" ",end_pos);
        if (start_pos == -1)
            break;
        end_pos = input.find_first_of(" ", start_pos);
        if (end_pos == -1)
        {
            split_input.push_back(input.substr(start_pos, input.size()-start_pos));
            break;
        }
        split_input.push_back(input.substr(start_pos, end_pos-start_pos));
    }

    // Analyse input string
    if (split_input.size() >= 1)    // Analyse the first position command
    {
        string command = split_input[0];
        if (command == "help" || command == "h")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'help\' not support this operate\n";
            else    // Excute "help" and "h"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(help);
            }
        }

        else if (command == "quit")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'quit\' not support this operate\n";
            else    // Excute "quit"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(quit);
            }
        }

        else if (command == "login")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'login\' not support this operate\n";
            else    // Excute "login"
            {
                if (id_name != "")
                {
                    cout << "please logout.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(login);
            }
        }

        else if (command == "register")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'register\' not support this operate\n";
            else    // Excute "register"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(reg);
            }
        }

        else if (command == "cls")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'cls\' not support this operate\n";
            else    // Excute "cls"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(cls);
            }
        }

        else if (command == "infor")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'infor\' not support this operate\n";
            else    // Excute "infor"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(infor);
            }
        }

        else if (command == "logout")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'logout\' not support this operate\n";
            else    // Excute "logout"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(logout);
            }
        }

        else if (command == "change")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'change\' not support this operate\n";
            else    // Excute "change"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(change);
            }
        }

        else if (command == "del")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'del\' not support this operate\n";
            else    // Excute "del"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(del);
            }
        }

        else if (command == "spfind")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'spfind\' not support this operate\n";
            else    // Excute "spfind"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(spfind);
            }
        }

        else if (command == "recommand")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'recommand\' not support this operate\n";
            else    // Excute "recommand"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(recommand);
            }
        }

        else if (command == "follow")
        {
            if (split_input.size() != 2) // Error handle
                cout << "Error: \'follow\' not support this operate\n";
            else    // Excute "follow"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(follow);
                cmd_type.add_data(split_input[1]);
            }
        }

        else if (command == "unfollow")
        {
            if (split_input.size() != 2) // Error handle
                cout << "Error: \'unfollow\'not support this operate\n";
            else    // Execute "unfollow"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(unfollow);
                cmd_type.add_data(split_input[1]);
            }
        }

        else if (command == "flist")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'flist\' not support this operate\n";
            else    // Excute "flist"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(flist);
            }
        }

        else if (command == "bflist")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'bflist\' not support this operate\n";
            else    // Excute "bflist"
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(bflist);
            }
        }

        else if (command == "cd")
        {
            if (split_input.size() != 2) // Error handle
                cout << "Error: \'cd\' not support this operate\n";
            else    // Excute "cd"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(cd);
                cmd_type.add_data(split_input[1]);
            }
        }

        else if (command == "speak")
        {
            if (split_input.size() > 1) // Error handle
                cout << "Error: \'speak\' not support this operate\n";
            else    // Excute "speak"
            {
                if (id_name == "")
                {
                    cout << "not login a ID.\n";
                    return;
                }
                cmd_type.set_valid(true);
                cmd_type.add_operate(speak);
            }
        }

        else if (command == "ls")
        {
            if (id_name == "")
            {
                cout << "not login a ID.\n";
                return;
            }
            if (split_input.size() == 2 && split_input[1] == "-i")
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(lsi);
            }
            else if (split_input.size() == 1)
            {
                cmd_type.set_valid(true);
                cmd_type.add_operate(ls);
            }
            else
                cout << "Error: \'ls\' not support this operate\n";
        }

        else
            cout << "\'" << split_input[0] << "\'" << "is not valid command operate\n";
    }

    return;
}


/* Interface    up*/





/* Kernel       down */


/*  This function call really execute instruction */
void Cmd_Inter::execute()
{
    switch (cmd_type.get_operate())
    {
    case help:
        exe_help();
        break;
    case quit:
        exe_quit();
        break;
    case reg:
        exe_register();
        break;
    case cls:
        exe_cls();
        break;
    case infor:
        exe_infor();
        break;
    case change:
        exe_change();
        break;
    case del:
        exe_del();
        break;
    case follow:
        exe_follow();
        break;
    case unfollow:
        exe_unfollow();
        break;
    case flist:
        exe_flist();
        break;
    case bflist:
        exe_bflist();
        break;
    case cd:
        exe_cd();
        break;
    case speak:
        exe_speak();
        break;
    case ls:
        exe_ls();
        break;
    case lsi:
        exe_lsi();
        break;
    case login:
        exe_login();
        break;
    case logout:
        exe_logout();
        break;
    case spfind:
        exe_spfind();
        break;
    case recommand:
        exe_recommand();
        break;
    default:
        ;
    }
}



void Cmd_Inter::exe_help()
{
    cout << endl;
    cout << "help           Get help information\n";
    cout << "quit           Quit this process\n";
    cout << "register       Register a ID\n";
    cout << "cls            Clean screen\n";
    cout << "cd             cd name to watch a person, cd .. to go back\n";
    cout << "infor          Show object's' information\n";
    cout << "change         Change your information\n";
    cout << "del            Delete your ID\n";
    cout << "spfind         Find person by special condition.\n";
    cout << "recommand      Recommand follow list.\n";
    cout << "follow         Follow a user\n";
    cout << "unfollow       Unfollow a followed user\n";
    cout << "flist          Show follow user.\n";
    cout << "bflist         Show be followed user.\n";
    cout << "speak          Speak on public.\n";
    cout << "ls             Message Mode. cd someone and ls show one's message, trans num to                comment and transmit\n";
    cout << "ls -i          Show your message, you can delete it.\n";
    cout << "login          Login your account\n";
    cout << "logout         Logout your account\n";
    cout << endl;
}

void Cmd_Inter::exe_quit()
{
    db->db_close();
    cout << "Enter anything to quit\n";
    exit(0);
}

void Cmd_Inter::exe_register()
{
    string id;
    string exist = "Y";
    string password;
    string name;
    int sex = 0;    // 1 男   2 女
    int bir_year;
    int bir_month;
    int bir_day;
    string hometown = "\0";
    string phone = "\0";
    cout << "Input -q to exit register\n";
    while(true) // 输入用户名
    {
        cout << "Register ID: ";
        cin >> id;
        if (id == "-q") {cin.sync(); return;}
        bool alnum_flag = true;
        for (unsigned int i = 0; i < id.length(); i++)
            if (!isalnum(id[i]))
                alnum_flag = false;
        if (id.length() < 5 || id.length() > 15)
            cout << "ID length should between 5 and 15.\n";
        else if(!alnum_flag)
            cout << "ID should only use num and alpha\n";
        else if(find_key(id) != 0)
            cout << "ID exist, choice another.\n";
        else
            break;
    }
    while(true) // 输入密码
    {
        cout << "Register Password: ";
        cin >> password;
        if (password == "-q") {cin.sync(); return;}
        bool alnum_flag = true;
        for (unsigned int i = 0; i < password.length(); i++)
            if (!isalnum(password[i]))
                alnum_flag = false;
        if (password.length() < 8 || password.length() > 32)
            cout << "Password length should between 8 and 32.\n";
        else if(!alnum_flag)
            cout << "Password should only use num and alpha\n";
        else
        {
            string second_password;
            cout << "Repeat Password: ";
            cin >> second_password;
            if (second_password == "-q") {cin.sync(); return;}
            if (second_password == password)
                break;
            cout << "Repeat wrong.\n";
        }
    }
    while(true) // 输入姓名
    {
        cout << "True Name: ";
        cin >> name;
        if (name.length() > USER_NAME_LENGTH)
        {
            cout << "name should less than 16 characters.\n";
            continue;
        }
        if (name == "-q") {cin.sync(); return;}
        if (name != "")
            break;
    }
    while(true) // 输入性别
    {
        cout << "Man or Woman (1:man 2:woman): ";
        int input_sex = -1; sex = 0;
        cin >> input_sex;
        if (input_sex == 1) { sex = 1; break;}
        else if (input_sex == 2){ sex = 0; break;}
        cin.clear();
        cin.ignore(1024,'\n');
    }
    while(true) // 输入出生年
    {
        cout << "Birth Year: ";
        cin >> bir_year;
        if (bir_year > 0 && bir_year < 2014)
            break;
        cin.clear();
        cin.ignore(1024,'\n');
    }
    while(true) // 输入出生月
    {
        cout << "Birth Month: ";
        cin >> bir_month;
        if (bir_month > 0 && bir_month < 13)
            break;
        cin.clear();
        cin.ignore(1024,'\n');
    }
    while(true) // 输入出生日
    {
        cout << "Birth Day: ";
        cin >> bir_day;
        bool leap_year_flag = (bir_year%4 == 0 && bir_year%100 != 0) || (bir_year%400 == 0);
        if (bir_month == 1 || bir_month == 3 || bir_month == 5 || bir_month == 7 ||
            bir_month == 8 || bir_month == 10 || bir_month == 12)
            if (bir_day > 0 && bir_day <= 31)
                break;
        if (bir_month == 4 || bir_month == 6 || bir_month == 9 || bir_month == 11)
            if (bir_day > 0 && bir_day <= 30)
                break;
        if (leap_year_flag && bir_month == 2 && bir_day <= 29 && bir_day > 0)
            break;
        if (!leap_year_flag && bir_month == 2 && bir_day <= 28 && bir_day > 0)
            break;
        cout << "date invalid.\n";
        cin.clear();
        cin.ignore(1024,'\n');
    }
    bool extra_flag = 0;
    while(true) // 附加信息
    {
        cout << "Write Extra Information ? (y or n):";
        string temp_flag;
        cin >> temp_flag;
        if (temp_flag == "n") { extra_flag = 0; break; }
        if (temp_flag == "y") { extra_flag = 1; break; }
    }
    if (extra_flag)
    {
        while(true) // 输入家乡
        {
            cout << "Hometown: ";
            cin >> hometown;
            if (hometown == "-q") {cin.sync(); return;}
            if (hometown != "") break;
        }
        while (true) // 输入电话号码
        {
            cout << "Phone: ";
            cin >> phone;
            if (phone == "-q") {cin.sync(); return;}
            bool phone_valid_flag = true;
            for (unsigned int i = 0; i < phone.length(); i++)
                if (!isdigit(phone[i]))
                    phone_valid_flag = false;
            if (phone_valid_flag) break;
            cout << "Phone should only use num.\n";
        }
    }
    // 写入文件
    int begin_pos = db->db_dat_alloc(USER_SUM_LENGTH);
    write_id(begin_pos, id);
    write_exist(begin_pos, exist);
    write_password(begin_pos, password);
    write_name(begin_pos, name);
    write_sex(begin_pos, sex);
    write_birth_year(begin_pos, bir_year);
    write_birth_month(begin_pos, bir_month);
    write_birth_day(begin_pos, bir_day);
    write_hometown(begin_pos, hometown);
    write_phone(begin_pos, phone);

    db->db_link_idx_key(begin_pos, id);

    cin.sync();
}

void Cmd_Inter::exe_cls()
{
    for (int i = 0; i < 70; i++)
        cout << "\n";
    cout << endl;
}

void Cmd_Inter::exe_infor()
{
    //判断是自己的信息还是 cd name 的信息
    int key_pos = (cd_pos == 0)? id_pos : cd_pos;
    if (key_pos == 0) { cout << "No member to infor.\n"; return; }
    cout << "===========================" << endl;
    cout << "ID         : " << get_id(key_pos) << endl;
    cout << "Name       : " << get_name(key_pos) << endl;
    cout << "Sex        : ";
    (get_sex(key_pos) == 1) ? cout << "Man\n" : cout << "Woman\n";
    cout << "Birthday   : " << get_year(key_pos) << "/" << get_month(key_pos) << "/" << get_day(key_pos) << endl;
    cout << "Hometown   : " << get_hometown(key_pos) << endl;
    cout << "Phone      : " << get_phone(key_pos) << endl;
    cout << "===========================" << endl << endl;
}

void Cmd_Inter::exe_change()
{
    cout << "You want to change:\n";
    cout << "1. password\n2. name\n3. sex\n4. birthday\n5. hometown\n6. phone\n";
    int choice = 0;
    while(true)
    {
        cout << "change: ";
        cin >> choice;
        if (choice > 0 && choice < 7) break;
        cin.clear();
        cin.ignore(1024,'\n');
    }
    switch (choice) {
    case 1: // 改密码
    {
        cout << "Input -q to exit register\n";
        string password;
        while(true)
        {
            cout << "Old password: ";
            string input;
            cin >> input;
            if (input == "-q") {cin.sync(); return;}
            if (input == get_password(id_pos)) break;
            cout << "password wrong\n";
            cin.sync();
        }
        while(true)
        {
            cout << "New password: ";
            cin >> password;
            if (password == "-q") {cin.sync(); return;}
            bool alnum_flag = true;
            for (unsigned int i = 0; i < password.length(); i++)
                if (!isalnum(password[i]))
                    alnum_flag = false;
            if (password.length() < 8 || password.length() > 32)
                cout << "Password length should between 8 and 32.\n";
            else if(!alnum_flag)
                cout << "Password should only use num and alpha.\n";
            else
            {
                string second_password;
                cout << "Repeat Password: ";
                cin >> second_password;
                if (second_password == "-q") {cin.sync(); return;}
                if (second_password == password)
                    break;
                cout << "Repeat wrong.\n";
            }
        }
        write_password(id_pos, password);
        cout << "password has changed.\n";
        break;
    }

    case 2: // 改姓名
    {
        string name;
        cout << "Old Name: " << get_name(id_pos) << endl;
        while(true) // 输入姓名
        {
            cout << "New Name: ";
            cin >> name;
            if (name.length() > USER_NAME_LENGTH)
            {
                cout << "name should less than 16 characters.\n";
                continue;
            }
            if (name == "-q") {cin.sync(); return;}
            if (name != "")
                break;
        }
        write_name(id_pos, name);
        cout << "name has changed.\n";
        break;
    }

    case 3: // 改性别
    {
        int sex = 0;    // 1 男   2 女
        while(true) // 输入性别
        {
            cout << "Man or Woman (1:man 2:woman): ";
            int input_sex = -1; sex = 0;
            cin >> input_sex;
            if (input_sex == 1) { sex = 1; break;}
            else if (input_sex == 2){ sex = 0; break;}
            cin.clear();
            cin.ignore(1024,'\n');
        }
        write_sex(id_pos, sex);
        cout << "sex has changed.\n";
        break;
    }

    case 4: // 改生日
    {
        cout << "Old Birthday: " << get_year(id_pos) << "/" << get_month(id_pos) << "/" << get_day(id_pos) << endl;
        int bir_year, bir_month, bir_day;
        while(true) // 输入出生年
        {
            cout << "Birth Year: ";
            cin >> bir_year;
            if (bir_year > 0 && bir_year < 2014)
                break;
            cin.clear();
            cin.ignore(1024,'\n');
        }
        while(true) // 输入出生月
        {
            cout << "Birth Month: ";
            cin >> bir_month;
            cout << bir_month;
            if (bir_month > 0 && bir_month < 13)
                break;
            cin.clear();
            cin.ignore(1024,'\n');
        }
        while(true) // 输入出生日
        {
            cout << "Birth Day: ";
            cin >> bir_day;
            bool leap_year_flag = (bir_year%4 == 0 && bir_year%100 != 0) || (bir_year%400 == 0);
            if (bir_month == 1 || bir_month == 3 || bir_month == 5 || bir_month == 7 ||
                bir_month == 8 || bir_month == 10 || bir_month == 12)
                if (bir_day > 0 && bir_day <= 31)
                    break;
            if (bir_month == 4 || bir_month == 6 || bir_month == 9 || bir_month == 11)
                if (bir_day > 0 && bir_day <= 30)
                    break;
            if (leap_year_flag && bir_month == 2 && bir_day <= 29 && bir_day > 0)
                break;
            if (!leap_year_flag && bir_month == 2 && bir_day <= 28 && bir_day > 0)
                break;
            cout << "date invalid.\n";
            cin.clear();
            cin.ignore(1024,'\n');
        }
        write_birth_year(id_pos, bir_year);
        write_birth_month(id_pos, bir_month);
        write_birth_day(id_pos, bir_day);
        cout << "birthday has changed.\n";
        break;
    }

    case 5: // 改家乡
    {
        string hometown;
        cout << "Old Hometown: " << get_hometown(id_pos) << endl;
        while(true) // 输入家乡
        {
            cout << "New Hometown: ";
            cin >> hometown;
            if (hometown == "-q") {cin.sync(); return;}
            if (hometown != "") break;
        }
        write_hometown(id_pos, hometown);
        cout << "hometown has changed.\n";
        break;
    }

    case 6:
    {
        string phone;
        cout << "Old Phone: " << get_phone(id_pos) << endl;
        while (true) // 输入电话号码
        {
            cout << "New Phone: ";
            cin >> phone;
            if (phone == "-q") {cin.sync(); return;}
            bool phone_valid_flag = true;
            for (unsigned int i = 0; i < phone.length(); i++)
                if (!isdigit(phone[i]))
                    phone_valid_flag = false;
            if (phone_valid_flag) break;
            cout << "Phone should only use num.\n";
        }
        write_phone(id_pos, phone);
        cout << "phone has changed.\n";
    }
    default:;
    }
    cin.sync();
}

void Cmd_Inter::exe_del()
{
    if (id_name == "")
    {
        cout << "no member to del.\n";
        return;
    }
    string password;
    while(true) // 输入密码
    {
        cout << "Password: ";
        cin >> password;
        if (password == "-q"){ cin.sync(); return;}
        string true_password = get_password(id_pos);
        if (password == true_password) break;
        cout << "Password wrong.\n";
    }
    cout << "DO YOU WANT TO DELETE THIS USER? (Y or N)\n";
    string input;
    while (true)
    {
        cin >> input;
        if (input == "N" || input == "n") return;
        if (input == "Y" || input == "y") break;
    }
    cout << "delete ID: " << get_id(id_pos) << endl;
    write_exist(id_pos, "N");
    exe_logout();
    cin.sync();
}

void Cmd_Inter::exe_follow()
{
    string follow_id = cmd_type.get_data();
    int follow_pos = find_key(follow_id);
    if (follow_pos == 0 || get_exist(follow_pos) != "Y")
    {
        cout << "Not find this ID: " << follow_id << endl;
        return;
    }
    // 判断是否是自己或者已经在follow列表中
    if (follow_id == id_name)
    {
        cout << "Can't follow yourself.\n";
        return;
    }
    vector<string> follow_name;
    int next_pos = get_follow_pointer(id_pos);
    while(next_pos != 0)
    {
        string temp_name = db->db_dat_read_string(next_pos, USER_ID_LENGTH);
        follow_name.push_back(temp_name);
        next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
    }
    for (auto& i:follow_name)
    {
        if (i == follow_id)
        {
            cout << follow_id << " has been followed.\n";
            return;
        }
    }
    write_follow(id_pos, follow_id);
    write_be_follow(follow_pos, id_name);
    cout << "Follow " << follow_id << " success.\n";
}

void Cmd_Inter::exe_unfollow()
{
    string unfollow_id = cmd_type.get_data();
    int next_pos = get_follow_pointer(id_pos);
    if (next_pos == 0)
    {
        cout << "No Follow List.\n";
        return;
    }
    while(next_pos != 0)
    {
        string temp_name = db->db_dat_read_string(next_pos, USER_ID_LENGTH);
        if (unfollow_id == temp_name)
        {
            db->db_dat_write_string(next_pos,"NONE\0", USER_ID_LENGTH);
            cout << "delete id from follow list.\n";
            int bfollow_pos = find_key(unfollow_id);
            int b_next_pos = get_be_follow_pointer(bfollow_pos);
            while(b_next_pos != 0)
            {
                if (id_name == db->db_dat_read_string(b_next_pos, USER_ID_LENGTH))
                {
                    db->db_dat_write_string(b_next_pos, "NONE\0", USER_ID_LENGTH);
                    cout << "delete id from be follow list.\n";
                    return;
                }
                b_next_pos = db->db_dat_read_int(b_next_pos +USER_ID_LENGTH + USER_EXIST_LENGTH);
            }
            cout << "Error: delete id from be follow list didn't find.\n";
        }
        next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
    }
}

void Cmd_Inter::exe_flist()
{
    vector<string> follow_name;
    int next_pos = get_follow_pointer(id_pos);
    if (next_pos == 0)
    {
        cout << "No Follow List.\n";
        return;
    }
    while(next_pos != 0)
    {
        string temp_name = db->db_dat_read_string(next_pos, USER_ID_LENGTH);
        follow_name.push_back(temp_name);
        next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
    }
    cout << endl;
    int num = 1;
    for (auto& i:follow_name)
        if (i != "NONE")
            cout << num++ << ": " <<  i << endl;
    cout << endl;
}

void Cmd_Inter::exe_bflist()
{
    vector<string> be_follow_name;
    int next_pos = get_be_follow_pointer(id_pos);
    if (next_pos == 0)
    {
        cout << "No be follow list.\n";
        return;
    }
    while(next_pos != 0)
    {
        string temp_name = db->db_dat_read_string(next_pos, USER_ID_LENGTH);
        be_follow_name.push_back(temp_name);
        next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
    }
    cout << endl;
    int num = 1;
    for (auto& i:be_follow_name)
        if (i != "NONE")
            cout << num++ << ": " << i << endl;
    cout << endl;
}

void Cmd_Inter::exe_cd()
{
    string watch_id = cmd_type.get_data();
    // 判断是否是 cd ..
    if (watch_id == "..")
    {
        cd_name = "";
        cd_pos = 0;
        return;
    }
    int watch_pos = find_key(watch_id);
    if (watch_pos == 0 || get_exist(watch_pos) != "Y")
    {
        cout << "Not find this ID: " << watch_id << endl;
        return;
    }
    // 判断是否是自己
    if (watch_id == id_name)
    {
        cout << "Can't watch yourself.\n";
        return;
    }
    cd_name = watch_id;
    cd_pos = watch_pos;
}

void Cmd_Inter::exe_speak()
{
    string input_message;
    while(true)
    {
        cout << "Input message (no more than 140 words, -q to quit):\n";
        cin >> input_message;
        if (input_message == "-q")
            return;
        if (input_message.length() > MES_BODY_LENGTH)
        {
            cout << "Please input no more than 140 words.\n";
            continue;
        }
        else if (input_message.length() < MES_BODY_LENGTH)
            input_message += '\0';
        break;
    }
    write_message(id_pos, input_message);
    return;
}

void Cmd_Inter::exe_ls()
{
    vector<int> save_message_pointer;
    // 查看全部好友包括自己的消息
    if (cd_name == "")
    {
        vector<int> follow_pos;
        follow_pos.push_back(id_pos);
        int next_pos = get_follow_pointer(id_pos);
        while(next_pos != 0)
        {
            string temp_name = db->db_dat_read_string(next_pos, USER_ID_LENGTH);
            follow_pos.push_back(find_key(temp_name));
            next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
        }
        // 得到全部可显示的消息
        for (unsigned int i = 0; i < follow_pos.size(); i++)
        {
            vector<int> temp_message = get_one_s_message(follow_pos[i]);
            for (unsigned int j = 0; j < temp_message.size(); j++)
                save_message_pointer.push_back(temp_message[j]);
        }
    }
    // 显示一个人的消息
    else
        save_message_pointer = get_one_s_message(cd_pos);

    // 折叠显示，按时间倒序排序
    if (save_message_pointer.size() == 0)
    {
        cout << "No message." << endl;
        return;
    }
    fold_message(save_message_pointer);
    sort_message(save_message_pointer);
    // 显示消息
    unsigned int start_message = 0;
    unsigned int end_message = save_message_pointer.size()-1;
    while(true)
    {
        for (unsigned int i = start_message; i <= start_message + ONCE_MAX_MESSAGE - 1; i++)
        {
            string message_name = get_mes_name(save_message_pointer[i]);
            vector<int> message_time = get_mes_time(save_message_pointer[i]);
            int message_trans_times = get_mes_trans_times(save_message_pointer[i]);
            cout << "===========================================================\n";
            cout << i+1 << ". " <<message_name << "\t" << message_time[0] << "/" << message_time[1] << "/" << message_time[2] << "\t" << message_time[3] << ":" << message_time[4] << ":" << message_time[5];
            cout << "\t\tTrans: " << message_trans_times << endl;
            cout << "\n\t" <<  get_mes_body(save_message_pointer[i]) << endl << endl;
            if (i >= end_message)
            {
                cout << "===========================================================\n";
                cout << "No more.\n";
                cout << " messages waiting to show.(\'trans\' to transmit,\'-q\' to quit)\n\n";
                break;
            }
        }
        cout << "===========================================================\n\n";
        int release_num = end_message - start_message - ONCE_MAX_MESSAGE + 1;
        if (int(end_message - start_message - ONCE_MAX_MESSAGE + 1) > 0)
            cout << endl << release_num << " messages waiting to show.(\'more\' to show,\'trans\' to transmit,\'-q\' to quit)\n";
        string input_com;
        while(true)
        {
            cout << "> ";
            cin >> input_com;
            if (input_com == "-q")
                return;
            else if (input_com == "more")
            {
                if (start_message + ONCE_MAX_MESSAGE -1 >= end_message)
                {
                    cout << "No more.\n\n";
                    return;
                }
                start_message += ONCE_MAX_MESSAGE;
                break;
            }
            // 转发
            else if (input_com == "trans")
            {
                unsigned int trans_num = 0;
                cout << endl;
                cin >> trans_num;
                if (trans_num > end_message + 1)
                {
                    cout << "trans num error.\n";
                    continue;
                }
                trans_message(save_message_pointer[trans_num-1]);
                return;
            }
            else
                cout << "\'more\' to show,\'trans\' to transmit,\'-q\' to quit";
        }
    }
}

void Cmd_Inter::exe_lsi()
{
    // 查看自己的消息
    vector<int> save_message_pointer = get_one_s_message(id_pos);
    // 按时间倒序排序
    if (save_message_pointer.size() == 0)
    {
        cout << "No message." << endl;
        return;
    }
    sort_message(save_message_pointer);
    // 显示消息
    unsigned int start_message = 0;
    unsigned int end_message = save_message_pointer.size()-1;
    while(true)
    {
        for (unsigned int i = start_message; i <= start_message + ONCE_MAX_MESSAGE - 1; i++)
        {
            string message_name = get_mes_name(save_message_pointer[i]);
            vector<int> message_time = get_mes_time(save_message_pointer[i]);
            int message_trans_times = get_mes_trans_times(save_message_pointer[i]);
            cout << "===========================================================\n";
            cout << i+1 << ". " <<message_name << "\t" << message_time[0] << "/" << message_time[1] << "/" << message_time[2] << "\t" << message_time[3] << ":" << message_time[4] << ":" << message_time[5];
            cout << "\t\tTrans: " << message_trans_times << endl;
            cout << "\n\t" <<  get_mes_body(save_message_pointer[i]) << endl << endl;
            if (i >= end_message)
            {
                cout << "===========================================================\n";
                cout << "No more.\n";
                cout << " messages waiting to show.(\'more\' to show, \'-q\' to quit, \'delete\' to delete)\n";
                break;
            }
        }
        cout << "===========================================================\n";
        int release_num = end_message - start_message - ONCE_MAX_MESSAGE + 1;
        if (int(end_message - start_message - ONCE_MAX_MESSAGE + 1) > 0)
            cout << endl << release_num << " messages waiting to show.(\'more\' to show, \'-q\' to quit, \'delete num\' to delete)\n";
        string input_com;
        while(true)
        {
            cout << "> ";
            cin >> input_com;
            if (input_com == "-q")
                return;
            else if (input_com == "more")
            {
                if (start_message + ONCE_MAX_MESSAGE -1 >= end_message)
                {
                    cout << "No more.\n";
                    return;
                }
                start_message += ONCE_MAX_MESSAGE;
                break;
            }
            else if (input_com == "delete")
            {
                unsigned int del_num = 0;
                cout << endl;
                cin >> del_num;
                if (del_num > end_message + 1)
                {
                    cout << "delete num error.\n";
                    continue;
                }
                delete_message(save_message_pointer[del_num-1]);
                return;
            }
            else
                cout << "\'more\' to show, \'-q\' to quit";
        }
    }
}

void Cmd_Inter::exe_login()
{
    cout << "\'-q\' to quit\n";
    string id;
    string password;
    int key_pos = 0;
    while(true) // 输入账号
    {
        cout << "ID: ";
        cin >> id;
        if (id == "-q"){ cin.sync(); return;}
        key_pos = find_key(id);
        if (key_pos == 0 || get_exist(key_pos) != "Y")
            cout << "Not find this ID\n";
        else break;
    }
    while(true) // 输入密码
    {
        cout << "Password: ";
        cin >> password;
        if (password == "-q"){ cin.sync(); return;}
        string true_password = get_password(key_pos);
        if (password == true_password) break;
        cout << "Password wrong.\n";
    }
    // 登陆成功
    id_pos = key_pos;
    id_name = get_id(id_pos);
    cin.sync();
}

void Cmd_Inter::exe_logout()
{
    id_pos = 0;
    id_name = "";
}

void Cmd_Inter::exe_spfind()
{
    string input_name;
    int input_sex;
    int input_year;
    int input_month;
    int input_day;
    string input_hometown;
    string input_phone;
    cout << "Enter special condition(\'-\' and -1(for sex,birthday) mean ignore):\n";
    cout << "Input name:";
    cin >> input_name;
    cout << "Input sex(0:woman 1:man):";
    cin >> input_sex;
    cout << "Input Birth Year:";
    cin >> input_year;
    cout << "Input Birth Month:";
    cin >> input_month;
    cout << "Input Birth Day:";
    cin >> input_day;
    cout << "Input hometown:";
    cin >> input_hometown;
    cout << "Input phone:";
    cin >> input_phone;
    vector<int> all_id_pos = get_all_id_pos();
    vector<int> match_id_pos;
    for (auto i:all_id_pos)
    {
        if(input_name != "-" && input_name != get_name(i))
            continue;
        if (input_sex != -1 && input_sex != get_sex(i))
            continue;
        if (input_year != -1 && input_year != get_year(i))
            continue;
        if (input_month != -1 && input_month != get_month(i))
            continue;
        if (input_day != -1 && input_day != get_day(i))
            continue;
        if (input_hometown != "-" && input_hometown != get_hometown(i))
            continue;
        if (input_phone != "-" && input_phone != get_phone(i))
            continue;
        match_id_pos.push_back(i);
    }
    if (match_id_pos.size() == 0)
    {
        cout << "No match user." << endl;
        return;
    }
    unsigned int index = 1;
    cout << "\nMatching user:\n";
    for (auto i:match_id_pos)
        cout << index++ << ":" << get_id(i) << endl;
}

void Cmd_Inter::exe_recommand()
{
    string my_hometown = get_hometown(id_pos);
    vector<int> all_id_pos = get_all_id_pos();
    vector<int> recommand_list;
    for (auto i:all_id_pos)
    {
        if (my_hometown == get_hometown(i) && i != id_pos)
            recommand_list.push_back(i);
    }
    if (recommand_list.size() == 0)
    {
        cout << "No recommand user." << endl;
        return;
    }
    unsigned int index = 1;
    cout << "\nRecommand user:\n";
    for (auto i:recommand_list)
        cout << index++ << ":" << get_id(i) << endl;
}









void Cmd_Inter::write_id(int begin_pos, string id)
{
    int offset = 0;
    db->db_dat_write_string(begin_pos + offset, id, USER_ID_LENGTH);
}

void Cmd_Inter::write_exist(int begin_pos, string exist)
{
    int offset = USER_ID_LENGTH;
    db->db_dat_write_string(begin_pos + offset, exist, USER_EXIST_LENGTH);
}

void Cmd_Inter::write_password(int begin_pos, string password)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH;
    db->db_dat_write_string(begin_pos + offset, password, USER_PASSWORD_LENGTH);
}

void Cmd_Inter::write_name(int begin_pos, string name)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH;
    db->db_dat_write_string(begin_pos + offset, name, USER_NAME_LENGTH);
}

void Cmd_Inter::write_sex(int begin_pos, int sex)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH;
    db->db_dat_write_int(begin_pos + offset, sex);
}

void Cmd_Inter::write_birth_year(int begin_pos, int year)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH;
    db->db_dat_write_int(begin_pos + offset, year);
}

void Cmd_Inter::write_birth_month(int begin_pos, int month)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH;
    db->db_dat_write_int(begin_pos + offset, month);
}

void Cmd_Inter::write_birth_day(int begin_pos, int day)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH;
    db->db_dat_write_int(begin_pos + offset, day);
}

void Cmd_Inter::write_hometown(int begin_pos, string hometown)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH;
    db->db_dat_write_string(begin_pos + offset, hometown, USER_HOMETOWN_LENGTH);
}

void Cmd_Inter::write_phone(int begin_pos, string phone)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH;
    db->db_dat_write_string(begin_pos + offset, phone, USER_PHONE_LENGTH);
}

void Cmd_Inter::write_follow(int begin_pos, string id)
{
    // 判断是否有NONE，有就填入
    int find_none_pos = get_follow_pointer(begin_pos);
    while(find_none_pos != 0)
    {
        string find_none_name = db->db_dat_read_string(find_none_pos, USER_ID_LENGTH);
        if (find_none_name == "NONE")
        {
            db->db_dat_write_string(find_none_pos, id, USER_ID_LENGTH);
            find_none_pos = db->db_dat_read_int(find_none_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
            return;
        }
    }
    // 保证了用户名存在
    if (get_follow_pointer(begin_pos) == 0)
    {
        int alloc_pos = db->db_dat_alloc(USER_ID_LENGTH + USER_EXIST_LENGTH + USER_FOLLOW_POINTER);
        int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH;
        db->db_dat_write_int(begin_pos + offset, alloc_pos);
        db->db_dat_write_string(alloc_pos, id, USER_ID_LENGTH);
    }
    else
    {
        int next_pos = get_follow_pointer(begin_pos);
        int save_pos;
        while(next_pos != 0)
        {
            save_pos = next_pos;
            next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
        }
        int alloc_pos = db->db_dat_alloc(USER_ID_LENGTH + USER_EXIST_LENGTH + USER_FOLLOW_POINTER);
        int offset = USER_ID_LENGTH + USER_EXIST_LENGTH;
        db->db_dat_write_int(save_pos + offset, alloc_pos);
        db->db_dat_write_string(alloc_pos, id, USER_ID_LENGTH);
    }
}

void Cmd_Inter::write_be_follow(int begin_pos, string id)
{
    // 判断是否有NONE，有就填入
    int find_none_pos = get_be_follow_pointer(begin_pos);
    while(find_none_pos != 0)
    {
        string find_none_name = db->db_dat_read_string(find_none_pos, USER_ID_LENGTH);
        if (find_none_name == "NONE")
        {
            db->db_dat_write_string(find_none_pos, id, USER_ID_LENGTH);
            find_none_pos = db->db_dat_read_int(find_none_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
            return;
        }
    }
    // 保证了用户名存在
    if (get_be_follow_pointer(begin_pos) == 0)
    {
        int alloc_pos = db->db_dat_alloc(USER_ID_LENGTH + USER_EXIST_LENGTH + USER_BE_FOLLOW_POINTER);
        int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER;
        db->db_dat_write_int(begin_pos + offset, alloc_pos);
        db->db_dat_write_string(alloc_pos, id, USER_ID_LENGTH);
    }
    else
    {
        int next_pos = get_be_follow_pointer(begin_pos);
        int save_pos;
        while(next_pos != 0)
        {
            save_pos = next_pos;
            next_pos = db->db_dat_read_int(next_pos + USER_ID_LENGTH + USER_EXIST_LENGTH);
        }
        int alloc_pos = db->db_dat_alloc(USER_ID_LENGTH + USER_EXIST_LENGTH + USER_BE_FOLLOW_POINTER);
        int offset = USER_ID_LENGTH + USER_EXIST_LENGTH;
        db->db_dat_write_int(save_pos + offset, alloc_pos);
        db->db_dat_write_string(alloc_pos, id, USER_ID_LENGTH);
    }
}

void Cmd_Inter::write_speak_head(int begin_pos, int val)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER + USER_BE_FOLLOW_POINTER;
    db->db_dat_write_int(begin_pos + offset, val);
}

void Cmd_Inter::write_speak_tail(int begin_pos, int val)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER + USER_BE_FOLLOW_POINTER + USER_SPEAK_HEAD;
    db->db_dat_write_int(begin_pos + offset, val);
}

int Cmd_Inter::write_message(int begin_pos, string message)
{
    int mes_pos = db->db_dat_alloc(MES_SUM_LENGTH);
    int speak_head_pointer = get_speak_head_pointer(begin_pos);
    if (speak_head_pointer == 0)
    {
        write_speak_head(begin_pos, mes_pos);
        write_speak_tail(begin_pos, mes_pos);
        write_mes_pre(mes_pos, 0);
        write_mes_back(mes_pos, 0);
    }
    else // 已经有过speak
    {
        int last_pos = get_speak_tail_pointer(begin_pos);
        write_speak_tail(begin_pos, mes_pos);
        write_mes_back(last_pos, mes_pos);
        write_mes_pre(mes_pos, last_pos);
        write_mes_back(mes_pos, 0);
    }
    write_mes_exist(mes_pos, 1);
    write_mes_time(mes_pos);
    write_mes_name(mes_pos, get_id(begin_pos));
    write_mes_origin(mes_pos, 0);
    write_mes_trans_times(mes_pos, 0);
    // 写被转发的初始化
    db->db_dat_write_int(mes_pos + MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH,
                         0);
    write_mes_body(mes_pos, message);
    return mes_pos;
}

void Cmd_Inter::write_mes_exist(int mes_pos, int val)
{
    int offset = 0;
    db->db_dat_write_int(mes_pos + offset, val);
}

void Cmd_Inter::write_mes_pre(int mes_pos, int val)
{
    int offset = MES_EXIST_LENGTH;
    db->db_dat_write_int(mes_pos + offset, val);
}

void Cmd_Inter::write_mes_back(int mes_pos, int val)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH;
    db->db_dat_write_int(mes_pos + offset, val);
}

void Cmd_Inter::write_mes_time(int mes_pos)
{
    struct tm *newtime;
    char tmpbuf[128];
    time_t lt;
    time(&lt);
    newtime = localtime(&lt);
    strftime(tmpbuf, 128, " %Y \n", newtime);
    int year = atoi(tmpbuf);
    strftime(tmpbuf, 128, " %m \n", newtime);
    int month = atoi(tmpbuf);
    strftime(tmpbuf, 128, " %d \n", newtime);
    int day = atoi(tmpbuf);
    strftime(tmpbuf, 128, " %H \n", newtime);
    int hour = atoi(tmpbuf);
    strftime(tmpbuf, 128, " %M \n", newtime);
    int minute = atoi(tmpbuf);
    strftime(tmpbuf, 128, " %S \n", newtime);
    int second = atoi(tmpbuf);
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH;
    db->db_dat_write_int(mes_pos + offset, year);
    db->db_dat_write_int(mes_pos + offset + 4, month);
    db->db_dat_write_int(mes_pos + offset + 8, day);
    db->db_dat_write_int(mes_pos + offset + 12, hour);
    db->db_dat_write_int(mes_pos + offset + 16, minute);
    db->db_dat_write_int(mes_pos + offset + 20, second);
}

void Cmd_Inter::write_mes_name(int mes_pos, string name)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH;
    name += '\0';
    db->db_dat_write_string(mes_pos + offset, name, name.length());
}

void Cmd_Inter::write_mes_origin(int mes_pos, int val)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH;
    db->db_dat_write_int(mes_pos + offset, val);
}

void Cmd_Inter::write_mes_trans_times(int mes_pos, int val)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH;
    db->db_dat_write_int(mes_pos + offset, val);
}

void Cmd_Inter::write_mes_trans_pointer(int mes_pos, int val)
{
    int temp_val = get_mes_trans_pointer(mes_pos);
    if (temp_val == 0)
    {
        int new_pos = db->db_dat_alloc(8);
        db->db_dat_write_int(mes_pos+ MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH,
                             new_pos);
        db->db_dat_write_int(new_pos, val);
        db->db_dat_write_int(new_pos + 4, 0);
        return;
    }
    int save_val = temp_val;
    while(temp_val != 0)
    {
        if (temp_val == 0)
        {
            int new_pos = db->db_dat_alloc(8);
            db->db_dat_write_int(new_pos, val);
            db->db_dat_write_int(new_pos + 4, 0);
            db->db_dat_write_int(save_val + 4, new_pos);
            return;
        }
        save_val = temp_val;
        temp_val = db->db_dat_read_int(temp_val + 4);
    }

}

void Cmd_Inter::write_mes_body(int mes_pos, string message)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH + MES_BE_TRANS_POINTER;
    db->db_dat_write_string(mes_pos + offset, message, message.length());
}



string Cmd_Inter::get_id(int begin_pos)
{
    int offset = 0;
    return db->db_dat_read_string(begin_pos + offset, USER_ID_LENGTH);
}

string Cmd_Inter::get_exist(int begin_pos)
{
    int offset = USER_ID_LENGTH;
    return db->db_dat_read_string(begin_pos + offset, USER_EXIST_LENGTH);
}

string Cmd_Inter::get_password(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH;
    return db->db_dat_read_string(begin_pos + offset, USER_PASSWORD_LENGTH);
}

string Cmd_Inter::get_name(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH;
    return db->db_dat_read_string(begin_pos + offset, USER_NAME_LENGTH);
}

int Cmd_Inter::get_sex(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_year(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_month(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_day(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH;
    return db->db_dat_read_int(begin_pos + offset);
}

string Cmd_Inter::get_hometown(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH;
    return db->db_dat_read_string(begin_pos + offset, USER_HOMETOWN_LENGTH);
}

string Cmd_Inter::get_phone(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH;
    return db->db_dat_read_string(begin_pos + offset, USER_PHONE_LENGTH);
}

int Cmd_Inter::get_follow_pointer(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_be_follow_pointer(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_speak_head_pointer(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER + USER_BE_FOLLOW_POINTER;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_speak_tail_pointer(int begin_pos)
{
    int offset = USER_ID_LENGTH + USER_EXIST_LENGTH + USER_PASSWORD_LENGTH + USER_NAME_LENGTH + USER_SEX_LENGTH + USER_BIRTHYEAR_LENGTH + USER_BIRTHMONTH_LENGTH + USER_BIRTHDAY_LENGTH + USER_HOMETOWN_LENGTH + USER_PHONE_LENGTH + USER_FOLLOW_POINTER + USER_BE_FOLLOW_POINTER + USER_SPEAK_HEAD;
    return db->db_dat_read_int(begin_pos + offset);
}

int Cmd_Inter::get_mes_exist(int mes_pos)
{
    int offset = 0;
    return db->db_dat_read_int(mes_pos + offset);
}

int Cmd_Inter::get_mes_pre_pointer(int mes_pos)
{
    int offset = MES_EXIST_LENGTH;
    return db->db_dat_read_int(mes_pos + offset);
}

int Cmd_Inter::get_mes_back_pointer(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH;
    return db->db_dat_read_int(mes_pos + offset);
}

vector<int> Cmd_Inter::get_mes_time(int mes_pos)
{
    vector<int> time;
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH;
    for (unsigned int i = 0; i <= 5; i++)
    {
        time.push_back(db->db_dat_read_int(mes_pos + offset + i*4));
    }
    return time;
}

string Cmd_Inter::get_mes_name(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH;
    return db->db_dat_read_string(mes_pos + offset, MES_NAME_LENGTH);
}

int Cmd_Inter::get_mes_origin(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH;
    return db->db_dat_read_int(mes_pos + offset);
}

int Cmd_Inter::get_mes_trans_times(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH;
    return db->db_dat_read_int(mes_pos + offset);
}

int Cmd_Inter::get_mes_trans_pointer(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH;
    return db->db_dat_read_int(mes_pos + offset);
}

string Cmd_Inter::get_mes_body(int mes_pos)
{
    int offset = MES_EXIST_LENGTH + MES_PRE_LENGTH + MES_BACK_LENGTH + MES_TIME_LENGTH + MES_NAME_LENGTH + MES_ORIGIN_LENGTH + MES_BE_TRANS_TIMES_LENGTH + MES_BE_TRANS_POINTER;
    return db->db_dat_read_string(mes_pos + offset, MES_BODY_LENGTH);
}

vector<int> Cmd_Inter::get_one_s_message(int begin_pos)
{
    vector<int> message_pointer;
    int temp_pos = get_speak_tail_pointer(begin_pos);
    while(temp_pos != 0)
    {
        if (get_mes_exist(temp_pos) != 0)
            message_pointer.push_back(temp_pos);
        temp_pos = get_mes_pre_pointer(temp_pos);
    }
    return message_pointer;
}

bool Cmd_Inter::time_compare_left_pre_than_right(vector<int>& left, vector<int>& right)
{
    for (unsigned int i = 0; i < 6; i++)
    {
        if (left[i] < right[i])
            return true;
        if (left[i] > right[i])
            return false;
    }
    return false;
}

void Cmd_Inter::sort_message(vector<int>& save_message_pointer)
{
    if (save_message_pointer.size() == 0)
        return;
    // 冒泡排序
    for (unsigned int i = 0; i < save_message_pointer.size()-1; i++)
    {
        for (int j = save_message_pointer.size()-1; j > 0; j--)
        {
            vector<int> right_time = get_mes_time(save_message_pointer[j]);
            vector<int> left_time = get_mes_time(save_message_pointer[j-1]);
            if (time_compare_left_pre_than_right(left_time, right_time))
            {
                int temp = save_message_pointer[j];
                save_message_pointer[j] = save_message_pointer[j-1];
                save_message_pointer[j-1] = temp;
            }
        }
    }
}

void Cmd_Inter::trans_message(int ori_mes_pos)
{
    string add_comment;
    cout << "comment: ";
    cin >> add_comment;
    string old_message = get_mes_body(ori_mes_pos);
    string old_name = get_mes_name(ori_mes_pos);
    string new_message = add_comment + " From " + old_name + ":" + old_message;
    if (new_message.length() > MES_BODY_LENGTH)
        new_message = new_message.substr(0, MES_BODY_LENGTH);
    int trans_pos = write_message(id_pos, new_message);
    cout << "trans success.\n";
    // 写转发的记录
    write_mes_trans_pointer(ori_mes_pos, trans_pos); //写转发记录
    int ori_trans_times = get_mes_trans_times(ori_mes_pos); // 读转发次数
    write_mes_trans_times(ori_mes_pos, ori_trans_times+1); // 写转发次数
    // 迭代写转发次数
    int temp_pos = get_mes_origin(ori_mes_pos);
    while(temp_pos != 0)
    {
        int temp_trans_times = get_mes_trans_times(temp_pos); // 读转发次数
        write_mes_trans_times(temp_pos, temp_trans_times+1); // 写转发次数
        temp_pos = get_mes_origin(temp_pos);
    }
    write_mes_origin(trans_pos, ori_mes_pos); // 写转发源
}

void Cmd_Inter::delete_message(int mes_pos)
{
    write_mes_exist(mes_pos, 0);
    int temp_pos = get_mes_trans_pointer(mes_pos);
    while(temp_pos != 0)
    {
        delete_message(db->db_dat_read_int(temp_pos));
        temp_pos = db->db_dat_read_int(temp_pos +4);
    }
}

void Cmd_Inter::fold_message(vector<int> &save_message_pointer)
{
    vector<int> new_message_pointer; // 折叠后的
    unsigned int length = save_message_pointer.size();
    for(unsigned int i = 0; i < length; i++)
    {
        bool add_flag = true;
        for(unsigned int j = 0; j < length; j++)
        {
            if (j != i && get_mes_origin(save_message_pointer[j]) == save_message_pointer[i])
            {
                add_flag = false;
            }
        }
        if (add_flag)
            new_message_pointer.push_back(save_message_pointer[i]);
    }
    save_message_pointer = new_message_pointer;
}


// 搜索一个 ID 是否存在
int Cmd_Inter::find_key(string key_name)
{
    int now_pos = db->db_hashCode(key_name) * HASH_UNIT_LEN + HASH_OFFSET;
    if (db->db_idx_get_1st_4byte(now_pos) == 0) return 0;
    while(true)
    {
        int temp_value1 = db->db_idx_get_1st_4byte(now_pos);
        string temp_key = get_id(temp_value1);
        if (temp_key == key_name)
            return temp_value1;
        now_pos = db->db_idx_get_2nd_4byte(now_pos);
        if (now_pos == 0)
            return 0;
    }
}

// 得到全部ID的pos
vector<int> Cmd_Inter::get_all_id_pos()
{
    vector<int> all_id_pos;
    for (int i = 0; i < HASH_BUCKET; i++)
    {
        int now_pos = HASH_OFFSET + HASH_UNIT_LEN*i;
        int temp_val = db->db_idx_get_1st_4byte(now_pos);
        while(true)
        {
            if (temp_val == 0)
                break;
            all_id_pos.push_back(temp_val);
            now_pos = db->db_idx_get_2nd_4byte(now_pos);
            if (now_pos == 0)
                break;
            temp_val = db->db_idx_get_1st_4byte(now_pos);
        }
    }
    return all_id_pos;
}



// 测试函数

// 测试注册的正确性和条件查找的正确性
void Cmd_Inter::test_01()
{
    int start_id = 100000;
    int end_id = 200000;
    for (int i = start_id; i < end_id; i++)
    {
        stringstream ss;
        ss << i;
        string temp_id = ss.str();
        int begin_pos = db->db_dat_alloc(USER_SUM_LENGTH);
        write_id(begin_pos, temp_id);
        write_exist(begin_pos, "Y");
        write_password(begin_pos, temp_id);
        write_name(begin_pos, "1");
        write_sex(begin_pos, 1);
        write_birth_year(begin_pos, 1);
        write_birth_month(begin_pos, 1);
        write_birth_day(begin_pos, 1);
        write_hometown(begin_pos, "hometown");
        write_phone(begin_pos, "phone");
        db->db_link_idx_key(begin_pos, temp_id);
        //cout << 100*float(i-start_id)/(end_id-start_id)  << "%" << endl;
    }
    cout << endl;
    vector<int> all_id_pos = get_all_id_pos();
    if (all_id_pos.size() == (end_id - start_id))
        cout << "Register True" << endl;
    else
        cout << "Register False" << endl;
    vector<int> match_id_pos;
    for (auto i:all_id_pos)
    {
        if(get_name(i) == "1")
            continue;
        if (get_sex(i) == 1)
            continue;
        if (get_year(i) == 1)
            continue;
        if (get_month(i) == 1)
            continue;
        if (get_day(i) == 1)
            continue;
        if (get_hometown(i) == "hometown")
            continue;
        if (get_phone(i) == "phone")
            continue;
        match_id_pos.push_back(i);
    }
    if (all_id_pos.size() == (end_id - start_id))
        cout << "Spfind True" << endl;
    else
        cout << "Spfind False" << endl;
}

// 测试注册性能
void Cmd_Inter::test_02()
{
    int start_id = 100000;
    int end_id = 110000;
    time_t begin_time = time(0);
    for (int i = start_id; i < end_id; i++)
    {
        stringstream ss;
        ss << i;
        string temp_id = ss.str();
        int begin_pos = db->db_dat_alloc(USER_SUM_LENGTH);
        write_id(begin_pos, temp_id);
        write_exist(begin_pos, "Y");
        write_password(begin_pos, temp_id);
        write_name(begin_pos, "1");
        write_sex(begin_pos, 1);
        write_birth_year(begin_pos, 1);
        write_birth_month(begin_pos, 1);
        write_birth_day(begin_pos, 1);
        write_hometown(begin_pos, "hometown");
        write_phone(begin_pos, "phone");
        db->db_link_idx_key(begin_pos, temp_id);
        //cout << 100*float(i-start_id)/(end_id-start_id)  << "%" << endl;
    }
    cout << "test 01 end.\n" << endl;
    cout << "time: " << time(0) - begin_time << "s" << endl;
}

// 测试发布消息的性能
void Cmd_Inter::test_03()
{
    string temp_id = "test03";
    int begin_pos = db->db_dat_alloc(USER_SUM_LENGTH);
    write_id(begin_pos, temp_id);
    write_exist(begin_pos, "Y");
    write_password(begin_pos, temp_id);
    write_name(begin_pos, "test03");
    write_sex(begin_pos, 1);
    write_birth_year(begin_pos, 1);
    write_birth_month(begin_pos, 1);
    write_birth_day(begin_pos, 1);
    write_hometown(begin_pos, "hometown");
    write_phone(begin_pos, "phone");
    db->db_link_idx_key(begin_pos, temp_id);
    id_pos = begin_pos;
    id_name = "test03";
    time_t begin_time = time(0);
    int test_times = 1000000;
    for (int i = 0; i < test_times; i++)
    {
        //cout << 100*float(i)/(test_times)  << "%" << endl;
        write_message(id_pos, "test03");
    }
    cout << "time: " << time(0) - begin_time << "s" << endl;
}

// 测试发布消息的正确性
void Cmd_Inter::test_04()
{
    string temp_id = "test04";
    int begin_pos = db->db_dat_alloc(USER_SUM_LENGTH);
    write_id(begin_pos, temp_id);
    write_exist(begin_pos, "Y");
    write_password(begin_pos, temp_id);
    write_name(begin_pos, "test04");
    write_sex(begin_pos, 1);
    write_birth_year(begin_pos, 1);
    write_birth_month(begin_pos, 1);
    write_birth_day(begin_pos, 1);
    write_hometown(begin_pos, "hometown");
    write_phone(begin_pos, "phone");
    db->db_link_idx_key(begin_pos, temp_id);
    id_pos = begin_pos;
    int test_times = 1000000;
    for (int i = 0; i < test_times; i++)
    {
        cout << 100*float(i)/(test_times)  << "%" << endl;
        stringstream ss;
        ss << i;
        string temp_message = ss.str();
        write_message(id_pos, temp_message);
    }
    vector<int> save_message_pointer = get_one_s_message(id_pos);
    for (int i = 0; i < test_times; i++)
    {
        stringstream ss;
        ss << i;
        if (!(get_mes_body(save_message_pointer[test_times-1-i]) == ss.str()))
        {
            cout << get_mes_body(save_message_pointer[i]);
            cout << endl << ss.str() << endl;
            cout << "Message correctness error." << endl;
            exit(0);
        }
    }
    cout << "Message correctness success." << endl;
}

