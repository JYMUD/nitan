//Cracked by Kafei
//music.h ����
#include <ansi.h>

int do_lianxi(string arg)
{
        string msg;
        object ob, me, where, weapon;
        int cost;

        string* zither_msg = ({
        "��ָ","��","����","����","����","���","��ע",
        "������","�","����","��ָ","��Բ","Ĩ��","����",
        });

        string* flute_msg = ({
        "��ָ", "����", "����","������", "��ָ����",
        });

        me = this_player();
        where = environment(me);
        weapon=query_temp("weapon", me);
        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( query("sleep_room", where) )
                return notify_fail("��˯���ﲻ����ϰ�������������Ӱ�����ˡ�\n");

        if( query("no_fight", where) )
                return notify_fail("���ﲻ�ʺ���ϰ����������\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if( me->is_fighting() )
                return notify_fail("���޷���ս����ר��������ϰ���࣡\n");

        if(!arg || !objectp(ob = present(arg, me)) )
                return notify_fail("��Ҫ��ϰ����ʲô��\n");

        if( !query("shape", ob) || 
        (query("shape", ob) != "flute" && query("shape", ob) != "zither") )
                return notify_fail("�㲻����ϰ����"+ob->name()+"��\n");

        if( ob != weapon )
                return notify_fail("�������װ��"+ob->name()+"��\n");

        if( (int)me->query_skill("music", 1) < 10 ) {
                if( query("shape", ob) == "zither" )
                message_vision("$N�ָ�$n�����˼��£����ɵ�������������\n"NOR, me, ob);
                if( query("shape", ob) == "flute" )
                message_vision("$N��$n���ڴ���һ�����������һ��������ȫ�����졣\n"NOR, me, ob);
                return 1;
        }

        if( query("potential", me)<1 )
                return notify_fail("���Ǳ���ѴＫ�ޣ�û�а취��������������\n");


        cost=50+random(40)*(40-query("int", me))/20;
        if (cost < 10) cost = 10; // minimum cost

        if( query("jing", me)>cost){
                if( query("shape", ob) == "zither"){
                msg = zither_msg[random(sizeof(zither_msg))] ;
                message_vision("$N�ָ�$n��������ϰ����"+msg+"���ļ��ɡ�\n"NOR, me, ob);
                if( query("family/family_name", me) == "�һ���" && me->query_skill("music",1)<333 )
                me->improve_skill("music", me->query_int()*2 + 1);
                }
                else if( query("shape", ob) == "flute"){
                msg = flute_msg[random(sizeof(flute_msg))] ;
                message_vision("$N�ְ�$n�����촵�࣬ר����ϰ����"+msg+"���ļ��ɡ�\n"NOR, me, ob);
                if( query("family/family_name", me) == "�һ���" && me->query_skill("music",1)<333 )
                me->improve_skill("music", me->query_int()*2 + 1);

                }
                else return notify_fail("���󿴿����ҿ�����ʵ�ڲ�֪������������"+ob->name()+"��\n");
                }
        else {
                cost=query("jing", me);
                if (cost < 0) cost = 0;
                write("�����ڹ���ƣ�룬�޷�ר��������ϰ����������\n");
                return 1;
        }

        me->receive_damage("jing", cost/2, "�����ʴ�����");
        addn("jingli", -cost/4, me);
        if( random(3) == 0)addn("potential", -random(2), me);
        return 1;
}