inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","�ʹ�����");
        set("long", @LONG
������ǻʹ��ı��ţ��ɸߵ������ų����ţ����Ͻ�ɫ��í��
�������⡣��������վ�����������������������ͣ�Ĵ����Ź�����
���ˡ����õ�����ֱ����Ρ����ΰ�Ĺų�ǽ�ϣ�ʹ�ó�ǽ�Ϸ����Ͻ�
�ǡ�����˸������Եø����ҫ�ۡ������������������ǵ��������
�����ڻʹ����ŵ��������ࡣ�ӱ��������ذ��ſ��Ե��ﱱ���ı���
����[2��37��0m
LONG );
        set("exits", ([
                "south" : "/d/huanggong/jingshan",
                "north" : "/d/beijing/dianmen",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/bing3" : 1,
                "/d/beijing/npc/yuqian1" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2800);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        if (objectp(ob = present("guan bing", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "������ס������˵�����ʹ��صأ�����Ѱ�����ճ��롣\n\n");
        if (objectp(ob = present("shi wei", environment(me))) && dir == "south")
                return notify_fail(ob->name() + "������ס������˵�����ʹ��صأ�����Ѱ�����ճ��롣\n\n");
        return ::valid_leave(me, dir);
}