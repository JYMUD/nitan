inherit ITEM;

void create()
{
       set_name("ҽҩ֪ʶ", ({ "medicine book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "��");
        set("long",
"�Ȿ������ֻ��һЩ�ּ�ģ�����־䣬�ƺ�\n"
"д����һЩ��ҩ�ⶾ�Ļ������š�\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "medical", // �书����,

        "exp_required": 5000,    // ��������Ҫ����;���.
        "jing_cost":     10,      // ���黨����.
        "difficulty":   20,      // �ο� /cmds/std/study.c
        "max_skill":    40,      // �ܶ�������ߵȼ�.
]) );
        }
}
int is_yaowang_book() { return 1; }

