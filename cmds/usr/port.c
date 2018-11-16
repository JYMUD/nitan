// port.c
// Created by robert@wllz
// Modify by ken@NT

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob;
        string str;
        int i, I1, I2, I3, I4;
        
        ob = filter_array(children(USER_OB),(: userp :));
        str = HBRED"����Ϊ����Ϸ���˿�ʹ����������� 6000 Ϊ������(BIG5)ר�ö˿ڡ�\n"NOR;
        for(i=0;i<sizeof(ob);i++){
                if(!environment(ob[i])) continue;
                if(query_ip_port(ob[i]) == 5000) I1++;
                if(query_ip_port(ob[i]) == 6000) I2++;
                if(query_ip_port(ob[i]) == 7000) I3++;
                if(query_ip_port(ob[i]) == 3000) I4++;
        }

        str += sprintf(HBRED"    " CYN "��3000��" HIW "%3d" CYN "�˩�5000��" HIW"%3d" CYN "�˩�6000��"HIW "%3d" CYN"��|7000�� "HIW "%3d" CYN "��|     \n" NOR,I4,I1,I2,I3);

        write(NOR + str + "\n");
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��port

���ָ���������˽�Ŀǰ��Ϸ�и��˿ڵ�ʹ�ó̶ȡ�Ϊ�˸����ṩһ����
�������绷��������ѡ��ʹ���ʽϵ͵Ķ˿����ߡ�

HELP
        );
        return 1;
}
