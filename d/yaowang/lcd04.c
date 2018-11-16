inherit ROOM;

protected string p = "";

void create()
{
        set("short", "��ŢС·");
        set("long", @LONG
����һ����С��·��������������¹���һ����Ţ��������
��һЩ���õĿ�֦��Ҷ������Ѭ�졣��ǰ���ǿ��ʯͷ��ʯͷ��
������̦�����٣���ס�������ĵ�·����֪���ܷ��ƿ�(push)ʯͷ��
��ʵ���ֲ�֪�����ĸ������ơ�
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "northeast" : __DIR__"lcd03",
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
                tell_object(me, "ʯͷ�Ѿ��ƿ��ˡ�\n");
                return 1;
        }

        if(sizeof(p) > 10)
                p = "";

        switch (arg)
        {
                case "left":
                        p = "l";
                        tell_object(me, "��������ʹ������һ��ʯͷ��մ��һ���ࡣ\n");
                        return 1;
                case "right":
                        p += "r";
                        tell_object(me, "��������ʹ������һ��ʯͷ��մ��һ���ࡣ\n");
                        if( (sizeof(p) > 5) && (p[<6..] == "lrrrrr") )
                        {
                                p = "";
                                if(!query("exits/west"))
                                {
                                        set("exits/west", __DIR__"lcd05");
                                        call_out("remove_west", 5);
                                        tell_room(__FILE__, "ʯͷ������һ����¶����һ����϶��\n");
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

protected void remove_west()
{
        if("exits/west")
        {
                delete("exits/west");
                p = "";
        }
}
