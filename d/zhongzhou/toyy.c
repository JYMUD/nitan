inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
���������ݽ�Զ��·�ϼ������������ˣ������ﲻ��Ҳ��
���������������ͨ�����ݸ������߲�Զ���Ǿ����ص������ǡ�
LONG);
        set("exits", ([
                "southwest" : "/d/xiangyang/eastgate2",
                  "north" : __DIR__"nroad",
        ]));

        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);
        set("coor/x", -150);
        set("coor/y", -130);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}