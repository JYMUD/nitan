#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "ӨѪ��˿" NOR, ({"yingxue zhusi", "yingxue", "zhusi"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "��˵������һ�綾֩�룬��Ϊ��ӨѪ��������ѪҺ��Ө��͸������ҹ��ӫ����\n"
                                                "�����������飬�綾�ޱȣ���֮����������֮˿ϸ�����ޣ�ȴ˿���޶���������\n"
                                                                "������ɽ��Ѩ֮�У����˼�ʹ���������٣���Ҫ��׽ȡ˿���Ҳ�Ǳ���綾���ˣ�\n"
                                                                "��һ���⡣\n" HIG 
                                                                "ǧ������ӨѪ��˿Ϊ�����������Ѳ��ϡ����������������ĥ��\n" NOR);
                set("unit", "��");
                set("value", 20000);
                set("item_origin", 1);
                set("material_attrib", "tian jing");
                set("material_name", HIR "ӨѪ��˿" NOR);
                set("can_make", ({ "����" }));
                set("power_point", 150 + random(10));
        }
}

int query_autoload()
{
        return 1;
}

