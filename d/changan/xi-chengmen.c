//Room: xi-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "����������");
        set("long", @LONG
�����ǵ������š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ
�򵱹أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�
���ƺ����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ���������
�ţ�ʿ�����
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "west" : "/d/changan/road7",
                "east" : "/d/changan/xian-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
                "/d/changan/npc/wujiang" : 1,
                "/d/changan/npc/guanbing" :2,
               "/clone/npc/walker"  : 1, 
        ]));

        set("outdoors", "changan");
        set("coor/x", -10770);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}