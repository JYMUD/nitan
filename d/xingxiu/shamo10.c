// This program is a part of NT MudLIB

inherit __DIR__"shamo";

int valid_leave(object me, string dir)
{
        string dest;

        if (dir == "west")
        {
                if( addn_temp("out_shamo",-1, me) <= -3 )
                {
                        me->move("/d/baituo/gebi");
                        write("���۵ð���������߳���ɳĮ��\n");
                        return -1;
                }
        }

        return ::valid_leave(me, dir);
}
