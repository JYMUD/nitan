
#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIR "�����롤����" NOR, ({ "yaoyan erhuan", "yaoyan", "erhuan" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "�㶨��һ����ȴ�޷���ʶ���������Ļ����ҫ���ۣ����˾�η��\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 40);
                set("armor_prop/magic_find", 10);
                set("limit", ([
                        "exp" : 10000000,
                        "sex" : 1, // 1 ΪŮ��
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}
