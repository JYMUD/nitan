// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// armor.c
// �Զ��������ߵĻ�׼�ļ���                             /* COMMENT_EXIT  */

#include <armor.h>
inherit RINGS;

#include <template/armor.h>
void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("��ָ", ({ "ring", }));                /* NAME_EXIT  */ 

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "����һö��ͨ�Ľ�ָ��\n");  /* DBASE_EXIT  */
                set("unit", "ö");
                set("value", 200);
                set("material", "gold");
                set("armor_prop/armor", 1);
        }

        set_weight(200);
        setup();
}
