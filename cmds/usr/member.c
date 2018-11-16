#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
#endif

int paying;
int help(object me);

int main(object me, string arg)
{
        string str1, str2;
        string info;
        object tar;
        string me_id, tar_id;
        int amount;

        if( time()-query_temp("last_member", me)<3 && 
            arg != "?" && ! wizardp(me))
                return notify_fail("ϵͳæ�����Ժ����ԣ�\n");

        if (arg != "?" && ! wizardp(me))
                set_temp("last_member", time(), me);

        // ������ǻ�Աʹ��member ?, member ??, member stats, member show goodsָ��
        if( !MEMBER_D->is_member(query("id", me)) )
        {
                if (! arg)return help(me);
                if (arg == "?")return help(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                        return MEMBER_D->show_all_members(0);

                if (sscanf(arg, "%s %s", str1, str2) != 2)
                        return 0;

                if (str1 != "look" && (str1 != "show" || str2 != "goods"))
                        return 0;
        }

        if (! arg)
        {
                MEMBER_D->show_member_info(me, "info");
                return 1;
        }

        if (arg == "?") return help(me);
        if (arg == "??") return help(me);
        if (arg == "stats")
        {
                return MEMBER_D->show_all_members(0);
        }

        if (sscanf(arg, "%s %s", str1, str2) != 2)
                return help(me);

        switch(str1)
        {
        case "show":
                if (str2 == "info")
                {
                        MEMBER_D->show_member_info(me, "info");
                        return 1;
                }
                else if (str2 == "payinfo")
                {
                        MEMBER_D->show_member_info(me, "payinfo");
                        return 1;
                }
                else if (str2 == "buyinfo")
                {
                        MEMBER_D->show_member_info(me, "buyinfo");
                        return 1;
                }
                else if (str2 == "goods" || str2 == "all")
                {
                        MEMBER_D->show_member_info(me, "goods");
                        return 1;
                }
                else if (str2 == "zhuaninfo")
                {
                        MEMBER_D->show_member_info(me, "transferinfo");
                        return 1;
                }
                else return help(me);

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if (! GOODS_D->buy_goods(me, str2))
                {
                        write("����ʧ�ܣ�\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "zhuan":
                if (sscanf(str2, "%d to %s", amount, tar_id) != 2)
                        return help(me);

                me_id=query("id", me);

                if (me_id == tar_id)
                        return notify_fail("��׳հ������Լ�ת�ʣ�\n");

                if (amount < 1 || amount > 100000)
                        return notify_fail("ÿ��ת�ʵĵ�λ������ 1 �� 100000 ֮�䣡\n");

                if (! MEMBER_D->db_transfer_member(me_id, tar_id, amount))
                {
                        write("ת��ʧ�ܣ�\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "check":
                if (wiz_level(me) < 4)
                        return help(me);

                if (sscanf(str2, "%s %s", tar_id, info) != 2)
                        tar_id = str2;

                // ���Է��Ƿ�Ϊ��Ա
                if (! MEMBER_D->is_member(tar_id))
                        return notify_fail("Ŀ��Ϊ�ǻ�Ա���޷���ѯ��\n");

                tar = UPDATE_D->global_find_player(tar_id);
                if (! objectp(tar))
                        return notify_fail("û�������ң�\n");

                if( !info ) info = "info";
                MEMBER_D->show_member_info(tar, info);

                UPDATE_D->global_destruct_player(tar, 1);

                return 1;

        case "remove":
                if (wiz_level(me) < 5)
                        return help(me);

                if (! MEMBER_D->db_remove_member(str2))
                {
                        write("ɾ����Աʧ�ܣ�\n");
                        return 1;
                }
                write("OK.\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        write(WHT "��������������������������������������������������������������������

" HIM "����ָ� member show info                     ��ʾ��Աϵͳ������
����ָ� member show payinfo                  ��ʾ��ʷ��ֵ������Ϣ
����ָ� member show buyinfo                  ��ʾ��ʷ������Ʒ��Ϣ
����ָ� member show zhuaninfo                ��ʾ��ʷת�ʼ�¼��Ϣ
����ָ� member show goods                    ��ʾ�����̵������Ʒ
����ָ� member check <id>                    ��ʦָ�����Ա��Ϣ
����ָ� member stats                         �г����л�Ա������Ϣ
����ָ� member zhuan <amount> to <id>        ת�����߱Ҹ�������ID

" WHT "��������������������������������������������������������������������
" HIC "�Ա���ֵ���ӵ�ַ:
" HIR "http://shop33371514.taobao.com\n
" HIG "��زο��ļ���help ntstore, help member\n" NOR);

        return 1;
}