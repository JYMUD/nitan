inherit ROOM;

void create()
{
        set("short", "ʯ����");
        set("long", @LONG
��������ݸ���Զ��·�������������ϣ����üͷҲ��չ
�˿���������ҲԽ��Խ�󡣱���������ݸ����ϳ����ˡ�
LONG);
        set("exits", ([
                  "south" : __DIR__"toyy",
                  "north" : __DIR__"nanmeng",
        ]));

        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -150);
        set("coor/y", -120);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}