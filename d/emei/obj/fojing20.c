// fojing20.c

inherit ITEM;

string* titles = ({
//      "������",
//      "άĦ��",
//      "������",
//      "���Ͼ�",
        "�����پ�",
        "������;�",
        "������",
        "��վ�",
        "�����۶��ľ�",
});

void create()
{
        set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��𾭡�\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "mahayana",  // name of the skill
                        "exp_required": 0,  // minimum combat experience required
                        "jing_cost":    10,     // jing cost every time study this
                        "difficulty":   10,     // the base int to learn this skill
                        "max_skill":    50     // the maximum level you can learn
                ]) );
        }
}