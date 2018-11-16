// huaiyun.c
// updated by linux
// updated by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int birth1(object me);
int birth2(object me);
int birth3(object me);

int update_condition(object me, int duration)
{
        if (duration < 1) return 0; 

        if (duration == 1200)
        {
                tell_object(me, HIY "�������Χ���˺�����͵͵���㣬����ò����ڣ�\n" NOR);
                message("vision", me->name() + HIY "��ɬ�ĵ���ͷ����Ū���Լ����½ǡ�\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 800)
        {
                tell_object(me, HIY "�������Χ���˶�����֣�����ָָ��㣬�������ᣡ\n" NOR);
                message("vision", me->name() + HIY "�����㣬������Ƿ����ʲô�Ƶġ���\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 400)
        {
                tell_object(me, HIY "�������Χ���˶���Ц�����Ŀ����㣬���������Ѿ����������㡭����\n" NOR);
                message("vision", me->name() + HIY "��һ���쳣�����Ŀ�⣬�����������Լ��Ķ��ӡ�\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 200)
        {
                tell_object(me, HIY "�������Χ���������綼����������ã������ޱȵ��泩��\n" NOR);
                message("vision", me->name() + HIY "һ������˰������Ϣ���ǻ�����ĸ����Ŀ�ⲻʱɨ������Χ��\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 20 || duration == 10)
        {
                tell_object(me, HIY "�������Χ���˶����ż�����е�Ŀ��ע�����㣬�ѵ��ǡ������ˣ�\n" NOR);
                message("vision", me->name() + HIY "�Ѿ��ж�ʮ�ֵĳٻ��ˣ���ʱ��ͣ����������\n" NOR,
                        environment(me), me);
        } else 
        if (duration == 1)
        {
                tell_object(me, HIY "��Χ���˶����ȵĺϲ�������ͣ�һ���Ǽ�����ʲô������飡\n"
                                "�����������Ͼ�Ҫ���ˣ���Ͻ��ͺ��ӵĸ���ȥ����ҩ�̵Ķ�¥�����������������Σ�յģ�\n" NOR);
                message("vision", me->name() + HIY "���Ŵ��Ķ��ӣ������˵��ϣ�����һ������ʹ������飡\n" NOR,
                        environment(me), me);
                remove_call_out("birth1");
                call_out("birth1", 100, me);
        }
        me->apply_condition("huaiyun", duration - 1);
        return 1;
}

int birth1(object me)
{
        object target;        
        
        if( (query("age", me))<18 )
        {
                message_vision(HIY "\n$N�ƺ����ø���һ���ʹ�����һ��������$N����̫С�����ʺ�������\n����$N�ĺ��������ˣ��ÿ�������\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        } 
        
        if (base_name(environment(me)) != "/d/city/chanfang")
        {
                message_vision(HIY "\n$N�ƺ����ø���һ���ʹ�����һ������������Ļ���ʵ����̫�����ˣ�\n����$N�ĺ��������ˣ��ÿ�������\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N�ƺ����ø���һ���ʹ�����һ�������ڹؼ�ʱ���������û���غ�����ߣ�\n����$N�ĺ��������ˣ��ÿ�������\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }
        
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                
        message_vision(HIY "\n$N��������һ��������Ͻ���ס$n���֣�����˵����Ҫ����! \n" NOR, me, target);
        remove_call_out("birth2");
        call_out("birth2", 15, me);
      
        return 1;
}

int birth2(object me)
{        
        object target;
         
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N�ƺ����ø���һ���ʹ�����һ�������ڹؼ�ʱ���������û���غ�����ߣ�\n����$N�ĺ��������ˣ��ÿ�������\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
              
        if (! me->is_busy())
                me->start_busy(15);
        if (! target->id_busy())
                target->start_busy(15);
                        
        message_vision(HIY "\n$N���Ǵ����죬һֱ���ں������أ�˫�ֽ�����ס$n���ֲ��š�\n\nӤ���Ѿ�̽����ͷ������\n" NOR, me, target);
        remove_call_out("birth3");
        call_out("birth3", 15, me);
        return 1;
}

int birth3(object me)
{
        object target;
        object baby;
        
        target=find_player(query("couple/couple_id", me));
        if (! target || environment(target) != environment(me))
        {
                message_vision(HIY "\n$N�ƺ����ø���һ���ʹ�����һ�������ڹؼ�ʱ���������û���غ�����ߣ�\n����$N�ĺ��������ˣ��ÿ�������\n" NOR, me);
                set("qi", 1, me);
                set("jing", 1, me);
                set("neili",query("neili",  me)/2, me);
                set("long",query("longbak",  me), me);
                delete("longbak", me);
                me->unconcious();
                return 1;
        }  
                
        message_vision(HIY "\n���ۡ���������Ӥ�������ˣ�\n" +
                "\n$N��ɫ�԰ף�б���ڴ�ͷ���������������¶��һ˿΢Ц��\n" NOR, me, target);
        set("long", "\n���������Ѿ���һ��������ٸ���Ŷ��\n"NOR, me);
        delete("longbak", me);

        set("neili", 0, me);
        set("qi", 1, me);
        set("jing", 1, me);
        
        baby = new("/clone/user/baby");
        if (random(2) > 0)
        {
                set("gender", "����", baby);
                baby->set_name("С"+query("name", target),
                               ({"xiao_"+query("id", target),"baby"}));
                               
                set("long", "����"+query("name", target)+"��"+query("name", me)+"�ĺ��ӡ����ĺ���"+query("name", target)+"����\n", baby);
                message("shout",HIR"������ϲ�¡�"HIM"��ϲ"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"��"HIR+query("name", target)+"("+query("id", target)+")"HIM"����һ������С�ӡ�\n"NOR,
                        users());
        } else
        {
                set("gender", "Ů��", baby);
                baby->set_name("С"+query("name", me),
                               ({"xiao_"+query("id", me),"baby"}));
                               
                set("long", "����"+query("name", target)+"��"+query("name", me)+"�ĺ��ӡ����ĺ���"+query("name", me)+"����\n", baby);
                message("shout",HIR"������ϲ�¡�"HIM"��ϲ"HIR+query("name", me)+"("+query("id", me)+")"
                        HIM"��"HIR+query("name", target)+"("+query("id", target)+")"HIM"����һ��ǧ��С������\n"NOR,
                        users());                
        }
        
        set("per", (query("per", me)+query("per", target))/2, baby);
        set("kar", (query("kar", me)+query("kar", target))/2, baby);
        set("int", (query("int", me)+query("int", target))/2, baby);
        set("str", (query("str", me)+query("str", target))/2, baby);
        set("con", (query("con", me)+query("con", target))/2, baby);
        set("dex", (query("dex", me)+query("dex", target))/2, baby);
        set("parents/father",query("id",  target), baby);
        set("parents/mother",query("id",  me), baby);
        baby->save();
        
        set("couple/child_id",query("id",  baby), me);
        set("couple/child_name",query("name",  baby), me);
        set("couple/child_id",query("id",  baby), target);
        set("couple/child_name",query("name",  baby), target);
        me->save();
        target->save();
        
        if (! baby->move(environment(me)))
                baby->move(environment(environment(me)));
                
        return 1;
}
