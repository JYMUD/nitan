
inherit ITEM;

void create()
{
        set_name("������", ({ "yufeng book", "book" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
"������д������Ĺ��������\n");
                set("value", 200);
                set("material", "paper");
        }
}
