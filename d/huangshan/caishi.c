// Room: /d/huangshan/caishi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
�ഫ��Ů洲�ʯ������ȡ����ɽʯ�о�Ӣ���ڣ�ɽɫ���ɽ���죬
��������ɫ��ɽ����ľҲ����ï�ܣ�ɽ�����ƣ��������˵��ɹ��ֺ��
�����ߣ���֮����ɽ�ٻ��ƣ��������ߣ������������˵��ˡ�ԶԶ����
��ԯ�壬ȴ��������ȥ��
LONG
        );
        set("exits", ([ 
                "westdown" : __DIR__"songgu",
                "east"     : __DIR__"xuanyuan",
        ]));
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -970);
        set("coor/z", 10);
        setup();
}
void init()
{
        add_action("do_chop","chop");
}

int do_chop(string arg)
{
        object obj, me = this_player();

        if(!arg || arg=="")
        {
                write("��Ҫ����ʲô��\n");
                return 1;
        }
        if( arg == "vine" || arg == "ɽ��")
        {
                if( !objectp(obj=query_temp("weapon", me)) )
                {
                        write("������֣���ʲô����\n");
                        return 1;
                }
                if( query("skill_type", obj) == "sword" || 
                        query("skill_type", obj) == "blade" || 
                        query("skill_type", obj) == "axe" )
                {
                        if( !query("exits/east") )
                        {
                                set("exits/east", __DIR__"xuanyuan");
                                message_vision(sprintf("$N�����е�%s����һ���򱱵�·��\n", obj->name()), me);
                                me->start_busy(1);
                        }
                        else
                                message_vision(sprintf("$N�����е�%s�����Ƶ�ɽ�١�\n",obj->name()), me);
                }
                else
                        message_vision(sprintf("$N�����е�%s�����Ƶ�ɽ��һ���ҿ���\n",obj->name()), me);
        }
        else write("��Ҫ����ʲô��\n");
        return 1;
}

void reset()
{
        ::reset();
        delete("exits/east");
}