// surrender.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        
        if( !me->is_fighting() )
                return notify_fail("Ͷ��������û�����ڴ��㰡....��\n");

        ob=query_temp("last_opponent", me);
        if( objectp(ob) && living(ob) && ob->is_killing(me) ) {
                message_vision("$N��$n���ģ�����$N����˵����"
                        + RANK_D->query_rude(me) + "�ϻ���˵����������\n", ob, me);
                return 1;
        }

        me->remove_all_enemy();
        if( query("score", me) >= 50 )
                addn("score", -50, me);
        else
                set("score", 0, me);

        message_vision( HIW "\n$N˵�����������ˣ������ˣ���Ͷ��....����\n\n" NOR, me);
        return 1;
}
int help(object me)
{
  write(@HELP
ָ���ʽ : surrender
 
���ָ��������������Ͷ������ֹս����
 
HELP
    );
    return 1;
}
 