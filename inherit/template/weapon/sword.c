// $file_name.c                                         /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                         /* COMMENT_ENTRY */
// sword.c
// �Զ��������Ļ�׼�ļ���                               /* COMMENT_EXIT  */

#include <weapon.h>

inherit SWORD;

#include <template/weapon.h>

void create()
{
//**    set_name("$name", ({ "$id", }));                /* NAME_ENTRY */
        set_name("��", ({ "sword", }));                 /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");    /* DBASE_ENTRY */
                set("long", "����һ����ͨ�ĳ�����\n");  /* DBASE_EXIT  */
                set("unit", "��");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }

//**    $function_name($argument);                      /* FUNCTION_ENTRY */
        set_weight(5000);
        init_sword(5, 2);                               /* FUNCTION_EXIT  */
        setup();
}

