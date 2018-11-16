// This program is a part of NT MudLIB
// /d/ruzhou/npc/meipo.c ֻ�����������

#include <ansi.h>
#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR        "/data/item/ring/"

inherit NPC;

int do_marry(string);
int do_name(string);
int do_chase(object,object);
int do_ok(object,int);
int meipo_waiting(object,object,object);
int ready_marry(object,object,object);
int wait_marry(object,object,object);
int start_marry(object,object,object);
int go_lou(object,object);
int do_back(object);
int do_bai(string);
int do_right(object me, object ob);
int return_home(object);

void create()
{
        set_name("ý��", ({ "mei po", "meipo", "mei", "po" }) );
        set("gender", "Ů��" );
        //set("nickname", HIR "������ʼ���գ�" HIC "����" HIR "�������̣�����������" NOR); 
        set("title", "����ׯ");
        set("age", 43);
        set("long","һλ�����ܸɵ���ý�š�\n");
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("inquiry", ([
                "���" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
                "marry" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)��ȻҪ��������ý��ѽ����\n",
                "�Ǽ�" : "ý��Ц���еص�ͷ�������ǰ�... Ҫ���(marry)�Ǽǵ�ȻҪ��������ý��ѽ����\n",
                "���" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...���ҿ��ǿ����ǳɻ��ѽ��\n"
                      "��������Ҫ��һ��Ҫ��Ļ����ǵ�ȥ����֪���������ˣ���\n",
                "unmarry" : "ý����ɫһ�䣬�е���ǿ��Ц������Ҫ...���(unmarry)����...���ҿ��ǿ����ǳɻ��ѽ��\n"
                      "��������Ҫ��һ��Ҫ��Ļ����ǵ�ȥ����֪���������ˣ���\n",
                "����":"ý������Ц�����������ô����£����ѵĵط��ɲ��٣�Ҫ50 gold��,�����\n"
                      "��Ҫ���Ѳ���Ǯ������Ҫ100 gold����\n",
        ]) );
        set_skill("literate", 100);
        set_skill("dodge", 500);
        set_skill("unarmed", 300);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_marry", "marry");
        add_action("do_bai","��");
        add_action("do_name","��");
}

int accept_object(object me, object ob)//��Ǯ
{
        object meipo = this_object();

        if( !query("money_id", ob) )
             return notify_fail("ý������Ц���������������г��кȲ���ʲô���������û�ȥ�ɣ���\n");
        if( !query_temp("ask_money", me))//�������жϽ�Ǯ�����Ƿ���Ͻ��������
                   return notify_fail("ý���Ի���ʣ��������ʲô���׸���Ǯ����\n");
          if( query_temp("marry/money", meipo))//�Ѿ����˽���Ǯ��
                  return notify_fail("ý��˵��������æ����һ����˵����\n");
          if(ob->value() < 500000)
                return notify_fail("ý��������üͷ˵������Ǯ̫���˰ɣ�50 gold�������ô����£����پͲ����ˡ���\n");
        message_vision("ý�Žӹ�Ǯ��$N˵������λ"+RANK_D->query_respect(me)+"�ҿ�û׬���Ǯ��������һ�Ҫ����ϲ�á���\n"
                   "Ҫ���ˡ����а���磬�㲻���һ�������һ��ģ������һ����԰��㷢������\n"
        "���������"HIC"���� <ĳ�˵�����>��"NOR"������������μӻ��񡣡�\n",me);
        set_temp("marry/money", me->name(), meipo);//��¼����Ǯ����
        log_file("static/MARRY",sprintf("%s(%s)��齻Ǯin%s��\n",query("name", me),
                query("id", me),ctime(time())));
          return 1;
}

