#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIG "���Ե���" NOR, ({ "badao book", "badao", "book"}));
        set_weight(500);
        if (clonep())
               destruct(this_object());
        else {
                set("unit", "��");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIG "\n����һ���ñ�ֽд�ɵ��飬��Ƥ��д�С��Ե������֡�\n"
                            "��������Ŷ���(read)����\n\n" NOR, );
        }
        
        remove_call_out("check_environment");
        call_out("check_environment", 3);
}

// ����Ȿ��
// 1����������������
// 2����ұ����ڱ�ˮ��̶�ڣ�һ���뿪��ˮ��̶����ʧ
void check_environment()
{
        object pob, eob;

        remove_call_out("check_environment");
        call_out("check_environment", 3);
                
        pob = environment(this_object());
        
        if (! objectp(pob))
        {
                destruct(this_object());
                return;
        }
        /*
        if (! userp(pob))
        {
                destruct(this_object());
                return;
        }
        */
        
        // ���ڱ�ˮ��̶����ʧ
        if (pob->query("is_hantan"))return;

        eob = environment(pob);
        
        if (! objectp(eob))
        {
                destruct(this_object());
                return;
        }
        
        if (! eob->query("is_hantan"))
        {
                tell_object(pob, HIG "���뿪�˱�ˮ��̶�����Ե�����~~��һ�����ڵ��ϣ���ʧ�ˣ�\n" NOR);
                destruct(this_object());
                return;
        }
        return;
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        string msg;
        
        if (! arg)
        {
                write("��Ҫ��ʲô��\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (where->query("no_fight")
           && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж��Ե���\n");
                return 1;
        }

    /* if (! me->query("scborn/ok"))
        {
                write("�㻹û�о����ֻ�ת���أ��޷������Ե���\n");
                return 1;
        } */
        
        if (me->query("str") < 38)
        {
                write("������������㣬�޷������Ե���\n");
                return 1;
        }

        if (me->query("con") < 38)
        {
                write("������������㣬�޷������Ե���\n");
                return 1;
        }

        if ((int)me->query_skill("sword", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }

        if ((int)me->query_skill("club", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }
                
        if ((int)me->query_skill("staff", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }
                
        if ((int)me->query_skill("whip", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }
                
        if ((int)me->query_skill("dagger", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }
                
        if ((int)me->query_skill("hammer", 1) && ! me->query("thborn/ok"))
        {
                write("����ѧ����ѧ̫���ˣ��޷�ר����ϰ�Ե���\n");
                return 1;
        }
                                                          
        if ((int)me->query("max_neili") < 20000)
        {
                write("���������Ϊ���㡣\n");
                return 1;
        }

        if ((int)me->query_skill("force", 1) < 500)
        {
                write("����ڹ����̫ǳ��\n");
                return 1;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 500)
        {
                write("�����ѧ�������㡣\n");
                return 1;
        }
                
        if ((int)me->query_skill("blade", 1) < 700)
        {
                write("��Ļ���������򲻹����޷�ѧϰ�Ե���\n");
                return 1;
        }
                
        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("�������ˮƽ̫�ͣ��޷��������������ص����ݡ�\n");        
                return 1;
        }
        
        if (! id(arg))
        {
                write("����û���Ȿ�顣\n");
                return 1;
        }

        if (me->query_skill("yinyang-shiertian", 1) && ! me->query("thborn/ok"))
        {
                write("�����ڵ����������޷���Ե�����ݡ�\n");
                return 1;
        }
        
        if (me->query_skill("lunhui-sword", 1) && ! me->query("thborn/ok"))
        {
                write("�����ڵ������ֻ������޷���Ե�����ݡ�\n");
                return 1;
        }
                
        if ((int)me->query("combat_exp") < 30000000)
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if ((int)me->query("jing") < 100
           || (int)me->query("qi") < 100
           || (int)me->query("neili") < 200)
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        
        msg = HIG "$N" HIG "�������Ե�������ϸ�о����������ص���ѧ�����Ǽ��������򡭡�\n" NOR;
        msg += HIG "$N" HIG "���������������ҿ�������üͷ������������Ŀ��˼��\n" NOR;
        msg += HIG "$N" HIG "��̾һ�����п���ǧ���ƺ�������ʲô ����\n" NOR; 
        message_vision(msg, me); 

        if (me->query_skill("badao", 1) < 180)
        {                        
                write(HIW "��ԡ�" HIG "�Ե�" HIW "�������µ�����\n" NOR);
                // ��һ��ѧϰ
                if (! me->query_skill("badao", 1))
                {
                        // �ֻص�
                        if (me->query("scborn/cur_lunhui_point") < 7 && ! me->query("thborn/ok"))
                        {
                                write("���ֻص㲻�㣬�޷�����Ե���\n");
                                return 1;
                        }    
                        if (! me->query("thborn/ok"))
                        {
                                me->add("scborn/cur_lunhui_point", -7);
                                write(HIG "\n��ϲ��ѧ���˰Ե��������ֻص� 7 �㣬���𽫰Ե�����Ϊ0����������ѧϰ��������Ҫ���������ֻص㡣\n" NOR);
                        }
                        me->set_skill("badao", 40 + random(21));
                        me->save();
                }
                else                                        
                        me->set_skill("badao", me->query_skill("badao", 1) + 40 + random(21));

                destruct(this_object());
        }
        else
        {
                write(HIR "��Ե������Ѿ��޷���ͨ���ж��ؼ��������ˡ�\n" NOR);
                return 1;
        }

        return 1;
}
