inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������Ϊ׷�������ˮ���£��ڴ�̨�Ͻ��죬���ڵĴ��������
��ƽ����һ�����Ű����£�ĿעԶ�������˶�������Ī����ˮ�ģ���
�¹�ȥ����Ƭ���֡�
LONG );
        set("objects", ([
                  __DIR__"npc/obj/dayu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "westdown" : __DIR__"yuwang",
        ]));

	set("coor/x", -5010);
	set("coor/y", 2100);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}