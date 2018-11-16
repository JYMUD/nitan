// jewel.c
#include <ansi.h>
#include <template.h>

inherit TEMPLATE_OB;

mixed *dbase_format = ({ "long", "value", "enchase", });

// ģ������
mapping template_data = ([
        "red gem1"    : ({ ({ RED "һƬ��ʯ��Ƭ��\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem1.c" 
                          }),
        "red gem2"    : ({ ({ RED "һ���������ľ�����ʯ�������쳣��\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem2.c" 
                          }),
        "red gem3"    : ({ ({ RED "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem3.c" 
                          }),
        "red gem4"    : ({ ({ RED "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem4.c" 
                          }),
        "red gem5"    : ({ ({ RED "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem5.c" 
                          }),
        "red gem6"    : ({ ({ RED "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem6.c" 
                          }),
        "red gem7"    : ({ ({ RED "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/redgem7.c" 
                          }),
        "grn gem1"    : ({ ({ GRN "һƬ��ʯ��Ƭ��\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem1.c" 
                          }),
        "grn gem2"    : ({ ({ GRN "һ���������ľ�����ʯ�������쳣��\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem2.c"  
                          }),
        "grn gem3"    : ({ ({ GRN "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem3.c" 
                          }),
        "grn gem4"    : ({ ({ GRN "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem4.c" 
                          }),       
        "grn gem5"    : ({ ({ GRN "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem5.c" 
                          }),
        "grn gem6"    : ({ ({ GRN "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem6.c" 
                          }),
        "grn gem7"    : ({ ({ GRN "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  20000,                                 
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/grngem7.c" 
                          }),
        "yel gem1"    : ({ ({ YEL "һƬ��ʯ��Ƭ��\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem1.c" 
                          }),
        "yel gem2"    : ({ ({ YEL "һ���������ľ�����ʯ�������쳣��\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem2.c"
                          }),
        "yel gem3"    : ({ ({ YEL "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem3.c"
                          }),
        "yel gem4"    : ({ ({ YEL "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem4.c"
                          }),
        "yel gem5"    : ({ ({ YEL "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem5.c"
                          }),
        "yel gem6"    : ({ ({ YEL "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem6.c"
                          }),
        "yel gem7"    : ({ ({ YEL "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/yelgem7.c"
                          }),
        "blu gem1"    : ({ ({ BLU "һƬ��ʯ��Ƭ��\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem1.c"
                          }),
        "blu gem2"    : ({ ({ BLU "һ���������ľ�����ʯ�������쳣��\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem2.c"
                          }),
        "blu gem3"    : ({ ({ BLU "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem3.c"
                          }),
        "blu gem4"    : ({ ({ BLU "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem4.c"
                          }),
        "blu gem5"    : ({ ({ BLU "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem5.c"
                          }),
        "blu gem6"    : ({ ({ BLU "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem6.c"
                          }),
        "blu gem7"    : ({ ({ BLU "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/blugem7.c"
                          }),
        "mag gem1"    : ({ ({ MAG "һƬ��ʯ��Ƭ��\n" NOR,                                    80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem1.c"
                          }),
        "mag gem2"    : ({ ({ MAG "һ���������ľ�����ʯ�������쳣��\n" NOR,                10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem2.c"
                          }),
        "mag gem3"    : ({ ({ MAG "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���\n" NOR,    12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem3.c"
                          }),
        "mag gem4"    : ({ ({ MAG "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem4.c"
                          }),
        "mag gem5"    : ({ ({ MAG "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem5.c"
                          }),
        "mag gem6"    : ({ ({ MAG "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem6.c"
                          }),
        "mag gem7"    : ({ ({ MAG "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/maggem7.c"
                          }),
]);

// ��ʼ��ģ��
void create()
{
        setup();
}

// �����������Ƿ�ʹ��ȫ��ʽģʽ���ʽ��Ӧģʽ
void setup()
{
        // ����׼�ļ�Ϊ "/inherit/template/gem/gem.c"��
        set_base_file("gem/gem");

        // ���� dbase ��ʽ
        set_dbase_format(dbase_format);

        // ����ģ������
        set_template_data(template_data);

        ::setup();
}
