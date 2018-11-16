// ride.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_ride(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj, env;
        object horse, person;
        string who, s1, s2;
        int i, level, rec_n, max_rec;
        mapping self_flag;
        string *ps;

        if( !arg ) return notify_fail("��Ҫ��ʲô������\n");
        
        env = environment(me);
        // ������������
        sscanf(arg, "%s %s", s1, s2);
        if( s1 == "up" ) // s1 == arg;
        {
                if( !MEMBER_D->is_valid_member(query("id", me)) )
                        return notify_fail("�Բ���ֻ�л�Ա����������������\n");

                if( sscanf(arg, "up %s", who) == 1 )
                {
                        if( !objectp(horse=query_temp("is_riding", me)) )
                                return notify_fail("�������ﶼû�У���ôҪ����������\n");

                        if( !objectp(person = present(who, env)) )
                                return notify_fail("����û������ˣ�\n");

                        if( query_temp("is_riding", person) )
                                return notify_fail("�����Ѿ��������ˡ�\n");

                        if( objectp(query_temp("is_rided_follow", horse)) )
                                return notify_fail("����������Ѿ������ˡ�\n");

                        message_vision(HIW "$N��������ǰ����$n˵������������һ��\n" NOR, me, person);
                        set_temp("ride_up",query("id", me), person);
                        tell_object(person, HIG + me->name() + "��������������ͬ�������� ride ok ��\n" NOR);                  
                        return 1;
                }

                return notify_fail("��Ҫ����˭�����\n");
        }

        // ͬ������������
        if( arg == "ok" )
        {
                if( !stringp(who=query_temp("ride_up", me)) )
                        return notify_fail("û���������������\n");

                if( query_temp("is_riding_follow", me) )
                        return notify_fail("�㻹���������ride down����˵�ɡ�\n");
        
                person = find_player(who);
        
                if( !objectp(person) ) return notify_fail("����û������ˡ�\n");

                if( environment(me) != environment(person) )
                        return notify_fail("����û������ˡ�\n");
                
                if( !objectp(horse=query_temp("is_riding", person)) )
                        return notify_fail(person->name() + "�ƺ�û������ɣ�\n");

                if( query_temp("is_rided_follow", horse) )
                        return notify_fail(person->name() + "��" + horse->name() + NOR "�Ѿ������ڳ����ˡ�\n");

                delete_temp("ride_up", me);
                MAP_D->me_ride(me, horse);
                
                return 1;
                
        }
        
        // follower ǿ��������
        if( arg == "down" )
        {
                if( objectp(horse=query_temp("is_riding_follow", me)) )
                {
                        delete_temp("is_riding_follow", me);
                        delete_temp("is_rided_follow", horse);
                
                        message_vision("$Nһ���� ��" + horse->name() + NOR "����������\n" NOR, me);

                        return 1;
                }
                
                return notify_fail("OK.\n");            
        }

        if (arg == "kick")
        {
                if( objectp(horse=query_temp("is_riding", me)) )
                {                       
                        if( objectp(person=query_temp("is_rided_follow", horse)) )
                                delete_temp("is_riding_follow", person);

                        delete_temp("is_rided_follow", horse);

                        message_vision("$Nǿ��Ҫ�������������\n", me);

                        return 1;               
                }

                return notify_fail("�㲢û�������\n"); 
        }
        
        if( arg == "?" )
        {
                self_flag = query("horse/flags", me);
                if( mapp(self_flag) && sizeof(self_flag) )
                {
                        ps = keys(self_flag);
                        for (i = 0; i < sizeof(ps); i ++)
                                write(sprintf(HIG "%-20s%-20s\n" NOR, ps[i], get_object(self_flag[ps[i]])->short()));
                } else
                        write("��Ŀǰû�м�¼�ص㡣\n");

                return 1;
        }

        if( sscanf(arg, "rec %s", who) == 1 )
        {
                env = environment(me);

                // �жϼ�¼�Ƿ��Ѿ���������
                if( !MEMBER_D->is_valid_member(query("id", me))) max_rec = 0;
                else
                {
                        level = MEMBER_D->db_query_member(me, "vip");
                        switch( level )
                        {
                                case 3:
                                        max_rec = 4;
                                        break;
                                case 2:
                                        max_rec = 3;
                                        break;
                                case 1:
                                        max_rec = 2;
                                        break;
                                default:
                                        max_rec = 1;
                                        break;                          
                        }
                }

                rec_n=sizeof(query("horse/flags", me));
                max_rec+=query("horse/stone", me);

                if( rec_n >= max_rec )
                {
                        write(HIR "��ļ�¼�Ѵﵽ " + sprintf("%d", rec_n) + " ����������\n" NOR);
                        write(HIR "����Գ���ʹ��������ﾾ���������ļ�¼����\n\n" NOR);

                        write(HIC "��ͨ��ң�         Max = 0 ��\n" NOR);
                        write(HIM "��ͨ��Ա��         Max = 1 ��\n" NOR);
                        write(WHT "������Ա��         Max = 2 ��\n" NOR);
                        write(HIY "�ƽ��Ա��         Max = 3 ��\n" NOR);
                        write(HIW "�׽��Ա��         Max = 4 ��\n" NOR);
                        write(HIG "�� ���� ʯ��         ÿ��������ʯ���� 1 �� Max\n" NOR);
                        
                        return 1;
                }
 
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("�㻹������ƥ������˵�ɣ�\n"); 

                if( stringp(MAP_D->get_trans_path(who)) )
                        return notify_fail("�Բ��𣬱�� " + who + " �Ѿ����ڣ�����ȡһ����š�\n");

                if( stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("�Բ��𣬱�� " + who + " �Ѿ����ڣ�����ȡһ����š�\n");

                // �������û�г��ڲ��ܼ�¼
                if( !sizeof(query("exits", env)) )
                        return notify_fail("�˵ص㲻�ܼ�¼��\n");

                // no_magic ���ܼ�¼
                if( query("no_magic", env) || query("maze", env) )
                        return notify_fail("�˵ص㲻�ܼ�¼��\n");

                if( clonep(env) || !env->is_room() )
                        return notify_fail("�˵ص㲻�ܼ�¼��\n");

                if( domain_file(base_name(environment(me))) == "city2" )
                        return notify_fail("�˵ص㲻�ܼ�¼��\n");

                if( sscanf(base_name(environment(me)), "/data/%*s" ) )
                        return notify_fail("�˵ص㲻�ܼ�¼��\n");

                //if( !query("outdoors", env) )
                //        return notify_fail("�˵ص㲻�ܼ�¼��\n");
                        
                set("horse/flags/"+who, base_name(env), me);
                me->save();
                write(HIG "��¼�ɹ���\n" NOR);

                return 1;

        } 

        if( sscanf(arg, "unrec %s", who) == 1 )
        {
                if( !objectp(horse=query_temp("is_riding", me)) )
                        return notify_fail("�㻹������ƥ������˵�ɣ�\n"); 

                if( !stringp(query("horse/flags/"+who, me)) )
                        return notify_fail("�Բ��𣬱�� " + who + " �����ڣ���ʹ�� rideto �鿴��\n");

                delete("horse/flags/"+who, me);
                me->save();

                write(HIG "ɾ����¼�ɹ���\n" NOR);

                return 1;
                
        }
        
        if( query_temp("is_riding", me) )
                return notify_fail("���Ѿ��������ˣ�\n");

        if( query_temp("is_riding_follow", me) )
                return notify_fail("��������ride down����˵�ɣ�\n");

        if( me->is_busy() )
                return notify_fail("����һ��������û����ɣ�\n");

        if( me->is_fighting() )
                return notify_fail("�㻹��ս���У�û������ȥ��\n");

        // Check if a container is specified.

        if (! objectp(obj = present(arg, environment(me))))
                return notify_fail("��û�������������\n");

        if( !query("ridable", obj) )
                return notify_fail("���������ҲҪ��������ƨ�ɣ�\n");

        if( query("owner", obj) && query("owner", obj) != query("id", me) )
                return notify_fail("���Ѿ��������ˣ����޷���Ԧ����\n");

        return do_ride(me, obj);
        write("����ȥ�ˡ�\n");
}

