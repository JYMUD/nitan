// snake_room.h �߹������ߵķ���

void python_attack(object);

#include <ansi.h>

void init()
{
        object me, here;

        string *msg =
        ({
                HIR"���ߵ����ͻȻ�����й��ȳ�����ζ����\n"NOR,
                HIR"���������һ��uɳɳ�v��ϸ�����죬��������˾�����\n"NOR,
                HIR"��һ�ߵ���ط���ͻȻ�е�����������\n"NOR,
        });

        me = this_player();
        here = this_object();

        set("enter_shegu", 1, me);
        addn("jingli", -5, me);

        if( time()-query("last_comeout", here)>180 || !query("last_search", here) )
                set("hide_python", 1, here);


        if( random(query("hide_python")+1) != 0 && query("race", me) != "����"){
                remove_call_out("python_attack");
                call_out("python_attack", 6+random(3), me);
                if( query("family/family_name", me) == "����ɽ" )
                tell_object(me, msg[random(sizeof(msg))]);
        }
}

void python_attack(object me)
{
        object python, here;
        here = this_object();

    if (! objectp(me))
        return;

        if ( environment(me) != here) return;

        if ( query("hide_python") < 1) return;

        addn("hide_python", -1);
        python = new(__DIR__"npc/bt_python");
        python->move(here);
        set("last_comeout", time() );

        message("vision", HIR"���Ȼ�ŵ�һ���ȷ磬�ͼ�һ��"+python->name()+HIR"���˳�����¶�����������"+me->name()+"ҧȥ��\n"NOR, environment(me), me);
        tell_object(me, HIR"����к���˻˻���죬һ���ɼ䣬����ȳ�ӭ�棬һ��"+python->name()+HIR"���Դܳ�����Ȼ�����ſ�������\n"NOR);

        python->kill_ob(me);

}
