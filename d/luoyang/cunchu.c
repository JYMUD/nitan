inherit ROOM;

void create()
{
        set("short", "�洢��");
        set("long", @LONG
�����ǵ��̵Ĵ洢�ң����ڴ洢һЩ�ѱ��䵱���������ܱ��������
�Ķ�������Ȼ��ֻ����ʱ�ģ�ֻҪһ���˿���ص����ޣ������ϰ�����
��ԥ�Ľ���߼۳��ۣ�Ҫ֪�����˳���Ǯ��ʲôҲ�����ϵġ�������ɭ��
����ʪ�����ҿ����л������һ��ùζ��
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"dangpu",
        ]));

	set("coor/x", -7000);
	set("coor/y", 2170);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}