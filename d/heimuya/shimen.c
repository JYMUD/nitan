// shimen.c

inherit ROOM;

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
�ߵ�һ����ʯ��ǰ��ֻ�����Կ������д��֣������ǡ��ĳ����
���������ǡ�����Ӣ����������Ͽ��š����¹������ĸ�����֡�
LONG );
        set("outdoors", "heimuya");
        set("objects", ([
            CLASS_D("riyue") + "/zhang2": 1,
        ]));
        set("exits", ([
            "eastdown" : __DIR__"shijie2",
            "westup"   : __DIR__"up1",
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}