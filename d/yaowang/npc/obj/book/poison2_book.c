inherit ITEM;

void create()
{
       set_name("�����²�", ({ "tang-du book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "��");
        set("long",
"�Ȿ������ֻ��һЩ�ּ�ģ�����־䣬�ƺ�\n"
"д����һЩ�ö��Ļ������š�\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "poison", // �书����,

        "exp_required": 10000,    // ��������Ҫ����;���.
        "jing_cost":     35,      // ���黨����.
        "difficulty":   30,      // �ο� /cmds/std/study.c
        "max_skill":    120,      // �ܶ�������ߵȼ�.
]) );
        }
}
int is_yaowang_book() { return 1; }

