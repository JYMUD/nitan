// YangXiao.h

#include <ansi.h>

string* names = ({
        "zhuang zheng",
        "wen cangsong",
        "tang yang",
        "xin ran",
        "yan yuan",
        "xie xun",
        "wei yixiao",
});

string ask_me()
{
        mapping fam, my_fam, skl;
        object fighter, me, room, monk;
        string *sname;
        int i,j;

        fighter = this_player();
        me = this_object();
        my_fam=query("family", me);

        skl = fighter->query_skills();
        if (sizeof(skl) <= 1)
                return RANK_D->query_respect(fighter) +
                "���������������ʸ񴳹���ʥ����";
        sname  = keys(skl);
        for(i=0; i<sizeof(skl); i++) {
                if (skl[sname[i]] < 80)
                return RANK_D->query_respect(fighter) +
                "���������������ʸ񴳹���ʥ����";
        }

        if( query("guangming_winner", fighter) )
                return RANK_D->query_respect(fighter) +
                "��Ȼ��������ʥ���󣬿ɲ�Ҫ�����п������Ц��";

        if( query("guilty", fighter)>0 )
                return RANK_D->query_respect(fighter) +
                "���۷����䣬�������������׼���㴳����ʥ����";

        if( query("assigned_fighter", me) )
                return RANK_D->query_respect(fighter) +
                "��������������ս����ʥ�������һ��ʱ�������ɡ�";

        set_temp("yangxiao-asked", 1, fighter);

        say("\n����˵�����ðɣ����ټ�лΤ������������ʹ�ڶ����ϣ����Ժ�ǰ
�����ҡ�\n");

        set("assigned_fighter",query("id",  fighter), me);

        if( !query_temp("fanyao-asked", fighter) )
        say("\n�����ֵ���������ȥ��֪����ʹ�����������м�������������ɢ������
���ϡ�\n");

        message_vision("\n���������뿪��\n\n", fighter);

// 1.
        if(!( room = find_object("/d/mingjiao/rjqdating")) )
        room = load_object("/d/mingjiao/rjqdating");
        me->move(room);
        if( !objectp(monk = present(names[0], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ�������ʹ�����˲��ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 2.
        if(!( room = find_object("/d/mingjiao/jmqdating")) )
        room = load_object("/d/mingjiao/jmqdating");
        me->move(room);
        if( !objectp(monk = present(names[1], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ�������ʹ�����˲��ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 3.
        if(!( room = find_object("/d/mingjiao/hsqdating")) )
        room = load_object("/d/mingjiao/hsqdating");
        me->move(room);
        if( !objectp(monk = present(names[2], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ�������ʹ�����˲��ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 4.
        if(!( room = find_object("/d/mingjiao/lhqdating")) )
        room = load_object("/d/mingjiao/lhqdating");
        me->move(room);
        if( !objectp(monk = present(names[3], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ�������ʹ�����˲��ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 5.
        if(!( room = find_object("/d/mingjiao/htqdating")) )
        room = load_object("/d/mingjiao/htqdating");
        me->move(room);
        if( !objectp(monk = present(names[4], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ�������ʹ�����˲��ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 6.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[5], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ���л�������ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);
// 7.
        if(!( room = find_object("/d/mingjiao/dadian")) )
        room = load_object("/d/mingjiao/dadian");
        me->move(room);
        if( !objectp(monk = present(names[6], room) ))
        {
                 me->move("/d/mingjiao/dadian");
                message_vision("\n�������˹�����\n\n", fighter);
                return "���ǶԲ���Τ�������ڣ��޷����й���ʥ����\n";
        }
        message("vision","\n�������˹�������"+query("name", monk)+"��������˵�˼��䡣\n",room,monk);
        monk->move("/d/mingjiao/eastdian");
        message("vision",query("name", monk)+"���˵�ͷ���첽���˳�ȥ��\n",room,monk);

        me->move("/d/mingjiao/qiandian");
        call_out("waiting", 1, me);
        return "�ã���Ҷ������ˡ�\n";
}

int waiting(object me)
{
        object fighter;
        int wait_time;

        if( wait_time == 300 )
        {
                say( "����˵�����������������ˣ����ǻ�ȥ�գ�\n\n");
                call_out("do_back", 0, me);
        }

        if( !objectp(fighter=present(query("assigned_fighter", me),environment(me))) )
        {
                wait_time++;
                call_out("waiting", 1, me);
        }
        else if( !present("fanyao",environment(me)) || !query_temp("fanyao-asked", fighter) )
        {
                if( random(10) == 0 )
                say("\n����˵����" + RANK_D->query_respect(fighter) + "ȥ���˷���ʹû�У� ���������ڸõ��˰գ�\n");

                wait_time++;
                call_out("waiting", 1, me);
        }
        else         call_out("preparing", 1, me, fighter);

        return 1;
}

int preparing(object me, object fighter)
{
        object monk, room, ob;

        if(!( room = find_object("/d/mingjiao/qiandian")) )
        room = load_object("/d/mingjiao/qiandian");

        message("vision", HIY "\n���д���������������ʥ�����Χ��\n" NOR, room);
        message("vision", "\nֻ����������ɳɳ�ĽŲ�������������ɢ������ʹ�Ǹ���������ɱ��\n"
                "����ֿ�ȭ�����ֱֳ�����������Χ����������ס��ͨ·��\n\n", room);
        delete("exits", room);

        say( "�����ֵ���׼��������ʥ���󼴿̷�����\n\n");

        delete_temp("yangxiao-asked", fighter);
        delete_temp("beat_count", fighter);
        set_temp("fighting", 1, fighter);

        call_out("fighting", 10, me, fighter, 0);
        return 1;
}

int fighting(object me, object fighter, int count)
{
        object monk1, monk2, room1, room2;

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        if(!( room2 = find_object("/d/mingjiao/qiandian")) )
        room2 = load_object("/d/mingjiao/qiandian");

        if( count <= 6 )
        {
                message("vision", "\n����ʥ�����ٵ���ת�ţ�һ���������ս���\n" NOR, room2);
                monk1 = present(names[count], room1);
                if (monk1) monk1->move(room2);
        }

        if( count >= 1 && count <= 7 ) {
                monk2 = present(names[count-1], room2);
                if (monk2) monk2->move(room1);
        }

        if( !find_player(query("assigned_fighter", me)) || 
        !living(fighter) || query("qi", fighter) <= 1 )
        {
                if( objectp(present(query("assigned_fighter", me),environment(me)))){
                        delete_temp("fighting", fighter);
                        delete_temp("beat_count", fighter);
                }
                monk1->move(room1);

                say( "����ҡ��ҡͷ��˵�����벻�� ... ����\n\n");
                command("sigh");
                call_out("do_back", 5, me );
        }
        else if( count >= 7 )
        {
                if( query_temp("beat_count", fighter) >= 14 )
                        call_out("do_recruit", 5, me, fighter);
                else
                        call_out("do_back", 5, me );
        }
        else
        {
                count++;
                call_out("fighting", 2, me, fighter, count);
        }

        return 1;
}

int do_recruit(object me, object fighter)
{
        mapping ft_fam, my_fam;

        delete_temp("beat_count", fighter);
        delete_temp("fighting", fighter);
        addn("combat_exp", 10000, fighter);
        set("guangming_winner", 1, fighter);

        if( !(ft_fam=query("family", fighter)) || ft_fam["family_name"] != "����" )
        {
                command("bow");
                say("����˵����" + RANK_D->query_respect(fighter) + "�˷����󣬵��Ա������д������棬�ٳ߸�ͷ������һ�������оʹ˱����\n");
                call_out("do_back", 5, me );
        }
        else
        {
                say("\n����˵������ϲ�㴳���˹���ʥ���󣡱����д˵Ƚܳ����ӣ���ʱ�ص�Ϊ���ַ�һ��ʣ�\n");
                call_out("do_back", 5, me );
        }
        return 1;
}

int do_back(object me)
{
        object monk, room1, room2;
        int i;

        message("vision", "\n���л��˻��֣� ����ʹ�Ͷ������漴����뿪ǰ�\n", environment(me) );

        if(!( room1 = find_object("/d/mingjiao/eastdian")) )
        room1 = load_object("/d/mingjiao/eastdian");

        for(i = 1; i <= 7; i ++)
        {
                switch (i)
                {
                case 1:
                        if(!( room2 = find_object("/d/mingjiao/rjqdating")) )
                        room2 = load_object("/d/mingjiao/rjqdating");
                        break;
                case 2:
                        if(!( room2 = find_object("/d/mingjiao/jmqdating")) )
                        room2 = load_object("/d/mingjiao/jmqdating");
                        break;
                case 3:
                        if(!( room2 = find_object("/d/mingjiao/hsqdating")) )
                        room2 = load_object("/d/mingjiao/hsqdating");
                        break;
                case 4:
                        if(!( room2 = find_object("/d/mingjiao/lhqdating")) )
                        room2 = load_object("/d/mingjiao/lhqdating");
                        break;
                case 5:
                        if(!( room2 = find_object("/d/mingjiao/htqdating")) )
                        room2 = load_object("/d/mingjiao/htqdating");
                        break;
                case 6:
                case 7:
                        if(!( room2 = find_object("/d/mingjiao/dadian")) )
                        room2 = load_object("/d/mingjiao/dadian");
                        break;
                }
                if( objectp( monk = present(names[i-1], room1) ));
                monk->move(room2);
        }

        delete("assigned_fighter", me);
        me->move("/d/mingjiao/dadian");

        return 1;
}

#include "shizhe.h"
