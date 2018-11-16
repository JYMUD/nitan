// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// identifyd.c

#include <ansi.h>

#pragma optimize
#pragma save_binary

mapping gems = ([
        "ruby":         "�챦ʯ",
        "topaz":        "�Ʊ�ʯ",
        "sapphire":     "����ʯ",
        "emerald":      "�����",
        "amethyst":     "��ˮ��",
        "diamond":      "ˮ����",
        "skull":        "����ͷ",
]);
mapping gems_color = ([
        "ruby":         HIR,
        "topaz":        HIY,
        "sapphire":     HIB,
        "emerald":      HIG,
        "amethyst":     MAG,
        "diamond":      HIW,
        "skull":        WHT,
]);

string *gems_level = ({
        "ϸ���",
        "",
        "ϡ��",
        "��֮",
});

string *gems_level_id = ({
        "chipped",
        "",
        "flawless",
        "magic",
});

string query_gem_name(string socket, int level) 
{
        return sprintf("%s%s%s"NOR, gems_color[socket], gems_level[level - 1], gems[socket]); 
}

string query_gem_id(string socket, int level) 
{
        if( gems_level_id[level - 1] == "" ) return socket; 
        return sprintf("%s %s", gems_level_id[level - 1], socket); 
}

mixed identify_ob(object me, object ob)
{
        int     i, level, mf;
        string  filename, name, id, *my_id;
        string  gem, s;
        mixed   obj;
        mapping data, temp;
        
        level = query("level", ob); // ֻ�б�ʯ���࣬û�еȼ�
        if( !level )
        {
                mf = query_temp("magic_find", me);
                i = random(100);
                i += mf;
                if (i < 50) { level = 1; s = "c"; }
                else if (i < 75) { level = 2; s = ""; }
                else if (i < 95) { level = 3; s = "f"; }
                else { level = 4; s = "m"; }
                gem = query("id", ob);
                filename = s+gem;
                id = query_gem_id(gem, level);
                name = query_gem_name(gem, level);
                my_id = ({ id });
        } else
        {
                id = query("id", ob);
                name = query("name", ob);
                my_id = ob->my_id();
                filename = query("material", ob);
        }

        temp = ([]);
        data = ([]);
        temp["weapon_prop"] = EQUIPMENT_D->apply_gem_prop("weapon", level, level-1);
        temp["armor_prop"] = EQUIPMENT_D->apply_gem_prop("armor", level, level-1);
        temp["rings_prop"] = EQUIPMENT_D->apply_gem_prop("rings", level, level-1);
        temp["SN"] = 1 + random(9);
        temp["type"] = "all";
        data["enchase"] = temp;
        data["name"] = name;

        obj = TEMPLATE_D->create_object("/inherit/template/gem/" + filename, id, data, 1);
        obj->set_name(name, my_id);

        return obj;
}

