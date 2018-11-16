// /d/hangzhou/npc/hongniang.c

// Modified by Constant Jan 11 2001

#include <ansi.h>

inherit NPC;

string marry();
string unmarry();

void create()
{
        set_name("����", ({ "hong niang","hong" }) );
        set("title", "����ׯ");
        set("gender", "Ů��" );
        set("age", 16);
        set("long",
                "һλ�����ݵ�С���\n");
        set("max_qi",800);
        set("max_jing",800);
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("inquiry", ([
                "��Լ" : "�ǰ���������Ϳ��Ե޽�(marry)�ͽ����Լ(unmarry)��",
                "���" : "�ǰ���������Ϳ��Ե޽�(marry)�ͽ����Լ(unmarry)��",
                "����" : "�ǰ���������Ϳ��Ե޽�(marry)�ͽ����Լ(unmarry)��",
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

int do_marry(string arg)
{
        object marry_card1,marry_card2, obj, me;
        object *list,ob;
        int i, have_marry;
        me = this_player();
        list = all_inventory(me);
        i = sizeof(list);
        have_marry = 0;

        if( query("couple/times", me)>2 )
        {
                say("����Ц��: �㶼���˼��λ��ˣ�������Ū���˼ҵĸ��飿\n");
                return 1;
        }
        if( query("couple/times", me)>1 )
        {
                say("����Ц��: ������Ķ���������Ů�������������ϳ�������������Ҳ������������������������һ���ˡ�\n");
        }
        if( query("gender", me) == "����" )
        {
                say("����Ц��: ��λ���������ⲻ�ǿ���Цô��\n");
                return 1;
        }
        if( query("class", me) == "bonze" )
                return notify_fail("����Ц���: ���ǳ����ˣ���ʲô�飡����Ϊ���ǲ�����а���\n");
        if( query("age", me)<17 )
                return notify_fail("����Ц��: �㻹С���ȵ�ʮ���������ɡ�\n");
        if( query("couple/couple_id", me) )
                return notify_fail("�����������: ���Ѿ�����˰ɣ�\n");
        if(!arg || !objectp(obj = present(arg, environment(me)))
                || !find_player(arg)|| !find_living(arg))
        return notify_fail("����Ц��: �����˭�޽���Ե��\n");
        if( !environment() || base_name(environment()) != query("startroom") )
                return notify_fail("����Ц��: ���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");
        if( !living(obj) )
                return notify_fail("����̾��������˵��: "+obj->name()+"�Ѿ��޷�����޽���Ե�ˡ�\n");
        if( query("couple/couple_id", obj) )
                return notify_fail("����Ц������: �˼��Ѿ�����˰ɣ�\n");
        if( query("couple/times", obj)>2 )
                return notify_fail("����ٺ���Ц�˼���: �˼Ҷ����˼��λ��ˣ�������Ū��ĸ������š�\n");
        if(obj==me)
                return notify_fail("����Ц��: ���Լ��޽��Լ�����в�����\n");
        if( query("gender", obj) == query("gender", me) )
                return notify_fail("����Ц��: ͬ������û��˵����\n");
        if( userp(obj) && !(query_temp("marks/"+me->name(1, obj))) )
        {
                message_vision(MAG "\n$N����$n˵����"+ RANK_D->query_self(me)
                        + me->name() + "��Ը���"+ RANK_D->query_respect(obj)
                        + "��Ϊ��\n\n"NOR, me,obj);
                set_temp("marks/"+obj->name(1), 1, me);
                tell_object(obj, MAG "�����Ը��ͶԷ���Ϊ�򸾣�����Ҳ��"
                        +me->name()+"("+query("id", me)+
                        ")"+ "��һ�� marry ָ�\n" NOR);
                write(MAG "�����㼱�����������������˵ͬ�⡭��\n" NOR);
                return 1;
        }

        addn("couple/times", 1, me);
        set("couple/have_couple", 1, me);
        set("couple/couple_id",query("id",  obj), me);
        set("couple/couple_name",query("name",  obj), me);
        addn("couple/times", 1, obj);
        set("couple/have_couple", 1, obj);
        set("couple/couple_id",query("id",  me), obj);
        set("couple/couple_name",query("name",  me), obj);
        if( query("gender", me) == "����" )
        {
                set("couple/couple_gender", "�ɷ�", obj);
                set("couple/couple_gender", "����", me);
        }
        else
        {
                set("couple/couple_gender", "�ɷ�", me);
                set("couple/couple_gender", "����", obj);
        }

        message_vision(MAG"��ϲ $N �� $n ��һ���������ϲ����Ե��\n"NOR,obj,me);
        CHANNEL_D->do_channel(this_object(), "chat",
                sprintf("%s �� %s ���ڿ�ʼ�Ƿ�����\n",me->name(1),obj->name(1)));
        return 1;
}

int do_unmarry(string arg)
{
        object me = this_player();
        object ob, couple_ob;
        int i, have_marry;
        string target, tmpstr1, tmpstr2,str1,str2;
        string cardname;

        if( !arg ) return notify_fail("����Ц��: ��Ҫ��˭��飿\n");
        if( !environment() || base_name(environment()) != query("startroom") )
                return notify_fail("����Ц��: ���Ǳ�Ǹ��������һ�µ�����ׯ�����Ұɡ�\n");
        if( !query("couple/couple_id", me) )
                return notify_fail("����Ц��: ��û�а��¡�\n");
        if (!objectp(couple_ob=present(arg,environment(me)))||!find_player(arg))
                return notify_fail("����Ц��: ��İ������ڲ��ڳ���\n");
        if( query("gender", couple_ob) != "Ů��" )
        {
                tmpstr1 = "����"; tmpstr2 = "�Ϲ�";
                str1 = "��"; str2 = "��";
        } else
        {
                tmpstr1 = "�Ϲ�"; tmpstr2 = "����";
                str1 = "��"; str2 = "��";
        }
        if( query("couple/couple_id", me) != query("id", couple_ob) || 
                query("couple/couple_id", couple_ob) != query("id", me) )
                return notify_fail("����Ц��: "+str2+"�������"+tmpstr2+"�����������ʲô�鰡��\n");

        if( userp(couple_ob) && !(couple_ob->query_temp("marks/"
                + "unmarry" +me->name(1))) )
        {
                message_vision(MAG "\n$N����$n˵����" + RANK_D->query_self(me)
                        + me->name() + "�����ǽ����Լ�ɣ�����\n\n"
                        NOR, me, couple_ob);
                set_temp("marks/"+"unmarry"+couple_ob->name(1), 1, me);
                tell_object(couple_ob, MAG "�����Ը������Լ������Ҳ"
                        + "��һ�� unmarry ָ�\n" NOR);
                write(MAG "������ֻ�е���" +str2 +" ͬ����...\n" NOR);
                return 1;
        }
        delete("couple/have_couple", me);
        delete("couple/couple_id", me);
        delete("couple/couple_name", me);
        delete("couple/couple_gender", me);
        delete("couple/have_couple", couple_ob);
        delete("couple/couple_id", couple_ob);
        delete("couple/couple_name", couple_ob);
        delete("couple/couple_gender", couple_ob);

        // ��¼�������������������ѧϰ�ٶȵ���ء�
        // Added by Constant Jan 11 2001
        if( !query("divorce", me) )
                set("divorce", 1, me);
        else
                addn("divorce", 1, me);

        if( !query("divorce", couple_ob) )
                set("divorce", 1, couple_ob);
        else
                addn("divorce", 1, couple_ob);

        message_vision(MAG" $N �� $n �����ڿ�ʼ�����Լ!\n"NOR,couple_ob, me);
        CHANNEL_D->do_channel(this_object(), "chat",
        sprintf( "��ɢ����Ե��%s �� %s �ӽ��Ժ�����ַɣ��������! \n",
        me->name(1), couple_ob->name(1)));

        return 1;
}
