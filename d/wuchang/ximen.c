inherit ROOM;

void create ()
{
        set ("short","����");
        set ("long", @LONG
�������人�������ˡ��кܶ����ú�������ʿ�����������м�����
�������������������ˡ��Ա�վ��һ�����٣�����������ʮ�㣬��ͣ
��ָ�ֻ��š�
LONG);

        set("exits", ([
                "east":__DIR__"hzjie4",
                "west":"/d/jingzhou/guandao1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
                "/d/city/npc/wujiang" :1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5110);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}