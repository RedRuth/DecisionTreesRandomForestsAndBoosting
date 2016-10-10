//
//  FeatureEnumerations.h
//  
//
//  Created by Varun Natu on 10/10/16.
//
//

#ifndef FeatureEnumerations_h
#define FeatureEnumerations_h

enum workClass{
    PRIVATE,
    SELF_EMPLOYED_NOT_INCLUDED,
    SELF_EMPLOYED,INC,
    FEDEREAL_GOV,
    LOCAL_GOV,
    STATE_GOV,
    WITHOUT_PAY,
    NEVER_WORKED
};

enum education{
    BACHELORS,
    SOME_COLLEGE,
    ELEVENTH,
    HS_GRAD,
    PROF_SCHOOL,
    ASSOC_ACDM,
    ASSOC_VOC,
    NINTH,
    SEVENTH_EIGHTH,
    TWELFTH,
    MASTERS,
    FIRST_FOURTH,
    TENTH,
    DOCTORATE,
    FIFTH_SIXTH,
    PRESCHOOL
};

enum maritalStatus{
    MARRIED_CIV_SPOUSE,
    DIVORCED,
    NEVER_MARRIED,
    SEPARATED,
    WIDOWED,
    MARRIED_SPOUCE_ABSENT,
    MARRIED_AF_SPOUSE
};

enum occupation{
    TECH_SUPPORT,
    CRAFT_REPAIR,
    OTHER_SERVICE,
    SALES,
    EXEC_MANAGERIAL,
    PROF_SPECIALTY,
    HANDLER_CLEANERS,
    MACHINE_OP_INSPCT,
    ADM_CLERICAL,
    FARMING_FISHING,
    TRANSPORT_MOVING,
    PRIVATE_HOUSE_SERVICE,
    PROTECTIVE_SERVICES,
    ARMED_FORCES
};

enum relationship{
    WIFE,
    OWN_CHILD,
    HUDBAND,
    NOT_IN_FAMILY,
    OTHER_RELATIVE,
    UNMARRIED
    
};

enum race{
    WHITE,
    ASIAN_PAC_ISLANDER,
    AMER_INDIAN_ESKIMO,
    OTHER,
    BLACK
};

enum sex{
    MALE,
    FEMALE
};

enum nativeCountry{
    UNITED_STATES,
    CAMBODIA,
    ENGLAND,
    PUERTO_RICO,
    CANADA,
    GERMANY,
    OUTLYING_US,
    INDIA,
    JAPAN,
    GREECE,
    SOUTH,
    CHINA,
    CUBA,
    IRAN,
    HONDURAS,
    PHILIPPINES,
    ITALY,
    POLAND,
    JAMAICA,
    VIETNAM,
    MEXICO,
    PORTUGAL,
    IRELAND,
    FRANCE,
    DOMINICAN_REPUBLIC,
    LAOS,
    ECUADOR,
    TAIWAN,
    HAITI,
    COLUMBIA,
    HUNGARY,
    GUATEMALA,
    NICARAGUA,
    SCOTLAND,
    THAILAND,
    YUGOSLAVIA,
    EL_SALVADOR,
    TRINIDAD_AND_TOBAGO,
    PERU,
    HONG,
    HOLAND_NETHERLANDS
};
#endif /* FeatureEnumerations_h */
