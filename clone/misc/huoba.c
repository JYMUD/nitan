// /clone/misc/fire.c
// Last Modified by Winder on May. 15 2001

inherit ITEM;

void create()
{
        set_name("���", ({"huo ba"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ѣ����˺ڰ��ĵط�����(fire)�����ˡ�\n");
                set("unit", "��");
                set("value", 100);
        }
}
