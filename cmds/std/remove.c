// remove.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_remove(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i;
        int count;

        if (! arg) return notify_fail("��Ҫ�ѵ�ʲô��\n");

        if (arg == "all")
        {
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++)
                        count += do_remove(me, inv[i]);
                if (count)
                        write("�������ˡ�\n");
                else
                        write("��ʲô��û����������\n");
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û������������\n");

        if( query("equipped", ob) != "worn" )
        {
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++) {
                        if( !inv[i]->id(arg) )
                                continue;

                        if( query("equipped", inv[i]) != "worn" )
                                continue;

                        ob = inv[i];
                        count++;
                        break;
                }

                if (! count)
                        return notify_fail("�㲢û��װ������������\n");
        }

        return do_remove(me, ob);
}

int do_remove(object me, object ob)
{
        string str;

        if( query("equipped", ob) != "worn" )
                return notify_fail("�㲢û��װ������������\n");

        if (ob->unequip())
        {
                if( !stringp(str=query("remove_msg", ob)) )
                        switch(query("armor_type", ob)){
                                case "cloth":
                                case "armor":
                                case "surcoat":
                                case "boots":
                                        str = YEL "$N��$n" YEL "����������\n" NOR;
                                        break;
                                case "bandage":
                                        str = YEL "$N��$n" YEL "���˿ڴ�����������\n" NOR;
                                        break;
                                default:
                                        str = YEL "$Nж��$n" YEL "��װ����\n" NOR;
                        }
                if( query_temp("no_wear", ob) )
                        str += "����" + ob->name() + "�Ժ������������ˡ�\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : remove all | <��Ʒ����>
 
���ָ�������ѵ�����ĳ������.
 
HELP );
        return 1;
}
 