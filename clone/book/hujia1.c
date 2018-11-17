// blade-book.c

inherit BOOK;

void create()
{
        set_name("胡家拳經",({ "hujia quanjing","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本胡家刀譜，記錄了胡家拳法微妙之處。\n");
                set("value", 50);
                set("material", "paper");
                set("skill", ([
                        "name":         "hujia-quan",      //name of the skill
						"family_name" : "關外胡家",
                        "exp_required": 1000,         //minimum combat experience required
                        "jing_cost":    30,           // jing cost every time study this
                        "difficulty":   30,           // the base int to learn this skill
                        "max_skill":    120           // the maximum level you can learn
                ]) );
        }
}
