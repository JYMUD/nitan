// refuse.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        function f;

        seteuid(getuid());

        if (! arg)
                return notify_fail("��Ҫ�ܾ�˭��\n");

        notify_fail("����û���������ʲôҪ�󰡣�\n");
        if( !functionp(f=query_temp("pending/answer/"+arg+"/refuse", me)) )
                return 0;

        delete_temp("pending/answer/"+arg, me);
        return evaluate(f);
}

int help(object me)
{
   write( @HELP
ָ���ʽ: refuse <someone>

�ܾ�ĳ�����������Ҫ��
HELP );
   return 1;
}
