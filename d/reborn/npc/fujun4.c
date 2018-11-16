// This program is a part of NITAN MudLIB
// Fujun4.c
// Written by Lonely@NITAN (03/29/2009)

#include <ansi.h>

inherit NPC;

int  ask_offer();
void destroy();
int  do_offer(string arg);
int  do_answer(string arg);
int  do_report(string arg);

void create()
{
        set_name(BLU "��ɽ����" NOR, ({ "hengshan fujun", "hengshan", "fujun" }));
        set("long", "�����Ǻ�ɽ������\n");
        set("title", HIW "����" NOR);
        set("gender", "����");
        set("age", 50);
        set("str", 91);
        set("int", 39);
        set("con", 50);
        set("dex", 62);
        
        set("max_qi", 10000000);
        set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
        set("max_neili", 12000000);
        set("neili", 12000000);
        set("jiali", 55000);
        set("combat_exp", 2000000000);
        set("score", 1200000);

        set_skill("force", 2700);
        set_skill("parry", 2700);
        set_skill("dodge", 2700);
        set_skill("sword", 2700);
        set_skill("unarmed", 2700);
        set_skill("pixie-jian", 2700);        
        set_skill("literate", 2700);
        set_skill("martial-cognize", 2700);
        set_skill("kuihua-mogong", 2700);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");

        set("inquiry", ([
                "�׼�"  : (: ask_offer : ),
                "offer" : (: ask_offer : ),
        ])); 
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "sword.bian" :),
                (: perform_action, "sword.tian" :),
                (: perform_action, "sword.qiong" :),
                (: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "roar" :),
        }) );
        
        set_temp("apply/attack", 5000); 
        set_temp("apply/armor", 10000); 
        set_temp("apply/damage", 50000); 
        set_temp("apply/unarmed_damage", 50000); 
        set_temp("apply/add_xuruo", 90); 
        set_temp("apply/reduce_xuruo", 100);
        set_temp("apply/add_damage", 100);
        set_temp("apply/reduce_damage", 90); 
        set_temp("apply/reduce_busy", 30); 
        set_temp("apply/add_busy", 10); 
         
        set("auto_perform", 1); 
        // set("bonus", 100000); 

        setup();

        carry_object("/clone/weapon/sword")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_report", "report");
}

int ask_offer()
{
        object me, ob;

        me = this_player();
        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !objectp( ob = present("contract", me) ) ||
            query("owner", ob) != query("id", me)){
                tell_object(me, BLU "��ɽ����˵�������㻹û��ȥ��ȡ������(contract)���Ҳ����������׼����󡣡�\n" NOR);
                return 1;
        }
        
        message_vision(CYN "$N" CYN "�ȵ�������������������������������һ������ɡ���\n"
                       CYN "$N" CYN "Ŀ������������������������������������гɣ����Ҵ���һ�ܣ�����ʤ�ˣ���������׼������׼�����\n" NOR, 
                       this_object(), me); 
                       
        tell_object(me, BLU "��ɽ������Ҫ�����д裬���Ƿ�ͬ��(answer yes/no)��\n" NOR);
        add_action("do_answer", "answer"); 
                       
        return 1; 
} 

int do_answer(string arg)
{
        object ob, me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( arg == "yes" ) { 
                message_vision(BLU "$N" BLU "��Ц�������úúã�����ҵĻ���ʹʹ������һ������\n" NOR, 
                               this_object(), me);
                ob = new(__DIR__"fujun4-shadow");
                ob->move(environment(me)); 
                set_temp("shadow/to_kill", 1, me);
        } else if( arg == "no" ) { 
                message_vision(BLU "$N" BLU "��ŭ����û���õĶ�������\n" NOR,
                               this_object(), me); 
                remove_call_out("destroy");
                call_out("destroy", 1);
        } else 
                return notify_fail("��Ҫ�ش�ʲô��\n"); 
                
        return 1; 
}

int do_report(string arg)
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( query("worship", ob) != query("id", me) )
                return 0;

        if( !query_temp("shadow/to_kill", me) )
                return notify_fail(BLU "��ɽ������ü����������Ҫ��ʲô����\n" NOR);

        if( !query_temp("shadow/killed", me) )
                return notify_fail(BLU "��ɽ������ü�������㻹û��սʤ�ҵĻ���ѽ����\n" NOR);

        message_vision( BLU "$N" BLU "Ц��������Ȼ���г��⣬����������������Ե�ˣ���\n"
                        BLU "$N" BLU "�ֵ������������������֮����������׼�(offer)һ�ű������ܡ���\n" NOR,
                        ob, me);
        delete_temp("shadow", me);
        set_temp("can_offer",query("id",  ob), me);
        add_action("do_offer", "offer");
        return 1;
}

