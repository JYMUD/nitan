inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ƿǳ����ɵĳ��ȡ������Ǽ���Ϣ�ҡ��ϱ���һ��СС��ҩ
�������洫��һ�������������������������ȹ����γ��š���������
������
LONG );
        set("exits", ([
                "west"  : __DIR__"ximen",
                "east"  : __DIR__"liangong",
                "north" : __DIR__"restroom",
                "south" : __DIR__"yaofang",
        ]));

        set("coor/x", -49980);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}