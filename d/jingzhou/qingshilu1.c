inherit ROOM;

void create()
{
        set("short", "��ʯ·" );
        set("long", @LONG
һ����ʯ�̳ɵ�·��ƽ̹������·�����档����������������
���˶�������ȥ�˳�����ЪЪ�ţ�һЩС��Ҳ�˻����������Ժȵ�
������
LONG );
        set("exits", ([
                "east" : __DIR__"nanshilu",
                "west" : __DIR__"qingshilu2",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}