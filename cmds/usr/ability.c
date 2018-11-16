// This program is a part of NT MudLIB

#include <ansi.h>
#ifndef F_ABILITY;
#define F_ABILITY        "/feature/ability"
#endif

inherit F_ABILITY;
int main(object me, string arg)
{
        string *lists,temp,id;
        int ab;
        int i, a_num, learned_ability;
        object ob;
        string arg1, myclass;

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        if( wizardp(me) )
        {
                if( arg && sscanf(arg, "-%s", id) == 1 )
                {
                        ob = present(id, environment(me));
                        if (!ob) ob = find_player(id);
                        if (!ob) ob = find_living(id);
                        if (!ob) return notify_fail("��Ҫ�쿴˭��������\n");
                } else
                        ob = me;
        } else
                ob = me;

        ab = query("ability", ob);

        learned_ability=query("learned_ability", ob);

        if( arg && ob == me )
        {
                if( !sscanf(arg, "+ %d", a_num) )
                        return notify_fail("��������ĸ�ʽ��ability + �������� \n");
                        
                if( a_num < 1 || a_num > 25 )
                        return notify_fail("û�д˴����������������1-20��\n");

                if( a_num < 21 )
                {
                        arg1 = bas_ability[a_num-1];

                        if( !valid_ability_improve(ob, arg1, 0) )
                                return notify_fail("��ľ���ȼ������������ո��ߵĸ���������\n");
                                
                        if( !do_ability_cost(ob, arg1, 0) )
                                return notify_fail("��û���㹻�������㴢������ߴ���������\n");
                                
                        improve_ability( ob, arg1, 0);
                        tell_object(ob, "�õ�"+ (a_num) + "���������ϡ�\n");
                        return 1;
                }

                if( !stringp(myclass=query("family/family_name", ob)) )
                        return notify_fail("���������ɣ�����ܹ���������书�ľ��裿\n");

                if( !arrayp(fam_ability[myclass]) )
                {
                        return notify_fail("OOPS�������ڵ����ɵ���ɫ��ûд��Ү��\n");
                } else
                {
                        arg1 = fam_ability[myclass][a_num-21];
                        if( !valid_ability_improve(ob, arg1, 1) )
                                return notify_fail("��ľ���ȼ������������ո��ߵĸ���������\n");
                                
                        if( !do_ability_cost(ob, arg1, 1) )
                                return notify_fail("��û���㹻�������㴢������ߴ���������\n");
                                
                        improve_ability(ob, arg1, 1);
                        tell_object(ob, "�õ�"+ (a_num) + "���������ϡ�\n");
                }

                return 1;
        }

        
        write("\n");
        write(HIC    "���              ��Ч                      �ȼ�          ��������\n"NOR);
        write(HIG "��������������������������������������������������������������������\n" NOR);
        write(HIC"�����������ף�\n\n"NOR);

        for(i=0; i<sizeof(bas_ability); i++)
                write(sprintf(WHT"("WHT"%3d"WHT")", (i+1)) + HIC"\t"+ get_ability_info(ob, bas_ability[i], 0) + NOR);
        write("\n");
     
        write(HIG "��������������������������������������������������������������������\n" NOR);
        write(HIC"�����������ף�\n\n"NOR);

        if( !stringp(myclass=query("family/family_name", ob)) )       
                write("������������ɫ��\n");
        /*
        else if( query("betrayer", ob) )
                write("������ʦǰ�ƣ��޷���������ɵľ��衣\n");
        */
        else if( !arrayp(fam_ability[myclass]) )
                write("OOPS�������ڵ����ɵ���ɫ��ûд��Ү��\n");
        else
                for( i=0; i<5; i++ )
                        write(sprintf(WHT"("WHT"%3d"WHT")", (i+21)) + HIC"\t"+ get_ability_info(ob, fam_ability[myclass][i],1) + NOR);

        write("\n");
        write(HIG "��������������������������������������������������������������������\n" NOR);

        write(HIW"�������ܹ���� "HIC + ab + NOR+HIW" ��������\n" NOR);
        write(HIW"���Ѿ���ȥ�� " RED+ learned_ability +NOR+HIW" ����������ʣ�� "HIG+ (ab-learned_ability) + NOR+HIW" ��ɹ����䡣\n" NOR);
        //write(HIG "��������������������������������������������������������������������\n" NOR);
        write("\n\n");
        return 1;
}


int help(object me)
{
write(@HELP

[0;1;37m����������������������������������������������������������������[0m
[0;1;36mָ���ʽ :     ability [0m
[0;1;37m����������������������������������������������������������������[0m

ability         ����֪����Ŀǰ��ѧ����һ��������
ability + n     ��ߵڣ��������ĵȼ���

��������̶��Ϸ�г�����ֵ������ֵ������������һ����Ҫ;����
��ͬ����ȼ��ģ������ߵ��˻��и������Ѫ����ɸ�����˺�����
���߿����и��ߵ�ѧϰЧ�ʡ���κ�������������ǳ�Ϊ���ֵ�һ
�����Ҫ��

���������ȼ���������������㣬�Ϳ����������ĸ��������ˣ�
�������������Ϳ��Կ���һ���������б��������࣬��һ
�๲�У�����������ɶ�������ϰ���������߻������Եģ���
������������������书�ľ������ڣ���ͬ���ɸ�����ɫ��

ÿ����������ʮ����ÿ���Ĺ�Ч������ϸ˵����

����ϰʲô�أ�������ɸ�����ͬ���ɵ��ص���߸���ϲ��������
�ˡ����������ս���г־ã��Ͷ����Щ��������������������
��Ҫ���ɱ�����������Щ������������



���������ã�
    ��ҿ�������̶�̳Ǵ��������������������Ѿ�����õ������㡣
���ú������������׻�ԭΪ�����㡣��һ����������������һ����
����֮��ÿ����һ�Σ����ٶ�������һ����������25�μ�֮�������
�������ٶ����������ģ��̶�ÿ��25��������

[0;1;37m����������������������������������������������������������������[0m
HELP
    );

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        return 1;
}
