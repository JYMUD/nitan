// brush.c
//
// This is the basic equip for players just login.

#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("ˢ��", ({ "brush", "shua zi" }) );
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "һ��ˢ�ӣ���ר������ˢЬ�õġ�\n");
                set("value", 200);
        }
        setup();
}

void init()
{
        add_action("do_swab", "swab");
        add_action("do_swab", "caxie");
}

int do_swab(string arg)
{
        int exp;
        object ob;      
        object me;
        object money;
        object shoeshine;

        me = this_player();
        if (! arg || ! objectp(ob = present(arg, environment(me))))
                return notify_fail("��ҪΪ˭��Ь��\n");

        if( !ob->is_character() || query("not_living", ob) )
                return notify_fail("������ˣ��ǲ��ǻ��ˣ�\n");

        if( !query("can_speak", ob) )
                return notify_fail("�Թ�����û����˵����" +
                                   ob->name() + "��Ь�ģ�\n");

        if (! living(ob))
                return notify_fail("�㻹�ǵȱ���������˵�ɣ�\n");

        if (ob == me)
        {
                message_vision("$N�������е�ˢ�ӣ������Լ�������"
                               "�Լ����Ǻ����࣬һʱ�̲�ס��Ҫ���ᣡ\n",
                               this_player());
                return 1;
        }

        if (! objectp(shoeshine = present("xie you", me)))
        {
                write("������û��Ь���ˡ�\n");
                return 1;
        }

        if (me->is_busy())
                return notify_fail("��������æ���أ����ǵ�һ�����˵�ɣ�\n");

        me->start_busy(2);

        if (playerp(ob))
        {
                shoeshine->cost();

                if( query("couple/couple_id", me) == query("id", ob) )
                {
                        message_vision("$N������һ�����ĵİ�$n��Ь����������"
                                       "�ġ�$n������$N��ͷ˵������" +
                                       (query("gender", me) == "����"?
                                        "�Ϲ������Ь���úú�Ŷ��" :
                                        "���ţ����Ь������Ư����") +
                                       "��\n", me, ob);
                        return 1;
                }

                message_vision("$Nһ�����ĵ���$n��Ь����������ֻ��$n"
                               "Ц���п���$P���������ã��ã���\n",
                               me, ob);
                if (ob->is_fighting(me))
                {
                        if( query("weiwang", me)>1000 )
                                addn("weiwang", -100, me);
                        else
                        {
                                message_vision("$NЦ������ĵ��л�ǳ������ô"
                                               "���Ҳ�ЬҲû���ã����У�\n",
                                               ob);
                                write("�����д��ֹ��\n");
                                return 1;
                        }
                        ob->remove_enemy(me);
                        ob->remove_killer(me);
                        me->remove_enemy(ob);
                        me->remove_killer(ob);
                        write(ob->name() + "ֹͣ�˶���Ĺ�����\n");
                        return 1;
                }
                write("�����а�����˥��һ��Ǯ��û�У�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("�㻹�ǵȴ�����ٲ�Ь�ɣ�\n");
                return 1;
        }

        if( time()-query_temp("last_swab", ob)<240 )
        {
                message_vision("$nһ���߿���$N��������������"
                               "�������ˣ��㻹�Ǹ��������ɣ�\n",
                               me, ob);
                return 1;
        }

        message_vision("$N�������������ڵİ�$n��Ь����һ����һ�顣\n",
                       me, ob);
        shoeshine->cost();
        if( query("weiwang", me)>10 )
                addn("weiwang", -10, me);
        else
                set("weiwang", 0, me);

        set_temp("last_swab", time(), ob);

        exp = 120 + random(50);
        if( query("combat_exp", me)<500000 )
                GIFT_D->delay_work_bonus(me, ([ "exp" : exp, "pot" : exp / 3 ]));

        else
                addn("potential", exp/3, me);

        money = new("/clone/money/coin");
        money->set_amount(30 + random(30));

        message_vision("$n����Ь���ߺߵ����ã��������Ǯ���͸���ģ�\n"
                       "$N��æ��ͷ������Ц���еĽ��˹�����\n", me, ob);
        money->move(me, 1);
        if (! query("zhufu_mod/boots", me) && random(10) == 1) 
        {
                message_vision("$n��$N�ٺ�һЦ�������ɵò������е�" 
                               "��˼�������֮ף��ս�¾��������͸��������ɡ�\n",
                               me, ob);
                money = new("/clone/goods/zhufu_boots"); 
                money->move(me, 1);
                tell_object(me, HIM "\n������һ��" + money->name() + HIM "��\n" NOR);
                set("zhufu_mod/boots", 1, me); 
        }
        return 1;
}
