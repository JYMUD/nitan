#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY"����"NOR, ({ "luo pan", "luo", "pan", "compass" }));
        set("weight", 1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
                set("long", "һֻ������������̣����Զ�λ(dingwei)���Ǻ����ߵıر���Ʒ��\n" NOR);
                set("value", 5000);
        }
        setup();
}

void init()
{ 
  add_action("do_dingwei","dingwei");
}
        
int do_dingwei()
{
    int stepe,stepw,steps,stepn;
    object me, where;
    string msg;
    me = this_player();
    where = environment(me);
    if( query("outdoors", where) != "��" )
        return notify_fail("����û�����������̸��\n");
    if( query("exits/out", where) || query("boat_of", where) )
           return notify_fail("����û���ء�\n");     
    message_vision("$N��$n�������ģ���ϸ�ز쿴�����ڵķ�λ��\n",me,this_object());
    msg = "\n������ʾ�����ڵ�λ�ڻƵ���";
    stepe=query_temp("stepe", where);
    stepw=query_temp("stepw", where);
    steps=query_temp("steps", where);
    stepn=query_temp("stepn", where);
    if(stepe) msg += "�Զ�"+chinese_number(stepe)+"������";
    if(stepw) msg += "����"+chinese_number(stepw)+"������";
    if(steps) msg += "������"+chinese_number(steps)+"������";
    if(stepn) msg += "���Ա�"+chinese_number(stepn)+"������";
    if(!stepe && !stepw && !steps && !stepn) msg += "����";
    msg += "�ĵط���\n"; 
    write(msg);
    return 1;
}