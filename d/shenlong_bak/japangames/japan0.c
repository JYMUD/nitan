inherit ROOM;

void create()
{
        set("short", "�ձ���");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�ɱ���ձ������尡~~
LONG);

        set("exits", ([
                "east"   : __DIR__"japan1",

        ]));

   setup();

}

void init() 
{ 
    object me;
      
    me = this_player(); 
      
    me->set("startroom", base_name(this_object())); 
    me->save(); 
       
} 
