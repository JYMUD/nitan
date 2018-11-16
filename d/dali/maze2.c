// Code of ShenZhou
// Room: /d/dali/maze2.c
// AceP

inherit ROOM;

int do_findout(string);
int do_out();

void create()
{
        set("short", "�Թ�����");
        set("long", @LONG
�����Թ��е�һ��·�ڣ��������º�ɭɭ�Ķ�����ľ������С·
�����������������ѱ淽�򣬾ٲ�̤���ľ��ǰ����Ӳݣ��������̵�
С�ȣ���������Ѫ���ܡ�һ��Сľ׮�϶������ľ�ƣ��ֱ�ָ������
С·������������ľ��ˮ����������������ľϡ��Щ����������
���߳�ȥ(out)�ķ���
LONG );
        set("exits", ([
                "��" : __FILE__,
                "ľ" : __FILE__,
                "ˮ" : __FILE__,
                "��" : __FILE__,
                "��" : __FILE__,
                ]));

        set("invalid_startroom", 1);
        set("cost", 3);
        set("outdoors", "dali");
        set("coor/x", -38000);
        set("coor/y", -71020);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me;
        me=this_player();

        if (me->query_skill("dodge",1)<100 && random(10)==1) {
                message_vision("$Nһ����С�ģ���������һ�裬����ཡ�һ��ˤ���˾����ԡ�\n", me);
                addn("qi", -100, me);
                addn("eff_qi", -100, me);
                message_vision("$N�����˰��죬�Ӿ����������˳��������������˴̣�ʹ���ѵ���\n", me);
        }
        add_action("do_findout", "findout");
        add_action("do_out", "out");
}

int valid_leave(object me, string dir)
{
        int mazepath;
        string walked,mpath;

        mazepath=query_temp("mazepath", me);

        mpath=sprintf("%d",mazepath);
        tell_object(me, "���룺"+mpath+"\n");

        walked=sprintf("%d%d%d%d%d",(query_temp("mark/maze��", me)-1),(query_temp("mark/mazeľ", me)-1),(query_temp("mark/mazeˮ", me)-1),(query_temp("mark/maze��", me)-1),(query_temp("mark/maze��", me)-1));
        tell_object(me, "�߹���"+walked+"\n");

        addn("qi", -10, me);

        if (walked==mpath) {
                tell_object(me,"���˼ڤ�룬����ϸ�㣬�����ҵ����ƴ��Թ�֮����ֻ��ת��ת�������˳�ȥ��\n");
                set("exits/"+dir, "/d/dali/yingroom1.c");
                remove_call_out("closing");
                call_out("closing",1,dir);
                return 1;
        }
                
        if (dir=="��")
                addn_temp("mark/maze��", 1, me);
        if (dir=="ľ")
                addn_temp("mark/mazeľ", 1, me);
        if (dir=="ˮ")
                addn_temp("mark/mazeˮ", 1, me);
        if (dir=="��")
                addn_temp("mark/maze��", 1, me);
        if (dir=="��")
                addn_temp("mark/maze��", 1, me);
        return ::valid_leave(me, dir);
}

void closing(string dir)
{
        set("exits/"+dir, __FILE__);
        return;
}

int do_findout(string arg)
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
                me->move("/d/dali/yideng9.c");
                return 1;
        }
        return 0;
}

int do_out()
{
        object me;
        me=this_player();

        tell_object(me, "���˼ڤ�룬��ת�ҿ�����ã�����û��ʲô�취�ҵ�·��ֻ�ô�ԭ·���˻�ȥ��\n");
        set_temp("mark/maze��", 1, me);
        set_temp("mark/mazeľ", 1, me);
        set_temp("mark/mazeˮ", 1, me);
        set_temp("mark/maze��", 1, me);
        set_temp("mark/maze��", 1, me);
        delete_temp("mazepath", me);
        me->move("/d/dali/maze1.c");
        return 1;
}