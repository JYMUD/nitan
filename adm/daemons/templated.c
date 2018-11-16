// This program is a part of NITAN MudLIB
// templated.c
// jjold.c

// ģ�徫�鹤�������̣�

// һ�����������ʽ
//  1�����ģ���׼�ļ�����������׼�����
//  2�����ģ���ļ���Ҫ����� DBASE �ĸ�ʽ��
//  3�����������������ݣ����ݴ���Ĳ���(arg)�ҵ�������������ݡ�
//  4�������ר�ŵĻ�׼������򴴽�ר�ŵġ�
//  5���趨 DBASE(m[DBASE_KEY1] = DBASE VALUE)��
//  6�����л�׼����еĺ���(call_other(ob, "function", argument))��
//  7�����ظ������

// ģ���ļ�׼�������ݽṹ��
// mixed *dbase_format = ({ DBASE_KEY1, DBASE_KEY2, });
// mapping object_data = ({ "arg1" : ({ ({ DBASE_VALUE1, DBASE_VALUE2, }),
//                         ([ "function1" : ({ argument1, }) ]), }) });
// ������ṹ
// mapping object_data = ({ "arg1" : ({ ([ DBASE_KEY1 : DBASE_VALUE1, DBASE_KEY2 : DBASE_VALUE2, ]),
//                         ([ "function1" : ({ argument1, }) ]), , "extra_base_file", }) });

// ģ������ṩ�Ľӿں�����
// query_base_file()       - ��׼�����
// query_dbase_format()    - dbase ��ʽ
// query_function_format() - function ��ʽ
// query_entire_data()     - ��������
// query_template_data()   - ָ��������

#include <ansi.h>
#include <template.h>


#define COMMENT_ENTRY   "/* COMMENT_ENTRY */"
#define COMMENT_EXIT    "/* COMMENT_EXIT  */"

#define NAME_ENTRY      "/* NAME_ENTRY */"
#define NAME_EXIT       "/* NAME_EXIT  */"

#define DBASE_ENTRY     "/* DBASE_ENTRY */"
#define DBASE_EXIT      "/* DBASE_EXIT  */"

#define FUNCTION_ENTRY  "/* FUNCTION_ENTRY */"
#define FUNCTION_EXIT   "/* FUNCTION_EXIT  */"

#ifdef DEBUG
#define monitor(x)              CHANNEL_D->do_channel(this_object(), "sys", x)
#else
#define monitor(x)
#endif

