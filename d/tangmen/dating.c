// Room: /d/tangmen/dating.c
//by hem
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "���´���");
        set("long", @LONG
        ���������ŵ����´�����ƽʱһ�㲻ʹ�ã�ֻ�������ŷ����ش������ʱ
�����ŵĳ�����������ۼ��������������������ú���֣������а˸�������
������ڷ�����������ƽʱұ��������ʣ����м���Ƴɵ����顣������һ���ܴ��
����ͼ(bagua)��
LONG
        );
        
        set("valid_startroom", 1);

        set("exits", ([
                
           "north" : __DIR__"houzhai",
        ]));
     set("objects", ([
 __DIR__"npc/dizi" : 1,
                        ]));

        set("item_desc", ([
                "bagua" : HIY "����ֵİ���ͼ����֪������ΪʲôҪ�������������\n",  
    ]));

        setup();

}
void init()
{
        add_action("do_break", "break");
}
int do_break(string arg)
{
    int n;
        object me = this_player();

    if( !arg || arg!="bagua" )
        {
        write("���ŵĲ���������������ƻ��ģ�\n");
        return 1;
    }
if( query_temp("marks/��", this_player())){
    message_vision(
    "$N�ߵ�����ǰ�������������ȫ��������˫�����϶������ػ�����ԡ�\n", this_player());


    n=query("neili", me);
    if (n >= 1500)
        {
        message_vision(
        HIR"$Nֻ�����һ�����죡�������Ծ�Ȼ��ת����ǰ����һ������\n"NOR, this_player());
        set("exits/down", "/d/tangmen/qiushi");
        set("neili", n-1500, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else
        {
                message_vision(
                HIW"���ֻ��һ���ƺߣ�$N�����Եķ����������ǰһ��....\n"NOR, this_player());
set("neili", 0,                 this_player());
                this_player()->unconcious();
    }
delete_temp("marks/��", me);
return 1;    
}
else 
        {write(HIY"�����Կ��а����������������ȶ�Ҫȥ��\n"NOR);
        return 1;}
}

void close(object room)
{
    message("vision","ֻ����һ��¸µ������������ַ���ת�����ָ���ԭ����\n", room);
    delete("exits/down", room);
}