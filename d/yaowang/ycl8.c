inherit ROOM;
string p = "";
void create()
{
        set("short", "��С·");
        set("long", @LONG
����һ���������۵�С·��������һСƬ�Ͱ������֣�����
�Ƕ��͵�ɽ�ڡ�����������ʯ�ӣ��еĻ��ܼ����������������
������������ǰ����һ�Ѵִ��ԭľ��ס��ȥ·��
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl7",
]));

        set("outdoors", "yaowang");
        setup();
}
void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
        object me = this_player();

        if( query("exits/west") )
        {
                tell_object(me, "ԭľ�Ѿ��ƿ��ˡ�\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "��������ʹ������һ��ԭľ��\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "��������ʹ������һ��ԭľ��\n");
                        if( (sizeof(p)>5) && (p[<6..] == "lrrrrr") && (query_temp("murong_ask", me) || query("family/master_name",me) == "ʯ����") )
                        {
                                p = "";
                                if(!query("exits/north"))
                                {
                                        set("exits/north", __DIR__"ycl9");
                                        call_out("remove_north", 5);
                                        tell_room(__FILE__, "ԭľ������һ����¶����һ����϶��\n");
                                        return 1;
                                }
                                return 1;
                        }
                        return 1;
                default:
                        tell_object(me, "��Ҫ���ĸ������ƣ�\n");
                        return 1;
        }
}

void remove_north()
{
        if("exits/north")
        {
                delete("exits/north");
                p = "";
        }
}
