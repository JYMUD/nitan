// system.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string fs(int supplied);
string fc(int cost);

int main(object me, string arg)
{
        string msg;
        mapping cm;

        cm = COMBAT_D->query_entire_dbase();
        msg = "ϵͳ���ڵ����ã�\n";
        if (! mapp(cm))
                msg += "���顣\n\n";
        else
                msg += "PK �������ƣ�ÿ�첻���� " HIR +
                       cm["pk_perday"] + NOR " �ˣ�ÿ�˲����� "
                       HIR + cm["pk_perman"] + NOR + " �Ρ�\n\n";

        cm = CPU_D->query_entire_dbase();
        msg += "���һ��ʱ��ϵͳʹ��CPU�����ͳ�ƣ�\n";
        msg += "ϵͳ�ṩCPU��Դ������ȣ�" + fs(cm["last_0"]["supplied"]) +
              "  ��Ϸ��CPU��ռ���ʣ�" + fc(cm["last_0"]["cost"]) + "��\n";

        msg += sprintf("ǰһЩʱ��CPU������Ⱥ�ռ���ʣ�%s/%s  %s/%s  %s/%s  %s/%s��\n",
                       fs(cm["last_1"]["supplied"]), fc(cm["last_1"]["cost"]),
                       fs(cm["last_2"]["supplied"]), fc(cm["last_2"]["cost"]),
                       fs(cm["last_3"]["supplied"]), fc(cm["last_3"]["cost"]),
                       fs(cm["last_4"]["supplied"]), fc(cm["last_4"]["cost"]));
        write(msg);
        return 1;
}

string fs(int supplied)
{
        if (supplied <= 70)
                return sprintf(RED "%d%%" NOR, supplied);
        else
        if (supplied <= 90)
                return sprintf(HIR "%d%%" NOR, supplied);

        return sprintf(WHT "%d%%" NOR, supplied);
}

string fc(int cost)
{
        if (cost < 0) cost = 0;
        if (cost >= 90)
                return sprintf(RED "%d%%" NOR, cost);
        else
        if (cost >= 70)
                return sprintf(HIR "%d%%" NOR, cost);

        return sprintf(WHT "%d%%" NOR, cost);
}


int help(object me)
{
        write(@HELP
ָ���ʽ : system [-ui] [+|- <����> <����>]
 
���ָ�������ʾ��Ŀǰ��Ϸ��ͨ�����ú�ʹ��ϵͳ��Դ��״����ʹ
�� ui �������Բ���Ŀǰ MUD ����߶��ڵ����ɵĸ������ȼ���
 
HELP );
        return 1;
}