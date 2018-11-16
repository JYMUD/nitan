#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǻش��õ����������ķ����ڷ��ż������Σ�ÿ�춼��ҩ����
��ҽʦ���������ã�Ϊ�˿������ˡ�
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"tingyuan",
        ]));

        set("objects", ([
                __DIR__"npc/yishi" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_zhiliao", "zhiliao"); //����
}

int do_zhiliao(string arg)
{
        object me, ob;
        int i, obj;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "ҩ����" )
        {               
                return notify_fail("�㲻��������������ˣ�\n");
        }

        if( !arg )
                return notify_fail("ָ���ʽ��zhiliao <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ�\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( me==ob )
                return notify_fail("�㲻��Ҫ��������Լ����ˣ�\n");

        obj=(query("max_qi", ob)-query("eff_qi", ob));

        if( !query_temp("heal", ob)){
        message_vision ("$N���Ƚ����"+MONEY_D->price_str(obj*10)+"���ƶﻯ��\n", ob);
                return 1;
        }

        if( i<5 ) i=5;
        if( i>40 ) i=40;
        if( query("jingli", me) <= i )
                return notify_fail("��̫���ˣ�����Ϣһ�°ɣ�\n");

        message_vision ("$NΪ$n���˰������ó�һ��������$nѨλ�����˼��¡�\n", me, ob);
        message_vision(WHT"$N�³�һ����Ѫ����ɫ�������ö��ˡ�\n"NOR, ob);

        delete_temp("heal", ob);
        set("eff_qi",query("max_qi",  ob), ob);
        set("qi",query("max_qi",  ob), ob);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)/2));
        addn("jingli", -i, me);
        me->start_busy(3);
        ob->start_busy(3);

        return 1;
}
