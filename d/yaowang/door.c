#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һ��ׯ���ߴ�ʯ�ţ����ڲ�ͬ���������Ը�����һ��
��ʯ��̵��Ի������ϻ��в��ٵ�С�ף�Ҳ��֪������ʲô�õģ�
�ŵ����Ϸ���ǽ��Ƕ��һ��ʯ�壬ʯ���Ͽ��š�ҩ���ȡ�������
���Ĵ��֣�ԭ�����������������ʿ��ɫ��ҩ���ȡ����ŵ��ұ�
����һ��ʯ��(bei)��
LONG
        );
        set("exits", ([
        "north" : __DIR__"bridge1",
        "east" : __DIR__"lcd07",
        "west" : __DIR__"tiandi1",
        "south" : __DIR__"tiandi2",
]));
        set("item_desc", ([
                "bei" :  HIW"\n     ��������\n"+
                   HIW"     �� "HIB"ҩ"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     �� "HIB"��"HIW" ��\n"+
                   HIW"     ��    ��\n"+
                   HIW"     �� "HIR"ɱ"HIW" ��\n"+
                   HIW"     �� "HIR"��"HIW" ��\n"+
                   HIW"     �� "HIR"��"HIW" ��\n"+
                   HIW"     ��������\n"NOR,
        ]));
        set("outdoors", "yaowang");

        setup();
        replace_program(ROOM);
}
int valid_leave(object me, string dir)
{
        if( dir=="north" 
         && query("party/party_name", me) != "ҩ����" )
                return notify_fail(WHT"�뿴ʯ����\n"NOR);
        return ::valid_leave(me, dir);
}