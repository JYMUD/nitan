#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIG "����֮ŭ" NOR, ({ "jianling zhinu", "zhinu", }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "�����ɺ���ʯ�ͽ����ŭ���ᾧ���ɵ�ͷ���������â������η��\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 45);
                set("armor_prop/str", 45);
                set("armor_prop/con", 45);
                set("armor_prop/damage", 4300);
                set("armor_prop/sword", 200);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "��������װ������֮һ������֮ŭ������֮�ۡ�����֮��������֮�꣩��\n"
                                    "                  ���ڽ�����װ�Ĵ�˵�μ� help boss\n"
                                    "                  ��Ч�������300����\n");
                set("limit", ([
                         "exp" : 100000000,
                         "thborn" : 1,
                         "jianling": 1, // equip.c�����ƣ�����Ҫ�����ɹ�����1�κ����װ��
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
