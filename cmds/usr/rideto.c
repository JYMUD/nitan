// This program is a part of NT MudLIB
// rideto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        object riding, env;
        string where;

        if( !arg )
        {
                MAP_D->show_trans(me);
                return 1;
        }
                
        if (me->over_encumbranced())
                return notify_fail("��ĸ��ɹ��أ��������á�\n");

        if (me->query_encumbrance() < 0)
                return notify_fail("��ĸ��ɳ��ֹ��ϣ��������á�\n");

        if( query_temp("sleeped", me) )
                return notify_fail("�������������ء�\n");

        if (me->is_in_prison())
                return notify_fail("�����������أ������ʲô����\n");

        if (me->is_fighting())
                return notify_fail("����������ս����\n");

        if( me->is_ghost() )
                return notify_fail("�㻹�ǵȻ�������˵�ɡ�\n");

        if( me->is_busy() || query("doing", me) )
                return notify_fail("��Ķ�����û����ɣ������ƶ���\n");

        if( !objectp(riding=query_temp("is_riding", me)) )
                return notify_fail("�㻹û�����\n");

        if( !present(query("id", riding),me) )
                return notify_fail("������ﲻ������ߣ�\n");

/*
        if( !query("outdoors", environment(me)) )
                return notify_fail("�ڷ����ﲻ�����ܣ�\n");
*/
        // �����в���rideto
        env = environment(me);
        if( objectp(env) )
        {
                if( base_name(env) == "/clone/fam/item/zhangpeng" || 
                        base_name(env) == "/clone/fam/item/zhangpeng2" )
                {
                        return notify_fail("�˴���������\n");
                }
        }

        if( query("no_rideto", env) )
                return notify_fail("�����޷�������\n");
               
        if( query("no_magic", env) || query("maze", env) )
                return notify_fail("�㷢�������е�Ź֣����������������ָ�ӣ�\n");

        //if (me->query_condition("killer"))
        //        return notify_fail("�������������أ��㻹��С��Ϊ������ڹٵ������޼ɵ����ߣ�\n");

        if( objectp(riding=query_temp("is_riding", me)) )
        {           
                MAP_D->move_to(me, arg);
                return 1;
        }
        
        return notify_fail("�㻹������ƥ������˵�ɡ�\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : rideto <�ص�>

���ָ�������������ָ���ص㣬���ָ��������������
�ο������ܵ��ĵط���

HELP );
        return 1;
}
