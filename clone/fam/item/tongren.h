// ͭ��

#include <ansi.h>

inherit ITEM;

#define MEMBER_D        "/adm/daemons/memberd"

int is_tongren() { return 1; };

void create()
{
        set_name(NOR + YEL "ͭ��������" NOR, ({ "ͭ��ID" }) );
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "����һ����Ѩͭ�ˣ���������˴�ͨ�����Ĺؼ�Ѩλ��\n" HIG
                                      "*�йؾ�����Ѩ����ϸ������μ� help jingmai \n" NOR);
                set("value", 1);
                set("unit", "��");
                set("neili", NEILICOST); // ��������
                set("jingmai_name", "JINGMAI_NAME"); // ������
                set("xuewei_name", "XUEWEI_NAME"); // Ѩλ��
                set("point", "CHONGXUE_XIAOGUO"); // ��ѨЧ��
        }

        setup();
}

int query_autoload()
{
         return 1;
}
