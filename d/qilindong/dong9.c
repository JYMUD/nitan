// Room: dong9.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIR "�����" NOR);
        set("long", HIR "\n\n" 
"��������ߡ������پ�һ��������������������������\n"
"��ȥ������һƬͨ�죬������ð��˿˿�������ŵ׾��ҵ���ʹ\n"
"ʹ�㼸�����Ų�ס���ȷ����¡¡�������Ŷ��ģ��������\n"
"������¯֮�У�ȫ����ˮ�ֶ��ڱ�һ�εεؿ��ɡ���е�����\n" 
"�������ȥ����\n\n" NOR 
     ); 
        set("exits", ([
                "east"      : __DIR__"dong1",
                "south"     : __DIR__"dong2",
                "west"      : __DIR__"qilindong",
                "north"     : __DIR__"dong1",
	]));
	setup();
}

void init()
{
        object me = this_player();

        me->set_temp("die_reason", "��������ߣ�������������");
        me->receive_damage("qi", 500);
        me->receive_wound("qi",  500);
        message_vision(HIR "�����һ����ܣ�����Ϯ��$N��$N�������ˣ�\n" NOR, me);
}
