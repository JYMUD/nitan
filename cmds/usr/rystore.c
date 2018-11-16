
#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_honord"
#endif

int help(object me);
int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;

        if( !arg || arg == "") return help(me);
        if( time()-query_temp("last_member", me)<3 )
                return notify_fail("ϵͳæ�����Ժ����ԣ�\n");

        if( !wizardp(me) )
                set_temp("last_member", time(), me);

        if( sscanf(arg, "%s %s", str1, str2) != 2 )
                return help(me);

        switch(str1)
        {
        case "show":
                return GOODS_D->show_goods(me, str2);

        case "exchange":
                if( !GOODS_D->exchange_goods(me, str2))
                {
                        write("�һ�ʧ�ܣ�\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        int money;

        money = query("honors", me);

        write(HIY "�� ��Ŀǰ������Ϊ " + money + " (NT)
" WHT "��������������������������������������������������������������������

" HIM "����ָ�    rystore show all                  �鿴�����̳ǵĻ���
����ָ�    rystore exchange <����>           �һ�ָ�����ŵ���Ʒ

" WHT "<����>  ��    ������Ʒ�� name �� ���
" WHT "��������������������������������������������������������������������\n" NOR);

        return 1;
}

