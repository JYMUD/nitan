inherit ROOM;

void create()
{
        set("short", "С����");
        set("long", @LONG
��ǽ�Ǳ߿���һ��С�ţ������е�ɮ�˾ͽ����⡣��������ľ��
�ģ�ԭ�ȵĺ����Ѿ�����ò���ˡ�һ�ߵ�Χǽ̣�˰�ߣ�Ѱ����
�������������ϱ���Ƭ�˵أ����˽���������֡�
LONG );
        set("objects", ([
                  __DIR__"npc/zhangsan" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"caidi5",
                  "north" : __DIR__"eroad",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}