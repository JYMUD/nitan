#include <ansi.h>

object book = find_object("/clone/book/qiankun_book");

object get_owner()
{
        object owner;
        if(objectp(book)) {
                owner = environment(book);
                if( !objectp(owner) ) return 0;
                if(owner->is_character()) return owner;
        }
        return 0;
}

object book_owner = get_owner();

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return "���޼ɣ�...............ȥ���ɣ�";
}

nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"ĳ��";

nosave mixed *story = ({
        "���̻���ʹ�ߣ�����������˵Ǭ���ķ�������͵���ˡ�����",
        "���޼ɣ��ס��������̵ģ��ҵ�������͵�������úú����ң�",
        "�������¿�ʼȫ��Ѱ�Ҵ���......",
        "���޼ɵ�����ô�Ҳ������أ���˭������˭͵����ô��",
        "���̻���ʹ�ߣ������������Ǹ�" + book_owner_name + "͵ȥ�ˡ�",
        "���޼ɵ���������ô����˵����������ɽ��ȥ����",
        "���޼�����" + book_owner_name + "��ǰ��",
        book_owner_name + "�������ܣ��ɱ����˸����š�",
                "���޼ɣ�%��*������������*��%��###��*������%*",
                "���޼ɣ�����С�ӣ���Ȼ��͵�����̵�Ǭ���ķ���",
        "���޼�ʹ������Ǭ�������ķ���" + book_owner_name + "��ʱ���ŵİ�����",
        book_owner_name + "���У�������Ǭ���ķ�ô�����˻����㡣",
        book_owner_name + "�ͳ���Ƥ�鶪�����޼ɡ�",
        (: get_book :),
        book_owner_name + "�����޼ɴ����ˡ�",
        "���޼ɿ������ĵĻص����̡�",
});

string prompt() { return HIW "���������¡�" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
