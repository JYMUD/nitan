//Room: qunyulou1.c

inherit ROOM;

void create()
{
        set("short", "Ⱥ��¥����");
        set("long", @LONG
Ⱥ��¥���������涼����ɴ���������ݺύ���ֳɴ�С��ʽ��
���ƣ�ÿһ����һ��С������Ƕ�ţ��Ե���Ϊ���£������ڵƹ���
ӳ���ԣ���ͷ��������÷������Ӱ��б��Ҳ���ڲ������ϡ���Ŀ�ĳ�
������������͸�룬΢��������������㣬������Ƣ��
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : "/d/changan/qunyulou",
                "up"   : "/d/changan/qunyulou2",
        ]));
        set("objects", ([
                "/d/changan/npc/lingfeixue" : 1,
        ]) );

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}