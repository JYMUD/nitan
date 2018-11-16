// This program is a part of NITAN MudLIB
// equip.c

#include <ansi.h>
#include <dbase.h>
#include <weapon.h>

int wear()
{
        object owner, weapon;
        mapping armor_prop, enchase_prop, applied_prop;
        mapping require;
        string *apply1;
        string *apply2;
        string type;
        int flag;
        int max_qi, max_jing;

        if( !objectp(this_object()) ) return 0;
        // Only character object can wear armors.
        owner = environment();
        if( !owner || !owner->is_character() ) return 0;

        if( query("no_identify") )
                return notify_fail(this_object()->name() + "��Ҫ������ſ���ʹ�á�\n");

        // Does the consistence valid ?
        if( query("consistence") < 1 )
                return notify_fail(this_object()->name() + "������̫�����ˣ����ܼ��������ˡ�\n");

        // If already worn, just recognize it.
        if( query("equipped") ) return 1;

        // If handing it now, stop handing
        if( query_temp("handing", owner) == this_object() )
                delete_temp("handing", owner);

        // Check if we have "armor_prop" defined.
        if( !mapp(armor_prop = query("armor_prop")) ||
            !stringp(type = query("armor_type")) )
                return notify_fail("��ֻ�ܴ����ɵ������ߵĶ�����\n");

        if( query_temp("armor/"+type, owner) )
                return notify_fail("���Ѿ�������ͬ���͵Ļ����ˡ�\n");

        if( type == "hands" &&
            weapon=query_temp("weapon", owner)){
                if( query("flag", weapon)&TWO_HANDED )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");
                if( query_temp("secondary_weapon", owner )
                 || query_temp("armor/finger", owner )
                 || query_temp("handing", owner) )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");
        }

        if( type == "hands" &&
            query_temp("armor/finger", owner) &&
            query_temp("handing", owner) )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");

        if( type == "finger" &&
            weapon=query_temp("weapon", owner)){
                if( query("flag", weapon)&TWO_HANDED )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");
                if( query_temp("secondary_weapon", owner )
                 || query_temp("armor/hands", owner )
                 || query_temp("handing", owner) )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");
        }

        if( type == "finger" &&
            query_temp("armor/hands", owner) &&
            query_temp("handing", owner) )
                        return notify_fail("�����ճ�һֻ��������װ��"+this_object()->name()+"��\n");

        if( userp(owner) && !wizardp(owner) &&
            (!query("reborn/times", owner) || query("id", owner) != this_object()->item_owner()) &&
            mapp(require = query("require")) && sizeof(require) ) {
                if( !undefinedp(require["level"]) &&
                    query("level", owner)<require["level"] )
                        return notify_fail("��ĵȼ��������޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["max_level"]) &&
                    query("level", owner)>require["max_level"] )
                        return notify_fail("��ĵȼ��������ޣ��޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["age"]) &&
                    query("age", owner)<require["age"] )
                        return notify_fail("������䲻�����޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["max_age"]) &&
                    query("age", owner)>require["max_age"] )
                        return notify_fail("������䳬�����ޣ��޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["str"]) &&
                    owner->query_str() < require["str"] )
                        return notify_fail("����������㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["dex"]) &&
                    owner->query_dex() < require["dex"] )
                        return notify_fail("����������㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["con"]) &&
                    owner->query_con() < require["con"] )
                        return notify_fail("��ĸ��ǲ��㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["int"]) &&
                    owner->query_int() < require["int"] )
                        return notify_fail("������Բ��㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["neili"]) &&
                    owner->query_dex() < require["neili"] )
                        return notify_fail("����������㣬�޷�װ���˷��ߡ�\n");
        }

        set_temp("armor/"+type, this_object(), owner);

        apply1 = keys(armor_prop);
        applied_prop=query_temp("apply", owner);
        if( !mapp(applied_prop) ) applied_prop = ([]);
        for( int i=0; i<sizeof(apply1); i++ )
                if( undefinedp(applied_prop[apply1[i]]) )
                        applied_prop[apply1[i]] = armor_prop[apply1[i]];
                else
                        applied_prop[apply1[i]] += armor_prop[apply1[i]];

        flag = 0;
        if( mapp(enchase_prop = copy(query("enchase/apply_prop"))) && sizeof(enchase_prop) ) {
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;

                        if( undefinedp(applied_prop[apply2[i]]) )
                                applied_prop[apply2[i]] = enchase_prop[apply2[i]];
                        else
                                applied_prop[apply2[i]] += enchase_prop[apply2[i]];
                }
        }
        if( mapp(enchase_prop = copy(query("enchase/rune_prop"))) && sizeof(enchase_prop) ) { // ��������
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;

                        if( undefinedp(applied_prop[apply2[i]]) )
                                applied_prop[apply2[i]] = enchase_prop[apply2[i]];
                        else
                                applied_prop[apply2[i]] += enchase_prop[apply2[i]];
                }
        }
        if( mapp(enchase_prop = copy(query("reform/apply_prop"))) && sizeof(enchase_prop) ) { // ����
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;

                        if( undefinedp(applied_prop[apply2[i]]) )
                                applied_prop[apply2[i]] = enchase_prop[apply2[i]];
                        else
                                applied_prop[apply2[i]] += enchase_prop[apply2[i]];
                }
        }
        if( mapp(enchase_prop = copy(query("qianghua/apply_prop"))) && sizeof(enchase_prop) ) {
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;

                        if( undefinedp(applied_prop[apply2[i]]) )
                                applied_prop[apply2[i]] = enchase_prop[apply2[i]];
                        else
                                applied_prop[apply2[i]] += enchase_prop[apply2[i]];
                }
        }
        set_temp("apply", applied_prop, owner);

        if( query("mod_level") )
                MODULE_D->equip_module(this_object(), owner);
        set("equipped", "worn");

        if( query("bindable") && query("bindable") == 1 &&
            !query("bind_owner") && userp(owner) ) {
                set("bind_owner",query("id", owner));
                set("set_data", 1);
                tell_object(owner, HIM "�����������ԼԼ�ĸ�Ӧ��" + this_object()->name() +
                                   HIM "������Ϊһ�塣\n" NOR);
        }

        // ս������Ч
        if( flag && !query_temp("warquest", owner) )
        {
                max_qi=query("max_qi", owner);
                max_jing=query("max_jing", owner);
                CHAR_D->setup_char(owner);
                if( query("eff_qi", owner) >= max_qi )
                        max_qi=query("max_qi", owner)-max_qi;
                else
                        max_qi = 0;
                if( query("eff_jing", owner) >= max_jing )
                        max_jing=query("max_jing", owner)-max_jing;
                else
                        max_jing = 0;
                addn("eff_qi", max_qi, owner);
                addn("eff_jing", max_jing, owner);
        }

        return 1;
}

