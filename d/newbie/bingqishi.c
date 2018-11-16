inherit ROOM;
#include <ansi.h>

string show_jia();

void create()
{
        set("short", "������");
        set("long", @LONG
�������ǹŴ�ı����ң������Ǽ��������ܣ���������˸��ָ�
���ı�����������ָ�� look jia�� ���Կ�����ʲô��������Ҫ�Ļ�
�����ã�����ָ�� qu ����ID from jia����
LONG);
        set("exits", ([
                "south" : __DIR__"lianwuchang",
        ]));

        set("item_desc", ([
                "jia"   :  (: show_jia :),
        ]));
        set("xinshoucun", 1);
        set("no_fight", 1);

        setup();
}

string show_jia()
{
        string msg;

        msg =  HIC "�������ϰ������±�����\n\n" NOR;
        msg += HIY "���ޣ�chang bian��\n" NOR;
        msg += HIY "�ֵ���gang dao��\n" NOR;
        msg += HIY "������chang jian��\n" NOR;
        msg += HIY "��ü����qimei gun��\n" NOR;
        msg += HIY "���ȣ�gang zhang��\n" NOR;
        msg += HIY "�����zhu bang��\n\n" NOR;
        msg += HIR "����ָ�� " HIY "qu <������Ӣ����> from jia" HIR " ��ȡ������\n\n" NOR;

        return msg;
}

void init()
{
        add_action("do_get", "qu");
}

int do_get(string arg)
{
        mapping ids = ([
                "chang bian" : "bian",
                "gang dao"   : "blade",
                "chang jian" : "changjian",
                "qimei gun"  : "qimeigun",
                "gang zhang" : "gangzhang",
                "zhu bang"   : "zhubang",
        ]);
        
        string wid;
        object weapon;

        if (! arg)return notify_fail("��Ҫȡʲô������qu <�����ɣ�> from jia��\n");

        if (sscanf(arg, "%s from jia", wid) != 1)return notify_fail("��Ҫȡʲô������qu <�����ɣ�> from jia��\n");

        if (! ids[wid])
                return notify_fail("������ı��������ڣ�������ָ�� look jia ���鿴����ȡ�ı�����\n");

        if( query_temp("qu_in_newbie", this_player()) )
                return notify_fail("���Ѿ�ȡ�������ˣ�������ٴ�ȡ�������˳���Ϸ������exit�������½��롣\n");

        weapon = new(__DIR__"obj/" + ids[wid]);

        if (! objectp(weapon))
                return notify_fail("clone " + wid + " error!\n");

        tell_object(this_player(),HIG"��ӱ�����������һ"+query("unit", weapon)+weapon->name()+"��\n"NOR);

        weapon->move(this_player(), 1);

        tell_object(this_player(),HIC"������ָ��look "+query("id", weapon)+"�鿴�ñ�����ʹ�÷�����\n"NOR);

        set_temp("qu_in_newbie", 1, this_player());

        return 1;
        
}
