inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
һ�ɳ�ζ�˱Ƕ�����һ�ѽ�ͷ��ӬΧ�Ÿ�С���Ӳ��ϴ�ת������
������ɮ����������˵ص�С����ӣ���Ȼ�ǱȽϲ������㻹�ǸϿ�
�߿�Щ�ɣ���С�Ļ����ȥ�ġ�
LONG );
        set("objects", ([
                  __DIR__"npc/popi" : 1,
                  __DIR__"npc/wulai" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"maofang",
                  "north" : __DIR__"kongdi",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -4980);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}