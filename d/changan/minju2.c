//Room: minju2.c

inherit ROOM;

void create ()
{
        set ("short", "���");
        set("long", @LONG
���������ǿ�������������ض���Ȼ�������һ����ɫ��ɫ��
������ױ̨��ǰ��������ź�ľԲ�Ρ��Ҳ�ǽ���Ϲ���һ����Ů����
ͼ���������м��бʼ����������С�֣��ڲ�����һ�ź�ɫ��ᣴ���
�ĵͰ�ľ齡�
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui2",
        ]));

        set("coor/x", -10740);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}