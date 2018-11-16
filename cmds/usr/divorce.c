// divorce.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object witness;
        mapping couple;
        object  user;
        string  msg;

        seteuid(getuid());

        if( !mapp(couple=query("couple", me)) )
                return notify_fail("�����ں����ǵ���һ�˰ɣ�\n");

        if (! arg)
                return notify_fail("��Ҫ��˭�����Լ��\n");

        if( arg == query("id", me) )
                return notify_fail("����...����ķ���...\n");

        if( arg != query("couple/couple_id", me) )
                return notify_fail("���˺������ڲ����Ƿ��޹�ϵ����\n");

        if (objectp(witness = present("marriage witness", environment(me))))
                return witness->do_divorce(me);

        if( !query_temp("pending/want_divorce", me) )
        {
                write("���������֤����˶�û�У�����ݲݵ�����"
                      "���ˣ�Ҫ�����������������һ�����ָ���ʾ���ġ�\n");
                set_temp("pending/want_divorce", 1, me);
                return 1;
        }

        write("���¶����ģ�һ��Ҫ��"+query("couple/couple_name", me)+"���׷��֣�\n");

        CHANNEL_D->do_channel(me, "chat",
                "��" + me->name(1) + "�ӽ�����ͺ�" + couple["couple_name"] +
                "(" + couple["couple_id"] + ")���׶Ͼ���ϵ��");

        user = find_player(couple["couple_id"]);
        if (user)
        {
                switch(query("character", user) )
                {
                case "��������":
                        msg = "���ģ�" + me->name(1) + "����û�����ĵ�" +
                              RANK_D->query_rude(me) + "��";
                        break;

                case "������":
                        msg = "��..�ߣ��٣��߰ɣ��߰ɣ�";
                        break;

                case "�ĺ�����":
                        msg = "�����" + me->name(1) + "�����������ƣ�";
                        break;

                default:
                        msg = "�ܺã�" + me->name(1) + "����Űɣ�";
                        break;
                }

                CHANNEL_D->do_channel(user, "chat", msg);
        }

        UPDATE_D->clear_user_data(query("id", me),"couple");
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : divorce
 
��顣��˼�����Ժ���߸���·��
 
see also : divorce
HELP );
    return 1;
}