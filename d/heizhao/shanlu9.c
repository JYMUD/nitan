// Room: /heizhao/shanlu9.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

int do_find(string arg);
void create()
{
        set("short", "ɽ·");
        set("long", @LONG
������һ���������ɿڿʣ�����Զ����������ˮ�����㵱��
�ӿ�Ų�����ɽ�żţ���ˮ����ɽ�ȼ伤�����죬������ڣ�����
ˮ�����󣬴��������붥��ֻ��һ�������ƵĴ��ٲ��Ӷ���˫��֮
�䱼�ڶ��£��������Ǿ��ˡ�����������ȥ���ٲ�����һ����ݡ�
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                //"northdown" : __DIR__"pubu",
                "northdown" : __DIR__"yideng1",
                "eastdown"  : __DIR__"shanlu8",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1290);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_find", "find");
        add_action("do_find", "zhao");
}

int do_find(string arg)
{
        object me;
        object *inv;
        int i;
        me=this_player();

        if( arg == "way" && query("family/master_id", me) == "yidengdashi" )
        {
                        
                inv=all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        if (userp(inv[i]))
                                return notify_fail("�㸺��̫���ˣ�û����·��ɽ��\n");
                }
                tell_object(me, "�����ҿ���û��ע���㣬͵͵���������������˽�ȥ��\n");
                tell_object(me, "���һ��û��֪����С·����ɽ��������һ�ƴ�ʦ���ڵĵط���\n");
                me->move(__DIR__"yideng9");
                return 1;
        }
        return 0;
}

