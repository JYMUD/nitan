// This program is a part of NT MudLIB
// quest1.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping q;
        string name, npc;

        if( query("ultra_count", me) )
                write(sprintf("���ͽ��������ʦ�������Ѿ���������� %d ����\n",
                              query("ultra_count", me)));

        if( !query("ultraquest/npc1", me) )
        {
                write("������û�����κ�����\n");
                return 1;
        }

        if( query("ultraquest/npc5", me) )
        {
                npc=query("ultraquest/npc5", me);
                name=query("ultraquest/name5", me);
        } else
        if( query("ultraquest/npc4", me) )
        {
                npc=query("ultraquest/npc4", me);
                name=query("ultraquest/name4", me);
        } else
        if( query("ultraquest/npc3", me) )
        {
                npc=query("ultraquest/npc3", me);
                name=query("ultraquest/name3", me);
        } else
        if( query("ultraquest/npc2", me) )
        {
                npc=query("ultraquest/npc2", me);
                name=query("ultraquest/name2", me);
        } else
        {
                npc=query("ultraquest/npc1", me);
                name=query("ultraquest/name1", me);
        }

        if( !mapp(q=query("ultraquest/quest", me)) )
        {
                if( query("ultraquest/id", me) )
                {
                        write("�����ڵ�������ȥɱ��Ļ�����"+query("ultraquest/name", me)+"("+
                              query("ultraquest/id", me)+")����������ͷ�����͡�\n");
                        return 1;
                }
                write("�����ڵ�������ȥѰ������֪����" + name + "(" + npc + ")��\n" +
                      "��˵��ǰ��������"+query("ultraquest/place", me)+"���ֹ���\n");
                return 1;
        } else
        {
                switch (q["type"])
                {
                case "kill":
                        write(name + "(" + npc + ")�Ը���ȥ����" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "����ͷ���������\n");
                        return 1;

                case "give":
                        write(name + "(" + npc + ")�Ը���ȥ�Ѱ����͵�" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "������������\n");
                        return 1;

                case "send":
                        write(name + "(" + npc + ")�Ը���ȥ�����͵�" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "������������\n");
                        return 1;

                case "guard":
                        write(name + "(" + npc + ")�Ը������������ﱣ������\n");
                        return 1;

                case "mathematics":
                        write(name + "(" + npc + ")�Ը�������������㡣\n");
                        return 1;

                case "literate":
                        write(name + "(" + npc + ")�Ը����������ʫ�ʡ�\n");
                        return 1;

                case "chess":
                        write(name + "(" + npc + ")�Ը�����������弼��\n");
                        return 1;

                case "calligraphy":
                        write(name + "(" + npc + ")�Ը������д���鷨��\n");
                        return 1;

                case "drawing":
                        write(name + "(" + npc + ")�Ը�������滭��\n");
                        return 1;

                case "medical":
                        write(name + "(" + npc + ")�Ը�������β���\n");
                        return 1;
                }
        }

        write("������û�����κ�����\n");
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quest2 ��ʾ���㵱ǰ����ʦ����
HELP );
        return 1;
}

