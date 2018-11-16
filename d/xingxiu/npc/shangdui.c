// Room: /d/xingxiu/npc/shangdui.c
// Last Modified by winder on Apr. 25 2001

#include <ansi.h>
inherit ITEM;
#include "dest.h";

void create()
{
        set_name("�����̶�", ({ "shangdui"}));
        set("unit", "ֻ");
        set("location", 1);
        set_weight(900000);
        set("long", "
һֻԶ�������������̶ӣ����ձ��϶����˻��������
��������һЩ�����������ǱȽ���Ҫ�Ķ���������\n");
        set("no_get", 1);
        set("no_drop", 1);
        seteuid(getuid());
}

void init()
{
        if (!query("inited"))
        call_out("destroying", 20, this_object());  
        add_action("do_rob", ({"qiang"}));
}

int do_rob()
{
        object me, ob;   
        string arg ;
        int stage, i;
        me = this_player();
        ob = this_object();
        stage = 0;
        i = sizeof(dest);
        arg = query("arg");

        if(!living(me)) return 0;
        if( !query_temp("xx_job2", me) || !query_temp("rob_start", me) )
                return notify_fail("������������ҹ��컯��֮�������̶ӣ����±�����������\n");
        if(objectp(present("hubiao biaoshi", environment(me))))
                return notify_fail("������ʦ�����书�������㻹���ȴ�����ǰ�����˵�ɣ�\n");  
        message_vision(HIY "$N����$n���һ��������"+me->name()+"�ڴˣ��������ǵ�Ǯ������\n"NOR, me, ob);
        set_temp("xx_rob", 1, me);
        if( !query("going", ob) )
        {
                while (i--) if (arg == dest[i]["name"]) break;
                remove_call_out("go_stage");
                set("f", 7*(query_temp("j", me)+1), ob);
                call_out("go_stage",1,ob,stage,i,sizeof(dest[i]["context"]),me);
                set("going", 1, ob);
        }
        remove_call_out("make_bs");
        call_out("make_bs", 1, me, ob); 
        return 1;     
}
void make_bs(object me, object ob)
{
        object obj, obj1;
        int j;
        j=query_temp("j", me);
//
        if(j>0)
        {
                obj = new("/d/xingxiu/npc/biaoshi");
                obj->move(environment(me));
                obj->do_copy(me);
                obj1 = new("/d/xingxiu/npc/biaoshi");
                obj1->move(environment(me));
                obj1->do_copy(me);
                addn_temp("j", -1, me);
                return;      
        }
        else
//
        {
                message_vision(HIW"$N���Ѿ����˱�������$n����в�£�ֻ��ͣ���������������Ĳ���ԹԵ����ϣ�\n"NOR, ob, me);    
                obj = new("/d/xingxiu/obj/red");
                obj->move(me);
                set("owner",query("id",  me), obj);
                addn("combat_exp", 150, me);
                addn("shen", -(query("combat_exp", me)/20), me);
                delete_temp("rob_start", me);
                delete_temp("xx_rob", me);
                delete_temp("xx_job2", me);
                delete_temp("j", me);
                message_vision("$N�������գ�ת������Сɽ��Ͳ����ˡ�\n", ob);
                destruct(ob);
        }        
}

void go_stage(object me, int stage, int i, int size, object player)
{
        object where;
        int f=query("f", me);
        if(stage < size)
        {
                message_vision(HIY"$N�Ҵ�ææ������פ���Ĺؿڷ�����ȥ��\n"NOR, me);
                me->move(dest[i]["context"][stage]);
                message_vision(HIY"$N�Ҵ�ææ�ر��˹�����\n"NOR, me);
                where = environment(me); 
                tell_object(player,HIM+query("name", me)+"����������"+query("short", where)+"һ����\n"NOR);
                call_out("go_stage", f, me, ++stage, i, size, player);
        }
        else
        {    
                tell_object(player,HIM+query("name", me)+"�ɹ����ӽ��˳���\n"NOR);
                delete_temp("xx_rob", player);
                delete_temp("xx_job2", player);
                delete_temp("rob_start", player);
                delete_temp("j", player);
                delete_temp("biaoshi", player);
                message_vision(MAG"\n$Nת�����У��ڹٱ��Ļ������뿪�ˡ�\n"NOR,me);      
                destruct(me);
        }
}
void destroying(object me)
{
        if( !query("going", me) )
        {
                message_vision("$N�������գ�ת������Сɽ��Ͳ����ˡ�\n", me);        
                destruct(me);
                return;
        }
        set("inited",1);
  call_out("destroying2", 450, me);
}

void destroying2(object me)
{
        message_vision("$N�������գ�ת������Сɽ��Ͳ����ˡ�\n", me);        
        destruct(me);
        return;
}
