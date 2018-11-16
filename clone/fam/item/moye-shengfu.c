
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "Īаʥ��" NOR, ({ "moye fu", "moye", "fu" }) );
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "Īаʥ�����Խ���ͨ��������Ϊ������ߣ��Ժ������ʱ�ٻ�������ĵ��ߡ�\n"
                                                "ָ���ʽ�� upd <����������ID> to <������ĵ���ID> \n"
                                                                "Ŀǰ��������������������ߡ�\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "��");
        }

        setup();
}

// �����ID�Ƿ�Ϸ�
int check_legal_id(string id)
{
                int i;

                i = strlen(id);

                if ((strlen(id) < 4) || (strlen(id) > 10))
                {
                        write(WHT "\n�Բ����������ID������" HIY " 4 " NOR + WHT 
                                  "��" HIY " 10 " NOR + WHT "��Ӣ����ĸ��\n" NOR);
                        return 0;
                }

                while (i--)
        {
                        if (id[i] < 'a' || id[i] > 'z' )
                        {
                                write(WHT "\n�Բ������Ӣ������ֻ����Ӣ����ĸ��\n" NOR);
                                return 0;
                        }
        }

                return 1;
}


void init()
{
        if (this_player() == environment())
        {
                add_action("do_upd", "upd");
        }
}


