// ride.c

#include <ansi.h>

#define MEMBER_D        "/adm/daemons/memberd"

void create() { seteuid(getuid()); }

int no_clean_up() { return 1; }

int main(object me, string arg)
{
        object ob, env;

	if (! arg)
                return notify_fail("ָ���ʽ�� lured <�ն�> \n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

	if( !query("lure", ob) )
		return notify_fail("�ⶫ���������ն��ɣ�\n");

	if (me->is_busy())
		return notify_fail("����æ������˵�ɣ�\n");

	if( query_temp("hunting", me) )
		return notify_fail("���ż����ٵȵȣ�\n");

	message_vision(HIG "$N��" + ob->name() + "���ڵ��ϣ�����һ�Ծ����غ��� ����\n" NOR, me);

	me->start_busy(3 + random(5));
set_temp("hunting", 1, 	me);

	env = environment(me);

        call_out("do_hunt", 5 + random(5), me, env, ob);

	return 1;
}

void do_hunt(object me, object env, object ob)
{
	object obq;
	string* temp;
	string str;
	mapping quarry;
	int i, point;

	if (! objectp(me))return;
	if (! objectp(env))return;
	if (! objectp(ob))return;

	if( !query("can_hunting", env) )
		return;

	quarry=query("quarry", env);
	temp = keys(quarry);
	i = random(sizeof(temp));

delete_temp("hunting", 	me);

        // ��ü����ж��Ƿ������
	point = quarry[temp[i]];
	if( MEMBER_D->is_valid_member(query("id", me)) )
		point += 3;

	if( query("level", ob)>1 )
		point=query("level", ob);

        if (random(100) >= point)
	{
		if (base_name(environment(me)) == base_name(env))
		{
			write(HIY "���˰���ȴ����������֣���ֻ�ð�" + ob->name() + HIY "����������\n");
		}
		else
		{
			destruct(ob);
		}
		return;
	}	
	
	obq = new("/clone/quarry/" + temp[i]);
	obq->move(env);
set("owner",query("id",  me), 	obq);
        set("name", HIR+me->name()+"("+query("id", me)+")�Գ���"+obq->name()+NOR, obq);
  
	if (environment(me) == env)
	{
		switch(random(4))
		{
			case 0:
			message_vision(HIG "��һ�����һֻ" + obq->name() + HIG "���˳�������" + 
                                       ob->name() + HIG "һ��ҧ�����\n" NOR, me);
			break;

			case 1:
			message_vision(HIM "ת�ۼ䣬һֻ" + obq->name() + HIG "ͻȻ���֣���" + 
                                       ob->name() + HIG "�̽����\n" NOR, me);
			break;

			case 2:
			message_vision(HIW "���ã�һֻ" + obq->name() + HIG "��ҡ��ڵ����˳�������ϸ�ش�����" + 
                                       ob->name() + HIG "��\n" NOR, me);
			break;

			default:
			message_vision(HIC "��ʱ��һֻ" + obq->name() + HIG "���˹�����һ�ڽ�" + 
                                       ob->name() + HIG "���������ϣ���ò̰��֮����\n" NOR, me);
			break;
		}
	}
	destruct(ob);
	return;
	
}


int help(object me)
{
	write(@HELP
ָ���ʽ :

        lured <�ն�>���ڵ�ǰ�ص�����ն��ȴ�������֡�
                     ע��һ��ֻ�ܷ�һ���ն���
                     
HELP
    );
    return 1;
}
