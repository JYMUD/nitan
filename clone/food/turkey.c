// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 

inherit ITEM;
inherit F_FOOD;

string *names= ({
  "�࿾��",
  "��Ѭ��",
  "�����",
});

string *parts= ({
  "����",
  "��С����",
  "�𼦴�����",
  "�𼦳����",
  "�𼦱�����",
  "�𼦸�����",
  "�𼦾�����",
  "��ƨ����",
  "��ͷ",
  "����",
  "�𼦸�",
  "�𼦳�",
  "���峦",
  "�����߰�����",
  "����ͷ��",
  "���߹�",
  "�𼦾���",
  "�𼦳��",
  "���ȹ�",
});

void create()
{
  string name = "��";
  set_name(name, ({"turkey"}));
  set_weight(1000);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "һֻ˶��ĸж��ڻ𼦡�\n");
    set("unit", "ֻ");
    set("value", 950);
    set("food_remaining", 30);
    set("food_supply", 10);
  }
  setup();
}

int do_get (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! arg)
    return 0;

  if (present(arg,environment(who))==me)
  {
    tell_object(who,
     "ι�������ô�ҳԻ��������������������ͷ���Ե����ӣ�\n");
    return 1;
  }
  return 0;
}
