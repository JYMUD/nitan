// /u/hotjc/dzt.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "����̨" NOR, ({ "dazao tai", "tai" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
          set("long", HIG @LONG
����һ�����졢���졢ǿ��������װ���Ĵ���̨��
��Ƕ��Ʒ              enchase
��ħ����              enchant
װ�����              notch
��ʯ�ϲ�              combine
ϴ װ ��              melt
װ��ǿ��              steady
װ������              increase
װ������              forging
LONG NOR );
                set("value", 2000);
                set("unit", "Ƭ");
                set("no_get", 1);
                set("auto_load", 1);
        }
        setup();
}