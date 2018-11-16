// enforce.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int pts;
        int max;

        if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) )
                return notify_fail("ָ���ʽ��enforce|jiali <ʹ�����������˵�>|none|max\n");

        if( !me->query_skill_mapped("force") )
                return notify_fail("������� enable һ���ڹ���\n");

        max = (int)me->query_skill("force") / 2;
        // ��֮�����Ӽ������� 
        if (query("special_skill/might", me)) 
                max += max * 20 / 100;

        if( query("jingmai/jiali", me) )
                max+=query("jingmai/jiali", me);

        if( query("jingmai/finish", me) )
                max += ZHOUTIAN_D->query_jingmai_effect("jiali");

        if( arg=="none" )
                delete("jiali", me);
        else
        if( arg=="max" )
                set("jiali", max, me);
        else {
                if( pts < 0 || pts > max )
                        return notify_fail("��ֻ���� none ��ʾ���������������ֱ�ʾÿһ���ü���������\n");
                set("jiali", pts, me);
        }

        write("Ok.\n");
        return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: enforce|jiali <ʹ�����������˵�>|none|max

���ָ������ָ��ÿ�λ��е���ʱ��Ҫ�������������˵С�

enforce none ���ʾ�㲻ʹ��������
enforce max ���ʾ��ʹ�����������

See Also: enable
HELP );
        return 1;
}
