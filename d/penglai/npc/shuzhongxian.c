// 
//

#include <ansi.h>

inherit NPC;

string ask_nanti1();
string ask_nanti2();
string ask_nanti3();
string ask_nanti4();
string ask_nanti5();
string ask_nanti6();

void create()
{
        set_name(HIW "������" NOR, ({ "shuzhong xian", "shuzhong", "xian" }));
                
        set("long", HIW "��λ�����˴��������������ɣ���˵���ϵ���֮����������֪����ͨ���\n" NOR);

        set("gender", "����");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "��β�����������"       :   "�����������Ŷ������Ƿ�����˵���޿ɱ���ģ�����ֻҪ���ܻش��ҵļ������⣬\n"
                                             "�����˵��ǿ��Խ�����μ���������������š�\n",
                "����"                   :   "�������ܹ����������⣬������ܰ�˳����һ������ұ������μ��ٱ��������ŵķ�����\n",                            
                "�������"               :   "������˾����������Ұɣ�����˳�����һ������� ask xian about ����һ ��\n",
                "��δ�"               :   "ÿ����Ŀ����һ��ʫ��һ���֣�����һ����Ʒ�����ҵ������Ʒ�����Ҿ����ˡ�\n",
                "�����ɵ�"               :   "�ⲻ��������ĵط����ҿ��㻹�ǿ��߰ɡ�\n",
                "����һ"                 :   (: ask_nanti1 :),
                "�����"                 :   (: ask_nanti2 :),
                "������"                 :   (: ask_nanti3 :),
                "������"                 :   (: ask_nanti4 :),
                "������"                 :   (: ask_nanti5 :),
                "������"                 :   (: ask_nanti6 :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

string ask_nanti1()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "����Ȼ����ɽ����" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 1)
                return "����������Ѿ������ˡ�";        
        
        tell_object(me, HIG "��Ŀ�ǣ�" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 1);
        me->save();
        
        return "�ҵ���ĺ���Ϣ�ˡ�";
}

string ask_nanti2()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "���̲������Ĺ��У�����ԡ¶�˴��ݡ���\n�������������Զ����������Ū��硣��" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 2)
                return "����������Ѿ������ˡ�";        
        
        if (me->query("penglai/go_quest/step") < 2)
                return "�㻹���Ƚ��ǰ�������ɡ�";
                        
        tell_object(me, HIG "��Ŀ�ǣ�\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 2);
        me->save();
        
        return "�ҵ���ĺ���Ϣ�ˡ�";
}

string ask_nanti3()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "���������ڸ����Σ��۳�����˿�ʫ����\n������Ѱ����л�磬��˼��������֪����" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 3)
                return "����������Ѿ������ˡ�";        
        
        if (me->query("penglai/go_quest/step") < 3)
                return "�㻹���Ƚ��ǰ�������ɡ�";
                        
        tell_object(me, HIG "��Ŀ�ǣ�\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 3);
        me->save();

        return "�ҵ���ĺ���Ϣ�ˡ�";
}

string ask_nanti4()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "������һ�������ǡ���\n" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 4)
                return "����������Ѿ������ˡ�";        
        
        if (me->query("penglai/go_quest/step") < 4)
                return "�㻹���Ƚ��ǰ�������ɡ�";
                        
        tell_object(me, HIG "��Ŀ�ǣ�\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 4);
        me->save();

        return "�ҵ���ĺ���Ϣ�ˡ�";
}

string ask_nanti5()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "��������׾�����������ۼ�����������" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 5)
                return "����������Ѿ������ˡ�";        
        
        if (me->query("penglai/go_quest/step") < 5)
                return "�㻹���Ƚ��ǰ�������ɡ�";
                        
        tell_object(me, HIG "��Ŀ�ǣ�\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 5);
        me->save();

        return "�ҵ���ĺ���Ϣ�ˡ�";
}

string ask_nanti6()
{
        object me;
        string str;
        
        me = this_player();
        str = HIC "��Ȱ��Ī�̾�������ʤ������\n��������͵أ����������ǡ���" NOR;
        
        if (me->query("penglai/go_quest/ok"))
                return "�ҵ����������㶼����ˣ���������";
                
        if (me->query("penglai/go_quest/step") > 6)
                return "����������Ѿ������ˡ�";        
        
        if (me->query("penglai/go_quest/step") < 6)
                return "�㻹���Ƚ��ǰ�������ɡ�";
                        
        tell_object(me, HIG "��Ŀ�ǣ�\n" + str + HIG "\n " NOR);
        me->set("penglai/go_quest/step", 6);
        me->save();

        return "�ҵ���ĺ���Ϣ�ˡ�";
}
int accept_object(object me, object obj)
{                        
        
        if (me->query("penglai/go_quest/ok"))
        {
                command("say �����ǻ۳�Ⱥ����������");
                return 0;
        }
        
        switch(me->query("penglai/go_quest/step"))
        {
                // �ջ�
                case 1:
                        if (obj->query("id") == "penglai juhua" &&
                                base_name(obj) == "/d/penglai/obj/juhua")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã�����Կ�ʼ�����һ�������ˡ�");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 2);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;
                        break;
                // ����        
                case 2:
                        if (obj->query("id") == "penglai lancao" &&
                                base_name(obj) == "/d/penglai/obj/lancao")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã�����Կ�ʼ�����һ�������ˡ�");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 3);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;                
                        break;                
                // �����걾
                case 3:
                        if (obj->query("id") == "hudie biaoben" &&
                                base_name(obj) == "/d/penglai/obj/biaoben")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã�����Կ�ʼ�����һ�������ˡ�");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 4);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;                
                        break;                
                // ÷��
                case 4:
                        if (obj->query("id") == "penglai meihua" &&
                                base_name(obj) == "/d/penglai/obj/meihua")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã�����Կ�ʼ�����һ�������ˡ�");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 5);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;                
                        break;                
                // ��Ҷ
                case 5:
                        if (obj->query("id") == "penglai songye" &&
                                base_name(obj) == "/d/penglai/obj/songye")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã�����Կ�ʼ�����һ�������ˡ�");
                                    destruct(obj);
                                    me->set("penglai/go_quest/step", 6);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;                
                        break;                
                // ��Ҷ
                case 6:
                        if (obj->query("id") == "penglai zhuye" &&
                                base_name(obj) == "/d/penglai/obj/zhuye")
                            {
                                    command("nod");
                                    command("say �ܺã��ܺã������ǻ۳�Ⱥ��������������һ���");
                                    destruct(obj);
                                    command("say �����˱������μ������������ţ���ɼǺ��� ����");
                                    tell_object(me, HIG "��ϲ�㣬�Ѿ�ѧ������μ��ٵ���������������š�\n" NOR);
                                    me->set("penglai/go_quest/ok", 1);
                                    me->save();
                                    return 1;
                            }
                            command("say �����˴Ӳ����ձ��˶�����");
                            return 0;                
                        break;        
                default :
                        command("say �����˴Ӳ����ձ��˶�����");
                        return 0;
                        break;                        
        }
        
        return 0;

}
void unconcious()
{
        die();
}
