//Room: zubaohang.c

inherit ROOM;

void create ()
{
        set ("short", "�鱦��");
        set("long", @LONG
�鱦������ⱦ�����䣬ѣ������Щ�������۾������µĳ�����
�����Ÿ��������鱦�������������м������ſ�����ѡ�����鱦��һ
����ľ���ϰ��ſ����߶�ߵ����������֮����͸�ŵ�����������
�ۺ���֮����
LONG );
        set("exits", ([
                "south" : "/d/changan/yongtai-beikou",
        ]));
        set("objects", ([
                "/d/changan/npc/jinfuhuan"  : 1,
        ]));

        set("coor/x", -10760);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}