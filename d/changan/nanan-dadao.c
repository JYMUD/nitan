//Room: nanan-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "�ϰ����");
        set("long", @LONG
�����ǵ������ϰ������Ϊ���֣����˱��ǵľ����⣬���в���
�������ÿͺ����ˡ��ϰ���������Ͼ��ǳ����ǵ��ϳ��ţ������ǹ�
�ʹ��������֡�
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/nanan-daokou",
                "north" : "/d/changan/qinglong2",
                "east"  : __DIR__"gongbu",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}