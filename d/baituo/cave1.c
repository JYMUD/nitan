inherit ROOM;

void create()
{
        set("short", "�Ҷ���");
        set("long", @LONG
�������Ҷ��ڲ��������������Ž�׵�����ʯ��
LONG );
        set("exits",([
                "out" : __DIR__"cave",
        ]));
        set("objects",([
                "/clone/beast/yanjingshe" : random(2),
                "/clone/beast/wangshe" : random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}