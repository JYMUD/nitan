// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("�����쵶������", ({ "kuangfeng book0", "book0", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
        "����һ�����ɵ��ؼ������飺�����쵶(����)����\n"
        "��Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "blade",
                        "exp_required": 200000,
                        "jing_cost" :  50,
                        "difficulty":  20,
                        "max_skill" :  60,
                        "min_skill" :  0
                ]) );
        }
}
