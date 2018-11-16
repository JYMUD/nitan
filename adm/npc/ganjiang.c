// ganjiang.c  �ɽ�
// Written by Doing Lu  1998/11/2
// Updated by Lonely@NT

// �ɽ����������ߵĳ��������ǲ�������ҵ���Ʒ������������
// ����Ӧ�ú�Īа�򽻵������ player ��Īа���ｫһ��������
// �ף�Īа��ԭ�Ͻ����ɽ���ͨ��accept_object ���������ɽ���
// ���Ƴ���

// �ɽ����յ�Īа�����ĵ��ߣ���������ж������������Ժ���
// ���õ��ߵ������ߣ������ߵ�ID�������õ��ߵ���Ч���� point��
// ��Ϊ��Īа�����Ѿ������ˡ����ҵȺ� player ������ڵ��ߵ�
// ��Ϣ�������ʱ����������˵ı�־�������object������û�
// finish����ѯ�� player �Ƿ����������������ɵ����ļ�����
// �����ɵ����͸� player����������޸ġ�

inherit NPC;
inherit F_NOCLONE;

#include <ansi.h>

// ����ַ��������ó����ֵ����ʾ������ַ������зǷ��ĸ�ʽ
#define ILLEGAL_STR     "."
// ��convertʱ����Ҫ��Ҫȥ����ɫ
#define NOCOLOR         1
#define COLORABLE       0

int mark = 0;
protected int   ask_forging();
protected int   ask_smelting();
protected int   ask_certosina();
protected int   ask_enchanting();
protected int   ask_me();                               // ��ʾ������Ϣ
protected int   show_order();                           // ��ʾ������Ϣ
protected int   start_work(object me, object ob);       // ��ʼ����
protected int   prepare_make(object me, object ob);     // ��ʼ����
protected int   do_show(string arg);
protected int   do_notch(string arg);                   // ���߿���
protected int   start_make(object me, object ob);       // װ��ǩ��
protected void  clear_data();                           // ��� ganjiang, moye, player ����ʱ������ȥ����������
protected object  create_object(object item_temp);
protected string  create_file(object item_temp);
protected int     save_item_file(string filename, string content);
protected void    tell_rules(object me);
protected void    waiting(object me, object ob, object moye);
protected string  converts(string arg, int max_len, int nocolor);
protected string  prop_segment(mapping p, string path);
protected int     save_item_file(string filename, string content);
protected int     legal_chinese(string str);

mapping rings_sockets = ([
        "1" : ({"rune05","rune12","rune18"}),
        "2" : ({"rune06","rune13","rune19"}),
        "3" : ({"rune07","rune14","rune20"}),
]);

mapping equip_sockets = ([
        "1" : ({"rune01","rune06","rune15"}),
        "2" : ({"rune02","rune07","rune16"}),
        "3" : ({"rune03","rune08","rune17"}),
        "4" : ({"rune04","rune09","rune18"}),
        "5" : ({"rune05","rune10","rune19"}),
        "6" : ({"rune06","rune11","rune20"}),
]);

mapping qianghua_rune = ([
        "0" : "rune28",
        "1" : "rune29",
        "2" : "rune30",
        "3" : "rune31",
        "4" : "rune32",
        "5" : "rune33",
        "6" : "rune34",
        "7" : "rune35",
        "8" : "rune36",
]);

mapping suit_level = ([
        "1" : HIC"���"NOR,
        "2" : HIB"ͨ��"NOR,
        "3" : HIM"���"NOR,
        //"4" : HIM"����"NOR,
        "4" : HIY"�컯"NOR,
]);

void create()
{
        seteuid(getuid());

        set_name("�ɽ�", ({ "gan jiang", "ganjiang", "gan" }));
        set("long", "�����ô�׳�������������絶����͸��һ��Ӣ�������ǹ�������������������ʦ��\n" );

        set("nickname", HIR "��ʦ" NOR);
        set("gender", "����");
        set("attitude", "friendly");

        set("age", 1535);
        set("shen_type", 0);

        set("str", 1000);

        set("inquiry", ([
                /*
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "װ��" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "װ��" : (: ask_me :),
                */
                
                "װ��ǩ��": "��BOSS�����װ��ֻ��ǩ��(qianming)����������Լ��ģ������ӵ��summon��hide��������\n",
                "����" : "��Ҫ��װ������(notch)���������˽⿪����Ҫ�ķ���help rune��\n",
                "ǿ������": "��Ҫ֪��ǿ��װ����Ҫ�Ĳ��ϣ���show <װ��id>���һ����������Ĳ��ϡ�\n",
                "����" : "��ֻ������������۴��(notch)��Ѱ����������Ī�ᣬ����һǧ���ƽ𽫴����п۳���\n",
                "���" : "��ֻ������������۴��(notch)��Ѱ����������Ī�ᣬ����һǧ���ƽ𽫴����п۳���\n",
                "ԭ��" : "�����͵���ԭ�ϣ�һ��Ǯ��һ�ֻ�����ԭ�Ͼ��ܳ��ö�����\n",
                "����" : "�����ٵúܣ��������ƽ�Ҫ�������뽻��Īа��\n",
                "�۸�" : "һ��Ǯһ�ֻ�......",
                "����" : "�Ǿ�...�˻�(discard)����...",
                "�˻�" : "�Ǿ�...�˻�(discard)����...",

                "����" : (: show_order :),
                "����" : (: show_order :),
                "order": (: show_order :),

                "ǿ��"    : "��Ҫ֪��ǿ��װ����Ҫ�Ĳ��ϣ���show <װ��>���һ����������Ĳ��ϡ�\n",
                "ǿ��װ��": "��Ҫ֪��ǿ��װ����Ҫ�Ĳ��ϣ���show <װ��>���һ����������Ĳ��ϡ�\n",
                "����"    : (: ask_forging :),
                "���켼��": (: ask_forging :),
                "���켼��": (: ask_forging :),
                "forging" : (: ask_forging :),
                "ұ��"    : (: ask_smelting :),
                "ұ������": (: ask_smelting :),
                "ұ������": (: ask_smelting :),
                "smelting": (: ask_smelting :),
                "��Ƕ"    : (: ask_certosina :),
                "��Ƕ����": (: ask_certosina :),
                "��Ƕ����": (: ask_certosina :),
                "certosina": (: ask_certosina :),
                "��ħ����": (: ask_enchanting :),
                "��ħ����": (: ask_enchanting :),
                "enchanting": (: ask_enchanting :),
                "����װ��": "����װ����õĲ���������֮�����쾧��֮������ָ��Ϊcuilian <װ��> with <����>",
                "����װ��": "��Ҫ����װ��֮�꼰����֮��ҾͰ������װ��(reform <װ��> with <װ��֮��>)��ŷұ��ʥ���������ӳɹ��ʡ�",
                "��װ"    : "�̻���װ����Ҫ������֮�ģ������������֮�ĵĻ����ҾͰ����̻�(douit <װ��>)��װ��",
                "������װ": "������װ����Ҫ�к���������ָ���ʽupsuit <װ��>",
        ]));

        set_skill("literate",  120);            // ����д��
        set_skill("forging",   2000);            // ���켼��
        set_skill("smelting",  2000);            // ұ������
        set_skill("certosina", 2000);            // ��Ƕ����
        set_skill("enchanting", 2000);            // ��ħ����

        set("no_teach", ([
                "literate" : "�ҿɲ��ǽ���������",
        ]));

        setup();

        set("startroom", "/d/item/xiaowu");
        check_clone();
        if (! this_object()) return;

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_name", "name");
        add_action("do_name", "����");
        add_action("do_desc", "desc");
        add_action("do_desc", "����");
        //add_action("do_level", "level");
        //add_action("do_level", "�ȼ�");
        add_action("do_wieldmsg", "wieldmsg");
        add_action("do_wieldmsg", "wearmsg");
        add_action("do_wieldmsg", "װ��");
        add_action("do_wieldmsg", "װ����Ϣ");
        add_action("do_unwield", "unwieldmsg");
        add_action("do_unwield", "removemsg");
        add_action("do_unwield", "����");
        add_action("do_unwield", "������Ϣ");
        add_action("do_finish", "finish");
        add_action("do_finish", "���");

        add_action("do_increase", "qianghua"); // ǿ��װ��
        add_action("do_reform", "reform"); // ����װ��
        add_action("do_suit", "dosuit"); // ��װ�׻�
        add_action("do_cuilian", "cuilian"); // ����װ��
        add_action("do_upsuit", "upsuit"); // ��װ����

        add_action("do_help", "help");
        add_action("do_help", "����");

        add_action("do_show", "show");
        add_action("do_notch", "notch"); // ����
        add_action("do_discard", "discard"); // ����
        add_action("do_signature", "qianming"); // װ��ǩ��

        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang"); 
}

// ������ʾ��Ϣ
protected int ask_me()
{
        message_vision("�ɽ���$N˵������Щ������Īа����ֻ��������\n", this_player());
        return 1;
}

// ��֤ѧϰ
int recognize_apprentice(object me)
{
        if( !query_temp("learnd_from/�ɽ�", me) )
        {
                message_vision("�ɽ���$N˵���ã����Ȼ����ѧ���Ҿ�"
                               "����һ��ɡ�\n", me);
                set_temp("learnd_from/�ɽ�", 1, me);
        }
        return 1;
}

// �ش��й���Ƕ���յ���Ϣ
protected int ask_certosina()
{
        message_sort("�ɽ���$N˵���������ﲻ������Ƕ�Ļ����"
                     "����������Ȥ�Ļ����ҿ��Խ���һ����Ƕ��"
                     "������\n", this_player());
        return 1;
}

protected int ask_forging()
{
        message_sort("�ɽ���$N˵���������ﲻ�������Ļ����"
                     "����������Ȥ�Ļ����ҿ��Խ���һ������"
                     "������\n", this_player());
        return 1;
}

protected int ask_smelting()
{
        message_sort("�ɽ���$N˵���������ﲻ����ұ���Ļ����"
                     "����������Ȥ�Ļ����ҿ��Խ���һ��ұ����"
                     "������\n", this_player());
        return 1;
}

protected int ask_enchanting()
{
        message_sort("�ɽ���$N˵���������ﲻ����ħ�Ļ����"
                     "����������Ȥ�Ļ����ҿ��Խ���һ�㸽ħ��"
                     "������\n", this_player());
        return 1;
}
        
