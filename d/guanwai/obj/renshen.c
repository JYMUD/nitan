// renshen.c

inherit ITEM;

void create()
{
        set_name("�˲�", ({"renshen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ó������ε���ɽ�Ρ�\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        addn("max_neili", 3, me);
        if( query("max_neili", me)>me->query_neili_limit() )
                set("max_neili", me->query_neili_limit(), me);

        message_vision("$N����һ����ɽ�Σ���ʱ�����ȫ������˻�����\n", me);
        destruct(this_object());
        return 1;
}