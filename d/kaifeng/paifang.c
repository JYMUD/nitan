inherit ROOM;

void create()
{
        set("short", "�Ʒ�");
        set("long", @LONG
����һ���ձڣ�����һ����ʯС������ǰ��Զ����һ���Ʒ���ͨ
�ú������һ�ߣ�������ԭ���ĵ�ɫ�����Ǹ��ص�ү����ɫ���񣬱�
���ֺ�������Ϸ¥��������ǹص���
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                  "north" : __DIR__"xilou",
                  "east" : __DIR__"guandi",
                  "west" : __DIR__"huiguan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/huizhang" : 1,
                  __DIR__"npc/pihuoshang" : 1,
        ]));

	set("coor/x", -5010);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}