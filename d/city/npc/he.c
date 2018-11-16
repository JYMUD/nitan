// he.c

#include <ansi.h>

inherit NPC;

mixed ask_back();

void create()
{
        set_name("��Ա��", ({ "he yuanwai", "he" }));
        set("shen_type", -1);

        set("gender", "����" );
        set("age", 53);
        set("long", "��Ա�������ݳ�����׸����͵��صĹ����к���Ľ��顣��˵�������һ�����Щ��ϵ��\n");
        set("combat_exp", 400);
        set("attitude", "friendly");
        set("inquiry", ([
                "�һ�ʢ��" : (: ask_back :),
        ]));
        setup();

        carry_object(__DIR__"obj/choucloth")->wear();
}

/*
void init()
{
        object ob;
        mapping myfam;
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
*/

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say("��Ա����ֵض���˵��������������ô������ؾ��ܵ��ҵ�԰����������\n");
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "�һ���" )
        {
                message_vision("$N�Թ��Եĸɻ����û������$n��˵ʲô��\n",
                               this_object(), me);
                return -1;
        }

        message_sort("$N��Ȼ̧��ͷ�����������´�����һ��"
                     "��$n���۽�΢΢һ�������̷������е�"
                     "��ƣ����������һֻ�׵�˵������"
                     "������ֻ�׵���һ����ɡ�\n",
                     this_object(), me);

        tell_object(me, HIW "�����ϰ׵���˺ܾã�Խ���󺣣���Ȼ��ǰһ����"
                    "���Ѿ��������һ�����\n" NOR);
        me->move("/d/taohua/jingshe");
        return -1;
}