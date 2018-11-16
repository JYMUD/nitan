// Room: /d/xiangyang/westgate2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "�׻�����");
        set("long", @LONG
�����������ǵ������ţ�ֻ�������Ϸ����š��׻��š��������֡�
���Ÿ����ɣ���Լ�������࣬�����ĳ�����������ȭͷ���С����
�����Ŷ���Լ���ɣ���Լÿ������ʱ���ͻ��ٱ����ء��������ɹ���
���ַ������ǣ�����������൱���ܣ�����һЩ�ٱ��������̲�Ҫ��
�����ǵ��ˡ�
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east"  : __DIR__"westgate1",
                "west"  : "/d/city2/yidao1",
        ]));
        set("objects", ([
                __DIR__"npc/pi"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7870);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

int valid_leave(object me,string dir)
{
       if( dir == "west" && !userp(me) 
            && !query_temp("warquest", me) )
                return notify_fail("��Ӫ�صأ������˵ȣ��������ڣ�\n");

       return ::valid_leave(me,dir);
}