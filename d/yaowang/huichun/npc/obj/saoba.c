// ɨ�� �ش���������ĵ��ߡ�

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("ɨ��", ({ "saoba" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����Ƶ�ɨ�ѡ�\n");
                set("value", 1);
                set("material", "iron");
                set("wield_msg", "$N�ó�һ��$n���������С�\n");
                set("unwield_msg", "$N�������е�$n��\n");
        }
        init_hammer(5);
        setup();
}

void init()
{
           add_action("do_job","dasao");
}

int do_job(string arg)
{
        object me;
        object weapon;
         int i, j;
        me = this_player();
        j=(random(query("str", me))/3);
        if (j <= 0)
                j = 5;

        if( query("jing", me) <= j){
                message_vision ("$N̫���ˣ�������Ϣһ�£����ܼ����������\n", me );
                return 1;
        }

        if( !query_temp("renwu_name", me)){
                message_vision ("$N����ɨ�ѣ�������һ������Ȥ��\n", me);
                return 1;
        }

        if( query_temp("renwu_wancheng", me) >= 100 )
        {
                set_temp("renwu_wancheng", 100, me);//��ʾ�������
                return notify_fail ("����������񣬻�ȥ�����ɣ�\n");
        }

              if (me->is_busy()) 
                      return notify_fail("��������æ���أ�\n"); 
        if( query("short", environment(me)) != query_temp("renwu_name", me) )
                return notify_fail ("���������������ɨ����\n");

        //�ж��Ƿ�wield�˹���
        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "saoba" )
        {
                return notify_fail ("�������ôɨ�أ�����ץ��\n");
        }
        else 
        {               
                addn_temp("renwu_wancheng", j, me);
                addn("jing", -j, me);
                me->improve_skill("medical", (j/3));
                message_vision ("$N����ɨ�ѣ�һ��ɨ�ŵذ壬һ������ҽʦ�ڸ��˰�����\n", me);
                   me->start_busy(1+random(3));
        }
        return 1;
}
