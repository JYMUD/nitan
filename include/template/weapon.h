// weapon.h
// ģ�����֮����

string long()
{
        string  long;
        string *fix_list;
        string  fix_name;
        string  extra;

        long = query("long");

        // ��ʾǰ׺����
        if (arrayp(fix_list = query("prefix")) && sizeof(fix_list))
        {
                foreach (fix_name in fix_list)
                        long += ITEM_D->get_prefix_desc(fix_name) + "\n";
        }
        // ��ʾ��׺����
        if (arrayp(fix_list = query("postfix")) && sizeof(fix_list))
        {
                foreach (fix_name in fix_list)
                        long += ITEM_D->get_postfix_desc(fix_name) + "\n";
        }

        if (stringp(extra = this_object()->extra_long()))
                long += extra;

        return long;
}

void init_damage(int damage) { set("weapon_prop/damage", damage); }

