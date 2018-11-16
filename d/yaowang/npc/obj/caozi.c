#include <ansi.h>
inherit ITEM;

#define CAO_NOR        "/d/yaowang/obj/putong-herb/"
#define CAO_SM         "/d/yaowang/obj/herb/"
#define CAO_MEM_SM     "/d/yaowang/obj/herb/rare/"
#define CAO_MEM        "/d/yaowang/obj/herb/member/"
#define MEMBER_D       "/adm/daemons/memberd" 

// ��Ա��ҩ�б�
string *MEM_LIST = ({ "huanyang", "huoxuezhu", "hy-bc",
                         "hy-js", "hy-ly", "hy-mh", "hy-sb", "hy-ty",
                           "hy-yq", "hy-ys", "hy-zhu", "jiegudan", 
                         "jiujia", "lgshenjin", "shujincao", "tbrenshen",
                         "wugong", "zhjcao", });

// ��Ա�����ҩ�б�
  string *MEM_SM_LIST = ({ "qixing-haitang", "tihuxiang", "bi", "heye",
                     "yanling", "hua", });

// �����ҩ�б�
string *SM_LIST = ({ "tihuxiang", "huoxuezhu", "hy-bc",
                         "hy-js", "hy-ly", "hy-mh", "hy-sb", "hy-ty",
                           "hy-yq", "hy-ys", "hy-zhu", "jiegudan", 
                         "jiujia", "lgshenjin", "shujincao", "tbrenshen",
                         "wugong", "zhjcao", });
                     
// ��ͨ��ҩ�б� //��д��ô�࣬�Ժ��ڲ���
string *NOR_LIST = ({ "chaihu", "chenpi", "chongcao",
                         "chuanwu", "dahuang", "danggui", "duhuo", "fangfeng",
                         "fuzi", "qianjinzi", });

//��ҩ��д��ô�࣬�Ժ��ڲ���

void create()
{
        set_name("����", ({"cao zi"}));
        set_weight(10);
        set("no_clean_up", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ������ɫ�Ĳ��ѣ����������(zhong)�᳤�ɲ�ҩ��\n");
                set("value", 10);
        }
        setup();
}

void init()
{
        add_action("do_zhong", "zhong");
}

int do_zhong(string arg)
{
        object ob, me, where, whereob;

        me = this_player();
        ob = this_object();
        where=environment(me);
        whereob=environment(ob);

          if( query("family/family_name", me) != "ҩ����" || me->query_skill("baicao-jue",1)<10 || me->query_skill("bencao-changshi",1)<10 || me->query_skill("medical",1)<60 )
                return notify_fail("�㲻����ֲ��ҩ��\n");

        if(me->is_fighting() || me->is_busy())
                return notify_fail("���æ��ûʱ�䡣\n");

        if( !arg || !present(arg, me))
                return notify_fail("ָ���ʽ��zhong cao zi\n");

        if( !query("yaotian", where) )
                return notify_fail("ֻ������ҩ���\n");

        if( query("zhongyao", where) >= 10 )
                return notify_fail("�����Ѿ�û�ط���ҩ���ˡ�\n");

        if( query("jingli", me) <= 20 )
                return notify_fail("��̫���ˣ���������Ϣһ�°ɣ�\n");
        
        if( query("jingli", me) <= 20 )
                return notify_fail("��̫���ˣ���������Ϣһ�°ɣ�\n");
                
        if( query_temp("growing", me) )
                return notify_fail("���Ѿ�����ֲ��ҩ�ˣ�\n");
                
        if( query("value", ob) != 10 )
                return notify_fail("�Ѿ����ڵ����ˣ�\n");

        message_vision("$N���Ὣ$n���ڵ��\n", me, ob);

        ob->move(where);

                remove_call_out("grow_a");
                remove_call_out("grow_b");
                remove_call_out("grow_c");
                remove_call_out("grow_d");
                remove_call_out("grow_e");

        message_vision(WHT"��������������ѿ��\n"NOR, ob);
        set_name( "С���" , ({"xiao qingcao"}));
        set("long", "һ�국��ɫ��С��ݣ���û�г��ɡ�\n");
        set("value", 0);
        set("no_get", 1);

        addn("zhongyao", 1, where);
        set_temp("growing", 1, me);
        if (random(2)>0)
        {
                me->improve_skill("baicao-jue",(query("int", me)/3));
        }else
        {
                me->improve_skill("bencao-changshi",(query("int", me)/3));
        }
        addn("jing", -50, me);
//      me->start_busy(50);
        call_out("grow_a", 1, ob, me);
        return 1;
}

