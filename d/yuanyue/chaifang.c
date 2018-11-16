// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "��"); 
        set("long", @LONG
Բ��ɽׯ�Ĳ񷿺��񲢲��ǶѲ�ģ����ǹ��˵ġ�������֩�룬
�������й�ʺè���ù����룬����ʣ�µ�úм(breeze)������ʲ
�ᶼ�У�����û�в�������û�С�
LONG );
        set("type","house");
        set("indoors", "wansong");
        set("exits",([
                "south":__DIR__"grass4",
        ]) );

        set("item_desc", ([
                "úм": "���ﵽ������úм�����ƺ����Դ�ɨһ�£�����������\n",
                "breeze": "���ﵽ������úм�����ƺ����Դ�ɨһ�£�����������\n",
        ]) ); 
        set("coor/x",-590);
        set("coor/y",260);
        set("coor/z",80);
        setup();
        
} 
void init()
{
        add_action ("do_dight", "dight");
} 
int do_dight()
{               
        object mh,bo;
        int eff_qi;
        /*
        if (!present("sao ba",this_player())) 
                return notify_fail("������û��ɨ�ѣ���ô��ɨ��\n");
        */
        eff_qi=query("qi", this_player());
        if( eff_qi<query("max_qi", this_player())/10 )
        {
                return notify_fail("��̫���ˣ���ô��ɨ��\n");
        }
        this_player()->receive_damage("qi",query("max_qi", this_player())/10);
        if( query("dighted", this_object()) )
        {       message_vision("$N����ɨ�Ѷ�����˵��ɨ������\n��ʱ������������Ļҳ�����ֱǺ��͸��������\n������һ������������ɾ���Щ��\n\n", this_player() );
                return 1;
        }
        else if (random(5)) 
        {
                message_vision("$N����ɨ�Ѷ�����˵��ɨ������\n��ʱ������������Ļҳ�����ֱǺ��͸��������\n������һ������������ɾ���Щ��\n\n", this_player());
                return 1;
        }
        else 
        {
                message_vision("$N����ɨ����������ɨ�ţ�ͻȻ��һ���ڰ��Ľ�����ƺ�������һ��Сľ���ӡ�\n", this_player());
                set("dighted", 1, this_object());
                mh=new(__DIR__"obj/muhe");
                bo=new("/clone/book/mojiao");
                bo->move(mh);
                mh->move(this_player());
                return 1;
        }
        return 0;
} 
void reset(){
        ::reset();
      
        if( query("dighted", this_object())){
                delete("dighted", this_object());
        }
        return;
}        
