inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���������Ŵ��ţ�������ľ���Ž����ر��š����ྲ�����رܡ�����
�ӷַ���ͷʯʨ�ӵ��Աߡ�ǰ����һ����ģ���Ȼ�ǹ�С����ԩ�õġ���
����������ǰѲ�ߡ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yamen",
                  "west" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/yayi" : 4,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}