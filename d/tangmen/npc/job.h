#include <ansi.h>;

int ask_job()
{
        object me;
        mapping myfam;
        
        me = this_player();
        myfam=query("family", me);
        

        if (! myfam || myfam["family_name"] != "��������")
        {
                command("say �������ǵ�������˵�ҵ������㲻һ������������ȥ�ɣ�");
                return 1;
        }

        if( query("tangmen/yanli", me) >= 100 )
        {       
                command("gongxi");
                command("say ���㳤��һ���˲ţ���֪������һ���ϣ���ɽȥ�ɣ�");
                set("tangmen/upshan", 1, me);
                return 1;
        }

        if( query_temp("started", me) )
        {
                command("say ��������Ϊʲô��ȥ����");
                return 1;
        }
        
        if( query_temp("tmjob_failed", me) )
        {
                delete_temp("tmjob_failed", me);
                me->apply_condition("tmagain", 10);
                command("hmm");
                command("������ȥЪЪ�ɣ�����������\n");
                return 1;
        }               
        
        if (me->query_condition("tmagain") > 0)
        {       command("heng");
                command("say ������˵һ�£���ȵȰɣ�");
                return 1;
        }        

        if( query_temp("jobok", me) == 1 )
        {
                command("say �úã��ɵĺã�����ȥЪЪ�ɡ�");
                addn("combat_exp", 3000, me);
                delete_temp("started", me);
                delete_temp("find_wz", me);
                me->apply_condition("tmjob", 0);
                delete_temp("jobok", me);
                addn("tangmen/yanli", 1, me);
                return 1;
        }
        

        command("say ��ȥ����ץһֻ���ӻ����ɡ�");
        command("say ���²���������ϵ�����ǰ�̣�һ��Ҫȫ��ȥ����");
        command("say �Ҳ����Ļ������ʱ��ˣ�˵�������ջ�");

        set_temp("started", 1, me);
        remove_call_out("putting");
        call_out("putting", 2 , me);
                       
        return 1;
}

int putting(object me)
{
        object ob1,ob2;
        string wh1,wh2;
        string *str = ({"/d/tangmen/kedian","/d/tangmen/edajie",
                        "/d/tangmen/tjpuzi","/d/tangmen/hcfdian",
                        "/d/tangmen/tsqianz","/d/tangmen/xdajie",
                        "/d/tangmen/tmbingqi","/d/tangmen/ndajie",
                        "/d/tangmen/bdajie1","/d/tangmen/bdajie2",
                        "/d/tangmen/jiulou","/d/tangmen/zhongxin",
                       });
        wh1 = str[random(sizeof(str))];
        wh2 = str[random(sizeof(str))];
        ob1 =new("/d/tangmen/npc/askdizi1.c");
        ob2 =new("/d/tangmen/npc/askdizi2.c");
        set("dname",query("id",  me), ob2);
        set("dname",query("id",  me), ob1);
        ob1->apply_condition("tmjob1", 10);
        ob2->apply_condition("tmjob1", 15);
        me->apply_condition("tmjob", 20);
        ob1->move(wh1);
        ob2->move(wh2);        
        tell_object(me, HIC "Ҫ��ȥ��ذ���\n" NOR);
        return 1;
}       
        
