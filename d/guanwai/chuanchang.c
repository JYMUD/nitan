#include <ansi.h>
inherit RIVER;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǹ��򴬳���������λ�ڹ����ƽԭ�в���һ������
��С�򣬴��������ϡ������������Ը�ǽ�������ڼ��ء�����
���ɻ���������գ��˱��ұ�����Ҫ�ء��ɻ��� (river)�ڶ�
��ʱ�����ͨ�У����ﻯ����ֻ���Ҵ��Ұ�æ�ˡ�
LONG);
        //set("arrive_room", "/d/guanwai/damenkan");
        set("to", "/d/guanwai/damenkan");
        set("need_dodge", 200);       
        set("exits", ([
                "south" : __DIR__"xuedi3",
        ]));
        set("objects", ([
                __DIR__"npc/chuanfu" : 1,
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "guanwai");
        set("coor/x", 4030);
	set("coor/y", 9260);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
