// Room: /d/yueyang/beimen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
�����������ǵı��š���ʯ��������¥̨����쳣��Ρ������Ĺ�
�γ����Ϸ������š�����������������֡�������һ������·��ֱͨ��
�ꡣ
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"beijie",
                "northwest" : "/d/jingzhou/tulu2",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
	set("coor/x", -6200);
	set("coor/y", -2990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}