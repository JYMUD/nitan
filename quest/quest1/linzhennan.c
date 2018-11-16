// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// linzhennan.c ������   

inherit NPC; 
#include <ansi.h>  
#include "biao.h"

mixed ask_biaodui();
mixed ask_yunbiao();
int   ask_fuwei();
int   ask_yuantu();
int   ask_pixie();
int   ask_tong();

void create()
{
        set_name("������", ({ "lin zhennan", "lin"}));
        set("gender", "����");
        set("age", 65);
        set("title", "�����ھ�����ͷ");
        set("long", "�����Ǹ����ھ�����ͷ���������ϡ�\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);
        
        set_skill("force", 140);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set("inquiry", ([     
                "����"     : (: ask_yunbiao :),
                "�ڶ�"     : (: ask_biaodui :),  
                "��"       : (: ask_yunbiao :),
                "������լ" : "������˵���������Ҵ�ǰ�ڸ���ʱס�ļ�Ժ���Ѿ��ư��ˡ�\n",
                "�����ھ�" : (: ask_fuwei :),
                "Զͼ��"   : (: ask_yuantu :),
                "��Զͼ"   : "�����ϴ�ŭ��С������ôû��ò��ֱ���������䣡\n",
                "��а����" : (: ask_pixie:),
                "ͭǮ"     : (: ask_tong:),
                "ͭ��"     : (: ask_tong:),
        ]));
        set_temp("apply/attack", 500);
        set_temp("apply/defense", 500);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_fuwei()
{
         say("��������ҫ��˵�������ּ��������ڣ�һ����������Զͼ�����괳�µ���������\n"
                 "�����������ּҼҴ������ն����㺬��������н��յľ��棬��Ϊ����������\n"
            "һָ�Ĵ��ھ֡��������ᵽ�������ھ֡����֣�˭��Ҫ�����Ĵָ��˵һ������\n"
            "�ø����������磡��������������\n");
         set_temp("marks/��1", 1, this_player());
         return 1;
}

int ask_yuantu()
{
          if( query_temp("marks/��1", this_player()) )
          {
                 say("�����Ͽ�һ���̶���˵����Զͼ�����ҵ��游�������ھ�����һ�ִ���ġ�����\n"
                        "�游����ʮ��·��а���������ھ֣������Ǵ��ڵ��޵��֡���ʱ�׵���Ӣ�ۼ�\n"
                          "��̫�����磬Ҳ��ȥ�����������յģ�����������������ʦ������������֮ʱ\n"
                        "��������а���������˼��С�\n");
                 set_temp("marks/��2", 1, this_player());
                 return 1;
          }
          else 
          {
                 say("������˵����Զͼ�����ҵ��游��\n");
                 return 1;
          }
}

int ask_pixie()
{
          int p1, p2, p3, p4;
          if( query("passwd", this_player()) )
          {
                 say("�����ϲ��õ�˵�����Ҳ��Ƕ������������ҵĽ����������档\n");
          }
          else if( query_temp("marks/��2", this_player()) )
          {
                 say("������һ����˵��������ô֪���ģ��ޣ��Ҹղ�˵¶���ˡ��ˣ����µĹ�������\n"
                          "��֪��ϸ����ʵ���������档��\n");
                 write("�����϶�һ�٣����Ŷ������˵������ȥ��ǰ�������Ҹ�����");
                 p1 = random(4) + 1;
                 p2 = random(4) + 1;
                 p3 = random(4) + 1;
                 p4 = random(4) + 1;
                 set("passwd", p1*1000+p2*100+p3*10+p4, this_player());
                 write(CHINESE_D->chinese_number(p1) + "ǧ" + CHINESE_D->chinese_number(p2) +
                             "��" + CHINESE_D->chinese_number(p3) + "ʮ" + CHINESE_D->chinese_number(p4));
                 write("��\nͭǮ����һֱδ�����а��ء�\n");
          }
          else 
          {
                   message("vision",
                           HIM "�����ϲ�Ȼ��ŭ���ȵ�����Ҳ���������ּҵı�а���ף����Ҹ���ƴ�ˣ�\n" NOR, 
                           environment(), this_object());
                   kill_ob(this_player());
          }
          delete_temp("marks/��1", this_player());
          delete_temp("marks/��2", this_player());
          return 1;
}

int ask_tong()
{
          int p, p1, p2, p3, p4;
          if( !(p=query("passwd", this_player())) )
          {
                 say("������һ����Ц�����ӣ�˵����ô�쵽��һ���˵���ҪǮ��\n");
          }
          else 
          {
                 write("�����ϵ���˵������ȥ��ǰ�������Ҹ�����");
                 p1 = (int)p / 1000;
                 p2 = (int)(p - p1 * 1000) / 100;
                 p3 = (int)(p - p1 * 1000 - p2 * 100) / 10;
                 p4 = (int)(p - p1 * 1000 - p2 * 100 - p3 * 10);
                 write(CHINESE_D->chinese_number(p1) + "ǧ" + CHINESE_D->chinese_number(p2) +
                             "��" + CHINESE_D->chinese_number(p3) + "ʮ" + CHINESE_D->chinese_number(p4));
                 write("��\nͭǮ����һֱδ�����а��ء�\n");
          }
          return 1;
}

string chinese_time(int t)
{
        int d, h, m, s;
        string time;
        s = t % 60;     t /= 60;
        m = t % 60;     t /= 60;
        h = t % 24;     t /= 24;
        d = t;
        if (d) time = chinese_number(d) + "��";
        else time = "";
        if (h) time += chinese_number(h) + "Сʱ";
        if (m) time += chinese_number(m) + "��";    
        time += chinese_number(s) + "��";
        return time;
}

mixed ask_yunbiao()
{
            int time;
            object me, biaoche;
            mapping biao;

            me = this_player();

        if( count_lt(query("combat_exp", me),100000) )
                      return "���ڿ��Ǽ�Σ�յĲ�ʹ�����������˹��������ɣ�\n";    
                      
            if( query_temp("quest_yunbiao/have_task", me) )
                       return "���ϴε��ڻ�û�͵��أ���ô�����ˣ�\n"; 

/*
            if( query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/finished_time", me))<20 )
                       return RANK_D->query_respect(me) + "�����ˣ�����û���ڳ�Ҫ�ˣ����������ɣ�\n";
*/

            if( mapp(query_temp("quest_yunbiao", me) )
         && !query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "����ҵ���Ū����ȥ�������Ǳ��˽��˰ɣ�\n";

            biao = yun_biao[random(sizeof(yun_biao))];
            time = biao["time"];
            
            delete_temp("quest_yunbiao", me);
            set_temp("quest_yunbiao/name", biao["name"], me);
            set_temp("quest_yunbiao/file", biao["file"], me);
            set_temp("quest_yunbiao/bonus", biao["bonus"], me);
            set_temp("quest_yunbiao/time", biao["time"], me);
            set_temp("quest_yunbiao/start_time", time(), me);
            set_temp("quest_yunbiao/have_task", 1, me);

            biaoche = new(__DIR__"biaoche");
            set("time", time, biaoche);
            set("file", biao["file"], biaoche);
            biaoche->start_escape_me();
            set("owner",query("id",  me), biaoche);
            set("owner_name",query("name",  me), biaoche);
            biaoche->move(environment(me));
            
        /*
             message("channel:rumor",HIM"���ھִ��š�"+query("name", me)+
                     "���������ڳ����ǰ��" + biao["name"] + "��\n" NOR,
                     users());  
        */
        
            delete_temp("apply/short", me);
            me->set_temp("apply/short",
                            ({HIM"�����ھ���ͷ"NOR+me->name()+"("+query("id", me)+")"}));

            message_sort(HIM "$N" HIM "��$n" HIM "�Ը���������" + chinese_time(time) + "�ڣ����ڳ����͵�" +
                     biao["name"] + "��һ·���С�ģ��㻹�ǳ�����·�ɣ�\n" NOR, this_object(), me);
        return 1;
}


mixed ask_biaodui()
{
            int time, i;
            object me, parter, biaoche, *team;
            mapping biao;

            me = this_player();

        if( count_lt(query("combat_exp", me),200000) )
                      return "���ڿ��Ǽ�Σ�յĲ�ʹ�����������˹��������ɣ�\n";
                      
            if (! pointerp(team = me->query_team()))
                       return "�ڶ���Ҫ�˶�һ����б��ϣ����Щ�������ɣ�\n";

            i = sizeof(team);
            if (i > 2) return "�˶����ӣ����׻��£�\n";

            if (objectp(team[0]) && objectp(team[1]))
            {
                     if(team[0] == me) parter = team[1];
                     else parter = team[0];
            }

            if (! objectp(parter) 
         || !present(query("id", parter),environment(me)) )
                       return "����Լ�����ͬ��һ�����ɣ�\n";

            if( query_temp("quest_yunbiao/have_task", me) )
                       return "�����ϴε��ڻ�û�͵��أ���ô�����ˣ�\n";

            if( mapp(query_temp("quest_yunbiao", me) )
         && !query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "����ҵ��ڶ�Ū���ˣ���Ȼ�������������ң�\n";

        if( count_lt(query("combat_exp", parter),50000) )
                      return "���ڿ��Ǽ�Σ�յĲ�ʹ����Ҫ�����ͬ��ȥ�����ˣ�\n";
                      
            if( mapp(query_temp("quest_yunbiao", parter) )
         && !query_temp("quest_yunbiao/finished_time", parter )
         && (time()-query_temp("quest_yunbiao/start_time", me))<120 )
                       return "�����������ܵ�ͬ�鵱���֣��ҿɲ����İ��ڶӽ����㣡\n";

            biao = yun_biao[random(sizeof(yun_biao))];
            time = biao["time"];
            
            delete_temp("quest_yunbiao", me);
            set_temp("quest_yunbiao/name", biao["name"], me);
            set_temp("quest_yunbiao/file", biao["file"], me);
            set_temp("quest_yunbiao/bonus", biao["bonus"], me);
            set_temp("quest_yunbiao/time", biao["time"], me);
            set_temp("quest_yunbiao/start_time", time(), me);
            set_temp("quest_yunbiao/have_task", 1, me);

        delete_temp("quest_yunbiao", parter);
            set_temp("quest_yunbiao/name", biao["name"], parter);
            set_temp("quest_yunbiao/file", biao["file"], parter);
            set_temp("quest_yunbiao/bonus", biao["bonus"], parter);
            set_temp("quest_yunbiao/time", biao["time"], parter);
            set_temp("quest_yunbiao/start_time", time(), parter);
            set_temp("quest_yunbiao/have_task", 1, parter);

            biaoche = new(__DIR__"da_biaoche");
            set("time", time, biaoche);
            set("file", biao["file"], biaoche);
            biaoche->start_escape_me();
            set("owner",query("id",  me), biaoche);
            set("parter",query("id",  parter), biaoche);
            set("owner_name",query("name",  me), biaoche);
            biaoche->move(environment(me));

        /*
            message("channel:rumor",HIM"���ھִ��š�"+query("name", me)+
                     "������ڶӼ������ǰ��" + biao["name"] + "��\n" NOR, users());
        */
        
            delete_temp("apply/short", me);
            me->set_temp("apply/short",
                         ({HIM"�����ھ���ͷ"NOR+me->name()+"("+query("id", me)+")"}));

            delete_temp("apply/short", parter);
            parter->set_temp("apply/short",
                             ({HIM"�����ھ���ʦ"NOR+parter->name()+"("+query("id", parter)+")"}));

            message_sort(HIM "$N" HIM "��$n" HIM "�Ը���������" + chinese_time(time) + "�ڣ����ڶ����͵�" +
                     biao["name"] + "��һ·���С�ģ����ǻ��ǳ�����·�ɣ�\n" NOR, this_object(), me);
        return 1;
}

void die()
{
        this_object()->recover();  
        return; 
}

void unconcious()  
{
        this_object()->recover();  
        return; 
}