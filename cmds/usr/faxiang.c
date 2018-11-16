// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *bh = ({}), *ulist;
        string banghui;
        int k, count, piece, rest_money, reward_money, reward; 
         
        if( !stringp(banghui=query("bunch/bunch_name", me) )
         || query("bunch/level", me)<9 )
                return notify_fail("����Ȩ�ڰ���ڽ��з��á�\n");

        if (! arg || ! sscanf(arg, "%d", rest_money) || rest_money < 1 
            || rest_money > 10000)
                return notify_fail("��׼���ö���Ǯ(gold)�����д˴η��ã�\n");

        rest_money = rest_money * 10000;

        if (query(banghui + "/money", get_object(BUNCH_D)) < rest_money + 100000000)
                return notify_fail("��������û����ô��Ǯ�ɹ����á�\n");
        
        addn(banghui+"/money", -rest_money, get_object(BUNCH_D));
        BUNCH_D->save();
        
        ulist = users();
        
        for (k = 0, piece = 0, count = 0; k < sizeof(ulist); k++)
        {
                if( !environment(ulist[k]) || !query("bunch/bunch_name", ulist[k] )
                 || query("bunch/bunch_name", ulist[k]) != banghui )
                        continue;
                bh += ({ulist[k]});
                count++;
                piece+=1+query("bunch/level", ulist[k]);
        }

        if( count )
        { 
                rest_money = rest_money / piece; 
                for (k = 0; k < count; k++)
                {
                        reward_money=rest_money*(query("bunch/level", bh[k])+1);
                        tell_object(bh[k], "���ɡ�" + banghui
                                    +"��" + "���ã��������������"
                                    + MONEY_D->money_str(reward_money) + "��\n");

                        if( query("bunch/quest", bh[k]) >= 4 )
                        {
                                reward = reward_money / 10000;
                                reward = reward * (random(4) + 1);
                                addn("combat_exp", reward, bh[k]);
                                addn("potential", reward/3, bh[k]);
                                addn("score", reward/50, bh[k]);
                                tell_object(bh[k], HIG"���������Ϊ�������"
                                            + "�����ף���" + banghui + "��" + "������\n"
                                            + chinese_number(reward) + "�㾭�顢"
                                            + chinese_number(reward / 3) + "��Ǳ�ܺ�"
                                            + chinese_number(reward / 50) + "���ۺ����ۣ�\n"NOR);
                                set("bunch/quest", 0, bh[k]);
                        }    
                        reward_money=query("balance", bh[k])+reward_money;
                        
                        if (reward_money > 2000000000 || reward_money < 0)
                        {
                                set("balance", 2000000000, bh[k]);
                        } else
                                set("balance", reward_money, bh[k]);
                }
        }
        
        for (k = 0; k < sizeof(ulist); k++)    
        {
                if( query("balance", ulist[k])>2000000000 )
                {
                        set("balance", 2000000000, ulist[k]);
                        tell_object(ulist[k], RED "����Ǯׯ��Ǯ�Ѵﵽ��ʮ�����ƽ𣬿�㻨�ɣ�\n" NOR);
                }
        }

        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��faxiang [�ƽ�����] 

�����ڱ����ڷ��ã��������߰���Ա�����һ���İ�����롣

HELP
        );
        return 1;
}                   
