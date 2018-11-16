inherit DREAM_NPC;
#include <ansi.h>

int is_snake(){return 1;}

void create()
{
        set_name(HIM "ɺ"HIY"��" HIC "��" NOR, ({ "shanhu she", "shanhu", "she" }));
        set("long", RED "����һ����ʰ�쵵�ɺ���ߣ���˵���������۾���֮�ϡ�\n" NOR);

        set("age", 90);
        set("str", 135);
        set("dex", 50);
        set("max_qi", 129900);
        set("max_ging", 129900);
                set("eff_jing", 100000);
                set("max_jing", 100000);
                set("jingli", 100000);
                set("max_jingli", 100000);
                set("jingli", 100000);
                set("max_neili", 25000);
                set("neili", 25000);
                set("eff_jingli", 100000);
        set("combat_exp", 500000000);

         set("no_nuoyi", 1); // ����Ų��Ӱ��
         
        set("snake_poison", ([
                "level"  : 550,
                "perhit" : 260,
                "remain" : 200,
                "maximum": 200,
                "supply" : 80,
        ]));

        set_temp("apply/parry", 350);
        set_temp("apply/dodge", 150);
        set_temp("apply/attack", 150);
        set_temp("apply/defense", 180);
        set_temp("apply/unarmed_damage", 580);
        set_temp("apply/armor", 380);

                set("gift/exp", 100);
                set("gift/pot", 80);
                set("oblist", ([
                        "/clone/fam/gift/str3" : 2,
                        "/clone/fam/gift/int3" : 2,
                        "/clone/armor/lan-feihun" : 10,
                        "/clone/armor/lan-feihun2" : 6,                
                        "/clone/armor/shenwu-xiangquan":40,
                        "/clone/armor/shenwu-xiangquan2":30,
                        "/clone/armor/shenwu-xiangquan3":20,                                        
                        "/clone/armor/yinyang-erhuan":20,
                        "/clone/armor/yinyang-erhuan2":10,
                        "/clone/armor/yinyang-erhuan3":8,        
                ]));
        setup();
                add_money("silver", 8 + random(8));
}

mixed hit_ob(object me, object ob, int damage)
{
        mapping p;
        string  msg;
        int force;
        int dur;

        p=query("snake_poison", me);
        if (! p) return;
        if (damage / 3 + random(damage * 2 / 3) <
            query_temp("apply/armor", ob) )
        {
                // Defeated by armor
                return;
        }

        msg = "";
        dur = p["perhit"];
        if (dur > (int)p["remain"]) dur = p["remain"];
        p["remain"] = (int)p["remain"] - dur;
        this_object()->apply_condition("poison-supply", 1);
        if (! dur) return;


        force = (int)ob->query_skill("force");
        if (random(force / 2) + force / 2 >= (int)p["level"] &&
            query("neili", ob)>damage/5 )
        {
                if( query("qi", ob)<150 )
                {
                        msg = HIR "������˿���Щ���飬��æ�˹����⣬��"
                              "��һʱ������֧������ʩΪ��\n" NOR;
                } else
                if( query("jing", ob)<60 )
                {
                        msg = HIR "������˿���Щ���飬��æ�˹����⣬��"
                              "��һʱ���񲻼ã�����ʩΪ��\n" NOR;
                } else
                if( query("neili", ob)<damage/5+50 )
                {
                        msg = HIR "������˿���Щ���飬��æ�˹����⣬��"
                              "��һʱ�������㣬����ʩΪ��\n" NOR;
                } else
                {
                        addn("neili", -damage/5, ob);
                        ob->receive_damage("qi", 20);
                        ob->receive_damage("jing", 10);
                        return HIM "����ñ�ҧ�еĵط���Щ���飬��æ�˹�"
                               "���ⶾ�ԡ�\n" NOR;
                }
        }

        if (ob->affect_by("poison", ([ "level" : (int)p["level"] / 2,
                                       "name"  : "�߶�",
                                       "id"    : "nature poison",
                                       "duration" : dur / 2, ])))
        {
                msg += HIR "$n" HIR "��ɫһ�䣬ֻ����ҧ�еĵط�һ����ľ��\n" NOR;
        }
        return msg;
}