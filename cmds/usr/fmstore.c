#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_familyd"
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
                // ��ֹע��idˢ��Ʒ
                if( query("combat_exp", me) < 3000000 && !MEMBER_D->is_valid_member(me) )
                        return notify_fail("����ʱ��û���ʸ񽫹��׵�һ�Ϊ��Ʒ��\n");
                
                if( sscanf(str2, "%s %d", str2, amount) != 2 )
                        amount = 1;
                
                if( amount > 100 ) amount = 100;
                if( amount < 1 ) amount = 1;        
                if( !GOODS_D->exchange_goods(me, str2, amount))
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

        money = query("family/gongji", me);

        write(HIY "�� ��Ŀǰ�����ɹ���Ϊ " + money + " (NT)
" WHT "��������������������������������������������������������������������

" HIM "����ָ�    fmstore show all                  �鿴�����̳ǵĻ���
����ָ�    fmstore exchange <����> <����>    �һ�ָ�����ŵ���Ʒ

" WHT "<����>  ��    ������Ʒ�� name �� ���
" WHT "��������������������������������������������������������������������\n" NOR);

        return 1;
}

