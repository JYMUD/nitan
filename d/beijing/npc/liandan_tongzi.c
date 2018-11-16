// liandan_tongzi.c

#include <ansi.h>

inherit NPC;

mixed ask_caiyao();

void create()
{
        set_name("Сͯ", ({"xiao tong", "xiao", "tong"}));
        set("gender", "����");
        set("age", 12);
        set("long",
                "�����������е��ƹ�ҩ�ĵ�ͯ�ӡ�����Ͳ��󣬵�������\n"
                "�Ե������ϳɡ�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 21);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);;

        set("combat_exp", 300000);

        set("inquiry", ([
                "ҩ��" : (: ask_caiyao :),
                "ҩ"   : (: ask_caiyao :),
                "��ҩ" : (: ask_caiyao :),
                "��ҩ" : (: ask_caiyao :),
                "yaocai" : (: ask_caiyao :),
        ]) );
        set("caiyao", 12);

        setup();
}

mixed ask_caiyao()
{
        object me = this_player();

        switch(query_temp("caiyao", me) )
        {
        case 1:
                return "����ȥ��ҩ������������";

        case 2:
                return "ҩ�����ˣ���������ң�";
        }

        switch(query_temp("liandan", me) )
        {
        case 1:
                // �Ѿ�����������������Ϣ��
                break;

        case 2:
                return "ҩ���Ѿ�׼���ã�����ȥ�ˡ�";

        case 3:
                return "�㲻����������ҩ����ô�����ˡ�";

        case 4:
                return "������ȥ�����ɡ�";

        default:
                return "���ֲ���ҩ��Ҫҩ�ĸ�ʲô��";
        }

        message_vision(CYN "Сͯ��$N" CYN "˵�����ðɣ�����"
                       "ȥ�������������ڼ������ʵĲ�ҩ����\n" NOR, me);
        set_temp("caiyao", 1, me);
        addn("caiyao", -1);
        return 1;
}

int accept_object(object me, object ob)
{
        int exp, pot;

        if (userp(ob) || ob->is_character() || ob->is_item_make())
                return 0;

        if( query_temp("caiyao", me)<1 )
        {
                command("say ��ʲôʱ�������������ҵģ�");
        } else
        if( query_temp("caiyao", me) == 1 )
        {
                command("say ��˭�����ҵĶ����������ң�����Ϊ��С�ͺ�ƭ��");
        } else
        if( strsrch(query("name", ob),"��֪����ҩ")<0 )
        {
                command("say ������С���������ֶ���ƭ�ҡ�\n");
        } else
        {
                command("say �ðɣ�����������ӹ���");
                command("say �ӹ����ˣ�������ֱ��ȥ����������liandan�������ˡ�");
                delete_temp("caiyao", me);
                set_temp("liandan", 2, me);

                if( query("combat_exp", me)<1000000 )
                {
                        exp = 100 + random(140);
                        pot = exp / 3;
                }
                else
                {
                        exp = 20 + random(100);
                        pot = exp / 3;
                }

                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
                destruct(ob);
                return 1;
        }
        return 0;
}