void do_broadcast(int index)
{
        if( !environment() )
                return;

        switch (index)
        {
        case(0):
                tell_room(environment(),
                        BLU "��ɽ������ͷ������������ã��������ص��������ϡ���\n" NOR);
                break;
        case(1):
                tell_room(environment(),
                        BLU "ֻ����ɽ�������дʣ�էʱɽ��Ҷ����Ƽ������â��ֻ��һ�ڰ�ƮȻ���£������ķ��ı�һӦ��ȫ��\n" NOR);
                break;
        case(2):
                tell_room(environment(),
                        BLU "��ɽ������ʻ�����ֻ��˿˿�Ϲ������������ϣ�Ƭ�̼��ɡ�\n" NOR);
                break;
        case(3):
                tell_room(environment(),
                        BLU "��ɽ������������������ˡ��������������ˣ�С�Ѷ�ౣ�ء���\n" NOR);
                break;
        default:
                tell_room(environment(),
                        BLU "��ɽ��������һ��������ʧ��ת˲����Ʈ�����١�\n�ڰ�����һ��������ʧ��ת˲����Ʈ�����١�\n" NOR);

                remove_call_out("destroy");
                destruct(this_object());
                return;
        }
        call_out("do_broadcast", 1, ++index);
}

int do_offer(string arg)
{
        object me, ob, weapon;
        string skill, msg;
        string *rec;
        int level;

        me = this_player();

        if( query("worship", this_object()) != query("id", me) )
                return 0;
                
        if( !arg || sscanf(arg, "%s %d", skill, level) != 2 )
                return notify_fail("��ʽ��offer skill level\n");

        if( !objectp( ob = present("contract", me) ) ||
                query("owner", ob) != query("id", me) )
                return notify_fail(BLU "��ɽ����˵�������㻹û��ȥ��ȡ������(contract)���Ҳ����������׼����󡣡�\n" NOR);

        if( query("offer_hengshan", ob) )
                return notify_fail(BLU "��ɽ����˵���������Ѿ��ں�ɽ�׼����ˣ��Ͳ��������׼��ɡ���\n" NOR);
                
        if( !query_temp("can_offer", me) || 
                query_temp("can_offer", me) != query("id", this_object()) )
                return notify_fail(BLU "��ɽ������ü�������㻹����ȥ����ҵ����������׼��ɡ���\n" NOR);

        if( me->query_skillo(skill, 1) < 2000 || level < 2000 )
                return notify_fail(BLU "��ɽ������ü���������С�����㻹���ûؼ��Լ���ɡ���\n" NOR);

        if( me->query_skillo(skill, 1) < level )
                return notify_fail(BLU "��ɽ������ü�����������ż���û����ô�ߵĵȼ�����\n" NOR);
        
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(BLU "��ɽ������ü���������Ȱ���ı���װ������˵����\n" NOR);
                    
        if( me->query_skill_mapped(query("skill_type", weapon)) != skill )
                return notify_fail(BLU "��ɽ������ü�������㻹���Ȱ�������ܼ��������������ϰɡ���\n" NOR);

        me->add_skill(skill, -level); 
        delete_temp("can_offer", me);
        set("offer/"+skill, level, me);
        
        message_vision( HIR "$N" HIR "��һ��˼��������Ȼ��ˣ�Ϊ�Գ��⣬�Ҿ����׼�" + to_chinese(skill) + level + "������\n" NOR, me );
        tell_object(me, BLU "��ɽ�������һ�ͣ����Ȼ�����Լ���������ʲô��\n" NOR);                  
        msg = HIW + NATURE_D->game_time() + "��" + me->query_idname() + HIW "�ں�ɽ�׼�" + to_chinese(skill) + level + "����\n";
        
        rec=query("offer", ob);
        if( ! rec ) rec = ({});
        rec += ({ msg });
        set("offer", rec, ob);
        set("offer_hengshan", 1, ob);
        
        do_broadcast(0);
        return 1;
}

void destroy()
{
        message_vision( BLU "$N����һ��������ʧ��ת˲����Ʈ�����١�\n" NOR,
                        this_object() );
        destruct(this_object());
        return;
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 900);
}

varargs void die(object killer)
{
        object me = this_object();

        me->full_self();
        return;
}

void unconcious()
{
        object me = this_object();

        me->full_self();
        return;
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
