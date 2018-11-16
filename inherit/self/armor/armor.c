
#include <armor.h>
#include <self.h>

inherit ARMOR;

void create(class data)
{
        set_name("��", ({ "armor", }));

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "����һ����ͨ�Ļ��ס�\n");
                set("unit", "��");
                set("value", 200);
                set("material", "cloth");
                set("armor_prop/armor", query("point")*2);
        }

        set_weight(500);
        setup();
}

// ����װ�����˺�ֵ
int apply_damage()
{
        int d;
        int p;

        attack_lvl = weapon_level();
        p = query("point");
        d = attack_lvl * p / MAX_LEVEL + query("bless") * 10; // Ǭ��ʥˮʥ��һ������ʮ�㹥��
        return d + p;
}

// ����װ������Чֵ
int apply_armor()
{
        int d;
        int p;

        defense_lvl = armor_level();
        p = query("point");
        // if( d > p * 3 / 2) d = p * 3 / 2 + query("bless") * 10;// Ǭ��ʥˮʥ��һ������10�����
        d = p * 3 / 2 + query("bless") * 2;// Ǭ��ʥˮʥ��һ������2�����
        return d + p;
}

#include <ansi.h>
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("��˿��", ({ "aarmor" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "��");
        set("long", "�������������ƶ��ɵ�һ�Ż��ס�
����Ե�Ͽ���һ��С�֣�����һ(adami)
");
        set("value", 2100000);
        set("point", 152);
        set("material", "magic stone");
        set("material_file", "ddd");
        set("wear_msg", "$Nװ����˿�ס�\n");
        set("remove_msg", "$N�����˽�˿�ס�\n");
        set("armor_prop/armor", apply_armor());

        setup();
}

string long() { return query("long") + item_long(); }


#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
        set_name("�׺罣", ({ "asword" }));
        set_weight(9000);
        set("item_make", 1);
        set("unit", "��");
        set("long", "�������������ƶ��ɵ�һ������
�����Ͽ���һ��С�֣�����һ(adami)
");
        set("value", 2100000);
        set("point", 190);
        set("material", "magic stone");
        set("wield_msg", "$N��ৡ���һ�����һ������������$n�������С�\n");
        set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");

        init_sword(apply_damage());

        setup();
}

string long() { return query("long") + item_long(); }
