
#include <armor.h>
#include <ansi.h>

inherit MEDAL3;

void create()
{
        set_name(HIY "�׻Ʒ���ʮ�����ѫ��" NOR, ({ "yhhero year10", "yhhero", "year10" }));
        set("long", HIY "Ϊ�����׻���Ӫʮ���꣬������ʮ�ꡱ��ر��������еļ���ѫ�£�\n" NOR);
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/year10", 1);
                set("armor_prop/damage", 4000);
                set("armor_prop/armor", 4000);
                set("armor_prop/force", 200);
                set("armor_prop/add_yanjiu_times", 100);
                set("special/desc", HIR "����������������ɱ�־��鼰Ǳ�ܽ���5%\n"
                                        "                  ��������100���о�����\n"
                                        "                  ��Ч�ڹ�����200��" NOR);
                set("armor_prop/con", 40);
                set("armor_prop/dex", 40);
                set("armor_prop/str", 40);
                set("armor_prop/int", 40);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}