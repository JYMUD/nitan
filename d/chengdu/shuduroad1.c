// Room: shuduroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "�񶼴��");
        set("long", @LONG
�������񶼴���������Ϳ��Ե��ᶽ���ˡ������ĳ����������
��������ȥ�Ĺٲ�����ɣ���һЩ�ٱ���·��Ѳ�ڡ���е�һ���
���£����ڹս���������
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"  : __DIR__"eastroad2",
            "west"  : __DIR__"guangchang",
            "south" : __DIR__"fomiao",
        ]));
        set("objects", ([
            "/d/city/npc/bing" : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}