#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
����ҩ����������ֲ��ҩ����أ�������ò�ҩ������������ֲ��ҩ(zhong)��
�Ȳ�ҩ�ֳ��˾Ϳ�����(dig)������
LONG );
        set("no_clean_up", 1);
        set("yaotian",1);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"door",

        ]));

        setup();
}

void init()
{
        add_action("do_dig", "dig");
        add_action("do_work", "get");
}

int do_dig(string arg)
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "ҩ����"
                || me->query_skill("medical",1) < 60 )
                return notify_fail("�㲻����ֲ��ҩ���������ڲ�ҩ��\n");

        if(me->is_fighting() && me->is_busy())
                return notify_fail("���æ��ûʱ�䡣\n");

        if( !arg || !ob = present(arg, environment(me)) )
                return notify_fail("ָ���ʽ��dig <��ҩID> \n");

        if( query("owner", ob) != query("id", me) )
                return notify_fail("���������������İ�����\n"); 

        message_vision("$N���Ὣ$n����������\n", me, ob);

        delete("no_get", ob);
        ob->move(me);
        delete("dig", ob);
        return 1;
}

int do_work(string arg) 

{
        return notify_fail("���ﲻ��ʹ�����ָ�\n");
}
