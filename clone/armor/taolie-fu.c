
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIY "���ѷ�" NOR, ({ "taolie fu", "taolie", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIY "����һ�ŵ��������滭��һ���Źֵľ��ޡ�\n" NOR);
                set("value", 10000);
                set("armor_prop/greedy", 1);
                set("special/desc", "5%���ʴ��ж��ֽ��ͶԷ�ʳ�Ｐ��ˮ����");
        }
        setup();
}

int query_autoload()
{
        return 1;
}