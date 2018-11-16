// whistle.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string file;
        mapping whistle;
        string *ks;
        string msg;
        int i;

        if (! arg)
        {
                whistle=query("can_whistle", me);
                if (! mapp(whistle) || ! sizeof(whistle))
                        return notify_fail("��Ҫ�ٻ�ʲô��\n");
                ks = keys(whistle);
                msg = "�����ڿ����ٻ���ħ������\n";
                for( i=0; i<sizeof(ks); i++ )
                {
                        if( sscanf(whistle[ks[i]], "/data/beast/%*s") )
                        {
                                delete("can_whistle/" + ks[i], me);
                                continue;
                        }
                        msg += sprintf(HIW "ħ���޴��룺%-15s    ħ�������֣�%-20s\n"NOR,ks[i],whistle[ks[i]]->name());
                }
                write(msg);
                return 1;
        }
                        
        if( me->is_busy() || query("doing", me) )
                return notify_fail("��������æ�أ������п�����˵�ɡ�\n");
 
        if (me->is_in_prison())   
                return notify_fail("�����������أ������ʲô����\n"); 
                               
        if (me->is_ghost())
                return notify_fail("���㻹�������ٻ��ɡ�\n");

        if( !stringp(file=query("can_whistle/"+arg, me)) )
                return notify_fail("�㲻֪������ٻ����ħ���ޡ�\n");

        if (file_size(file + ".c") < 0)
                return notify_fail("�㲻֪������ٻ����ħ���ޡ�\n");
        
        if( query("warcraft/status", me) == "died" )
                return notify_fail("���ħ�����Ѿ��������뵽����ʦ���������ȸ��\n");

        if( query("no_magic", environment(me)) || query("no_fly", environment(me)) )
                return notify_fail("�㷢�������е�Ź֣����ħ���޺����ܽ�����\n");    
         
        call_other(file, "???");
        ob = find_object(file);

        if (! ob || ! ob->receive_whistle(me))
        {
                message_vision(HIM "$N" HIM "����һ�����ڡ�\n"
                               "Ȼ��ʲôҲû�з��� :)\n", me);
        }
        
        if (! ob) return 1;
        ob->reset_action();
        ob->set_leader(me);
        
        if (me->is_fighting())                                                                     
                me->start_busy(1 + random(3));

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : whistle <ħ����ID>

��ָ�����������ħ���޺�����������Ȼ�����һ���ľ���ʩչ���С�
HELP );
        return 1;
}

