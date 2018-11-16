// ͨ������ �ƹ�ת��
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define MEMBER_D   "/adm/daemons/memberd"
#define FUBEN_D    "/adm/daemons/fuben_daemonsd"

mixed start_thborn();

void create()
{
        set_name(HIY "�׻�����" NOR, ({ "yanhuang tianshen", "yanhuang", "tianshen" }));
        set("long", HIY "    �׻������������ݣ��ڴ˹�������ʱ�ˣ���Ҫ\n"
                        "ͨ������ת���������������Ŀ��顣\n" NOR);

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
                "��ת"   :   (: start_thborn :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

mixed start_thborn()
{
        object me = this_player();
        
        string item1, item2;
        object ob1, ob2;
        
        string *keys_item1, *keys_item2;        
        object ob_taixu, ob_boss;
        
        mapping  ob_list1 = ([
                "������"            : "/clone/misc/boss_item/jiangjun-ling",
                "��ʿɽ�羰��"      : "/clone/misc/boss_item/fengjing-hua",
                "��ɱ����"          : "/clone/misc/boss_item/ansha-mingdan",
                "����"              : "/clone/misc/boss_item/jiaozi",
                "��ӣ���ޡ�"        : "/clone/misc/boss_item/yinghua-zan",
                "���ظ��ͼ"        : "/clone/misc/boss_item/anshouge-tu",
                "��ʦ���"          : "/clone/misc/boss_item/tianshi-guifu",            
        ]);        
                
        mapping  ob_list2 = ([
                "������"            : "/clone/misc/boss_item/jiangjun-ling",
                "��ʿɽ�羰��"      : "/clone/misc/boss_item/fengjing-hua",
                "��ɱ����"          : "/clone/misc/boss_item/ansha-mingdan",
                "����"              : "/clone/misc/boss_item/jiaozi",
                "��ӣ���ޡ�"        : "/clone/misc/boss_item/yinghua-zan",
        ]);                
        
        // ���ת������
        if (! me->query("scborn/ok"))
                return "�㻹û��ͨ��ת�������ܽ��ж�ת��\n";
        
        if (me->query("thborn/ok"))
        {
                if (me->query("thborn/repeat"))// ����2ת
                {
                        tell_object(me, HIG "\n����Խ������¶�ת��\n" NOR);
                        me->move("/kungfu/class/sky/sky2zhuan");
                        return 1;
                }
                return "�㲻���Ѿ���ת���𣬻�����ʲô��\n";
        }

        if (me->query("combat_exp") < 380000000)
                return "���ʵս���鲻��3.8�ڣ����ܽ��ж�ת��\n";
                
        if (me->query_skill("force", 1) < 1500)
                return "������ڹ�����1500���𣬲��ܽ��ж�ת��\n";

        if (me->query_skill("dodge", 1) < 1500)
                return "������Ṧ����1500���𣬲��ܽ��ж�ת��\n";
                
        if (me->query_skill("parry", 1) < 1500)
                return "������мܲ���1500���𣬲��ܽ��ж�ת��\n";

        if (! MEMBER_D->is_valib_member(me->query("id")))
                return "�㲻����Ч��Ա�����ܽ��ж�ת��\n";
                          
        // �Ѿ���������                          
        if (sizeof(me->query("scborn/thborn_item1_id")))
        {
                if (! objectp(ob1 = present(me->query("scborn/thborn_item1_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item1_name") + NOR "���ҵ�����\n";
                }
                if (! objectp(ob2 = present(me->query("scborn/thborn_item2_id"), me)) && ! me->query("scborn/item_ok"))
                {
                        return me->query("scborn/thborn_item2_name") + NOR "���ҵ�����\n";
                }
                /*
                // �����ڼ䲻������սBOSS
                if (me->query("id") != "rcwiz" && me->query("id") != "axiao" && me->query("id") != "mrhy")
                {
                        message_sort(HIM "\n$N" HIM "��$n" HIM "˵�������������������Ѿ�ͨ���˵�һ"
                                         "�ֿ��飬�����ҽ���������޾�̫��֮����ս��ת�ػ��񣬴���ػ�"
                                         "���ɿ�����ת֮�ţ�\n", this_object(), me);
                        tell_object(me, HIG "�޾�̫��֮�Ż�δ�������뱣�������������Ʒ�������ճ�������ϵͳͨ�棡\n" NOR);                                 
                        return 1;
                }
                */
                // �������ҵ���
                if (! me->query("scborn/item_ok"))
                {
                        destruct(ob1);
                        destruct(ob2);
                }
                
                me->set("scborn/item_ok", 1);
                
                message_sort(HIM "\n$N" HIM "��$n" HIM "˵�������������������Ѿ�ͨ���˵�һ"
                                 "�ֿ��飬�����ҽ���������޾�̫��֮����ս��ת�ػ��񣬴���ػ�"
                                 "���ɿ�����ת֮�ţ�\n\n", this_object(), me);

                CHANNEL_D->do_channel(this_object(), "rumor", HIY +  me->name() + "(" + me->query("id") + ")" HIM "���׻�����"
                                                              "�����޾�̫�飬��ս��ת�ػ���" NOR);        
                                                                              
                ob_taixu = new("/kungfu/class/sky/wujin-taixu");
                ob_boss = new("/kungfu/class/sky/npc/shouhushen");
                ob_boss->move(ob_taixu);
                ob_boss->set("myroom", ob_taixu);
                
                FUBEN_D->move_lonely_fb_room(me, ob_taixu, "ϵͳ��ʾ�������޾�̫�飬�뿪����� out ���ڣ�", "", "");        
                
                me->save();                                              
                return 1;                                                              
        }
        else
        {
                keys_item1 = keys(ob_list1);
                keys_item2 = keys(ob_list2);
                
                if (me->query_skill("force", 1) < 1800)
                {                        
                        item1 = keys_item2[random(sizeof(ob_list2))];
                        ob1 = new(ob_list2[item1]);                        
                        //ob_list2 -= ([ item1 ]);
                        keys_item2 -= ({ item1 });
                        item2 = keys_item2[random(sizeof(keys_item2))];                        
                        me->set("scborn/thborn_item1_name", item1);

                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list2[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);        
                }
                else
                {
                        item1 = keys_item1[random(sizeof(ob_list1))];
                        ob1 = new(ob_list1[item1]);                        
                        //ob_list1 -= ([ item1 ]);
                        keys_item1 -= ({ item1 });
                        item2 = keys_item1[random(sizeof(keys_item1))];
                        
                        me->set("scborn/thborn_item1_name", item1);
                        me->set("scborn/thborn_item1_id", ob1->query("id"));
                        me->set("scborn/thborn_item2_name", item2);
                        ob2 = new(ob_list1[item2]);
                        me->set("scborn/thborn_item2_id", ob2->query("id"));
                        destruct(ob1);
                        destruct(ob2);
                }

                message_sort(HIM "\n$N" HIM "��$n" HIM "˵����������򣬼�ʹ����ͨ����һ��ת��"
                                 "��ȡ�˳�Խ���˵����������ǣ��ڶ���ת����Ҫ����ﵽ��ʶ�ϵĳ�"
                                 "�Ѽ��������̲صľ޴��������Ӷ������İ����������������̥���ǡ�"
                                 "�������Ѿ�����˶���ת���Ļ������������ڣ���ֻ��Ҫ��������"
                                 "���飬��������Э������ɶ���ת����\n"
                                 HIM "$N" HIM "���˶ټ���������������ҵ�" + item1 + HIM "��" +
                                 item2 + HIM "�����������ұ����Э��������޾�̫�飬��ս��ת"
                                 "�ػ���\n", this_object(), me);
                     
                tell_object(me, HIG "��ʾ��������ҵ�" + item1 + HIG "��" + item2 + HIG "���ٴ���������Ի���\n" NOR);
        }
        
        me->save();

        return 1;
}

void unconcious()
{
        die();
}
