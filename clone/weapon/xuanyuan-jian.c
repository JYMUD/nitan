// �Ϲ�ʮ������֮ ��ԯ��
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY "��ԯ��" NOR, ({ "xuanyuan jian", "xuanyuan", "jian" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIY "�����Ϲ�����֮�ף�ӵ�����������������˵"
                                "ӵ�д˽��߿ɳ۳��ˡ�ħ�������磬�Ʋ��ɵ���\n"
                                "��������˸�����ֵ����֣����Ƿ�̾��ġ�\n" NOR);
                set("material", "tian jing");
                set("wield_msg", HIY "$N" HIY "һ���������������������£�ӵ��һ��������\n"
                                 "�����񽣣�ɲ�Ǽ�˽�����һ�����ǻ���������$N" HIY "���С�\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "����һת����ԯ���ѹ��ʡ�\n" NOR);
                set("stable", 100);

        }
        init_sword(1200);
        setup();
}