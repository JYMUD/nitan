// tianshi.c ����ʦ
// Modified by haiyan

#include <ansi.h>
inherit NPC;

mixed ask_ghost();
string ask_fail();
int accept_object(object me, object ob);

void create()
{
        set_name("����ʦ", ({ "li tianshi", "li", "tianshi" }));
        set("long", "����һλ�ɷ���ǵķ�ʦ�����ϵĵ����ϻ���һЩ��ħ���š�\n");
        set("nickname", HIY"��������"NOR);
        set("gender", "����");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("str", 20);
        set("int", 20);
        set("con", 25);
        set("dex", 20);

        set("max_qi", 5000);
        set("max_jing", 500);
        set("neili", 3000);
        set("max_neili", 3000);

        set("combat_exp", 800000);
        set("score", 1000);

        set_skill("force", 200);
        set_skill("wudang-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("strike", 200);
        set_skill("wudang-zhang", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("wudang-jian", 200);
        set_skill("taoism", 300);

        map_skill("parry", "wudang-jian");
        map_skill("sword", "wudang-jian");
        map_skill("strike", "wudang-zhang");

        prepare_skill("strike", "wudang-zhang");

        set("inquiry", ([
                "job"   : (: ask_ghost :),
                "׽��"  : (: ask_ghost :),
                "ʧ��"  : (: ask_fail :),
                "fail"  : (: ask_fail :),
                "��ľ��": "��ľ����׽��ıر�֮��Լ�ȥ��һ�Ѻ��ˡ�",
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
        carry_object("/d/taohua/obj/taojian")->wield();
}

#include "dirs.h"
#include "gui.h"

mixed ask_ghost()
{
      string *kp, p, room;
      object me, ob, ghost;
      int dam;
      me = this_player();

      if( query("family/family_name", me) != "�䵱��" && 
          query("family/family_name", me) != "ȫ���" )
           return "��λ" + RANK_D->query_respect(me) + "Ҳ��׽��ı�����";

      if (me->query_skill("taoism", 1) < 50)
           return "�������˰ɣ���������ֻ�¸���׽�ˡ�";

      if( query("combat_exp", me)>400000 )
           return "��������ô�ߣ�����С����ô�����㶯�֣�";

      if( query_temp("gui/shougui", me) )
           return "�ղŲ�������ȥ׽�������ô�ֻ����ˣ�";

      kp = keys(dirs);
      p = kp[random(sizeof(kp))];
      room = dirs[p][random(sizeof(dirs[p]))];
      if( wizardp(me) )  tell_object(me,sprintf("<������� %s �ص�>\n",room));

      dam = me->query_skill("taoism", 1) + random(10) - random(10);
      ghost = new(gui[random(sizeof(gui))] );
      ghost->move(room);
      set_temp("player",query("id",  me), ghost);
      set_temp("born_time", time(), ghost);
      set_temp("damage", dam*2/5, ghost);
      ghost->set_skill("claw", dam);

      tell_object(me, this_object()->name() + "���������˵���" +
                  p + "����" + ghost->name() + "��û����������"
                  "�����亦����ȥ�������˰ɡ�\n");
      message("vision", this_object()->name() + "��" + me->name() + "���߷Ը���ʲô��" +
              me->name() + "һ������һ�߲�ס�ص�ͷ��\n", environment(me), me);
      ob = new("/d/wudang/quest/obj/fuzhi");
      ob->move(this_object());
      command("givefuzhito"+query("id", me));
      tell_object(me, this_object()->name() + "��������" + ob->name() +
                  "�����ù�������ɱ�Ū���ˡ�\n");
      message_vision("$n��$N˵�����춯��ɣ����С�ġ�\n", me, this_object());
      set_temp("gui/shougui", 1, me);
      return 1;
}

string ask_fail()
{
      object me = this_player();

      if( !query_temp("gui/shougui", me) )
           return "��û�и���ʲô���񰡣�";

      if (present("fu zhi", me))
          destruct(present("fu zhi", me));
      delete_temp("gui/shougui", me);
      delete_temp("gui/base", me);
      command("sigh"+query("id", me));
      addn("weiwang", -random(20), me);
      if( query("weiwang", me)<0)set("weiwang", 0, me);
      tell_object(me, HIR"��Ľ������������ˣ�\n"NOR);
      return "�㲻�ܸɣ���ֻ�������ȥ�ˣ�";
}


int accept_object(object me, object ob)
{
    int base, exp, pot;
    if( !me || environment(me) != environment() ) return 0;
    if ( !objectp(ob) ) return 0;
    if ( !present(ob, me) ) return notify_fail("������û������������");
    if( query("id", ob) == "fuzhi" )
    {
         if( !query_temp("gui/finish", me) )
         {
             command("sneer"+query("id", me));
             command("say ����ƭ����ʦ��");
             addn("weiwang", -random(50), me);
             if( query("weiwang", me)<0)set("weiwang", 0, me);
             tell_object(me, HIR"������������ˣ�\n"NOR);
             return 1;
         }

         base=query_temp("gui/base", me);
         exp = base + random(base/2);
         pot = exp/3 + random(exp/3);
         if( query("potential", me) >= me->query_potential_limit())pot=1;
         message_vision("$n��$N���˵�ͷ����������\n", me, this_object());
         tell_object(me, HIG "ͨ�����������������" + chinese_number(exp) +
                     "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n" NOR);
         tell_object(me, HIC"��Ե�ѧ�ķ������µ�����\n"NOR);
         me->improve_skill("taoism", me->query_int()*2);
         addn("combat_exp", exp, me);
         addn("shen", exp/2+random(exp/2), me);
         addn("potential", pot, me);
         delete_temp("gui/base", me);
         delete_temp("gui/shougui", me);
         delete_temp("gui/finish", me);
         destruct(ob);
         return 1;
    }
    else
    {
        command("say ��������ֶ�����ʲô��");
        return 0;
    }
}
