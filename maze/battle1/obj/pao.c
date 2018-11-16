// This program is a part of NT MudLIB
//
// sdong, 3/18/2000

#include <ansi.h>
#include <armor.h>
#include <room.h>
inherit F_SSERVER;
inherit ITEM;
#define ORIGINAL "/maze/battle1/room_28.c"
int explode(object me, object ob);
int do_fire(string arg);
int do_aim(string arg);
string look_room(object me, object env);
int do_load(string arg);

mapping default_dirs = ([
        "north":        "��",
        "south":        "��",
        "east":                "��",
        "west":                "��",
        "northup":        "����",
        "southup":        "�ϱ�",
        "eastup":        "����",
        "westup":        "����",
        "northdown":        "����",
        "southdown":        "�ϱ�",
        "eastdown":        "����",
        "westdown":        "����",
        "northeast":        "����",
        "northwest":        "����",
        "southeast":        "����",
        "southwest":        "����",
        "up":                "��",
        "down":                "��",
        "out":                "��",
        "enter":        "��",
        "in":                "��",
        "left":                "��",
        "right":        "��",
]);

string day_event(){return NATURE_D->outdoor_room_event();}

void create()
{
        set_name(HIY"��ͭ��"NOR, ({"pao","qingtong pao","bombgun"}));
        set_weight(1500000);
        set("value",150000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"һ����ͭ����Ĵ��ڣ��޴���ڹܰ�Ȼͦ�գ��˵���������档
�����Խ�ɽׯ�����ռ��������ű�����û�뵽�����ڶ��У�ֻ��
��֪���ò����á�\n\n");

                set("unit", "��");
                set("material", "bronze");
        }
        setup();
}

void init()
{
        add_action( "do_load", "load" );
        add_action( "do_aim", "aim" );
        add_action( "do_fire", "shoot" );
}

int do_load(string arg)
{
        object ob = this_object(), huoyao, dantou;
        object me = this_player();
        int exp_time;

        if ( !arg || (arg!="powder" && arg!="huo yao" && arg!="dan tou" ) )
           return notify_fail( "����Ҫ����ʲô��\n");

        if( me->is_busy() ) return notify_fail("�㻹��æ���أ�\n") ;

        if( arg=="powder" || arg =="huo yao" )
        {
                huoyao = present("huo yao");
                if( !huoyao || !objectp(huoyao) )return notify_fail( "����Ҫ����ʲô��\n");

                if( query_temp("yao_loaded") > 2 )return notify_fail("�����Ѿ�װ����ҩ�ˡ�\n");

                if( huoyao && objectp(huoyao) && query("load", huoyao)>0 )
                {
                        message_vision("$N����Ͳ�����һЩ��ҩ��\n",me);
                        set("load",query("load",  huoyao)-1, huoyao);
                        if( query("load", huoyao) <= 0)destruct(huoyao);
                        addn_temp("yao_loaded",1);
                        me->start_busy(1);
                }
        }
        else if( arg =="dan tou" )
        {
                dantou = present("dan tou");
                if( !dantou || !objectp(dantou) )return notify_fail( "����Ҫ����ʲô��\n");

                if( query_temp("dan_loaded") > 0 )return notify_fail("�����Ѿ�װ�е�ͷ�ˡ�\n");

                message_vision("$N����Ͳ�����һö��ͷ��\n",me);
                destruct(dantou);
                addn_temp("dan_loaded",1);
                me->start_busy(1);
        }

        return 1;
}



string look_room(object me, object env)
{
                  int i;
                  object *inv;
                  mapping exits;
                  string str, *dirs;

                  if( !env ) {
                                         return "������ܻ����ɵ�һƬ��ʲôҲû�С�\n";
                  }
                  str = sprintf( "%s - %s\n    %s%s",
                                         query("short", env),
                                         wizardp(me)? file_name(env): "",
                                         query("long", env),
                                         query("outdoors", env)?NATURE_D->outdoor_room_description():"");

                  if( mapp(exits=query("exits", env))){
                                         dirs = keys(exits);
                                         for(i=0; i<sizeof(dirs); i++)
                        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                                                                  dirs[i] = 0;
                                         dirs -= ({ 0 });
                                         if( sizeof(dirs)==0 )
                                                                str += "    ����û���κ����Եĳ�·��\n";
                                         else if( sizeof(dirs)==1 )
                                                                str += "    ����Ψһ�ĳ����� " + BOLD + dirs[0] + NOR + "��\n";
                else
                        str += sprintf("    �������Եĳ����� " + BOLD + "%s" + NOR + " �� " + BOLD + "%s" + NOR + "��\n",
                                implode(dirs[0..sizeof(dirs)-2], "��"), dirs[sizeof(dirs)-1]);
                  }
//      str += env->door_description();

        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
                                         if( inv[i]==me ) continue;
                                         if( !me->visible(inv[i]) ) continue;
                                         if( objectp(query("rider", inv[i])))continue;
                                         else delete("rider", inv[i]);
                                         if( objectp(query("rided", inv[i]))){
                                                                str += "  " + inv[i]->short() + "����" +
                                                                (query("rided", inv[i]))->name()+"��";
                                         if( stringp(query_temp("exit_blocked", inv[i])) )
                                                                str+="������"+query_temp("exit_blocked", inv[i])+
                                                                "ȥ��·";
                                                                str += "\n";
                                         }
                                         else {
                                                                if( stringp(query_temp("exit_blocked", inv[i])) )
                                                                str+=""+inv[i]->short()+"������"+query_temp("exit_blocked", inv[i] )
                                                                                  +"ȥ��·\n";
                                                                else
                                                                str += "  " + inv[i]->short() + "\n";
                                                                delete("rided", inv[i]);
                                         }
                  }

                  return(str);
}


