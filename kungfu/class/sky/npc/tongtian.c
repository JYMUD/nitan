// ͨ������ �ƹ�ת��
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define SCBORN_D   "/adm/daemons/scbornd"
#define MEMBER_D   "/adm/daemons/memberd"

mixed start_scborn();
mixed start_kaoyan();

void create()
{
        set_name(HIW "ͨ������" NOR, ({ "tongtian laoxian", "tongtian", "laoxian" }));
        set("long", HIW "    ���������������������ͨ�����ɣ���˵��\n"
                        "�ƹ������ת��֮·���һ�������š�\n" NOR);

        set("gender", "����");
        set("age", 199);
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
                "ת��"   :   (: start_scborn :),
                "����"   :   (: start_kaoyan :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

// ת�������12������ٻ��2���ֻص�
mixed start_kaoyan()
{
           object me;

           me = this_player();

           if (! me->query("scborn/ok"))
           {
                   write("�㻹ûת���ء�\n");
                   return 0;
           }

       if (me->query("sky12/floor") != 13)
       {
              write("�㻹û��ͨ��ʮ�������Ŀ��飡��֪����ô�����ģ������\n");
                          me->move("/d/city/wumiao");
              return 0;
       }

           // ����Ƿ��Ѿ���ù�
           if (me->query("scborn/get_lunhui_point_12t"))
           {
                          write("���Ѿ���ȡ���ֻص��ˡ�\n");
                          return 0;
           }

           if (me->query("scborn/total_lunhui_point") >= 17)
           {
                          write("���ݴ���\n");
                          return 0;
           }

           // ����ֻص�
           me->add("scborn/total_lunhui_point", 2);
           me->add("scborn/cur_lunhui_point", 2);
           me->set("scborn/get_lunhui_point_12t", 1);

           me->save();

           write("��ϲ�㾭��ʮ�����쿼�飬��� �� ���ֻص㡣\n");
           return 1;
}


mixed start_scborn()
{
        object me = this_player();
        
        // ���ת������
        if (! SCBORN_D->check_data2(me))return 1;

        if (me->query("sky12/haotianta"))
        {
                tell_object(me, HIG "ͨ�����ɶ���˵����������ҵ�����\n" NOR);
                return 1;
        }

        message_sort(HIM "\n$N" HIM "��$n" HIM "˵������֮���ϲ�����ת���ֻؽ��ж�����"
                     "������ע���������Ҫ������У������ͨ�����ѹأ������ڴ�ͨ�����"
                     "ʮ�����죬ԭ��Ӧ�ÿ���ת����������������Υ��������˵�����Ҫ˳��"
                     "ת���������˻��轫��������������У����ô��������ǻ���֮�����ɡ�\n" NOR,
                     this_object(), me);
                     
        tell_object(me, HIG "ͨ���������ĸ����㣺������ҵ�������Ͱ��������ң��һ����"
                        "�����ת����\n" NOR);
        
        me->set("sky12/haotianta", 1);

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
}

// ѡ��ְҵ
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

    // ����
        if (! arg)
        {
                // һת����
                msg  = HIR "\n��Ŀǰ����ѡ������ְҵ��Ϊ��ת�����ְҵ��\n" NOR;
                msg += HIC "���ͣ�������˾�����ְҵ��ӵ�������๥���ؼ���\n" NOR;
                msg += HIM "ħʦ: ������η���ְҵ��ӵ��а���๥���ؼ���\n" NOR;
                msg += HIG "��ʿ: ���������������������⣬ӵ�ж��ָ������ؼ���\n" NOR;
                msg += HIY "����ְҵ������μ�ת��ְҵ�����ļ� help scborn_yhjob\n" NOR;
                msg += HIY "������ָ��" HIR " yhjob ְҵ " HIY "��ѡ����ת�����ְҵ��ѡ��ǰ�������Ķ�ת��ְҵ�����ļ���\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "����" && arg != "ħʦ" && arg != "��ʿ")
                return notify_fail("��ѡ����ȷ��ְҵ�����͡�ħʦ����ʿ��\n");
        
        if (me->query("scborn"))
                return notify_fail("�Բ���������ѡ�����ְҵ��\n");

        if (me->query("yhjob/job") && me->query("yhjob/job") != "��ʿ")
                return notify_fail("�Բ���������ѡ�����ְҵ��\n");

        write(HIG "��ѡ���� " + arg + " ��ְҵ��\n");

        me->set("yhjob/job" , arg);
        me->save();

        return 1;
}

int accept_object(object me, object ob)
{        
        string obj;
        string msg;
        string *spes;
        mapping special;
        string job;

                if (me->query("scborn/ok"))
                {
                        write("���Ѿ�ת�����ˡ�\n");
                        return 0;
                }
                
        // ���ת������
        if (! SCBORN_D->check_data2(me))return 0;
        
        obj = filter_color(ob->name());

        if (obj != "�����" || 
            ob->is_item_make() ||
            ! ob->is_magic_item())return 0;

                if (! me->query("yhjob"))
                {
                        write("����û��ѡ����ת�����ְҵ�أ�������ָ�� yhjob ��ʼѡ������ְҵ��\n");
                        return 0;
                }

                job = me->query("yhjob/job");

                if (job != "����" && job != "ħʦ" && job != "��ʿ")
                {
                        write("��ѡ���ְҵ����ȷ��������ѡ��\n");
                        return 0;
                }

        // ��ʼת��
        if (! SCBORN_D->start_scborn(me))
        {
                write("ת��ʱ���ݳ���\n");
                return 0;
        }
        destruct(ob);

        message_sort(HIC "\n$N" HIC "��������������е��������ɲʱ�䣬�ߵ���â��"
                         "������б��ڶ�������$n" HIC "���˽�ȥ ����\n" NOR,
                         this_object(), me);
                         

        me->move("/kungfu/class/sky/haotian");
        tell_object(me, HIG "�㴩��ʱ�գ�������������\n\n" NOR);

        me->move("/d/city/wumiao");
                
        special = me->query("special_skill");
        spes = keys(special);
        
        if (MEMBER_D->is_valib_member(me->query("id")) &&
            sizeof(spes) == 2)
        {
                msg = SCBORN_D->get_special_name(spes[0]) + "��";
                msg += SCBORN_D->get_special_name(spes[1]);
        }
        else 
                msg = SCBORN_D->get_special_name(spes[0]);


                // ����ְҵ����
                if (job == "����")
                {
                        me->set("special_skill/haoran",1);
                        me->set("special_skill/xiagu",1);
                        me->set("special_skill/shewo",1);
                }
                else if (job == "ħʦ")
                {
                        me->set("special_skill/moxin",1);
                        me->set("special_skill/youran",1);
                        me->set("special_skill/haoling",1);
                }
                else // ��ʿ
                {
                        me->set("special_skill/haina",1);
                        me->set("special_skill/xianyun",1);
                        me->set("special_skill/tianxia",1);
                }
        // UPDATE_D->born_player(me);

        call_out("notify_all", 1, me, msg, spes);

        return 1;
}

int notify_all(object me, string msg, mixed spes)
{
                CHANNEL_D->do_channel(this_object(), "rumor", 
                               HIY "��˵" + me->name() + HIY + 
                               "��ͨʮ�����죬����ʱ�գ�������������\n" NOR);
         
         tell_object(me, HIW "\n����ת�����ܣ�" + msg + "\n" NOR);

                 // ����ֻص�
                 tell_object(me, HIG"ת���ɹ������ �� ���ֻص㣬�Ժ���ʹ�� power ָ��鿴��\n");
                 me->add("scborn/total_lunhui_point", 5);
                 me->add("scborn/cur_lunhui_point", 5);

         // ��������ת�����ܣ�update_d->born_player()Ҫɾ�����м���
         if (MEMBER_D->is_valib_member(me->query("id")) &&
             sizeof(spes) == 2)
         {
                me->set("special_skill/" + spes[0], 1);
                me->set("special_skill/" + spes[1], 1);
         }
         else
                me->set("special_skill/" + spes[0], 1);
                
         me->save();
         
         // ֪ͨ���ݱ�����Ϣ
         call_out("notify_me", 1, me);
         
         return 1;
}

int notify_me(object me)
{
        tell_object(me, HIR "\n��ת��ǰ�������ѱ��ݣ��������緢�������쳣���뼰ʱ֪ͨ��վadmin��\n\n" NOR);
        return 1;
}
void unconcious()
{
        die();
}
