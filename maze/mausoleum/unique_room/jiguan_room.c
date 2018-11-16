#include <ansi.h>

void init()
{
       object me = this_player();
       object ob;

       if( !objectp(ob = FUBEN_D->query_maze_mainobj(me)) ) {
             write(HIR "TSR �������������뱾վ (admin) ��ϵ��\n" NOR);
             return;
       }

       //if( wizardp(me) || present("dispay serial", me) ) {
       if( userp(me) ) {

                write(HIG "\n����ID��" + query("room_id") + "\n");
                write(HIG "�����������÷�������кţ�" + query(query("room_id"), ob) +"\n"NOR);
                write(HIG "��ȷ����˳��A��B��C��D\n" NOR);
       }

       add_action("do_move", "move");
}

int do_move(string arg)
{
       object me = this_player();
       object ob;
       string room_id;

       if( !arg || arg != "desk" )
             return notify_fail("�����ƶ�ʲô��\n");

       if( me->is_busy() || me->is_fighting() )
             return notify_fail("����æ������˵�ɣ�\n");

       ob = FUBEN_D->query_maze_mainobj(me);

       if( !objectp(ob) )
             return notify_fail("TSR ����������������ʦ��ϵ��\n");

       if( query("lock/unlocked", ob) )
             return notify_fail("�����Ѿ������ˣ������Ƕ��һ�١�\n");

       room_id = query("room_id");
       room_id = query(room_id, ob);

       if( !stringp(ob->openlock(me, room_id)) )
             return notify_fail("TSR ���ݳ���������ʦ��ϵ��\n");

       me->start_busy(1 + random(2));

       message_vision(HIC "$N" HIC "��ʯ����������ת��ֻ���ò�Զ������"
                      "һ���¡¡�����Ǵ������ص�������\n" NOR, me);

       return 1;
}
