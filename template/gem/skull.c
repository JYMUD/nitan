// jewel.c
#include <ansi.h>
#include <template.h>

inherit TEMPLATE_OB;

mixed *dbase_format = ({ "long", "value", "enchase", });

// ģ������
mapping template_data = ([
        "skull1"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ, ��Щ���ơ�\n" NOR,              80000,
                                ([ "SN" : random(9) + 1, "level" : 1, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull1.c"
                          }),
        "skull2"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ��������ȱ��˿�����ơ�\n" NOR,    10000,
                                ([ "SN" : random(9) + 1, "level" : 2, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull2.c"
                          }),
        "skull3"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ�������Բ�ͬѰ���ĸо���\n" NOR,  12000,
                                ([ "SN" : random(9) + 1, "level" : 3, "consistence" : 70 + random(31), ]), 
                              }), ([ ]), BASIC_OB_DIR + "gem/skull3.c"
                          }),
        "skull4"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ�����˸е�һ������ļ¡�\n" NOR,  14000,
                                ([ "SN" : random(9) + 1, "level" : 4, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull4.c"
                          }),
        "skull5"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ�����˸е�һ������ļ¡�\n" NOR,  16000,
                                ([ "SN" : random(9) + 1, "level" : 5, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull5.c"
                          }),
        "skull6"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ�����˸е�һ������ļ¡�\n" NOR,  18000,
                                ([ "SN" : random(9) + 1, "level" : 6, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull6.c"
                          }),
        "skull7"    : ({ ({ BLU "һ��ð������ɫ��â������ͷ�����˸е�һ������ļ¡�\n" NOR,  20000,
                                ([ "SN" : random(9) + 1, "level" : 7, "consistence" : 80 + random(21), ]),
                              }), ([ ]), BASIC_OB_DIR + "gem/skull7.c"
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
        // ����׼�ļ�Ϊ "/inherit/template/gem/skull.c"��
        set_base_file("gem/skull");

        // ���� dbase ��ʽ
        set_dbase_format(dbase_format);

        // ����ģ������
        set_template_data(template_data);

        ::setup();
}

