inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ���������������������������ֹ�������ɫ��ʯ�ӣ���
�ϱ���ͷ���졣�����Ǹߴ�ľ��ݳ�ǽ���ϱߺ�����һ����Ȫ��
LONG );
        set("outdoors", "jingzhou");
        set("objects", ([
                  "/d/kaifeng/npc/qigai" : 1,
        ]));        
        set("exits", ([
                "north" : __DIR__"lydao1",
                "southdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7130);
	set("coor/y", -2060);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}