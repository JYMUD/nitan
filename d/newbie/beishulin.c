inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������ľ��Ǽ��˺ϱ��Ĵ�����������������·�ˣ����߸���
�谵�����ֶ������ּ�������ȥ��ʹ��������˲���������
LONG);
        set("exits", ([
                "south" : __DIR__"shulin",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 40 + random(20),
        ]));
        setup();

        replace_program(ROOM);
}