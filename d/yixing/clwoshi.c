// /d/yixing/clwoshi.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ڳ��������ݻ�������Ĵ����������������������������ӣ���
�̽��档��ǰ���ʵʹ�����Լ���������ƺ����ˡ���ǰ����¯��������
������ֻ��������һ�������磬����������ɶ�����
LONG );
        set("exits", ([
                "south" : __DIR__"clxiaoting",
        ]));
        set("objects",([
                __DIR__"npc/cl_shijian" : 1,
        ]));
        set("coor/x", 279);
	set("coor/y", -971);
	set("coor/z", -1);
	setup();

        replace_program(ROOM);
}