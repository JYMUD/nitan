#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ͱ�");
        set("long", @LONG
�Թ����ƣ�����ѣ����������죬�غ����޹ִ�ʫ��������д��
·�����������ν�����ޱȣ�һ�������ϵĽ�ˮ��һ�����絶�а��
�ͱڡ���������һ����Σ�յ��ͱ��ϣ��㻹�ǿ��߰ɣ���һ��С�ĵ�
����ȥ��
LONG );
        set("exits", ([
                  "eastdown" : __DIR__"shudao7",
                  "westup" : __DIR__"shudao9",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15060);
	set("coor/y", -1830);
	set("coor/z", -50);
	setup();
        replace_program(ROOM);
}