// ������Ʒ->�Ϲ���Ʒ->�й���Ʒ->Զ����Ʒ->̫����Ʒ
// ̫ʼ��̫����̫�� ̫�顢���
// ڤ���桢̫���桢Ԫ�����������
// ����Ԫ�����ֻ���Ϊ��Ԫ�Ŵ�����Ԫ�Ŵ�����Ԫ�Ŵ���
// �����滮�ֹ�����������������������
varargs int identify_ultimate_ob(object item, int close)
{
        mapping data, prop;
        string *apply;
        mixed inset;
        int i, n, sn;
        int r_effect, d_effect, p_effect;

        r_effect = 0;
        d_effect = 0;
        p_effect = 0;

        sn=query("enchase/SN", item);
        if( sn == 37 && !query("ultimate/37", item) )
        {
                addn("enchase/apply_prop/research_effect", 10, item);
                if( query("enchase/apply_prop/research_effect", item)>40 )
                        set("enchase/apply_prop/research_effect", 40, item);
                addn("enchase/apply_prop/practice_effect", 10, item);
                if( query("enchase/apply_prop/practice_effect", item)>40 )
                        set("enchase/apply_prop/practice_effect", 40, item);
                addn("enchase/apply_prop/derive_effect", 10, item);
                if( query("enchase/apply_prop/derive_effect", item)>40 )
                        set("enchase/apply_prop/derive_effect", 40, item);
                addn("enchase/flute", 1, item);
                addn("enchase/SN", -(random(9)+1), item);
                set("ultimate/37", 1, item);
                item->save();
                return 1;
        } else
        if( sn == 39 && !query("ultimate/39", item) )
        {
                addn("enchase/apply_prop/research_effect", 15, item);
                if( query("enchase/apply_prop/research_effect", item)>40 )
                        set("enchase/apply_prop/research_effect", 40, item);
                addn("enchase/apply_prop/practice_effect", 15, item);
                if( query("enchase/apply_prop/practice_effect", item)>40 )
                        set("enchase/apply_prop/practice_effect", 40, item);
                addn("enchase/apply_prop/derive_effect", 15, item);
                if( query("enchase/apply_prop/derive_effect", item)>40 )
                        set("enchase/apply_prop/derive_effect", 40, item);
                addn("enchase/flute", 1, item);
                set("ultimate/39", 1, item);
                item->save();
                return 1;
        } else
        if( sn == 69 && !query("ultimate/69", item )
         && query("armor_type", item) && query("armor_type", item) != "hands"
         && query("armor_type", item) != "finger" )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] = data[apply[i]] * 3 / 2;

                inset=query("enchase/inset", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = r_effect * 3 / 2;
                data["derive_effect"] = d_effect * 3 / 2;
                data["practice_effect"] = p_effect * 3 / 2;

                data["reduce_busy"]     = EQUIPMENT_D->query_prop_value("reduce_busy", 1 + random(2));
                data["avoid_busy"]      = EQUIPMENT_D->query_prop_value("avoid_busy", 1 + random(4));
                data["def_damage"]       = EQUIPMENT_D->query_prop_value("def_damage", 1 + random(6));
                data["avoid_weak"]     = EQUIPMENT_D->query_prop_value("avoid_weak", 1 + random(4));
                data["add_locked"]= EQUIPMENT_D->query_prop_value("add_locked", 1 + random(4));
                data["reduce_damage"]   = EQUIPMENT_D->query_prop_value("reduce_damage", 1 + random(3));

                set("enchase/apply_prop", data, item);
                set("ultimate/69", 1, item);
                set("ultimate/ob", 1, item);
                item->save();

                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "��˵�Ϲ���Ʒ" + item->name() + HIM +
                              "�������˼䡣");


                log_file("static/ultimate", sprintf("%s Have 69 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 87 && !query("ultimate/87", item) )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                if (item->is_weapon() || item->is_unarmed_weapon())
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] = data[apply[i]] * 3 / 2;

                        inset=query("enchase/inset", item);
                        if (!inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                                {
                                        if (!undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (!undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (!undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }
                        if( r_effect ) r_effect = 30 + r_effect * 3 / 2;
                        if( d_effect ) d_effect = 30 + d_effect * 3 / 2;
                        if( p_effect ) p_effect = 30 + p_effect * 3 / 2;
                        data["research_effect"] = r_effect;
                        data["derive_effect"] = d_effect;
                        data["practice_effect"] = p_effect;

                        data["add_busy"]        = EQUIPMENT_D->query_prop_value("add_busy", 1 + random(5));
                        data["add_weak"]    = EQUIPMENT_D->query_prop_value("add_weak", 1 + random(3));
                        data["avoid_locked"] = EQUIPMENT_D->query_prop_value("avoid_locked", 1 + random(3));
                        data["add_damage"] = EQUIPMENT_D->query_prop_value("add_damage", 1 + random(3));
                        data["add_skill"]  += EQUIPMENT_D->query_prop_value("add_skill", 1 + random(4));

                        set("enchase/apply_prop", data, item);
                        set("ultimate/87", 1, item);

                        if (!close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "��˵�Ϲ���Ʒ" + item->name() + HIM +
                                "�������˼䡣");

                } else
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] *= 2;


                        inset=query("enchase/inset", item);
                        if (!inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                                {
                                        if (!undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (!undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (!undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }

                        if( r_effect ) r_effect = 40 + r_effect * 2;
                        if( d_effect ) d_effect = 40 + d_effect * 2;
                        if( p_effect ) p_effect = 40 + p_effect * 2;
                        data["research_effect"] = r_effect;
                        data["derive_effect"] = d_effect;
                        data["practice_effect"] = p_effect;

                        data["reduce_busy"]     = 6;
                        data["avoid_busy"]      = 16;
                        data["def_damage"]      = 2000;
                        data["avoid_weak"]     = 16;
                        data["add_locked"]= 16;
                        data["reduce_damage"]   = 16;
                        set("enchase/apply_prop", data, item);
                        set("ultimate/87", 1, item);

                        if (!close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "��˵Զ����Ʒ" + item->name() + HIM +
                                "�������˼䡣");
                }

                set("ultimate/ob", 1, item);
                item->save();
                log_file("static/ultimate", sprintf("%s Have 87 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 105 && !query("ultimate/105", item) )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 2;

                inset=query("enchase/inset", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }

                if( r_effect ) r_effect = 120 + r_effect * 2;
                if( d_effect ) d_effect = 120 + d_effect * 2;
                if( p_effect ) p_effect = 120 + p_effect * 2;
                data["research_effect"] = r_effect;
                data["derive_effect"] = d_effect;
                data["practice_effect"] = p_effect;

                data["add_busy"]        = 16;
                data["add_weak"]    = 40;
                data["avoid_locked"] = 40;
                data["add_damage"]      = 80;
                data["add_skill"]  = 500;

                set("enchase/apply_prop", data, item);
                set("ultimate/105", 1, item);
                set("ultimate/ob", 1, item);
                item->save();
                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "��˵Զ����Ʒ" + item->name() + HIM +
                              "�������˼䡣");

                log_file("static/ultimate", sprintf("%s Have 105 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
        if( sn == 121 && !query("ultimate/121", item) )
        {
                data=query("enchase/apply_prop", item);
                if (!mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 3;

                inset=query("enchase/inset", item);
                if (!inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (!undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (!undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (!undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = 2000 + r_effect * 3;
                data["derive_effect"] = 2000 + d_effect * 3;
                data["practice_effect"] = 2000 + p_effect * 3;

                data["add_busy"]        = 36;
                data["add_weak"]    = 96;
                data["avoid_locked"] = 96;
                data["add_damage"]      = 200;
                data["add_skill"]  = 1000;
                data["avoid_armor"] = 96;
                data["add_freeze"] = 96;
                data["avoid_freeze"] = 96;
                data["add_lethargy"] = 96;
                data["avoid_lethargy"] = 96;
                data["add_chaos"] = 96;
                data["avoid_chaos"] = 96;
                data["final_kill"] = 96;
                data["full_self"] = 96;
                data["avoid_call"] = 96;

                data["magic_find"] = 100;
                data["add_reward"] = 100;
                data["gold_find"] = 100;

                data["reduce_busy"]     = 32;
                // data["avoid_busy"]      = 96;
                data["def_damage"]       = 100000;
                data["avoid_weak"]     = 96;
                data["add_locked"]= 96;
                data["reduce_damage"]   = 96;

                data["ap_power"]        = 200;
                data["dp_power"]        = 200;
                data["da_power"]        = 200;
                data["avoid_parry"]     = 96;
                data["avoid_dodge"]     = 96;
                data["avoid_attack"]    = 96;

                set("enchase/apply_prop", data, item);
                set("ultimate/121", 1, item);
                set("ultimate/ob", 1, item);
                item->save();
                if (!close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "��˵̫����Ʒ" + item->name() + HIM +
                              "�������˼䡣");

                log_file("static/ultimate", sprintf("%s Have 121 SN. Wash %d Times. %s\n",
                          base_name(item),query("enchase/wash", item),TIME_D->replace_ctime(time())));
                return 1;
        } else
                return 0;
}
