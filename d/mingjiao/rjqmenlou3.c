//RJQMENLOU3.C

inherit ROOM;

void create()
{
        set("short", "��¥����");
        set("long", @LONG
������һ���ʯ�ң�����ڷ���ʯ��(zhuo)ʯ��(chair)��ʯ����
�����ݺύ���ͼ������ϸ����ԭ����һ��֣�����������(heizi)��
һ��(bai zi)�����ð׷������ˡ�ȴ��֪���ĵ���ʿΪ��û�����ꡣ
LONG );
        set("exits", ([
                "down" : __DIR__"rjqmenlou2",
        ]));
        setup();
}

void init()
{
        add_action("do_push", "push");
        add_action("do_sit", "sit");
}

int do_sit(string arg)
{

        if (arg != "chair")
                return notify_fail("��һ�����˸�ƨ�ɶա�\n");

        if( query_temp("allsit", this_player()) == 1 )
                return notify_fail("���Ѿ������ˡ�\n");

        set_temp("allsit", 1, this_player());
        return notify_fail("�����˸����������£���ʼ˼����֡�\n");
}

int do_push(string arg)
{
        object me;

        me = this_player();
        if (query_temp("allsit", me) != 1)
        {
                message_vision("$Nֻ����һ���㱣������˵��ϡ�\n", me);
                delete_temp("hei", me);
                delete_temp("allsit", me);
                me->unconcious();
                return 1;
        }

        if (arg != "hei zi" && arg != "bai zi")
                return notify_fail("�����ᰴ��һ��ʯ��������һ�����ѽ��\n");

        if( query_temp("allsit", me) && (arg == "heizi") )
        {
                if (query_temp("hei", me)==2)
                {
                        delete_temp("hei", me);
                        write("�����ᰴ��һ�º����ӣ�ʲô��ӦҲû�С�\n");
                        return 1;
                } else
                if (query_temp("hei", me)==1)
                {
                        set_temp("hei", 2, me);
                        write("�����ᰴ��һ�º����ӣ�ʲô��ӦҲû�С�\n");
                        return 1;
                } else
                if (query_temp("hei", me)==0)
                {
                        set_temp("hei", 1, me);
                        write("�����ᰴ��һ�º����ӣ�ʲô��ӦҲû�С�\n");
                        return 1;
                }
        }

        if (query_temp("allsit", me) && (arg=="bai zi"))
        {
                if(query_temp("hei", me)==2)
                {
                        message_vision("ֻ��ʯ���͵�һ����$Nһ���ҽУ�ֱ"
                                       "��������ȥ�ˡ�\n", me);
                        delete_temp("hei", me);
                        delete_temp("allsit", me);
                        me->move(__DIR__"rjqmidao");
                        return 1;
                }
                else
                {
                        write("�����ᰴ��һ�°����ӣ�ʲô��ӦҲû�С�\n");
                        return 1;
                }
        }
}

int valid_leave(object me, string dir)
{
            delete_temp("hei", me);
            delete_temp("allsit", me);
            return ::valid_leave(me, dir);
}
