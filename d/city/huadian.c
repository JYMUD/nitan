// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�������½����ŵ�һ���ʻ��꣬���ڰٻ���ţ��������ҡ�������
�����֣�ȴҲ��使�����Ρ��������ڴ������ʺ���ĬĬ��ף������
�����˼���������ʻ���֪�Ǵ�һЩ���ܵĵط�������������ʮ��
���޶��ҹ������㡣��Ϊ�Ƿֵ꣬Ҳ�������ϰ塣һ������ֳֻ�����
�ڻ��������߶�������������ÿ���ʻ�����Ŀ��(sign)�͹���ǽ�ϡ�
LONG );
        set("region", "yangzhou");
        set("no_fight", "1");
        set("no_steal", "1");
        set("no_sleep_room", "1");
        set("item_desc", ([
                "sign" :
"��������������������������"+HIG"������֪"NOR+"������������������������������\n"
"�� һ�������ﻨ���ļ۸���(list)�鿴                           ��\n"
"�� �����򻨿�ֱ�����ƹ���(buy)��buy <����> <���ݴ���>       ��\n"
"�� �������ʻ����ṩ�ͻ����ͻ�����send <���ݴ���> to <���id>��\n"
"�� �ġ�����(help flower)����ѯ���京������ϡ�                ��\n"
"����������������������������������������������������������������\n"
        ]));
        set("objects", ([
                __DIR__"npc/huoji3" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"xiaohuayuan",
                "south" : __DIR__"dongdajie3",
        ]));
	set("coor/x", 30);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}