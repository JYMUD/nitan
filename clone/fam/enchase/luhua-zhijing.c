inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "¶��֮��" NOR, ({"luhua zhijing", "luhua", "zhijing" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "¶��֮�����������ɾ�֮�ߵ�¶�飬��ȡ������֮�����ᾧ���ɣ��̺���������֮������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "¶��֮��");
                set("enchase/point", 1);
                set("enchase/type", "10k");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", (["luhua-zhijing":1]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

