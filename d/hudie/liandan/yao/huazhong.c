#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(NOR"�ʻ�����"NOR, ({ "hua zhong"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "��ͨ���ʻ����ѣ���֪���Ὺ��ʲô���Ļ�����\n");
                set("unit", "��"); 
                set("no_get",1);
                set("no_put",1);
                set("no_give",1);   
                set("value",50000);
        }
    setup();
}