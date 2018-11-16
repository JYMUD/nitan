// unwield.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob, *inv;
        string str;
        int i;
        int count;

        if( !arg ) return notify_fail("��Ҫ����ʲô��\n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( query("equipped", ob) != "wielded"){
                inv = all_inventory(me);
                for (count = 0, i = 0; i < sizeof(inv); i++) {
                        if( !inv[i]->id(arg) )
                                continue;

                        if( query("equipped", inv[i]) != "wielded" )
                                continue;

                        ob = inv[i];
                        count++;
                        break;
                }

                if( !count )
                        return notify_fail("�㲢û��װ������������Ϊ������\n");
        }

        if( ob->unequip() ) {
                if( !stringp(str=query("unwield_msg", ob)) && !stringp(str=ob->do_unwield()) )
                        str = "$N�������е�$n��\n";
                message_vision(str, me, ob);
                return 1;
        } else
                return 0;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : unwield <��Ʒ��>
 
���ָ������������е�������
 
HELP
    );
    return 1;
}
 
