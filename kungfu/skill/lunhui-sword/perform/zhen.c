#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

string name() { return HIR "�桤�����ֻ�" NOR; } 

int perform(object me, object target)
{
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage;
        int wait_time;
        int in_shejingdong;

        /*
        // ����Ƿ񾭹�������Ч�����ֻص�6��
        if( !query("scborn/perform_zhen_saishenlong", me) && !query("thborn/ok", me) )
        {
                // �ֻص����6���Զ��۳������ñ�־
                if( query("scborn/cur_lunhui_point", me) >= 6 )
                {
                        addn("scborn/cur_lunhui_point", -6, me);
                        set("scborn/perform_zhen_saishenlong", 1, me);
                        me->save();
                }
                // �����޷�ʩչ����
                else
                        return notify_fail("�Բ�����������ֻص������⣬����ʱ�޷�ʩչ���У�����μ����š�\n");
        }
        */
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "lunhui-sword")
                return notify_fail("��Ҫ�������ֻؽ�����Ϊ�ڹ�����ʩչ��\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("��������ķ����򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("lunhui-sword", 1) < 900)
                return notify_fail("�������ֻؽ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "lunhui-sword")
                return notify_fail("��û�м��������ֻؽ�������ʩչ" + name() + "��\n");

        if( query("neili", me)<4000 )
                return notify_fail("��������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
        wait_time = 30;
        
        if (me->query_skill("yinyang-shiertian", 1) >= 1000)
                wait_time = 25;
                
        if (me->query_skill("yinyang-shiertian", 1) >= 1400)
                wait_time = 20;
                
        if (me->query_skill("yinyang-shiertian", 1) >= 1600)
                wait_time = 15;
                
        if( time()-query_temp("last_perform_zhen", me)<wait_time )
                return notify_fail("���ʩչ��" + name() + "������������û����ȫ˳������ʱ����ǿ���˹���\n");
                
                                
        wn = weapon->name();

        message_combatd(HIW "$N" HIW "��¶�黨֮�⣬��������" + wn +
                        HIW "����ʱ�̲���ת���������ɣ�˵��������͡�"
                        "\n" NOR, me, target);

        //  ��¼������ķ���
        if (! objectp(sroom = environment(me)))
                return 1;

        if (base_name(sroom) == "/d/shenlong/shejingdong" ||
            base_name(sroom) == "/d/shenlong/huodong1" ||
            query("fight_room", sroom) )
                in_shejingdong = 1;

        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "force");

        damage = damage_power(me, "sword")*3;

        // �����ֻ�֮�˼��
        room = find_object("/d/death/liudaolunhui/rendao");
        if (! room) room = load_object("/d/death/liudaolunhui/rendao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "��������һ�����������ֵ�" + wn +
                       HIY "�������죬����˵����������������\n" NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack1, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // �����ֻ�֮������
        room = find_object("/d/death/liudaolunhui/chushengdao");
        if (! room) room = load_object("/d/death/liudaolunhui/chushengdao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\nȴ��$N" HIY "���ޱ��飬������" + wn +
                       HIY "�͵���ǰһ�ݣ����綾�߰�����$n" HIY "��\n"
                       NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack2, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // �����ֻ�֮�����
        room = find_object("/d/death/liudaolunhui/eguidao");
        if (! room) room = load_object("/d/death/liudaolunhui/eguidao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "һ����̾���������Ž���������" +
                       wn + HIY "��Ѫ��֮����Ũ����$n" HIY "ӭͷն�䡣\n"
                       NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                if( query("death_skill/guimai", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack3, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack3, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // �����ֻ�֮���޵�
        room = find_object("/d/death/liudaolunhui/xiuluodao");
        if (! room) room = load_object("/d/death/liudaolunhui/xiuluodao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n����$N" HIY "����΢�Σ���ʱ�ó�ʮ������"
                       "Ӱ��ʮ����" + wn + HIY "����$n" HIY "��ȥ��"
                       "\n" NOR, me, target);

        if (ap * 4 / 5  + random(ap) > dp)
        {
                if( query("death_skill/lonely", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack4, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack4, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // �����ֻ�֮������
        room = find_object("/d/death/liudaolunhui/diyudao");
        if (! room) room = load_object("/d/death/liudaolunhui/diyudao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n������$N" HIY + wn + HIY "һ������������"
                       "����������һ�����캮������������ɢ��ȥ��\n" NOR,
                       me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           (: attack5, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // �����ֻ�֮�켫��
        room = find_object("/d/death/liudaolunhui/tiandao");
        if (! room) room = load_object("/d/death/liudaolunhui/tiandao");

        if (! in_shejingdong)me->move(room);
        if (! in_shejingdong)target->move(room);

        message_combatd(HIY "\n$N" HIY "���⻯�����⻯��������" + wn +
                       HIY "���������ڿգ����Ƽ��գ����Ϊ֮ʧɫ��\n"
                       NOR, me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                if( query("death_skill/emperor", target) )
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage / 2, 100,
                                                   (: attack6, me, target, damage :));                
                else
                
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                   (: attack6, me, target, damage :));
        } else
        {
                msg = CYN "����$n" CYN "�������񣬷�����"
                      "�ܣ�������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(4 + random(4));
        addn("neili", -4000, me);
        set_temp("last_perform_zhen", time(), me);
        
        // Ϊʲô���У�Ϊ�˻����Ϊ������Ŀ����
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

        // ת�ƻ�����ķ���
        if (! in_shejingdong)me->move(sroom);
        if (! in_shejingdong)target->move(sroom);

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "ֻ����ͷһ����࣬���̲�סҪ��"
              "������������һ��Ż��һ����Ѫ��\n" NOR;

        if( !query_temp("liudaolunhui", target) )
        {
                msg += WHT "$p��Ȼ�����ȫ�����������һ˿"
                       "˿Զ���Լ���ȥ������֮����\n" NOR;

                addn_temp("apply/attack", -damage/10, target);
                addn_temp("apply/parry", -damage/10, target);
                addn_temp("apply/dodge", -damage/10, target);
                
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

        msg = HIR "��Ȼ��$n" HIR "�е��ؿڴ�һ����ȣ�����"
              "Ϯ�壬����һ��Ѫ�ꡣ\n" NOR;

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                // ����Ч���쾧��Ч
                if( query("material", weapon) == "tian jing")return msg;
                
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

        msg = HIR "$n" HIR "��ʱ��ʧɫ��˲���ѱ�$N" HIR "����"
              "������ֱ����Ѫ��ģ����\n" NOR;

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                // ����Ч���쾧��Ч
                if( query("material", cloth) == "tian jing")return msg;
                              
                cn = cloth->name();
                msg += WHT "������Ȼ��������$n" WHT "���ŵ�" + cn +
                       WHT "��$N" WHT "���������£�������÷��顣\n"
                       NOR;

                set("consistence", 0, cloth);
                cloth->move(target);
        } else
        if( objectp(armor=query_temp("armor/armor", target)) )
        {
                // ����Ч���쾧��Ч
                if( query("material", armor) == "tian jing")return msg;
                                
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

        msg = HIR "ֻ��$n" HIR "ȫ��һ��鴤����������Я�ļ�������"
              "�������У���ʹ�ѵ���\n" NOR;

        if (! target->query_condition("poison"))
        {
                // ���ж������Ե�����Ч
                if( query("death_skill/zhuha", target))return msg;
                
                target->affect_by("poison",
                        (["level":query("jiali", me)*3+random(query("jiali", me)),
                           "name"     : "��������",
                           "id":query("id", me),
                           "duration" : 80 ]));

                msg += WHT "��ʱ��$n" WHT "����һ���溮ɢ���߾�����"
                       "���·���ѪҺ��ֹͣ��������\n" NOR;
        }
        return msg;
}
void clear_no_exert(object target)
{
        if (! objectp(target))return;
        
        delete_temp("no_exert", target);
}

string attack6(object me, object target, int damage)
{

        string msg;

        msg = HIR "$N" HIR "����Ѹ��֮������$n" HIR "�����м���أ�"
              "�����ӵ��������ִ��С�\n" NOR;

        if( !query_temp("no_exert", target) )
        {
                // ���ж��������������Ч
                if( query("death_skill/guimai", target))return msg;
                
                set_temp("no_exert", 1, target);
                remove_call_out("clear_no_exert");
                call_out("clear_no_exert", 20, target);

                msg += WHT "$n" WHT "ֻ�е�ȫ��������ɢ����Ԫ�߽⣬��"
                       "�����е��书�������Ŵ�����\n" NOR;
        }
        return msg;
}