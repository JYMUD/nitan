inherit ROOM;

void create()
{
        set("short", "���������");
        set("long", @LONG
������Ǿ�����Ϊ��������������֡�������������æ�Ľֵ��ϣ�
�ֵ��ϳ�ˮ�������������������ַǷ����ϱ߽Ӿ��ǵĽ�ͨҪ������
���֣����߲�Զ���Ƿ����ĵذ��Ŷ���ֹ㳡�������Ǿ��������ġ�
ȫ�۵¡���Ѽ�ꡣ������һ��ϷԺ���Ǿ��ǰ�����Ϣ�����ֵĳ�����
LONG );
       set("exits", ([
                "north" : "/d/beijing/quanjude",
                "south" : "/d/beijing/wang_8",
                "west" : "/d/beijing/wang_9",
                "east" : "/d/beijing/xiyuan",
        ]));

        set("objects", ([
                "/d/beijing/npc/youren" : 1,
        ]));

	set("coor/x", -2770);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
       set("outdoors", "beijing");
        replace_program(ROOM);
}