int accept_object(object me, object ob)
{
        if( query_temp("item") ) return notify_fail("�ɽ���æ���أ��ԵȻᡣ\n");
        
        if (me->name(1) == "Īа")
        {
                if( query("id", me) != "mo ye" )
                {
                        command("kick "+query("id", me));
                        message_vision("$N�ٺٵļ�Ц����������$n˵����"
                                       "����Ϊȡ�������ӵ����־����ɱ�"
                                       "�ң��һ�ûϹ�أ�\n",
                                       this_object(), me);
                        return 1;
                }
                start_work(query("item/owner", ob),ob);
                return 1;
        }
        
        if (ob->is_item_make())
        {
                if( ob->item_owner() != query("id", me) )
                {
                        command("heng");
                        command("say ������Ķ�����û���ˣ�");
                        destruct(ob);
                        return 1;
                }
                message_vision("$N�ɻ������$n��������������"
                               "����ô���Ǿ��˵�(discard)�ɣ���\n",
                               this_object(), me);
                return 0;
        }
        else if( query("id", ob) == "wangzhe zhixin" )
        {
                message_vision("�ɽ���$N˵����������֮�ģ�����װ���Ϳ����̻���װ��(dosuit)������"
                               "�̻���װʲô���ߣ�\n", me);
                set_temp("paid/dosuit", 1, me);
                destruct(ob);
                return 1;
        }

        message_vision("�ɽ�����Ķ�$N˵�����������Щ������ʲ"
                       "ô����������������Щ������\n", me);
        return 0;
}

protected int start_work(object me, object ob)
{
        remove_call_out("prepare_make");
        call_out("prepare_make", 1, me, ob);
        set_temp("item/making", ob);
        set_temp("item/player", me);
        set_temp("item/status", "waiting", me);
        return 1;
}

protected int prepare_make(object me, object ob)
{
        message_vision(HIC "\n$N˵�����ã���¯������\n\n" NOR, this_object());
        message_vision(HIM "$N�ӹ�Īа���е�" + ob->name() +
                       HIM "�����ְ�������¯�ڣ���ʱ�䣬��" + ob->name() +
                       HIM "�ѱ���¯�е�����" HIR "����" HIM "��û��\n" +
                       "$N������¯����˵�������֮����Ϊ��Ѫ������"
                       "��֮�����������......\n\n" NOR , this_object());
        remove_call_out("work_step_1");
        call_out("work_step_1", 5, me, ob);
        return 1;
}

protected int work_step_1(object me, object ob)
{
        message_vision(HIG "¯�𽥽���ת������ɫ�����粻����Ծ���������"
                       "��ʮ�����ȣ����Ǹɽ�Īа�������¡�\n\n" NOR, this_object());

        if (objectp(me) && environment(me) == environment())
        {
                set_temp("item/can_help", 1, me);
                message_vision(HIW "$N��$n˵��������������ø��ã���"
                               "Ҫע���Լ��ľ���Ѫ�����������д��⣬��"
                               "��(help)��һ��֮����\n\n", this_object(), me);
        }
        remove_call_out("work_step_2");
        call_out("work_step_2", 6, me, ob);
        return 1;
}

protected int work_step_2(object me, object ob)
{
        message_vision(RED "¯�𵭵��İ������������ֳ�һƬ��ɫ......\n\n" NOR, this_object());
        remove_call_out("work_step_3");
        if (objectp(me))
                delete_temp("item/can_help", me);
        call_out("work_step_3", 3, me, ob);
        return 1;
}

protected int work_step_3(object me, object ob)
{
        message_vision(HIW "$N���ֳ���������һ�����Ѿ�ȡ����" + ob->name() +
                       HIW "�����ֳֽ�մ��۾��������������\n�����ģ�" + ob->name() +
                       HIW"�ڸɽ����µĳ���"+query("item/ctype", ob)+
                       HIW "����״��\n\n" NOR, this_object());
        remove_call_out("work_step_4");
        call_out("work_step_4", 5, me, ob);
        return 1;
}

protected int work_step_4(object me, object ob)
{
        message_vision(HIC"$N������ϣ����һ������"+query("item/ctype", ob)+
                       HIC "����ˮ�أ�ֻ��˿˿���죬��ˮ������һ��������"
                       "�������ܡ�\n\n" NOR, this_object());
        remove_call_out("work_step_5");
        call_out("work_step_5", 3, me, ob);
        return 1;
}

protected int work_step_5(object me, object ob)
{
        message_vision(HIW"$N�����Ĵ�ˮ�س�������õ�"+query("item/ctype", ob)+
                       HIW "���˿��������˵���ܺã��ܺá�\n\n" NOR,
                       this_object());
        remove_call_out("work_step_6");
        call_out("work_step_6", 2, me, ob);
}

protected int work_step_6(object me, object ob)
{
        object moye;

        if (! objectp(moye = present("mo ye")))
        {
                message_vision(HIW "�ɽ����˿����ܣ�˵�����ף�Īа�أ�"
                               "�������ˣ������ˣ�ȥ�ɣ�\n"
                               "�ɽ������õĵ����׽���¯���ʹ˲�����\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                return 1;
        }

        if (! objectp(me))
                me = find_player(query("item/owner_id", ob));

        if (! objectp(me) || environment(me) != environment())
        {
                message_vision(HIW "$N̾�˿�����˵��������Ϊ�����ȥ"
                               "�ˣ������˰��ˣ������ˣ�ȥ�ɣ�\n"
                               "$N�����õĵ����׽���¯���ʹ˲�����\n\n" NOR,
                               this_object());
                if (objectp(me))
                        delete_temp("item", me);

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item");
                delete_temp("item", moye);
                return 1;
        }
        set_temp("item/status", "waiting", moye); 
        set_temp("item/status", "inputing", me); 
        message_vision("$N��$n˵����һ"+query("item/unit", ob)+"��"+
                       query("item/ctype", ob)+NOR"����û�����֣������������ְɣ�\n",
                       this_object(), me);

        tell_rules(me);

        // ������ߵ����֣�ID�����������ԣ��������õ��ߵļ�ֵ��������
        set("item/long", "", ob);
        set("item/wield_msg", "", ob);
        set("item/wear_msg", "", ob);
        set("item/unwield_msg", "", ob);
        set("item/remove_msg", "", ob);
        set("item/owner_name",query("name",  me), ob);
        set("item/owner_id",query("id",  me), ob);

        // ���õȴ�ʱ�䣬���3��
        set_temp("item/waited", 4);

        // �����ʱ����������
        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
        return 1;
}

// ����������¯����ߵ��ߵȼ�
// Ҫ�󣺾� >= 180  �� >= 300  ������Ч�ȼ� >= 100  ���� >= 800 ������� >= 1000
// ������ķ� 200 ��������������� 10%
int do_help(string arg)
{
        object me;
        object ob;

        me = this_player();
        if( query_temp("item/status", me) != "waiting" )
        {
                return notify_fail("û��ʲôҵ��\n");
        }
        if( !query_temp("item/can_help", me) )
        {
                if (arg) return 0;
                write("���ڲ������æ��ʱ��\n", me);
                return 1;
        }
        if( query("jing", me)<180 )
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е�����˥�ߡ�\n" NOR);
                set("jing", 0, me);
                return 1;
        }
        me->receive_damage("jing", 180);
        if( query("qi", me)<300 )
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е��������̡�\n" NOR);
                set("qi", 0, me);
                return 1;
        }
        me->receive_damage("qi", 300);
        if( query("neili", me)<800 || query("max_neili", me)<1000 )
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е������ݽߡ�\n" NOR);
                set("neili", 0, me);
                return 1;
        }
        message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ�ɲ�Ǽ䣬¯����ڣ�"
                       "һ��" HIW "�׹�" HIR "��ֱ��������\n\n" NOR, me);

        ob = query_temp("item/making");
        // ���ﴦ��������ϵ�Ч��
        addn("item/point",query("item/point",  ob)*me->query_skill("force")/500, ob);
        addn("item/point",query("item/power",  ob), ob);
        delete_temp("item/can_help", me);
        addn("max_neili", -200, me);
        addn("neili", -200, me);
        return 1;
}

protected int show_order()
{
        object me;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
        {
                message_vision("$N������������������$n��\n",
                               this_object(), me);
                return 1;
        }

        tell_rules(me);
        return 1;
}

void tell_rules(object me)
{
        tell_object(me, CYN @RULES
�ɽ������������˵����
������Ҫ��������������Ϣϵͳ��ȱʡ����������ȻҲ���������Լ�Ϊ���Զ�������
��Ȼ�ˣ���ò����ñ������Ĵ����־��ޡ�����ķ������¡�
    ����: name �������� Ӣ�Ĵ��š�   (������)
    ����: desc �������������֡�      (��  ѡ)
    װ��: wieldmsg   װ��ʱ��������  (��  ѡ)
    ����: unwieldmsg ����ʱ��������  (��  ѡ)
����ʱ��������\n������Ӣ�Ĵ����������е����ֶ���������ɫ��ʹ����ɫ�ķ������Բ���nick ��
�������ÿ����ˣ����������(finish)��Ҫ��û������������������� < ���� >

RULES NOR);
}

void waiting(object me, object ob, object moye)
{
        if (! objectp(me))
                me=find_player(query("item/owner_id", ob));

        if (! objectp(me))
        {
                message_vision("$N̾�˿���˵������ô�����ˣ�������"
                               "�ˣ�ȥ�ɣ�\n", this_object());
                if (objectp(moye))
                        delete_temp("item", moye);

                delete_temp("item");
                destruct(ob);
                return;
        }

        if (addn_temp("item/waited", -1) <= 0)
        {
                // �ȴ���ʱ
                if (objectp(moye))
                        delete_temp("item", moye);

                log_file("static/item", sprintf("%s %s do timeout when make item of %s\n",
                                 log_time(), log_id(me),
                                 (ob ? filter_color(ob->name(1)) : "???")));
                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("item", me);
                delete_temp("item");
                if (in_input(me)) return;
                if (environment(me) == environment())
                {
                        message_vision("$N������üͷ˵����������ô��ô"
                                       "ĥ�䣬���ˣ���Ҫ�Ͳ�Ҫ�ɣ�\n",
                                       this_object());
                        return;
                }
                message_vision("$N������üͷ��$n˵������������ô��ô"
                               "ĥ�䣬��Ҫ�����ˣ�ˡ���˿\n",
                               this_object(), me);
                return;
        }

        if (environment(me) != environment())
        {
                message_vision("$N�ɻ��˵��������ô�ܵ��ˣ����ˣ��ٵ�"
                               "��һ��ɡ�\n", this_object());
        } else
        if (! in_input(me))
        {
                message_vision(HIR "$N" HIR "��$n" HIR
                               "������㣬��㣬��ĥ�䣬�����ҿɾͲ����ˡ�\n" NOR,
                               this_object(), me);
        }

        remove_call_out("waiting");
        call_out("waiting", 300, me, ob, moye);
}

