// Room: /d/gumu/qianliu1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"Ǳ��"NOR);
        set("long", @LONG
��û��ˮ�У�ֻ��ˮ��������������޷����㡣�������쳣��ֻ��������
��Ǳ�У������ǽ���ά�ȡ�
LONG        );

        set("exits", ([
                "east"   : __DIR__"qianliu2",
                "westup" : __DIR__"anhe1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2990);
        set("coor/y", -50);
        set("coor/z", -30);
        setup();
}

void init()
{
        object me = this_player();

        me->receive_damage("qi", 50 );
        me->receive_damage("jing", 50 ); 
        message_vision(HIB"$N������������ʧ������ʮ�����ѡ�\n"NOR, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("last_damage_from", "��Ǳ���б���", me);
                me->unconcious();
                me->die();   
                return;
        }
}