// �������
varargs object create_object(string file, string arg, mapping dbase_data,
                             int model, mapping function_data)
{
        object  tob;     // ģ�����
        object  ob;      // ���������

        string  template;// ģ���ļ���
        string  type;    // ��������

        int     full;    // �Ƿ��� data ��ָ�� key �� value
        mixed   format;  // dbase��function ��ʽ
        mixed   data;    // ����
        mixed   key;     // ����(mapping)�е�һ�� key
        mapping dbase;   // ����� dbase
        int     i, max;  // ������
        object  shadow_ob;
        mapping applied_prop, temp;
        string *apply;

        if( file[<2..<1] != FILE_EXTENSION )
                file += FILE_EXTENSION;

        if( file_size(file) < 1 )
                return 0;

        if( !objectp(tob = find_object(file)) &&
                catch(tob = load_object(file)) )
                return 0;

        if( !sscanf(file, TEMPLATE_DIR "%s.c", template) ) {
                // ��ģ���ļ��������
                if( !objectp(ob = new(file)) )
                        return 0;

                dbase = ob->query_entire_dbase();
                if( sizeof(dbase_data) ) {
                        format = keys(dbase_data);
                        foreach( key in format ) {
                                if( !model )
                                        dbase[key] = dbase_data[key];
                                else 
                                {
                                        if( mapp(dbase[key]) && mapp(dbase_data[key]) )
                                        {
                                                applied_prop = copy(dbase[key]);
                                                temp = copy(dbase_data[key]);
                                                apply = keys(temp);
                                                for( i = 0; i < sizeof(apply); i++ )
                                                {                                                                                                
                                                        if( undefinedp(applied_prop[apply[i]]) )
                                                                applied_prop[apply[i]] = temp[apply[i]];
                                                        else
                                                        {
                                                                if( (mapp(applied_prop[apply[i]]) && mapp(temp[apply[i]])) || 
                                                                    (arrayp(applied_prop[apply[i]]) && arrayp(temp[apply[i]])) ) 
                                                                        applied_prop[apply[i]] = applied_prop[apply[i]] + temp[apply[i]];
                                                                else
                                                                        applied_prop[apply[i]] = temp[apply[i]];
                                                        }
                                                }
                                                dbase[key] = copy(applied_prop);
                                        }
                                        else if( arrayp(dbase[key]) && arrayp(dbase_data[key]) )
                                                dbase[key] = dbase[key] + dbase_data[key];
                                        else
                                                dbase[key] = dbase_data[key];
                                }
                        }

                        if( shadow_ob = ob->query_default_object() ) 
                                dbase["shadow_ob"] = shadow_ob;

                        dbase["set_data"] = 1;
                }

                // ��������
                if( member_array(F_NAME, deep_inherit_list(ob)) != -1 ) {
                        if( !undefinedp(dbase_data["name"]) )
                                ob->set_name(dbase_data["name"], ({ arg }));
                        else
                                X_NameD->x_name(ob, arg);

                        dbase["set_data"] = 1;
                }

                if( sizeof(function_data) ) {
                        set("function", function_data, ob);
                        format = keys(function_data);
                        foreach( key in format )
                                call_other(ob, key, function_data[key]);
                }

                return ob;
        }

        // ģ���ļ��������
        if( !arrayp(data = tob->query_template_data(arg)) || !sizeof(data) )
                return 0;

        // �Ƿ���ר�ŵĻ�׼�ļ���
        if( sizeof(data) > EXTRA_BASE_DATA )
                file = data[EXTRA_BASE_DATA];

        if( sizeof(data) <= EXTRA_BASE_DATA || file_size(file) <= 0 ) {
                // ���޻�׼����ļ�
                if( !stringp(file = tob->query_base_file()))
                        return 0;
        }

        // ���ݻ�׼�ļ�����������ܷ���أ�
        if( !objectp(ob = new(file)) )
                return 0;

        // ���� dbase ����
        if( !arrayp(format = tob->query_dbase_format()) || !sizeof(format) )
                full = 1;
        else    full = 0;

        // ��ģ���е� dbase ����ת�������
        dbase = ob->query_entire_dbase();
        switch (full)
        {
        // ����ȫ��ʽģʽ
        case 1:
                if( !mapp(data[DBASE_DATA]) ||
                    !sizeof(data[DBASE_DATA]) )
                        return 0;

                format = keys(data[DBASE_DATA]);
                foreach( key in format )
                        dbase[key] = data[DBASE_DATA][key];

                break;
        // ���ø�ʽ��Ӧģʽ
        default:
                if( !arrayp(format) )
                        return 0;

                // �����ʽ��ֻ��һ��������ֲ��������͵ģ�
                // ��ֱ�Ӱ� dbase �е���Ψһ�ĸ�ʽ��Ϊ���ݡ�
                max = sizeof(format);
                if( max == 1 && !arrayp(data[DBASE_DATA]) )
                        dbase[format[0]] = data[DBASE_DATA];
                else {
                        for (i = 0; i < max; i++)
                                dbase[format[i]] = data[DBASE_DATA][i];
                }

                break;
        }

        // �����ⲿ����� dbase_data ����
        if( sizeof(dbase_data) ) {
                format = keys(dbase_data);
                foreach( key in format ) {
                        if( !model )
                                dbase[key] = dbase_data[key];
                        else 
                        {
                                if( mapp(dbase[key]) && mapp(dbase_data[key]) )
                                {
                                        applied_prop = copy(dbase[key]);
                                        temp = copy(dbase_data[key]);
                                        apply = keys(temp);
                                        for( i = 0; i < sizeof(apply); i++ )
                                        {                                                                                                
                                                if( undefinedp(applied_prop[apply[i]]) )
                                                        applied_prop[apply[i]] = temp[apply[i]];
                                                else
                                                {
                                                        if( (mapp(applied_prop[apply[i]]) && mapp(temp[apply[i]])) || 
                                                            (arrayp(applied_prop[apply[i]]) && arrayp(temp[apply[i]])) ) 
                                                                applied_prop[apply[i]] = applied_prop[apply[i]] + temp[apply[i]];
                                                        else
                                                                applied_prop[apply[i]] = temp[apply[i]];
                                                }
                                        }
                                        dbase[key] = copy(applied_prop);
                                }
                                if( arrayp(dbase[key]) && arrayp(dbase_data[key]) )
                                        dbase[key] = dbase[key] + dbase_data[key];
                                else
                                        dbase[key] = dbase_data[key];
                        }

                        if( shadow_ob = ob->query_default_object() ) 
                                dbase["shadow_ob"] = shadow_ob;

                        dbase["set_data"] = 1;
                }
        }

        if( member_array(F_NAME, deep_inherit_list(ob)) != -1 ) {
                // ��������
                if( !undefinedp(dbase_data["name"]) ) {
                        i = strsrch(template, "/") + 1;
                        type = template[i..<1];

                        ob->set_name(dbase_data["name"], ({ arg, type }));
                } else
                        ob->set_name(dbase["name"], ({ arg, type }));

                dbase["set_data"] = 1;
        }

        // �Ƿ�Ԥ���� function (ģ�����ݵĵڶ���)�ĸ�ʽ��
        // ���ޣ������ȫ��ʽģʽ����ģ�����ݵ�����Ϊ
        // mapping������Ͳ��� array ��ʽ��
        if( !arrayp(format = tob->query_function_format()) || !sizeof(format) )
                full = 1;
        else
                full = 0;

        // ���к�������
        // ���������ģ����ָ���ĺ���
        if( sizeof(data) > FUNCTION_DATA &&
           // (mapp(data[FUNCTION_DATA]) || arrayp(data[FUNCTION_DATA])) &&
           sizeof(data[FUNCTION_DATA]) ) {
                // ʹ��ȫ��ʽģʽ
                if( full ) {
                        format = keys(data[FUNCTION_DATA]);

                        foreach( key in format ) {
                                monitor(sprintf("create_objectִ��%O->%s(%O)", ob, key,
                                                data[FUNCTION_DATA][key]));
                                call_other(ob, key, data[FUNCTION_DATA][key]);
                        }
                } else { // ʹ�ø�ʽ��Ӧģʽ
                        if( !arrayp(format) )
                                return 0;

                        // �����ʽ��ֻ��һ��������ֲ��������͵ģ�
                        // ��ֱ������һ��Ϊ���������Ǹ�������
                        if( sizeof(format) == 1 && !arrayp(data[FUNCTION_DATA]) )
                                call_other(ob, format[0], data[FUNCTION_DATA]);
                        else {
                                max = sizeof(format);

                                for( i = 0; i < max; i++ ) {
                                        // ����������������
                                        if( undefinedp(data[DBASE_DATA][i]) )
                                                call_other(ob, format[i]);
                                        else
                                                call_other(ob, format[i], data[DBASE_DATA][i]);
                                }
                        }
                }
        }

        // �����ⲿ����� function_data ����
        if( sizeof(function_data) ) {
                dbase["function"] = function_data;
                format = keys(function_data);
                foreach( key in format )
                        call_other(ob, key, function_data[key]);
        }

        return ob;
}

