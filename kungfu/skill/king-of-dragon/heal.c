// heal.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( me->is_busying() )
                return notify_fail("��������æ���أ����п��˹���\n");

        if ( !wizardp(me)) return 0 ;
        write( HIY "��ȫ����ɣ���������ʼ�˹����ˡ�\n" NOR);
        message("vision", HIY + me->name() + "�³�һ�ڽ�Ӳӵ�Ѫ����ɫ���ָ̻���������\n" NOR, environment(me), me);

        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("neili",query("max_neili",  me), me);
        set("jingli",query("max_jingli",  me), me);
        return 1;
}