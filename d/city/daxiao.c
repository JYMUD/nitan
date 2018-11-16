// Room: /city/daxiao.c

inherit ROOM;

int sos(int,int);
void fresh(object ob);
void create()
{
        set("short", "�ĳ�");
        set("long", @LONG
�����Ƕ�(gamble)����С���ķ��䣬ǽ�Ϲ���һ������(paizi)��
LONG );
        set("item_desc", ([
                "paizi" :
"���ĳ��¿��Ŷġ���С�������ڲ��Խ׶Ρ�\n"
"����С���ķ���\n"
"��������ɫ������һֻ���ɫ�ӵ����ܺͣ�\n"
"       �� �� ʮ Ϊ��С����\n"
"       ʮһ �� ʮ�� Ϊ���󡹣�\n"
"       ����ɫ�ӵ�����ͬ�����Сͨ�ԡ�\n"
"\n������󣬿�С��С��һ��һ��\n"
"\n���ĳ����ܸ��ֻ���Ϊ��ע��\n"
"\n��עΪ��ʮ����١�\n",
        ]));
        set("exits", ([
                "east" : "/d/city/duchang",
                "north" : "/d/city/bocai",
        ]));
//	set("no_clean_up", 0);
        set("no_fight", "1");
	set("coor/x", -20);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_gamble", "gamble");
}

int do_gamble(string arg)
{
        int a,b,c;
        int wager, skill, lpoint, tpoint;
        string wtype1, wtype2, wtype0, status;
        object mtype, me;
        mapping lrn;

        int min, max;
        min = 500;
        max = 500000;

        me = this_player();

        if( query_temp("casino/mark", me) )
                return notify_fail("����ô�ż���? �����ٶ���Ϣһ����� -:)\n");

        if (!arg || sscanf(arg, "%s %s %s %d", wtype0, wtype1, wtype2, wager) !=4)
                return notify_fail("gamble big|small money|skill <type> <amount>\n"
                                   "eg. gamble big money silver 3\n");

        if (wtype1 == "money")
        {
                mtype = present(wtype2 + "_money", me);
                if( !mtype)          return notify_fail("������û�����ֻ��ҡ�\n");
                if( wager < 1 )        return notify_fail("��Ҫѹ���ٰ�?\n");
                if( (int)mtype->query_amount() < wager)
                        return notify_fail("������û����ô��"+query("name", mtype)+"��\n");
                if( wager*(query("base_value", mtype))<min || 
                    wager*(query("base_value", mtype))>max )
                        return notify_fail("��Ķ�ע�����޶�֮��!\n"
                        "������޶���" + chinese_number(min) + "��" + chinese_number(max) + "��\n");
        }
        else    return notify_fail("���ĳ����������ֶ�ע��\n");

        if ( (wtype0 != "big") && (wtype0 != "small") )
                return notify_fail("��Ҫ�Ĵ��Ƕ�С?\n");

        set_temp("gamb_t", (query_temp("gamb_t", me)+1), me);
        if( query_temp("gamb_t", me)>50 )
        {
                call_out("fresh", 300, me);
                set_temp("casino/mark", 1, me);
                return notify_fail(
"��λ" + RANK_D->query_respect(me) + "�����Ѿ����˺ܾ��ˣ���������Ϣһ����ɡ�\n");
        }

        a = random(6) + 1;
        b = random(6) + 1;
        c = random(6) + 1;

        message_vision("����" + a + "   " + b + "   " + c + "   ��", me);

        if ((a == b) && (b == c) )
//              message_vision("����" + a + " " + b + " " + c " ,��Сͨɱ��\n", me);
                message_vision("��Сͨɱ��\n", me);
        else if ( (a+b+c) > 10 )
//              message_vision("����" + a + " " + b + " " + c " ,��С���\n", me);
                message_vision("��С���\n",me);
        else if ( (a+b+c) < 11 )
//              message_vision("����" + a + " " + b + " " + c " ,�Դ���С��\n", me);
                message_vision("�Դ���С��\n",me);

        if ( ( (a == b) && (b == c) ) ||
             ( (a+b+c) > 10 && (wtype0 == "small") ) ||
             ( (a+b+c) < 11 && (wtype0 == "big") ) )
                status = "lose";

        if (wtype1 == "money")
        {
                if ( status == "lose") {
        message_vision(query("name", me)+"����"+chinese_number(wager)+
query("base_unit", mtype)+query("name", mtype)+"��\n",me);
                        mtype->set_amount((int)mtype->query_amount() - wager);
                        mtype->move(me);
                }
                else {
        message_vision(query("name", me)+"Ӯ��"+chinese_number(wager)+
query("base_unit", mtype)+query("name", mtype)+"��\n",me);
                        mtype->set_amount((int)mtype->query_amount() + wager);
                        mtype->move(me);
                }
        }
        else if (wtype1 == "skill")
        {
                if ( status == "lose") {
        message_vision(query("name", me)+"����"+chinese_number(wager)+
"��" + to_chinese(wtype2) + "�Ĺ�����\n", me);
                        wager -= lpoint;
                        while (wager > 0)
                        {
                           wager -= skill*skill;
                           skill -= 1;
                        }
                        wager *= -1;
                        if (wager > lpoint) wager -= lpoint;
                        else wager += (lpoint*-1);
                }
                else {
        message_vision(query("name", me)+"Ӯ��"+chinese_number(wager)+
"��" + to_chinese(wtype2) + "�Ĺ�����\n", me);
                        wager += lpoint;
                        while (wager >= (skill+1)*(skill+1))
                        {
                          skill += 1;
                          wager -= skill*skill;
                        }
                        wager -= lpoint;
                }
                me->set_skill(wtype2, skill);
                me->improve_skill(wtype2, wager);
        }
        return 1;
}

void fresh(object ob)
{
	if (! objectp(ob)) return;
        delete_temp("gamb_t", ob);
        delete_temp("casino/mark", ob);
}

int sos(int lower, int upper)
{
        int x,y;
        x = 0;

        while (lower <= upper)
        {
                y = lower*lower;
                x += y;
                lower++;
        }
        return x;
}