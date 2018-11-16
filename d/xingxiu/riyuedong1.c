// Room: /d/xingxiu/riyuedong1.c
// Last Modified by winder on Apr. 25 2001
#include <ansi.h>

string look_duilian();
inherit ROOM;
void create()
{
        set("short", "���¶���");
        set("long", @LONG
���������޺��ľ�ͷ��˵�Ǻ�����ʵ��Ƭ���������󣬵���ʮ����
�񡣷�Բ�����ﶼ��һ���޼ʵĺ��������󣬵��������˾ͳ�֮Ϊ����
����������������ͨ�����޺������������һ��Сʯɽ���������ܶ�
���¶������������������һ��ͭ������(paizi)��
LONG);
        set("exits", ([
                "north"     : __DIR__"riyuedong",
                //"west"      : __DIR__"xxh4",
                //"east"      : __DIR__"xxh3",
                "northwest" : __DIR__"xxhb2",
                "northeast" : __DIR__"xxhb1",
                "southdown" : __DIR__"huangdi",
        ]));
        set("item_desc", ([
                "paizi" : (: look_duilian :),
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/anran" : 1,
                CLASS_D("xingxiu")+"/first" : 1,
                //CLASS_D("xingxiu")+"/first" : 1,
                __DIR__"npc/gushou" : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou" : 1,
        ]) );
        set("valid_startroom","1");
        set("coor/x", -50000);
        set("coor/y", 20300);
        set("coor/z", 100);
        set("outdoors", "xingxiu");
        setup();
        "/clone/board/xingxiu_b"->foo();
        //replace_program(ROOM);
}

string look_duilian()
{
        return
        RED "\n"
        "        ��������������            ��������������\n"
        "        ��������������            ��������������\n"
        "        ����      ����            ����      ����\n"
        "        ����" NOR + HIW "���ǡ�" NOR + RED "����            ����" NOR + HIW "  ��  " NOR + RED "����\n"
        "        ������ �� ����            ����      ����\n"
        "        ����" NOR + HIW "  ��  " NOR + RED "����            ����" NOR + HIW "  ��  " NOR + RED "����\n"
        "        ����      ����            ����      ����\n"
        "        ����" NOR + HIW "  ��  " NOR + RED "����            ����" NOR + HIW "  ��  " NOR + RED "����\n"
        "        ����      ����            ����      ����\n"
        "        ����" NOR + HIW "  ��  " NOR + RED "����            ����" NOR + HIW "  ��  " NOR + RED "����\n"
        "        ����      ����            ����      ����\n"
        "        ����" NOR + HIW "  ��  " NOR + RED "����            ����" NOR + HIW "  ��  " NOR + RED "����\n"
        "        ����    ������            ����      ����\n"
        "        ��������������            ��������������\n"
        "        ��������������            ��������������\n\n\n" NOR;
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("anran zi", this_object())))
                return 1;

        if (dir == "north")
                return guarder->permit_pass(me, dir);


        return 1;
}
