inherit ROOM;

void create()
{
        set("short", "�η�");
        set("long", @LONG
�������η������涼��������Χס��������һ��С�������ţ������
����һ�ȴ�������͸����΢���Ĺ��ߴӴ������˽����������η�����һ��
��������������һЩ���񼫵ķ��ˡ�
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xunbu",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -7020);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}