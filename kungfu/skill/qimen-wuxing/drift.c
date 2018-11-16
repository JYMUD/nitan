// drift_sense.c
#include <ansi.h>
//inherit SSERVER;

int conjure(object me, object target)
{
        object ob;
        int i;

        if ( !query("reborn/times", me) ) return notify_fail("�㻹û���������Ŷݼס�\n");

        if ( !wizardp(me) && me->query_family() != "�һ���" && member_array("�һ���", query("reborn/fams", me)) == -1 )
                return notify_fail("ֻ���һ�������Ҳ����������Ŷݼס�\n");

        if ( me->is_fighting() ) return notify_fail("ս������û��ʱ���,�Ǻǣ�\n");
          
        if ( !query("outdoors", environment(me)) ) return notify_fail("�ԣ��ԣ��ԣ�����ĵذ壬�ƺ���ӲӴ��\n");

        ob = first_inventory(me);
        while ( ob )
        {
                if (ob->is_character() && !ob->is_corpse() )
                        return notify_fail(ob->name()+"���ܺ���һ���궴��\n");
                ob = next_inventory(ob);
        }
        if ( query("jing", me) < 30 ) return notify_fail("��ľ���������\n");
        if ( target ) return notify_fail("���Ŷ���ֻ���Լ�ʹ�ã�\n");

        if ( virtualp(environment(me)) ) return notify_fail("�����޷�ʹ����ͨ!\n");
        write("��Ҫ�굽��һ������ߣ�");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob, env;
        mapping exits;
        int i;
        
        if ( !name || name=="" ) 
        {
                write("��ֹʩ����\n");
                return;
        }
        ob = find_player(name);
        if ( !ob || !me->visible(ob) || wizardp(ob) ) ob = find_living(name);
        if ( !ob || !me->visible(ob) || !living(ob) || wizardp(ob) ) 
        {
                write("���޷����ܵ�����˵ľ��� ....\n");
                return;
        }
        if ( !objectp(env=environment(ob)) )
        {
                write("���޷����ܵ�����˵ľ��� ....\n");
                return;
        }
        if ( random(query("jing",me))<30 )
        {
                write("���޷��о����Է��Ĵ���\n");
                return;
        }
        /*
        if ( query("quest/quest_type",me)=="ɱ"
                && (string)query("quest/quest",me)==ob->short()
                && query("quest/task_time",me)<time() )
        {
                write("���޷����ܵ�����˵ľ��� ....\n");
                return;
        }
        */
        if ( me->is_fighting() ) 
        {
                write("ս������û��ʱ���,�Ǻǣ�\n");
                return;
        } 

        me->receive_damage("jing", 30);
        if ( query("jingli",ob) > random(query("jingli",me)) 
                || !random(3)
                || time() - query_temp("do_flee",me) < 2 ) 
        {
                message_vision( HIY "$N�ɿ���ڵ��ϰ��˸��������˽�ȥ ....\n" NOR, me);
                write("���˼��������ڵ������ʯͷ���ۣ�û�ţ�\n");
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
                return;
        }
        set_temp("do_flee",time(),me);
        if ( !environment(ob) || query("no_magic",environment(ob)) 
                || query("no_fight", environment(ob)) 
                || random(me->query_skill("qimen-wuxing",1)) < 30 ) 
        {
                write("����ָ��ĥ���ˣ����ڳ������󶴣�MY GOD����ô��ѽ��\n");
                message( "vision",HIY+me->name()+"ʹ��������������˼��£������ġ�\n" NOR, environment(me),({me}));
                return;
        }
        exits=query("exits", environment(ob));
        if (!mapp(exits) || !sizeof(exits) )
        {
                write("���ڵ�һ��ʯǽ�����ò����˻�����\n");
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
                return;
        }
        if ( domain_file(base_name(environment(ob)))=="shaolin" 
                || domain_file(base_name(environment(ob)))=="newbie" 
                || domain_file(base_name(environment(ob)))=="mingjiao" 
                || domain_file(base_name(environment(ob)))=="shenlong" 
                || domain_file(base_name(environment(ob)))=="wizard" 
                || domain_file(base_name(environment(ob)))=="death" ){
                write("����������أ��ǵ������ܼ���\n");
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));           
                return;         
        }               

        if ( domain_file(base_name(environment(ob)))=="taohua" || domain_file(base_name(environment(ob)))=="binghuo"){
                write("��ϲ�㣬���ڵ���Ȫˮ����\n");
                message( "vision",HIY+me->name()+"�ӿ����³�����ˮ��У�����ѽ��\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="xiakedao" ){
                write("��ϲ�㣬���ڵ���é������\n");
                message( "vision",HIY+me->name()+"�ӿ����³����ڴ���У��ó�ѽ���ó�ѽ��\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="gaochang" ) {
                write("����̫ңԶ�ˡ�\n");
                message( 
                        "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
                return;
        }

        if ( sscanf(base_name(environment(ob)), "/data/%*s") ){
                write(HIM "�������˼ҵ�˽լ�����ȥ͵������?\n" NOR);
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
        }

        if ( !environment(ob) || wizardp(ob) ){
                 message_vision( HIY "$N�ɿ���ڵ��ϰ��˸��������˽�ȥ ....\n" NOR, me);
                write("���ڵص����˰��죬����"+ob->name()+"�ƺ������� ....\n");
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
                return;
        }
        
        /*
        if( userp(ob) )
        {
                message_vision( HIY "$N�ɿ���ڵ��ϰ��˸��������˽�ȥ ....\n" NOR, me);
                write("���ڵص����˰��죬�����ƺ����ű߼� ....\n");
                message( "vision",HIY+me->name()+"һ�������ܻ�����ͷ�����شӶ��������˻�����\n" NOR, environment(me),({me}));
                return;
        }
        */
        message_vision( HIY "$N�ɿ���ڵ��ϰ��˸��������˽�ȥ ....\n" NOR, me);
        message( "vision", HIY "\n�ܿ죬�����ַ���������" + me->name() + "�����ˣ�\n\n" NOR, environment(me), ({ me }) );


        if( file_size(file_name(environment(ob))+".c")<=0 )
        {
                write(HIY"���ǣ��ܿ���㷢�������ƺ��������ڣ������ֻ�ͷ���������˻�����\n"NOR);        
                return;
        } else 
                me->move(environment(ob));
        message( "vision", HIY "\nһ����ӰͻȻ�ӵ���ð�˳����������������Ļң�\n\n" NOR,
                environment(ob), ({ me }) );
        
        /*
        if( me->query_skill("taoism",1) > me->query_skill("qimen-wuxing", 1) )
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 0);
        else    
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 1);
        */
}


