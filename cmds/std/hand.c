// drop.c

#include <weapon.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, old;
        object weapon;
        string str;

        if (! arg)
                return notify_fail("��Ҫ�ó�ʲô������\n");

        if (arg == "none" || arg == "nothing")
        {
                if( !objectp(ob=query_temp("handing", me)) )
                        return notify_fail("�㱾����ʲô��û���ð���\n");

                if( !stringp(str=query("unhand_msg", ob)) )
                        str = "$N��$n�ջذ��ҡ�\n";
                message_vision(str, me, ob);
                delete_temp("handing", me);
                return 1;
        }

        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û������������\n");
                
        if( ob->is_pet() || ob->is_warcraft() || query("ridable", ob) )
                return notify_fail("����������ﲻ�����������ϡ�\n");
                
        if( objectp(old=query_temp("handing", me)) )
        {
                if (old == ob)
                        return notify_fail("�㲻������������\n");

                if( !stringp(str=query("unhand_msg", old)) )
                        str = "$N�ջ����е�$n��\n";
                message_vision(str, me, old);
                delete_temp("handing", me);
        }

        if( (ob->query_amount()?query("base_weight", ob):ob->query_weight())>20000 )
                return notify_fail(ob->name() + "̫���ˣ��㵥���ò�ס��\n");

        weapon=query_temp("weapon", me);
        if (weapon &&
            ((query("flag", weapon))&TWO_HANDED || 
             query_temp("secondary_weapon", me) || 
             query_temp("armor/hands", me) || 
             query_temp("armor/finger", me)) )
        {
                // none of two hand is free
                return notify_fail("��˫�ֶ�����������û�а취"
                                   "������" + ob->name() + "�ˡ�\n");
        }

        if( query_temp("armor/hands", me) && 
            query_temp("armor/finger", me) )
        {
                // none of two hand is free
                return notify_fail("��˫�ֶ�����������û�а취"
                                   "������" + ob->name() + "�ˡ�\n");
        }
        if( query("equipped", ob) )
                return notify_fail("����װ�������أ�\n");

        set_temp("handing", ob, me);
        if( !stringp(str=query("hand_msg", ob)) )
                str = "$N�ó�" + (old && ob->name() == old->name() ? "����" : "") +
                      // "һ" + (ob->query_amount() ? ob->query("base_unit")
                      "һ"+(ob->query_amount()?query("unit", ob )
                                                 :query("unit", ob))+
                      "$n���������С�\n";
        message_vision(str, me, ob); 
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : hand <��Ʒ����> | nothing
 
���ָ����������ó�һ������Я������Ʒ����ʱ׼��ʹ�á�
 
HELP );
    return 1;
}
 
