inherit ROOM;

void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
ɽ·���������˾�ͷ����ǰͻȻ����һƬ�Ѽ��Ŀ���������
����һƬ��ʯ������Сɽ�ڣ�ֻ����Щʯͷǧ�˰�̬��������
������⣬�������ֹ����������
LONG);
        set("exits", ([
                "north" : __DIR__"zhulin",
                "west" : __DIR__"houcun-shanlu",
                 "southeast" : __DIR__"luanfengang",
        ]));

        set("xinshoucun", 1);
            set("outdoors", "newbie");

           set("objects", ([
                "/clone/quarry/tu" : 40 + random(30),
           ]));
        setup();

        replace_program(ROOM);
}