varargs int wield(int left)
{
        object owner, old_weapon;
        mapping weapon_prop, enchase_prop;
        mapping require;
        string *apply1;
        string *apply2;
        string type;
        mixed no_wield;
        int flag, f;
        int max_qi, max_jing;

        if( !objectp(this_object()) ) return 0;
        // Only character object can wear armors.
        owner = environment();
        if( !owner || !owner->is_character() ) return 0;

        if( query("no_identify") )
                return notify_fail(this_object()->name() + "��Ҫ������ſ���ʹ�á�\n");

        // Does the consistence valid ?
        if( query("consistence") < 1 )
                return notify_fail(this_object()->name() + "������̫�����ˣ����ܼ���װ���ˡ�\n");

        // If already wielded, just recognize it.
        if( query("equipped") ) return 1;

        // If the item can not wield, I will return the fail message
        if( no_wield = query("no_wield") ) {
                // can not wield
                if( stringp(no_wield) )
                        return notify_fail(no_wield);
                else
                        return notify_fail("���������޷�װ����");
        }

        if( query("skill_type") == "throwing" )
                return notify_fail("����ֻ�������������װ����\n");

        // If handing it now, stop handing
        if( query_temp("handing", owner) == this_object() )
                delete_temp("handing", owner);

        // Check if we have "weapon_prop" defined.
        if( !mapp(weapon_prop = query("weapon_prop")) ||
            !stringp(query("skill_type")) )
                return notify_fail("��ֻ��װ���ɵ��������Ķ�����\n");

        if( userp(owner) && !wizardp(owner) &&
            (!query("reborn/times", owner) || query("id", owner) != this_object()->item_owner()) &&
            mapp(require = query("require")) && sizeof(require) ) {
                if( !undefinedp(require["level"]) &&
                    query("level", owner)<require["level"] )
                        return notify_fail("��ĵȼ��������޷�װ����������\n");

                if( !undefinedp(require["max_level"]) &&
                    query("level", owner)>require["max_level"] )
                        return notify_fail("��ĵȼ��������ޣ��޷�װ����������\n");

                if( !undefinedp(require["age"]) &&
                    query("age", owner)<require["age"] )
                        return notify_fail("������䲻�����޷�װ����������\n");

                if( !undefinedp(require["max_age"]) &&
                    query("age", owner)>require["max_age"] )
                        return notify_fail("������䳬�����ޣ��޷�װ����������\n");

                if( !undefinedp(require["str"]) &&
                    owner->query_str() < require["str"] )
                        return notify_fail("����������㣬�޷�װ����������\n");

                if( !undefinedp(require["dex"]) &&
                    owner->query_dex() < require["dex"] )
                        return notify_fail("����������㣬�޷�װ����������\n");

                if( !undefinedp(require["con"]) &&
                    owner->query_con() < require["con"] )
                        return notify_fail("��ĸ��ǲ��㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["int"]) &&
                    owner->query_int() < require["int"] )
                        return notify_fail("������Բ��㣬�޷�װ���˷��ߡ�\n");

                if( !undefinedp(require["neili"]) &&
                    owner->query_dex() < require["neili"] )
                        return notify_fail("����������㣬�޷�װ����������\n");
        }

        flag = query("flag"); // ˫��������־ 1:����˫�ֲ���װ��,2:���Բ�ͬ��װ��

        if( left ) { // ָ��������װ��������
                if( !(flag & SECONDARY) )
                        return 0;
                if( query_temp("secondary_weapon", owner) )
                        return 0;
                set_temp("secondary_weapon", this_object(), owner);
        }
        else if( flag & TWO_HANDED ) {
                if( query_temp("secondary_weapon", owner) ||
                    query_temp("weapon", owner) ||
                    query_temp("armor/hands", owner) ||
                    query_temp("armor/finger", owner) ||
                    query_temp("handing", owner) )
                        return notify_fail("�����ճ�˫�ֲ���װ����������\n");
                set_temp("weapon", this_object(), owner);
                set_temp("secondary_weapon", this_object(), owner);
        } else {
                if( query_temp("armor/hands", owner) &&
                    (query_temp("armor/finger", owner) ||
                     query_temp("handing", owner)) )
                        return notify_fail("�����ճ�һֻ�ֲ���װ����������\n");

                if( query_temp("armor/finger", owner) &&
                    (query_temp("armor/hands", owner) ||
                     query_temp("handing", owner)) )
                        return notify_fail("�����ճ�һֻ�ֲ���װ����������\n");

                // If we are are using any weapon?
                if( !(old_weapon=query_temp("weapon", owner)) )
                        set_temp("weapon", this_object(), owner);

                else // If we still have a free hand?
                if( !query_temp("secondary_weapon", owner) &&
                    !query_temp("armor/hands", owner) &&
                    !query_temp("armor/finger", owner) &&
                    !query_temp("handing", owner)){
                        // If we can wield this as secondary weapon?
                        if( flag & SECONDARY ) {
                                set_temp("secondary_weapon", this_object(), owner);
                        }
                        // If we can switch our old weapon to secondary weapon ?
                        else if( query("flag", old_weapon)&SECONDARY){
                                old_weapon->unequip();
                                set_temp("weapon", this_object(), owner);
                                old_weapon->wield();
                                message_vision("$N�����ֵ�$n�������֡�\n", owner, old_weapon);
                        // We require unwield our old weapon before we can use this one.
                        } else
                                return notify_fail("������ȷ�����Ŀǰװ����������\n");

                // We have both hands wearing something.
                } else
                        return notify_fail("�����ճ�һֻ����ʹ��������\n");
        }

        apply1 = keys(weapon_prop);
        for( int i = 0; i<sizeof(apply1); i++ )
                addn_temp("apply/"+apply1[i], weapon_prop[apply1[i]], owner);

        f = 0;
        if( mapp(enchase_prop = copy(query("enchase/apply_prop"))) && sizeof(enchase_prop) ) {
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                f = 1;
                        addn_temp("apply/"+apply2[i], enchase_prop[apply2[i]], owner);
                }
        }
        if( mapp(enchase_prop = copy(query("enchase/rune_prop"))) && sizeof(enchase_prop) ) { // ��������
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                f = 1;
                        addn_temp("apply/"+apply2[i], enchase_prop[apply2[i]], owner);
                }
        }
        if( mapp(enchase_prop = copy(query("reform/apply_prop"))) && sizeof(enchase_prop) ) { // ����
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                f = 1;
                        addn_temp("apply/"+apply2[i], enchase_prop[apply2[i]], owner);
                }
        }
        if( mapp(enchase_prop = copy(query("qianghua/apply_prop"))) && sizeof(enchase_prop) ) {
                apply2 = keys(enchase_prop);
                for( int i = 0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                f = 1;
                        addn_temp("apply/"+apply2[i], enchase_prop[apply2[i]], owner);
                }
        }

        if( query("mod_level") )
                MODULE_D->equip_module(this_object(), owner);

        owner->reset_action();
        set("equipped", "wielded");

        // modified by Lonely
        // bindable == 1 װ����
        if( query("bindable") && query("bindable") == 1 &&
            !query("bind_owner") && userp(owner) ) {
                set("bind_owner",query("id", owner));
                set("set_data", 1);
                tell_object(owner, HIM "�����������ԼԼ�ĸ�Ӧ��" + this_object()->name() +
                                   HIM "������Ϊһ�塣\n" NOR);
        }

        // ս������Ч
        if( f && !query_temp("warquest", owner) )
        {
                max_qi=query("max_qi", owner);
                max_jing=query("max_jing", owner);
                CHAR_D->setup_char(owner);
                if( query("eff_qi", owner) >= max_qi )
                        max_qi=query("max_qi", owner)-max_qi;
                else
                        max_qi = 0;
                if( query("eff_jing", owner) >= max_jing )
                        max_jing=query("max_jing", owner)-max_jing;
                else
                        max_jing = 0;
                addn("eff_qi", max_qi, owner);
                addn("eff_jing", max_jing, owner);
        }
        return 1;
}

