// Room: /d/xingxiu/job2.h
// Last Modified by winder on Apr. 25 2001

int valid_leave(object me, string dir)
{
        object ob;
        if( query_temp("wait_target", me) && 
                objectp(present("anran zi", environment(me))))
                return notify_fail("��Ȼ��������������ǰ���ȵ�������������ҹ�������\n");
        if( query_temp("xx_rob", me) && 
                objectp(ob = present("hubiao biaoshi", environment(me))) &&
                query("target", ob) == me )
                return notify_fail("������ʦ������ס���ȥ·�����������������ˣ�\n");  
        if( query_temp("xx_rob", me) && objectp(present("shangdui",environment(me))) )
                return notify_fail("�̶��������أ�����(qiang)����\n");  
        return ::valid_leave(me, dir);
} 