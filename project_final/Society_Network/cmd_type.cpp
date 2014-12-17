#include "cmd_type.h"

Cmd_Type::Cmd_Type()
{
    command_operate = 0;
    command_data = "";
}

void Cmd_Type::init()
{
    valid = false;
    command_operate = 0;
    command_data = "";
}

void Cmd_Type::set_valid(bool input)
{
    valid = input;
}

bool Cmd_Type::is_valid()
{
    return valid;
}

bool Cmd_Type::is_empty()
{
    return (command_operate == 0 && command_data == "");
}

void Cmd_Type::add_operate(int _command_operate)
{
    command_operate = _command_operate;
}

void Cmd_Type::add_data(string _command_data)
{
    command_data = _command_data;
}

int Cmd_Type::get_operate()
{
    return command_operate;
}

string Cmd_Type::get_data()
{
    return command_data;
}
