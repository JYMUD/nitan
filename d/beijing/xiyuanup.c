#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ϷԺ��̨");
        set("long", @LONG
�����ǳ���ϷԺ�ĺ�̨����̨����ȴ��ɨ�úܸɾ�������Ϸ��
���ں�̨��ױ�����������ˣ����ú���ֵ��������㡣
LONG );
        set("exits", ([
                "south" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 2,
                __DIR__"npc/xizi2" : 1,
                __DIR__"npc/xizi3" : 1,
        ]));

	set("coor/x", -2760);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        int i;
        
        if (dir == "south")
        {
                message_vision(
                        "\n$Nһ�����գ�һҾ��������ƽ�ɣ���̨��Ծ����˫��أ��\n"+
                        "��ȭ�����������̬������������Ȳɡ�\n", me);
                        
                i=query("meili", me);
                if (i < 20) 
                {
                        i = i + 10;
                        set("meili", i, me);
                        message_vision(HIC "\n$N������ֵ����ˡ�\n" NOR, me);
                }
        }
        return ::valid_leave(me, dir);
}