int unequip()
{
        object owner, weapon;
        mapping prop1 = 0, prop2 = 0, prop3 = 0, prop4 = 0, prop5 = 0;
        mapping applied_prop;
        string *apply1;
        string *apply2;
        string equipped;
        int flag;

        if( !environment() ) return 0;

        if( !(owner = environment() )->is_character())
                return 0;

        if( !stringp(equipped = query("equipped")) )
                return notify_fail("��Ŀǰ��û��װ������������\n");

        if( equipped == "wielded" ) {
                if( query_temp("weapon", owner) == this_object()){
                        delete_temp("weapon", owner);
                        if( query_temp("secondary_weapon", owner) == this_object() )
                                delete_temp("secondary_weapon", owner);
                        if( objectp(weapon=query_temp("secondary_weapon", owner))){
                                weapon->unequip();
                                weapon->wield();
                        }
                }else if( query_temp("secondary_weapon", owner) == this_object()){
                        delete_temp("secondary_weapon", owner);
                }
                prop1 = query("weapon_prop");
                owner->reset_action();
        } else
        if( equipped == "worn" ) {
                delete_temp("armor/"+query("armor_type"), owner);
                prop1 = query("armor_prop");
        }

        prop2 = query("enchase/apply_prop");
        prop3 = query("enchase/rune_prop");
        prop4 = query("reform/apply_prop");
        prop5 = query("qianghua/apply_prop");

        applied_prop = query_temp("apply", owner);
        if( !mapp(applied_prop) ) applied_prop = ([]);
        if( mapp(prop1) && sizeof(prop1) ) {
                apply1 = keys(prop1);
                for( int i=0; i<sizeof(apply1); i++ )
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply1[i]] -= prop1[apply1[i]];
        }

        flag = 0;
        if( mapp(prop2) && sizeof(prop2) ) {
                apply2 = keys(prop2);
                for( int i=0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply2[i]] -= prop2[apply2[i]];
                }
        }
        if( mapp(prop3) && sizeof(prop3) ) {
                apply2 = keys(prop3);
                for( int i=0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply2[i]] -= prop3[apply2[i]];
                }
        }
        if( mapp(prop4) && sizeof(prop4) ) {
                apply2 = keys(prop4);
                for( int i=0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply2[i]] -= prop4[apply2[i]];
                }
        }

        if( mapp(prop5) && sizeof(prop5) ) {
                apply2 = keys(prop5);
                for( int i=0; i<sizeof(apply2); i++ ) {
                        if( apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing" )
                                flag = 1;
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply2[i]] -= prop5[apply2[i]];
                }
        }

        if( query("mod_level") )
                MODULE_D->unequip_module(this_object(), owner);

        delete("equipped");

        // ս������Ч
        if( flag && !query_temp("warquest", owner) ) CHAR_D->setup_char(owner);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed foo;

        foo = this_object()->weapon_hit_ob(me, victim, damage_bonus);

        ITEM_D->reduce_consistence(this_object(), me, victim, damage_bonus);

        if (! mapp(query_temp("daub")))
                return foo;

        COMBAT_D->hit_with_poison(me, victim, this_object());
        return foo;
}

// other one hit me as an armor
mixed valid_damage(object me, object victim, int damage_bonus)
{
        ITEM_D->reduce_consistence(this_object(), me, victim, damage_bonus);

        if( !mapp(query_temp("daub")) )
                return;

        if( query_temp("weapon", me) || query_temp("remote_attack", me) ||
            query("not_living", me)){
                // the attacker has weapon, or remote attack, or not living,
                // he won't be poisoned by my cloth or armor
                return;
        }

        COMBAT_D->hit_poison(me, victim, this_object());
        return;
}