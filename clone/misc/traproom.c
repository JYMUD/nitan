// Room: /clone/room/traproom.c
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

inherit ROOM;

void falldown(object);
void flydown(object);
int do_jump(string);
int do_climb(string);
int do_push(string);
int do_fill();
void maintaining(object, int);
int trap_power(object);

void create()
{
        set("short",HIR "����" NOR);
        set("long", HIR @LONG
����һ�ڲ�֪��˭�ھ�����塣����������ɣ�����������ȥ��ֻ
�ܼ����������һƬ��ա�������Χ����������㣬��ͣ��������ˮ��
�ƺ��ո��ں�û��á�
LONG NOR
);      
        set("invalid_startroom",1);
        set("trap_room",1);
        setup();
        call_out("maintaining", 30, this_object(), 0);
}

void init()
{
        int depth, power, reward;
        object me = this_player();
        object roomtrap = this_object();
        object owner=query("owner", roomtrap);

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( query_temp("is_riding", me))delete_temp("is_riding", me);
        remove_call_out("maintaining");
        call_out("maintaining", 30, roomtrap, 0);

        if( depth>power && owner != me && query("limit", roomtrap) && 
                !query_temp("trap/" + file_name(roomtrap), me) )
        {
                me->set_temp("trap/"+file_name(roomtrap));
                call_out("falldown", 1, me);

                if( objectp(owner) && userp(me) &&
                        environment(owner) == roomtrap &&
                        query("limit", roomtrap) >= 1 )
                {
                        reward=query("combat_exp", me)/300;
                        if( reward >= 40 ) reward = 40;
                        addn("combat_exp", reward, owner);

                        reward=query("shen", me)/300;
                        if( reward >= 10 ) reward = 10;
                        addn("shen", -reward, owner);
                }
                if( query("limit", roomtrap) >= 1)addn("limit", -1, roomtrap);
                if( depth / 5 > power ) me->unconcious();
        }
        else call_out("flydown", 1, me);
// tell_object(me, HIY "power = " + power + "\n" NOR);

        add_action("do_jump", "tiao");
        add_action("do_climb", "pa");
        add_action("do_push", "tui");
        add_action("do_fill", "tian");

        add_action("do_jump", "jump");
        add_action("do_climb", "climb");
        add_action("do_push", "push");
        add_action("do_fill", "fill");
}

void falldown(object me)
{
        object rum_ob;
        object owner=query("owner", this_object());

// To noisy. 
        if( !objectp(rum_ob = find_object("/d/city/npc/aqingsao")) )
                rum_ob = load_object("/d/city/npc/aqingsao");
        CHANNEL_D->do_channel(rum_ob, "rumor",
                sprintf("%s�����������ˡ�", me->name(1)));
//
        message("vision", HIY "ֻ���۵�һ���������ϱߵ���һ�ź�Ӱ����\n" NOR, environment(me), me);
        tell_object(me, HIR "��ֻ���ý���һ�飬���һ����ˤ����ȥ��\n" NOR);
        me->start_busy(3+random(5));
        if( present(owner, environment(me)))
        {
                owner->start_busy(3+random(5));
        }
}

void flydown(object me)
{       
        if( random(5) == 0 )
        message("vision", "ֻ����Ӱһ����" + me->name() + "�Ѿ�վ�������ǰ��\n", environment(me), me);
}

