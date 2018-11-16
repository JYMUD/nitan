// ��ĺ� ҩ��ׯҽ��ʩ���ĵ��ߡ�

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( CYN "��ĺ�" NOR , ({"zhenjiu he", "zhenjiu", "box"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN"����һ����ĺУ���ҩ���ȵ���ҽ�ƺ�ʩ���Ĺ��ߡ�\n"
                                "       xiadu   �¶�\n"
                                "       heal    ����\n"
                                "       jiedu   �ⶾ\n"NOR);
                set("unit", "��");
//              set("no_get", 1);
//              set("no_sell", 1);
//              set("no_drop", 1);
//              set("no_give", 1);
                set("value", 0);
                set("weight", 100);
        }
}

void init()
{
        add_action("do_xiadu", "xiadu"); //�¶�
        add_action("do_heal", "heal"); //����
        add_action("do_jiedu", "jiedu"); //�ⶾ
}

int do_heal(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "ҩ����" )
                return notify_fail("�㲻��ʹ�������ĺУ�\n");

        if( query("shen", me)<0 )
                return notify_fail("�㲻��ʹ������ܣ�\n");

        if( !arg )
                return notify_fail("ָ���ʽ��heal <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ�\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("��̫���ˣ�����Ϣһ�°ɣ�\n");

        if( query("max_qi", ob) >= (query("eff_qi", ob)+(i*2))){
                set("max_qi", (query("eff_qi", ob)+(i*2)), ob);
        } else { set("eff_qi",(query("max_qi",ob)),ob); } 

        message_vision(CYN"$N����ĺ����ó�һ��������$nѨλ�����˼��¡�\n"NOR, me, ob);
        message_vision(WHT"$N�³�һ����Ѫ����ɫ�������ö��ˡ�\n"NOR, ob);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
        addn("jing", -i, me);
        me->start_busy(3);
        return 1;
}

int do_xiadu(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "ҩ����" )
                return notify_fail("�㲻��ʹ�������ĺУ�\n");

        if( query("shen", me)>0 )
                return notify_fail("�㲻��ʹ������ܣ�\n");

        if( (query("no_fight", environment(me))) )
                return notify_fail("�����ֹս����\n");

        if( !arg )
                return notify_fail("ָ���ʽ��xiadu <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ�\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("��̫���ˣ�����Ϣһ�°ɣ�\n");

        message_vision(HIR"$N���ᰴ��һ����ĺС�ͻȻ�Ӻ��������֧"
                HIW"����"HIR"��������$n���ϡ�\n"NOR, me, ob);
        ob->receive_damage("qi",(int)me->query_skill("medical",1));
        if(random(10)<5)
        {
        ob->apply_condition("ill_dongshang", ((int)me->query_condition("ill_dongshang")+i));
        } 
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_fashao", ((int)me->query_condition("ill_fashao")+(i*10)));
        }
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_kesou", ((int)me->query_condition("ill_kesou")+(i*10)));
        }
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_shanghan", ((int)me->query_condition("ill_shanghan")+(i*10)));
        }
        else
        {
        ob->apply_condition("ill_zhongshu", ((int)me->query_condition("ill_zhongshu")+(i*10)));
        }
        
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
        me->improve_skill("poison", ((int)me->query_skill("poison",1)));
        addn("jing", -i, me);
        me->start_busy(3);
                if(random(me->query_skill("medical",1))<50) {
                        ob->kill_ob(me); }
        return 1;
}

int do_jiedu(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "ҩ����" )
                return notify_fail("�㲻��ʹ�������ĺУ�\n");

        if( query("shen", me)>0 )
                return notify_fail("�㲻��ʹ������ܣ�\n");

        if( !arg )
                return notify_fail("ָ���ʽ��jiedu <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ�\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("��̫���ˣ�����Ϣһ�°ɣ�\n");

        message_vision(CYN"$N����ĺ����ó�һ��������$nѨλ�����˼��¡�\n"NOR, me, ob);

//�� ����
        if( (int)ob->query_condition("ill_dongshang")>=1 ) 
        {
                if ((int)ob->query_condition("ill_dongshang") <= 10 ) 
                {
                        ob->apply_condition("ill_dongshang", 0);
        message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"���ˣ���ɫ����ȥ�ö��ˡ�\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"��ȥһЩ����ɫ��������������\n"NOR, me, ob);
                ob->apply_condition("ill_dongshang", (int)ob->query_condition("ill_dongshang") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//�� ����
        if( (int)ob->query_condition("ill_fashao")>=1 ) 
        {
                if ((int)ob->query_condition("ill_fashao") <= 10 ) 
                {
                        ob->apply_condition("ill_fashao", 0);
        message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"���ˣ���ɫ����ȥ�ö��ˡ�\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"��ȥһЩ����ɫ��������������\n"NOR, me, ob);
                ob->apply_condition("ill_fashao", (int)ob->query_condition("ill_fashao") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//�� ����
        if( (int)ob->query_condition("ill_kesou")>=1 ) 
        {
                if ((int)ob->query_condition("ill_ill_kesou") <= 10 ) 
                {
                        ob->apply_condition("ill_ill_kesou", 0);
        message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"���ˣ���ɫ����ȥ�ö��ˡ�\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"��ȥһЩ����ɫ��������������\n"NOR, me, ob);
                ob->apply_condition("ill_ill_kesou", (int)ob->query_condition("ill_ill_kesou") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//�� �˺�
        if( (int)ob->query_condition("ill_shanghan")>=1 ) 
        {
                if ((int)ob->query_condition("ill_shanghan") <= 10 ) 
                {
                        ob->apply_condition("ill_shanghan", 0);
        message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"���ˣ���ɫ����ȥ�ö��ˡ�\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"��ȥһЩ����ɫ��������������\n"NOR, me, ob);
                ob->apply_condition("ill_shanghan", (int)ob->query_condition("ill_shanghan") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//�� ����
        if( (int)ob->query_condition("ill_zhongshu")>=1 ) 
        {
                if ((int)ob->query_condition("ill_zhongshu") <= 10 ) 
                {
                        ob->apply_condition("ill_zhongshu", 0);
        message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"���ˣ���ɫ����ȥ�ö��ˡ�\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n���ϵ�"HIB"����֢״"NOR+YEL"��ȥһЩ����ɫ��������������\n"NOR, me, ob);
                ob->apply_condition("ill_zhongshu", (int)ob->query_condition("ill_zhongshu") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }

        else {
                message_vision(CYN"����$n��û���ж�����\n"NOR, me, ob);
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
}
