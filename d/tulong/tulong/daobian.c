inherit ROOM;

void create()
{
        set("short","����ɽ����");
        set("long", @LONG
����ɽ��Ǯ�����ڵĶ���֮�У��Ǹ�����С����ɽʯ��ᾣ������˾ӡ�����
���˸��ٴ��죬����ʾ�⣬ֻ����������Ͼ�����һͷ��ӥ��˫����չ��������
�䡣�������֮��վ��һ�����ߡ�����ɽ�Ǹ�С����ɽʯ��ľ�޿ɹ�֮��������
���и����壬Φ�ɸ��ʣ�ͣ����ʮ���Ҵ󴬣����Ǿ޾����ɳ��һ���˵�������
LONG );
        set("exits",([
                "southdown":"/d/tulong/tulong/boat2",
                "east":"/d/tulong/tulong/gukou",
            ]));

        set("objects",([
                 "/d/tulong/tulong/npc/jiaozhong1": 2,
                 "/d/tulong/tulong/npc/jiaozhong2": 2,
                 "/d/tulong/tulong/npc/bai": 1,
            ]));

setup();
}

int valid_leave(object me,string dir)
{
        object ob;
        if( !query_temp("dao", me) && dir == "east" )
        return notify_fail("һ���˻᳡��������֮�����������������ǵĴ�(break boat)�Է����⡣\n");

        if( query_temp("dao", me) && dir == "east" && ob=present("baiguishou") )
        {
        ob->ccommand("tnnd"+query("id", me));
        ob->ccommand("slap3"+query("id", me));
        message_vision("$N�ȵ���$n��ȥ���ɣ�\n",ob,me);
        ob->kill_ob(me);
        ob=present("jiao zhong");
        if (objectp(ob)) ob->kill_ob(me);
        ob=present("jiao zhong 2");
        if (objectp(ob)) ob->kill_ob(me);
        ob=present("jiao zhong 3");
        if (objectp(ob)) ob->kill_ob(me);
        ob=present("jiao zhong 4");
        if (objectp(ob)) ob->kill_ob(me);
        return notify_fail("�򶫵�·���׹�����ס�ˡ�\n"); }
        return 1;
}