// ��������Ϊ�������
// upd <Ŀ�����ID> <�������ID>
int do_upd(string arg)
{
                object me;
                string tar_id, new_id, armor_type;
                object ob;
                mapping can_summon_list;
                string *key_can_summon_list;
                string head_file; // ������Ʒ�ļ���ͷ
                string input_file; // ���д����ļ���Ϣ
                mapping armor_prop, limit;
                string *key_armor_prop, *key_limit;
                int i;

                me = this_player();

                if (! arg)return notify_fail("ָ���ʽ: upd <����������ID> to <������ĵ���ID>\n");

                if (sscanf(arg, "%s to %s", tar_id, new_id) != 2)
                        return notify_fail("ָ���ʽ: upd <����������ID> to <������ĵ���ID>\n");
                
/*
1�������жϸõ����Ƿ���ڡ�
2���õ����Ƿ�Ϊ���ߡ�
3���õ����Ƿ������
3.1 �õ����Ƿ����߲���ʧ
3.2 �õ����Ƿ�Ϊ������ߡ�
3.3 ����Ʒ��ID�Ƿ�Ϸ���ȫΪӢ������
3.4 ����Ʒ��ID�Ƿ�������������ƷID�ظ���can_summon)��
*/
        // �����жϸõ����Ƿ����
                if (! objectp(ob = present(tar_id, me)))
                        return notify_fail("�����Ϻ���û�������Ʒ�ɣ�\n");

                // ���ob�Ƿ�Ϊ����
                if (! stringp(armor_type = ob->query("armor_type")))
                        return notify_fail("�Բ���ֻ��������������Ʒ��\n");

                // �õ����Ƿ������
                // �õ����Ƿ����߲���ʧ
                if (! ob->query_autoload())
                        return notify_fail("��ֻ���������߲���ʧ����Ʒ��\n");
                
                // �õ����Ƿ�Ϊ�������
                if (ob->is_item_make())
                        return notify_fail("������Ʒ����������\n");                

                // 
                if (ob->query("no_upd"))
                        return notify_fail("��������Ʒ����������\n");
                        
                // ����Ʒ��ID�Ƿ�Ϸ���ȫΪӢ����
                if (! check_legal_id(new_id))return 1;
                                                
                // ����Ʒ��ID�Ƿ�������������ƷID�ظ���can_summon)
                can_summon_list = me->query("can_summon");

                if (mapp(can_summon_list))
                {
                        if (sizeof(can_summon_list))
                        {
                                key_can_summon_list = keys(can_summon_list);

                                if (member_array(new_id, key_can_summon_list) != -1)
                                {
                                        return notify_fail("�������ID�����ظ��������� summon �鿴���е�ID����\n");
                                }
                        }
                }
                
                // �����ѫ�������������� xxx(id)
                if (ob->query("armor_type") == "medal" ||
                    ob->query("armor_type") == "medal2")
                {
                        ob->set("long", ob->query("long") + 
                                        HIC "ֻ��ѫ�µı�Ե����һ��С�֣�������� " + me->name() + HIC + "(" + me->query("id") + ")\n" NOR);
                }


/*
4����������
4.1 ���ݵ�����������������ݣ���д���ļ���
4.2 ���ø����can_summon ���ݡ�
4.3 destruct �õ��ߺ��������ߣ�����ʾsummon
*/

                // 4����������
                // 4.1 ���ݵ�����������������ݣ���д���ļ���
                head_file = 
                "\n"
                "#include <ansi.h>\n"
                "#include <armor.h>\n"
                "\n"
                "inherit ==ARMOR_TYPE==;\n"
                "inherit F_ITEMMAKE;\n"
                "\n"
                "void create()\n"
                "{\n"
                "\tset_name(==ARMOR_NAME==, ({ ==ARMOR_ID== }));\n"
                "\tset_weight(==ARMOR_WEIGHT==);\n"
                "\tset(\"item_make\", 1);\n"
                "\tset(\"unit\", ==ARMOR_UNIT==);\n"
                "\tset(\"long\", ==ARMOR_LONG==);\n"
                "\tset(\"value\", ==ARMOR_VALUE==);\n"
                "\tset(\"point\", ==ARMOR_POINT==);\n"
                "\tset(\"material\", ==ARMOR_MATERIAL==);\n";
                if (ob->query("wear_msg"))
                {
                        head_file += "\tset(\"wear_msg\", \"" + ob->query("wear_msg") + "\");\n";
                }
                if (ob->query("remove_msg"))
                {
                        head_file += "\tset(\"remove_msg\", \"" + ob->query("remove_msg") + "\");\n";
                }
                head_file += "\tif (! check_clone()) return;\n";
                head_file += "\trestore();\n";

                // �滻head_file������
                // 1. ==ARMOR_TYPE== ��������
                //    ==ARMOR_ID==
                head_file = replace_string(head_file, "==ARMOR_TYPE==", upper_case(armor_type));
                head_file = replace_string(head_file, "==ARMOR_ID==", "\"" + new_id + "\"");
                // 2. ==ARMOR_NAME== ����
                head_file = replace_string(head_file, "==ARMOR_NAME==", "\"" + ob->name() + "\"");
                // 3. ==ARMOR_WEIGHT==
                head_file = replace_string(head_file, "==ARMOR_WEIGHT==", sprintf("%d", ob->query_weight()));
                // 4. ==ARMOR_UNIT==
                head_file = replace_string(head_file, "==ARMOR_UNIT==", "\"" + ob->query("unit") + "\"");
                // 5. ==ARMOR_LONG==
                head_file = replace_string(head_file, "==ARMOR_LONG==", "\"" + (ob->query("long") ? ob->query("long") : ob->query("name")) + "\\n\"");
                // 6. ==ARMOR_VALUE==
                head_file = replace_string(head_file, "==ARMOR_VALUE==", sprintf("%d", ob->query("value")));
                // 7. ==ARMOR_POINT==
                head_file = replace_string(head_file, "==ARMOR_POINT==", sprintf("%d", ob->query("armor_prop/armor") * 5 / 6));
                // 8. ==ARMOR_MATERIAL==
                head_file = replace_string(head_file, "==ARMOR_MATERIAL==", ob->query("material") ? 
                                                                            "\"" + ob->query("material") + "\"" : 
                                                                                "\"" +  "steel" + "\"");
                        
                // 11.���õ��ߵ�armor_pro
                armor_prop = ob->query("armor_prop");
                
                key_armor_prop = keys(armor_prop);
                input_file = head_file;
                if (sizeof(key_armor_prop))
                {                
                        for (i = 0; i < sizeof(key_armor_prop); i ++ )
                        {
                                if (key_armor_prop[i] == "armor")continue;                                
                                
                                // ���Ϊ����� ����ʱ��д��fy&qyֵ����ѭ���󵥶�д��
                                if (ob->query("armor_type") == "myheart" || 
                                    ob->query("armor_type") == "myheart2")
                                {
                                        if (key_armor_prop[i] =="fy" || key_armor_prop[i] == "qy")
                                                continue;
                                }

                                input_file += "\tset(\"armor_prop/" + key_armor_prop[i] + "\", ";
                                                                
                                if (stringp(armor_prop[key_armor_prop[i]]))
                                        input_file += armor_prop[key_armor_prop[i]] + ");\n";
                                else                                        
                                        input_file += sprintf("%d", armor_prop[key_armor_prop[i]]) + ");\n";
                        } 
                        
                        // ����д�븣Ե�����˵ļ��㹫ʽ
                        if (ob->query("armor_type") == "myheart" || 
                            ob->query("armor_type") == "myheart2")
                        {
                                input_file += "\tset(\"armor_prop/fy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/fy")) + " + f_enchase_points(0));\n";
                                input_file += "\tset(\"armor_prop/qy" + "\", ";
                                input_file += sprintf("%d", ob->query("armor_prop/qy")) + " + f_enchase_points(1));\n";                                
                        }
                
                }
                input_file += "\tset(\"armor_prop/armor\", apply_armor());\n";
                // �����armor_prop����װ����������
                input_file += "\tset(\"armor_prop/can_wear\", 1);\n";

                // 12. ���õ���limit��Ϣ
                limit = ob->query("limit");
                if (mapp(limit))key_limit = keys(limit);
                if (sizeof(key_limit))
                {
                        for (i = 0; i < sizeof(key_limit); i ++ )
                        {
                                input_file += "\tset(\"limit/" + key_limit[i] + "\", ";
                                input_file += sprintf("%d", limit[key_limit[i]]) + ");\n";
                        }                        
                }

                input_file += "\n\tsetup();\n";
                input_file += "}\n\n";
                input_file += "string long() { return query(\"long\") + item_long(); }\n\n";

                // д���ļ�
                if (! ITEM_D->extern_write_file("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c",
                                              input_file, 
                                                                  1) )
                {
                        return notify_fail("����ʧ�ܣ�д���ļ��쳣��\n");
                }                                

                // ���µ���
                load_object("/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");

                // ��¼
                log_file("moyefu", me->query("id") + " �� " + ctime(time()) + " ʹ��Īа������ " + new_id + "��\n");
                
                // ����CAN_SUMMON
                me->set("can_summon/" + new_id, "/data/item/" + me->query("id")[0..0] + "/" + me->query("id") + "-" + new_id + ".c");
                me->save();

                // ��ʾ
                write(HIG "������ϣ�������ָ�� summon " + new_id + " �ٻ����������Ʒ��\n" NOR);

                destruct(ob);
                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
