//Room: minju1.c

inherit ROOM;

void create ()
{
        set ("short", "���");
        set("long", @LONG
������һ�����ס������̨�Ϸ��Ŵ��С��С����ɹޣ�������
�Ż���֮��Ķ��������ȴ��Ӵ󿪣�Ʈ��һ�ɻ��ݵ�����ζ�������
ʮ�����֣�һ�Ŵ�ľ���ӣ���Χ���ż������ӣ������������һ��
��֪��̸ʲô��
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/huarui1",
        ]));

        set("coor/x", -10750);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}