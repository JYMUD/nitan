inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
��������������ͷ���Щ�����Ͽ�ʱ�����������ĺ��ӵģ������ֺ�
��С�����Һ����ȣ�û���κζ���������վ�Ų��ܰ��κ����ƣ������ӵ�
�������ܷ���С���ӿ�Ҫ�úóԳԿ�ͷ�ˡ�
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"sishu",
        ]));
        set("objects", ([
                "/d/wudu/npc/xuetong" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}