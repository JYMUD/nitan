inherit ROOM;

void create()
{ 
        set("short", "�޼�����ǰ");
        set("long", @LONG
�������޼��ﱱ���ֲ��Ĵ���ǰ�棬�޼�����������ֻ�Ƿ���
��������ڣ���ʹ��ˣ���������Ҳ��ķ����Ȼ������һ�ۿ���ȥ��
�;������Ʋ�����
LONG );
        set("outdoors", "beijing");
        set("exits", ([
                "west" :  "/d/beijing/yongdingdao",
                "east" : "/d/beijing/wjb_bjwdt",
        ])); 
        set("objects", ([   
             "/d/beijing/npc/wjb-guard" : 2,   
            ]));
               
	set("coor/x", -2790);
	set("coor/y", 7620);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if( !query_temp("good_wjb2", me) && query("bunch/bunch_name", me) != "�޼���" )
               return notify_fail("����һ����ס�㣬�����ȵ������޼������������˵���������\n"); 
           else
           {
              delete_temp("good_wjb2", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 