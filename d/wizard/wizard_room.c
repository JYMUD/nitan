// Room: /d/wizard/wizard_room.c

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "��ʦ��Ϣ��");
        set("long", @LONG
���������̶��ʦ����Ϣ���ڣ��շ�ˢ��������ǽ���Ϲ�ͺͺ��
ʲô��û�У����ӵ����������һ���ľ�����������һ����ʦ����
��(board)�������������������һЩBUG������������
LONG );

        set("exits", ([
               "down" : __DIR__"guest_room",
               "up" : __DIR__"meeting_room",
               "west" : __DIR__"debug_room",
        ]));
        set("valid_startroom", 1);
        set("no_fight", "1");
        set("coor/x", 10000);
        set("coor/y", 10000);
        set("coor/z", 10000);
        setup();

        call_other("/clone/board/wiz_b", "???");
        replace_program(ROOM);
}
