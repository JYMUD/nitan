#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(WHT "����" NOR, ({"hu gu", "hu", "gu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", WHT "\nһ�����ʵĻ��ǣ������ް׻���������ȡ����������ҩ��\n" NOR);
                set("value", 6000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        message_vision(HIR "$N" HIR "�����ǽ������£�ֻ��һ������ֱ�嶥�š�\n" NOR, me);
        set("jingli",query("max_jingli",  me), me);
        set("neili",query("max_neili",  me), me);
        set("jing",query("max_jing",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        me->improve_skill("force", 200000000);

        me->start_busy(6);
        destruct(this_object());
        return 1;
}