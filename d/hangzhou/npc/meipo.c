// mei_po.c
#include <ansi.h>

inherit NPC;

string marry();
string unmarry();

void create()
{
        set_name("ý��", ({ "mei po","mei" }) );
        set("title", "����ׯ");
        set("gender", "Ů��" );
        set("age", 43);
        set("long",
                "һλ�����ܸɵ���ý��\n");
        set("max_qi",800);
        set("max_jing",800);
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("inquiry", ([
                "��Լ" : "�ǰ���������Ϳ��Ե޽�ͽ����Լ",
        ]) );
        set_skill("literate", 70);
        set_skill("dodge", 200);
        set_skill("unarmed", 100);
        setup();
        add_money("gold", 10);
        carry_object("/clone/misc/cloth")->wear();
}

/*
void init()
{
        object ob;

        ::init();
        add_action("do_marry", "marry");
        add_action("do_unmarry", "unmarry");
}
*/

int do_marry(string arg) {
        object marry_card1,marry_card2, obj, me;
        object *list,ob;
        int i, have_marry;
        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        if( query("gender", me) == "����"){
              say("��Ȼ���Ѿ��Թ��ˣ��Ͳ��ܽ���ˣ���ذɣ�\n");
              return 1;
            }
        if( query("class", me) == "bonze" )
             return notify_fail("���ǳ�����,��ô�ܽ�飡�ˣ����ڵĺ��С���\n");
        if( query("age", me)<17 )
             return notify_fail("�����仹С,�ȵ�ʮ����������.\n");
        while (i--) {
              if( (query("id", list[i])) == "marrycard" )
                return notify_fail(
                "���Ѿ��ͱ����л�Լ�˰�?���ﲻ�����ػ�ġ�\n");
        }

        if(!arg || !objectp(obj = present(arg, environment(me)))
                || !find_player(arg)|| !find_living(arg))
        return notify_fail("�����˭�޽���Ե��\n");
        if( !environment()
        ||      base_name(environment()) != query("startroom") )
             return notify_fail(
                "���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");

        if( !living(obj) )
                return notify_fail(obj->name() +
                "�Ѿ��޷�����޽���Ե�ˡ�\n");

        if( query("gender", obj) == query("gender", me) )
                return notify_fail("�ѵ��㲻��" + RED"AIDS"NOR + "��\n");

        if(obj==me)     return notify_fail("�㲻�ܺ��Լ��޽��Լ��\n");

        if( userp(obj) && !(query("marks/"+me->name(1, obj)))){
                message_vision(MAG "\n$N����$n˵����"
                    + RANK_D->query_self(me)
                    + me->name() + "��Ը���"
               + RANK_D->query_respect(obj) +
                "��Ϊ��\n\n"NOR, me,obj);
                 set("marks/"+obj->name(1), 1, me);
           tell_object(obj, MAG "�����Ը��ͶԷ���Ϊ�򸾣�����Ҳ��"
                        +me->name()+"("+query("id", me)+
                        ")"+ "��һ�� marry ָ�\n" NOR);
                write(MAG
                        "�����㼱�����������������˵ͬ�⡭��\n" NOR);
                return 1;
        }


        marry_card1 = new("/obj/marry_card");
        set("name", "���"+query("id", obj)+"�Ļ�Լ", marry_card1);
        marry_card1->move(me);
        marry_card2 = new("/obj/marry_card");
        set("name", "���"+query("id", me)+"�Ļ�Լ", marry_card2);
        marry_card2->move(obj);

     message_vision(MAG "��ϲ $N �� $n ��һ���������ϲ����Ե��\n" NOR,obj,me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s ���ڿ�ʼ�Ƿ���! \n",
        me->name(1), obj->name(1)));
        return 1;
}

int do_unmarry(string arg)
{
        object marry_card1,marry_card2,  me;
        object *list,ob, couple_ob;
        int i, have_marry;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;

        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
         if( (query("id", list[i])) == "marrycard"){
                        marry_card1 = list[i];
                        cardname=query("name", list[i]);
                        have_marry = 1;
                }
        }

        if (have_marry == 0)
                return notify_fail("�㻹δ�л�Լ����\n");
        if( !environment()
        ||      base_name(environment()) != query("startroom") )
           return notify_fail("���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");
        if (sscanf(cardname,"���%s�Ļ�Լ" ,target)!=1)
                return notify_fail("��û�а���.\n");
         if(!objectp(couple_ob = present(target, environment(me)))
                || !find_player(target) )
                return notify_fail("��İ������ڲ��ڳ�.\n");

        if( query("gender", couple_ob) != "Ů��"){
                tmpstr1 = "����"; tmpstr2 = "�Ϲ�";
                str1 = "��"; str2 = "��";
        } else {
                tmpstr1 = "�Ϲ�"; tmpstr2 = "����";
                str1 = "��"; str2 = "��";
        }

        list = all_inventory(couple_ob);
        i = sizeof(list);
        have_marry = 0;
        while (i--) {
              if( (query("id", list[i])) == "marrycard"){
                        marry_card2 = list[i];
                        have_marry = 1;
                }
        }
        if (have_marry = 0) {
                destruct(marry_card1);
        message_vision(MAG " $N �� $n �����ڿ�ʼ�����Լ,�������!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s �����ڿ�ʼ�����Լ,�������! \n",
        me->name(1), couple_ob->name(1)));

                return 1;
        }

        if( userp(couple_ob) && !(couple_ob->query("marks/"
                + "unmarry" +me->name(1))) ) {
                message_vision(MAG "\n$N����$n˵����"
                        + RANK_D->query_self(me)
                        + me->name() + "�����ǽ����Լ��!����?\n\n"
                        NOR, me, couple_ob);
                 set("marks/"+"unmarry"+couple_ob->name(1), 1, me);
           tell_object(couple_ob, MAG "�����Ը������Լ������Ҳ"
                + "��һ�� unmarry ָ�\n" NOR);
                write(MAG
                "������ֻ�е���" +str2 +" ͬ����...\n" NOR);
                return 1;
        }
        destruct(marry_card1);
        destruct(marry_card2);

        message_vision(MAG " $N �� $n �����ڿ�ʼ�����Լ,�������!\n" NOR,
        couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "%s �� %s �����ڿ�ʼ�����Լ,�������! \n",
        me->name(1), couple_ob->name(1)));

        return 1;
}
