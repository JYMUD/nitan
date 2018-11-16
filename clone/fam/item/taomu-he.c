#include <ansi.h>

inherit ITEM;

#define DANSTORE_D         "/adm/daemons/danstored"

void create()
{
        set_name(NOR + YEL "��ľ��" NOR, ({ "taomu he", "taomu", "he" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "����һ������ľ�Ƴɵĺ��ӣ�����������ŵ�ҩ����˵�����Ǵ��\n"
                                                      "�����������ĵ�ҩ���ߺ󶼲��ᶪʧ��\n" HIG
                                                                          "ָ���ʽ���洢��ҩ��  store cun ���� ��ҩID\n"
                                                                          "          ȡ����ҩ��  store qu ���� ��ҩID\n"
                                                                          "          �鿴���ӣ�  store show \n" NOR);
                set("value", 1);
                set("no_sell", 1);
                                set("no_give", 1);
                                set("no_drop", 1);

                        set("unit", "��");
        }

        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_store", "store");
}

int do_store(string arg)
{
        object me = this_player();
        string para, ob_id;
        int amount;

    // ��ȡ�����
    if (me->query_temp("apply/mask_flag"))
    {
         return notify_fail("����Ϊ�β�������Ŀʾ�ˣ�\n");
    }

        if (! arg)return notify_fail("\nδ��������������������\n");

        if (arg == "show")
        {                
                DANSTORE_D->show_player_objects(me->query("id"));
                return 1;
        }

        // �鿴���вֿ��û�
        if (arg == "list")
        {
                if (! wizardp(me))return 0;
                DANSTORE_D->show_store_list();
                return 1;
        }
        // �鿴������ҵĴ洢���
        if (sscanf(arg, "show %s", para) == 1)
        {
                if (! wizardp(me))return notify_fail("\n����������࣡\n");

                DANSTORE_D->show_player_objects(para);
                
                return 1;
        }

        if (sscanf(arg, "%s %d %s", para, amount, ob_id) != 3)
                return notify_fail("\n����������� ��\n");
        
        if (amount < 1)
                return notify_fail("\n������������С�� 1 ��\n");

        if (para == "cun")
        {
                DANSTORE_D->store_player_objects(me, ob_id, amount);
                return 1;
        }
        if (para == "qu")
        {
                DANSTORE_D->get_player_objects(me, ob_id, amount);
                return 1;        
        }
        
        return notify_fail("\n�����������\n");
}