int do_name(string target)//�����
{
        object me,ob,dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();

        if (me->is_busy())
                return notify_fail("ý��˵��������æ����ٺ���˵���ɣ���\n");
        if( ob->is_fighting()||me->is_fighting() )
                return notify_fail("ý��˵����������û���򣡡�\n");
        if( !living(ob) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");
        if( query_temp("marry/money", ob) != me->name() )
      return notify_fail("ý���۾�б��б�㣺������û��Ǯ����\n");
        if( query("marry/waiting_que", ob) )
                return notify_fail("ý��ЦЦ˵������Ҫ�����ҵ�Сϲȵ�ǻ�û�зɻ����أ���\n");
        if( !target || target==" ")
                return notify_fail("ý�ų��һ�����д�˼����ʣ���������˭���μ���Ļ��񣿸�������(��)�����֣���\n");
        for(i=0; i<sizeof(all); i++)
        {
                if( query("env/invisible", all[i]))continue;
                if( target == all[i]->name() || target == query("id", all[i]) )
                {
                        dest = all[i];
                        break;
                }
        }
    if( !dest)
                return notify_fail("ý�Ÿ����㣺�����ź�����������������ڲ�����Ϸ�У���\n");
        if (dest->is_ghost())
                   return notify_fail("ý����ϧ�صظ����㣺����������֪����Ҫ������Ѿ����ˣ�����ڰ�˳�㣡��\n");
        set("marry/waiting_que", 1, ob);//��ȵ
        set("marry/me_name", me->name()+"("+query("id", me)+")", ob);//������
        message_vision(HIG"ý��һ��ϲ����д�ϼ����֣�˫��һ�ģ��Ӷ��Ⱦͷɳ�һֻСϲȵ������ϲ����\n"
                "���㶵�һ������ʧ��������ˡ�\n" NOR,me);
        call_out("do_chase", 1, ob,dest);
        return 1;
}

int do_chase(object ob,object dest)//ϲȵ�����
{
        object obj;

        if( !objectp(dest) || !environment(dest) )
        {
                call_out("do_ok",1,ob,1);//��һ��ʧ�ܵĲ�����ȥ
                return 1;
        }
        message_vision(HIY"\n�����ͻȻ�ɹ���һֻ��ϲȵ������$N��ͷ�������ŵ�һ��ϲ��ݸ�$N��\n" NOR, dest);
        obj = new("/d/ruzhou/npc/obj/xitie");
        obj->set_name(HIR+query("marry/me_name", ob)+"�Ľ������"NOR);
        obj->move(dest);
        call_out("do_ok", 1, ob,0);
        return 1;
}

int do_ok(object ob,int flag)//ϲȵ�ͼ�ɹ�����
{
        if(flag)
                message_vision("��ϲȵ�Ӵ���������طɽ���������ý�����ԣ�ý��Ŷ��һ��˵�����ղŵ��Ǹ���û�ҵ��������������˰ɣ���\n",ob);
        else
                message_vision("ͻȻ������ϲȵ�Ӵ���ɽ���������ý�����ԣ�ý��Ц���еظ��Ż�ϲȵ��ͷ��\n"
                        "˵���������ղ��Ѿ����͵��ˣ���������˭���������˾Ϳ�ʼ�������(marry <��Ķ���>)�ɣ���\n",ob);
          delete("marry/waiting_que", ob);
        delete("marry/me_name", ob);
        return 1;
}

int do_marry(string arg) //�жϽ��
{
    object obj, me, ob, old_target, room, xlf;
        me = this_player();
        ob = this_object();
        if( query("marry/have_couple", ob) )
                return notify_fail("ý��һ㶣�����������ϲ����ô�ࣿ�Բ����Ұ���ͷ��һ�ԵĻ��°��꣬�ٸ����ɣ���\n");

    room = find_object("/d/city/zxlpath");
    if (! objectp(room))  room = load_object("/d/city/zxlpath");
    xlf = present("xi laifu", room);
    if (objectp(xlf))
         return notify_fail("ý��Ц��������ѽ�治���ɣ�ϲ�ϰ��������ֻ��磬" +
                            "Ҫ������������ȥ�ȱ�ϲ�ƣ������ٸ����ǰ죿��\n");

/*
        if( query("gender", me) == "����" )
                return notify_fail("ý�ź���һ���������޸����ԣ����ʲô�飿����\n");
        if( (query("age", me)<14) && (query("gender", me) == "����" )
                 || (query("age", me)<14) && (query("gender", me) == "����" )
                 || (query("age", me)<14) && (query("gender", me) == "Ů��") )
                return notify_fail("ý��Ц������˵�������������ڻ����ᣬ�Ժ���˵�ɣ���\n");
*/
        if (me->is_busy())
                return notify_fail("ý��˵�����������ڲ�����æ���𣿡�\n");
        if( me->is_fighting(ob) )
        {
                if( !ob->is_killing(me) )
                        ob->kill_ob(me);
                return notify_fail("ý��˵�������ã��ã���������ȥ����ɻ飡��\n");
        }
        if( ob->is_fighting() )
                return notify_fail("ý��˵������û����������˵����𣡡�\n");
        if( !living(ob) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");
        if( me->is_fighting() )
                return notify_fail("ý��˵�����ٺ٣����Ȼ������������������˵�ɣ�\n");
        if( !environment() || base_name(environment()) != query("startroom"))
                return notify_fail("ý��˵�������汧Ǹ�������ں�æ��������һ�ᵽ�����������Ұɡ���\n");
        if( query("class", me) == "bonze" || query("jobname", me) == "bonze" )
                return notify_fail("ý��Ц��������������ô���ŷ��Ҳ�뿪ɫ������?��\n");
        if( query("jobname", me) == "taoist" )
                return notify_fail("ý��ҡ��ҡͷ�����������˵������Ƿ��Ĳ�����������Ҫ�����룬���ǻ����������ɣ���\n");
        if(!arg ||!objectp(obj = present(arg, environment(me))))
                return notify_fail("ý��˵������������Ҫ������һ������ѽ����\n");
        if( query_temp("pending/pro", me) )
                return notify_fail("ý����������ף���Ļ��������ڽ������𣿻�Ҫ��ʲô����\n");
        if( query_temp("pending/pro", obj) )
                return notify_fail("ý��˵��������������˽����𣿡�\n");
        if( !obj->is_character() )
                return notify_fail("ý��˵���������ⲻ�����Լ������𡣡�\n");

        if( mapp(query("couple", me)) )
        {
                if( query("couple/married", me)>2 )
                        return notify_fail("ý�ŷ��˷���Ե����������˵����������͸���˵������ô�����ˣ�\n"
                                "�����ʵ�ڲ��ܰ���ʲô�ˣ��������̫���ˣ�����͢�ټͣ��ǲ�׼�ٸ�����\n"
                                "���������ˣ������Լ�ȥ����Ұԧ��ɣ�\n");
                if( query("couple/have_couple", me) )
                {
                        if( obj == present(query("couple/couple_id", me),environment(me)) )
                                return notify_fail("ý������������Ǳ������Ƿ���ѽ�����ﻹҪ��������\n");
                        if( query("couple/couple_gender", me) == "�ɷ�" )
                                return notify_fail("ý��˵���������Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ���\n");
                        else
                                return notify_fail("ý��˵���������Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ���\n");
                }
        }
        if( mapp(query("couple", obj)) )
        {
      if( query("couple/married", obj)>2 )
              return notify_fail("ý�ŷ��˷���Ե����̾�˿����������������˵������ô�����ˣ���\n"
              "����ʵ�ڲ��ܰ�����ʲô�ˣ�����û���⣬��"+obj->name()+"������̫���ˣ�\n"
              "����͢�ټͣ��ǲ�׼�ٰ����������ˣ�����ȥ����Ұԧ��ɣ�\n");
             if( query("couple/have_couple", obj) )
                {
                        //if( query("couple/couple_gender", obj) == "�ɷ�" )
                        if( query("gender", obj) == "����" )
                                return notify_fail("ý��˵������ϧ���Ѿ����з�֮���ˣ����ﲻ�����ػ�ġ�\n");
                        else
                                return notify_fail("ý��˵������ϧ���Ѿ����и�֮���ˣ����ﲻ�����ػ�ġ�\n");
                }
        }
        if( !living(obj) )
                return notify_fail("ý��ҡҡͷ˵������"+ obj->name()+"���ڻ�û���ѹ������һ�����ȷ������˫��������Ը�ġ���\n");
        if(obj == me)
                return notify_fail("ý��˵���������ⲻ�����Լ������𣿡�\n");
        if( query("gender", obj) == query("gender", me) )
                return notify_fail("ý�ž��������ۣ�����ͬ�������Բ��������Ӵ��������£���\n");
        if( !userp(obj) )
                return notify_fail("ý��˵�������Բ�����ֻ�ܺ���ҽ�顣��\n");
        if( query_temp("marry/money", ob) != me->name( )
                    && query_temp("marry/money", ob) != obj->name())//ֻҪ������һ���˸�������
           {
                set_temp("ask_money", 1, me);
            set_temp("ask_money", 1, obj);//��ʾ�������ϣ����Ը�Ǯ����ֹ���������׸�Ǯ
                   return notify_fail("ý��Ц�����ص��������Ҫ��һ��Ǯ��ඣ�Ҫ50 gold������Ǯ���ҿ�û������죡\n");
        }
        if( !query_temp("marry/answer", me) )
        {
                message_vision(HIG"ý��̯����Ե��������߶߶��˵�����������һ���ӵ�������£��ɲ���\n"
                           "�����㣬���������������ˡ�ÿ����ֻ��������������ν��������\n"
                        "���ҿ�����"HIC""+me->name()+"���"+query("couple/married", me)+"�λ飻"+obj->name()+"���"+query("couple/married", obj)+"�λ飻"
                        HIG"�õģ�\n������������濼��һ�£��ǲ�������Ը��ͶԷ���飿��\n"NOR,me);
                set_temp("marry/answer", 1, obj);
        }
        if( query_temp("pending/marry", obj) != me )
        {
                if( query("gender", obj) == "Ů��" || (query("gender", obj) == "����" && query("gender", me) == "����") )
                        message_vision(MAG "\n$N����$n�ʵ�������Ը��޸����𣿡�\n\n"NOR, me,obj);
                else
                        message_vision(MAG "\n$N����$n�ʵ�������Ը��Ȣ���𣿡�\n\n"NOR, me,obj);

                if( objectp(old_target=query_temp("pending/marry", me)) && old_target != obj )
                        tell_object(old_target, YEL + me->name() +
                        "ȡ���˺��������ͷ��\n" NOR);
                set_temp("pending/marry", obj, me);
                if( query("gender", obj) == "Ů��" || (query("gender", obj) == "����" && query("gender", me) == "����") )
                        tell_object(obj, MAG "�����Ը��޸���������Ҳ��" + me->name()
                        +"("+query("id", me)+")"+"��һ��marryָ�\n"NOR);
                else
                        tell_object(obj, MAG "�����Ը��Ȣ��������Ҳ��" + me->name() +
                        "("+query("id", me)+")"+"��һ��marry"+query("id", me)+"��ָ�\n"NOR);
                write(MAG"�����㼱�����������������˵ͬ��...\n" NOR);
                return 1;
        }
        message_vision(MAG "\n$N����$n����˵������Ը�⣡\n\n"NOR, me,obj);
        message_vision(MAG "ý�źǺ�Ц�������Ǿͺã��Ǿͺã������ҵ����ߵ���Ե����׼�����ðɣ���\n"
                "˵�꣬ý��һŤһŤ���߽��˶��ߵĴ��á�\n" NOR, obj, me);
        me->delete_temp("ask_marry");//���ȡ���ʽ��Ĳ���
        obj->delete_temp("ask_marry");//���ȡ���ʽ��Ĳ���

        ob->delete_temp("marry/money");//ý��ȡ������Ǯ�Ĳ���
        set("marry/have_couple", 1, ob);//ý�������ֻ�����
        ob->move("/d/city/yinyuan-tang");

        set_temp("pending/pro", 1, me);
        set_temp("pending/pro", 1, obj);//������

        set("couple/couple_name", obj->name(1), me);
        set("couple/couple_id",query("id",  obj), me);
        set("couple/couple_name", me->name(1), obj);
        set("couple/couple_id",query("id",  me), obj);//��ʽ������

        if( query("gender", obj) == "Ů��" || (query("gender", obj) == "����" && query("gender", me) == "����") )
        {
                set("couple/couple_gender", "����", me);
                set("couple/couple_gender", "�ɷ�", obj);
        }
        else
        {
                set("couple/couple_gender", "����", obj);
                set("couple/couple_gender", "�ɷ�", me);
        }
        call_out("meipo_waiting", 1,ob,me,obj);
         return 1;
}

int meipo_waiting(object ob,object me,object obj)//ý�ŵȰ���
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say( "ý���ɻ��˵������С����������Ҳ�������ѵ�������Ե�޷ݣ�����������ȡ���գ�\n"
              "������ǰ�׬��50 gold�ˣ��ǺǺ�...��\n\n");
                call_out("do_back", 0, ob);
                return 1;
        }
        if( environment(ob)==environment(me)&&environment(ob)==environment(obj) )
        {                                                 //���˶���
                delete_temp("wait_time", ob);
                call_out("ready_marry", 1,ob,me,obj);
        }
        else
        {
                if( environment(ob)==environment(me)&&environment(ob)!=environment(obj) )
                {
                        if( random(10) == 0 )
                        say("\ný���ʵ�����"+me->name()+"����ȥ����"+obj->name()+"��ô�����������ѵ���Ը���ˣ�\n");
                        addn_temp("wait_time", 1, ob);//����һ��obj����
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                   else if( environment(ob)!=environment(me)&&environment(ob)==environment(obj) )
                {                                            //����һ��me����
                        if( random(10) == 0 )
                        say("\ný���ʵ�����"+obj->name()+"����ȥ����"+me->name()+"��ô�����������ѵ���Ը���ˣ�\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                else
                {
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
        }
        return 1;
}

int ready_marry(object ob,object me,object obj)//׼������
{
        object room,npc;

        if(!( room = find_object("/d/city/yinyuan-tang")) )
        room = load_object("/d/city/yinyuan-tang");

        message("vision", HIY "\ný�Ÿ����е��������죬�ɻ�Ķ������ˣ����ϲ���ϲ�ã���\n" NOR, room);
        message("vision", HIC"\nֻ���ú�����һ��Ų�����ʮ����������������·���������Ů�����������ܽ�����\n"
                "ߴߴ�����������ţ��ַ�ͷ�ܿ��ˣ�ʱ��ʱ��Ц�ſ�һ��"+me->name()+"��"+obj->name()+"��\n\n"NOR, room);
        say("ý�Ŷ���λ����˵��������Ҫ�ż������Ƕ��Ǻ��о���ģ��ܿ�ͻ᲼�úõģ���\n"
                CYN"ֻ����ߵ���������ȥ��æ�ò����ˡ�\n"NOR);
        call_out("wait_marry", 1, ob,me,obj);
        return 1;
}

int wait_marry(object ob,object me,object obj) //����ϲ��
{
        object room,m_cloth,w_cloth;
        if(!( room = find_object("/d/city/yinyuan-tang")) )
                room = load_object("/d/city/yinyuan-tang");
        addn_temp("wait_time", 1, ob);
        switch(query_temp("wait_time", ob) )
        {
           case 0:
            say(RED"\nһ��С�һ��ܹ������е�����ý�ţ����ֽ��Ǯ�����ˣ���ý�ŸϽ�����һЩǮ��\n\n"NOR);
                break;
        case 1:
             say(MAG"\nͻȻ���Ǳߵ�С����е�����ý�ţ���ԧ�����������������ý��һ�������ұ�����ȥ�㣡��\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 2:
             say(CYN"\n�ĸ��һ��Ӵ��Ӵ��̧��һֻ�����Ӵ�����������߹���ý�Ŷ�����������Щ����㣡��\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 3:
                say("\ný��һ����ס����ܹ���һ��С���ӣ���ӭ��¥��ϲ�綩���𣿿�ȥ����\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 4:
                say(YEL"\n�Ǳߵ��˽е��������û��������������������������\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 5:
             say("\n�Ǳ��ֽ���������ý�ţ�����Ǯ���ͻ����İɣ��������ˣ���ý�ŸϽ��ܹ�ȥ��\n\n");
                 call_out("wait_marry", 1, ob,me,obj);
                break;
        case 6:
             say(CYN"\ný��һ·С�ܹ��������������������ģ����ͷ��ͷ�У����죬������׼��ϲװ����\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 7:
                  say(WHT"\nһ�������ְ˽ŵ�̧���˼��Ŵ����ӣ��������Ϲ���һ������\n"HIR
"                               ��      ��\n"
"                            ����������������\n"
"                            ����������������\n"
"                             ������  ������\n"
"                             ������  ������\n"
"                              ����    ����\n"
"                            ����������������\n"
"                             ������  ������\n"
"                             ������  ������\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
           case 8:
             say(YEL"\n�������ֿ�ʼ���Ի������������������������ʶ����ʶ���ˣ��׷׹�����أ�����ϲ��ϲ����\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 9:
                    say("\n����С����Ц������һ�߲������Σ�һ�߻���ҧ�Ŷ��䣬��ʱ��͵�ۿ������ˡ�\n\n");
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 10:
                    say("\n��λ������Ů������һ�״���߹����۵ݸ����ɣ�һ����ߴ���ˮ���佻����������������������ﴩϲװ����\n\n");
                    m_cloth = new("/d/ruzhou/npc/obj/longpao");
                    w_cloth = new("/d/ruzhou/npc/obj/yunxiu");
                    //if( query("couple/couple_gender", me) == "����" )
                    if( query("gender", me) == "Ů��" )
                    {
                            m_cloth->move(me);
                            w_cloth->move(obj);
                    }
                    else
                    {
                            m_cloth->move(obj);
                            w_cloth->move(me);
                    }
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 11:
                message("vision", HIY "\ný�Ÿ�������һ��������׼�������𣿡�����Ӧ���������ˣ���\n"
                "ý�������ϳ��������������������������ֻ��񡭡�����\n"
                HIM"��ʱ���������������ڴ��������ɰ���ӵ���������ְ˽Ÿ����ɡ����ﻻ�����£�\n"
                        "׺ӵ�������������ȥ��\n"NOR, room);
                call_out("start_marry", 1, ob,me,obj);
                break;
   }
   return 1;
}

int start_marry(object ob,object me,object obj) //��ʼ����
{
        object moon,room;
        string msg;
        if(!(room = find_object("/d/city/yinyuan-tang")))
                room = load_object("/d/city/yinyuan-tang");
        moon=new("/d/ruzhou/npc/yuelao");
        moon->move(room);
        message("vision", "\n����һ�������Ц��һλ�����������ߣ��첽������У��ڳ���������Ů��������ݣ�\n"
           "����������үү�������ϰڰ��֣�Ц�Ǻǵؿ���"+me->name()+"��"+obj->name()+"�����ͷ����\n"
      "���ã��ã��ɲ�Ůò������֮�ϣ�����֮��ѽ����\n"
           HIY"\ný��һ���֣�ϲ���ָ���ֻ�������ϸ��������������ɡ�����ݡ���ء�������\n"NOR,room, moon);
        CHANNEL_D->do_channel(moon, "mudnews",
           sprintf("����%s��%sϲ����Ե�����ô���ʱ��ʼ��\n",me->name(),obj->name()));
        say("ý����С���ض���������˵������˳�����롮�� ��ء��� ���úͰ� �Է������֡�����\n");
        set_temp("pending/bai", 1, me);
        set_temp("pending/bai", 1, obj);
        return 1;
}

int do_back(object ob)//����
{
        delete_temp("wait_time", ob);
        delete_temp("marry", ob);//ȡ��һ���йؽ��Ĳ���
        delete("marry", ob);
        say("ý�����������ϣ���һŤһŤ����������ȥ��\n");
        ob->move("/d/city/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)//����
{
        object me,ob,obj;
        string act;

        me = this_player();
        ob = this_object();
        if (me->is_busy())
                return notify_fail("ý��˵�����������ڲ�����æ����æ����˵����\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("ý��˵������������ĸ������£���Ҷ��䣬����ȥ����ɻ�ɣ���\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("ý��˵����û����������˵�����\n");

        if( !living(this_object()) )
                return notify_fail("�㻹������취��ý�ž��Ѱɡ�\n");

        if( me->is_fighting() )
                return notify_fail("ý��˵�������ٺ٣����Ȼ������������������˵�ɣ���\n");

        if( !environment()||base_name(environment()) != ("/d/city/yinyuan-tang") )
                return notify_fail("ý��˵���������������ǵģ�������Ҫ����Ե�ò��е�ѽ����\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("ý��Ц�������������㷸ʲôɵѽ����\n");

        if( !objectp(obj=present(query("couple/couple_id", me),environment(me)) )
                 || !find_player(query("couple/couple_id", me)) )
        {
                message_vision("ý��ת��һ�������ȵ�˵��������ѽ����İ�����ôͻȻ���ˣ�������ô���У����ɢ̯�ɡ���\n"
                        "��һƬ��ϧ������ҷ׷��볡��ϲ���ϵĶ���Ҳ��һ�ն��ա�\n",me);
                call_out("do_back",1,ob);
                return 1;
        }
        if( arg==" ���"||arg==" ����"||arg==" "+(string)query("couple/couple_name", me) )
                return notify_fail("���ݡ������Ĵ�֮�����ð�ǿո�\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "���" )
                 || (query_temp("pending/bai", me) == 2 && arg != "����" )
                 || (query_temp("pending/bai", me) == 3 && arg != query("couple/couple_name", me)) )
                return notify_fail("ý��Ц���������Ұ�ʲôѽ��һ����أ����ݸ��ã�������İ��ˣ��ɱ��ٴ��ˣ���\n");

        if( query_temp("pending/act", obj) != arg )
        {
                if( query_temp("pending/bai", me) != 3 )
                {
                        tell_object(obj, MAG"��İ��������ź���� " + arg + " ��...\n" NOR);
                        write(MAG "���������ȴ�����İ���...\n" NOR);
                        set_temp("pending/act", arg, me);
                }
                else
                {
                        tell_object(obj, MAG"��İ��������ź��㻥�ݣ����������֣���...\n" NOR);
                        write(MAG "���������ȴ�����İ���...\n" NOR);
                        set_temp("pending/act", me->name(), me);
                }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
        {
                  message_vision("��һ�ݡ��졭�ء�����$N��$n�������������ӯӯ����......\n",me,obj);
                addn_temp("pending/bai", 1, me);
                addn_temp("pending/bai", 1, obj);
                return 1;
        }
        else if( query_temp("pending/bai", me) == 2 )
        {
                  message_vision("�����ݡ��ߡ��á�����$N��$n��վ��������һЦ���ֻ�������......\n",me,obj);
                addn_temp("pending/bai", 1, me);
                addn_temp("pending/bai", 1, obj);
                return 1;
        }
        else if( query_temp("pending/bai", me) == 3 )
        {
                  message_vision("�����ޡ��ԡ��ݡ�����$N��$n���໥�������һ��......\n",me,obj);
                message_vision(HIY "����Ц�Ǻǵ�˵�������ã�$N��$n��������ʽ��Ϊ����! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf( "��ϲ%s��%s��һ�����ϲ����Ե��\n        ��λ������ѣ���Я����������¥�μ����ǵĻ��磡\n", me->name(), obj->name()));

                addn("couple/married", 1, me);//������
                set("couple/have_couple", 1, me);//�����ѻ�״̬
                set_temp("married_party", 1, me);//���ϼǺţ�ϲ�����ϰ忴���ͻ�ͬ�⿪��ϯ
                set_temp("married_party", 1, obj);//���˶�������ֻ�����Բ�����
                addn("couple/married", 1, obj);//������
                set("couple/have_couple", 1, obj);//�ѻ�״̬

                delete_temp("pending/bai", me);
                delete_temp("pending/bai", obj);
                delete_temp("pending/act", me);
                delete_temp("pending/act", obj);
                delete_temp("pending/pro", me);
                delete_temp("pending/pro", obj);
             delete_temp("ask_money", me);
                delete_temp("ask_money", obj);
                call_out("do_right",1,me,obj);
                call_out("last_marry",1,ob,me,obj);
                return 1;
        }
}

int do_right(object me, object ob)
{
        string fn;
        string fc;
        object ring;

        message("visoin", name() + "Ц�ŶԶ���˵���������������"
                "��ϲ�����ӣ���û��ʲô���ֻ���͸���"
                "���������һ�Խ���ָ�ɣ���\n\n", environment(me));

        fc = read_file(MARRY_RING);
        fc = replace_string(fc, "LONG_DESCRIPTION",
                            "����" + me->name(1) + "��" +
                            ob->name(1) + "�Ľ���ָ�������˵Ķ���֮�\n");

        // give ring to me
        fn=RING_DIR+query("id", me);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        ring = load_object(fn);
        ring->move(me, 1);
        tell_object(me, HIY "������һ������ָ��\n" NOR);
        set("can_summon/"+"wedding ring", fn, me);

        // give ring to ob
        fn=RING_DIR+query("id", ob);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        ring = load_object(fn);
        ring->move(ob, 1);
        tell_object(ob, HIY "������һ������ָ��\n" NOR);
        set("can_summon/"+"wedding ring", fn, ob);

        // record
        set("couple/witness", name(), me);
        me->save();
        set("couple/witness", name(), ob);
        ob->save();
        return 1;
}
int last_marry(object ob,object me,object obj)//���ý���
{
        object moon,room;
        if(!(room = find_object("/d/city/yinyuan-tang")))
                room = load_object("/d/city/yinyuan-tang");
        moon = present("yue lao", room);
        if( objectp(moon) )
        destruct(moon);
        delete_temp("wait_time", ob);
        ob = this_object();
        delete_temp("marry/money", ob);
        say("ý�ź��������η򣡿콫�����͵�ӭ��¥���л��磬�Һ����ϾͲ�ȥ�ˣ��Ǻǣ���\n˵��һŤһŤ����������ȥ��\n");
        write_file("/log/static/MARRY",sprintf("%s(%s)and%s(%s)marriedin%s��\n",query("name", me),query("id", me),
                query("name", obj),query("id", obj),ctime(time())));
        delete("have_couple", ob);
        delete_temp("marry", ob);
        delete("marry", ob);
        ob->move("/d/city/hongniang-zhuang");
        message_vision(HIR"���ɰ���ӵ����λ���ˣ������ſڵ�������컨�Σ�ֻ���η���һ������Σ���\n"
                   "һ���˴������ر���ӭ��¥......\n"NOR,me,obj);
        me->move("/d/ruzhou/jiao1");
        obj->move("/d/ruzhou/jiao2");
        call_out("go_lou",8,me,obj);
        return 1;
}

int go_lou(object me,object obj)
{
        object npc;
        message_vision("\n    ���˺ó�һ�����ֻ���η���һ����������������������һ�������䵽�˵��ϣ�\n"
           "$N��$n�ӽ���������һ����ԭ���Ѿ�����ӭ��¥�������ֱ�ӵ����һֱ���˶�¥�����á�\n"
      "ֻ��һ��Ǻ�Ц����ӭ��¥�ϰ�ϲ����Ц�������ӭ����������ϲ��λ���ˣ���ϲ��ϲ����\n",me,obj);
        npc=new("/d/ruzhou/npc/xi-laifu");
        set("name1", me->name(), npc);
        set("name2", obj->name(), npc);//˫������
        npc->move("/d/city/zxlpath");
        me->move("/d/city/zxlpath");
        obj->move("/d/city/zxlpath");
        return 1;
}

/*
int return_home(object home)//���Ǳ�׼�̳��еĸú�������ֹ�����и��£�ý�Żؼ�
{
    if( !environment()||  environment()==home ) return 1;
        if( !living(this_object()) ||  is_fighting()) return 0;
        if( query("marry", this_object()))return 0;//�н��Ĳ����Ͳ���ȥ

    message("vision", this_object()->name() + "����ææ���뿪�ˡ�\n",
            environment(), this_object());
    return move(home);
}
*/
