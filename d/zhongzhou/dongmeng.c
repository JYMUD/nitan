inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���������ݵĶ����š�������һ�����������ص����ݵ�
�˶�����������ݳǣ��ٸ���������ؿ����ʹ������ˡ�һ��
���Ʋ��ȵ�ʱ��������ر�Ľ��š�
LONG);
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/city/npc/wujiang" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"eroad1",
                  "west" : __DIR__"yanlingdong2",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -9000);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}