#include <ansi.h>;
#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "�͵�");
        set("long",
"�������������Ŀ�ջ������ǳ���¡������οͶ�ѡ��������ţ���\n"
"�ŵ��ӿ������ɵĽ�����˯��Ҳ����ѵġ���С����������æ������ת��\n"
"�Ӵ���������ĺ������ѡ��͵�����˴Ӳ�¶�棬��������˭���и��ָ�\n"
"���Ĳ²⡣�����е��������������˶�֪���ģ���������ŵĵ��̣��ݲ�\n"
"���������ڴ˺�����Ϊ��\n"
);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room", 1);
        set("item_desc", ([
                "paizi" : "��\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"bdajie1",
                "up"   : __DIR__"kedian2",
        ]));

        setup();
        
}

int valid_leave(object me, string dir)
{          
        object ob;
        mapping myfam;

        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("��С��һ�µ���¥��ǰ������һ���������ţ����ס�����������"+HIC"��������"NOR+"��\n");

        if( query_temp("rent_paid", me) && dir == "west" )
        {     
                myfam=query("family", me);
                if (myfam["family_name"] != "��������")
                        return notify_fail("��С���ܵ��ű���ס���͹��Ѿ��������ӣ����᲻ס��������أ����˻���ΪС���ź����أ�\n");
                delete_temp("rent_paid", me);
                me->move("/d/tangmen/bdajie1");
                tell_object(me,"��С��Ц�����˵������λ"+RANK_D->query_respect(ob)+"����ӭ����"+HIG"���ſ͵�"NOR+"\n\n");
                return 1;
        }
        return ::valid_leave(me, dir);
}

