// pixie_sword_book.c

inherit BOOK;

void create()
{
        set_name("辟邪剑谱", ({ "pixie_sword_book", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本林家的辟邪剑谱。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":        "pixie-sword",          // name of the skill
                        "exp_required": 10000,                          // minimum combat experience required
                                                                        // to learn this skill.
                        "sen_cost":     30,                             // gin cost every time study this
                        "difficulty":   30,                             // the base int to learn this skill
                                                                        // modify is gin_cost's (difficulty - int)*5%
                        "max_skill":    100,                            // the maximum level you can learn
                        "min_skill":    0                               // the maximum level you can learn
                                                                        // from this object.
                ]) );
        }
}
int query_autoload() { return 1; }