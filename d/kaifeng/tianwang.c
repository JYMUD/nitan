inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����������Ĵ��������շ������߾��ڷ�̳֮�ϣ������к�ɫ
դ�����м��ͨ��������ÿ���������ǰ����һ�����Ź�������Ů��
Ĥ�ݣ���������˳��
LONG );
        set("objects", ([
                  __DIR__"npc/hufa" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"qianyuan",
                  "north" : __DIR__"zhongyuan",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}