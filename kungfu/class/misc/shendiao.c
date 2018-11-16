// donghai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(NOR + YEL "���" NOR, ({ "shen diao", "shen", "diao" }) );
        set("title", HIG "������η" NOR);
        set("gender", "����");
        set("age", 120);
        set("long", HIY "���Ƕ��������ǰ������񣬺������������������������\n"
                        "�˵����������������ѵС�\n" NOR);

        set("combat_exp", 90000000);
        set("attitude", "heroism");
        set("max_neili", 100000);
        set("neili", 1000000);
        set("max_jing", 500000000);
        set("jing", 500000000);
        set("max_qi", 1000000000);
        set("eff_qi", 1000000000);
        set("qi", 1000000000);
        set("jingli", 100000000);
        set("max_jingli", 100000000);


        set_skill("unarmed", 1);
        set_skill("dodge", 1);
        set_skill("parry", 1);
        set_skill("sword", 20);
        set_skill("dugu-jiujian", 20);  
        set_skill("force", 1);

        map_skill("sword", "dugu-jiujian");
        map_skill("parry", "dugu-jiujian");

        set("str", 2);
        set("int", 1);
        set("con", 1);
        set("dex", 1);

        setup();

        carry_object("/clone/weapon/zhujian")->wield(); 
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
                "/clone/armor/heitie-kai",
                "/clone/armor/longshen-toukui",
                "/clone/armor/wuzhe-huwan",     
                "/clone/fam/item/longxue",
                "/clone/armor/yecha2",
                "/clone/armor/yin-erhuan",
        });

        string *gift3 = ({
                "/clone/weapon/qinggang-jian",
                "/clone/weapon/ningyue-dao",
                "/clone/weapon/qingtong-zhang",
                "/clone/weapon/tiemu-gun",
                "/clone/weapon/longwei-bian",           
                "/clone/weapon/pangu-gong",

                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/str2",

                "/clone/armor/jinsi-beixin",
                "/clone/armor/heitie-kai",
                "/clone/armor/shangu-zhixing",
                
        });

        string *gift4 = ({
                "/clone/armor/jinsi-shoutao",
                "/clone/armor/shengling-yaodai",
                "/clone/armor/chiyou-zhanpao",
                "/clone/armor/shendiao-yumao",
                "/clone/armor/yecha1",
                "/clone/armor/yinyang-erhuan",
                "/clone/armor/biyu-chai",
        });

        if (! objectp(who))return 1;
        
/*
        // ת������Ч
        if( query("reborn/times", who) )
        {
                return 1;
        }
*/
        
        
        // ǿ�йر�ս����Ϣ
        set("env/combatd", 4,   who);

        // ������ͼ
        // ���39-42
        if( MEMBER_D->is_valid_member(who) && query("quest_tuteng/start", who) ) 
        {
                int n_tt;
                object ob_tt;
        
                        if (random(10000) == 1 /*&& random(100) == 1*/)
                {
                        n_tt = 39 + random(4);
                        ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                        if (ob_tt)
                        {
                                write(HIG "������һ�ŵ�����ͼ��Ƭ��\n" NOR);
                                ob_tt->move(who, 1);
                        }
                }
        }
                
        // ��ʮ���鵽��ʮ�������¿����Ӿ����QN
        // ������һЩ��Ʒ
        if( query("combat_exp", who) >= 500000 && query("combat_exp", who) <= 800000 )
        {
                if( MEMBER_D->is_valid_member(who) )
                {                       
                        addn("combat_exp", 6+random(8), who);
                        // ����POT����2000��
                        if( query("potential", who)-query("learned_points", who)<20000000 )
                        {
                                addn("potential", 6+random(10), who);
                        }
                        if( query("experience", who)-query("learned_experience", who)<10000000 )
                        {
                                addn("experience", random(10),  who);
                        }
                }
                else
                {
                        addn("combat_exp", 3+random(4), who);
                        if( query("potential", who)-query("learned_points", who)<20000000 )
                        {
                                addn("potential", 3+random(5),  who);
                        }
                        if( query("experience", who)-query("learned_experience", who)<10000000 )
                        {
                                addn("experience", random(5),   who);
                        }
                }               

                // ���Ǯ
                if (random(1000) == 1)money = new("/clone/money/gold");
                else if (random(400) == 1)money = new("/clone/money/silver");
                else if (random(50) == 1)
                {
                        money = new("/clone/money/coin");       
                }
                if (objectp(money))
                {
                        if( query("id", money) != "coin" || 
                        (query("id", money) == "coin" && !query("env/no_coin", who)) )
                        {
                                if( query("id", money) == "gold")amount=10;
                                if( query("id", money) == "silver")amount=50+random(100);
                                if( query("id", money) == "coin")amount=100+random(300);
                                money->set_amount(amount);
                                money->move(who, 1);
                                tell_object(who, HIG "���������ϻ����" + sprintf("%d", amount) + 
                                                 query("base_unit", money)+money->name()+"��\n"NOR);                                
                        }                                               
                }
                // ��������Ʒ
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", ob)+ob->name()+"��\n"NOR);                         
                        }
                }
                if (random(100000) == 1 && random(3) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", weapon)+weapon->name()+"��\n"NOR);                         
                        }
                }
                if (random(300000) == 1 && random(3) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", armor)+armor->name()+"��\n"NOR);                           
                        }
                }
                if (random(500000) == 1 && random(4) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", armor2)+armor2->name()+"��\n"NOR);                         
                        }
                }
        }       

        // ���鲻����Ҫ��Ҳ�ɻ�ý����������ʸ���
        else
        {
                // ���Ǯ
                if (random(500) == 1 && random(8) == 1)money = new("/clone/money/gold");
                else if (random(200) == 1 && random(3) == 1)money = new("/clone/money/silver");
                else if (random(50) == 1 && random(3) == 1)money = new("/clone/money/coin");    
                if (objectp(money))
                {
                        if( query("id", money) == "gold")amount=10+random(6);
                        if( query("id", money) == "silver")amount=50+random(100);
                        if( query("id", money) == "coin")amount=100+random(300);
                        money->set_amount(amount);
                        money->move(who, 1);
                        tell_object(who, HIG "���������ϻ����" + sprintf("%d", amount) + 
                                         query("base_unit", money)+money->name()+"��\n"NOR);
                }

                // ��������Ʒ
                if (random(10000) == 1 && random(3) == 1)
                {
                        ob = new(gift[random(sizeof(gift))]);

                        if (objectp(ob))
                        {
                                ob->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", ob)+ob->name()+"��\n"NOR);                         
                        }
                }
                if (random(600000) == 1 && random(4) == 1)
                {
                        weapon = new(gift2[random(sizeof(gift2))]);

                        if (objectp(weapon))
                        {
                                weapon->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", weapon)+weapon->name()+"��\n"NOR); 
                        }
                }
                if (random(800000) == 1 && random(5) == 1)
                {
                        armor = new(gift3[random(sizeof(gift3))]);

                        if (objectp(armor))
                        {
                                armor->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", armor)+armor->name()+"��\n"NOR);            
                        }
                }
                if (random(1000000) == 1 && random(8) == 1)
                {
                        armor2 = new(gift4[random(sizeof(gift4))]);

                        if (objectp(armor2))
                        {
                                armor2->move(who, 1);
                                tell_object(who,HIR"���������ϻ����һ"+query("base_unit", armor2)+armor2->name()+"��\n"NOR);   
                        }
                }       
        }

        return ::receive_damage(type, damage, who);
}

void init()
{
        set("env/combatd", 4, this_player());
}
