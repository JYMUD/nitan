//Room: minju5.c

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
                "north" : "/d/changan/huarui5",
        ]));

        set("coor/x", -10700);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}