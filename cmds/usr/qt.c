// quest.c

#include <ansi.h>
 
int main(object me, string arg)
{
        int status=query("to_pvp/status", me);
        string str,master=query("family/master_name", me);

        if( !query("to_pvp", me) )
                return 0;

        if( !status )
        {
                if( query("to_pvp/time", me)<time() )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"��̾�������ѵ������о�û������ɱ������������������");
                }
                if( arg == "cancel" )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"ŭ�������ߣ�������˵�С֮�ˣ����ܳɴ�����������\n");
                }
                if( arg == "ok" )
                {
                        set("to_pvp/status", 1, me);
                        set("to_pvp/time", time()+600, me);
                        return notify_fail("��ŭ���������д�����˶����������������ڴ����ϣ�����ȥɱ�˴������汾�ɳ�������\n");
                }
                str =  sprintf("�㽫Ҫ����ȥɱ�ı��ų��%s(%s)��\n", 
                        query("to_pvp/name", me),query("to_pvp/id", me));
                str += sprintf("�㻹��%s���������������\n",
                        CHINESE_D->chinese_number(query("to_pvp/time", me)-time()));
                str += "�����Ҫ�������������롰qt ok��\n";
                write(str);
                return 1;
        }
        else
        {
                if( query("to_pvp/time", me)<time() )
                {
                        delete("to_pvp", me);
                        return notify_fail(master+"����ɱ��С������Ȼ������ô�õ�ʱ�仹ûɱ�����ҿ�Ҳ���������ˣ�����Һúõ�ѧ�հɣ����������ˣ��ߣ�������");
                }
                str =  sprintf("��Ҫɱ�ı��ų����%s(%s)��\n", 
                        query("to_pvp/name", me),query("to_pvp/id", me));
                str += sprintf("����Ҫ��%sǰ������������\n",
                        CHINESE_D->chinese_date(query("to_pvp/time", me)));
                write(str);
                return 1;
        }
        return 0;
}
