inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ���ǳ������ĳ��ȣ����Ӻ��������û������̴ľ�Ƴɣ�
���������������ͼ�����������ɣ�����ʤ�ա��ذ岻֪����ʲô��
�����ģ��������������Ϣ����ֻ�е���������ģ��ǳ����������
����ͨ����ױ¥��
LONG );
        set("exits",([
                "east" : __DIR__"daban",
                "west" : __DIR__"changl10",
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}