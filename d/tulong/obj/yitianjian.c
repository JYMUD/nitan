#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE; 
inherit F_NOCLONE; 
inherit SWORD;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "���콣" NOR, ({ "yitian sword", "jian", "sword" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "�������������������������Ƶ����콣��\n�ഫ�õ����Կ�(duikan)���Եõ������������ؼ���\n" NOR);
                set("value", 100000);
                set("no_sell", "����������������\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1); 
                set("replica_ob","/d/city/npc/obj/changjian"); 
                set("enchase/flute", 9);    
                set("material", "steel");
                set("wield_msg", HIW "ֻ����ಡ���һ���ƿ����죬�ų����µ�һ��������콣�ѱ�$N�������С�\n" NOR);
                set("unwield_msg", HIW "$N�����콣������䣬����ֽ����ų���â��\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));

        init_sword(5000);
        setup();
        start_borrowing();
        check_clone(); 
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_dex() * 100;
        addn("neili", -dam*10, victim);

        if( query("neili", victim)<0 )
        set("neili", 0, victim);

        return HIW "���콣Я���쬴̹Ƿ�����ֱֱ����$n��$nֻ�е�ȫ���������һ˿˿���Ž���ӿ����\n" NOR;
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/yitian/obj/shelf")
        {
                call_out("return_to_back",3600+random(3600));
                return ;
        }
        
        if (playerp(me)) 
        { 
                if (me->is_fighting()) 
                { 
                        call_out("return_to_back", 1); 
                        return; 
                } 
                //�Ƿ�Ӧ��ִ��unwield
                tell_object(me, HIR"\nһ����Ӱ������ǰһ��������" +
                            "����л���Ϸ�ȡ��" NOR + name() + HIR
                            "���ʹ�л�������Ǻ�����ڣ���\n\n"NOR);
        } else 
        { 
                message("vision", "��Ȼһ�������˹���������"+name()+"��̾�˿�����ҡҡͷ���ˡ�\n", me); 
        } 

        move("/clone/misc/void");
        call_out("real_back", random(2));
}

void real_back()
{
        object room, shelf;

        room = get_object("/d/tulong/yitian/was_lou4");
        shelf = present("shelf", room);
        move(shelf);
        start_borrowing();
} 
