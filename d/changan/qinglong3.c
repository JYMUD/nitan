//Room: qinglong3.c

inherit ROOM;
void create ()
{
        set ("short", "������");
        set("long", @LONG
�������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء�������ǳ���������
�������ˡ���Ϊ���������������������ΰ��ܺã�����ϵ�����
Ҳ������Ϊ��ȫ���ġ�
LONG );
        set("exits", 
        ([ //sizeof() == 3
                "south" : "/d/changan/yamen",
                "west" : "/d/changan/qinglong2",
                "east" : "/d/changan/fengxu5",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}