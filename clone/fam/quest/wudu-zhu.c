#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "�嶾��" NOR, ({ "wudu zhu", "wudu", "zhu" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "�����嶾������֮��Ʒ�����Ǵ������������涾���������ɣ�����\n"
                                "��ɴ�������������ڶ��ԡ��������嶾���ķ���ϣ�һ��������\n"
                                "�����С����������Ʋμ� help scborn_sk���������߲���ʧ)��\n" NOR);
                set("value", 500000);
                set("unit", "��");             
                set("only_do_effect", 1);
                set("do_effect", 1);
        }
}

int do_effect(object me)
{
        if (environment(this_object()) != me)
                return notify_fail("������û������������\n");
                
        if (query("do_effect") < 1)
                return notify_fail("�嶾���Ѿ������ù��ˡ�\n");

        if (me->query("max_neili") < 10000)
                return notify_fail("��������Ϊ���㣬���·��ú��������ն��ԡ�\n");

        if (me->query("neili") < 10000)
                return notify_fail("���������㣬���ú���������˹������綾��\n");

        if (me->query("can_perform/qianzhu-wandushou/suck_time") >= 5)
                return notify_fail("���Ѿ��������㹻�Ķ��أ�����Ҫ���ظ���ȡ�ˡ�\n");
        
        if (time() - me->query("last_eating_wudu_zhu") < 3600)
                return notify_fail("������չ����أ����������գ�\n");

        message_vision(HIM "$N" HIM "����һ���嶾�飬������ڼ�����Ƭ�̣�$N" HIM "��ɫ���أ��ƺ��綾����\n"
                       "�������� ����\n" NOR, me);
                       
        if (me->query_skill("wudu-qishu", 1) < 300 || me->query_skill("wudu-jing", 1) < 200 ||
            me->query_skill("qianzhu-wandushou", 1) < 800 || me->query("family/family_name") != "�嶾��" )
        {
                if (! me->query("special_skill/zhuha"))
                {
                        message_vision(HIR "\n$N" HIR "ͻȻʹ���ޱȣ����ر��У�ģ��ʮ�ֲֿ���\n" NOR, me);
                        me->set_temp("die_reason", "�����嶾��󱩱�");
                        me->die();                        
                        destruct(this_object());
                        return 1;
                }
                else
                {
                        tell_object(me, HIW "������������涾�����嶾��綾�ѱ�ȫ�����⡣\n" NOR);
                        destruct(this_object());
                        return 1;                        
                }
        }
        
        set("do_effect", 0);

        me->set("last_eating_wudu_zhu", time());
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, 0);
        
        //destruct(this_object());
        return 1;
}

void start_xishou(object me, int i)
{
        string* msg = ({
                "�㿪ʼ�˹������嶾��ľ綾���������ɵ������𣬲�Ѹ����ȫ������ ����\n",
                "��о��嶾��綾�����ޱȣ���ͨ������������֮���⣬�鼱֮��æ�����嶾�������ķ� ����\n",
                "�����أ��嶾��綾��ʼ�й��ɵ��˶����������嶾���ķ���ǣ�������� ����\n",
                "�㿪ʼʩչǧ�������ķ��������嶾���еĶ��� ����\n",
                "һ����󣬶��ؿ�ʼ�����ʮָ�ƶ�������ʼ�������ڵ������ں� ����\n",        
        });
        
        int ran;
        
        if (! objectp(me))
        {
                destruct(this_object());
                return;
        }
        
        if (environment(this_object()) != me)
        {
                tell_object(me, HIG "�嶾���Ѷ�ʧ����ȡʧ�ܣ�\n" NOR);
                destruct(this_object());
                return;
        }
        
        if (i >= sizeof(msg))
        {
                // zhuha���60%�������ճɹ����������30%���ճɹ�
                if (me->query("special_skill/zhuha"))
                {
                        ran = 6;        
                }
                else
                {
                        ran = 3;
                }
                
                if (random(10) >= ran) // ����ʧ��
                {
                        tell_object(me, HIG "ͻȻ�䣬��о��嶾���еľ綾��ʧ����Ӱ���٣���δ���������������գ�ʵ���ź���\n" NOR);
                        destruct(this_object());
                        return;
                }
                
                tell_object(me, HIG "��̼䣬��ֻ�������ж����ѱ����������գ��ں���һ�𣬾ۼ������ڣ�Ϊ�����ã�\n" NOR);
                tell_object(me, HIG "�㽫�����˻ص���о���̩�ޱȣ�\n" NOR);
                tell_object(me, HIR "��ϲ�㣬�ɹ��������嶾���еľ綾��\n" NOR);
                me->add("can_perform/qianzhu-wandushou/suck_time", 1);
                if (me->query("can_perform/qianzhu-wandushou/suck_time") >= 5)
                {
                        tell_object(me, HIM "��ϲ�㣬�Ѿ������˾�����˫�ľ�ѧ���򶾴����֣�\n" NOR);
                        me->set("can_perform/qianzhu-wandushou/chuan", 1);
                        me->save();
                }
                destruct(this_object());
                return;        
        }

        tell_object(me, HIW + msg[i] + NOR);
        
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, i + 1);
        
}

int query_autoload()
{
                return 1;
}