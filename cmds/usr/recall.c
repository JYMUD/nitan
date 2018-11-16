// recall.c
// created by lonely@nitan2

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string file;
        string str;
        object ob;
 
        if (! environment(me)) 
                return 0; 

        if (! arg || (arg != "back" && 
            arg != "home" && sscanf(arg, "%s %s", arg, str) != 2))
                return help(me);
                               
        if (me->is_busy())
                return notify_fail("����æ���ء�\n");

        if (me->is_fighting())
                return notify_fail("����������ս����\n"); 

        if (me->is_ghost()) 
                return notify_fail("���㻹������˵�ɡ�\n"); 
                
        if (me->is_in_prison())   
                return notify_fail("�����������ء�\n");

        if( query("doing", me) )
                return notify_fail("�㻹���ʲô����\n");
                
        if( query("no_magic", environment(me)) )
                return notify_fail("�㷢�������е�Ź֣�\n");                
        
        if (arg == "back")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("�㻹����ս����ʹ�ã���\n");

                if (present("biao huo", me))
                        return notify_fail("�����ϴ�������������ʩչ��\n");

                if( sscanf(base_name(environment(me)), "/d/register/%*s") )
                        return notify_fail("�㻹û�г����أ�����ʩչ��\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("���ڹŴ��У�����ʩչ��\n");
                
                file = "/d/city/kedian";
                
                if (base_name(environment(me)) == file)
                        return notify_fail("���Ѿ������ݿ͵��ˡ�\n");
                        
                if (! get_object(file))
                        return notify_fail("��о����ƺ���ʲô���Ծ���\n");

                message("vision", me->name() + "������������ǰ���ٻ���һ��Բ������������ǰ��"
                        "�ռ䣬\nֻ��Բ�ڵĿռ���ս�" + me->name() + "�����˽�ȥ��\n",
                        environment(me), ({me}));
                
                tell_object(me, "��ӿ͵��ĳ������ռ��ѷ��������\n");

                me->move(file);
                message("vision", me->name() + "�ӿ͵��ĳ������ռ��ѷ��������\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
 
        if (arg == "back" || arg == "home")
        {
                if( query_temp("warquest/party", me) )
                        return notify_fail("�㻹����ս����ʹ�ã���\n");

                if (present("biao huo", me))
                        return notify_fail("�����ϴ�������������ʩչ��\n");

                if( sscanf(base_name(environment(me)), "/d/newbie/%*s") )
                        return notify_fail("���ڹŴ��У�����ʩչ��\n");
                
                if( arg == "back" )
                        file = "/d/city/kedian";
                else
                        file = query("private_room/position", me);
                
                if( !file ) return notify_fail("�㻹û��ס���أ�\n");
                
                if (base_name(environment(me)) == file)
                        return notify_fail("���Ѿ��������ˡ�\n");
                        
                if (! get_object(file))
                        return notify_fail("��о����ƺ���ʲô���Ծ���\n");

                message("vision", me->name() + "������������ǰ���ٻ���һ��Բ������������ǰ��"
                        "�ռ䣬\nֻ��Բ�ڵĿռ���ս�" + me->name() + "�����˽�ȥ��\n",
                        environment(me), ({me}));
                
                tell_object(me, "���ĳ������ռ��ѷ��������\n");

                me->move(file);
                message("vision", me->name() + "��ĳ������ռ��ѷ��������\n",
                        environment(me), ({me}));

                MYGIFT_D->check_mygift(me, "newbie_mygift/recall");
                return 1;
        }
                                       
        if( !stringp(file=query("can_whistle/"+str, me)) )
                return notify_fail("�㲢û�����ħ���ޡ�\n");

        if (file_size(file + ".c") < 0)
                return notify_fail("�㲢û�����ħ���ޡ�\n");
                                
        if( arg == "reborn" && query("warcraft/status", me) == "died" )
        {
                if (me->query_skill("huisheng-jue", 1) < 100)
                        return notify_fail("��Ļ����������������޷���ħ����������\n"); 

                if( query("neili", me)<query("max_neili", me)*9/10 )
                        return notify_fail("�����������������棬����óȻ���ã�\n");

                if( query("jingli", me)<query("max_jingli", me)*9/10 )
                        return notify_fail("�����ھ������ã�����óȻ���ã�\n");

                if (me->query_skill("force") < 200)
                        return notify_fail("����ڹ�����������ʵ������óȻ���á�\n");

                if( query("max_neili", me)<3000 )
                        return notify_fail("�㳢������һ���������޷�˳"
                                   "������һ�����죬����ʩչ���������\n");

                if( query("max_jingli", me)<1000 )
                        return notify_fail("����ͼ�������þ��������Ǹо�����Ƿȱ��\n");                                
                
                if( query("experience", me)<query("learned_experience", me)+1000 )
                        return notify_fail("�����ڻ��۵�ʵս��ỹ̫�٣��޷�óȻ���á�\n");

                message_sort(HIR "$N���о�����ָ��أ�ͬʱ��ת������������"
                        "���澭����ԴԴ������������ע���ء�\n" NOR, me); 

                me->start_busy(1);
        
                addn("max_neili", -500, me);
                set("neili",query("max_neili",  me), me);
                addn("max_jingli", -300, me);
                set("jingli",query("max_jingli",  me), me);
                addn("learned_experience", 1000, me);
                set("warcraft/status", "living", me);
                tell_object(me, HIW "������Ƭ�̣�����ħ����"
                        HIW "�ƺ�������������ڲ�Զ��������΢΢һЦ��\n" NOR);                                                                             
                
        } 
        else return help(me);
        return 1;
}

int help(object me)
{
 write(@HELP
ָ���ʽ : recall back | home
�ص����ݿ͵��ָ��Ϊ < recall back >��
�ص�ס����ָ��Ϊ < recall home >��
HELP
    );
    return 1;
}