int do_ride(object me, object obj)
{
        object old_env, *guard;

        if( !obj ) return 0;

        if( guard=query_temp("guarded", obj)){
                guard = filter_array(guard, (: objectp($1) && present($1, environment($2)) && living($1) && ($1!=$2) :), me);
                if( sizeof(guard) )
                        return notify_fail( guard[0]->name()
                                + "������" + obj->name() + "һ�ԣ���ֹ�κ������ߡ�\n");
        }

        obj->set_weight(1);
        if( obj->move(me) )
        {
                message_vision( "$N����Ծ��$n�����ֺ��ǽýݡ�\n", me, obj );
                set_temp("is_rided_by", me, obj);
                set_temp("is_riding", obj, me);
        }
        else
        {
                message_vision( "$N���ϴ��Ķ���̫���ˣ��޷��ﵽ$n����ȥ��\n", me, obj );
        }

        return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ :

ride <������>        ���ϴ�������ѱ���Ķ��
ride up <id>         �������������Աָ���
ride ok              ͬ����˵����롣
ride down            �ӱ��˵�����������ָ����רΪͬ�����˵����������õģ���
ride kick            �����ϵ�ͬ��������            
ride rec <����>      ���������¼��ǰ�ص㵽rideto�б���ȥ���Ժ����ֱ��������
                     ʹ�� rideto <����> ��������ط���

                     ��ͨ��ң�               �ɼ�¼ 0 ����
                     ��ͨ��Ա��		      �ɼ�¼ 1 ����
                     ������Ա��		      �ɼ�¼ 2 ����
                     �ƽ��Ա��		      �ɼ�¼ 3 ����
                     �׽��Ա��		      �ɼ�¼ 4 ����
                     ʹ�ò���ʯһ�Σ�	      ���������ɼ�¼�ռ� 1 ����

ride unrec <����>    ɾ��ָ����ŵļ�¼��
                       
HELP
    );
    return 1;
}
