inherit ROOM;

void create()
{
          set ("short", "��¥����");
          set ("long", @LONG
һ���ϳ�¥�����������һ��Ƭ�Ŀ����ؾ����۵ף�Ҫ��
�����ﲼ�������Ҫ����˭�빥��������ֱ�ȵ��컹�ѡ�
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([  
                    "down" : __DIR__"chenglou",
 
        ]));

        set("coor/x", -9080);
	set("coor/y", -1000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}