int grow_a(object ob, object me)
{
        int i=5+random(5);
        set("no_get", 1);
        call_out("grow_b", i, ob, me);
        return 1;
}

int grow_b(object ob, object me)
{
        if (environment(ob)==environment(me))
        {
                int i=10+random(5);
                message_vision(WHT"С��������س�����һƬҶ�ӡ�\n"NOR, ob);
                set_name( "���" , ({"qingcao"}));
                set("long", "һ�국��ɫ����ݣ���û�г��ɡ�\n");
                call_out("grow_c", i, ob, me);
                return 1;
        }else
        {
                message_vision(WHT"��������û�й���С��ݿ�ή�ˡ�\n"NOR, ob);
                tell_object(me, HIC "������û�м�ǿ��С��ݵĹ���С��ݿ�ή�ˡ�\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_c(object ob, object me)
{
        if (environment(ob)==environment(me))
        {
                int i=10+random(5);
                message_vision(WHT"��������س�����һ�㡣\n"NOR, ob);
                call_out("grow_d", i, ob, me);  
                return 1;
        }else
        {
                message_vision(WHT"��������û�й�����ݿ�ή�ˡ�\n"NOR, ob);
                tell_object(me, HIC "������û�м�ǿ����ݵĹ�����ݿ�ή�ˡ�\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_d(object ob, object me)
{
        if (environment(ob)==environment(me))
        {                       
                int i=10+random(10);
                message_vision(WHT"����������ֳ�����һЩ��\n"NOR, ob);
                set_name( CYN"�����"NOR , ({"da qingcao"}));
                set("long", "һ����ɫ�Ĵ���ݣ���û�г��ɡ�\n");
                call_out("grow_e", i, ob, me);  
                return 1;
        }else
        {
                message_vision(WHT"��������û�й�������ݿ�ή�ˡ�\n"NOR, ob);
                tell_object(me, HIC "������û�м�ǿ�Դ���ݵĹ�������ݿ�ή�ˡ�\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
        }
}

int grow_e(object ob, object me)
{
        object obj;
        int skill, skilla, skillb, exp, pot;
        skill = (int)me->query_skill("baicao-jue", 1) + (int)me->query_skill("bencao-changshi", 1);
        skilla = (int)me->query_skill("baicao-jue", 1);
        skillb = (int)me->query_skill("bencao-changshi", 1);
        
        exp = 8 + random(5);
        pot = 3 + random(3);

        if( query("potential", me)>me->query_potential_limit() )
                pot = 1;
                
        if (environment(ob)!=environment(me))
        {                       
                message_vision(WHT"��������û�й�������ݿ�ή�ˡ�\n"NOR, ob);
                tell_object(me, HIC "������û�м�ǿ�Դ���ݵĹ�������ݿ�ή�ˡ�\n" NOR);
                delete_temp("growing", me);
                destruct(ob);
                return 1;
        }
        
        message_vision(WHT"����ݳ����ˣ�������������(dig)��\n"NOR, me);
        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));
        if (random(skill) < 100 && random(3) == 1) 
        {
                delete_temp("growing", me);
                obj=new(__DIR__"cao"); 
                set("owner",query("id",  me), obj);
                obj->move(environment(ob)); 
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                        tell_object(me, HIC "������" + chinese_number(exp) +
                                "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );      
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 
        } else

        if( MEMBER_D->is_valib_member(query("id", me)) )
        {
                if (random(skill) > 300 && random(5) == 1)
                {
                        message_vision(HIY "$N��ֲ�Ĳ�ҩ�����ˣ�������������(dig)��$N��Ȼ�����������������һ����⡣\n"NOR, me);
                delete_temp("growing", me);
                        obj = new(CAO_MEM_SM + MEM_SM_LIST[random(sizeof(MEM_SM_LIST))]);
                        tell_object(me, HIC "���ֳ���ϡ�в�ҩ��" + NOR + obj->name() + NOR + HIC "����\n" NOR);                
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        exp += exp;
                        pot += pot;
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "������" + chinese_number(exp) +
                                "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)+10);
                                tell_object(me, HIC "���ֲݹ�������ġ��ٲݾ�������ˣ�\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)+10);
                                tell_object(me, HIC "���ֲݹ�������ġ����ݳ�ʶ������ˣ�\n" NOR);
                        }
                        
                } else 
                if (random(skill) > 100 && random(2) == 1)
                {
                        message_vision(HIC "$N��ֲ�Ĳ�ҩ�����ˣ�������������(dig)��\n" NOR, me);
                        delete_temp("growing", me);
                        obj = new(CAO_MEM + MEM_LIST[random(sizeof(MEM_LIST))]);
                        tell_object(me, HIC "���ֳ��ˡ�" + NOR + obj->name() + NOR + HIC "����\n" NOR);
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "������" + chinese_number(exp) +
                                "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)/4);
                                tell_object(me, HIC "���ֲݹ�������ġ��ٲݾ�������ˣ�\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)/4);
                                tell_object(me, HIC "���ֲݹ�������ġ����ݳ�ʶ������ˣ�\n" NOR);
                        }
                }
                else
                {
                        message_vision(HIC "$N��ֲ�Ĳ�ҩ�����ˣ�������������(dig)��\n" NOR, me);
                        delete_temp("growing", me);
                        obj = new(CAO_NOR + NOR_LIST[random(sizeof(NOR_LIST))]);
                        tell_object(me, HIC "���ֳ��ˡ�" + NOR + obj->name() + NOR + HIC "����\n" NOR);
                        set("owner",query("id",  me), obj);
                        set("no_get", 1, obj);
                        obj->move(environment(ob)); 
                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);
                        tell_object(me, HIC "������" + chinese_number(exp) +
                                "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
                        addn("zhongyao", -1, (environment(ob)));
                        destruct(ob); 
        
                        if (me->can_improve_skill("baicao-jue") && skilla < 500)
                        {
                                me->improve_skill("baicao-jue",query("int", me)/4);
                                tell_object(me, HIC "���ֲݹ�������ġ��ٲݾ�������ˣ�\n" NOR);
                        }
                        if (me->can_improve_skill("bencao-changshi") && skillb < 500)
                        {
                                me->improve_skill("bencao-changshi",query("int", me)/4);
                                tell_object(me, HIC "���ֲݹ�������ġ����ݳ�ʶ������ˣ�\n" NOR);
                        }
                }
                                
        }else

        if (random(skill) > 300 && random(10) == 1)
        {
                message_vision(HIY "$N��ֲ�Ĳ�ҩ�����ˣ�������������(dig)��$N��Ȼ�����������������һ����⡣\n"NOR, me);
                        delete_temp("growing", me);
                obj = new(CAO_SM + SM_LIST[random(sizeof(SM_LIST))]);
                tell_object(me, HIC "���ֳ���ϡ�в�ҩ��" + NOR + obj->name() + NOR + HIC "����\n" NOR);                
                set("owner",query("id",  me), obj);
                set("no_get", 1, obj);
                obj->move(environment(ob)); 
                exp += exp;
                pot += pot;
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                tell_object(me, HIC "������" + chinese_number(exp) +
                        "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 

                if (me->can_improve_skill("baicao-jue") && skilla < 400)
                {
                        me->improve_skill("baicao-jue",query("int", me)+10);
                        tell_object(me, HIC "���ֲݹ�������ġ��ٲݾ�������ˣ�\n" NOR);
                }
                if (me->can_improve_skill("bencao-changshi") && skillb < 400)
                {
                        me->improve_skill("bencao-changshi",query("int", me)+10);
                        tell_object(me, HIC "���ֲݹ�������ġ����ݳ�ʶ������ˣ�\n" NOR);
                }
                
        } else
        {
                message_vision(HIC "$N��ֲ�Ĳ�ҩ�����ˣ�������������(dig)��\n" NOR, me);
                        delete_temp("growing", me);
                obj = new(CAO_NOR + NOR_LIST[random(sizeof(NOR_LIST))]);
                tell_object(me, HIC "���ֳ��ˡ�" + NOR + obj->name() + NOR + HIC "����\n" NOR);
                set("owner",query("id",  me), obj);
                set("no_get", 1, obj);
                obj->move(environment(ob)); 
                addn("combat_exp", exp, me);
                me->improve_potential(pot);
                tell_object(me, HIC "������" + chinese_number(exp) +
                        "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"NOR );
                addn("zhongyao", -1, (environment(ob)));
                destruct(ob); 

                if (me->can_improve_skill("baicao-jue") && skilla < 400)
                {
                        me->improve_skill("baicao-jue",query("int", me)/4);
                        tell_object(me, HIC "���ֲݹ�������ġ��ٲݾ�������ˣ�\n" NOR);
                }
                if (me->can_improve_skill("bencao-changshi") && skillb < 400)
                {
                        me->improve_skill("bencao-changshi",query("int", me)/4);
                        tell_object(me, HIC "���ֲݹ�������ġ����ݳ�ʶ������ˣ�\n" NOR);
                }
        }

}