protected void clear_data()
{
        object me;
        object ob;
        object moye;

        if (objectp(moye = present("mo ye")))
                delete_temp("item", moye);

        if (objectp(ob = query_temp("item/making")))
                destruct(ob);

        if (objectp(me = query_temp("item/player")))
                delete_temp("item", me);

        delete_temp("item");
        remove_call_out("waiting");
}

int do_level(string arg)
{
        object me, ob;
        int level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! arg || sscanf(arg, "%d", level) != 1)
        {
                write("��ʽ���ԣ�Ӧ���ǣ�level �ȼ�\n���磺level 30\n");
                return 1;
        }

        if( level<10 || level>query("level", me) )
        {
                write("װ���ĵȼ���Ͳ���С��10�������Ҳ���ܸ��������ڵ�����ȼ���\n");
                return 1;
        }

        if (level%10 != 0)
        {
                write("װ���ĵȼ�������10�ı�����\n");
                return 1;
        }

        ob = query_temp("item/making");
        set("item/level", level, ob);
        write(CYN "���������" + level + "���ĵ��ߡ�\n" NOR);
        return 1;
}

int do_name(string arg)
{
        object me;
        object ob;
        string pname;
        string sname, sid;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! arg || sscanf(arg, "%s %s", sname, sid) != 2)
        {
                write("��ʽ���ԣ�Ӧ���ǣ����� �������� Ӣ������\n���磺���� ���� sword\n");
                return 1;
        }

        // ILLEGAL_STR = "." ��ʾ�Ƿ�������
        if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
                return 1;

        if ((sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR)
                return 1;

        if (! sname || ! sid)
        {
                message_vision("$Nҡҡͷ����$n�������в��У���úø��������֣�\n",
                               this_object(), me);
                return 1;
        }

        if( file_size(ITEM_DIR+query("id", me)[0..0]+"/"+
                      query("id", me)+"-"+sid+".c") != -1 )
        {
                message_vision("$Nҡҡͷ����$n�������ã��㲻Ҫ����(" + sid +
                               ")���Ӣ�Ĵ����ˣ���һ���ɣ�\n",
                               this_object(), me);
                return 1;
        }

        if (! is_chinese(filter_color(sname)))
        {
                command("kick "+query("id", me));
                command("say ����д��������ô�ģ�");
                return 1;
        }

        if (! is_legal_id(sid))
        {
                command("say Ӣ�Ĵ��ű���ȫ����СдӢ�Ĳſ��ԣ�");
                return 1;
        }

        if (strlen(filter_color(sname)) < 4)
        {
                command("say ��˵�����������Ҳ̫���˰ɣ������������֣�");
                return 1;
        }

        if (strlen(sid) < 3)
        {
                command("say ��˵����������Ҳ̫���˰ɣ����������ַ���");
                return 1;
        }

        if (sid == "cruise")
        {
                command("say ����������ΰ�ר�ô��ţ�������ѡ����ţ�");
                return 1;
        }

        if (sname[0] == 27 &&
            sname[4] == 'm')
        {
                // Add color prefix
                sname = NOR + sname;
        }

        ob = query_temp("item/making");
        set("item/name", sname, ob);
        set("item/id", sid, ob);

        write("���֣�" CYN + sname + "    ���ţ�" CYN + sid + NOR "\n");
        return 1;
}

