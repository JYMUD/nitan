inherit ROOM;

void create()
{
        set("short", "�ӻ���");
        set("long", @LONG
�����ǹŴ���ӻ��̣����ų����Ļ����ϰ������������
��Ҫ�Ķ������ϰ��Ǹ����ֵ������ˣ�����һ�߾�����к���
���ˣ��������Ҫʲô�Ļ����Կ���������ָ�� list����
LONG);
        set("exits", ([
                "north" : __DIR__"road2",
        ]));

        set("xinshoucun", 1);
        set("no_fight", 1);

        set("objects", ([
               __DIR__"npc/qianbo"  :  1,
        ]));
        setup();

        replace_program(ROOM);
}
