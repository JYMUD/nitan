inherit ROOM;

void create()
{
        set("short", "�η�");
        set("long", @LONG
�������һƬ����ϸϸ���������ñ�����ʯ�ŵķ�϶���Լ�
ͷ��ȥ��ʯ�ž�����ҡ�Σ���֪�ж���ʵ��һ����ɫ�԰׵�����
�ˣ���ͷɥ�������ڵ��ϡ�
LONG );
        set("no_clean_up", 0);

        setup(); 
        replace_program(ROOM);
}


