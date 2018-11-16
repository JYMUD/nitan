// Room: flower.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>                     
#include <armor.h>
inherit HEAD;

void create()
{
        set_name(HIG"�����޻�"NOR,({ "flower", "hua" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 0);
                set("material", "plant");
                set("long", "����һ�������޻���\n"
                        "�⻨֭ԭ���ȳ�֮���������޶���, \n"
                        "��һ������Ѫ��ͣ�ȴ���綾��ͬʱ�ȳ�תΪ���㡣\n");
                set("wear_msg", "");
                set("unequip_msg", "$Nժ����ǰ��$n��\n");
                set("armor_prop/armor", 0);
        }
        setup();
}

int wear()
{
        object me = environment();
        int ret;

        message_vision("$N�ó�һ��"+query("name", this_object())+"��������ǰ��",me);
        if (ret=::wear())
        {
                if( query("gender", me) == "����" )
                        message_vision("��һ�����������ɣ�\n", me);
                else if( query("gender", me) == "Ů��" )
                        message_vision("��һ�������μ��ޣ�\n", me);
                else
                        message_vision("��һ���������ĵļһ\n", me);
        }
        return ret;
}