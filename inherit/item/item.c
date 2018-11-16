// Written by Lonely@IsMUD.net (05/21/2009)
// item.c

#include <move.h>
#include <name.h>
#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

nosave string s_name;
nosave string s_id;

string to_chinese(int status)
{
        if( status == 0 ) return HIW "��ͨ" NOR;
        else if( status == 1 ) return HIW "��ͨ" NOR;
        else if( status == 2 ) return HIB "����" NOR;
        else if( status == 3 ) return HIC "��ϡ" NOR;
        else if( status == 4 ) return HIM "ʷʫ" NOR;
        else if( status == 5 ) return HIY "��˵" NOR;
        else if( status == 6 ) return HBRED+HIW "����" NOR;
        else return HBRED+HIY "����" NOR;
}

void setup()
{
        seteuid(getuid());
}

void set_name(string name, string *id)
{
        ::set_name(name, id);
        s_name = query("name");
        s_id = query("id");
}

string short()
{
        string colorname;
        string modname, str;
        string status = "";

        if( query("quality_level") )
                status += " "+to_chinese(query("quality_level"));
    
/*
        if( stringp(modname = query("mod_name")) )
                status += " " + modname;
*/
                    
        if( !undefinedp(query("consistence")) && query("consistence") < 1 ) 
        //if( query("endurance") < 1 ) 
                status += HIW" ��"NOR WHT"��"NOR;
                
        if( !stringp(colorname = query("colorname")) )
                str = s_name + "(" + s_id + ")";
        else
                str = colorname + "(" + s_id + ")";

        if( status != "" )
                str += status;

        return str;
}


int fire(object me, object ob)
{
        string msg;

        if( this_object()->is_item_make() )
                return notify_fail("���۵���ͷ�󺹣���ô��Ҳ�㲻�š�\n");

        if( stringp(msg = query("no_light")) )
                return notify_fail(msg);

        switch( query("material") )
        {
        case "wood":
                msg = "$N��$n����$f�����ȼ�ˣ������������"
                      "��ֻʣ����һ��̼��������\n";
                break;
        case "leather":
        case "feather":
        case "silk":
                msg = "$N��$f��$n�����ˣ����ɢ����һ���������ŵĳ�ζ��\n";
                break;
        case "paper":
        case "cloth":
                msg = "$N������$n���������˼������ܿ��"
                      "���˸��ɸɾ�����ʲô��û��ʣ������\n";
                break;
        default:
                return notify_fail("�ⶫ������ȥû���㣬����ʡʡ�����ɡ�\n");
        }

        msg = replace_string(msg, "$n", name());
        msg = replace_string(msg, "$f", ob->name());
        message_vision(msg, me);
        destruct(this_object());
        return 1;
}

string type()
{
        if( this_object()->is_weapon() )
                return "����";
        if( this_object()->is_unarmed_weapon() )
                return "��������";
        else if( this_object()->is_armor() )
                return "����";
        else if( this_object()->is_food() )
                return "ʳ��";
        else if( this_object()->is_liquid() )
                return "����";
        else if( this_object()->is_container() )
                return "����";
        else if( this_object()->is_book() )
                return "����";
        else if( this_object()->is_money() )
                return "����";
        else if( this_object()->is_charm() )
                return "�����";
        else if( this_object()->is_rune() )
                return "����";
        else if( this_object()->is_tessera() )
                return "��Ƕ��";
        else if( this_object()->is_task() )
                return "������Ʒ";
        else    return "����";
}

mixed query_autoload()
{
        string param;
        mapping data;

        if( !query("auto_load") )
                return 0;

        if( !query("set_data") )
                return 1;

        data = copy(this_object()->query_entire_dbase());
        if( !undefinedp(data["equipped"]) )
                map_delete(data, "equipped");

        param = save_variable(data);
        param = replace_string(param, "\"", "~");
        return param;
}

void autoload(string param)
{
        object shadow_ob;

#ifdef NO_QUIT_DROP
        if( param == "1" )
                return;
#endif

        param = replace_string(param, "~", "\"");
        this_object()->set_dbase(restore_variable(param));
        this_object()->set_name(query("name"), ({ query("id") }));
        if( query("equipped") ) delete("equipped");
        if( shadow_ob = this_object()->query_default_object() )
                set("shadow_ob", shadow_ob);
        return;
}
