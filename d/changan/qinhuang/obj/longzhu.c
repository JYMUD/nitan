//mingzhu.c
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIB BLINK "����" NOR, ({ "long zhu" ,"zhu", }) );
        set_weight(100000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","���ǿ����ۣ�������ֵ����Ǯ��\n");
                set("value", 1000000);
                set("material", "dainomd");
              }
}
void init()
{
        if (environment()==this_player())
        add_action("do_pushin","pushin");
}
int do_pushin(string arg)
{
        object me=this_player();
        object room=environment(me);
        if(base_name(room) != "/d/changan/qinhuang/dadian3") return 0;
        if( query("in_zhu", room) == 2 )
                return 0;
        if( !query_temp("killer", me )
         || !query_temp("climb", me )
         || query_temp("chan", me) )
        return 0;
        message_vision("$N����һ��"+query("name")+"������ʯ�ŵĶ��ڡ�\n",me);
        addn("in_zhu", 1, room);
        if( query("in_zhu", room) == 2){
                room->open_door(me,1);
        }
        destruct(this_object());
        return 1;
}
