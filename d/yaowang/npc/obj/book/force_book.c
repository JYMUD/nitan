inherit ITEM;

void create()
{
       set_name("�����ڹ�", ({ "force book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "��");
        set("long",
"�Ȿ������ֻ��һЩ�ּ�ģ�����־䣬�ƺ�\n"
"д����һЩ�ڹ������ľ���̸֮��\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "force", // �书����,
        "exp_required": 100,    // ��������Ҫ����;���.
        "jing_cost":     15,      // ���黨����.
        "difficulty":   20,      // �ο� /cmds/std/study.c
        "max_skill":    60,      // �ܶ�������ߵȼ�.
]) );
        }
}
int is_yaowang_book() { return 1; }

