//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
�����人����Ľֵ����Ӵ��ϱ����ĸ�ɫ�˵ȣ�����������Ħ
����ࡣ������һ��Ǯׯ�������������������Ľ���������������һ
����¥���Ŷ�������һ�����ң����ļ��������ֲ������������������
�����ζ���������������������
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"sijimei",
                "west" : __DIR__"qianzhuang",
                "south": __DIR__"hzjie2",
                "north": __DIR__"beimen",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}