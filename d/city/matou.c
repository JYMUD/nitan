// This program is a part of NT MudLIB

#include <ansi.h>;
#define MAX_EXP 200000
#define MIN_EXP 50000
inherit ROOM;
string look_sign();
int do_go(string);
mapping *sign=({
        ([      "name" : "����",
                "id"   : "bj",
                "file" : "/d/beijing/matou",
                "value": 100,
                "time" : 10
        ]),
        ([      "name" : "����",
                "id"   : "sz",
                "file" : "/d/suzhou/szyunhe",
                "value": 100,
                "time" : 10
        ]),
        ([      "name" : "����",
                "id"   : "hz",
                "file" : "/d/hangzhou/matou",
                "value": 200,
                "time" : 20
        ])
});
void create()
{
        set("short","��ͷ");
        set("long",@LONG
�����Ǵ��˺���������ͷ���Ϸ�����ʳ�������������ڴ�ж����
������Ĺ�Ա��飬��ת�˻���ʱ���档������Ա���ӣ���С���ڽ�����
�й����ڰ����������й�Ա�ֳֳ����ڼ๤���м�����Ƥ��ת��תȥ��
��֪��Щʲô���⡣
    ����ͣ����һ���ʹ����ʹ���Ŀ��������һ������(sign)��
LONG );
        set("region", "yangzhou_zone");
        set("outdoors", "yangzhou");
        set("worktimes", 20);
        set("exits", ([
                "west"  : __DIR__"dujiangqiao",
        ]));
        set("item_desc", ([
                "sign" : (: look_sign :)
        ]));
        set("objects", ([
                __DIR__+"npc/jiangong" :1,
        ]));
	set("coor/x", 10);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_work", ({"work", "ganhuo"}) );
        add_action("do_go", "qu");
}

int do_work()
{
        object me = this_player();
//      if ( query("worktimes") < 0)
//              return notify_fail("��ͷ�����ڲ���Ҫ�˸ɻ�´ΰɣ�\n");
        if( query_temp("working", me) )
                return notify_fail("���Ѿ��ڸɻ��ˣ���\n");
        if ( !objectp( present ("jian gong", environment(me) ) ) )
                return notify_fail("��ͷ�����ڲ���Ҫ�˸ɻ�´ΰɣ�\n");
        if( query("combat_exp", me)<MIN_EXP )
        {
             tell_object(me,"���ﶼ���ػ�����ڻ��ɲ���,��Ҫ�ܹ�5���������ɡ�\n");
                return 1;
        }

        if( query("combat_exp", me) >= MAX_EXP )
        {
                tell_object(me,"����С�²���������ݡ�\n");
                return 1;
        }
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���أ�\n");
        if( query("jing", me)<10 || query("qi", me)<10 )
        {
                message_vision(
                        "�๤����$N����һ���ӣ�$N���϶�ʱ����һ��Ѫ�ۣ�$N�������Ķ㵽һ\n"
                        "��ȥ�ˡ�����ģ���С���⸱ή�Ҳ�������ӻ���ɻ�������๤��\n"
                        "��������������\n", me);
                me->receive_damage("qi", 11);
                me->receive_wound("qi", 11);
                return 1;
        }
        write("�๤�ñ���ָ��ָ��˵������ȥ���������ɡ���\n");
        write("�����һ���������ʼ�ɻ\n");
        addn("worktimes", -1);
        me->start_busy(3);
        set_temp("working", 1, me);
//      remove_call_out("work_end");
        call_out("work_end", 5, me);
        return 1;
}

int work_end(object me)
{
        object ob1;
        int add_exp,add_pot,add_score;

        if( !objectp(me) ) return 1;

        write("��������๤�ˣ�����һ���������۸�������\n"
              "�๤������������ļ��˵������С�ӣ������ģ�������Ĺ�Ǯ����\n");
        me->receive_damage("jing",10);
        me->receive_damage("qi",10);
                add_exp=60+random(50);
                add_pot=add_exp/3;
                add_score=3+random(3);
                GIFT_D->work_bonus(me, ([ "exp" : add_exp, "pot" : add_pot ]));
                ob1 = new("/clone/money/silver");
                ob1->set_amount(add_score);
                ob1->move(me);
        if( query_temp("working", me))delete_temp("working", me);
        return 1;
}

string look_sign()
{
        string str="�ɴ�ȥ(qu)��������ͷ��\n";
        int i=sizeof(sign);

        while (i--)
        {
                str += sign[i]["name"];
                str += "(" + sign[i]["id"] + ") ";
                str += MONEY_D->price_str(sign[i]["value"]) + "\n";
        }

        return str;
}

void do_move(object ob, int i)
{
//      ob->enable_player();
        delete_temp("noliving", ob);
        //ob->delete_temp("block_msg/all");
        tell_object(ob, "�յ�վ���ˡ�\n");
        ob->move(sign[i]["file"]);
        tell_room(environment(ob), ob->name() + "�Ӵ�������������\n", ({ob}));
}

int do_go(string arg)
{
        object ob=this_player();
        int i=sizeof(sign);

        if (!arg) return 0;
        if (ob->is_busy() || ob->is_fighting())
                return notify_fail("����æ���أ�\n");
        while(i--)
        {
                if (arg == sign[i]["id"])
                {
                        switch (MONEY_D->player_pay(ob, sign[i]["value"]))
                        {
                                case 0:
                                        return notify_fail("��⵰��һ�ߴ���ȥ��\n");
                                case 2:
                                        return notify_fail("����Ǯ��\n");
                        }
                        message_vision("$N������ȥ" + sign[i]["name"] + "�Ĵ���\n", ob);
//                      ob->disable_player("<��;��>");
                        set_temp("noliving/journey", 1, ob);
                        //ob->set_temp("block_msg/all", 1);
                        ob->move("/d/suzhou/onroad");
                        call_out("do_move", sign[i]["time"], ob, i);
                        return 1;
                }
        }
        return notify_fail("��Ҫȥ���\n");
}