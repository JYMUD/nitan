#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name(HIG "����֮��" NOR, ({ "jianling zhihen2", "zhihen2" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
                set("long", HIG "�����ɽ���������ᾧ���ɵı�ѥ������ȥ�쳣���ء�\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60);
                set("armor_prop/dodge", 300);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "��������װ������֮һ������֮ŭ������֮�ۡ�����֮��������֮�꣩��\n"
                                    "                  ���ڽ�����װ�Ĵ�˵�μ� help boss\n"
                                    "                  ��Ч�Ṧ�ȼ����300����\n");
                set("material", "boots");
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
