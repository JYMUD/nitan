//HSQTAN5.C

inherit ROOM;

void create()
{
        set("short", "��̶");
        set("long", @LONG
�������ٲ��µĺ�̶��ˮ���İ��ޱȣ�ˮ�б���̹ǣ���������
���ܣ���ֻ����������һ��һ����ʧ�������м������ڣ�������ƺ�
��Щ����͸����
LONG );
        set("exits", ([
                "east" : __DIR__"hsqtan6",
                "west" : __DIR__"hsqtan4",
                "south" :__DIR__"hsqtan5",
                "north" :__DIR__"hsqtan5",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me;
        int meqi,meneili,decqi,mq;
        me=this_player();
        meqi=query("qi", me);
        meneili=query("neili", me);
        mq=query("max_qi", me);
        decqi=(int)(mq/(random(4)+5+meneili/200));
        meqi=meqi-decqi;
        set("neili", 0, me);
        if( meqi>0)set("qi", meqi, me);
        else me->die();
}
