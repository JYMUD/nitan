// Room: /d/huangshan/mengbi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "�α�����");
        set("long", @LONG
ԶԶ���ɺ���������һ�����ص�ʯ�����²�ֱ��ʸˣ��϶˿��Ʊ�
�⣬�ʸ˺ͱʼ�֮���һʯ�죬���Ե���һֻ��Ȼë�ʣ��ʼ�֮�ϸ���
һ����ɣ��������ۣ�������Ȼ�������ʯ������֮�����ഫ����̫��
���ڴ���ʫ�����ǹ�ʯҲ������̫����ʱ��������֮��ͷ����������
���հ�ݣ��������¡������������α���������
LONG
        );
        set("exits", ([ 
                "west" : __DIR__"sanhua",
        ]));
        set("objects", ([
                __DIR__"obj/meng" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -575);
        set("coor/y", -1010);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}