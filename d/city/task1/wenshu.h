// Room: /d/city/wenshu.h


void init()
{
  call_out("dest", 1800);
  add_action("do_guankan", ({"guankan","kan"}));
  add_action("do_wancheng", ({"wancheng"}));
}

int do_guankan(string arg)
{
        int now_time, time;
        object me;

        me = this_player();
        now_time = me->query_condition("guanfu_task");
        time=query_temp("guanfu_time", me);

        if(!arg) return 0;
        if( arg=="wenshu" )
        {
                write("\n����һ������֪������׽�ý����������飬�������������Ļ���һ��\n�˵�ͷ��������һ��С�֣�����д�ţ�\n����������"+query_temp("guanfu_targetnm", me)+"��������׽�á���\n�ݷɸ봫�飬�÷�Ŀǰ��û�ڡ�"+query_temp("ch_weizhi", me)+"��������\n");
                if(now_time>time*3/4) write("�������г����ʱ��ȥѰ��Ŀ�ꡣ\n");
                if(now_time>time/2 && now_time<=time*3/4 ) write("�Ѿ���ȥһС��ʱ���ˡ�\n");
                if(now_time>time/4 && now_time<=time/2 ) write("�㻹��һ���ʱ��ȥ׷��Ŀ�ꡣ\n");
                if(now_time>time/8 && now_time<=time/4 ) write("���ʱ���Ѿ������ˡ�\n");
                if(now_time>0 && now_time<=time/8) write("�ٸ������Ѿ������µ�Ŀ���ˣ���Ҫץ��ʱ���ˣ�\n");
                return 1;
        }
}

int do_wancheng(string arg)
{
        object me, target;
        int exp,pot,score,gfjob_times,now_time;

        if(!arg) return notify_fail("��Ҫ��ʲô��\n");
        me = this_player();
        target = present(arg, environment(me));
        now_time = me->query_condition("guanfu_task");

        if(!target) return notify_fail("�Ҳ������������\n");
        if( query("id", target) != "corpse")return notify_fail("�㲢û���������\n");
        if( query("victim_id", target) != query_temp("guanfu_target", me) )
                return notify_fail("�Ǹ�������Ŀ�꣡\n");
        if( query("victim_user", target) )
                return notify_fail("�ٺ٣������ף���\n");
        if( query("kill_by", target) != me )
                return notify_fail("������һ����Ŀ���Ѿ�����ɱ�ˡ�\n");
  if( query_temp("mark/dune1", target) )
                return notify_fail("���Ѿ���һ���Ѿ�����ɱ����ʬ���ˡ�\n");

        addn("gf_job", 1, me);
        gfjob_times=query("gf_job", me);
        if (gfjob_times < 1) gfjob_times = 1;
        message_vision(HIW "$N��Цһ�����ӻ����ͳ����鿴�˿���΢���ھ�����������з����ȥ��\n�������黯��ƬƬѩƬ��������$n���ϡ�\n"NOR, me, target);
        write(WHT "�ܺã���ɹ������������Ŀǰ���Ѿ�Ϊ�ٸ�����"+chinese_number(gfjob_times)+"�ι��ס�\n"NOR);
        set("long",query("long",  target)+"������������ֽƬ��\n", target);
  set_temp("mark/dune1", 1, target);
        delete_temp("guanfu_time", me);
        me->clear_condition("guanfu_task");
        delete_temp("guanfu_target", me);
        delete_temp("guanfu_targetnm", me);
        delete_temp("ch_weizhi", me);
        delete_temp("path_rooms", me);
        delete_temp("gstart_rooms", me);
        delete_temp("mark/gkill3", me);

//����һЩ����
        exp=800+random(400);
        if (exp > 1000) exp = 1000;
        pot=250+random(100);
        if (pot > 300) pot = 300;
        score=250+random(100);
        if (score > 300) score = 300;
        addn("potential", pot, me);
        addn("combat_exp", exp, me);
        addn("score", score, me);
        write(HIW"�㱻�����ˣ�\n" +
               chinese_number(exp) + "��ʵս����\n" +
               chinese_number(pot) + "��Ǳ��\n"+
               chinese_number(score) + "�㽭������\n"NOR);
        destruct(this_object());
        return 1;

}

void dest()
{
        object me = this_player();
        write("�����Ѿ��������ģ�������ˣ������Ѿ�ûʲ�����ˣ���ֻ�����ֶ�����\n", me);
        destruct(this_object());
}
