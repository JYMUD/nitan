inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������ǿ���ı����ţ��������������ǻʳ����ڡ���ǽ������
�����ι̡����ߵĲر���������ǧ�ˣ��������ǵ����˹��Ƴ���֮ʱ��
�ɷ���ɱ������ɱ���ˡ�
LONG );
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kaifeng");
        set("exits", ([
                  "south" : __DIR__"road6",
                  "north" : __DIR__"jiaowai",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}