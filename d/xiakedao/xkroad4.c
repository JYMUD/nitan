// Room: /d/xiakedao/xkroad4.c
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
        set("short", "�Ϻ����");
        set("long", @LONG
�����Ϻ��ذ���ƫƧС�壬ϡϡ����ļ����˼ҡ��յ������ż�
��������������ǲ��κ����Ϻ��ˡ������ߺ����и���ۡ�����
��С���ɳ̲ɹ������
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad3",
                "east"    : __DIR__"xkroad5",
                "west"    : __DIR__"haigang",
                "south"   : __DIR__"haibin",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("resource/quarry", ([
                "/clone/quarry/gui" :  50,
                "/clone/quarry/eyu" :  10,
                "/clone/quarry/haibei" :  10,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}