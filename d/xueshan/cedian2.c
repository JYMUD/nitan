#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
������ѩɽ�µ����������ǽ��������ŷ��洫���Ĺ��£�
��������𻨱���ׯ�ϡ�
LONG );
        set("exits", ([
                "northup" : __DIR__"zoulang2",
                "east"    : __DIR__"dadian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/samu" : 1,
                __DIR__"npc/xiang-ke" : 3,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "ѩɽ��")
           && dir=="northup"
           && objectp(present ("samu huofo", environment(me)))) 
                return notify_fail(CYN "��ľ���˵�������ѩɽ��"
                                   "���ӣ��������ڡ�\n" NOR);

        return ::valid_leave(me,dir);
}