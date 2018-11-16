
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "��" HIY "��" NOR + WHT "��" NOR, ({ "riyue jing", "riyue", "jing" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "��˵Ů洴��������ʱ��Ϊ��ʱ�̼��������һ��һ����\n"
                                "�������������������һ�汦������Ի���¾���ӵ������\n"
                                "�����˿�����ʱ�鿴����Ϸ�е������Ҽ�NPC��λ�á�\n"
                                "ÿ��ʹ�����Ļƽ�һ���������׻������1YSG/�Ρ�\n" HIY
                                "ָ� echo ����Ӣ��ID\n" NOR);
                set("value", 800000);
                
        }
        setup();
}

void init()
{
        add_action("do_echo", "echo");
}

int do_echo(string arg)
{

        object me, target;
        string where;
        
        me = this_player();

        if (environment(this_object()) != me)return 0;

        if (! arg)return notify_fail("ָ���ʽ�� echo ����Ӣ��ID\n");

        target = find_living(arg);

        if (! objectp(target))
                return notify_fail(HIG "���¾�����һ�����⣺û���ҵ�Ŀ��������ܸ����ﲻ���ڻ�δ�����£�\n" NOR);
                
        // ���ܲ鿴����ID����ʦ
        if (wizardp(target))
                return notify_fail(HIG "���¾�����һ�����⣺û���ҵ�Ŀ��������ܸ����ﲻ���ڻ�δ�����£�\n" NOR);
                
        // �۳�YSG
        if (me->query("stocks/balance") < 1)
                return notify_fail("�Բ������YSG���㣬�޷�ʹ�����¾���\n");        
        
        if (target->query_temp("apply/invisible") && ! me->query_condition("niuyanlei"))
                return notify_fail(HIG "���¾�����һ�����⣺û���ҵ�Ŀ��������ܸ����ﲻ���ڻ�δ�����£�\n" NOR);

        me->add("stocks/balance", -1);

        if (! environment(target))
                return notify_fail("�Բ��𣬸ö����޷���ѯ������λ�á�\n");

        where = stringp(environment(target)->query("short")) ? environment(target)->query("short")
                                                                 : environment(target)->short();

        tell_object(me, HIG "���¾�����һ�����⣺" + target->name() + "(" + arg + ")������" + 
                         where + HIG "��\n" NOR);

        return 1;
}

int query_autoload()
{
        return 1;
}
