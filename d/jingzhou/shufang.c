//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "�鷿");
        set ("long", @LONG
����֪�����˵��鷿��������һ����ܣ����ž��ݸ�־���Լ�����
�����Ĺ����¼��������һ����ɫ����ĵ�ľ�ܣ��ڷ��˾���ͭ����
���������ȸ�ɫ���档����һ�Ŵ���������������������ķ��ı���
������һ�����ȣ��ϱ���һ�����ԣ���Լ�����ŵ����󻨵����㡣
LONG);
        set("exits", ([
                "west" : __DIR__"huayuan",
        ]));
  
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}