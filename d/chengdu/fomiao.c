#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ƿ���������з����������Ȼ�����֡����ҵȷ��ʢ��
��ȣ��������С�ּ�ª�����Ǿݴ����������Ĳ��������˵����
����������������ޱ����죬������ﳣ�����ʢ�����Ž���һ��
Ե�֣������˵�������ǣ��������Ϊ�����Լ�ӵ�г����ĸ��ǣ���
�������ﶥ��Ĥ��(mobai)�� �����Ҳ�����������ǩ(chouqian)��
��ȷһ���Լ����Ը�̤����������·��
LONG );

       set("no_fight",1);
        set("no_drift", 1);
        set("valid_startroom","1");
        set("exits", ([
                "north" : __DIR__"shuduroad1",
        ]));

        set("coor/x", -15210);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
/*
void init()
{
        add_action("do_mobai","mobai");
        add_action("do_chouqian","chouqian");
}

int do_mobai(string arg){
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;
        if (me->is_busy()) return notify_fail("����æ���أ�Ĥ�ݻ�Ҫ���Ķ��⣿\n");
        if( query("can_not_change", me) )
                return notify_fail("�������ŷ������˫ϥ���£��ޱ��ϵĶ���Ĥ�ݣ����ò�������\n");
        write(HIC "����ŷ������Ϲ��Ͼ��Ĺ�����ȥ��˫�ֺ�ʮ��ʼĤ�ݡ�\n" NOR, me);
        tmpstr = tmpint = tmpcon = tmpdex = 13;
        tmpcon = 23;
        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: 
                        if (tmpstr < 30) tmpstr++;
                        else i--; 
                        break;
                case 1: 
                        if (tmpint < 30) tmpint++;
                        else i--;
                        break;
                case 2: 
                        if (tmpcon < 30) tmpcon++;
                        else i--;
                        break;
                case 3:
                        if (tmpdex < 30) tmpdex++;
                        else i--;
                        break;
                }
        }
        my = me->query_entire_dbase();
        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);
        write(HIC "ͻȻһ����������������ͷ���𣺡������Ҵ���������ʣ���\n" NOR, me);
        write(sprintf(HIY "\nһ�����������ȫ������ı��Ա仯�ˣ�\n"
                          "�������� " HIG "%d" HIY " �� "
                          "���ԣ��� " HIG "%d" HIY " �� "
                          "���ǣ��� " HIG "%d" HIY " �� "
                          "�������� " HIG "%d" HIY " ��\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        me->start_busy(1);
        return 1;
}

int do_chouqian(string arg)
{
        object me;
        string *character = ({
                "�ĺ�����",
                "��������",
                "������",
                "���ռ�թ",
         });
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( time()-query("last_chouqian_time", me)<1800 )
                return notify_fail("��ôƵ���ĳ�ǩ����Ĳ�����ǩ���飬�����Сʱ�����ɡ�\n");

        write(HIC "���ϵĳ���һ��ǩ����Ŀ������һ�󣬲������۾���ǩ���������֡�\n" NOR, me);
        write(HIC "ǩ��д�ţ�" + CHOUQIAN->query_chouqian() + "��\n" NOR, me);
        set("last_chouqian_time", time(), me);
        if( query("can_not_change", me))return 1;
        set("character", character[random(sizeof(character))], me);
        write(sprintf(HIY"\n����������һ����������������%s���ķ���չ�ɡ�\n"NOR,query("character", me)));
        return 1;
}
*/