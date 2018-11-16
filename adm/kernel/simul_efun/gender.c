// gender.c

#include <gender.h>
#include <pronoun.h>

string gender_self(string sex)
{
        switch(sex) {
                case "Ů��": return "��";       break;
                default: return "��";
        }
}

string gender_pronoun(string sex)
{
        switch(sex) {
                case "������":  return "��";    break;
                case "�ɽ�":    return "��";    break;
                case "����":    return "��";    break;
                case "����":    return "��";    break;
                case "Ů��":    return "��";    break;
                case "����":
                case "����":    return "��";    break;
                default: return "��";
        }
}


// �˳ƴ�����
string pnoun(int pronoun_number, mixed arg)
{
        if( objectp(arg) ) 
                arg = query("gender", arg);
        
        switch(pronoun_number)
        {
                case FIRST_PERSONAL:    
                        return FIRST_PERSONAL_PRONOUN;
                
                case SECOND_PERSONAL: 
                        switch( arg )
                        {
                                case MALE_GENDER:       return SECOND_PERSONAL_PRONOUN_MALE;    break;
                                case FEMALE_GENDER:     return SECOND_PERSONAL_PRONOUN_FEMALE;  break;
                                default:                return SECOND_PERSONAL_PRONOUN_DEFAULT; break;
                        }

                case THIRD_PERSONAL:    
                        if( undefinedp(arg) )
                                return THIRD_PERSONAL_PRONOUN_ANIMAL;     
                        switch( arg )
                        {
                                case MALE_GENDER:       return THIRD_PERSONAL_PRONOUN_MALE;     break;
                                case FEMALE_GENDER:     return THIRD_PERSONAL_PRONOUN_FEMALE;   break;
                                case ANIMAL_GENDER:     return THIRD_PERSONAL_PRONOUN_ANIMAL;   break;
                                default:                return THIRD_PERSONAL_PRONOUN_DEFAULT;  break;
                        }
                default:
                        error("�����˳ƴ����ʡ�\n");
        }
}

