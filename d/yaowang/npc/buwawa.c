#include <ansi.h>
inherit NPC;


void create()
{
        set_name("������", ({ "buwawa", "bu", "wawa" }) );
        set("gender", "����" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");

        setup();
}

void init()
{
        add_action("do_lianxi", "lianxi");
}

int do_lianxi(string arg)
{
        object me;
        int i;
        me=this_player();
        i=(int)me->query_skill("zhenjiu-shu",1);

        if( query("family/family_name", me) != "ҩ����" || me->query_skill("zhenjiu-shu",1) >= 100 )
        {       
                return notify_fail("�㲻��ʹ�ò����ޣ�\n");
        }

        if (!id(arg))
                return notify_fail("ָ���ʽ��lianxi <ID> \n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( query("jing", me) <= i )
                return notify_fail("��̫���ˣ���Ϣһ����ɣ�\n");

        message_vision ("$N����һ֧���룬�ڲ������������ž���ͼ���Ȼ��ţ�\n", me);
        me->improve_skill("zhenjiu-shu", (i/3));
        addn("jing", -i, me);
        me->start_busy(1);

        return 1;
}
