inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
������һ����ʯ����ϣ�������Լ�ɼ������ݳǵ��ϳ�ǽ��
�˴���������ȥ�����Կ���һ������
LONG);
        set("outdoors", "sanbuguan");
        set("exits", ([
                "south" : __DIR__"wdroad3",
                "north" : __DIR__"wdroad1",
                "west"  : "/d/hudie/shanbi",
                "southeast" : "/d/yixing/yixing",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
