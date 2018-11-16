// common.h

// ��ͨ��Ʒ�б�

// weapon : ����
// sword��: ��
// knife��: ذ��
// axe����: ��ͷ
// mace�� : ��
// club�� : ��
// bow����: ��
// javelin: ��ǹ
// spear��: ì
// hammer : ��

// equip��: װ��
// helmet : ͷ��
// armor��: ����
// shield : ��
// gloves : ����
// boots��: ѥ��
// belt�� : ����
// ring�� : ��ָ
// amulet : ����
// charm��: ���� - �ش�, ����, С��
// other��: ����

mapping common_list = ([
        "weapon" : ([   "sword" : ([ "short sword": "�̽�", "scimitar" : "�䵶",
���������������������������������� "sabre"������: "��", "fachion"��: "���µ�",
���������������������������������� "long sword" : "����", "war sword": "ս��",
���������������������������������� "crystal sword"��: "ˮ����", "broad sword"��: "����",
���������������������������������� "two-hand sword" : "˫�ֽ�", "claymore"���� : "˫�е�",
���������������������������������� "giant sword"����: "�޽�",�� "bastard sword": "���н�",
���������������������������������� "flamberge"������: "���潣", "great sword"��: "���˽�", ]),

                        "knife" : ([ "dagger" : "�̽�",�� "dirk"��: "ذ��",
���������������������������������� "kris"�� : "���н�", "blade" : "��",
���������������������������������� "throwing knife" : "Ͷ����", "balanced knife" : "ƽ�⵶", ]),

                        "axe"�� : ([ "hand exe"�� : "�ָ�",�� "axe"���������� : "��", 
���������������������������������� "double exe" : "˫�и�", "military pick" : "ս��",
���������������������������������� "war axe"����: "ս��",�� "large axe"���� : "��",
���������������������������������� "broad axe"��: "��",�� "battle axe"����: "ս��",
���������������������������������� "great axe"��: "�޸�",�� "giant axe"���� : "�޸�", ]),

                        "mace"��: ([ "mace" : "��", "morning star" : "������", "flail" : "����", ]),
����������������������
                        "club"��: ([ "club" : "��", "spiked club"��: "����", ]),
����������������������
                        "bow"�� : ([ "short bow" : "�̹�", "hunter's bow"��: "�Թ�",
                        "long bow"��: "����", "composite bow" : "���Ϲ�",
���������������������������������� "short battle bow" : "��ս��", "long battle bow" : "��ս��",
���������������������������������� "short war bow"����: "��ս��", "long war bow"����: "��ս��", ]),

                        "javelin" : ([ "javelin"��������: "��ǹ", "pilum"��: "�ر�ǹ",
������������������������������������ "short spear"����: "��ì", "glaive" : "��",
������������������������������������ "throwing spear" : "��ì", ]),

                        "spear"�� : ([ "spear"������ : "ì",�� "trident" : "�����",
������������������������������������ "brandistock" : "��ì", "spetum"��: "��ì",
������������������������������������ "pike"��������: "��ǹ", ]), ]),

        "helmet" : ([ "cap"������ : "ñ��",�� "skull cap"��: "ͷ��", "helm"��: "ͷ��", 
��������������        "full helm" : "ȫͷ��", "great helm" : "�޿�", "crown" : "��",
��������������������  "mask"������: "���",�� "bone helm"��: "�ǿ�", ]),

������  "armor"��: ([ "quilted armor"������: "���",�� "leather armor" : "Ƥ��",
������������������    "hard leather armor" : "ӲƤ��", "studded armor" : "����",
��������������������  "ring mail"����������: "����",�� "scale mail"����: "�ۼ�",
��������������������  "chain mail"�������� : "���Ӽ�", "breast plate"��: "�ؼ�",
������������������    "splint mail"��������: "�ټ�",�� "plate mail"����: "�ְ��",
��������������������  "field plate"��������: "Ƭ��",�� "gothic plate"��: "���ؼ�",
��������������������  "full plate mail"����: "ȫ���", "ancient armor" : "�ɼ�",
��������������������  "light plate"��������: "���", ]),

        "shield" : ([ "buckler"������: "С԰��", "small shield"��: "С��",
��������������������  "large shield" : "���",�� "kite shield"�� : "����",
��������������������  "tower shield" : "ƽ��",�� "gothic shield" : "���ض�",
��������������������  "bone shield"��: "�Ƕ�",�� "spiked shield" : "����", ]),

        "gloves" : ([ "leather gloves" : "Ƥ����", "heavy gloves"����: "������",
��������������������  "chain gloves"�� : "������", "light gauntlets" : "��������",
��������������������  "gauntlets"������: "������", ]),

        "boots"��: ([ "boots"������ : "ѥ��",�� "heavy boots"��������: "��ѥ",
��������������������  "chain boots" : "����ѥ", "light plated boots" : "����ѥ",
��������������������  "greaves"���� : "���ּ�", ]),

        "belt"�� : ([ "sash" : "����", "light belt" : "������",
��������������������  "belt" : "����", "heavy belt" : "������",
��������������������  "plated belt" : "������", ]),

        "ring"�� : "��ָ",
        "amulet" : "�����",

        "charm"��: ([ "grand charm" : "��������", "large charm" : "������",
��������������������  "small charm" : "С����", ]),

        "potion" : ([ "healing"��: ([ "minor healing potion"�� : "С����ƿ",
������������������������������������  "light healing potion"�� : "������ƿ",
������������������������������������  "healing potion"�������� : "������ƿ",
������������������������������������  "greater healing potion" : "������ƿ",
������������������������������������  "super healing potion"�� : "�ؼ�����ƿ", ]),
��������������������  "mana"���� : ([ "minor mana potion"�� : "Сħ��ƿ",
������������������������������������  "light mana potion"�� : "��ħ��ƿ",
������������������������������������  "mana potion"�������� : "��ħ��ƿ",
������������������������������������  "greater mana potion" : "��ħ��ƿ",
������������������������������������  "super mana potion"�� : "�ؼ�ħ��ƿ", ]),
��������������������  "antidote potion" : "�ⶾ��",
��������������������  "thawing potion"��: "�ⶳ��", ]),

        "key"�� : "Կ��",
        "jewel" : "�鱦",
]);

// ��Ʒ���ֵļ���
array common_rate_table = ({ "weapon", "potion", "armor", "helmet", "shield",
������������������������������ "key", "gloves", "boots", "belt", "ring", "amulet",
������������������������������ "charm", "jewel", });

static int max_rate;

int *common_rate_list = ({ 120, 100, 100, 80, 80, 70, 60, 60, 60, 20, 20, 20, 10, });
