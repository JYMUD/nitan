// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me,string arg)
{
        int amount;
        object target;
        string who, tar_name;

        if( me->is_busy() ) {
                write(BUSY_MESSAGE);
                return 1;
        }

        if( !arg ) {
                write(HIG "Ŀǰ��̶��������Ϊ�� " HIY + MONEY_D->money_str(DB_D->query_data("fund/balance")) + "��\n" NOR);
                return 1;
        }

        if( sscanf(arg, "juan %d", amount) == 1 ) {
                if( amount <= 0 ) {
                        write("��������Ϊ����\n");
                        return 1;
                }

                if( query("balance", me) < amount ) {
                        write("�����еĴ��û����ô�ࡣ\n");
                        return 1;
                }
                addn("balance", -amount, me);
                addn("weiwang", amount/10000, me);
                DB_D->add_data("fund/balance", amount);
                if( amount >= 100000000 )
                CHANNEL_D->channel_broadcast("chat", HIW + me->name(1) + "(" +
                              me->query_id() + ")" HIC" Ϊ��̶������� "  + HIY + MONEY_D->money_str(amount) + HIC "��\n" NOR);
                write("�ǳ���л��Ϊ��̶�����Ĺ��ף�\n");

                me->start_busy(1);
                return 1;
        } else
        if( sscanf(arg, "fenpei %s %d", who, amount) == 2 ) {
                if( !wizardp(me) && query("viremploy/job", me) != "���ֵ�ʦ" )
                        return 1;

                if( who == me->query_id(1) ) {
                        write("���ܸ��Լ��������\n");
                        return 1;
                }

                if( amount <= 0 ) {
                        write("��������Ϊ����\n");
                        return 1;
                }

                if( amount > 1000000000 ) {
                        amount = 1000000000;
                        write("������ʮ�����ƽ�\n");
                }

                if( DB_D->query_data("fund/balance") < amount ) {
                        write("��̶�����㡣\n");
                        return 1;
                }

                target = UPDATE_D->global_find_player(who);

                if( !objectp(target) ) {
                        write("�޴���ҡ�\n");
                        UPDATE_D->global_destruct_player(target, 1);
                        return 1;
                }

                tar_name = target->name(1);
                addn("balance", amount, target);
                DB_D->add_data("fund/balance", -amount);

                target->save();

                UPDATE_D->global_destruct_player(target, 1);

                // ��¼
                log_file("fund", me->query_id(1) + " �� " + ctime(time()) + " ����̶������� " +
                          amount + " �� " + who + "��\n");

                // ����
                CHANNEL_D->channel_broadcast("chat", HIW + me->name(1) + "(" +
                              me->query_id(1) + ")" HIC "����̶�����з��� "  + HIY +
                              MONEY_D->money_str(amount) + HIC " �� " + tar_name + " ��\n" NOR);

                return 1;
        }

        return notify_fail("��ʽ����\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : fund <����>
fund                              ��ʾ��̶��������
fund juan <����>                  ������̶����
fund fenpei <���ID> <����>       ������̶�����ĳλ���
HELP );
        return 1;
}
