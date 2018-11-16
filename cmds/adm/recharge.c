#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string target;
        int    money;
        int flower;
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(boss)"))
                return 0;

        if( query("id", me) != "cqpkzaz" && query("id", me) != "luoyun")
                return 0;
        
        if (! arg || sscanf(arg, "%s %d", target, money) != 2)
                return notify_fail("ָ���ʽ��recharge <id> <amount>��\n");
        
        if (! objectp(ob = UPDATE_D->global_find_player(target)))
                return notify_fail("û������ˣ�\n");
                
        if (MEMBER_D->is_member(target))
                MEMBER_D->db_pay_member(target, money);
        else
                MEMBER_D->db_create_member(target, money);
                
        flower = money / 100;
        addn("flowers/amount", flower, ob);
        if( ob ) tell_object(ob, HIC "������ " + flower + " �����ֵ�ʦ����Ʊ��\n" NOR);

        log_file("static/recharge",sprintf("%s %s have recharge %s %d $NT\n",TIME_D->replace_ctime(time()),query("id", me),target,money));
        
        UPDATE_D->global_destruct_player(ob, 1);
        write("ok.\n");
        return 1;
}

