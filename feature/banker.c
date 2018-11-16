// banker.c
// Rewritten by Lonely@XYZX (16/05/2009)

#include <ansi.h>

#ifndef STORAGE_D
#define STORAGE_D "/adm/daemons/storaged"
#endif


#define REBOOT_CMD      "/cmds/arch/reboot"

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)query("balance", this_player());
        if( !total || total < 0) {
                set("balance", 0, this_player());
                write("���ڱ��̺�û�д�Ǯ��\n");
                return 1;
        }
        write(query("name")+"���ĸ����㣺���ڱ��̺Ź�����" +
              MONEY_D->money_str(total) + "��\n");
        return 1;
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3 )
                return notify_fail("�����ʽ��convert|duihuan <����> <���ҵ�λ> to <�»��ҵ�λ>\n");

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if( !to_ob && file_size("/clone/money/" + to + ".c") < 0 )
                return notify_fail("����һ���ʲô��\n");

        if( !from_ob )
                return notify_fail("������û�д�����Ǯ��\n");

        if( from_ob == to_ob )
                return notify_fail("����ë������\n");

        if( amount < 1 )
                return notify_fail("�����׬����\n");

        if( (int)from_ob->query_amount() < amount )
                return notify_fail("�����" + query("name", from_ob) + "������\n");

        bv1 = query("base_value", from_ob);
        if( !bv1 )
                return notify_fail("����������ֵǮ��\n");

        bv2 = to_ob ? query("base_value", to_ob)
                    : query("base_value", get_object("/clone/money/" + to));

        if( !bv2 )
                return notify_fail("����������ֵǮ��\n");

        if( bv1 < bv2 )  amount -= amount % (bv2 / bv1);
        if( amount == 0 )
                return notify_fail("��Щ" + query("name", from_ob) +
                                   "��������\n ");

        if( bv1 > bv2 && bv1 / bv2 * amount > 20000 )
                return notify_fail("Ŷ��...����һ���ӻ��ò�����ô��ɢǮ...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if( !to_ob ) {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        } else  to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N������ȡ��%s%s%s��������%s%s%s��\n",
                chinese_number(amount),
                query("base_unit", from_ob),
                query("name", from_ob),
                chinese_number(amount * bv1 / bv2),
                query("base_unit", to_ob),
                query("name", to_ob)), me);

        return 1;
}

int do_deposit(string arg)
{
        string what;
        int amount;
        object what_ob, me;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( !arg || (sscanf(arg, "%d %s", amount, what) != 2 &&
            sscanf(arg, "all %s", what) != 1) )
                return notify_fail("�����ʽ��deposit:cun <����>|all <���ҵ�λ>\n");

        what_ob = present(what + "_money", me);
        if( !what_ob )
                return notify_fail("������û�д�����Ǯ��\n");

        if( !amount ) amount = what_ob->query_amount();
        if( amount < 1 )
                return notify_fail("��������" + query("name", what_ob) + "��\n");

        if( (int)what_ob->query_amount() < amount )
                return notify_fail("�����" + query("name", what_ob) + "������\n");

        // deposit it
        me->start_busy(1);

        addn("balance", query("base_value", what_ob) * amount, me);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        MYGIFT_D->check_mygift(me, "newbie_mygift/cunqian"); 
        return 1;
}

int do_withdraw(string arg)
{
        string what, t;
        int amount;
        object what_ob, me;
        int v;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( !arg || sscanf(arg, "%d %s", amount, what) != 2 )
                return notify_fail("�����ʽ��withdraw|qu <����> <���ҵ�λ>\n");

        if( amount < 1 )
                return notify_fail("����ȡ������Ǯ��\n");

        if( amount >= 10000 )
                return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("����ȡ��ʲôǮ��\n");

        t = "/clone/money/" + what;
        if( (v = amount * query("base_value", get_object(t))) > query("balance", me) || v <= 0 )
               return notify_fail("����Ǯ����ȡ��\n");

        me->start_busy(1);

        what_ob = new(t);
        what_ob->set_amount(amount);
        if( me->query_encumbrance() + what_ob->query_weight() > me->query_max_encumbrance() )
        {
                tell_object(me, "��ĸ��ز������޷��ö���ô��Ǯ��\n");
                destruct(what_ob);
                return 1;
        }
        what_ob->move(me, 1);
        addn("balance",  -v, me);
        //MONEY_D->pay_player(me, v, what);

        //message_vision(sprintf("$N��������ȡ��%s��\n", MONEY_D->money_str(v)), me);
        message_vision(sprintf("$N��������ȡ��%s%s%s��\n",
                chinese_number(amount), query("base_unit", what_ob),
                query("name", what_ob)), me);

        me->save();
        return 1;
}

int do_transfer(string arg)
{
        string who, what;
        int value;
        object me, ob;
        int amount;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( REBOOT_CMD->is_rebooting() )
                return notify_fail("���ڱ�վ����׼��������������Ǯׯ��ͣת�ʹ��ܡ�\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, what, who) != 3 )
                return notify_fail("�����ʽ��transfer|zhuan <����> <���ҵ�λ> to <ĳ��>\n");

        if( amount < 1 )
                return notify_fail("����ת�ʶ���Ǯ��\n");

        if( amount > 10000000 )
                return notify_fail("��ô�����Ŀ����ϴǮ�����ɣ�����ɲ��ҷ�����\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("����ת��Ǯ�ĵ�λ�ǣ�\n");

        what = "/clone/money/" + what;
        value = amount*query("base_value", get_object(what));

        if( value > query("balance", me) || value <= 0 )
               return notify_fail("����Ǯ����ת�ʡ�\n");

        if( !objectp(ob = UPDATE_D->global_find_player(who)) )
                return notify_fail("û������ˣ�\n");

        me->start_busy(1);

        addn("balance", -value, me);
        addn("balance",  value, ob);
        me->save();
        ob->save();
        tell_object(ob, "\a", 0);
        tell_object(ob, HIR + me->query_idname(1) + HIR "�������ﻮת"+ MONEY_D->money_str(value) + "������ʻ��ϡ�\n" NOR);
        tell_object(me, HIR "��������ﻮת"+ MONEY_D->money_str(value) + "��" + ob->query_idname(1) + HIR "���ʻ��ϡ�\n" NOR);
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

//�����ҵ��
int do_cw(string arg)
{
        string cmd;
        object me = this_player();
        if( !arg || arg=="" ) {
                write("��ʹ��cw help����ѯʹ�ð�����\n");
                return 1;
        }
        arg = lower_case(arg);
        if( arg == "help" || arg == "cancel" || arg == "list" )
                cmd = arg;
        else if( sscanf(arg,"%s %s",cmd,arg) != 2 ) {
                //dohelp2
                write("��ʹ��cw help����ѯʹ�ð�����\n");
                return 1;
        }
        switch( cmd ) {
        case "open":    //���ʻ�
                STORAGE_D->OpenAccount(me,arg);
                break;
        case "put":
                STORAGE_D->PutObject(me,arg);
                break;
        case "get":
                STORAGE_D->GetObject(me,arg);
                break;
        case "fee":
                STORAGE_D->DoFee(me,arg);
                break;
        case "list":
                STORAGE_D->ListObject(me);
                break;
        case "cancel":
                STORAGE_D->CancelAccount(me);
                break;
        case "help":
                STORAGE_D->ShowHelp(me);
                break;
        default:
                write("����Ҫ��ʲô��������ʹ��cw help���鿴һ�°����ɣ�\n");
        }
        return 1;
}
