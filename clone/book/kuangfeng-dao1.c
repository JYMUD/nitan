// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("�����쵶���ϲ�", ({ "kuangfeng book1", "book1", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
        "����һ�����ɵ��ؼ������飺�����쵶(��)����\n"
        "��Ƥ���ƣ������Ѿ�����ܾ��ˡ�\n", );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "kuangfeng-blade",
                        "exp_required": 2000000,
                        "jing_cost" :  200,
                        "difficulty":  90,
                        "max_skill" :  100,
                        "min_skill" :  0
                ]) );
        }
}
