inherit ROOM;

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
 ������ѩɽ�µĺ�Ժ����Ժ�������˼������ѩ�ɣ��ڰ׻λ�
��ѩɽ�����£�����ƮȻ�������Ķ����ϱ߱��ǵ����䳡�ˡ�
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "northdown" : __DIR__"dilao",
                "south"     : __DIR__"chang3",
        ]));
        setup();
        replace_program(ROOM);
}