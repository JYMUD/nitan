//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
�����人����Ľֵ����Ӵ��ϱ����ĸ�ɫ�˵ȣ�����������Ħ
����ࡣ����һ����������ڷ������ջ�������̺죬����̾Ϊ��ֹ��
��������������̨��
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"qintai",
                "west" : __DIR__"juhuahui",
                "south": __DIR__"hzjie5",
                "north": __DIR__"zhongxin",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}