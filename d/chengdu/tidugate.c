#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ᶽ����");
        set("long", @LONG
������ᶽ���š�Ρ����ΰ�ĳ�ǽ�ϣ��ɶ��ᶽ���������ʮ��
���ۣ����ƻԻ͡������ױ��������ԡ�
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "south" : __DIR__"guangchang",
            "north" : __DIR__"tidufu",
        ]));
        set("objects", ([
            __DIR__"npc/qinbing" : 2,
        ]));
        set("coor/x", -15220);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        int i;
        object bing;

        bing = present("qin bing", environment(me));
        if (dir != "north" || ! objectp(bing) || ! living(bing))
                return ::valid_leave(me, dir);

        if( query("weiwang", me) >= 10000 )
        {
                message_vision(CYN "$N" CYN "Ц����" + RANK_D->query_respect(me) +
                               "�������������ȥ����ͨ����\n" NOR, bing, me);
                return ::valid_leave(me, dir);
        }

        if( query("special_skill/trick", me) )
        {
                message_vision(CYN "$N" CYN "����$n" CYN "���˹�����������ס��ȴ"
                               "��$n" CYN "һ���Ϻȣ�����ɢ����\n$N" CYN "���ɵ�"
                               "����һ����ڨڨ�Ĳ���˵����\n" NOR, bing, me);
                return ::valid_leave(me, dir);
        }

        return notify_fail(CYN "�ױ���ǰ��ס�㣬����˵������λ" +
                           RANK_D->query_respect(me) + "��ذɡ���ү�����͡�\n" NOR);
}