int valid_leave(object me, string dir)
{
        int power, depth;
        mapping exit;
        object roomtrap = this_object();

        if( query("owner", roomtrap) == me)return ::valid_leave(me,dir);
        if( query("race", me) == "����")return ::valid_leave(me,dir);
//      if( !roomtrap->query("limit") )         return ::valid_leave(me, dir);

        depth=query("depth", roomtrap);
        power = trap_power(me);
        if(me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( depth / 3 > power )
        {
                return notify_fail("����̫���ˣ�����ô��Ҳ������ȥ�������������������ƣ��ԣգɣ���ȥ�ˡ�\n");
        }
        else
                if( depth / 2 > power)
                {
                        return notify_fail("��������������ܲ��������У�����ȥ��\n");
                }
                else
                        if( depth > power )
                        {
                                return notify_fail("���忴��ͦ��ģ���������ܲ���ʹ�������ԣɣ��ϣ���ȥ��\n");
                        }
                        
                        else if( !mapp(exit=query("exits", roomtrap)) || !stringp(exit[dir]) )
       {
         return notify_fail("�������û��·��\n");
       }
                        else
                        {
                                me->receive_damage("qi", depth/20, "��������������");
                                message_vision("$N����ƮƮ����̬����ش������Ϸ���Ծ������\n", me);
                                return ::valid_leave(me, dir);
                        }
}

int do_jump(string arg)
{
        int depth, power;
        object me, roomtrap, roomto;

        me = this_player();
        roomtrap = this_object();

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("��Ҫ���ĸ�������Խ��\n");
        if( !(roomto=find_object(query("exits/"+arg, roomtrap))) )
                roomto=load_object(query("exits/"+arg, roomtrap));
        if( depth < power )
                return notify_fail("����ı��죬�õ�����ô������\n");
        if(me->is_busy())
                return notify_fail("��������æ���ء�\n");
        if( depth>power && depth/2<power && query("qi", me) >= depth/10 )
        {
                me->receive_damage("qi", depth/10, "��������������");
                if( random(me->query_kar() + me->query_dex()) >= 15 )
                {
                        me->move(roomto);
                        message_vision("$Nչ���Ṧ����һ����ವش�������Ծ�˳�ȥ��\n", me);
                        return 1;
                }
                else
                {
                        message_vision("$Nʹ���͵�һ���������һ�����Ӳ������������ص�ˤ��������\n", me);
                        return 1;
                }
        }
        else return notify_fail("�������������\n");

        if( depth / 2 > power && depth / 3 < power )
        return notify_fail("�������ǲ��ɵ��ˣ������ܲ�������ȥ��\n");
        return notify_fail("����̫���ˣ�����һ���ú����������ȥ�ˡ�\n");
}

int do_climb(string arg)
{
        int depth, power;
        object me, roomtrap, roomto;

        me = this_player();
        roomtrap = this_object();

        depth=query("depth", roomtrap);
        power = trap_power(me);

        if( !arg || !query("exits/"+arg, environment(me)) )
                return notify_fail("��Ҫ���ĸ���������ȥ��\n");
        if( !(roomto=find_object(query("exits/"+arg, roomtrap))) )
                roomto=load_object(query("exits/"+arg, roomtrap));
        if( depth < power )
                return notify_fail("����ı��죬�õ�����ô������\n");
        if( depth > power && depth / 2 < power )
                return notify_fail("���岢�������ʩչ�Ṧ�������ܲ�������ȥ��\n");
        if(me->is_busy()) return notify_fail("��������æ���ء�\n");
        if( depth/2>power && depth/3<power && query("qi", me) >= depth/5 )
        {
                me->receive_damage("qi", depth/5, "������������");
                if( random(me->query_kar() + me->query_str()) >= 15 )
                {
                        me->move(roomto);
                        message_vision("$Nץס������ϵĲݸ�����֦���ֽŲ��õ��������˳�ȥ��\n", me);
                        return 1;
                }
                else
                {
                        message_vision("$N�����������������ţ���Ȼƺ��һ�����Ǳ�������ˤ��������\n", me);
                        return 1;
                }
        }
        else return notify_fail("�������������\n");
        return notify_fail("����̫���ˣ�����һ���ú����������ȥ�ˡ�\n");
}

int do_push(string arg)
{
        object me, ob, roomtrap, roomto;
        int depth, power_me, power_ob;
        string who, where;

        me = this_player();
        roomtrap = this_object();

        if( !arg || sscanf(arg, "%s %s", who, where)!=2 ) 
                return notify_fail("ָ���ʽ��tui <����> <����>\n");
        if( !objectp(ob = present(who, environment(me))) || !living(ob))
                return notify_fail("��Ҫ��˭��ȥ��\n");
        if( query("id", me) == who )
                return notify_fail("�Լ����Լ���ȥ�������аɡ�\n");

        depth=query("depth", roomtrap);
        power_me = trap_power(me);
        power_ob = trap_power(ob);

        if( !query("exits/"+where, environment(me)) )
                return notify_fail("��Ҫ���ĸ�������"+ob->name()+"��ȥ��\n");
        if( !(roomto=find_object(query("exits/"+where, roomtrap))) )
                roomto=load_object(query("exits/"+where, roomtrap));
        if( depth>power_me || query("qi", me)<depth/5 )
                return notify_fail("��û���������"+ob->name()+"��ȥ�ɣ�\n");
        if(me->is_busy())
                return notify_fail("��������æ���ء�\n");
        me->receive_damage("qi", depth/5, "���˳�����ʱ������");
        if( random(me->query_str() + ob->query_kar()) >= 15 )
        {
                ob->move(roomto);
                me->move(roomto);
                message_vision("$N��������$n������������һ�¾Ͱ�$n�ͳ������塣����һ�����Լ�ҲԾ�˳�ȥ��\n", me, ob);
                return 1;
        }
        else
        {
                message_vision("$N��ס$n���$n�ͳ����壬���$N��һ�����˶�ˤ���ڵء�\n", me, ob);
                return 1;
        }
        return notify_fail("����̫���ˣ�����������취��\n");
}

int do_fill()
{
        object me, roomtrap, roomto, roomfrom, *inv;
        int depth, power_me, i;

        me = this_player();
        roomtrap = this_object();
        roomfrom=query("roomfrom", roomtrap);
        roomto=query("roomto", roomtrap);

        depth=query("depth", roomtrap);
        power_me = trap_power(me);

        if( (depth*2>power_me || query("qi", me)<depth/3) && 
                me != query("owner", roomtrap) )
                return notify_fail("�������̫���ˣ�����ס�������������ɡ�\n");
        me->receive_damage("qi", depth/3, "������ʱ������");
        message_vision("$N��ͷ�󺹵����ൣˮ������������ʵʵ������������\n\n", me);
        set("exits/"+query("from", roomtrap), file_name(roomto), roomfrom);
        set("exits/"+query("to", roomtrap), file_name(roomfrom), roomto);
        delete("exits/jump"+query("from", roomtrap), roomfrom);
        delete("exits/jump"+query("to", roomtrap), roomto);
        
        inv = all_inventory(environment(me));

        if( sizeof(inv) >= 1 )
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        if( !living(inv[i]) || inv[i] == me ) continue;
                        else inv[i]->move(roomto);
                }
        }

        me->move(roomto);
        destruct(roomtrap);

        return 1;
}

