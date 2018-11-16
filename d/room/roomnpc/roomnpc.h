// major function of room's npc

#define GOLDS  10000
#include <ansi.h>

int is_owner(object ob)
{
        if( query("id", ob) == query("room_owner_id", environment()) || 
            query("couple/couple_id", ob) == query("room_owner_id", environment()) )
                return 1;

        return 0;
}

int is_owner_permit(object ob)
{
        string *vip;

        if (query_temp("permit_enter/" + query("room_owner_id",environment()),ob)) 
                return 1;

        if (objectp(present(query("room_owner_id",environment()) + " pass", ob))) 
                return 1;

        vip=query("vip", this_object());
        if (vip && sizeof(vip) && member_array(query("id",ob),vip) != -1) 
                return 1;

        return 0;
}

int owner_is_present()
{
        string id;

        if( present(id=query("room_owner_id", environment())) )
                return 1;

        return 0;
}

int do_invite(string arg)
{
        object ob;
        object me;

        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        if (! arg || ! objectp(ob = present(arg, environment())))
                return notify_fail("��Ҫ����˭��\n");

        if (! ob->is_character())
                return notify_fail("������������������������·����\n");

        if( !query("can_speak", ob) )
                return notify_fail("����˼����������û�������һ�����ˡ���\n");

        if (ob == me)
                return notify_fail("��Ҫ�������Լ����뷨������ϧû���á�\n");

        if (is_owner(ob))
                return notify_fail("����Ҳ������������ˣ���ʲô������ģ�\n");

        if (! userp(ob))
                return notify_fail("�����㻹�Ǳ������ˡ�\n");

        me = this_player();
        message_vision("$Nָ��" + ob->name() + "��$n������������������"
                       "���ˣ���ɲ�Ҫ�����ˣ���\n$n��æ��ͷ����������"
                       "֪���ˣ�֪���ˣ���λ" + RANK_D->query_respect(ob) +
                       "��С�����в��ܾ����ᣡ��\n", me, this_object());
        set_temp("permit_enter/"+query("id", me), 1, ob);
        return 1;
}

int do_show(string arg)
{
        object ob;
        object me;
        string msg;

        if (! arg)
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");
 
        msg="$N����һ"+query("unit", ob)+ob->name()+"\n";
       if (! ob->id(query("room_owner_id",environment()) + " pass")) 
                msg += "����$n��û����$n��\n";
        else
                if (is_owner_permit(me))
                        msg += "$n������Ц����$N������ʧ����ʧ������\n";
                else
                {
                        msg += "$nһ����������Ц����$N������ԭ����" +
                               environment(query("room_owner", ))+
                               "�����ѣ�ʧ����ʧ������\n";
                        me->set_temp("permit_enter/"+
                                     environment(query("room_ownerid", )),1);
                }
        message_vision(msg, me, this_object());
        return 1;
}

int list_vip()
{
        object ob;
        int i;
        string msg,*vip;

        if (!is_owner(this_player()))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        ob = this_object();

        vip=query("vip", ob);
        if (!vip || sizeof(vip) < 1)
        {
                msg = "����û�ж����κεĹ����\n";
                msg += "������ͨ��vip <id>����ӹ����ͨ��vip <id> -c����������\n";
                return notify_fail(msg);
        }
        msg = HIY "��������Ĺ����������ң�\n" NOR;
        msg += "------------------------------\n";
        for (i = 0;i < sizeof(vip);i++)
        {
                msg += sprintf(HIY"%s\n"NOR, vip[i]);
        }
        msg += "------------------------------\n";

        msg += HIY "�ܹ�" + sizeof(vip) + "�������\n" NOR;
        msg += HIY "������ͨ��vip <id>����ӹ����ͨ��vip <id> -c����������\n" NOR;
        write(msg);
        return 1;
}

