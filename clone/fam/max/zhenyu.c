// zhenyu.c ����������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "����������" NOR, ({ "zhenyu wan", "zhenyu", "wan" }) );
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�����۴�С��ҩ�裬���˱ǣ�һ��֮�±���Ŀ�\n"
                                "����������ҩ�������Ž�����Ĺ������ֳ��أ���\n"
                                "���Ļ�����ͣ������������һ�㡣\n"
                                "����Ʒ��һ�γ�Ч����ѣ�\n" NOR);
                set("value", 500000);
                set("no_sell", 1);
                set("unit", "��");
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/using", sprintf("%s(%s) eat ���������� at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

        if( query("skybook/item/zhenyu", me) )
        {
                /*
                message_vision(HIR "$N" HIR "һ������������һ�����������裬ȴ��$P"
                               HIR "һ�����������һ����Ѫ��\n" NOR, me);

                me->set_temp("die_reason","̰�����������裬���Ū��ȫ���������"
                                           "����");
                me->die();
                */ 
                me->improve_neili(800);
                me->improve_jingli(500);
                addn("skybook/item/zhenyu", 1, me);
                message_vision(HIW "$N" HIW "һ������������һ�����������裬ֻ��$P"
                               HIW "����һ�������϶�ð����������\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "һ������������һ�����������裬ֻ��$P"
                               HIW "����һ�������϶�ð����������\n" NOR, me);

                //addn("combat_exp", 2000000+random(1000000), me);
                addn("magic_points", 3000, me);
                addn("potential", 30000, me);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);

                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);
                       me->improve_skill("martial-cognize", 1500000);

                me->improve_neili(800);
                me->improve_jingli(500);
                addn("skybook/item/zhenyu", 1, me);
        }
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
