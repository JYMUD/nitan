// stone.c

inherit ITEM;

void create()
{
        set_name("石樑", ({ "shi liang", "shiliang" }) );
        set_weight(500);
        set_max_encumbrance(80000);
        set("no_get", 1);
        set("no_shown", 1);
        set("prep","under");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", "一座石樑，遠望去好似青鸞騰空，背上可以行人。\n");
                set("value", 1);
        }
}

int is_container() { return 1; }
