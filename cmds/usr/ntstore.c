#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
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

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if( !GOODS_D->buy_goods(me, str2))
                {
                        write("����ʧ�ܣ�\n");
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
        int money, buyvalue;

        money = MEMBER_D->db_query_member(me, "money");
        buyvalue = MEMBER_D->db_query_member(me, "buyvalue");

        write(HIY "�� ��Ŀǰ�����߱�Ϊ " + money + " (NT)
" WHT "��������������������������������������������������������������������

" HIM "����ָ�    ntstore show all                  �鿴�����̳ǵĻ���
����ָ�    ntstore show object               ��ʾ�����̳���Ʒ��
����ָ�    ntstore show pill                 ��ʾ�����̳ǵ�ҩ��
����ָ�    ntstore show special              ��ʾ�����̳��ؼ���
����ָ�    ntstore show story                ��ʾ�����̳ǹ�����
����ָ�    ntstore show symbol               ��ʾ�����̳ǵķ���
����ָ�    ntstore show enchase              ��ʾ�����̳���Ƕ��
����ָ�    ntstore show prop                 ��ʾ�����̳�װ����
����ָ�    ntstore show other                ��ʾ�����̳�������
����ָ�    ntstore show srv                  ��ʾ�����̳Ƿ�����
����ָ�    ntstore buy <����>                ����ָ�����ŵ���Ʒ
����ָ�    ntstore look <����>               �鿴ָ����Ʒ������

" WHT "<����>  ��    ������Ʒ�� name �� id �� ���
" WHT "��������������������������������������������������������������������
" HIC "�Ա���ֵ���ӵ�ַ: " HIR "http://shop61698067.taobao.com\n
" HIY "���ܹ�����Ϸ�̳����� " + buyvalue + " (NT)��

" HIG "��زο��ļ���help member\n\n" NOR);

        return 1;
}