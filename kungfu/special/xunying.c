// xunying.c ��Ӱ����
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "��Ӱ����" NOR; }

int perform(object me, string skill)
{        
        
        if (me->query("special2/xunying") && ! me->query("thborn/ok"))
        {
                // 2ת���ʹ��һ��
                if (me->query("special2/thborn_xunying"))        
                        return notify_fail("�Բ������ڽ����Ѿ�ʹ�ù��þ������޷��ٴ�ʹ���ˡ�\n");
        }
        
                if (me->query("combat_exp") < 2700000)
                        return notify_fail("����ʵս����С��270���޷�ʩչ�ü��ܡ�\n");
                
        if (me->query_temp("special2/xunying"))
        {
                me->set_skill("count", 300);
                me->set_skill("mathematics", 300);
                me->set("special2/xunying", 1);
                if (me->query("thborn/ok"))
                        me->set("special2/thborn_xunying", 1);
                me->save();
                return notify_fail("�������������Լ��������ټ���\n");
        }
        else
        {
                me->set_temp("special2/xunying", 1);
        
                      return notify_fail("����ת���������ݹ����󣬲����������\n"
                                                "��������أ�������̬�����۵ס��˺�\n"
                                             "�����ܵ�����ж��֮�����Ի�ת����ʹ\n"
                                             "�øþ����ɻ���������Լ������ȼ�����\n"
                                             "������һ������ʹ��һ�Σ�����������\n"
                                             "��ʹ����������һ�� " HIY "special xunying" NOR " ��\n");
       }
}