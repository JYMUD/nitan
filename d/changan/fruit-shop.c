//Room: fruit-shop.c

inherit ROOM;

void create ()
{
        set ("short", "ˮ����");
        set("long", @LONG
������Ψһ��һ��ˮ���ꡣ�����������һ���ŵ���𣬿�����
��ʽ������ˮ���������ˮ��Ϊ�˱������ʣ�����ÿ��ӳ���Ĺ�԰
�ÿ쳵�����ġ�ˮ����Ů�ϰ���������������к��ſ��ˡ�
LONG );
        set("exits", ([
                "north"   : "/d/changan/qixiang2",
        ]));
        set("objects", ([
                "/d/changan/npc/lanxiang"   : 1,
        ]));

        set("coor/x", -10740);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}