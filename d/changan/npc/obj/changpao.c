//changpao.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("����", ({"chang pao", "cloth"}));
          set_weight(3000);
          if (clonep())
                    set_default_object(__FILE__);
          else
        {
                set("long", "һ�����ۡ�\n");
                    set("material", "cloth");
                    set("unit", "��");
                    set("value", 300);
                    set("armor_prop/armor", 15);
        }

        setup();
}