int do_aim(string arg)
{
        object me = this_player();
        object cur_target, target;
        string str, dest;
        mapping exit;

        if( me->is_busy() ) return notify_fail("�㻹��æ���أ�\n") ;

        cur_target = query_temp("target");

        if( !cur_target ){
                cur_target = find_object(ORIGINAL);
                if( !cur_target )cur_target=load_object(ORIGINAL);
                if (!objectp(cur_target))return notify_fail("�Ҳ���Ŀ�ꡣ\n");
        }

        if( arg=="down" || arg=="up" || arg=="out" || arg=="enter" )return notify_fail("�������û���򵽡�\n");

        if( arg )
        {
                if( !mapp(exit=query("exits", cur_target)) || undefinedp(exit[arg])){
                        return notify_fail("�������û�г�·��\n");
                }

                if( !cur_target->valid_leave(me, arg) ) notify_fail("�������̫Զ�ˡ�\n");

                dest = exit[arg];

                if( !(target = load_object(dest)) )
                        return notify_fail("�޷��ƶ���\n");
        }
        else target = cur_target;

        set_temp("target",target);

        str = look_room(me, target);
        tell_object(me, str+"\n");
        if(arg)
                message_vision(HIW"$N���ڿڻ�����"+default_dirs[arg]+"ת����׼��"+query("short", target)+"��\n"NOR,me);

        me->start_busy(1);

        return 1;
}

int do_fire(string arg)
{
        object ob = this_object();
        object me = this_player();
        int exp_time;

    if( query_temp("fired", ob))return notify_fail("��һ���ŷ��ִ����ѱ���ȼ�ˣ��Ϳ췢���ˣ�\n");
        if( query_temp("dan_loaded", ob) <= 0)return notify_fail("�ڻ�û���ϵ�ͷ�أ�\n");
        if( query_temp("yao_loaded", ob)<3)return notify_fail("�ڻ�ûװ��\��ҩ�أ�\n");

        message_vision("$N��������һ����������$n��������\n", me,ob);
        set_temp("fired", 1, ob);
        set_temp("owner", me, ob);
        call_out("explode", 1 + random(5), me, ob);

        return 1;
}

int explode(object me, object ob)
{
        object *victims, env, owner;
        int i,damage;
        string str;

                delete_temp("fired", ob);
                delete_temp("owner", ob);
                delete_temp("dan_loaded", ob);
                delete_temp("yao_loaded", ob);

        env = query_temp("target");
        if( !env ){
                env = find_object(ORIGINAL);
                if( !env )env=load_object(ORIGINAL);
                if (!objectp(env))return notify_fail("�Ҳ���Ŀ�ꡣ\n");
        }

        message_vision(HIY"ֻ����һ�����춯�صı��죬$N"+HIY"�����ˣ���ͷ����һ�����߷���"+query("short", env)+HIY"������һƬ����������\n"NOR,ob);

        owner = query_temp("owner");

        if( !owner || !objectp(owner) )
        {
                if(me && objectp(me) )
                        owner=me;
                else owner=ob;
        }

        tell_room(env,HIR"ֻ����һ�����춯�صı��죬һ���ڵ���أ�����һ�����̱�ը�ûҷ�����\n"NOR, me);

        if( query("no_fight", env)){
                return 0;
        }

        victims = all_inventory(env);

        for (i=0; i<sizeof(victims); i++) {
                   if (!living(victims[i]) || victims[i]==me ) continue;
                damage= 4000+random(8000);
        victims[i]->receive_damage("qi", damage,  owner);
        victims[i]->receive_wound("qi", random(damage), owner);
        str=COMBAT_D->status_msg(query("qi", victims[i])*100/query("max_qi", victims[i]));

                message_vision(HIR"$N��ը����������\n"NOR,victims[i]);
                message_vision(HIR"��ԶԶ����"+query("name", victims[i])+"��ը����������\n"NOR,ob);
        message_vision("($N"+str+")\n", victims[i]);
                message_vision(HIR"��ԶԶ����("+query("name", victims[i])+str+")\n",ob);
        }

        if( !query("th_buzhen", env))return 1;

        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}
