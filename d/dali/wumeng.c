//Room: /d/dali/wumeng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","���ɴ���");
        set("long", @LONG
������ɽ�Ļ��£������˰�ʯȥ�����������޳�һ������״��
ƽ̨����ӷֱ��ڸ���ƽ̨�ϣ��������ӣ�������ʯ��Χǽ������
��·Ҳ��ʯͷ�̳ɡ�
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "west"    : "/d/dali/wunong",
            "east"    : "/d/dali/caopo",
            "north"   : "/d/dali/wuyiminju1",
            "south"   : "/d/dali/wuyiminju2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19170);
	set("coor/y", -6780);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}