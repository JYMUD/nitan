#include <ansi.h>
#include <combat.h>

#define XIN "��" HIR "�����ֻ�" NOR "��"

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage, wound;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))   
                return notify_fail(XIN "ֻ����ս����ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" XIN "��\n");

        if ((int)me->query_skill("force") < 380)
                return notify_fail("���ڹ���Ϊ���㣬����ʩչ" XIN "��\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("��������Ϊ���㣬����ʩչ" XIN "��\n");

        if ((int)me->query_skill("buddhism", 1) < 240)
                return notify_fail("�������ķ���Ϊ���㣬����ʩչ" XIN "��\n");

        if ((int)me->query_skill("lunhui-jian", 1) < 260)
                return notify_fail("�������ֻؽ���Ϊ���㣬����ʩչ" XIN "��\n");

        if (me->query_skill_mapped("sword") != "lunhui-jian")
                return notify_fail("�㻹û�м��������ֻؽ�������ʩչ" XIN "��\n");

        if( query("neili", me)<600 )
                return notify_fail("���������㣬����ʩչ" XIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        message_combatd(HIW "$N" HIW "��¶�黨֮�⣬��������" + wn +
                        HIW "����ʱ�̲���ת���������ɣ�˵��������͡�"
                        "\n" NOR, me, target);

        //  ��¼������ķ���
        if (! objectp(sroom = environment(me)))
                return 1;

        if (base_name(sroom) == "/d/shenlong/shejingdong" ||
            base_name(sroom) == "/d/shenlong/huodong1" ||
            query("biwu_room", sroom) )
                return notify_fail("��������޷��ڴ˴�ʩչ��\n");
                
        ap = me->query_skill("sword") + me->query_skill("buddhism", 1) * 4 / 5;

        dp = target->query_skill("parry") +
             target->query_skill("buddhism", 1);

        damage = ap + random(ap);

        damage /= 3;
        wound = 60;

                if (me->query_skill("lunhui", 1) > 1)
                {
                        damage = damage + damage * me->query_skill("lunhui", 1) / 1000;
                        wound = wound + wound * me->query_skill("lunhui", 1) / 1500;
                }

        // �����ֻ�֮�˼��
        room = find_object("/d/death/liudaolunhui/rendao");
        if (! room) room = load_object("/d/death/liudaolunhui/rendao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\n$N" HIY "��������һ�����������ֵ�" + wn +
                       HIY "�������죬����˵����������������\n" NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack1, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����ֻ�֮������
        room = find_object("/d/death/liudaolunhui/chushengdao");
        if (! room) room = load_object("/d/death/liudaolunhui/chushengdao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\nȴ��$N" HIY "���ޱ��飬������" + wn +
                       HIY "�͵���ǰһ�ݣ����綾�߰�����$n" HIY "��\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack2, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����ֻ�֮�����
        room = find_object("/d/death/liudaolunhui/eguidao");
        if (! room) room = load_object("/d/death/liudaolunhui/eguidao");
        
        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\n$N" HIY "һ����̾���������Ž���������" +
                       wn + HIY "��Ѫ��֮����Ũ����$n" HIY "ӭͷն�䡣\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack3, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����ֻ�֮���޵�
        room = find_object("/d/death/liudaolunhui/xiuluodao");
        if (! room) room = load_object("/d/death/liudaolunhui/xiuluodao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\n����$N" HIY "����΢�Σ���ʱ�ó�ʮ������"
                       "Ӱ��ʮ����" + wn + HIY "����$n" HIY "��ȥ��"
                       "\n" NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack4, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����ֻ�֮������
        room = find_object("/d/death/liudaolunhui/diyudao");
        if (! room) room = load_object("/d/death/liudaolunhui/diyudao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\n������$N" HIY + wn + HIY "һ������������"
                       "����������һ�����캮������������ɢ��ȥ��\n" NOR,
                       me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack5, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // �����ֻ�֮�켫��
        room = find_object("/d/death/liudaolunhui/tiandao");
        if (! room) room = load_object("/d/death/liudaolunhui/tiandao");

        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(room);
                target->move(room);
        }


        message_vision(HIY "\n$N" HIY "���⻯�����⻯��������" + wn +
                       HIY "���������ڿգ����Ƽ��գ����Ϊ֮ʧɫ��\n"
                       NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, wound,
                                           (: attack6, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        me->start_busy(3 + random(3));

        addn("neili", -200-random(400), me);

        // Ϊʲô���У�Ϊ�˻����Ϊ������Ŀ����
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

        // ת�ƻ�����ķ���
        if (base_name(sroom) != "/d/shenlong/shejingdong")
        {
                me->move(sroom);
                target->move(sroom);
        }


/*
        // ����ͨ������������
        if( query("qi", target)<0 )
                target->die(me);
*/
        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                damage = damage * p / 100;

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

        msg = HIR "$n" HIR "ֻ����ͷһ����࣬���̲�סҪ��"
              "������������һ��Ż��һ����Ѫ��\n" NOR;

        if( !query_temp("liudaolunhui", target) )
        {
                msg += WHT "$p��Ȼ�����ȫ�����������һ˿"
                       "˿Զ���Լ���ȥ������֮����\n" NOR;

                addn_temp("apply/attack", -damage, target);
                addn_temp("apply/parry", -damage, target);
                addn_temp("apply/dodge", -damage, target);
                if( query_temp("apply/attack", target)<0 )
                        set_temp("apply/attack", 0, target);
                if( query_temp("apply/parry", target)<0 )
                        set_temp("apply/parry", 0, target);
                if( query_temp("apply/dodge", target)<0 )
                        set_temp("apply/dodge", 0, target);
                                                                        
                set_temp("liudaolunhui", 1, target);
        }

        return msg;
}

string attack2(object me, object target, int damage)
{
        object weapon;
        string wn, msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "��Ȼ��$n" HIR "�е��ؿڴ�һ����ȣ�����"
              "Ϯ�壬����һ��Ѫ�ꡣ\n" NOR;

        if( objectp(weapon=query_temp("weapon", target)) && query("material", weapon) != "tianjing" )
        {
                wn = weapon->name();
                msg += WHT "�����������ϡ��������죬$n" WHT "��" + wn +
                       WHT "����$N" WHT "�ʳ��˿����Ƭ��\n" NOR;

                set("consistence", 0, weapon);
                weapon->move(target);
        }
        return msg;
}

string attack3(object me, object target, int damage)
{
        int shd;
        string msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "�����������������Ѫ�ˣ�$n" HIR "ֻ��ͷ��Ŀ"
              "ѣ����֫������������ս��\n" NOR;

        if( query_temp("shield", target) )
        {
                shd=query_temp("apply/armor", target);

                addn_temp("apply/armor", -shd, target);
                if( query_temp("apply/armor", target)<0 )
                        set_temp("apply/armor", 0, target);
                        
                delete_temp("shield", target);

                msg += WHT "$N" WHT "����ӿ�������������ʱ��$n"
                       WHT "�Ļ��������ݻٵõ�Ȼ�޴档\n" NOR;
        }
        return msg;
}

string attack4(object me, object target, int damage)
{
        object cloth, armor;
        string cn, an, msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "$n" HIR "��ʱ��ʧɫ��˲���ѱ�$N" HIR "����"
              "������ֱ����Ѫ��ģ����\n" NOR;

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                cn = cloth->name();
                msg += WHT "������Ȼ��������$n" WHT "���ŵ�" + cn +
                       WHT "��$N" WHT "���������£�������÷��顣\n"
                       NOR;

                set("consistence", 0, cloth);
                cloth->move(target);
        } else
        if( objectp(armor=query_temp("armor/armor", target)) && query("material", armor) != "tianjing" )
        {
                an = armor->name();
                msg += WHT "������������һ�����죬$n" WHT "���ŵ�" +
                       an + WHT "����$N" WHT "���ѣ����ɿ����Ƭ��\n"
                       NOR;

                set("consistence", 0, armor);
                armor->move(target);
        }
        return msg;
}

string attack5(object me, object target, int damage)
{
        string msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "ֻ��$n" HIR "ȫ��һ��鴤����������Я�ļ�������"
              "�������У���ʹ�ѵ���\n" NOR;

        if (! target->query_condition("poison"))
        {
                target->affect_by("poison",
                        ([ "level"    : damage / 3,
                           "name"     : "��������",
                           "id":query("id", me),
                           "duration" : damage / 50 ]));

                msg += WHT "��ʱ��$n" WHT "����һ���溮ɢ���߾�����"
                       "���·���ѪҺ��ֹͣ��������\n" NOR;
        }
        return msg;
}

string attack6(object me, object target, int damage)
{

        string msg;

                int p;                

        // ת�����������������кܴ��ʳ�����Ч
                // ���ɼ��������ֻؿ���߳���Ч�ļ���
                p = 0;
                if( query("scborn/ok", me) )
                {
                        if( query("int", me) >= 39 && 
                                query("dex", me) >= 39 && 
                                query("con", me) >= 39 && 
                                query("str", me) >= 39 )
                        {                        
                                p = 40;
                        }

                }

                if (me->query_skill("lunhui", 1) > 1 || random(10) > 1)
                {
                        p = p + me->query_skill("lunhui", 1) / 20;
                }

                if (random(101) >= p)
                {
                        return HIR "$n" HIR "ֻ�������þ�����������ȫ��"
                   "�����������Լ����ơ�\n" NOR;
                }

                damage = damage * p / 100;

        msg = HIR "$N" HIR "����Ѹ��֮������$n" HIR "�����м���أ�"
              "�����ӵ��������ִ��С�\n" NOR;

        if( !query_temp("no_exert", target) )
        {
                set_temp("no_exert", 1, target);

                msg += WHT "$n" WHT "ֻ�е�ȫ��������ɢ����Ԫ�߽⣬��"
                       "�����е��书�������Ŵ�����\n" NOR;
        }
        return msg;
}
