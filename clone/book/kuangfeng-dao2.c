// kuangfeng1.c

inherit ITEM;
inherit F_UNIQUE;
 
void create()
{
        set_name("�����쵶���²�", ({ "kuangfeng book2", "book2", }));
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
                        "exp_required": 2500000,
                        "jing_cost" :  300,
                        "difficulty":  92,
                        "max_skill" :  200,
                        "min_skill" :  100
                ]) );
        }
}
