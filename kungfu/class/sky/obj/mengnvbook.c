#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "����" NOR, ({ "zi tiao", "zi", "tiao" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "����һ�����������飺\n\n" HIW
                                 "   ���������Ϊ�ã��᱾��Ϊ�ã������Ѿ������������������ٱ�\n"
                                 "������������������������ν��ѣ������ӣ����������أ�����\n\n"
                                 "                                                      ---- �Ρ�����\n\n" NOR);
                set("value", 300);
                set("material", "paper");
        }
}

