// This program is a part of NT MudLIB

inherit __DIR__"shamo";

int valid_leave(object me, string dir)
{
        string dest;

        if (dir == "east")
        {
                if( addn_temp("out_shamo",1,me) >= 3 )
                {
                        me->move(__DIR__"silk5");
                        write("���۵ð���������߳���ɳĮ��\n");
                        return -1;
                }
        }

        return ::valid_leave(me, dir);
}
