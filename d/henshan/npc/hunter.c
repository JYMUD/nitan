#include <ansi.h>
inherit NPC;

mixed teach_hunting();
string ask_chushengdao();

void create()
{
        set_name("����", ({"hunter"}));
        set("gender", "����" );
        set("class", "swordman");
        set("age", 45);
        set("str", 200);
        set("con", 26);
        set("int", 28);
        set("dex", 200);
        set("combat_exp", 12000000);
        set("attitude", "peaceful");

        set_skill("unarmed", 300);
        set_skill("dodge", 300);
        set_skill("hunting", 2000);

        set("max_qi", 4500);
        set("max_jing", 2000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 150);

        set("inquiry", ([
                "hunting" : ( :teach_hunting: ),
                "����"    : ( :teach_hunting: ),
                "������"  : (: ask_chushengdao :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();

 }

int accept_object(object me, object ob)
{
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("��û�����������");
        if( query("id", ob) == "bushou jia" )
        {
                command("nod");
                command("say ��������õ��ţ���������Ϊ���������Ը�⣬��\n����"
                        "����һЩ���Եļ��ɡ�");
                 set_temp("marks/hunter", 1, me);
                return 1;
        }
        else
        {
                 command("shake");
                 command("say ����ʲô�������Ҳ���Ҫ��");
        }

           return 1;
}



mixed teach_hunting()
{
        object me = this_player();
        int jing, add;

        jing=query("jing", me);
        add = me->query_int() + random(me->query_int() / 2 );

        if( !query_temp("marks/hunter", me) )
                return "���������������γ����ԣ�\n";

        if (me->is_busy() || me->is_fighting())
        {
                write("��������æ�š�\n");
                return 1;
        }

        if (jing < 20)
        {
                write("��ľ����޷����С�\n");
                return 1;
        }

        if( (query("potential", me)-query("learned_points", me))<1 )
        {
                write("���Ǳ�ܲ������޷�����ѧϰ��\n");
                return 1;
        }
        write(HIW "���˸��㽲�����йز��Ե�һЩ���ɡ�\n" NOR);
        write(HIY "���������˵�ָ�����ƺ������ĵá�\n" NOR);

        addn("learned_points", 1, me);

        me->improve_skill("hunting", add);

        addn("jing", -(5+random(6)), me);

        return 1;

}

string ask_chushengdao()
{
        object me;
        
        me = this_player();
        
        if( query("int", me)<32 || 
            query("con", me)<32 || 
            query("str", me)<32 || 
            query("dex", me)<32 )
            return "����������Ի��������������������ҿ��㻹���Ȼ�ȥ�ɡ�\n";


        if( query("reborn/times", me)<3 )
                return "�߿����߿���û������æ��\n";
        
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me)<4 )
                return "�����书�Ѿ��������£��α����̰��?\n";
                        
        if (me->query_skill("lunhui-sword",1))
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                                        
        // �Ѿ��������
        if( query("lunhui-sword_quest/chushengdao/finish", me) )
                return "�Ǻǣ������书�Ƿ������亱�У�����������������\n";

        // ��������
        // ɱ�ƽ����
        if( !query("lunhui-sword_quest/chushengdao/give_quest", me) )
        {
                command("look"+query("id", me));
                command("say ���¿������Ƿ���֮������Ȼ���������ң�������Ȱ���һ��æ��");
                command("tan");
                command("say ǰ����Զ����һƬ���֣����������ڴ����ԣ�һֱ��ƽ�˾���Ҳ����ø�������ʳ�����ڿ�");
                command("say ǰ���ã����������һֻ���ޣ������������������ȫ�������ˣ���������Ҳ�����䶾�֡�");
                command("say ��˵������һֻ���ǧ��Ļƽ���񻢣����ͷǳ����������ָ���ǰȥ����һ���� ����");
                command("look"+query("id", me));
                command("say ��������б�����ʰ�������������洫��ѧ����������ܡ�");
                tell_object(me, this_object()->name() + HIG "�������������ƽ���񻢣�\n" NOR);
                set("lunhui-sword_quest/chushengdao/give_quest", 1, me);
                me->save();
                return "��ô������ȥ��";
        }
        
        // �������
        if( !query("lunhui-sword_quest/chushengdao/killed", me) )
                return "��ô����������ƽ��������\n";

        command("hehe");
        command("nod"+query("id", me));
        command("say �ã��ã��ã������书�Ƿ��������������ʹ��㡸������������");

        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);

        tell_object(me, HIG "��ϲ�������ˡ���������������Ŀǰ�ȼ�Ϊ10����\n");
        me->set_skill("chusheng-dao", 10);
        set("lunhui-sword_quest/chushengdao/finish", 1, me);
        
        return "���أ�";
        
                
}
