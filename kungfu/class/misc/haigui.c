// donghai.c

#include <ansi.h>

inherit NPC;

string get_long();

void create()
{
        set_name(NOR + YEL "���꺣��" NOR, ({ "hero of chelonian", "chelonian", "hero" }) );
        set("title", HIM "��������" NOR);
        set("gender", "����");
        set("age", 88888);
        set("long", get_long());

        set("combat_exp", 90000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 90000000);
        set("neili", 90000000);
        set("max_jing", 90000000);
        set("jing", 90000000);
        set("max_qi", 90000000);
        set("eff_qi", 90000000);
        set("qi", 90000000);
        set("jingli", 90000000);
        set("max_jingli", 90000000);

        set("str", 1);
        set("int", 30);
        set("con", 1);
        set("dex", 1);
        set("jiali", 0);

        setup();
}

void unconcious()
{
        //die();
        set("max_neili", 90000000);
        set("neili", 90000000);
        set("max_jing", 90000000);
        set("jing", 90000000);
        set("max_qi", 90000000);
        set("eff_qi", 90000000);
        set("qi", 90000000);
        set("jingli", 90000000);
        set("max_jingli", 90000000);
        revive();
}

void die()
{
        //unconcious();
        ::die();
        return;
}

string get_long()
{

                string msg;

                msg =  "\n" NOR + YEL
"����������Ӣ�ۺ��꣬�ʺ�����ʵ���书������й��\n" HIC
"�������ԣ�1\n"
"������ǣ�30\n"
"��������1\n"
"���������1\n"
"��   ���� 0\n"
"Σ�ճ̶ȣ�΢С\n" HIG
"��ʹ��ָ�� crave <��Ϣ> �ں��걳�Ͻ��е�̣�\n\n" HIR 
"�������꺣�걳��������������˺ܶ����֡�\n\n" NOR;

        return msg;
}

int receive_damage(string type, int damage, object who)
{
        object money, ob, weapon, armor, armor2;
        int amount;
        
        string *gift = ({
                "/clone/fam/pill/puti1",
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/lingzhi2",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/linghui1",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/linghui3",
                "/clone/fam/pill/sheli1",
                "/clone/fam/pill/sheli2",
                "/clone/fam/pill/sheli3",
        });
        
        string *gift2 = ({
                "/clone/weapon/qinggang-jian",
                "/clone/weapon/ningyue-dao",
                "/clone/weapon/qingtong-zhang",
                "/clone/weapon/tiemu-gun",
                "/clone/weapon/longwei-bian",
                "/clone/weapon/pangu-gong",
                "/clone/armor/yin-erhuan",
        });

        string *gift3 = ({
                "/clone/armor/tie-shoutao",
                "/clone/armor/shenwu-xiangquan",
                "/clone/armor/gangtie-kai",
                "/clone/armor/zhanshen-toukui",
        });     

        string *gift4 = ({
                "/clone/armor/wushi-pifeng",
                "/clone/armor/feima-xue",
                "/clone/armor/yecha2",
                "/clone/armor/zijinhua-erhuan",
                "/clone/armor/xingyue-erhuan",
        });

        if (! objectp(who))return 1;

/*
        // ת������Ч
        if (query("reborn/times", who))
        {
                return 1;
        }
*/
        
        set("env/combatd", 4, who);
        
        
                // ������ͼ
                // ���36-38
                if( MEMBER_D->is_valid_member(who) && query("quest_tuteng/start", who) ) 
                {
                        int n_tt;
                        object ob_tt;
        
                        if (random(10000) == 1 /*&& random(100) == 1*/)
                        {
                                n_tt = 36 + random(3);
                                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                                if (ob_tt)
                                {
                                        write(HIG "������һ�ŵ�����ͼ��Ƭ��\n" NOR);
                                        ob_tt->move(who, 1);
                                }
                        }
                }
                        
        // ʮ�������¿����Ӿ����QN
        // ������һЩ��Ʒ
        if (query("combat_exp", who) <= 500000)
        {
                if (MEMBER_D->is_valid_member(who))
                {
                        addn("combat_exp", 2 + random(4), who);
                        addn("potential", 2 + random(4), who);
                        addn("experience", random(4), who);                      
                }
                else
                {
                        addn("combat_exp", 1 + random(2), who);  
                        addn("potential", 1 + random(2), who);
                        addn("experience", random(2), who);
                }
                // ���Ǯ
                if (random(200) == 1) money = new("/clone/money/gold");
                else if (random(100) == 1) money = new("/clone/money/silver");
                else if (random(30) == 1)
                {
                        money = new("/clone/money/coin");       
                }
                if (objectp(money))
                {
                        if (query("id", money) != "coin" || 
                           (query("id", money) == "coin" && !query("env/no_coin", who)))
                        {
                                if ( query("id", money) == "gold" )amount = 1;
                                if ( query("id", money) == "silver" )amount = 5 + random(10);
                                if ( query("id", money) == "coin" )amount = 10 + random(30);
                                money->set_amount(amount);
                                money->move(who, 1);
                                tell_object(who, HIG "������꺣�����ϻ����" + sprintf("%d", amount) + 
                                        query("base_unit", money) + money->name() + "��\n" NOR);                                
                        }                                               
                }       
                // ��������Ʒ
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who, HIR "������꺣�����ϻ����һ" + query("base_unit", ob) + ob->name() + "��\n" NOR);                            
                        }
                }
                if (random(10000) == 1 && random(3) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who, HIR "������꺣�����ϻ����һ" + query("base_unit", weapon) + weapon->name() + "��\n" NOR);                            
                        }
                }
                if (random(300000) == 1 && random(4) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who, HIR "������꺣�����ϻ����һ" + query("base_unit", armor) + armor->name() + "��\n" NOR);                              
                        }
                }
                if (random(500000) == 1 && random(4) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who, HIR "������꺣�����ϻ����һ" + query("base_unit", armor2) + armor2->name() + "��\n" NOR);                            
                        }
                }
        }       

                
        return ::receive_damage(type, damage, who);
        
}
