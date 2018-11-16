// This program is a part of NT MudLIB
// yinggu.c

#include <ansi.h>
inherit NPC;

string ask_me();
int do_answer(string);

void create()
{
        set_name("����", ({ "ying gu", "ying", "gu" }) );
        set("gender", "Ů��" );
        set("nickname", CYN "������" NOR ) ;
        set("age", 48);
        set("long",
                "��ͷ�����ף����������������ŵ���������һ������Ƭ��"
                "��Ȼ����Ǳ��˼������Ȼ�������˽�����ȴ��̧ͷ��\n");

        set("str", 25);
        set("dex", 35);
        set("con", 27);
        set("int", 25);
        set("shen_type", 1);
        set("max_neili",800);
        set("neili",800);
        set("jiali",30);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("sword",100);
        set_skill("force", 100);
        set("combat_exp", 100000);

        set("attitude", "peaceful");
        set("inquiry", ([
                "�λ�ү"  : "��������ʲô���ߣ�����ҽ���ᣬ���������İɡ�",
                "�ܲ�ͨ"  : "�����������������",
                "������"  : "����Ϻ��У����ƴȱ���\n",
                "����"    :  (: ask_me :),
        ]) );

        set("book_count", 1);

        setup();

        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/xiuhua.c")->wield();
        carry_object("/clone/weapon/qijue.c")->wield();
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

string ask_me()
{
        object who=this_player();
        if( query_temp("marks/��", who)){
                        write("���������˵����һ���㻹û������أ���ʲô��\n");
                        return "һ��һ��������\n";
        }
        else {
                write("����̧ͷ������һ�ۣ���λ"+RANK_D->query_respect(who)+"��������\n");
                switch(random(2))
                {
                case 0:
                        write("������ǧ���ٶ�ʮ���ƽ����Ϊ���\n");
                        set_temp("marks/��", 1, who);
                        break;
                case 1:
                        write("���������ݺ�б���������������\n");
                        write("�Ķ�����һ����������һ�ǣ���Ǻ���? \n");
                        set_temp("marks/��", 2, who);
                        break;
                case 2:
                        write("�����ˣ���ȡ��룬���տ���? \n");
                        set_temp("marks/��", 3, who);
                        break;
                }
                message_vision("��������ض�$N˵�����? \n", who);
                return "�������ͻش�(answer)�ҡ�\n";
        }
}

int do_answer(string arg)
{
        int soln,riddle;
        object ob;
        object me = this_player();
        riddle=query_temp("marks/��", this_player());

        if (!riddle) {
                write("���ֲ�����ʦ�������ò��Żش��ҡ�\n");
                return 1;
        }

        if( !arg || arg=="" ) {
                write("����յ��ٻش�\n");
                return 1;
        }
        message("vision", me->name() + "�����ش�\n", environment(me), ({me}));

        switch (arg)
        {
        case "������ʮ��": soln=1; break;
        case "��ʮ" : soln=2; break;
        case "���ز���" : soln=3; break;
        default :
                say("������Ц����������Ū������Ȼ��Ͱ�"+ me->name() +"���˳�ȥ��\n");
                me->move("/d/heizhao/maze1");
        return 1;
        }

        if (riddle==soln) {
                say ("����̧ͷ�����Ƴ��"+me->name()+"һ�ۣ��������ڶ����������Դ��\n");
                set_temp("marks/��", 0, this_player());
                ob = new("/d/heizhao/npc/obj/whiteobj");
                ob->move(me);
                ob = new("/d/heizhao/npc/obj/yellowobj");
                ob->move(me);
                ob = new("/d/heizhao/npc/obj/redobj");
                ob->move(me);
                say ("����������ðɣ��������Ҷ����㣬��Ե���ȥ�����ɡ�\n");
                say ("���õ�ͷ��ʼ�о�����������"+me->name()+"��\n");
                return 1;
        }
        else {
                command("slapsb "+getuid(me));
                say("����ŭ�������㵽�׶�����������������"+ me->name() +"���˳�ȥ��\n");
                me->move("/d/heizhao/maze1");
        return 1;
        }
}
