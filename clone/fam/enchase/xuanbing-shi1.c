inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "����ʯ��1����" NOR, ({"xuanbing shi1", "shi1"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIW "����һ��ͨ���ɫ����ʯ�����Լ���֮�أ���˵��ʹ�Ǿ�ǧ�߶����ɵã�\n"
                                "�ɼ�����ʯ�Ǽ����ϡ�У�����ֻ�е�����ٹ��˺͵�λ�Ժ�֮�˲�ӵ�С�\n"
                                "����ʯ�ֳư���ͨ�������ڽ��һ����֮�ϣ���ζ�ŵ�λ�Ժգ�����\n"
                                "���ӡ�\n" HIY
                                "ʹ�÷�ʽ����Ƕ�ڻ�����ϣ����Ӹ�Ե +1\n " NOR); 
                              
                set("value", 500000);
                set("enchase/name", "����ʯ��1����");
                set("enchase/fy", 1);
                set("enchase/point", 1);
                set("enchase/type", "myheart");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );
        }
        setup();
}

int query_autoload()
{
        return 1;
}

