
#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIG "ն��ѫ��" NOR, ({ "zhanyao xunzhang", "zhanyao", "xunzhang" }));
        set("long", HIG "նɱǧ���ͷ�߾����õ�ѫ�£��ǳ���������ߵ�������\n" NOR);
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 200000);
                set("material", "bronze");
                set("armor_prop/damage", 200);
                set("armor_prop/zhanyao", 1);
                set("special/desc", HIR "����������������ɱ�־��鼰Ǳ�ܽ���10%��" NOR);
                set("armor_prop/con", 6);
                set("armor_prop/dex", 6);
                set("armor_prop/str", 6);
                set("armor_prop/int", 6);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}