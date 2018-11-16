// wear.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
        object ob, *inv;
        int i, count;

        if (! arg) return notify_fail("��Ҫ����ʲô��\n");

        if (arg == "all")
        {
                inv = all_inventory(me);
                for(count = 0, i = 0; i < sizeof(inv); i++)
                {
                        if( query("equipped", inv[i]))continue;
                        if (do_wear(me, inv[i])) count++;
                }
                if (! count)
                        write("��ʲô��û�д��ϡ�\n");
                else
                        write("�㴩���ˡ�\n");
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û������������\n");

        if( query("equipped", ob) )
        {
                inv = all_inventory(me) - ({ ob });
                for(count = 0, i = 0; i < sizeof(inv); i++)
                {
                        if (! inv[i]->id(arg)) continue;
                        if( query("equipped", inv[i]))continue;
                        if (do_wear(me, inv[i]))
                        {
                                count++;
                                break;
                        }
                }
                if (! count)
                        return notify_fail("���Ѿ�װ�����ˡ�\n");

                return 1;
        }

        return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
        string str;
        mapping p;
        mixed notice;

        if( notice=query_temp("no_wear", ob) )
        {
                if (stringp(notice)) write(notice);
                return notify_fail("�������Ա�İɣ�\n");
        }

        if( query("female_only", ob) && 
            query("gender", me) == "����" )
                return notify_fail("����Ů�˵���������һ��������Ҳ�봩����Ҳ���ߣ�\n");

        switch (ob->wear())
        {
        case 0:
                return 0;

        case -1:
                if (me->is_fighting())
                        me->start_busy(1);
                return 1;

        default:
                if( !stringp(str=query("wear_msg", ob)) )
                        switch(query("armor_type", ob) )
                        {
                                case "cloth":
                                case "armor":
                                case "boots":
                                        str=YEL"$N����һ"+query("unit", ob)+"$n"YEL"��\n"NOR;
                                        break;
                                case "head":
                                case "neck":
                                case "wrists":
                                case "hands":
                                        str=YEL"$N����һ"+query("unit", ob)+"$n"YEL"��\n"NOR;
                                        break;
                                case "waist":
                                        str=YEL"$N��һ"+query("unit", ob)+"$n"YEL"�������䡣\n"NOR;
                                        break;
                                default:
                                        str = YEL "$Nװ��$n" YEL "��\n" NOR;
                        }
                if( query_temp("daub", ob) && 
                    query("armor_type", ob) != "hands" )
                        DAUB_CMD->check_poison(me, ob);

                message_vision(str, me, ob);
                if (me->is_fighting())
                        me->start_busy(1);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ��wear <װ������>
 
���ָ������װ��ĳ�����ߡ�
 
HELP );
        return 1;
}
