// huqingyu.c
#include <ansi.h>
#include <command.h>
inherit NPC;

void create()
{
        set_name("������",({ "hu qingyu","hu" }));
        set("gender", "����" );
        set("age", 63);
        set("long",
"�������ǵ���һ����ҽ�����ı��������ޱȡ������������֮����\n");
        set("combat_exp", 200000);
        set("attitude", "friendly");
/*
        set("inquiry", ([
                "����": "������ƽ𣬸����ͷ���棬������û�˻�֪����ģ�",
        ]) );
        set("chat_chance", 30);
        set("chat_msg",({
                "�����൭��˵�������ĸ��������������ˡ���\n",
        }));
*/
        setup();
}
void init()
{
        object ob,me;
        //add_action("do_name","name");
//        add_action("do_betrayer","betrayer");
//        add_action("do_age","age");
}
/*
int accept_object(object me, object ob)
{
        if (userp(me))
        {
                if( query("money_id", ob) && ob->value() >= 5000000 )
                {
                        if( query("class", me) == "bonze" || query("class", me) == "quanzhen" )
                        {
                                say("�������ڿڰ�Ц���������ǲ��ܸ����ֵġ��һ�����������ʦ���������ҵ�С���ء�\n");
                                return 0;
                        }
                        command("nod");
                        command("say�ðɣ�"+query("name", me)+"����˵���³̣�\n");
                        set_temp("marks/huqingyu", 1, me);
                        return 1;
                }
        } else return 1;
}
int do_name(string arg,object me)
{
        string *banned_name = ({
                "��", "��", "��", "��", "��", "��", "��", "��", "��",
                "����ү", "������", "����", "ʱ��", "��",
                "ľ��", "��������", "����", "ΤС��",
                "����", "�����п�", "����", "���", "�������", "����",
                "����ѩ", "����", "��־��","Ϻ�����"
        });
        int i;

        me = this_player();
        if( query("class", me) == "bonze" || query("class", me) == "quanzhen" )
                return notify_fail("�������ڿڰ�Ц���������ǲ��ܸ����ֵġ��һ�����������ʦ���������ҵ�С���ء�\n");
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("�����෭�źڰ��ۣ�Ǯ�أ�û��Ǯ��ռ���ˣ�\n");
        }
        if( !arg ) return notify_fail("������Ц���������ܸ�дȫ�ɡ�\n");
        if( strlen(arg) > 10 )
        return notify_fail("�����ྪ��������������ô�������֣�\n");
        if( strlen(arg) < 4 )
        return notify_fail("���������һ������ô����ɶ���֣�\n");
        i=strlen(arg);
        while(i--)
        {
                if( arg[i]<=' ' ) {
                        write("�Բ�������������ֲ����ÿ�����Ԫ��\n");
                        return 1;
                }
                if( (strsrch(arg, "��") >= 0) ||
                    (strsrch(arg, "��") >= 0)) {
                        write("�Բ�������������ֲ������������ĵ��֡�\n");
                        return 1;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) {
                        write("�Բ��������á����ġ�ȡ���֡�\n");
                        return 1;
                }
        }
        if( member_array(arg, banned_name)!=-1 ) {
                write("�Բ����������ֻ���������˵����š�\n");
                return 1;
        }
        if( (strlen(arg) < 2) || (strlen(arg) > 10 ) ) {
                write("�Բ�������������ֱ����� 1 �� 5 �������֡�\n");
                return 1;
        }

        delete_temp("marks/huqingyu", me);
        if( query("gender", me) == "Ů��" )
                message_vision(CYN"�������һ�Ӿ͸���$N�ķ�������ˬ����....\n"NOR,me);
        else message_vision(CYN"�������һ�Ӿ͸���$N�Ĵ���...����\n"NOR,me);
        set("name", arg, me);

        return 1;
}

int do_betrayer(object me)
{
        me = this_player();
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("�����෭�źڰ��ۣ�Ǯ�أ�û��Ǯ��ռ���ˣ�\n");
        }

        delete_temp("marks/huqingyu", me);
        if( query("combat_exp", me)<10000 )
                return notify_fail("��ԩ������ľ��黹���������ʦ�ģ�\n");

        set("betrayer",query("betrayer",  me)+1, me);
        set("title", "��ͨ����", me);
        set("class", "0", me);
        delete("family", me);
        message_vision(CYN"�����Ц���������Ϻ�����գ�����$N������ˣ������������ʦ��¼Ҳ����һ�Σ�\n"NOR,me);
        command("sigh");
        return 1;
}

int do_age(object me)
{
        object obj;
        me = this_player();

        return notify_fail("�����෭�źڰ��ۣ�������������Ҳ��̫�����ˣ�\n");
        if( !query_temp("marks/huqingyu", me) )
        {
                return notify_fail("�����෭�źڰ��ۣ�Ǯ�أ�û��Ǯ��ռ���ˣ�\n");
        }
        delete_temp("marks/huqingyu", me);

        if( query("age", me)<21 )
        {
//                obj=new("/clone/money/gold");
//                obj->set_amount(100);
//                obj->move(me);
                return notify_fail("���������㻹������ģ���һ�����ƽ�����Ϸ�׻��ˣ�\n");
        }

        addn("mud_age", -86400, me);
        addn("age", -1, me);
        delete("last_slp", me);
        delete("jingzuo_time", me);
        log_file("CHANGEAGE",sprintf("%sat%s:%d\n",query("id", me),ctime(time()),query("age", me)));
        message_vision(CYN"����������Ȼ��Ǯ��ʹ����ĥ��$N���ڿ���������ˣ�\n"NOR,me);
        return 1;
}
*/
