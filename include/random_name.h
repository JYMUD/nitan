string *surname = ({
"��","Ǯ","��","��","��","��","֣","��","��","¬","����","��","��","����",
"��","��","ţ","��","��","��","��","��","³","��","��","��","��","��","��",
"ʷ","��","��","��","��","��","��","��","��","��","��","��","κ","��","��",
"ŷ��","��","��","��","��","��","Ѧ","��","��","��","��","��","ͯ","��",
"��","��","��","֣","��","��","��","��","��","ʯ","ʱ","��","��","��","��",
"��","ξ��","��","��","��","��","��","��","ë","��","��","ʩ","��","��",
"��","��","��","��","��","��","��",
});
string *manname1 = ({
"����","����","���","����","��Ȥ","���","����","�Կ�","����","�ĺ�",
"����","����","��»","����","���","����","����","ʮ��","ʮһ��","����",
"��ţ","����","����","����","��ţ","���","��","���","����","����",
"��","��","��","��","��","˳","��","��","��","ʨ","��","����","����",
"���","����","����","ʤ","��","ƽ","��","���","����",
});
string *nickname1 =({
"����","̫��","����","��ɽ","�ɷ�","�׻�","����","����","�ƺ�","����",
"��ɽ","�䵱","��","����","����","������","ɱ��","��ţ","���","����һ",
"����һ","����","���","����","����","����","����","ϧ��","����","����",
"����","����","���","����","����","��Ӣ","����","��ɱ","���ջ�","�����п�",
"�����޻�","ʫ��","ɱ������",
});
string *nickname2 =({
"��","��","ǹ","�","��","��","��",
});

string comm_man_name()
{
        return surname[ random ( sizeof ( surname ) ) ] +
        manname1[ random ( sizeof(manname1 ) ) ];
}

string comm_man_nick()
{
        return nickname1[ random( sizeof( nickname1 ) ) ] +
        nickname2[ random (sizeof ( nickname2 ) ) ];
}

