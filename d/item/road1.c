// road1.c С��

inherit ROOM;

void create()
{
        object ob;

        set("short", "С��");
        set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·���Ϲ⻬ƽʵ��������
����������������������ԼԼ���Կ�����ʯ�̾͵Ĺٵ���
LONG );

        set("exits", ([
                "west"   : "/d/suzhou/qsgdao1",
                "eastup" : __DIR__"road2",
        ]));

        set("objects", ([
                "/adm/npc/zhang" : 1,
        ]));

        set("outdoors", "suzhou");
        set("coor/x", 860);
        set("coor/y", -1070);
        set("coor/z", 0);
        set("coor/x", 860);
        set("coor/y", -1070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}