// Room: /d/kunlun/bainiuling.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_wo(string arg);
int do_breathe();
void delete_done(object me);

void create()
{
        set("short", "��ţ��");
        set("long",@long
����ɽ�������긲�ǰ�ѩ������״Զ������һͷ���ڳԲݵ�ţ����
�������ﺮ���Х�������̹ǣ��㲻�����˸�������ɽ����һ��ƽ�أ�
����һ����ɫ�ľ�ʯ(stone)��
long);
        set("exits",([
                "southwest" : __DIR__"fufengshan",
        ]));
        set("no_clean_up", 0);
        set("item_desc", ([
                "stone" :"����ʯ�ܴ󣬿�������һ���ˡ�����ʮ��ƽ���⻬���ƺ�������Ħ����\n",
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -119970);
        set("coor/y", 40180);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_wo", "wo");
        add_action("do_breathe", "breathe");
}

int do_wo(string arg)
{
        if ( !arg || (arg != "stone") )
        return notify_fail("��Ҫ����ʲô���棿\n");

        if (this_player()->is_busy())
                return notify_fail("����æ���ء�\n");

        if( query_temp("marks/wo", this_player()) )
                return notify_fail("���Ѿ�������ʯ���ˡ�\n");

        set_temp("marks/wo", 1, this_player());
        return notify_fail("�����������ʯ�ϣ����ص��������գ�˫����Ȼ΢����ȫ����ɡ�\n");
}

int do_breathe()
{
        object me=this_player();

        if( !query_temp("marks/wo", me) )
                return notify_fail("���������˼�������ֻ���ú�������������������ڵ����������᲻������\n");

        if (me->is_busy())
                return notify_fail("����æ���ء�\n");

        if( query_temp("marks/done", me) )
                return notify_fail("��������������˹�����������ʮ���������Ⱥú���Ϣһ�°ɡ�\n");

        if (me->query_skill("liangyi-shengong", 1) < 120 ) 
                return notify_fail("���ڹ�����̫�������������������Ϣ��\n");
                
        if (me->query_skill("liangyi-shengong", 1) > 199 ) 
                return notify_fail("����������Ѿ���ǿ�ˣ��޷���ͨ����������ǿ������\n"); 
                
        if (! me->can_improve_skill("liangyi-shengong")) 
                return notify_fail("���ʵս���鲻�㣬�޷���������������\n"); 

        if (query("qi", me) < 40 || query("jing", me) < 40) 
                return notify_fail("�������Ѿ���ƣ���ˣ���Ϣһ��������Ϣ��\n"); 

        message_vision(HIW "\n$N" HIW "�������ڵ����������������������������ֻ����Ľ�" 
                       "�����\n���⡣$N" HIW "ֻ����ȫ��͸�������Ķ���ˮ���·�������" 
                       "��Ȼһ�塣\n\n" NOR, me); 

        me->receive_damage("jing", random(30));
        me->receive_damage("qi",   random(30));
        if (me->can_improve_skill("liangyi-shengong")) 
                me->improve_skill("liangyi-shengong", 5 + query("int", me) / 2 + 
                                  me->query_skill("force") / 6); 

        set_temp("marks/done", 1, me);
        call_out("delete_done", 5, me);

        return 1;
}

void delete_done(object me)
{
        if( objectp(me))delete_temp("marks/done", me);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/wo", me);
        return ::valid_leave(me, dir);
}