int do_vip(string arg)
{
        string *vip;
        object ob,me;
        int num;
        
        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        if (!arg)
                return notify_fail("������ͨ��vip <id>����ӹ����ͨ��vip <id> -c����������\n");

        vip=query("vip", ob);
        if (!vip) vip = ({});

        if (sscanf(arg,"%s -c",arg) == 1)
        {
                if (member_array(arg,vip) == -1)
                        return notify_fail(ob->name(1) + "����Ц��˵��" + arg + "�����Ͳ������Ĺ������\n");
                vip -= ({arg});
                set("vip", vip, ob);
                ob->save();
                write(ob->name(1) + "��ͷ��������˵���յ����յ������Ժ�" + arg + "�������Ĺ���ˡ�\n");
                return 1;
        }

        if( sizeof(vip) >= query("max_vip", ob) )
                return notify_fail(ob->name(1) + "������˵�������Ĺ��̫���ˣ���ū��ʵ���Ǽǲ�ס����\n");

        if( arg == query("id", me) )
                return notify_fail(ob->name(1) + "һ�����£�սս������˵���������˰�����ū���ҵ����ǿ��ˣ�\n");

        if (member_array(arg,vip) != -1)
                return notify_fail(ob->name(1) + "����Ц��˵��" + arg + "�������Ѿ������Ĺ������\n");

        vip += ({ arg });
        set("vip", vip, ob);
        ob->save();
        write(ob->name(1) + "������Ц����ͷ��������" + arg + "��Ȼ����������Ժ�һ�����У�\n");
        return 1;
}

int add_force()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        if( query("max_jing", ob) >= 1000000 || query("max_qi", ob) >= 1000000
             || query("max_neili", ob) >= 1000000 )
                return notify_fail("���͵ľ������������Ѿ����������ˡ�\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),100000000) )
#else
        if( query("balance", me)<100000000 )
#endif
                return notify_fail("��Ĵ��㡣\n");

        addn("balance", -10000*GOLDS, me);
        addn("max_qi", 2000, ob);
        addn("max_jing", 2000, ob);
        addn("max_jingli", 2000, ob);
        addn("max_neili", 2000, ob);
        addn("qi", 2000, ob);
        addn("jing", 2000, ob);
        addn("jingli", 2000, ob);
        addn("neili", 2000, ob);

        ob->save();
        message_vision("ֻ��$N���Ϻ��������֣�" +
                "˲���ָֻ�ƽ����\n", ob);
        tell_object(me, "���͵ľ����������������ɹ���\n");
        return 1;
}

int add_skill()
{
        object ob, me;
        int oldlvl;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        oldlvl = ob->query_skill("force", 1);

#ifdef LONELY_IMPROVED
        if( count_lt(query("balance", me),count_mul(oldlvl,200000)) )
#else
        if( query("balance", me)<oldlvl*200000 )
#endif
                return notify_fail("��Ĵ��㡣\n");

        addn("balance", -oldlvl*20*GOLDS, me);
        ob->set_skill("force", oldlvl + 100);
        ob->set_skill("parry", oldlvl + 100);
        ob->set_skill("dodge", oldlvl + 100);
        ob->set_skill("strike", oldlvl + 100);
        ob->set_skill("claw", oldlvl + 100);
        ob->set_skill("jiuyang-shengong", oldlvl + 100);
        ob->set_skill("lingbo-weibu", oldlvl + 100);
        ob->set_skill("qiankun-danuoyi", oldlvl + 100);
        ob->set_skill("jiuyin-baiguzhao", oldlvl + 100);
        ob->set_skill("cuixin-zhang", oldlvl + 100);
        ob->set_skill("martial-cognize", oldlvl + 100);
        ob->set_skill("count", oldlvl + 100);

        ob->save();
        message_vision("��Ȼ������$Nȫ��Ĺ�������������һ���죬" +
                "˲���ָֻ�ƽ����\n", ob);
        tell_object(me, "���͵��书�����ɹ���\n");
        return 1;
}

int buy_vip()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),2000*GOLDS) )
#else
        if( query("balance", me)<2000*GOLDS )
#endif
                return notify_fail("��Ĵ��㡣\n");

        addn("balance", -2000*GOLDS, me);
        addn("max_vip", 1, ob);

        ob->save();
        tell_object(me, "�ɹ�����һ��VIP���\n");
        tell_object(me,sprintf("�ֹ���%d��VIP���\n",query("max_vip", ob)));
        return 1;
}

int add_hujiu()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("������ֵ��ʣ�����˭��ƾʲô����ָ�ֻ��ŵģ�\n");

        if( query("can_hujiu", ob) )
                return notify_fail("�����Ѿ��Ը����ˣ���ū�������ǡ�\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),3000*GOLDS) )
#else
        if( query("balance", me)<30000*GOLDS )
#endif
                return notify_fail("��Ĵ��㡣\n");

        addn("balance", -30000*GOLDS, me);
        set("can_hujiu", 1, ob);

        ob->save();
        tell_object(me, "���˷��ģ���ū��ס�ˣ�\n");
        return 1;
}