int trap_power(object me)
{
        return  me->query_skill("dodge")*5
                + me->query_dex()*4
                + me->query_int()*3
                + me->query_kar()*2
                +query("qi", me);
}

void maintaining(object roomtrap, int count)
{
        object owner, roomfrom, roomto;
  int i;
  object *inv;
        roomfrom=query("roomfrom", roomtrap);
        roomto=query("roomto", roomtrap);

        if( objectp(owner=query("owner", roomtrap)) && count<10 )
        { 
/*                if( environment(owner) == roomtrap ||
                        environment(owner) == roomfrom ||
                        environment(owner) == roomto )
                        count = 0;
                else */count++;
                call_out("maintaining", 120, roomtrap, count);
        }
        else
        {
                set("exits/"+query("from", roomtrap), file_name(roomto), roomfrom);
                set("exits/"+query("to", roomtrap), file_name(roomfrom), roomto);
                delete("exits/jump"+query("from", roomtrap), roomfrom);
                delete("exits/jump"+query("to", roomtrap), roomto);
                inv=all_inventory(roomtrap);
    tell_room(roomtrap,"��ʱ���߹���һ�����꺺�ӣ���������������棬�����������Ӱ�������������\n�������һ���������˵���������ʵʵ������������\n");
                for (i=0;i<sizeof(inv);i++)
                        if (!living(inv[i])) continue;
                        else inv[i]->move(roomfrom);
                destruct(roomtrap);
        }
}
