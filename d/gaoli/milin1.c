// /d/gaoli/xuanwumen
// Room in ����
inherit ROOM;

void create()

{
set("short", "����");

        set("long", @LONG
��������һï�ܵĴ���֮�С����ܶ��ǲ���Ĺ�������ס��ͷ�ϵ�
���⡣��ʱ�м�ֻҰ�ô���������ܹ�������֮�У������˺ܶ����޶�
�ߣ��㲻��С��������
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"shanlu2",
                "south" : __DIR__"jiangbei",
               
        ]));
       setup();
        replace_program(ROOM);
}
