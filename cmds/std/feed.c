// Filename : /cmds/std/feed.c
// Last Modified by winder on Aug. 5 2001

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, pet;
        string owner, food, ob;
        int i, j, lvl, effect;

        seteuid(getuid());

        if(!arg || sscanf(arg, "%s to %s", food, ob) !=2)
                return notify_fail("��Ҫιʲô������˭��\n");
        if(!objectp(obj = present(food, me)) ) 
                return notify_fail("������û��������������\n");
        if(!objectp(pet = present(ob, environment(me))) || !living(pet))
                return notify_fail("����û�������Ķ��\n");
        if( query("race", pet) == "����" )
                return notify_fail(pet->name()+"�ǳ���ô���ɴ��۾�������\n");
        if(pet->is_busy() )
                return notify_fail(pet->name()+"��æ���أ��ĳԵ���ʲô��\n");
        if(pet->is_busy() )
                return notify_fail(pet->name()+"��æ���أ��ĳԵ���ʲô��\n");
        if(me->is_busy() )
                return notify_fail("����æ���أ�ʲôҲ�����ˣ�\n");
        if(pet->is_fighting() )
                return notify_fail("�����ڴ���أ����ѵ�û��������\n");
        if(me->is_fighting() )
                return notify_fail("һ�ߴ��һ��ιʳ�������ǻ����ˣ�\n");
        if( !wizardp(me) && query_temp("feeded", pet) )
                return notify_fail("��һ�β��ܶ�Զ������Զ��˻������ӣ�"+query("name", pet)+"Ҳһ����\n");
        if( query("id", me) != query_temp("owner", pet) )
                return notify_fail("�㿴��"+query("name", pet)+"��ǰ�������£����һ���߿��ˡ�\n");
        if( !query("siliao_supply", obj) )
                return notify_fail("�ƺ�"+query("name", pet)+"������������Ȥ����\n");
        if( !query("siliao_remaining", obj) )
                return notify_fail( obj->name() + "�Ѿ�ûʲô�óԵ��ˡ�\n");
        if( query("food", pet) >= pet->max_food_capacity() )
                return notify_fail(pet->name()+"�Ѿ���̫���ˣ���Ҳ�������κζ����ˡ�\n");
        set("value", 0, obj);
        addn("siliao_remaining", -1, obj);
        me->start_busy(1);
// ����ʳ��״̬�ı䡣
        addn("food",query("siliao_supply",  obj), pet);
// ��ʱ��ʳ�����������ԡ��ճ���Ҳ�����ó����˳�������������ι76��ﵽ100����
// 9����Դﵽ50����
        set_temp("feeded", "1", pet);
        call_out("del", 20, pet);
// ������������ѱ���޹ء�
        if( query("owner", pet) == query("id", me) )
        {
// ʳ�����øı䣬�ۼ��Ա�������
                if( query("siliao_effect", obj) )
                        addn("feed",query("siliao_effect",  obj), pet);
// ι�������顣
                addn("combat_exp", 5+random(10), pet);
                i=query("feed", pet);
                j=query("level", pet);
                if(i>=2+j*j)
                {
                        tell_object(me,HIY"��ι����һ��ʳ��󣬷���"+query("name", pet)+"�ƺ��Եø�ǿ����Ҳ�������ˣ�\n"NOR);
// ι��������
                        addn("level", 1, pet);
                        set("feed", 0, pet);
// ι����ѱ���ȡ�
                        addn("obe", 1, pet);
                        lvl=query("level", pet);
                }
                addn("max_qi", lvl, pet);
                addn("max_jing", lvl, pet);
        }
        if( !query("siliao_remaining", obj) )
        {
                delete_temp("apply/long", obj);
                if( query("finish_msg", obj) )
                        message_vision(query("finish_msg", obj),pet,obj);
                else
                {
                        message_vision("$N�ó�һ"+query("unit", obj)+query("name", obj)+"������$n�������֡�\n$n��ѱ˳�����˹�ȥ��һ�ѵ�����"+query("name", obj)+"�����˸��ɸɾ�����\n",me,pet);
                }
                if( !obj->finish_eat() ) destruct(obj);
        } 
        else
        {
                if( query("eat_msg", obj) )
                        message_vision(query("eat_msg", obj),pet,obj);
                else 
                        message_vision("$N�ó�һ"+query("unit", obj)+query("name", obj)+"������$n�������֡�\n$n��ѱ˳�����˹�ȥ��һ�ѵ�����"+query("name", obj)+"���ݺݾ���һ�ڡ�\n",me,pet);
        }
        if( !obj ) return 1;
        
        return 1;
}

void del(object pet)
{
        delete_temp("feeded", pet);
}

int help(object me)
{
        write(@HELP
ָ���ʽ : feed <����> to <������>

    ��ָ�������ι������ѱ���Ķ��

    �����Ѿ�ѱ���Ķ�����Խ�������ָ�

����ָ�
        come <������>:                  �ö�����������ж���
        stay:                           ֹͣ����ĸ���״̬��
        attack <ĳ��>:                  �ö��﹥�����ˡ�
        stop <������>:                  �ö���ֹͣ���˵Ĺ�����
        release:                        ������ū״̬����������롣

����ָ���ֻ��ĳЩ�������ã�
        ride <������>:                  ���������������ȡ�
        unride <������>:                �£��뿪���
        feed <����> to <������>:        �涯��ιʳ��
        imbibe <������>:                ��������ˮ��

HELP
        );
        return 1;
}
