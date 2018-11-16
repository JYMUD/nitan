inherit BOSS;
#include <ansi.h>
int big_blowing();
void create()
{
        set_name(HIR"�һ�����"NOR, ({ "fire dragon king", "dragon king", "dragon" }) );
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 200);
        set("long",
"����һ��ȫ���죬�����֮��Ļ����������������
��ȫ��ɢ���ų��ɫ�Ļ��档\n");

        set("str", 248);
        set("con", 252);
        set("dex", 222);

        set_skill("dodge", 2999);
        set_skill("force", 2999);
        set_skill("unarmed", 2999);
        set_skill("parry", 2999);
        set("max_qi", 20000000);
        set("max_jing", 9999999);
        set("max_neili", 90001000);
        set("neili", 90001000);
        set("jiali", 900000);
        set("attitude", "aggressive");
        set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("death_msg", "$N����һ������ȥ��\n");
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: big_blowing :)
        }) );

        set("combat_exp", 901100000+random(600110000));
        set("bellicosity", 30000 );
        set("level", 100);

        set_temp("apply/attack", 3000+random(3000));
        set_temp("apply/unarmed_damage",3000+random(3000));
        set_temp("apply/armor", 3000+random(3000));
        set_temp("apply/add_weak", 70);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);

        set("rewards", ([
                "exp"   : 40000,
                "pot"   : 10000,
                "mar"   : 1000,
                "score" : 600,
                "gold"  : 100,
        ]));
        set("drops", ([
                "MO&A3000"       :       3,
                "MO&A3001"       :       3,
                "MO&A3002"       :       3,
                "MO&A3003"       :       3,
                "MO&A3004"       :       3,
                "MO&A3005"       :       1,
                "MO&A3006"       :       1,
                "FI&/clone/tessera/rune24"   :           1,
                "FI&/clone/tessera/rune25"   :           1,
                "FI&/clone/tongren/tongren"+(1+random(2))   :           1,
        ]));

        setup();
        carry_object("/clone/money/gold")->set_amount(200);
}
int big_blowing()
{
        message_vision( HIR "\n\n�һ��������������һ������ȫ��תΪ�ʺ�Ļ�ɫ�����������ʹ��˼�������\n\n" NOR,
                        this_object());
        call_out("hurting", random(2)+1);


        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;
        message_vision( HIR "\n\n�һ������³�һ�ɳ�ɷٽ�Ļ��森����������ƺ�����ȼ���ţ�����\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
                dam = 100000+random(100000);
                inv[i]->receive_wound("qi",dam, this_object());
                inv[i]->receive_wound("jing",dam/2, this_object());
                inv[i]->affect_by("poison",
                                  ([ "level" : 1500,
                                     "id":query("id", this_object()),
                                     "name" : "�һ������Ļ�",
                                     "duration" : 200 ]));
                tell_object(inv[i], HIG "�������һ������Ļ𶾡�\n");
                COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}

void die()
{
        object obj, env;
        object killer;
        object ob, me;
        int exp;
        int userexp;
        int i;

        me = this_object();

        if (objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                me->full_self();
                addn_temp("apply/attack", 3000+random(3000));
                addn_temp("apply/unarmed_damage",3000+random(3000));
                addn_temp("apply/armor", 3000+random(3000));
                return;
        }

        if (! query("have_reborn"))
        {
                set("have_reborn", 1);
                me->full_self();
                return;
        }
                env = environment(this_object());
        if (objectp(killer=this_object()->query_last_damage_from()))
        {
                userexp=query("combat_exp", killer);
                exp=(query("literate", killer)*4)+random(10000)+40000+userexp/60000;
                if (exp > 100000) exp = 100000;

                if( !query_temp("m_success/����", killer) )
                {
                        set_temp("m_success/����", 1, killer);
                        addn("combat_exp", exp, killer);
                        addn("potential", 50000, killer);
                        message("channel:chat",HBMAG"��������硿"+query("name", killer)+"�ɹ���ɱ���˶������⿪�˷�ӡ!�õ����������Ǳ�ܼ���ʯ.\n"NOR,users());

                message_vision(MAG "һ���������������ҫ��$N��\n" NOR, killer);
                message_vision(HIR "һ�Ż����͵����ڣ�һ������˵����лл���ǽ⿪�˵��߸���ӡ����Щ��ʯ����Ϊл��ɣ�����\n" NOR, this_object());

                for (i = 0; i < 7; i++)
                {
                        obj = new("/clone/tessera/rune2" + random(10));
                        obj->move(env, 1);
                }
                if (! random(5))
                {
                        obj = new("/clone/goods/tianshi-charm");
                        obj->move(env, 1);
                }

                message_vision(HIY "�����ȥ����ͻȻ���ֵ����кܶණ�����������⡣\n" NOR, this_object());
                }
        }
        set("exits/north", "/d/city/wumiao", env);
/*
        message_vision("$N����һ������ȥ��\n", this_object());
        destruct(this_object());
*/
        return ::die();
}

void unconcious()
{
        object ob;

        if (objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                this_object()->full_self();
                return;
        }

        die();
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;

        damage = 10000 + random(10000);
        damage-=query_temp("apply/reduce_fire", ob);
        if (damage < 0) damage = 0;
        ob->receive_damage("qi", damage, me);
        ob->receive_wound("qi", damage, me);
        set("neili",query("max_neili",  me), me);
        return HIR "$N" HIR "���𡱵�һ���³�һ�Ļ��棬��ʱ��$n"
               HIR "�о�������������ƺ�����ȼ���š�\n" NOR;
}

