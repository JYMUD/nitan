//Room: dong-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "����������");
        set("long", @LONG
�����ǵĶ����š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ
�򵱹أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�
���ƺ����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ���������
�ţ�ʿ�����
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "east" : "/d/changan/baqiao",
                "west" : "/d/changan/dongan-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
                "/d/changan/npc/wujiang" : 1,
                "/d/changan/npc/guanbing" :2,
               "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", 1);
        set("coor/x", -10670);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}