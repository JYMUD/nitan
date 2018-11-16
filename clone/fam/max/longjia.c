// longjia.c �������׵�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "�������׵�" NOR, ({ "longjia dan", "longjia", "dan" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "��ҩ�е���Ʒ�����ú󲻵�����ҽ���κ����ˣ�����\n"
                                "��ƽ��һ���������ϵĹ����������ഫ˵�˵�ɢ����\n"
                                "�������������Χ��ʮ��Բ������Ʒ��һ�γ�Ч����ѣ�\n" NOR);
                set("value", 100000);
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

        log_file("static/using", sprintf("%s(%s) eat �������׵� at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        effect = 0;

        if( query("skybook/item/longjia", me) )
        {
                /*
                message_vision(HIR "$N" HIR "һ������������һ���������׵���ȴ��$P"
                               HIR "һ�����������һ����Ѫ��\n" NOR, me);
                
                me->set_temp("die_reason","̰���������׵������Ū��ȫ���������"
                                           "����");
                me->die();
                */ 
                me->improve_neili(500);
                addn("skybook/item/longjia", 1, me);
                message_vision(HIW "$N" HIW "һ������������һ���������׵���ֻ��$P"
                               HIW "����һ�������϶�ð����������\n" NOR, me);
        } else
        {
                message_vision(HIW "$N" HIW "һ������������һ���������׵���ֻ��$P"
                               HIW "����һ�������϶�ð����������\n" NOR, me);

                //addn("combat_exp", 1000000+random(500000), me);
                addn("potential", 10000, me);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("parry");
                if (me->can_improve_skill("parry"))
                        me->improve_skill("parry", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                mapsk = me->query_skill_mapped("dodge");
                if (me->can_improve_skill("dodge"))
                        me->improve_skill("dodge", 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                me->improve_neili(500);
                set("skybook/item/longjia", 1, me);
        }
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
