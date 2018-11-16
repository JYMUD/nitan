#include <weapon.h>
#include <ansi.h>
inherit BLADE;
inherit F_UNIQUE;
inherit F_NOCLONE;

void return_to_back();
void start_borrowing() 
{
        remove_call_out("return_to_back"); 
        call_out("return_to_back", 3600+random(7200)); 
} 

void create()
{
        set_name(CYN "������" NOR, ({ "tulong blade" , "blade" ,"dao", "tulong" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����Ǻų���������������������ĳ������ĵ���������һ�ٶ��֮�ء�\n�ഫ���в��п����Ĵ����ܡ�\n" NOR);
                set("value", 100000);
                set("no_sell", "����������������\n");
                set("no_store", 1);
                set("rigidity",8000);   
                set("unique", 1);
                set("material", "steel");
                set("wield_msg", HIY "$Nһ����Ц���ӱ������Ǳ��ųơ�"NOR+HIR"��������"NOR+HIY"�������������߸߾���\n" NOR);
                set("unwield_msg", HIY "$N����һЦ��������������ر���\n"NOR);
        }
        set("enchase/apply_prop", ([
                "add_busy"  : 10,
                "add_weak"  : 40,
                "avoid_locked" : 40,
                "add_damage" : 50,
                "add_skill"  : 200,
        ]));
        init_blade(5000);
        setup();
        start_borrowing();
        check_clone();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = me->query_str()*100;
        victim->receive_damage("jing",dam * 2);
        return HIM "�������д��Ŵ̶����ƿ�������һ�������磬$nֻ�е��������ң���ǿ�����ֵ���\n" NOR;
}

void init()
{
        add_action("do_open","duikan");
}

int do_open(string arg, object me)
{
        object pai,ob;
        if(arg != "yitian sword" || !ob = present("yitian sword", environment(this_object()))) 
        {
                return notify_fail("��Ҫ��ʲô��\n");
        }
        else if( query("jiali", this_player()) <= 160 )
                return notify_fail(WHT "\n��������������׼���콣�����Ŀ�����ȥ��"NOR+HIR"\n\nֻ�����ꡱ��һ�����죬�ɽ���������ǡ�\n" NOR);
        {
                pai = new("/d/tulong/obj/duan1");
                pai->move(this_player());
                pai = new("/d/tulong/obj/duan2");
                pai->move(this_player());
                pai = new("/d/tulong/obj/zhenjing");
                pai->move(this_player());
                pai = new("/d/tulong/obj/miji");
                pai->move(this_player());
                pai = new("/d/tulong/obj/yishu");
                pai->move(this_player());
                message_vision(WHT "\n$N������������׼���콣�����Ŀ�����ȥ��\n\n"NOR+HIW"ֻ��һ�����죬$N�ֱ�һ�������������콣�Ѿ����ˡ��㷢�ֵ����о�Ȼ�в��ż����\n"NOR,this_player());
                destruct (ob);
                destruct(this_object());
                return 1;
        }
}

void return_to_back() 
{ 
        object me; 

        me = environment(); 
        if (! objectp(me)) 
                return; 

        while (objectp(environment(me)) && ! playerp(me)) 
                me = environment(me); 

        if(base_name(me)=="/d/tulong/tulong/obj/ding")
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
        object room, ding;

        room = get_object("/d/binghuo/wangpangu2");
        ding = present("ding", room);
        move(ding);
        start_borrowing();
} 
