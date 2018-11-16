#include <ansi.h> 

int help(object me);
int main(object me, string arg)
{
        object *virlist;
        object ob;
        object eob;
        string str;
        string target;
        int option = 0;
        int amount;
        int i;

        amount = query("flowers/amount", me);
        if( !arg || arg == "" )
        {
                write(HIW "��Ŀǰӵ�� " + amount + " �����ֵ�ʦ����Ʊ��\n" NOR);
                if( sizeof(virlist = DB_D->query_data("virlist/teacher")) )
                {
                        str = HIC "\n��"  + HIM "��Ϸ��������ְ��ʦ" + HIC + "��\n" NOR;  
                        for (i = 0; i < sizeof(virlist);i ++) 
                        {
                                if( objectp(eob = find_player(virlist[i])) )
                                {
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ")--����--"; 
                                        str += HIY "�ʻ� " + query("flowers/recognition", eob) + " ��--"; 
                                        str += HIY "������ " + query("flowers/antipathy", eob) + " ��\n" NOR; 
                                }
                                else
                                {
                                        eob = UPDATE_D->global_find_player(virlist[i]); 
                                        if( !objectp(eob) ) continue; 
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ") --����ʱ�䣺" + NOR; 
                                        str += HIY + sprintf("%d", (time() - query("last_on", eob)) / 86400) + "��--";
                                        str += HIY "�ʻ� " + query("flowers/recognition", eob) + " ��--"; 
                                        str += HIY "������ " + query("flowers/antipathy", eob) + " ��\n" NOR; 
                                        UPDATE_D->global_destruct_player(eob, 1); 
                                }
                        }
                        write(str);
                }
                return 1;
        }

        if( amount < 1 )
                return notify_fail(HIW "��Ŀǰӵ�� 0 �����ֵ�ʦ����Ʊ��\n" NOR);

        if( sscanf(arg, "-a %s", target) )
                option = 1;
        else if( sscanf(arg, "-o %s", target) )
                option = 0;
        else
                return help(me);

        if( !objectp(ob = UPDATE_D->global_find_player(target)) ) 
                return notify_fail("û������ˣ�\n"); 

        if( query("viremploy/job", ob) != "���ֵ�ʦ" )
        {
                UPDATE_D->global_destruct_player(ob, 1);
                write("���������ֵ�ʦ����ֻ�ܸ����ֵ�ʦͶ����Ʊ��(who -v�ɲ�ѯ���ֵ�ʦ)\n");
                return 1;
        }

        addn("flowers/amount", -1, me);
        if( option )
        {
                addn("flowers/recognition", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "�����ֵ�ʦ" + ob->query_idname()+"�Ĺ�����ʾ�Ͽɣ�����"
                        HIW"һ��"HIY"����"HIW"��"HIG"��"HIR"��"NOR"��\n");
        }
        else
        {
                addn("flowers/antipathy", 1, ob);
                CHANNEL_D->channel_broadcast("news", me->query_idname() + "�����ֵ�ʦ" + ob->query_idname()+"�Ĺ����������⣬�Ӹ�"
                        HIW"һ��"HIY"����"HIW"��"HIG"��"HIR"����"NOR"��\n");
        }

        UPDATE_D->global_destruct_player(ob, 1);  
        return 1; 

}

int help(object me)
{
        write("flowers                 ��ѯ�Լ�ӵ�����ֵ�ʦ����Ʊ��\n"
              "flowers -a <id>         Ͷ�����ֵ�ʦһ�����������Ʊ\n"
              "flowers -o <id>         Ͷ�����ֵ�ʦһ�Ų����������Ʊ\n");
        return 1;
}
