//Room: nan-chengmen.c

inherit ROOM;

void create ()
{
        set ("short", "�����ϳ���");
        set("long", @LONG
�����ǵ��ϳ��š�����Ļ��ǺӼ������������ҳǸ�ǽ����һ
�򵱹أ����Ī��֮�ƣ����ڻ�פ������Ӫʿ����Զ����Ӫ���࣬�
���ƺ����ľ�����֮�ƣ�������¥��ֻ����¥�ߴ������ڱ���������
�ţ�ʿ������������ȥ��Զ���Ǳ���Ҫ���书��
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south" : "/d/changan/road5",
                "north" : "/d/changan/nanan-daokou",
        ]));
        set("objects", ([ //sizeof() == 3
                "/d/changan/npc/wujiang" : 1,
                "/d/changan/npc/guanbing": 2,
                "/clone/npc/walker"  : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}