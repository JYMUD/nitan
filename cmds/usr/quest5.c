#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object me, string arg)
{
        int mark;
        int quest;
        string *site;

        site=({"��������","��������","��ȸ����","�׻�����"});
        if( !(quest=query("jungong", me)) )
        return notify_fail(
               HIW"�㲢û�������κι�����������һ����\n"NOR);

        mark=query_temp("guo_shoucheng/mark_shadi", me);

        if( mark && mark < 5 )
             write(HIW"\n�����ڵ�������ȥЭ��"HIR+site[mark-1]
                     +HIW"���ξ��������ɹ����ӵ����֣�\n"NOR);
         
        else
          if( query_temp("guo_shoucheng/mark_jianlou", me) )
             write(HIW"\n�����ڵ�������ȥЭ����������"HIR"���Ǽ�¥"
                    +HIW"���ξ������ξѻ��ɹŹ����ֵ�����\n"NOR);
        else
             write(
HIW"\n===============================================================\n"NOR
+HIR"            ���Ѿ���������"HIY
+chinese_number(quest)+HIR"�ߣ�\n"NOR+
HIW"===============================================================\n"NOR);

       return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quest5  ���ָ�������ʾ�����Ѿ�����������������
HELP
        );
        return 1;
}
