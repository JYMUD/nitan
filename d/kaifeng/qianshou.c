inherit ROOM;

void create()
{
        set("short", "ǧ��ǧ�۷��");
        set("long", @LONG
��������й������ǧ��ǧ�۹�������˵���������ն���������
����ǧ������ϸ��ȥ��ֻ��������������̶̵��ֱ�ÿ���������Ķ�
��ֻ�۾�����˼�Ǿ����㡺���۾��࣬ʲô���ܹ�ע�⵽�����ֶ࣬
ʲô���ܹܵ����ɱ������¡���
LONG );
        set("exits", ([
                  "west" : __DIR__"fangsheng",
                  "east" : __DIR__"houyuan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                  __DIR__"npc/oldwomen" : 1,
                  __DIR__"npc/obj/guanyin" : 1,
        ]));

	set("coor/x", -5050);
	set("coor/y", 2220);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}