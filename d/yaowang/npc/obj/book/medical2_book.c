inherit ITEM;

void create()
{
       set_name("ҽҩ�߼�֪ʶ", ({ "medicine book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
        set("unit", "��");
        set("long",
"�Ȿ������ֻ��һЩ�ּ�ģ�����־䣬�ƺ�\n"
"д����һЩ��ֲ���ݵĻ������š�\n");
        set("value", 800);
        set("material", "paper");
        set("skill", ([
        "name":         "baicao-jue", // �书����,
        "exp_required": 5000,    // ��������Ҫ����;���.
        "jing_cost":     30,      // ���黨����.
        "difficulty":   25,      // �ο� /cmds/std/study.c
        "max_skill":    100,      // �ܶ�������ߵȼ�.
        "min_skill":    10,      // �ܶ�������ߵȼ�.
]) );
        }
}
int is_yaowang_book() { return 1; }

