//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
�����人����Ľֵ����Ӵ��ϱ����ĸ�ɫ�˵ȣ�����������Ħ
����ࡣ������һ���ӻ��꣬������һ����Ժ��
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"guiyuansi",
                "west" : __DIR__"zahuodian",
                "north": __DIR__"hzjie3",
                "south": __DIR__"nanmen",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}