int do_desc(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("���ո�ʽ��Ӧ���� desc ���������֡�\n���磺һ��"
                      "������$n\\n������������������ -- ����\\n��ʾ���У�$n������ߡ�\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        arg = replace_string(arg, "$N", me->name(1));

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
                return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");

        arg=replace_string(arg,"$n",query("item/name", ob));
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");
        arg = chinese_desc(arg);
        set("item/long", arg, ob);
        write(CYN "����۲�����ʱ�򽫻��������������\n" NOR + arg + "\n");
        return 1;
}

int do_wieldmsg(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !objectp(ob) ) return 0;
        if( !query("item/name", ob) )
        {
                message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("���ո�ʽ��Ӧ���� wieldmsg ���������֡�\n���磺"
                      "$N����һ�������һ�ѷ��������� -- ����$N��ʾ����"
                       "����$n������ߡ�\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
                return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");

        // ���ﲻ������������װ�����������ļ�ʱ�Զ�ѡ��һ����Ϣ
        /*
        arg = "��" + arg;
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        arg = replace_string(arg, "\\n", "\n��");
        set("item/wear_msg", arg, ob);
        set("item/wield_msg", arg, ob);
        */
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/wear_msg", arg, ob);
        set("item/wield_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg = replace_string(arg, "$N", me->name(1));
        arg=replace_string(arg,"$n",query("item/name", ob));
        write(CYN "����װ������ʱ�򽫻��������������\n" NOR + arg + "\n");
        return 1;
}

int do_unwield(string arg)
{
        object ob;
        object me;
        string chk;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        ob = query_temp("item/making");
        if( !query("item/name", ob) )
        {
                message_vision("$N����$nһ�۵����㻹���ȸ���ȡ�������ٿ��������ɣ�\n",
                               this_object(), me);
                return 1;
        }

        if (! arg)
        {
                write("��ʽ���ԣ�Ӧ���ǣ�unwield ���������֡�\n���磺"
                       "$N����һ�ӣ�$n�������ڡ� -- ����$N��ʾ���Լ���$n������ߡ�\n");
                return 1;
        }

        if ((arg = converts(arg, 200, COLORABLE)) == ILLEGAL_STR)
                return 1;

        chk = filter_color(arg);
        if (strlen(chk) >= 2 && chk[0..1] == "��" || strsrch(chk, "\\n��") != -1)
                return notify_fail("�Բ������������ԡ��㡱�ִ�ͷ��\n");

        chk = replace_string(chk, " ", "");
        chk = replace_string(chk, "\\n", "");
        chk = replace_string(chk, "$N", "");
        chk = replace_string(chk, "$n", "");
        if (! legal_chinese(chk))
                return notify_fail("�Բ�����������ʹ�ú��ֺ�ϵͳ�涨����ʹ�õĴ�����š�\n");

        // ���ﲻ������������װ�����������ļ�ʱ�Զ�ѡ��һ����Ϣ
        /*
        arg = "��" + arg;
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        arg = replace_string(arg, "\\n", "\n��");
        set("item/unwield_msg", arg, ob);
        set("item/remove_msg", arg, ob);
        */
        arg = chinese_desc(arg);
        arg = replace_string(arg, me->name(1), "$N");
        set("item/unwield_msg", arg, ob);
        set("item/remove_msg", arg, ob);
        arg = replace_string(arg, "\\n", "\n");
        arg=replace_string(arg,"$N",query("name", me));
        arg=replace_string(arg,"$n",query("item/name", ob));
        write(CYN "�����ջ�����ʱ�򽫻��������������\n" NOR + arg + "\n");
        return 1;
}

// �ж��Ƿ��ǺϷ��ĺ���
protected int legal_chinese(string str)
{
        int i;

        if (strlen(str) < 2) return 0;

        for (i = 0; i < strlen(str); i++)
        {
                if (str[i] < 161 || str[i] == 255) return 0;
                if ((! (i % 2)) && str[i] >= 248) return 0;
        }

        return 1;
}

// ת���ַ����е���ɫ��־
protected string converts(string arg, int max_len, int no_color)
{
        int i;

        // ȥ���ַ����еĿո����ţ����ⱻ�����������ƻ�
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for (i = 0; i < strlen(arg) - 1; i++)
        {
                if (arg[i] == '\\' && arg[i + 1] != 'n')
                {
                        write("�ַ�'\\'����ֻ�ܸ���n�ַ���ʾ�س���\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "��");
        arg = replace_string(arg, ":", "��");
        arg = replace_string(arg, "?", "��");

        if (no_color)
        {
                arg = filter_color(arg, 1);
        } else
        {
                arg = trans_color(arg, 3);
                if (strlen(arg) < strlen(NOR) ||
                    arg[strlen(arg) - strlen(NOR)..<1] != NOR)
                {
                        // append NOR at tail
                        arg += NOR;
                }
        }
        if (strlen(arg) > max_len + 30 ||
            strlen(filter_color(arg)) > max_len)
        {
                write("�Բ�������ַ���̫���ˣ��벻Ҫ���볬��" + chinese_number(max_len) +
                      "���ַ������ַ�����\n");
                // ��ʾ�Ƿ�������
                return ILLEGAL_STR;
        }
        return arg;
}

int do_finish()
{
        object me;
        object ob;
        object moye;
        string msg;
        int    level;

        me = this_player();
        if( query_temp("item/status", me) != "inputing" )
                return 0;

        if (! objectp(ob = query_temp("item/making")))
        {
                // ���ݲ��ԣ�����������BUG��ɣ�Ҳ��������Ϊ�ɽ���update��
                write("ϵͳ���ϣ����ݲ�һ�£����޷�������Ƶ��ߣ�\n");
                delete_temp("item", me);
                delete_temp("item");
                if (objectp(moye = present("mo ye")))
                        delete_temp("item", moye);

                // ����ʧ�ܣ�ֹͣ����
                return 0;
        }

        if( !query("item/name", ob) )
        {
                message_vision("$N����$nһ�ۣ�˵��������ô�ܲ��������"
                               "���֣���Ҫ�ǲ���Ҫ�˾����ˣ�\n",
                               this_object(), me);
                return 1;
        }

        if( !query("item/id", ob) )
        {
                message_vision("$N����$nһ�ۣ�˵��������ô�ܲ��������"
                               "���ţ���Ҫ�ǲ���Ҫ�˾����ˣ�\n",
                               this_object(), me);
                return 1;
        }
        
        /*
        level = query("item/level", ob);
        if (! level)
        {
                level=(query("level", me)/10)*10;
                set("item/level", level, ob);
        }
        */
        
        // ��ʾ player �������Ϣ
        msg = sprintf("�ɽ���$N˵����ĵ����������£��뿴����û�д�\n");
        message_vision(msg, me);
        // ˽����Ϣ
        msg = sprintf("�������֣�%s   ����Ӣ�Ĵ��ţ�%s\n\n",
                      query("item/name", ob),query("item/id", ob));

        //msg += sprintf("���ߵȼ���%d\n\n",query("item/level", ob));

        if( query("item/long", ob) != "" )
                msg += sprintf(CYN"����������£�"NOR"\n%s\n\n",query("item/long", ob));
        else
                msg += "����ȱʡ�����������\n";

        if( query("item/wield_msg", ob) != "" )
                msg += sprintf(CYN "װ��ʱ�������£�" NOR "\n%s\n\n",
                               replace_string(query("item/wield_msg", ob),"\\n","\n"));
        else
                msg += "װ��ʱ����ȱʡ��������\n";

        if( query("item/unwield_msg", ob) != "" )
                msg += sprintf(CYN "�ջ�ʱ�������£�" NOR "\n%s\n\n",
                               replace_string(query("item/unwield_msg", ob),"\\n","\n"));
        else
                msg += "�ջ�ʱ����ȱʡ��������\n";
                msg += CYN "���û�����⣬�Ϳ��Լ���������(y/n):" NOR;
        msg=replace_string(msg,"$N",query("name", me));
        msg=replace_string(msg,"$n",query("item/name", ob));

        tell_object(me, msg);

        // �ж� player �Ƿ�������ɵ���
        input_to("confirm_make", ob);
        return 1;
}

void confirm_make(string arg, object ob)
{
        mapping enchase, insert, require;
        mapping temp = ([]);
        object me;
        object moye;
        object item;
        string item_filename;
        int rate, level, quality_level;

        me = this_player();

        if (!objectp(query_temp("item/making")))
        {
                command("kick "+query("id", me));
                command("say ��̫ĥ���ˣ��������Ҳ����ˣ�ˡ���˻���");
                return;
        }

        if (arg != "y" && arg != "Y")
        {
                message_vision("$N�Ե������㻹���ٿ����ɣ�\n", this_object());
                return;
        }

        message_vision("$N��$n˵�����ã����Ͼͺã�\n",
                       this_object(), me);

        if (item_filename = create_file(ob))
        {
                // clear the old item's data
                //level = query("item/level", ob);
                enchase = query("item/enchase", ob);
                insert  = query("item/insert", ob);
                require = query("item/require", ob);
                quality_level = query("item/quality_level", ob);
                
                DBASE_D->set_object_data(ob, 0);
                destruct(ob);
                
                /*
                temp["level"] = level;
                rate = random(100);
                if( rate < 40 ) temp["str"] = level*2 + random(level);
                else if( rate < 60 ) temp["con"] = level*2 + random(level);
                else if( rate < 80 ) temp["dex"] = level*2 + random(level);
                else temp["int"] = level*2 + random(level);
                */
                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);
                if (! ob)
                {
                        message_vision("$Nһ������$n������Ǹ��Ǹ������һЩ���⣡\n",
                                       this_object(), me);
                } else
                {
                        //set("require", temp, ob);
                        set("require", require, ob);
                        set("enchase", enchase, ob);
                        set("insert", insert, ob);
                        set("quality_level", quality_level, ob);
                        set("status", 1, ob);
                        set("consistence", query("max_consistence", ob), ob);
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database();
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        ob->move(me, 1);
                        ob->save();             // Create the record in dbase
                        message_vision("$N��"+query("name", ob)+"������$n��\n",
                                       this_object(), me);
                        
                        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/makeweapon");
                        log_file("static/item", sprintf("%s %s created  %s(%s)\n",
                                 log_time(), log_id(me),
                                 filter_color(ob->name(1)),query("id", ob)));
                }
        }
        if (objectp(moye = present("mo ye", environment())))
                delete_temp("item", moye);

        delete_temp("item", me);
        delete_temp("item");
        remove_call_out("waiting");
}

// ���ɵ����ĵ�, ��Ҫһ���ĵ���ԭ�϶���
// �����Ժ��� ITEM_DIR/???.c Ȼ��ɾ���ɵ�ԭ�϶���, ����һ���µĵ��ߣ������ļ���

// ����ԭ�϶���������Ե�˵��(item/)
// ------ �û���������������
// name                 ���ߵ����ƣ� ����Ҫ
// id                   ���ߵ�ID��   ����Ҫ
// long                 ���ߵ�������ϵͳ�������ɵ���ʱ�Զ���ӹ�������ԭ�ϵ�����
// wield_msg            װ�����������������û��ϵͳ���Զ�����
// unwield_msg          �ջ�����ʱ������
// wear_msg             ���ϻ���ʱ������
// unwear_msg           �ѵ�����ʱ������

// ------ �����û�����������
// owner_id             �����ߵ�ID
// owner_name           �����ߵ�����
// unit                 ��λ
// type                 ���ߵ����� weapon �� armor
// stype                ���ߵ������ weapon Ϊ sword, blade, whip, stick �� armor Ϊ armor
// ctype                ���ߵ����������� weapon Ϊ ���������ޡ��� �� armor Ϊ ����
// value                ���ߵļ�ֵ
// point                �˺���

// ------ ˵�����û������ĵ��ߵ�����
// item_make            1

protected object create_object(object item_temp)
{
        string  filename;
        string  desc;
        mapping info;
        string  id;
        object ob;

        info=query("item", item_temp);
        id = info["id"];
        if (info["type"] == "weapon")
        {
                desc="������"+query("material_name", item_temp)+"���ƶ��ɵ�һ"+
                       info["unit"] + info["ctype"] + "��\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                info["long"] = desc;

                info["makeinfo"] = info["ctype"] + "���Ͽ���һ��С�֣�" +
                        info["owner_name"] + "(" + info["owner_id"] + ")\n";

                if (info["wield_msg"] == "")
                {
                        info["wield_msg"] = HIC "$N" HIC "һ����Х��" +
                                            (info["stype"] == "throwing" ? "����һ" : "����һ") +
                                            info["unit"] + HIC "$n" HIC "��" NOR;
                }

                if (info["unwield_msg"] == "")
                {
                        info["unwield_msg"] = "$N����һĨ��������$n��";
                }
                info["wield_msg"] += "\n";
                info["unwield_msg"] += "\n";
                info["max_consistence"] = info["point"];
                info["material"]=query("material_attrib", item_temp);
                info["material_file"] = base_name(item_temp);

                filename = sprintf("/inherit/self/weapon/%s.c", info["stype"]);
                //ob = TEMPLATE_D->create_object(filename, id, info, 0, (["init_damage" : info["point"]*2]));
                ob = TEMPLATE_D->create_object(filename, id, info, 0);
                if( !objectp(ob) )
                        return 0;
                //ob->init_damage(info["point"]*2);
        }
        else
        {
                desc="������"+query("material_name", item_temp)+"���ƶ��ɵ�һ"+
                       info["unit"] + info["ctype"] + "��\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                info["long"] = desc;

                info["makeinfo"] = info["ctype"] + "Ե�Ͽ���һ��С�֣�" +
                        info["owner_name"] + "(" + info["owner_id"] + ")\n";

                if (info["wear_msg"] == "")
                {
                        info["wear_msg"] = YEL "$N" YEL "װ��" +
                                           YEL "$n" YEL "��" NOR;
                }
                if (info["remove_msg"] == "")
                {
                        info["remove_msg"] = YEL "$N" YEL "������" +
                                             YEL "$n" YEL "��" NOR;
                }
                info["wear_msg"] += "\n";
                info["remove_msg"] += "\n";
                info["max_consistence"] = info["point"];
                info["material"]=query("material_attrib", item_temp);
                info["material_file"] = base_name(item_temp);

                filename = sprintf("/inherit/self/armor/%s.c", info["stype"]);
                //ob = TEMPLATE_D->create_object(filename, id, info, 0, (["init_armor" : info["point"]*2]));
                ob = TEMPLATE_D->create_object(filename, id, info, 0);
                if( !objectp(ob) )
                        return 0;
                //ob->init_armor(info["point"]*2);
        }

        return ob;
}

protected string create_file(object item_temp)
{
        string  buf;                    // �����ļ��Ļ�����
        string  filename;
        string  desc;
        int     i;
        mapping info;
        string  ih;
        string  id;

        // �����ļ���
        id = query("item/owner_id", item_temp);
        filename = ITEM_DIR + id[0..0] + "/" + id +
                   "-"+query("item/id", item_temp)+".c";
        if( file_size(filename) != -1 )
        {
                write("�޷����ɵ�������֪ͨ��ʦ����\n");
                return 0;
        }
        assure_file(filename);
        buf="//ITEMMadebyplayer("+query("item/owner_name", item_temp)+
              ":"+query("item/owner_id", item_temp)+")"+filename+
              "\n// Written by GAN JIANG(Doing Lu 1998/11/2)\t" + ctime(time()) + "\n";
        info = query("item", item_temp);
        ih = up_case(info["stype"]);
        if( info["type"] == "weapon" )
        {
                // �������������ļ�
                desc = "������"+info["material_name"]+"���ƶ��ɵ�һ"+
                       info["unit"] + info["ctype"] + "��\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "���Ͽ���һ��С�֣�" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " ��Ʒ\n" NOR;

                // �Զ��������Ϣ
                if( info["wield_msg"] == "" )
                {
                        info["wield_msg"] = HIC "$N" HIC "һ����Х��" +
                                            (info["stype"] == "throwing" ? "����һ" : "����һ") +
                                            info["unit"] + HIC "$n" HIC "��" NOR;
                }

                if( info["unwield_msg"] == "" )
                {
                        info["unwield_msg"] = "$N����һĨ��������$n��";
                }

                buf += "#include <ansi.h>\n";
                buf += "#include <weapon.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                if( info["stype"] == "throwing" )
                {
                       buf += sprintf("\tset(\"base_weight\", %d);\n",
                                       item_temp->query_weight()*query("item/wscale", item_temp)/10000);
                       buf += sprintf("\tset(\"base_unit\", \"ö\");\n");
                       // buf += sprintf("\tset(\"base_value\", %d);\n", info["value"] / 100);
                       buf += sprintf("\tset(\"base_value\", 1);\n");
                }
                buf += sprintf("\tset(\"point\", %d);\n", info["prop"]["weapon_prop"]["damage"]);
                //buf += sprintf("\tset(\"consistence\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\",\"%s\");\n",info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                if( info["stype"] == "throwing" )
                {
                        buf += sprintf("\tset(\"hand_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unhand_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                } else
                {
                        buf += sprintf("\tset(\"wield_msg\", \"%s\\n\");\n", info["wield_msg"]);
                        buf += sprintf("\tset(\"unwield_msg\", \"%s\\n\");\n", info["unwield_msg"]);
                }
                buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
                if (info["stype"] == "throwing")
                        buf += sprintf("\tset_amount(100);\n");   
                buf += sprintf("\tinit_%s(apply_damage());\n", info["stype"]);    
                buf += prop_segment(info["prop"], "");    
                buf += sprintf("\n\tsetup();\n}\n\n");
                // �������������ļ����
        }
        else
        {
                // ���ɷ��������ļ�
                desc="������"+info["material_name"]+"���ƶ��ɵ�һ"+
                       info["unit"] + info["ctype"] + "��\n";

                desc += info["long"];
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                //info["makeinfo"] = info["ctype"] + "���Ͽ���һ��С�֣�" +
                //        info["owner_name"] + "(" + info["owner_id"] + ")\n";
                info["makeinfo"] = HIR "\n" + info["owner_name"] + "(" + info["owner_id"] + ")" + HIR " ��Ʒ\n" NOR;

                // �Զ��������Ϣ
                if (info["wear_msg"] == "")
                {
                        info["wear_msg"] = YEL "$N" YEL "װ��" +
                                           YEL "$n" YEL "��" NOR;
                }
                if (info["remove_msg"] == "")
                {
                        info["remove_msg"] = YEL "$N" YEL "������" +
                                             YEL "$n" YEL "��" NOR;
                }
                buf += "#include <ansi.h>\n";
                buf += "#include <armor.h>\n\n";
                buf += "inherit " + ih + ";\n";
                buf += "inherit F_ITEMMAKE;\n\n";
                buf += "void create()\n{\n";
                buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n",
                                info["name"], info["id"]);
                buf += sprintf("\tset_weight(%d);\n",
                                item_temp->query_weight()*query("item/wscale", item_temp)/100);
                buf += sprintf("\tset(\"item_make\", 1);\n");
                buf += sprintf("\tset(\"unit\", \"%s\");\n", info["unit"]);
                buf += sprintf("\tset(\"long\", \"%s\");\n", desc);
                buf += sprintf("\tset(\"makeinfo\", \"%s\");\n", info["makeinfo"]);
                buf += sprintf("\tset(\"value\", %d);\n", info["value"]);
                buf += sprintf("\tset(\"point\", %d);\n", info["prop"]["armor_prop"]["armor"]);
                //buf += sprintf("\tset(\"consistence\", %d);\n", info["point"]);
                buf += sprintf("\tset(\"max_consistence\", %d);\n", 100);
                buf += sprintf("\tset(\"material\",\"%s\");\n",info["material_attrib"]);
                buf += sprintf("\tset(\"material_file\", \"%s\");\n", info["material_file"]);
                buf += sprintf("\tset(\"wear_msg\", \"%s\\n\");\n", info["wear_msg"]);
                buf += sprintf("\tset(\"remove_msg\", \"%s\\n\");\n", info["remove_msg"]);
                buf += sprintf("\tif (! check_clone()) return;\n\trestore();\n");
                if( info["stype"] == "hands" || info["stype"] == "finger" )
                {
                        buf += sprintf("\tset(\"armor_prop/armor\", 10);\n");
                        buf += sprintf("\tset(\"armor_prop/unarmed_damage\", apply_damage());\n");
                } else  
                if( info["stype"] == "rings" || info["stype"] == "neck" || info["stype"] == "charm" )
                        buf += sprintf("\tset(\"armor_prop/armor\", 10);\n");     
                else    buf += sprintf("\tset(\"armor_prop/armor\", apply_armor());\n");
                buf += prop_segment(info["prop"], "");
                buf += sprintf("\n\tsetup();\n}\n\n");
                // ���ɷ��������ļ����
        }
        buf += sprintf("string long() { return short() + query(\"makeinfo\") + query(\"long\") + item_long(); }\n");

        if (save_item_file(filename, buf) == 1)
                return filename;
        
        return 0;
}

// add mapping
protected string prop_segment(mapping p, string path)
{
        string path2;
        string buf;
        string *ks;
        int i;

        buf = "";
        if (! p) return buf;

        ks = keys(p);
        for (i = 0; i < sizeof(ks); i++)
        {
                // check the paramter's type
                if (mapp(p[ks[i]]))
                {
                        path2 = path + ks[i] + "/";
                        buf += prop_segment(p[ks[i]], path2);
                } else
                {
                        if( intp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", %d);\n",
                                       path + (string)ks[i], p[ks[i]]);
                        else if( stringp(p[ks[i]]) )
                                buf += sprintf("\tset(\"%s\", \"%s\");\n",
                                       path + (string)ks[i], p[ks[i]]);
                }
        }

        return buf;
}

// filename ��д���ĵ������ƣ��Ѿ�������·��
// content ��д���ĵ�������
protected int save_item_file(string filename, string content)
{
        rm(filename);
        if (write_file(filename, content))
        {
                VERSION_D->append_sn(filename);
                return 1;
        } else
        {
                write("д�뵵��(" + filename + ")ʱ������֪ͨ��ʦ����\n");
                return 0;
        }
}

int do_discard(string arg)
{
        string desc, file;
        object money;
        object ob, item;
        object me;
        int n;

        if (! arg)
                return notify_fail("��ȥ�˻�ʲô������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        message_vision("$n�ó�һ"+query("unit", ob)+ob->name()+
                       "��$N˵����������������˵���...��\n",
                       this_object(), me);

        //if (! ob->is_item_make())
        if( !query("material_file", ob) )
        {
                command("heng");
                command("say �ⲻ������������Ķ������ҿɲ��ܸ���");
                return 1;
        }

        if( query("equipped", ob) ) 
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n"); 

        if( ob->item_owner() != query("id", me) )
        {
                command("kick "+query("id", me));
                command("say �����˱��˵Ķ����������������Ϊ����ɵ�ӣ�");
                return 1;
        }

        command("sigh");
        command("say һǧ��������û��ʲô�����ҵĻ�ɫ���õģ����ˣ����ˣ�");
        message_vision("$N�ӹ�$n�ݹ�����" + ob->name() + "������"
                       "�ӽ��˻�¯�����������˰��Ρ�\n",
                       this_object(), me);

        item=new(query("material_file", ob));
        item->move(me, 1);

        message_vision("��һ���" + ob->name() + "���ۻ���һ��" + item->name() + "��\n",
                       this_object(), me);

        command("say ���Ȼ�������ҵĶ�������Ҳ���������Ǯ��"
                "��Щ�������˻ظ���ģ�");
        n=(query("value", ob)*8/10+9999)/10000;
        if (! n)
        {
                money = new("/clone/money/silver");
                money->set_amount(1);
        } else
        {
                money = new("/clone/money/gold");
                money->set_amount(n);
        }
        message_vision("$N�ó�һ"+query("unit", item)+item->name()+"����"
                       "$n��\n", this_object(), me);
        message_vision("$N�ó�һЩ" + money->name() + "����"
                       "$n��\n", this_object(), me);
        log_file("static/item", sprintf("%s %s discard  %s(%s)\n",
                                log_time(), log_id(me),
                                filter_color(ob->name(1)),query("id", ob)));
        delete("can_summon/"+query("id", ob), me);
        file = base_name(ob) + ".c";
        DBASE_D->clear_object(ob);
        if (sscanf(file, "/data/item/%*s"))
                rm(file);
        money->move(me, 1);
        return 1;
}

int do_notch(string arg)
{
        object me, ob, ob1;
        string *runes;
        int i, n;

        if (! arg)
                return notify_fail("��Ҫ��ʲô�������ۣ�\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

        if( query("balance", me)<10000000 )
                return notify_fail("����Ǯׯ��Ĵ���֧�����߿��۷��á�\n");

        message_vision(CYN"$n�ó�һ"+query("unit", ob)+ob->name()+
                       CYN "��$N˵������������" + ob->name() + CYN "��Щ��Ƕ�õİ��ۡ�\n",
                       this_object(), me);

        if (!ob->is_item_make())
        {
                command("heng");
                command("say �����ܸ������ƽ��֮�￪����ף���");
                return 1;
        }

        if( !query("armor_type", ob) &&
            !query("skill_type", ob) )
        {
                command("say ��ֻ��������������͵ĵ��߿��۴�ס�");
                return 1;
        }

        n = query("enchase/flute", ob);
        n++;
        
        if( n > 6 )
                return notify_fail(ob->name() + "�Ѿ��ٿ��۵������ˣ�\n");
                        
        if( !query("armor_type", ob) || (query("armor_type", ob) != "rings" && 
             query("armor_type", ob) != "neck" && query("armor_type", ob) != "charm") )
        {
                if( !ob->is_weapon() && !ob->is_unarmed_weapon() && n > 4 )
                        return notify_fail(ob->name() + "�Ѿ��ٿ��۵������ˣ�\n");
                runes = equip_sockets[to_string(n)];
        }
        else
        {
                if( n > 3 )
                        return notify_fail(ob->name() + "�Ѿ��ٿ��۵������ˣ�\n");
                        
                runes = rings_sockets[to_string(n)];
        }
        
        for( i=0; i< sizeof(runes); i++ )
        {  
                // ��Ҫ����
                if( !objectp(present(runes[i], me)) )
                        return notify_fail("�����û���뿪�۷���"+runes[i]+"�ɣ�\n");
        }

        for( i=0; i< sizeof(runes); i++ )
        {  
                if( objectp(ob1 = present(runes[i], me)) )
                        destruct(ob1);
        }

        message_vision(HIM "$N�ӹ�$n" HIM "���е�" + ob->name() + HIM "������......\n" NOR,
                     this_object(), me);

        addn("enchase/flute", 1, ob);

        switch(query("material", ob) )
        {
        case "tian jing":
                set("enchase/SN", 8, ob);
                break;
        case "no name":
                set("enchase/SN", 16, ob);
                break;
        default         :
                break;
        }

        ob->save();

        addn("balance", -10000000, me);
        me->save();

        message_vision(HIW "ֻ��һ��ѣ��������" + ob->name() + HIW"�����Ȼ����һ��Բ�ε�С�ס�\n\n" NOR, this_object(), me);

        message_vision(HIC "$N��" + ob->name() + HIC "��������$n��\n" NOR, this_object(), me);
        command("say ���ˣ����ˣ���������ˡ�");
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/notch");
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;

        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len ))
        {
                write(sprintf("�Բ��������ֱ����� 1 �� %d �������֡�\n",
                      max_len / 2));
                return 0;
        }

        if (max_len < 9 && ! is_chinese(name))
        {
                write("�Բ��������á����ġ�Ϊ��װȡ���֡�\n");
                return 0;
        }
        return 1;
}

void get_modname(string arg, object me, object ob)
{
        mapping prop;
        string arg_old;
        string type;

        if( arg == "q" || arg == "Q" ) {
                write("��ȡ�����̻���װ����װ��ȡ�ء�\n");
                return;
        }
        if( query_temp("big5", me) )
                arg = LANGUAGE_D->Big52GB(arg);

        arg_old = arg;
        arg = trans_color(arg, 3);
        arg = filter_color(arg, 1);

        if (! check_legal_name(arg, 8))
        {
                write("�������̻�װ�������װ����(��Ҫ����4���֣��ɼ���ɫ)��\n");
                input_to( (: get_modname :), me, ob);
                return;
        }
        
        if( !(type = query("skill_type", ob)) )
                type = query("armor_type", ob);
                
        arg = arg_old;
        arg = trans_color(arg, 3);
        //arg = HIG "��" NOR+arg+NOR+HIG "��" NOR;

        prop = EQUIPMENT_D->apply_ultimate_prop(ob, type, 3);
        set("enchase/mod_prop", prop, ob);
        set("mod_name", arg, ob);
        //mark++;
        //set("mod_mark", "M"+(10000+mark), ob);
        set("mod_mark", base_name(ob), ob);
        set("mod_level", "1", ob);
        ob->save();
        delete_temp("paid/dosuit", me);

        message_sort(HIY "\n�ɽ�С������ؽӹ�" + ob->name() + HIY "����������ظ�Ħ������" + ob->name() +
                     HIY "����΢΢������ɫ��â���������֣�����ңԶҹ���е�һ���ǹ⡣�漴���ɽ���" + ob->name() +
                     HIY "�����Աߵ�Īа��Īа΢΢һЦ��˫������" + ob->name() + HIY "������ĬĬ��������ֵ����� ����" +
                         "һ�����" + ob->name() + HIY "�������â��ʧ��������������������â�����ţ���������" +
                         "һ����ɫ�ĵ�⣬�쳣��ҫ���ƺ�Ҫ��һ�����ɡ���Īа����һ������С������ؽ�" + ob->name() + HIY "������" +
                         "�ɽ����У��ɽ��ٴ��ḧ" + ob->name() + HIY "����ֵ��ǣ�" + ob->name() + HIY "��Χ�Ĺ�â" +
                         "ͻȻ����ʧ���ظ���ƽ����\n\n" NOR, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "��ϲ" + query("name", me) + HIY "��" + ob->name() + HIY "����Ϊ" + 
                                                          suit_level[query("mod_level", ob)] + HIY "Ʒ�ʣ�\n" NOR);
                                                          
        tell_object(me, HIG "�ɽ��� " + ob->name() + HIG + "�������㡣\n" NOR);
        MYGIFT_D->check_mygift(me, "newbie_mygift/dosuit");
        return;
}

int do_suit(string arg)
{
        object me, obj;

        string *type_list = ({
                "head",
                "waist",
                "boots",
                "surcoat",
                "armor",
                "cloth",
                "wrists",
                "neck",
                "rings",
                "charm",
        });

        me = this_player();

        if (! query_temp("paid/dosuit", me)) 
                return notify_fail("�ɽ�˵�����������ʲô��������˼������\n");

        if (! arg) return notify_fail("��ҪΪʲô��Ʒ�̻���װ���� dosuit <��ƷID> \n");

        if (! objectp(obj = present(arg, me)))
                return notify_fail("������û���������ߡ�\n");
        
        if( query("equipped", obj) )
                return notify_fail("���Ƚ��" + obj->name() + "��װ����˵��\n");
                
        if (! obj->is_item_make())
                return notify_fail("������Ʒ����������װ���ԡ�\n");
        
        /*
        if (obj->item_owner() != query("id", me))
                return notify_fail("���������������ɣ�����������ʡ�\n");
        */
        
        // �ж�Ŀ���Ƿ����ڿ�����������װ����
        if (! obj->is_weapon() && !obj->is_unarmed_weapon() )
                if (member_array(query("armor_type", obj), type_list) == -1)
                        return notify_fail("��װ�����಻�ܽ����̻���װ������� help suit ˵����\n");

        if (query("status", obj) < 6)
                return notify_fail(obj->name() + NOR "��Ʒ�ʻ����������޷��̻���װ��\n");

        if (query("balance", me) < 10000000)
                return notify_fail("���������Ǯ�����ɣ�Ϊ" + obj->name() + NOR "�̻���װ��Ҫ" +
                                   HIY "һǧ���ƽ�" NOR "���Ǵչ������ɣ�\n");

        // �ж�Ŀ�겿���Ƿ��Ѿ��̻���װ
        if (query("mod_name", obj))
        {
                if (!query_temp("pending/dosuit", me))
                {
                        set_temp("pending/dosuit", 1, me);
                        return notify_fail(obj->name() + NOR "�Ѿ����̻�����װ��һ�������ˣ���Ҫ�����̻���������һ��dosuit��\n");
                }

                delete("mod_level", obj);
                delete("mod_name", obj);
                delete("enchase/mod_prop", obj);
        }

        delete_temp("pending/dosuit", me);
        addn("balance", -10000000, me);

        write("�������̻���װ�����װ����(��Ҫ����4���֣��ɼ���ɫ)��\n");
        input_to( (: get_modname :), me, obj);
        return 1;
}

int do_upsuit(string arg)
{
        object me, ob, item;
        mixed level;

        me = this_player();
        
        if( !arg ) return notify_fail("��Ҫ�����ĸ���װ����Ʒ�� upsuit <��ƷID> \n");

        if( !objectp(ob = present(arg, me)) )
                return notify_fail("������û���������ߡ�\n");
        
        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");
                
        if( !ob->is_item_make() )
                return notify_fail("������Ʒ����������װƷ����\n");
        
        if( !query("mod_name", ob) )
                return notify_fail("�����̻���װ�󣬲���������װƷ����\n");
        
        if( (level = query("mod_level", ob)) == "4" )
                return notify_fail(ob->name() + NOR "�Ѵﵽ��߼����컯������\n");
        
        /*       
        if( ob->item_owner() != query("id", me) )
                return notify_fail("���������������ɣ�����������ʡ�\n");
        */
        
        if( !objectp(item = present("hongmeng lingqi", me)) )
                return notify_fail("�����û������������ɣ�\n");

        if (query("balance", me) < 100000000)
                return notify_fail("���������Ǯ�����ɣ�Ϊ" + ob->name() + NOR "������װƷ����Ҫ" +
                                   HIY "һ�����ƽ�" NOR "���Ǵչ������ɣ�\n");
        
        level = to_int(level);
        level++;
        level = to_string(level);
        set("mod_level", level, ob);
        ob->save();
        message_sort(HIY "\n�ɽ�С������ؽӹ�" + ob->name() + HIY "����������ظ�Ħ������" + ob->name() + 
	             HIY "����΢΢������ɫ��â���������֣�����ңԶҹ���е�һ���ǹ⡣�漴���ɽ���" + ob->name() + 
	             HIY "�����Աߵ�Īа��Īа΢΢һЦ��˫������" + ob->name() + HIY "������ĬĬ��������ֵ����� ����" + 
	                 "һ�����" + ob->name() + HIY "�������â��ʧ��������������������â�����ţ���������" + 
	                 "һ����ɫ�ĵ�⣬�쳣��ҫ����"+item->name()+HIY"���ɡ���Īа����һ������С������ؽ�" + ob->name() + HIY "������" + 
	                 "�ɽ����У��ɽ��ٴ��ḧ" + ob->name() + HIY "����ֵ��ǣ�" + ob->name() + HIY "��Χ�Ĺ�â" + 
	                 "ͻȻ����ʧ���ظ���ƽ����\n\n" NOR, me);
        
        destruct(item);
        addn("balance", -100000000, me);

        CHANNEL_D->do_channel(this_object(), "chat", HIY "��ϲ" + query("name", me) + HIY "��" + ob->name() + HIY "����Ϊ" + 
                                                          suit_level[query("mod_level", ob)] + HIY "Ʒ�ʣ�\n" NOR);

        if( query("mod_level", ob) == "4" )                                           
                CHANNEL_D->do_channel(get_object(__DIR__"moye"), "chat", HIC "����ǧ��֮�����ٴμ�����˵�е��컯������ʵ���������޺�Ҳ��\n" NOR);                                                    

        tell_object(me, HIG "�ɽ��� " + ob->name() + HIG + "�������㡣��ϲ��" + 
                       ob->name() + HIG "����Ϊ" + suit_level[query("mod_level", ob)] + HIG "Ʒ�ʣ�\n" NOR);
        return 1;
}

int do_reform(string arg)
{
        mapping props;
        object me;
        object ob, ob1, ob2, ob3;
        string item, what, soul, type;
        string *apply;
        int i, status, qlvl, success, value;
        
        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || sscanf(arg, "%s with %s & %s", item, soul, what ) != 3 )
                return notify_fail("����װ��ָ���ʽ��reform <װ��> with <װ��֮��> & <�������쾧>\n");

        if( !objectp(ob = present(item, me)) )
                return notify_fail("������û������װ���������졣\n");
        
        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");
                
        if( !ob->is_item_make() )
                return notify_fail("������Ʒ���ܸ���Ʒ�ʡ�\n");
        
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("���������������ɣ�����������ʡ�\n");
        */
        
        if( query("status", ob) == 6 )
                return notify_fail(ob->name()+"�Ѿ��ﵽ����Ʒ���ˣ�����Ҫ���������ˡ�\n");
                
        // ��Ҫ����֮��
        if( !objectp(ob1 = present(what, me)) || !ob1->is_reform_ob())
                return notify_fail("�����û��������֮�������쾧�ɣ�\n");

        // ��Ҫװ��֮��
        if( !objectp(ob2 = present(soul, me))|| !ob2->is_equip_soul() )
                return notify_fail("�����û���������Ҫ��װ��֮��ɣ�\n");
        
        type = query("type", ob2); // װ��֮�겿λ

        if( ob->is_weapon() )
        {
                if( type != "weapon" )
                        return notify_fail("����"+ob->name()+NOR"��Ҫ����֮�꣡\n");
        }
        else
        {
                if( type != query("armor_type", ob) )
                        return notify_fail("����"+ob->name()+NOR"��Ҫ"+query("armor_type", ob)+"֮�꣡\n");
        }
        
        status = query("status", ob2); // װ��֮��ȼ�
        qlvl = query("status", ob);
        if( !qlvl ) 
        {
                set("status", 1, ob);
                qlvl = 1;
        }
        if( status <= qlvl )
                return notify_fail("���װ��֮��ȼ��������޷����죡\n");
        
        if( query("balance", me) < 100000000 )
                return notify_fail("������д��㣬���������Ҫһ�����ƽ�\n");
                
        if( qlvl == 1 ) success = 80;
        else if( qlvl == 2 ) success = 70;
        else if( qlvl == 3 ) success = 40;
        else if( qlvl == 4 ) success = 20;
        else if( qlvl == 5 ) success = 10;
        
        success += (status - qlvl) * 10;
        
        if( success < 70 )
        {
                if( query("id", ob1) == "tian jing" )
                {
                        if( objectp(ob3 = present("ouyezi symbol", me)) )
                                success = 70;
                }
        }
        if( success < 90 )
        {
                if( query("id", ob1) == "no name" )
                {        
                        if( objectp(ob3 = present("ouyezi symbol", me)) )
                                success = 90;
                }
        }
        
        if( random(100) < success || query("id", me) == "lonely" )
        {
                addn("reform/apply_prop/max_jing", 1000*(qlvl+1), ob);     // ���Ӿ�
                addn("reform/apply_prop/max_qi", 2000*(qlvl+1), ob);       // ������
                addn("status", 1, ob);

                if( type == "rings" || type == "neck" || type == "charm" )
                {
                        addn("reform/apply_prop/research_effect", 1, ob);
                        addn("reform/apply_prop/derive_effect", 1, ob);
                        addn("reform/apply_prop/practice_effect", 1, ob);
                }

                tell_object(me, HIC "�����" + ob->name() + HIC "�����˲��������ı仯��\n" NOR); 
                if( query("status", ob) == 6 )
                {
                        if( type == "rings" || type == "neck" || type == "charm" )
                        {
                                addn("reform/apply_prop/research_effect", 3, ob);
                                addn("reform/apply_prop/derive_effect", 3, ob);
                                addn("reform/apply_prop/practice_effect", 3, ob);
                                tell_object(me, HIC "������Ʒ��ʹ��" + ob->name() + HIC "���о�����ȡ����ϰ��Ч�������3%��\n" NOR); 
                        }
                        else
                        {
                                addn("enchase/flute", 1, ob);
                                tell_object(me, HIC "������Ʒ��ʹ��" + ob->name() + HIC "����һ�����ۡ�\n" NOR); 
                        }
                        if( ob->is_weapon() )
                        {
                                props = copy(query("weapon_prop", ob));
                                map_delete(props, "damage");
                        }
                        else 
                        {
                                props = copy(query("armor_prop", ob));
                                map_delete(props, "unarmed_damage");
                                map_delete(props, "armor");
                        }
                        if( sizeof(props) > 0 )
                        {
                                apply = keys(props);
                                for( i=0;i<sizeof(apply);i++ )
                                {
                                        value = EQUIPMENT_D->query_prop_value(apply[i], 3, 1); // ǿ��ֵ
                                        if( query("quality_level", ob) == 4 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 3;
                                        } else
                                        if( query("quality_level", ob) == 5 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 4;
                                                else if( sizeof(apply) == 2 )
                                                        value = value * 2;
                                        } else
                                        if( query("quality_level", ob) == 6 )
                                        {
                                                if( sizeof(apply) == 1 )
                                                        value = value * 16;
                                                else if( sizeof(apply) == 2 )
                                                        value = value * 8;
                                                else if( sizeof(apply) == 3 )
                                                        value = value * 4;
                                                else
                                                        value = value * 2;
                                        }
                                        addn("reform/apply_prop/"+apply[i], value, ob); 
                                        tell_object(me, HIC "������Ʒ��ʹ��" + ob->name() + HIC "��" + EQUIPMENT_D->chinese(apply[i]) + "�����"+value +"��\n" NOR); 
                                }
                        }
                }
                
                MYGIFT_D->check_mygift(me, "newbie_mygift/reform");      
        }
        else
                tell_object(me, HIW "���ź�������ʧ�ܡ�\n" NOR);
        
        addn("balance", -100000000, me);
        if( objectp(ob3) ) destruct(ob3);       
        destruct(ob1);
        destruct(ob2);
        ob->save();
        return 1;
}

int do_show(string arg)
{
        mapping props;
        string str, what, element;
        string *apply;
        object me, ob;
        int i, n, level;
       
        if( !arg )
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");
                
        message_vision("$n�ó�һ"+query("unit", ob)+ob->name()+
                       "��$N˵�������а���...��\n",
                       this_object(), me);

        if( !ob->is_item_make() )
        {
                command("heng");
                command("say ��...��...�ҿ��������˰ɣ�");
                return 1;
        }
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !mapp(query("insert", ob)) )
                return notify_fail(ob->name() + NOR "����ʯ��û����Ƕ�������ǿ����\n");
        
        level = query("qianghua/level", ob);
        what = qianghua_rune[to_string(level)];
        
        str = CYN"�ɽ�˵����ǿ��"+ob->name()+CYN"��"+(level+1)+"����Ҫ�����У�Ǭ��ʥˮ��";
        str += "����"+what + " 3���Լ����е�����Ԫ��\n";
          
        props = query("enchase/apply_prop", ob);
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                element = apply[i];
                str += EQUIPMENT_D->chinese(element)+"Ԫ��3��"; 
                if( i+1 == n ) str += "��\n";
                else if( (i+1) % 6 == 0 ) str += "��\n"; 
                else str += "��";      
        }
        
        str += "����㱸�������ϲ��ϣ�������qianghua <װ��>����ǿ����\n" NOR;
        tell_object(me, str);

        return 1;
}

int do_increase(string arg)
{
        mapping props;
        string what, item, element;
        object me, ob, crystal;
        object ob_water, ob_zz1, ob_zz2, ob_zz3;
        object ob_rune1, ob_rune2, ob_rune3;
        object *obs;
        int level, value, success;
        string *apply;
        int i, n;
        int wash;
        int rate, rate2;

        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg )
                return notify_fail("ǿ��װ��ָ���ʽ��qianghua <װ��> �� qianghua <װ��> with <ǿ��ˮ��>\n");
        
        if( sscanf(arg, "%s with %s", arg, item ) == 2 )
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("������û������װ������ǿ����\n");
                
                if( !objectp(crystal = present(item, me)) )
                        return notify_fail("������û������������������ǿ����\n");
        } 
        else     
        {
                if( !objectp(ob = present(arg, me)) )
                        return notify_fail("������û������װ������ǿ����\n");
        }
        
        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");
                
        if( !ob->is_item_make() )
                return notify_fail("������Ʒ����ǿ�����ԡ�\n");
        
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("���������������ɣ�����������ʡ�\n");
        */
        
        if( !mapp(props = query("enchase/apply_prop", ob)) || !mapp(query("insert", ob)) )
                return notify_fail(ob->name() + NOR "������Ƕ��ʯ�����ǿ����\n");
                
        if( query("status", ob) < 6 )
               return notify_fail(ob->name() + NOR "û�дﵽ����Ʒ�����޷�ǿ����\n");
            
        // ��ҪǬ��ʥˮ
        if( !objectp(ob_water = present("bless water", me)) )
                return notify_fail("�����û����Ǭ��ʥˮ�ɣ�\n");    
       
        level = query("qianghua/level", ob); 
        // ��Ҫ����
        what = qianghua_rune[to_string(level)];  
        if( !objectp(ob_rune1 = present(what + " 1", me)) || !ob_rune1->is_rune() )
                return notify_fail("�����û����3��"+what+"�ɣ�\n");

        if( !objectp(ob_rune2 = present(what + " 2", me)) || !ob_rune2->is_rune() )
                return notify_fail("�����û����3��"+what+"�ɣ�\n");

        if( !objectp(ob_rune3 = present(what + " 3", me)) || !ob_rune3->is_rune() )
                return notify_fail("�����û����3��"+what+"�ɣ�\n");

        // ��Ҫ�ƽ�һ����
        if( query("balance", me) < 100000000 )
                return notify_fail("������������û�б���1�����ƽ�ɡ�\n");
         
        apply = keys(props);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                if( query("id", me) == "lonely" ) break;
                // ��Ҫǿ������
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");

                if( base_name(ob_zz1) != "/inherit/template/element/element" )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");

                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");

                if( base_name(ob_zz2) != "/inherit/template/element/element" )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");

                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");

                if( base_name(ob_zz3) != "/inherit/template/element/element" )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");
        }
        for( i=0;i<n;i++ )
        {
                if( query("id", me) == "lonely" ) break;
                element = apply[i];
                if( !objectp(ob_zz1 = present(element + " 1", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");
                if( !objectp(ob_zz2 = present(element + " 2", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");
                if( !objectp(ob_zz3 = present(element + " 3", me)) )
                        return notify_fail("�����û����ǿ����Ҫ��3��"+element+"Ԫ�ذɣ�\n");
                
                destruct(ob_zz1);
                destruct(ob_zz2);
                destruct(ob_zz3);
        }        
        
        destruct(ob_water);
        destruct(ob_rune1);
        destruct(ob_rune2);
        destruct(ob_rune3);
        addn("balance", -100000000, me);
               
        command("say ������Ȼ��Ҫ�Ķ����㶼�����ˣ�����Ϳ�ʼǿ��"+ob->name()+NOR+CYN"��\n"NOR);
        
        if( level == 0 ) success = 70;
        else if( level == 1 ) success = 70;
        else if( level == 2 ) success = 70;
        else if( level == 3 ) success = 50;
        else if( level == 4 ) success = 35;
        else if( level == 5 ) success = 20;
        else if( level == 6 ) success = 15;
        else if( level == 7 ) success = 10;
        else if( level == 8 ) success = 5;
        
        if( query("material", ob) == "no name" )
                success += 5;
        
        message_vision(HIW "\n$N��Ǭ��ʥˮ�����ĺ�Ԫ�ط�ĩ�����һ���ںϣ�Ȼ���ںϺ��Ǭ��ʥˮ��������" + ob->name() + HIW "�ϣ�\n��̼�"
                       + ob->name() + HIW "�����һ�������һ�㣬ɢ����ѤĿ�Ĺ�ʣ�\n\n", this_object(), me);
        
        rate = random(100);
/*
        rate2 = random(100);
        rate = (rate + rate2)/2;
*/
        if( rate < success || (level < 6 && objectp(crystal)) || query("id", me) == "lonely" )
        {      
                level++;
                for(  i=0;i<n;i++ )
                {               
                        what = apply[i];
                        value = EQUIPMENT_D->query_prop_value(what, level, 1); // ǿ��ֵ
                        // set("enchase/pink_prop/"+what, value, ob); 
                        set("qianghua/apply_prop/"+what, value, ob); 
                }
                addn("qianghua/level", 1, ob);
                ob->save();
                tell_object(me, HIG "ǿ���ɹ���" + ob->name() + HIG "ǿ�������� " + 
                                sprintf(HIY "%d" HIG, query("qianghua/level", ob)) + " �ǡ�\n" NOR); 
                if( query("qianghua/level", ob) >= 4 ) 
                { 
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",  
                                                      YEL "��˵" + ob->name() +  
                                                      YEL "ǿ���� " HIR + sprintf("%d", query("qianghua/level", ob)) +  
                                                      YEL " �ǡ�\n" NOR); 
                } 
                if( query("qianghua/level", ob) >= 9 )
                {
                        if( !wizardp(me) )
                        CHANNEL_D->channel_broadcast("news",
                                                      YEL "��ϲ" + ob->name() +  
                                                      YEL "ǿ��Ϊ���������\n" NOR); 
                }
                tell_object(me, HIC "�����" + ob->name() + HIC "�����˲��������ı仯��\n" NOR); 
                if( objectp(crystal) )
                        destruct(crystal);
                        
                MYGIFT_D->check_mygift(me, "newbie_mygift/qianghua");     
        }        
        else
        {
                if( query("qianghua/level", ob) > 4 )
                {
                        if( objectp(crystal=present("shengling crystal", me)) )
                        {
                                destruct(crystal);
                                tell_object(me, HIR "���ź���ǿ��ʧ�ܡ�\n" NOR);
                        }
                        else
                        {
                                set("qianghua/level", 4, ob);
                                ob->save();
                                tell_object(me, HIR "���ź���ǿ��ʧ����(ǿ���ȼ���Ϊ4������\n" NOR); 
                        }
                }
                else
                        tell_object(me, HIR "���ź���ǿ��ʧ�ܡ�\n" NOR);
        }
        message_vision("$N" NOR "�ó�" + ob->name() + NOR "����$n" NOR "��\n" NOR, this_object(), me);
        return 1;
}

// װ��ǩ��
int do_signature(string arg)
{
        object me, ob;
        mapping data, enchase, insert, require;
        mapping prop, armor_prop, weapon_prop;
        int value, quality_level;
        string type, ctype, stype, unit;
        string material_attrib, material_name, material_file;
        
        if( query_temp("item") ) return notify_fail("�ɽ���æ���أ��ԵȻᡣ\n");

        if (! arg)
                return notify_fail("��Ҫ��ʲôװ��ǩ����\n");
        
        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");

        if( query("equipped", ob) )
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

        if( ob->is_item_make() )
                return notify_fail(ob->name() + "�����Ѿ�ǩ��������\n");
                
        if( !query("can_sign", ob) )
                return notify_fail(ob->name() + "�޷�ǩ����\n");

        if( query("require/level", ob) < 20 )
                return notify_fail("��ֻ��20�����ϵ�װ��ǩ����\n");

        if( query("balance", me) < 10000000 )
                return notify_fail("����Ǯׯ��Ĵ���֧��װ��ǩ�����á�\n");

        message_vision(CYN"$n�ó�һ"+query("unit", ob)+ob->name()+
                       CYN "��$N˵�������" + ob->name() + CYN "ǩ����\n",
                       this_object(), me);

        if( !(stype = query("armor_type", ob)) &&
            !(stype = query("skill_type", ob)) )
        {
                command("say ��ֻ��������������͵�װ��ǩ����");
                return 1;
        }
        
        set_temp("item/status", "makeing");
        message_vision(HIM "$N�ӹ�$n" HIM "���е�" + ob->name() + HIM "����ϸ�����˰��죬̾���������ɳ�����ϧ����ϧ������\n"
                        "Ҳ�գ���Ȼ����������Ե�����ҾͰ�������ǩ����˵�꣬���ֽ�" + ob->name() + HIM "����¯�У�\n" +
                        ob->name() + HIM "ת�ۼ�ͱ�¯����û��\n" NOR,
                        this_object(), me);
        
        if( query("skill_type", ob) )
        {
                type = "weapon";
                material_name = "��������";
                material_attrib = "iron";
                material_file = "/d/item/obj/jingtie";            
                if( query("skill_type", ob) == "throwing" )
                        ctype = filter_color(query("name", ob), 1)[<4..<1];
                else
                        ctype = filter_color(query("name", ob), 1)[<2..<1];
        }
        else 
        {
                type = "armor";
                material_name = "����˿";
                material_attrib = "silk";
                material_file = "/d/item/obj/tiancs";
                if( query("armor_type", ob) == "charm" )
                        ctype = filter_color(query("name", ob), 1)[<6..<1]; 
                else   
                        ctype = filter_color(query("name", ob), 1)[<4..<1];
        }
        unit = query("unit", ob);
        
        data = ob->query_entire_dbase();
        
        enchase = data["enchase"];
        insert  = data["insert"];
        require = data["require"];
        quality_level = data["quality_level"];
        value = pow(quality_level,3) * 100000;
        if( query("skill_type", ob) )
        {
                weapon_prop = data["weapon_prop"];
                map_delete(weapon_prop, "damage");
                prop = ([ "weapon_prop" : weapon_prop ]);
        }
        else
        {
                armor_prop = data["armor_prop"];
                map_delete(armor_prop, "unarmed_damage");
                map_delete(armor_prop, "armor");
                prop = ([ "armor_prop" : armor_prop ]);        
        }       
        set("item/value", value, ob);
        set("item/type", type, ob);
        set("item/ctype", ctype, ob);
        set("item/stype", stype, ob);
        set("item/unit", unit, ob);
        set("item/material_attrib", material_attrib, ob); 
        set("item/material_name", material_name, ob); 
        set("item/material_file", material_file, ob); 
        set("item/enchase", enchase, ob);
        set("item/insert", insert, ob);
        set("item/require", require, ob);
        set("item/quality_level", quality_level, ob);
        set("item/wscale", 100, ob);
        set("item/prop", prop, ob);
        set("item/owner", me, ob);
        set("item/owner_id", query("id", me), ob);
        set("item/owner_name", query("name", me), ob);
       
        addn("balance", -10000000, me);
        me->save();
        
        set_temp("item/making", ob);
        set_temp("item/player", me);
        set_temp("item/status", "waiting", me);
        ob->move(this_object());
        work_step_6(me, ob);
        return 1;
}

int do_cuilian(string arg)
{
        object me, ob, obj, item;
        string target, what;
        string filename, content_str;
        string *content;
        string type;
        int i, n, a, b;
        
        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || sscanf(arg, "%s with %s", target, what ) != 2 )
                return notify_fail("����װ��ָ���ʽ��cuilian <װ��> with <��Ʒ>\n");

        if( !objectp(item = present(target, me)) )
                return notify_fail("������û������װ������������\n");
        
        if( query("equipped", item) )
                return notify_fail("���Ƚ��" + item->name() + "��װ����˵��\n");
                
        if( !item->is_item_make() )
                return notify_fail("������Ʒ����ͨ������������\n");

        if( item->item_owner() != query("id", me) )
                return notify_fail("���������������ɣ�����������ʡ�\n");
        
        if( !objectp(ob = present(what, me)) )
                return notify_fail("������û������������������װ����\n");
                
        if( !query("item_origin", ob) || !(type=query("can_make", ob)) )
                return notify_fail(ob->name()+"���Ǵ���װ���Ĳ��ϡ�\n");
        
        if( type != "all" && type != query("skill_type", item) && type != query("armor_type", item) )
                return notify_fail(ob->name()+"�޷���������������װ����\n");
                
        if( query("balance", me) < 10000000 )
                return notify_fail("���������Ǯ�����ɣ�Ϊ" + item->name() + NOR "������Ҫ" +
                                   HIY "һǧ���ƽ�" NOR "���Ǵչ������ɣ�\n");

        addn("balance", -10000000, me);

        message_vision(HIM "$N�ӹ�$n" HIM "���е�" + item->name() + HIM "����ϸ�����˰��죬̾���������ɳ�����ϧ����ϧ������\n"
                     "Ҳ�գ���Ȼ���ҵ��õĲ��ϣ����ҾͰ������һ����˵�꣬���ֽ�" + item->name()+HIM"��"+ob->name() + HIM "����¯\n" +
                     "�ڣ���ʱ�䣬��" + item->name()+HIM"��"+ob->name() + HIM "�ѱ���¯�е���" HIR "����" HIM "��û��\n"
                     "$N������¯������̾�������֮����Ϊ��Ѫ��������֮�����������......\n" NOR,
                     this_object(), me);
        
        filename = base_name(item) + ".c";    
        destruct(item);          
        content_str = read_file(filename); 
        rm(filename); 
        content = explode(content_str, "\n"); 
        n = sizeof(content); 
        for (i = 0; i < n; i++) 
        {
                /*
                if( (a = strsrch(content[i], "����")) > 0 && (b = strsrch(content[i], "���ƶ��ɵ�һ")) > 0 ) 
                        content[i] = content[i][0..a]) + "����" + query("material_name", ob) + content[i][b..]);
                */
                if( (a = strsrch(content[i], "������")) > 0 && (b = strsrch(content[i], "���ƶ��ɵ�һ")) > 0 ) 
                        content[i] = sprintf("\tset(\"long\", \"������%s%s", query("material_name", ob), content[i][b..]);
                else        
                if( strsrch(content[i], "material_file") != -1 ) 
                        content[i] = sprintf("\tset(\"material_file\",\"%s\");", base_name(ob));
                else        
                if( strsrch(content[i], "material") != -1 ) 
                        content[i] = sprintf("\tset(\"material\",\"%s\");", query("material_attrib", ob)); 
                
                write_file(filename, content[i] + "\n"); 
        }
        
        catch(call_other(filename, "???")); 
        obj = find_object(filename); 
        if( !obj ) 
        {
                write(HIR "װ�������������⣬��㱨����ʦ��\n" NOR); 
        }
        else 
        {
                destruct(ob);
                obj->move(me, 1); 
                message_vision("$N" NOR "�ó��Ѿ������õ�" + obj->name() + NOR "��$n" NOR "��\n" NOR, this_object(), me);
        }
        
        return 1;
}
