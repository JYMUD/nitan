inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǵ峤�ҵĳ�����ƽ�������Ƕ��˿��Ե�����Ҫ ������ָ
�� yao��Щʳ��������������һ�����ʦ��æ����ͷ�󺹡��ݽ�
����һ����ˮ�ס�  
LONG);

        set("exits", ([
                "east" : __DIR__"cunzhangjia",
        ]));

        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("ricewater", 1000);
        set("xinshoucun", 1); 
        set("no_fight", 1);
        setup();
}

void init()
{
        add_action("do_yao", "yao");
}

int do_yao()
{
        object me;
        object food;
        object water;
        me = this_player();

        if (present("man tou", this_player())) 
                return notify_fail(CYN "��ʦüͷһ�壬˵�������������ã����˷�ʳ�\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "��ʦüͷһ�壬˵�������������ã����˷�ʳ�\n" NOR);

        if( time()-query_temp("last_yao_food", me)<30 )
                return notify_fail(CYN "��ʦüͷһ�壬˵�������Ҫ��ʳ���ˣ�������������˰ɣ�\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "��ʦ��һ����ͷ��һ����ˮ�ݵ�$N���У�Ц"
                               "���������á�\n" NOR, me);
                food = new("/d/henshan/obj/mantou");
                water = new("/d/henshan/obj/water");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
                set_temp("last_yao_food", time(),                 me);
        }
        else 
                message_vision(CYN "��ʦ��$N" CYN "Ǹ�������ˣ��ԵĺȵĶ�"
                               "û�ˡ�\n" NOR,me);
        return 1; 

}
