inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
 ������ѩɽ�µĺ�Ҳ��ѩɽ���ӱ��������ĵط���������һ
Щ���������ź�ľ�ˣ�����һЩ�����ŵ�ɳ����ֱ����ľ׮��
LONG );

        set("exits", ([
                "north" : __DIR__"chanshi",
                "south" : __DIR__"neidian",
                "east" : __DIR__"tower",
        ]));

        setup();
        replace_program(ROOM);
}