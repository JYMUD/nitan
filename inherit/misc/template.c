// template.c

#include <template.h>

nosave mixed  *dbase_format;    // dbase ��ʽ
nosave mixed  *function_format; // ������ʽ

nosave mapping template_data;   // ģ������
nosave string  base_file;       // ��׼�ļ�

// ����һ��ģ��
int is_template() { return 1; }

// ��ѯ dbase ��ʽ
mixed *query_dbase_format()
{
        return (sizeof(dbase_format) ? dbase_format : 0);
}

// ��ѯ������ʽ
mixed *query_function_format()
{
        return (sizeof(function_format) ? function_format : 0);
}

// ��ѯ��׼�ļ�
string query_base_file() { return sprintf("%s%s.c", BASIC_OB_DIR, base_file); }

// ��ѯȫ��ģ������
mapping query_entire_data() { return template_data; }

// ��ѯָ��ģ������
mixed *query_template_data(string template)
{
        if( undefinedp(template_data[template]) )
                return 0;

        return template_data[template];
}

void set_dbase_format(string *format)
{
        if( !arrayp(format) || !sizeof(format) )
                return;

        dbase_format = format;
}

void set_function_format(string *format)
{
        if( !arrayp(format) || !sizeof(format) )
                return;

        function_format = format;
}

// ���û�׼�ļ�
void set_base_file(string file)
{
        if( !stringp(file) || file == "" )
                return;

        base_file = file;
}

// ����ģ������
void set_template_data(mapping data)
{
        if( !mapp(data) || !sizeof(data) )
                return;

        template_data = data;
}

// ģ��ĳ�ʼ��
void setup()
{
        if( !this_object()->is_template() )
                return;
}
