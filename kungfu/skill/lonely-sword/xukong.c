
#include <ansi.h>

#define HUA "��" MAG "���֮��" NOR "��"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object landie;
        object *obs, wanjia, env;
        string msg;
        
        if (! objectp(me))return 1;
        
        // ֻ�н��������
        if (base_name(me) != "/kungfu/class/misc/jianling")
                return notify_fail("����ʹ�õ��⹦��û��������ܡ�\n");

        // �������ӻ�����ʱ������
        landie=query("mylandie", me);
        if (objectp(landie))return 1;
        
        // �����ϴ�������ʧ����3�����޷�ʩչ
        if( query("first_landie", me))//�Ѿ��ٻ����������ܴ�����
        {
                if( time()-query("last_summon_landie", me)<180 )
                        return 1; 
        }

        msg = HIC "$N" HIC "����һ��������������������ʱ��â���֣�����ջ���һ�������Ļ��� ����"
              "��ʱ�����֮��˺��һ���ѷ죬����Ů洲���ʱ�����֮�ۣ�һ��������ѷ�����������ǧ"
              "��â���֣�һλ���������Ӵ���������ػ��Ž��飡\n" NOR;

        // ��¼�����Ƿ��ǵ�һ���ٻ�����
        if( !query("first_landie", me) )
                set("first_landie", 1, me);

        env = environment(me);
        // ��ʼ����������
        landie = new("/kungfu/class/misc/landie-xianzi");
        // ���ѡ��ǰ����һ�����
        obs = all_inventory(env);
        obs = filter_array(obs, (: userp($1) :));
        
        if (! sizeof(obs))return notify_fail("û���ҵ���ң�\n");

        wanjia = obs[random(sizeof(obs))];      
        if( !objectp(obs) ) return 1;
        landie->init_me(me, wanjia);
        landie->move(env);
        
        set("mylandie", landie, me);

        msg += HIY "\n$n" HIY "����������ƺ��������������ӵ�������\n" NOR;
        
        message_vision(sort_msg(msg), me, wanjia);
        
        return 1;
}
