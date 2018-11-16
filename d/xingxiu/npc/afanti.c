// npc: /d/xingxiu/npc/afanti.c
// Jay 3/26/96

inherit NPC;

//string ask_me();

void create()
{
        set_name("������", ({ "afanti" }) );
        set("gender", "����" );
        set("age", 48);
        set("long", 
            "��ͷ�ϰ���ͷ�����������̵İ��ֺ�����ϲ��׽Ū�������������ˡ�����"
            "�����˳����\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);

        set_skill("unarmed", 30);
        set_skill("dodge", 25);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set("combat_exp", 2500);

        set("attitude", "peaceful");
        set("inquiry", ([
            "name" : "�Ҿ������ն��İ����ᡣ",
            "here" : "��������Ǹ��õط���",
            "���ն�" : "���ҳ����ĵط���",
            "����" : "������ҵ�Сë¿���Ҿ͸�������",
            "����" : "�����ҹ�������г��кȣ��ҾͲ����ˡ������Ǹ�������Ը����ͷ�����",
            "ë¿" : "�ҵ�Сë¿���ҵ�ɳĮ��ƭ�����ֽ���ʱ�߶��ˡ�",
            "¿" : "�ҵ�Сë¿���ҵ�ɳĮ��ƭ�����ֽ���ʱ�߶��ˡ�",
            "Сë¿" : "�ҵ�Сë¿���ҵ�ɳĮ��ƭ�����ֽ���ʱ�߶��ˡ�",
            "������" : "������ָ�յ׸���˳��ߵ�������������ۡ�",
            "����" : "������������������������",
            "����" : "�����������������Ψ���������º�Ĭ����������ʹ�ߡ�",
       ]) );

        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
             "������̾�˿������ˣ���ϧ�ҵ�¿��\n",
        }) );
        carry_object(__DIR__"obj/wcloth")->wear();
        carry_object(__DIR__"obj/dongbula");
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{
//     if((string)ob->query("name")=="Сë¿") {
     if( query("id", ob) == "maolv"){
           remove_call_out("destroying");
           call_out("destroying", 1, this_object(), ob);

           if( query_temp("marks/��", who)){
                 write("������Ц��Ц��˵�����Ȱ��ϸ��ղ³�����˵��\n");
//               destruct(ob);
                 return 1;
           }
           else {
                 write("������Ц���춼�ϲ����ˣ�˵����л��λ" + 
                       RANK_D->query_respect(who) +
                       "�İ��������ǲ¸�����ɣ�\n");
                 switch(random(20)) {
                   case 0:
                       write("��Ů���(��һ����̶�����)\n");
                       set_temp("marks/��", 1, who);
                       break;
                   case 1:
                       write("ѩ���գ�ѩ���ա�(��һ����̶�����)\n");
                       set_temp("marks/��", 2, who);
                       break;
                   case 2:
                       write("��Сƽ֮��(��һ����̶NPC��)\n");
                       set_temp("marks/��", 3, who);
                       break;
                   case 3:
                       write("���þ��䡣(��һ����̶�����)\n");
                       set_temp("marks/��", 4, who);
                       break;
                   case 4:
                       write("��ȳ��ϵ�NPC��(��һ����̶�����)\n");
                       set_temp("marks/��", 5, who);
                       break;
                   case 5:
                       write("����ϰ�(��һ����̶��������������)\n");
                       set_temp("marks/��", 6, who);
                       break;
                   case 6:
                       write("�������š�(��һ��)\n");
                    // this riddle made by �Ϲ��������������մ��ѧ��
                       set_temp("marks/��", 7, who);
                       break;
                   case 7:
                       write("���������Ʋ��֡�(��һ��)\n");
                    // this riddle modified from one made by �������������ִ���ݣ�
                       set_temp("marks/��", 8, who);
                       break;
                   case 8:
                       write("�����Ŷɶ���ȥ��(��һ����̶��ʦ����)\n");
                    // this riddle made by ����������������ִ���ݣ�
                       set_temp("marks/��", 9, who);
                       break;
                   case 9:
                       write("������ս�ܡ�(��һ����̶NPC��)\n");
                    // this riddle modified from one made by ţ����������
                       set_temp("marks/��", 10, who);
                       break;
                   case 10:
                       write("���굱����(��һ����̶NPC��)\n");
                    // this riddle made by ���¡���������
                       set_temp("marks/��", 11, who);
                       break;
                   case 11:
                       write("ŷ����������(��һ����)\n");
                    // this riddle made by ħ����������
                       set_temp("marks/��", 12, who);
                       break;
                   case 12:
                       write("�������ߡ�(��һ����̶NPC��)\n");
                    // this riddle made by ��ʿ����������
                       set_temp("marks/��", 13, who);
                       break;
                   case 13:
                       write("��˽ܿ�ѷ��(�������̶NPC��)----�ش�ʱ����һ��ش��м䲻���κα�㡣\n");
                       set_temp("marks/��", 14, who);
                       break;
                   case 14:
                       write("�١��(�������̶NPC��)----�ش�ʱ����һ��ش��м䲻���κα�㡣\n");
                    // this riddle made by �Ϲ�����������
                       set_temp("marks/��", 15, who);
                       break;
                   case 15:
                       write("ʥּ��(��һ����̶�����)\n");
                       set_temp("marks/��", 16, who);
                       break;
                   case 16:
                       write("Ե��һϦ��δ�ɡ�(��һ����̶������)\n");
                    // this riddle made by �Ϲ����������� hanxx002@maroon.tc.umn.edu
                       set_temp("marks/��", 17, who);
                       break;
                   case 17:
                       write("���֡�(��һ����̶NPC��)\n");
                    // this riddle made by ��ħ���������� ning@phish.ecii.org
                       set_temp("marks/��", 18, who);
                       break;
                   case 18:
                       write("һ���Ĳ�ֹһ�����㡣(��һ����̶������һ������)\n");
                       set_temp("marks/��", 19, who);
                       break;
                   case 19:
                       write("�ؿۡ�(��һ����̶NPC��)\n");
                       set_temp("marks/��", 20, who);
                       break;

                  }
                  write("����˻ش� (answer) �ҡ���ס������й¶������յס�\n");
                  message("vision", "���������"+who->name()+"�ֹ��˼��仰��\n",
                          environment(who), ({who}) );
                  remove_call_out("destroying");
                  call_out("destroying", 1, this_object(), ob);
                  return 1;
            }
      }
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
int do_answer(string arg)
{
        object me,gold;
        int soln,riddle;
        me = this_player();
        riddle=query_temp("marks/��", this_player());

        if (!riddle) {
           write("���ֲ�����ʦ�������ò��Żش��ҡ�\n");
           return 1;
        }

        if( !arg || arg=="" ) {
           write("����յ��ٻش�\n");
           return 1;
        }
        message("vision", me->name() + "����յ�������Ķ������ֹ�����\n",
                 environment(me), ({me}) );

        switch (arg) {
          case "�": soln=1; break;
          case "����" : soln=2; break;
          case "����ʤ" : soln=3; break;
          case "õ" : soln=4; break;
          case "����" : soln=5; break;
          case "��ѧ�ķ�" : soln=6; break;
          case "��" : soln=7; break;
          case "��" : soln=8; break;
          case "������" : soln=9; break;
          case "ŷ����" : soln=10; break;
          case "������" : soln=11; break;
          case "������ʩ" : soln=12; break;
          case "³�н�" : soln=13; break;
          case "���޳����޳�":
          case "���޳����޳�": soln=14; break;
          case "ŷ����ŷ����": soln=15; break;
          case "����": soln=16; break;
          case "����": soln=17; break;
          case "��Ī��" : soln=18; break;
          case "��ң����ң��" : soln=19; break;
          case "������" : soln=20; break;
          default :
              say("�������Ц������˵������˵ʲôѽ��ţͷ�������졣\n"
                  + me->name() + "����������ͨ�졣\n");
              return 1;
        }
        if( query("combat_exp", me)>10 )
        {
              say("�������Ц������˵�����㻹��ƭ����ѽ��\n" + me->name() + "����������ͨ�졣\n");
              return 1;
        }
        if (riddle==soln) {
//          gold = new("clone/money/gold");
//          gold->move(this_player());
//          say("���������" + me->name() + "һ���ƽ�\n");
          set_temp("marks/��", 0, this_player());
          say ("�������" + me->name() + "�����ķָ����Ȼ��������ˡ��ƽ��ǰ����Ĳ���֮�ƣ�����ȥ�ָ����˰ɡ�\n");
          set("combat_exp",query("combat_exp",  this_player())+80, this_player());
          write ("��ľ��������ˣ�\n");

        }
        else
          write ("˭���յ׸������? ����!!\n");
        return 1;
} 
 

   