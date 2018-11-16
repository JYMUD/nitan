

#include <ansi.h>

inherit ITEM;

int is_zhangpeng() { return 1;}

void create()
{
        set_name(HIM "˫������" NOR, ({ "shuangren zhangpeng", "shuangren", "zhangpeng"}) );
        set_weight(4000);
                set_max_encumbrance(1000000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("value", 1000000);
                set("long", HIM "����һ��˫����������Դ���������Ϣ��ָ�openzp)��\n" NOR);
                set("unit", "��");
                                set("no_hand", 1);
                                set("no_steal", 1);
                                set("no_clean_up", 1);
        }
        setup();
}

void init()
{
                add_action("do_open", "openzp");
                add_action("do_close", "closezp");
                add_action("do_out", "outzp");
                add_action("do_enter", "enterzp");
                add_action("do_joinzp", "joinzp"); // ����������������ID
}

// ����������������ID
int do_joinzp(string arg)
{
                object me, ob;

                me = this_player();
                ob = this_object();

                if (! arg)return notify_fail("����ʧ�ܣ�ָ���ʽ��joinzp ID\n");

                ob->set("join_id", arg);
                tell_object(me, HIG "���óɹ���\n" NOR);

                return 1;                
}

// ��������
int do_enter()
{
                object me, ob, obj;
                object *obs;
                int i;

                me = this_player();
                ob = this_object();
                
                if (ob->query("opening") != me->query("id") && ob->query("join_id") != me->query("id"))
                        return notify_fail("��Ŀǰ�޷������������\n");

                if (environment(me) == ob)
                        return notify_fail("�㲻���Ѿ���������\n");

                // ���˼��
                obs = all_inventory(ob);

                i = 0;
                foreach (obj in obs)
                {
                        if (userp(obj))i ++;                                                        
                }

                if (i >= 2)
                        return notify_fail("�Բ���˫�������Ѿ������ˡ�\n");
                
                me->move(ob);
                
                message_vision(HIC "$Nһͷ���" + ob->name() + HIC "��\n" NOR, me);

                return 1;
}

// ������
int do_out()
{
                object me, ob;

                me = this_player();
                ob = this_object();

                if (environment(me) != ob)
                        return notify_fail("�㲢û���������ﰡ��\n");

                if (! ob->query("out"))
                        return notify_fail("Ŀǰ�޷�������\n");

                message_vision(HIC "$N�������\n" NOR, me);

                me->move(ob->query("out"));

                return 1;                        
}

// ������
int do_open()
{
                object me;
                object env;
                object obt, obj;
                object *obs;

                me = this_player();

                if (environment(this_object()) != me)return 0;
                                
                if (me->query("shuangren_zhangpeng/flag"))
                {
                        return notify_fail("���Ѿ���˫�����񱻴��ˣ������ٴ�����\n");
                }
                                                
                if (this_object()->query("opening"))
                                return notify_fail("�����Ǵ򿪵�ô��\n");

                env = environment(me);

                if (env->is_zhangpeng())
                                return notify_fail("����ط������ٴ�˫�������ˡ�\n");        

                if (! env->query("outdoors"))
                                return notify_fail("����ֻ���ڻ���򿪡�\n");
                
                if (me->is_busy() || me->is_fighting())
                                return notify_fail("��������æ�����������飬�޷�������\n");
                
                // һ���ص�ֻ�ܿ�һ������
                obs = all_inventory(env);
                
                foreach(obj in obs)
                {
                        if (obj->is_zhangpeng())
                        {
                                return notify_fail("����ط��Ѿ����˰������ˣ��㻹�ǻ����ط��ɡ�\n");
                        }
                }
                
                obt = new("/clone/fam/item/zhangpeng2");

                // ��������
                obt->set("opening", me->query("id"));                
                obt->set("no_get", 1);
                
                // ��������
                obt->set("long", HIW "����һ��˫�������������������(ָ�closezp����\n"
                                 HIW "****��������������������ID��ָ�joinzp ID)��\n"
                                 HIW "****����������˿��Ե�����͸͸��(outzp������������ʹ��ָ�enterzp����\n" NOR);

                // ������������
                obt->set("sleep_room", 1);
                obt->set("no_fight", 1);

                // ���ó���
                obt->set("out", file_name(env));

                message_vision(HIC "$N��" + this_object()->name() + HIC "һͷ���˽�ȥ��\n" NOR, me);

                me->move(obt);
                obt->move(env);

                // ���������־
                me->set("shuangren_zhangpeng/flag", 1);
                me->set("shuangren_zhangpeng/ob", obt);
                
                me->save();

                destruct(this_object());

                return 1;
}

int do_close(string arg)
{
                object me, obt;
                object *obs;
                object obj, newob;

                me = this_player();
                obt = this_object();

                if (! obt->query("opening"))
                                return notify_fail("˫�������ǹر��ŵ�ô��\n");

                if (obt->query("opening") != me->query("id"))
                                return notify_fail("��û��Ȩ�������������\n");

                // ����һ������������
                newob = new("/clone/fam/item/zhangpeng2");
                
                message_vision(HIW "$N����������������װ�����ҡ�\n" NOR, me);

                // ��鸺��
             if (newob->query_weight() + me->query_encumbrance() >= me->query_max_encumbrance())
                {
                                tell_object(HIR "�Բ�����ĸ��ز��㣬�޷������������\n" NOR);
                                destruct(newob);
                                return 1;
                }

                // �뽫����������Ƴ�����Ȼ��ݻ����������һ������������
                obs = all_inventory(obt);

            // ����������˶��Ƴ���
                if (sizeof(obs))
                {
                        foreach(obj in obs)
                        {
                                obj->move(environment(obt));
                        }
                }

        // �����Ƶ�����������
                newob->move(me, 1);

                me->delete("shuangren_zhangpeng");

                me->save();
                // �ݻ��������
                destruct(this_object());

                return 1;
                
}

int query_autoload()
{
                return 1;
}