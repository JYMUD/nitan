#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
   ������ѩɽ�µĶ�����������̬�����ʮ���޺����񣬽��
���⣬����ׯ�ϡ�
LONG );
        set("exits", ([
                "northup" : __DIR__"zoulang1",
                "west"    : __DIR__"dadian",
        ]));
        set("objects", ([
                CLASS_D("xueshan")+"/jiamu" : 1,
                __DIR__"npc/xiang-ke"       : 3,
        ]));
        setup();

}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((! myfam || myfam["family_name"] != "ѩɽ��")
           && dir=="northup"
           && objectp(present ("jiamu huofo", environment(me))))
          return notify_fail(CYN "��ľ���˵��������ѩɽ�µ�"
                                   "�ӣ��������ڡ�\n" NOR);

        return ::valid_leave(me, dir);
}