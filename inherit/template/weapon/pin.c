// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// axe.c
// �Զ�������ͷ�Ļ�׼�ļ���                             /* COMMENT_EXIT  */

#include <weapon.h>

inherit PIN;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("�廨��", ({ "pin", }));               /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "����һ����ͨ���廨�롣\n");/* DBASE_EXIT  */
                set("unit", "��");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(50);
        init_pin(5, 2);                                 /* FUNCTION_EXIT  */
        setup();
}