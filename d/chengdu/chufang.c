// Room: chufang.c

inherit ROOM;
void create()
{
        set("short", "��¥����");
        set("long", @LONG
�����Ǿ�¥����ĳ�����������ˮ��ǰ���в��ٵĻ����ժ�˺�
��ϴ���������һЩ���վ������ֱð���͹���ǰŬ���ķ����Ÿ�ɫ
���ȣ���һ�����ִ�ŵ�����������ߺ�ȣ�ָ�ֻ��ŵ�ȴ���ɻ
LONG );
        set("exits", ([
                "west" : __DIR__"jiudian",
        ]));
        set("objects", ([
                __DIR__"npc/chuniang" : 1,
        ]) );
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("coor/x", -15180);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}