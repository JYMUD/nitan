// yinli.c
#include <ansi.h>

inherit NPC;

string ask_me();
void create()
{
        set_name("����", ({ "yin li", "yin", "li"}));
        set("long",
            "�������޼ɵı��ã���Ұ����Ů����һ��������������Ϊ��ǧ����
�ֵ��书����ø��ײ�����\n");
        set("gender", "Ů��");
        set("age", 16);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 12);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_qi", 500);
        set("max_jing", 200);
        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 50000+random(10000));
        set("score", 20000);

        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("unarmed", 80);
        set_skill("qianzhu-wandushou", 70);
        set_skill("qingfu-shenfa",50);
        map_skill("dodge", "qingfu-shenfa");
        map_skill("parry", "qianzhu-wandushou");
        map_skill("unarmed", "qianzhu-wandushou");

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
        set("inquiry", ([
            "���޼�" :  "�����ʰ�ţ����",
            "��ţ"   :  "������Ķ�����......",
               "��ĸ": "������������Ҫ�ң������Ҿͻ�ɱ�ҡ����������Һ����ġ�\n",
               "���": "����ô֪����?���߿�,��Ȼ���㳢���ҵ�ǧ�����ֵ�����!\n",
                "����":(:ask_me:),
        ]));

        set("book_count", 1);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}

string ask_me()
{
        object me,ob;
        ob=this_player(); 

        if (query("book_count") < 1)
                return "�������ˣ��������Ѿ����͸������ˡ�";   
        addn("book_count", -1);                  

        message_vision(HIY"����ӻ����ó�һ�����У����˸�$N \n\n"NOR,ob);
        me=new("/clone/book/jinhe");
        me->move(ob);

        return "���������Ҫ�úñ��ܡ�\n";
}
