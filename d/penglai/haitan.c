#include <ansi.h>
inherit ROOM;

#define MEMBER_D          "/adm/daemons/memberd"

void create()
{
        set("short", "��̲");
        set("long", @LONG
������������ɵ��ˡ�������һ���޼ʵĴ󺣣�������ȥ����
�������������֣�ǰ����Զ����һƬ���֣���������������������
��������
LONG);

        set("exits",([
                "south" :__DIR__"zhulin1",
        ]));
        set("outdoors", "penglai");
        set("valid_startroom", 1);
        set("no_clean_up", 1);
        set("no_rideto", 1);         // ���ò������������ط�
        set("no_flyto", 1);          // ���ò��ܴ������ط�����������
        set("no_die", 1);            // �������ƶ�����ȵ��
        set("penglai", 1);           // ��ʾ�������� 
        set("no_fight", 1);       

        set("objects", ([
               // __DIR__"npc/milu-shangren" : 1,
        ]));
       
        setup();
        "/clone/board/penglai_shibi"->foo(); 
}

void init()
{
        if (base_name(this_player()) == "/d/penglai/npc/qingmianshou")
        {
                destruct(this_player());
                return;
        }
                
        if (! GIFT_D->is_open_pld())
        {
                   // ������ˣ��ƶ��ؿ͵�
                   if (random(2))
                   {
                           this_player()->move("/d/city/wumiao");
                           this_player()->set("startroom", "/d/city/wumiao");
                   }
                   else
                   {
                           this_player()->move("/d/city/kedian");
                           this_player()->set("startroom", "/d/city/kedian");
                   }


        }
        this_player()->set("startroom", base_name(this_object()));
        this_player()->save();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir == "south")
        {
                if (! MEMBER_D->is_valib_member(me->query("id")))
                        return notify_fail("ֻ������Ч��Ա������������\n");
        }

        return 1;
}
