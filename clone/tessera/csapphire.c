// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIB "細碎的藍寶石" NOR, ({ "chipped sapphire" }) ); /* NAME_EXIT  */
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIB "一片藍色的藍寶石碎片。\n" NOR); /* DBASE_EXIT  */
                set("value", 20000);
                set("unit", "顆");
                set("level", 1);
                set("material", "csapphire");
                set("can_be_enchased", 1);
                set("magic/type", "water");
                set("magic/power", 70);
                set("auto_load", 1);
        }
        set("no_identify", 1);
        setup();
}

