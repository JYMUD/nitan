// caoyuan.c ��ԭ
inherit ROOM;
void create()
{
        set("short", "��ԭ��Ե");
        set("long", @LONG
�����Ǵ��ԭ��ɳĮ����֮�أ������ϡ���ܣ��������������ȥ��
�����м�������̤������ӡ�����������ﳣ�����̶����������Ϸ�������
Щ���̡�
LONG);
        set("exits", ([
            "east" : __DIR__"caoyuana",
            "southwest" : __DIR__"caoyuan1",
            "northwest" : __DIR__"caoyuan2",
            "north" : __DIR__"caoyuan3",
 //           "north" : __DIR__"caoyuana",
            "south" : __DIR__"caoyuana",
        ]));
        set("objects", ([
                    __DIR__"npc/biaoshi" : 1,
        ])); 
        set("outdoors", "hasake");
        setup();
}
/*
int valid_leave(object me, string dir)
{
       if( dir == "north")addn_temp("mark/steps", 1, me);
       if( dir == "south")addn_temp("mark/steps", -1, me);
        
       if( query_temp("mark/steps", me) == 4){
            me->move(__DIR__"hswz");
            delete_temp("mark/steps", me);
            return notify_fail("��������\n");
           }  
     if( query_temp("mark/steps", me) == -4){
           me->move(__DIR__"caoyuan1");
           delete_temp("mark/steps", me);
             return notify_fail("��������\n");
        }  
        return ::valid_leave(me, dir);
}
*/