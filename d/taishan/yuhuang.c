// Room: /d/taishan/yuhuang.c
// Last Modified by Winder on Aug. 25 2001
// Modified by Zeratul Jan 11 2001 ������������10000���ܼ�����

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������Ǵ���̩ɽ��������ۣ��ų�̫�幬����۹ۣ���ɽ�š���
�ʵ����ͤ������ͤ������������ɡ�ɽ�Ŷ��顰�����ʶ�������
����������ͭ����ʴ�����������Ҷ�����ŷ硱��Զ�ŵ�������
���ܲ���죬����ɽ�����񡣹�ǰΪ�ŵǷ�̨�������ʵ۷�������ʽ��
����������С�̨����һ���ֱ�����˵�Ǻ����������
��������ʯƺ������ƽ���壬�Ͻ�Ǭ��ͤ���Ͽ̡�����С���´�����
�������ϱ���������������֮��������̨��
LONG );
        set("exits", ([
                "southdown" : __DIR__"nantian",
                "southeast" : __DIR__"riguan",
                "northwest" : __DIR__"zhangren",
                "east"      : __DIR__"guanriting",
                "west"      : __DIR__"wangheting",
                "up"        : __DIR__"fengchan",
        ]));
        set("objects",([
                __DIR__"npc/jiang" : 1,
                __DIR__"npc/wei-shi2" : 3,
        ]));
        set("coor/x", 30);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob1, ob2, ob3;
        string mengzhu, shangshan, fae;
        
        if(!( ob1 = find_living("mengzhu")) )
                ob1 = load_object("/adm/npc/meng-zhu");
        mengzhu=query("winner", ob1);

        if(!( ob2 = find_living("shangshan")) )
                ob2 = load_object("/adm/npc/shang-shan");
        shangshan=query("winner", ob2);

        if(!( ob3 = find_living("fae")) )
                ob3 = load_object("/adm/npc/fa-e");
        fae=query("winner", ob3);

        if( dir == "up" )
        { 
                if( userp(me) && query("score", me)<10000 )
                        return notify_fail( "�����ǲ����������С����ģ����ǻ�ȥ�ɡ�\n" );
                if( present("jiang baisheng", environment(me)) &&
                        query("id", me) != mengzhu && 
                        query("id", me) != shangshan && 
                        query("id", me) != fae )
                        return notify_fail("����ʤ������ס��˵����������æ�����ڲ�����ͣ�����ɽȥ�ɣ�\n");
                else if( query("id", me) == mengzhu )
                {
                        message_vision(HIY "\n����ʤ�ϻ̳Ͽֵ���$N�򵹿�ͷ�������������������꣬���꣬�����꣡\n" NOR, me);
                }        
                else if( query("id", me) == shangshan )
                {
                        message_vision(HIY "\n����ʤ�Ϲ��Ͼ�����$N�ݵ�����������ʹ�����ã� ���½���ʤ�μ����ˣ�\n" NOR, me);
                }        
                else if( query("id", me) == fae )
                {
                        message_vision(HIY "\n����ʤ�Ϲ��Ͼ�����$N�ݵ�����������ʹ�����ã� ���½���ʤ�μ����ˣ�\n" NOR, me);
                }        
        }

        return ::valid_leave(me, dir);
}