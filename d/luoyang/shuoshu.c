inherit ROOM;

void create()
{
        set("short", "˵�����");
        set("long", @LONG
�������˵�������һλ��ʮ����������������ڴ���������������
��ҡͷ����˵����ͣ���������壬����������Ѧ�ٷ��ƣ������ƣ���Ӣ�ң�
���μǣ�ˮ䰴��ȵȣ���λ˵��������������ͨ����˵����Һ��ɡ���Χ
���������ǽ����ζ����ס�ĵ�ͷ�Ƶ���
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"chalou2",
        ]));
        set("objects", ([
                "/d/beijing/npc/chaboshi" : 1,
                "/d/beijing/npc/teahuoji" : 1,
                "/d/beijing/npc/chake" : 4,
        ]));
	set("coor/x", -7010);
	set("coor/y", 2160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}