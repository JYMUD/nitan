#include <ansi.h> 
inherit ROOM;

int do_lianzhi(string arg);

void create()
{
        set("short", "������");
        set("long", @LONG
�������嶾�̵���ר�ŵ������ң��������������Ƹ��ֶ�
ҩ�����ϰ��Ÿ�ʽ���������ߡ��������з���һ��һ�˶�ߵ�
��¯��¯���������и����ݵĵ������ֳ���ľ����¯���ߣ���
���������ﲻ֪����Щʲô��
LONG);
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"nanyuan",
        ]));
        set("objects", ([
                __DIR__"npc/daoren": 1,
        ]));
        setup();
}

void init()
{
        add_action("do_lianzhi", "lianzhi");
}

int do_lianzhi (string arg)
{
        object ob, me = this_player();
        int time = 15 + random(15);

        if( query("family/family_name", me) != "�嶾��" )
                return notify_fail("�㲻֪����������֡�\n");

        if( query_temp("liandu/wudu", me) )
                return notify_fail("�������������أ�������ġ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (me->query_skill("wudu-qishu", 1) < 60 )
                return notify_fail("����嶾����������죬�޷�������\n");

        if( query("jing", me)<80 || query("qi", me)<80 )
                return notify_fail("�����ڵľ���״�����ѣ��޷�������\n");

        if (arg != "heding hong" && arg != "furou gao" &&
            arg != "kongque dan" && arg != "chixie fen" &&
            arg != "wusheng san" && arg != "duanchang san")
                return notify_fail("��Ҫ����ʲô��ҩ��\n");

        if (arg == "heding hong")
        {
                if (! present("du nang", me)
                   || ! present("shexin zi", me)
                   || ! present("qianri zui", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("shexin zi", me));
                destruct(present("qianri zui", me));
                set_temp("liandu/wudu", "hedinghong", me);
        } else

        if (arg == "furou gao")
        {
                if (! present("du nang", me)
                   || ! present("fugu cao", me)
                   || ! present("chuanxin lian", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("fugu cao", me));
                destruct(present("chuanxin lian", me));
                set_temp("liandu/wudu", "furougao", me);
        } else

        if (arg == "kongque dan")
        {
                if (! present("du nang", me)
                   || ! present("fugu cao", me)
                   || ! present("qianri zui", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("fugu cao", me));
                destruct(present("qianri zui", me));
                set_temp("liandu/wudu", "kongquedan", me);
        } else

        if (arg == "chixie fen")
        {
                if (! present("du nang", me)
                   || ! present("shexin zi", me)
                   || ! present("duanchang cao", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("shexin zi", me));
                destruct(present("duanchang cao", me));
                set_temp("liandu/wudu", "chixiefen", me);
        } else

        if (arg == "duanchang san")
        {
                if (! present("du nang", me)
                   || ! present("duanchang cao", me)
                   || ! present("chuanxin lian", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("duanchang cao", me));
                destruct(present("chuanxin lian", me));
                set_temp("liandu/wudu", "duanchangsan", me);
        } else

        if (arg == "wusheng san")
        {
                if (! present("du nang", me)
                   || ! present("heding hong", me)
                   || ! present("duanchang san", me)
                   || ! present("furou gao", me)
                   || ! present("chixie fen", me)
                   || ! present("kongque dan", me)
                   || ! present("jinshe duye", me))
                        return notify_fail("�����ϵ�ԭ�ϲ��룬�޷�������\n");

                destruct(present("du nang", me));
                destruct(present("heding hong", me));
                destruct(present("duanchang san", me));
                destruct(present("furou gao", me));
                destruct(present("chixie fen", me));
                destruct(present("kongque dan", me));
                destruct(present("jinshe duye", me));
                set_temp("liandu/wudu", "wushengsan", me);
        }

        message_vision (HIR "\n$N" HIR "�����ϵ�ҩƷͶ�뵤¯�������ط�С��"
                        "����������\n\n" NOR, me);
        me->start_call_out((: call_other, __FILE__, "liandu", me :), time);
        me->start_busy(time / 2 + 1);
        return 1;
}

void liandu(object me)
{
        object ob;
        int skill, lvl;
        int exp, pot, sco;

        exp = 300 + random(300);
        pot = 100 + random(200);
        sco = 100 + random(100);

        skill = (int)me->query_skill("wudu-qishu", 1);

        lvl = (int)me->query_skill("poison", 1) / 2 +
              (int)me->query_skill("wudu-qishu", 1) + 10;

        if (environment(me) != this_object())
                return;

        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));

        if (random(skill) < 50 && random(3) == 1) 
        {
                delete_temp("liandu/wudu", me);
                message_vision(HIR "\nͻȻ��һ���ȶ�Ľ�����$N" HIR "���Դ�"
                               "��������������ʧ���ˡ�\n"NOR,me);
        } else
        {
                message_vision(HIW "\n¯��������ת����������̱ǵ���ζ��$N"
                               HIW "��æС������ؽ�ҩ��ȡ����\n" NOR, me);

                if( query_temp("liandu/wudu", me) == "hedinghong" )
                {
                        ob = new("/clone/poison/hedinghong");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "�׶���綾",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "�������ˡ�" + NOR + ob->name()
                                        + NOR + HIY "����\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "furougao" )
                {
                        ob = new("/clone/poison/furougao");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "�����綾",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "�������ˡ�" + NOR + ob->name()
                                        + NOR + HIY "����\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "kongquedan" )
                {
                        ob = new("/clone/poison/kongquedan");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "��ȸ���綾",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "�������ˡ�" + NOR + ob->name()
                                        + NOR + HIY "����\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "chixiefen" )
                {
                        ob = new("/clone/poison/chixiefen");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "��Ы�۾綾",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "�������ˡ�" + NOR + ob->name()
                                        + NOR + HIY "����\n" NOR);
                } else

                if( query_temp("liandu/wudu", me) == "duanchangsan" )
                {
                        ob = new("/clone/poison/duanchangsan");
                        ob->set("poison",([
                                "level" : lvl,
                                "id":query("id", me),
                                "name"  : "�ϳ�ɢ�綾",
                                "duration" : 15,
                        ]));
                        tell_object(me, HIY "�������ˡ�" + NOR + ob->name()
                                        + NOR + HIY "����\n" NOR);
                } else
                if( query_temp("liandu/wudu", me) == "wushengsan" )
                {
                        ob = new("/clone/poison/wushengsan");
                        ob->set("poison",([
                                "level" : lvl + 20,
                                "id":query("id", me),
                                "name"  : "��ʥɢ�綾",
                                "duration" : 25,
                        ]));
                        tell_object(me, HIY "���������嶾�̶�����ҩ��" + NOR
                                        + ob->name() + NOR + HIY "����\n" NOR);

                        if( query("potential", me)>
                           me->query_potential_limit()) 
                                pot = 1;

                        addn("combat_exp", exp, me);
                        addn("score", sco, me);
                        me->improve_potential(pot);

                        tell_object(me, HIC "������" + chinese_number(exp)
                                        + "�㾭�顢" + chinese_number(pot) +
                                        "��Ǳ���Լ�" + chinese_number(sco) +
                                        "�㽭��������\n" NOR); 
                }

                ob->move(me);
                delete_temp("liandu/wudu", me);

                me->improve_skill("poison",50+query("int", me));
                if (me->can_improve_skill("wudu-qishu"))
                        me->improve_skill("wudu-qishu",50+query("int", me));

                tell_object(me, HIC "������������ġ������������͡��嶾������"
                                "����ˣ�\n\n" NOR);
        }
}