// add mapping
protected string prop_segment(mapping p, string path)
{
        string path2;
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path2 = path + ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path2);
                } else
                {
                        if( stringp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", \"%s\");\n",
                                       path + ks[i], (string)p[ks[i]]);
                        else
                        if( intp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %d);\n",
                                       path + ks[i], (int)p[ks[i]]);
                }
        }

        return buf;
}

// ����Ϊ�ļ�
varargs string create_file(string tfile, string arg, mapping dbase_data,
                           int model, mapping function_data)
{
        string  bfile;          // ��׼����ļ���
        string  cfile;          // ��������ļ���
        string  type;           // �������
        string  name;

        string  template;       // ģ���ļ���
        string *content;        // ������ļ�����
        string  content_str;    // ������ļ�����
        string  content_line;   // ������һ�е�����

        int     i;              // ������
        int     n;              // �ļ�����
        int     l;
        int     j;              // ������
        int     k;              // dbase / ������Ŀ
        string  t;              // ��ǰʱ��

        int     comment_on;     // ������дע��
        int     dbase_on;       // ������д dbase ����
        int     function_on;    // ������д��������

        object  tob;            // ģ�����
        object  ob;

        int     full_dbase;     // �Ƿ����� dbase ��ʽ
        int     full_function;  // �Ƿ�����������ʽ

        string *dbase_format;   // dbase ��ʽ
        string *function_format;// ������ʽ
        string  temp_str1;
        string  temp_str2;

        mixed   data;           // ģ������
        mixed   format;         // dbase��function ��ʽ
        mixed   key;            // ����(mapping)�е�һ�� key
        mixed   dbase;

        if( tfile[<2..<1] != FILE_EXTENSION )
                tfile += FILE_EXTENSION;

        if( file_size(tfile) < 1 )
                return 0;

        if( !objectp(tob = find_object(tfile)) &&
                catch(tob = load_object(tfile)) )
                return 0;

        if( !sscanf(tfile, TEMPLATE_DIR "%s.c", template) ) {
                data = tob->query_entire_dbase();

                if( sizeof(dbase_data) && !undefinedp(dbase_data["name"]) ) {
                        name = dbase_data["name"];
                        map_delete(dbase_data, "name");
                } else
                        name = data["name"];

                if( sizeof(dbase_data) && !undefinedp(dbase_data["id"]) )
                        map_delete(dbase_data, "id");

                if( sizeof(dbase_data) && !undefinedp(dbase_data["shadow_ob"]) )
                        map_delete(dbase_data, "shadow_ob");

                while( 1 ) {
                        // ���ɴ�������ļ���
                        cfile = sprintf("%sunknow/%s-%d.c", TEMPLATE_DATA, arg, time() + random(99999999));
                        // ���ո��滻Ϊ "_"
                        cfile = replace_string(cfile, " ", CONNECT_CHAR);
                        if( file_size(cfile) == -1 )
                                break;
                }

                assure_file(cfile);
                content_str = read_file(tfile);
                content_str = replace_string(content_str, "\r", "");
                content = explode(content_str, "\n");

                n = sizeof(content);
                t = ctime(time());
                content_str = "";

                for( i = 0; i < n; i++ ) {
                        // �ҵ������ⲿ���� dbase_data ���ݵ�λ��
                        temp_str1 = content[i];
                        temp_str1 = replace_string(temp_str1, " ", "");

                        if( !j && strsrch(temp_str1, "setup\(") != -1 )
                                j = i;

                        if( strsrch(temp_str1, "set_name") != -1 )
                                content[i] = sprintf("\tset_name(\"%s\", ({ \"%s\" }));",
                                                     name, arg);

                        // �����ⲿ���� dbase_data ���ļ��������ص�����
                        if( sizeof(dbase_data) ) {
                                format = keys(dbase_data);
                                foreach (key in format)
                                if( strsrch(temp_str1, sprintf("set\(\"%s\"", key)) != -1
                                ||  strsrch(temp_str1, sprintf("set\(\"%s/", key)) != -1 ) {
                                        dbase_on = 1;

                                        if( !model )
                                                dbase = dbase_data[key];
                                        else {
                                                if( (mapp(data[key]) && mapp(dbase_data[key])) ||
                                                    (arrayp(data[key]) && arrayp(dbase_data[key])) )
                                                        dbase = data[key] + dbase_data[key];
                                                else
                                                        dbase = dbase_data[key];
                                        }
                                        // �����и��Ű������
                                        content[i] = sprintf("\tset\(\"%s\", %O\);",
                                                             key, dbase);
                                                             
                                        l = i;
                                        while( l < (n -1) ) {
                                                l++;
                                                temp_str2 = content[l];
                                                temp_str2 = replace_string(temp_str2, " ", "");
                                                if( dbase_on && (strsrch(temp_str2, "set_") != -1 ||
                                                    strsrch(temp_str2, "set\(") != -1 ||
                                                    strsrch(temp_str2, "init") != -1 ||
                                                    strsrch(temp_str2, "if") != -1 ||
                                                    strsrch(temp_str2, "else") != -1 ||
                                                    strsrch(temp_str2, "setup\(") != -1 ||
                                                    strsrch(temp_str2, "}") != -1) )
                                                        dbase_on = 0;

                                                if( dbase_on ) {
                                                        content[l] = "";
                                                        continue;
                                                }

                                                if( strsrch(temp_str2,sprintf("set\(\"%s\"", key)) != -1
                                                ||  strsrch(temp_str2, sprintf("set\(\"%s/", key)) != -1 ) {
                                                        dbase_on = 1;
                                                        content[l] = "";
                                                }
                                        }

                                        map_delete(dbase_data, key);
                                }
                        }

                        if( sizeof(function_data) ) {
                                format = keys(function_data);
                                for (k = 0; k < sizeof(format); k++ ) {
                                        if( strsrch(temp_str1, sprintf("%s", format[k])) != -1 ) {
                                                content[i] = sprintf("\t%s(%O);",
                                                                     format[k],
                                                                     function_data[format[k]]);
                                                break;
                                        }
                                }
                        }
                }

                content_line = sprintf("// %s.c\n", replace_string(arg, " ", CONNECT_CHAR));
                content_line += sprintf("// Create by TEMPLATE_D. %s.", t);

                // д��һ��
                content_str += content_line + "\n";

                for( i = 0; i < j; i++ )
                        content_str += content[i] + "\n";

                // �����ⲿ���� dbase_data ����
                content_str += prop_segment(dbase_data, "");
                /*
                if( sizeof(dbase_data) ) {
                        format = keys(dbase_data);
                        foreach( key in format )
                                content_str += sprintf("\tset\(\"%s\", %O\);\n",
                                                       key, dbase_data[key]);
                }
                */

                for( i = j; i < n; i++ )
                        content_str += content[i] + "\n";

                // ��receive_summon�ӿ�
                content_str += @SUMMON
int receive_summon(object me)
{
        return ITEM_D->receive_summon(me, this_object());
}

// ������Ʒ
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}

SUMMON;
                // �����ļ�
                write_file(cfile, content_str, 1);

                // �����ļ�
                return cfile;
        }

        // ģ�������Ƿ���ϸ�ʽ��
        if( !arrayp(data = tob->query_template_data(arg)) || !sizeof(data))
                return 0;

        // �Ƿ���ר�ŵĻ�׼�ļ���
        if( sizeof(data) > EXTRA_BASE_DATA)
                bfile = data[EXTRA_BASE_DATA];
        // ����ʹ��Ԥ��Ļ�׼�ļ�
        else
                bfile = tob->query_base_file();

        if( !stringp(bfile) || file_size(bfile) < 1)
                return 0;

        if( !objectp(ob = get_object(bfile)))
                return 0;

        if( sizeof(dbase_data) && !undefinedp(dbase_data["name"]))
        {
                name = dbase_data["name"];
                map_delete(dbase_data, "name");
        } else
                name=query("name", ob);

        while(1)
        {
                // ���ɴ�������ļ���
                cfile = sprintf("%s%s/%s-%d.c", TEMPLATE_DATA, template, arg, time() + random(99999999));
                // ���ո��滻Ϊ "_"
                cfile = replace_string(cfile, " ", CONNECT_CHAR);
                if( file_size(cfile) == -1)
                        break;
        }

        // ׼��������������

        // �Ƿ�Ԥ���� dbase (ģ�����ݵĵ�һ��)�ĸ�ʽ��
        if( !arrayp(dbase_format = tob->query_dbase_format()) ||
            !sizeof(dbase_format))
                full_dbase = 1;
        else
                full_dbase = 0;

        // �Ƿ�Ԥ���˺���(ģ�����ݵĵڶ���)�ĸ�ʽ��
        if( !arrayp(function_format = tob->query_function_format()) ||
            !sizeof(function_format))
                full_function = 1;
        else
                full_function = 0;

        // ��ʼ����

        assure_file(cfile);

        content_str = read_file(bfile);
        content_str = replace_string(content_str, "\r", "");
        content = explode(content_str, "\n");

        n = sizeof(content);
        t = ctime(time());
        content_str = "";

        i = strsrch(template, "/") + 1;
        type = template[i..<1];

        for (i = 0; i < n; i++)
        {
                // ��дע��
                if( strsrch(content[i], COMMENT_ENTRY) != -1 && !comment_on)
                {
                        comment_on = 1;
                        content_line = sprintf("// %s.c\n", replace_string(arg, " ", CONNECT_CHAR));
                        content_line += sprintf("// Create by TEMPLATE_D. %s.", t);

                        // д��һ��
                        content_str += content_line + "\n";
                        continue;
                }

                if( strsrch(content[i], NAME_ENTRY) != -1)
                {
                        content_line = sprintf("\tset_name(\"%s\", ({ \"%s\", \"%s\" }));",
                                               name, arg, type);
                        content_str += content_line + "\n";
                        continue;
                }

                // ��д dbase ����
                if( strsrch(content[i], DBASE_ENTRY) != -1)
                {
                        dbase_on = 1;

                        // ʹ�ø�ʽ��Ӧģʽ
                        if( !full_dbase)
                        {
                                if( !arrayp(dbase_format))
                                        continue;

                                k = sizeof(dbase_format);

                                if( k == 1 && !arrayp(data[DBASE_DATA]))
                                {
                                        dbase = data[DBASE_DATA];
                                        if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[0]]))
                                        {
                                                if( !model)
                                                        dbase = dbase_data[dbase_format[0]];
                                                else
                                                {
                                                        if( mapp(dbase) && mapp(dbase_data[dbase_format[0]]))
                                                                dbase = dbase + dbase_data[dbase_format[0]];
                                                        else
                                                                dbase = dbase_data[dbase_format[0]];
                                                }
                                                map_delete(dbase_data, dbase_format[0]);
                                        }
                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               dbase_format[0], dbase);
                                        content_str += content_line + "\n";
                                } else
                                {
                                        for (j = 0; j < k; j++)
                                        {
                                                dbase = data[DBASE_DATA][j];
                                                if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[j]]))
                                                {
                                                        if( !model)
                                                                dbase = dbase_data[dbase_format[j]];
                                                        else
                                                        {
                                                                if( (mapp(dbase) && mapp(dbase_data[dbase_format[j]])) ||
                                                                    (arrayp(dbase) && arrayp(dbase_data[dbase_format[j]])))
                                                                        dbase = dbase + dbase_data[dbase_format[j]];
                                                                else
                                                                        dbase = dbase_data[dbase_format[j]];
                                                        }
                                                        map_delete(dbase_data, dbase_format[j]);
                                                }
                                                if( stringp(dbase))
                                                        dbase = replace_string(dbase, "\n", "\\n");

                                                content_line = sprintf("\t\tset(\"%s\", %O);",
                                                                       dbase_format[j], dbase);
                                                content_str += content_line + "\n";
                                        }
                                }
                        } else
                        // ʹ��ȫ��ʽģʽ
                        {
                                if( !mapp(data[DBASE_DATA]) || !sizeof(data[DBASE_DATA]))
                                        continue;

                                dbase_format = keys(data[DBASE_DATA]);
                                k = sizeof(dbase_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[DBASE_DATA][dbase_format[j]];
                                        if( sizeof(dbase_data) && !undefinedp(dbase_data[dbase_format[j]]))
                                        {
                                                if( !model)
                                                        dbase = dbase_data[dbase_format[j]];
                                                else
                                                {
                                                        if( (mapp(dbase) && mapp(dbase_data[dbase_format[j]])) ||
                                                            (arrayp(dbase) && arrayp(dbase_data[dbase_format[j]])))
                                                                dbase = dbase + dbase_data[dbase_format[j]];
                                                        else
                                                                dbase = dbase_data[dbase_format[j]];
                                                }
                                                map_delete(dbase_data, dbase_format[j]);
                                        }

                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               dbase_format[j], dbase);
                                        content_str += content_line + "\n";
                                }
                        }

                        if( sizeof(dbase_data))
                        {
                                format = keys(dbase_data);
                                foreach (key in format)
                                {
                                        dbase = dbase_data[key];
                                        if( stringp(dbase))
                                                dbase = replace_string(dbase, "\n", "\\n");

                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               key, dbase);
                                        content_str += content_line + "\n";
                                }
                        }
                        continue;
                }

                // ��д��������
                if( strsrch(content[i], FUNCTION_ENTRY) != -1)
                {
                        function_on = 1;

                        // ʹ�ø�ʽ��Ӧģʽ
                        if( !full_function)
                        {
                                k = sizeof(function_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[FUNCTION_DATA][j];
                                        if( sizeof(function_data) && !undefinedp(function_data[function_format[j]]))
                                        {
                                                dbase = function_data[function_format[j]];
                                                map_delete(function_data, function_format[j]);
                                        }
                                        content_line = sprintf("\t%s(%O);",
                                                               function_format[j],
                                                               dbase);
                                        content_str += content_line + "\n";
                                }
                        } else
                        // ʹ��ȫ��ʽģʽ
                        {
                                if( !mapp(data[FUNCTION_DATA]) || !sizeof(data[FUNCTION_DATA]))
                                        continue;

                                function_format = keys(data[FUNCTION_DATA]);
                                k = sizeof(function_format);

                                for (j = 0; j < k; j++)
                                {
                                        dbase = data[FUNCTION_DATA][function_format[j]];
                                        if( sizeof(function_data) && !undefinedp(function_data[function_format[j]]))
                                        {
                                                dbase = function_data[function_format[j]];
                                                map_delete(function_data, function_format[j]);
                                        }
                                        content_line = sprintf("\t%s(%O);",
                                                               function_format[j],
                                                               dbase);
                                        content_str += content_line + "\n";
                                }
                        }

                        if( sizeof(function_data))
                        {
                                format = keys(function_data);
                                foreach (key in format)
                                {
                                        dbase = function_data[key];
                                        content_line = sprintf("\t\tset(\"%s\", %O);",
                                                               key, dbase);
                                        content_str += content_line + "\n";
                                }
                        }
                        continue;
                }

                // �����д������־

                // ��дע�ͽ���
                if( strsrch(content[i], COMMENT_EXIT) != -1)
                {
                        comment_on = 0;
                        continue;
                }

                // ��д���ƽ���
                if( strsrch(content[i], NAME_EXIT) != -1)
                        continue;

                // ��д dbase ����
                if( strsrch(content[i], DBASE_EXIT) != -1)
                {
                        dbase_on = 0;
                        continue;
                }

                // ��д��������
                if( strsrch(content[i], FUNCTION_EXIT) != -1)
                {
                        function_on = 0;
                        continue;
                }

                // ��������дע�ͣ�����
                if( comment_on) continue;

                // ��������д dbase������
                if( dbase_on) continue;

                // ��������д����������
                if( function_on) continue;

                // ����ֱ�������һ��
                content_str += content[i] + "\n";
        }

        // �����ļ�
        write_file(cfile, content_str, 1);

        // �����ļ�
        return cfile;
}
