// tune.c

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

int main(object me, string arg)
{
        int my_channels = query("channels", me), flag;
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D));
        class channel_class ch;

        if( !arg )
        {
                tell(me, "������ʹ���е�Ƶ���У�"+CHANNEL_D->query_using_channel(me)+"��\n");
                return 1;
        }
        
        if( wizardp(me) && sscanf(arg, "-l %s", arg) ) flag = 1;

        if( undefinedp(ch = channels[arg]) || !classp(ch) )
                return notify_fail("û�����Ƶ����\n");

        if( !(ch->number & my_channels) && (wiz_level(me->query_id(1)) < ch->level) )
                return notify_fail("û�����Ƶ����\n");

        if( flag )
        {
                string *names;
                names = CHANNEL_D->query_channel_users(arg)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "Ŀǰ���� " + arg + " Ƶ���Ĺ� " + sizeof(names) + " �����£�\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");

                names = CHANNEL_D->query_channel_users(arg, 1)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "���� " + sizeof(names) + " �����£�\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");
                return 1;
        }

        if( ch->number & my_channels )
        {
                set("channels", my_channels ^ ch->number, me);
                CHANNEL_D->remove_register(me, ch->number);
                tell(me, "�ر� "+arg+" Ƶ����\n");
        }
        else
        {
                set("channels", my_channels | ch->number, me);
                CHANNEL_D->register_channel(me, ch->number);
                tell(me, "���� "+arg+" Ƶ����\n");
        }
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��tune [<Ƶ������>]

���ָ������ѡ���Ƿ�Ҫ����ĳһƵ����ѶϢ�����û��ָ��Ƶ�����ƣ��ͻ��г�
��Ŀǰ�����е�Ƶ�������ָ����Ƶ����ԭ�������еľͻ�ص�����֮�򿪡�

������һ��û�������е�Ƶ�����������Զ������򿪡�
Ҫ��һ��Ƶ��������ֻҪ�ã�

<Ƶ������> <ѶϢ> ....

���ӣ�
  chat hello everyone!

������� help channels ��ѯĿǰ����ЩƵ������������

see also : chat, rumor ...
HELP
        );
        return 1;
}
