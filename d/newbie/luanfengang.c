inherit ROOM;

void create()
{
        set("short", "�ҷظ�");
        set("long", @LONG
����һƬ���Ƿ�Ĺ����֪�����˶���Ӣ�ۺú������پ޼�
������˲�������������������˵ı���֮�⡣�������̻�
һ���������Ƕ���Ҳ�ܷ���ѣĿ�Ĺ�ʣ�һ��ˣ��㲻����
�𱯹۵���ͷ����Ѫ���ȣ��޲�������Ͷ�����������ȥ
��ȡ������ʷ��
LONG);
        set("exits", ([
                "northwest" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        setup();

        replace_program(ROOM);
}