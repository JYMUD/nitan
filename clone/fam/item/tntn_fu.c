#include <ansi.h>

inherit ITEM;

int do_use(string arg);

void create()
{
        set_name(NOR + YEL "ͯ��ͯŮ��" NOR, ({"tntn fu", "fu"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "����һ�ŵ��������滭������С�ޣ�һ����һ��Ů����̬ʮ�ֱ��档\n"
                                      "*���߾����ӳ��˷���reng fu���������߾���\n\n" NOR);
                set("unit", "��");
                set("value", 8000);
        }
}

int query_autoload()
{
        return 1;
}


void init()
{
        add_action("do_use", "reng");       
}

int do_use(string arg)
{
        object me, ob;
        
        me = this_player();
        
        if(! objectp(present("tntn fu", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
                 
        ob = environment(me);
        
        if (base_name(ob) != "/d/shenlong/shejingdong")
                return notify_fail("�˷�ֻ�����߾���ʹ�á�\n");

        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                        return notify_fail("�߾��Ѿ������ˣ�����Ҫ��ʹ�÷���\n");
        }

        // �����峡������
        ob = environment(me);
        if( query("doing", ob) )
        {
                return notify_fail("�����ս���꣬�����峡���㻹�ǵ��´ΰɣ�\n");
        }
        
        // ʹ������
        message_sort(HIY + "\n$N" HIY "�ӳ�ͯ��ͯŮ������Ȼ�䣬�ض�ɽҡ��Զ�������~~�"
                     "�����ƺ����߾��ڳ�����ƶ���һʱ�䣬������������ ����\n" NOR, me);

        me->start_busy(5);
        
        // �ٻ�����ͷ�߾�
        remove_call_out("summon_shejing");
        call_out("summon_shejing", 5, me);



        return 1;
}

void summon_shejing(object me)
{
        object ob;
        
        ob = find_living("jiutou shejing");
        
        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
                {
                        write("�߾��Ѿ������ˣ�����Ҫ��ʹ�÷�����Ͻ���������\n");
                        return;                        
                }
        }        

        ob = new("/d/shenlong/npc/shejing");
        
        message_sort(HIR + "\n��Ȼ�䣬һ���������ǵĽ��������˼ž���ֻ��һֻ�޴�Ķ��߳�����"
                           "�߾����ڣ������ѻ������Σ������ɾ����о�ͷ����״���ǿ��¡�\n" NOR, me);
        
        ob->move("/d/shenlong/shejingdong");
        set("life_time", time(), ob);
        
        // �ݻٷ�
        destruct(this_object());
        
        return;        
}
