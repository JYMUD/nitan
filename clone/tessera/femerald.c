// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIG "ϡ�������" NOR, ({ "flawless emerald" }) );   /* NAME_EXIT  */
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIG "һ�����������ױȵĴ���䡣\n" NOR);  /* DBASE_EXIT  */
                set("value", 100000);
                set("unit", "��");
                set("level", 3);
                set("material", "femerald");
                set("can_be_enchased", 1);
                set("magic/type", "wood");
                set("magic/power", 200);
                set("auto_load", 1);
        }
        set("no_identify", 1);
        setup();
}

