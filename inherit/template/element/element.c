// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit ITEM;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(YEL "Ԫ��" NOR, ({ "element" }));              /* NAME_EXIT  */
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", YEL "�������ˮ���д�ȡ������Ԫ�ط�ĩ��\n" NOR); /* DBASE_EXIT  */
                set("value", 100);
                set("unit", "��");
        }
        setup();
}

