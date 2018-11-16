// toptenadd.c
#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string str,*astr,type;
        int i;
        mapping paiming;

        seteuid(geteuid(me));
        if (!arg||arg=="")
                  return notify_fail("ָ���ʽ : topten ��������
Ŀǰ�����������У�\n
        ��"+LOCAL_MUD_NAME()+"��ʮ��������а�gaoshou��
        ��"+LOCAL_MUD_NAME()+"��ʮ���������а�xinrui��
        ��"+LOCAL_MUD_NAME()+"��ʮ�������а�exp��
        ��"+LOCAL_MUD_NAME()+"��ʮ�������а�richman��
        ��"+LOCAL_MUD_NAME()+"��ʮ���������а�neili��
        ��"+LOCAL_MUD_NAME()+"��ʮ�������а�jingli��
        ��"+LOCAL_MUD_NAME()+"��ʮ���ĺ����а�dushu��\n");

        if( time()-query_temp("last_topten", me)<1 )
              return notify_fail("ϵͳ�������̾���������� ....\n");  

        if( !wizardp(me) )
        set_temp("last_topten", time(), me);
        if (arg=="gaoshou")
              type="gaoshou";
        else if(arg=="xinrui")
              type="xinrui";
        else if(arg=="exp")
        {
              // if (!wizardp(me)) return notify_fail("����Ȩ�鿴�����Ŀ��\n");
              type="exp";
        }
        else if(arg=="richman"||arg=="rich")
        {
              // if (!wizardp(me)) return notify_fail("����Ȩ�鿴�����Ŀ��\n");
              type="rich";
        }
        else if(arg=="neili")
              type="neili";
        else if(arg=="jingli")
              type="jingli";
        else if(arg=="dushu"||arg=="literate")
              type="dushu";
        else 
              type=arg;
        if (type == "gaoshou")
        {
                paiming = COMPETE_D->query_tops();
                str = HIC "      *          ��       ��       ��       ��          *\n"NOR;
                str += HIC "-------------------------------------------------------------\n";
                str += "\n";
                for (i = 0;i < sizeof(paiming);i++)
                {
                        str += HIY + "   �����µ�" + chinese_number(i+1) + "�� " + NOR + 
                               paiming[i]["title"] + "\n";
                        str += "\n";
                }
                str += HIC "-------------------------------------------------------------\n";
        } else if (type == "xinrui")
        {
                paiming = XINRUI_D->query_tops();
                str = HIC "      *          ��       ��       ��       ��          *\n"NOR;
                str += HIC "-------------------------------------------------------------\n";
                str += "\n";
                for (i = 0;i < sizeof(paiming);i++)
                {
                        str += HIY + "   ����" + chinese_number(i+1) + "���� " + NOR + 
                               paiming[i]["title"] + "\n";
                        str += "\n";
                }
                str += HIC "-------------------------------------------------------------\n";
        } else str = TOPTEN_D->topten_query(type);
        write(str+"\n");
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : topten ��������
Ŀǰ������������:
gaoshou  ʮ�����
xinrui   ʮ������
exp      ʮ����[��ʦ�鿴]
richman  ʮ����[��ʦ�鿴]
neili    ʮ������
jingli   ʮ����
dushu    ʮ���Ĳ�
HELP
    );
    return 1;
}
