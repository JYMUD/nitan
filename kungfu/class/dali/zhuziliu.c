// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit NPC;

void create()
{
        set_name("������", ({ "zhu ziliu", "ziliu", "zhu" }) );
        set("gender", "����" );
        set("age", 48);
        set("long",
                "����һ��������������������һ�����飬������ҡͷ���Եġ� \n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);
        set_skill("unarmed", 70);
        set_skill("dodge", 65);
        set_skill("hammer",70);
        set("combat_exp", 550000);


        set("attitude", "peaceful");
        set("inquiry", ([
                "�λ�ү" : "���Ծ����ˡ�",
                "��·" :  "·���ǲ��õģ���Ҫ�������Ҿʹ���һָ��",
                ]) );

        setup();

        set("chat_chance", 20);
        set("chat_msg", ({
                "�������ʵ������Է������������ô������ʲô��������Ǵ�������\n",
        }) );
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{
        object me=this_object();

        if( query("name", ob) == "������"
                 && query("material", ob) == "steel"){

                remove_call_out("destroying");
                call_out("destroying", 1, ob);

                if( query("visited", me)>3){
                        write("������ҡͷ�����Բ�ס����ʦ�������ʦ���ȥ��ɽ�ˣ����¸��������ɡ�\n");
                        return 1;
                }
                addn("visited", 1, me);

                if( query_temp("marks/����", who)){
                        write("������Ц���е�˵���𲻳����ͺú�ȥ�������\n");
                        return 1;
                }
                else {
                        write("������̧ͷ������һ�ۣ�"+"��λ"+RANK_D->query_respect(who) + "Ҳ��ʫ�ʣ�\n");
                        write("������ҡͷ���Ե�������\n");
                        switch(random(7)) {
                        case 0:
                                write("�鵶��ˮˮ�������ٱ��������\n");
                                write("�������������⣬����ɢ��Ū������\n");
                                set_temp("marks/����", 1, who);
                                break;
                        case 1:
                                write("֣���ۻ��泤ҹ���ܰԵ����Ѱ�ͷ��\n");
                                write("���º�����ɽˮ���˼䲻���ء����� \n");
                                set_temp("marks/����", 2, who);
                                break;
                        case 2:
                                write("��ɪ�޶���ʮ�ң�һ��һ��˼���ꡣ\n");
                                write("ׯ�������Ժ��������۴����жž顣\n");
                                write("�׺�����Ӧ���ᣬ������ů�����̡�\n");
                                write("����ɴ���׷�䣬����������������\n");
                                set_temp("marks/����", 3, who);
                                break;
                        case 3:
                                write("�׹�¶�Ұ��ǧ���޼����� \n");
                                write("�������һ����֮�ϡ�����  \n");
                                set_temp("marks/����", 4, who);
                                break;
                        case 4:
                                write("��ϴ�գ���������¥������ǧ���Բ��ǣ�\n");
                                write("б������ˮ���������ϰ�ƻ�ޣ� \n");
                                set_temp("marks/����", 5, who);
                                break;
                        case 5:
                                write("ǽ����ǧǽ�����ǽ�����ˣ�ǽ�����Ц�� \n");
                                write("Ц�����������ģ��������������� \n");
                                set_temp("marks/����", 6, who);
                                break;
                        case 6:
                                write("�޴�ȥ���������ڣ�Ū��ɫ�� \n");
                                write("�������ء�����  \n");
                                set_temp("marks/����", 7, who);
                                break;
                        case 7:
                                write("ǰ�������ˣ��󲻼����ߣ� \n");
                                write("������������������������ \n");
                                set_temp("marks/����", 8, who);
                                break;
                        }
                        message_vision("������Ц���е��ʵ����Ҳ��ǵ��ˣ����ܸ�����ô��\n", who);
                        return 1;
                }
        }
        return 0;
}

void destroying(object obj)
{
        destruct(obj);
        return;
}

int do_answer(string arg)
{
        int soln,riddle;
    object me = this_player();
    riddle=query_temp("marks/����", this_player());

    if (!riddle) {
                write("���ֲ�����ʦ�������ò��Żش��ҡ�\n");
                return 1;
        }
    if( !arg || arg=="" ) {
                write("����յ��ٻش�\n");
                return 1;
        }

    message("vision", me->name() + "�����ش�\n", environment(me), ({me}) );
        switch (arg) {
        case "����": soln=1; break;
        case "����" : soln=2; break;
        case "ֻ�ǵ�ʱ����Ȼ" : soln=3; break;
        case "�˳�" : soln=4; break;
        case "����" : soln=5; break;
        case "����ȴ��������" : soln=6; break;
        case "�滨ѩ": soln=7; break;
        case "�����֮���ƶ���Ȼ������" : soln=8; break;
        default :
                say("��������Ц������ɨ��ä��ô��\n"+me->name()+"��æ����ɽȥ��\n");
                me->move("/d/heizhao/shanlu9");
                return 1;
        }

        if (riddle==soln) {
                delete_temp("marks/����", this_player());
                say ("������һ�ϵ��أ���" + me->name() + "˵������������������������\n");
                write ("�������ƿ����ߣ���������һԾ��������ɽ��ȥ�� \n");
                me->move("/d/heizhao/yideng8");
        }
        else write (" ���ԣ���\n");
        return 1;
}
