
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();

void setup()
{
        object room;

        ::setup();

        if (room = find_object(query("boat")))
                delete("yell_trigger", room);
}

void init()
{
        add_action("do_yell", "yell");
}

int do_yell(string arg)
{
        string dir;

        if (! arg || arg == "") return 0;

        if (arg == "boat") arg = "����";

        if( query("age", this_player())<14 )
                message_vision("$Nʹ�����̵���������һ������" + 
                               arg + "��\n", this_player());
        else if( query("neili", this_player())>200 )
                message_vision("$N���˿�����һ����" + arg + 
                               "������������ƽ�͵�ԶԶ��"
                               "�˳�ȥ��\n", this_player());
        else    message_vision("$N������������Хһ������" + arg + 
                               "����\n", this_player());

        if (arg == "����") 
        {
                check_trigger();
                return 1;
        }else message_vision(query("name", this_object())+"����ԶԶ����һ���������"+arg+
                               "��������\n", this_player());

        return 1;
}

void check_trigger()
{
        object room;
        string myboat;

        if( query("exits/enter", this_object()) )
        {
                message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n",
                        this_object());
                return;
        }

        if( !(room=find_object(myboat=query("boat", this_object()))) )
                room = load_object(myboat);

        if (! (room = find_object(myboat))) 
        {
                message("vision", "ERROR: boat not found\n", this_object());
                return;
        }

        if( query("yell_trigger", room) )
        {
                message("vision","ֻ����"+query("name", this_object())+"�������������������"
                        "�����æ���š�����\n", this_object() );
                return;
        }

        set("yell_trigger", 1, room);
        set("exits/enter", myboat, this_object());
        set("exits/out", base_name(this_object()), room);

        message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
                "����ϵ̰����Ա�˿�\n���¡�\n", this_object());
        message("vision", "������һ��̤�Ű���ϵ̰����γ�һ������"
                "�Ľ��ݡ�\n", room);

        remove_call_out("on_board");
        call_out("on_board", 15);
}

void on_board()
{
        object room;

        if( !query("exits/enter", this_object()) )
                return;

        message("vision","������̤�Ű��������������һ�㣬������"+query("name", this_object())+"��ʻȥ��\n",
                this_object());

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision", "������̤�Ű���������˵��һ��������ඡ���"
                        "���һ�㣬������\n"+query("name", this_object())+"��ʻȥ��\n",
                        room);
        }

        delete("exits/enter", this_object());

        remove_call_out("arrive");
        call_out("arrive", 20);
}

void arrive()
{
        object room;
        string myboat = query("boat");
        string myopp = query("opposite");

        if (room = find_object(myboat)) 
        {
                set("exits/out", myopp, room);
                message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű�"
                        "���ϵ̰���\n", 
                        room );
        }

        /*
        if( !(room = find_object(myopp)) )
                room = load_object(myopp);

        if( room = find_object(myopp) ) {
                set("exits/enter", myboat, room);
                message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
                        "����ϵ̰����Ա�˿�\n���¡�\n", 
                        room);
        }
        */       

        remove_call_out("close_passage");
        call_out("close_passage", 20);
}

void close_passage()
{
        object room;

        if (room = find_object(query("boat"))) 
        {
                delete("exits/out", room);
                message("vision","������̤�Ű����������ѱ���ʻ��"+query("name", this_object())+"�ġ�\n",
                room);
                delete("yell_trigger", room);
        }

        /*
        if( room=query("opposite", find_object(this_object()))){
                delete("exits/enter", room);
                message("vision","������̤�Ű��������������һ�㣬������"+query("name", this_object())+"��ʻȥ��\n",
                        room);
        }
        */
}
