// Room: /d/mingjiao/shanmen.c
// Date: Java 97/04/3

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����ɽ��");
        set("long", @LONG
һ���޴����Ȼʯ�ź������Ƭɽ��֮�䣬ʯ�����Ϸ����̷���
�����������֣������̡����ּ���Щ���䣬����ȥ�����Զ����λ��
ʮ����Ĵ��ֳָֽ�����ɽ�����ࡣ
LONG );
        set("exits", ([
                "westup" : __DIR__"shanlu1",
                "east" : __DIR__"tomen1",
        ]));
        set("outdoors", "mingjiao");
        set("objects",([
                __DIR__"npc/menwei1" : 2,
                __DIR__"npc/jieyinshi":1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object *inv;
        int i;

        if (me->query_family() != "����" &&
            me->query_family() != "�䵱��"  &&
            dir == "westup")
        {
                inv = all_inventory(me);
                for(i=sizeof(inv)-1; i>=0; i--)
                        if(query("weapon_prop", inv[i]) && ((string)query("equipped", inv[i])=="wielded"))
                                if(objectp(present("da han", environment(me))))
                                        return notify_fail("����ס��˵������λ" +
                                                RANK_D->query_respect(me) + "����±��С��ҽ̹̽���"
                                                "������Ͳ�\n�óֱ�����ɽ������¡�\n");
        }
        return ::valid_leave(me, dir);
}
