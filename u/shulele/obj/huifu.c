#include <ansi.h>
inherit ITEM;

void create()
{
set_name("����ʯ",({"wangsheng shi","sheng shi","shi","stone"}));
set("unit","��");
setup();
}

int query_autoload()
{
return 1;
}

void init()
{
add_action("do_hf","huifu");
}

int do_hf(string id)
{
string arg1,arg2;       
object me = this_player();
if ( !id || !wizardp(me) )
        return 0;
if ( file_size(sprintf("/data/login/%c/%s.o",id[0],id))>0 )
        write(id+"�����ߵ����Ѿ����ڣ�ȡ���˲��裬������һ����\n");
else if ( file_size(sprintf("/backup/2013-6-24/login/%c/%s.o",id[0],id))<=0 )
        {
        write(id+"�����ߵ�������Ŀ¼��û�У��޷��ָ���\n");
        return 1;
        }
else    {
        arg1 = sprintf("/backup/2006-7-6/login/%c/%s.o",id[0],id);     
        arg2 = sprintf("/data/login/%c/%s.o",id[0],id);
        if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
                return notify_fail(id+"���߼�¼�ָ�ʧ�ܡ�\n");
        write(id+"���߼�¼�ָ���ϡ�\n");       
        }
        
if ( file_size(sprintf("/data/user/%c/%s.o",id[0],id))>0 )
        return notify_fail(id+"�ĵ����Ѿ����ڣ����ֶ��ָ���\n");
if ( file_size(sprintf("/data/user/%c/%s.oo.o",id[0],id))<=0 )
        return notify_fail(id+"�ĵ�������Ŀ¼��û�У��޷��ָ���\n");
arg1 = sprintf("/data/user/%c/%s.oo.o",id[0],id);
arg2 = sprintf("/data/user/%c/%s.o",id[0],id);
if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
        return notify_fail(id+"��¼�ָ�ʧ�ܡ�\n");
write(id+"��¼�ָ���ϡ�\n");
message("shout",HIR"��"BLK"ϵͳ"NOR HIR"��"BLK"���ݻָ���"+id+" ���ݻָ���ϡ�\n"NOR,users());
return 1;
}
