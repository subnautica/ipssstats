#include "ptoc.h"
#include "graph.h"


boolean flag;
real value;
integer bigLoop, PercentM, IA;

real TotalBirths, TotalBirthsFemale, TotalBirthsMale, TotalMidPeriodPop, RF, TotalFertilityRate, RM, LifeExpMales, LifeExpFemales, SpecialEventTotalMales, SpecialEventTotalFemales;

real T1, TotalPopulationMales, TotalPopulationFemales, T2, TotalDeaths, TotalMigrantes;
/*T1=pop at time 1*/
/*T2=pop at time 2*/

integer NofAgeGroups, NGP1, J, NG1, I;
array<1,22,real> RF1;

integer index1;
real TheMax, MaxPercent, MaxWithinYear;

array<1,22,real> SpecialAgeEventMales, SpecialAgeEventFemales;

real NetReprodutionRate, Pop04, Popf1549, DependentPopUnder, DependentPopOver, IndependentPop, DependencyRatioTotal;
real GrossReprodRate, ChildMortalityRate, MaleFem12;
real TotalMigInMale, TotalMigInFemale, TotalMigOutMale, TotalMigOutFemale, MigrantesMale, MigrantesFemale;

real MdnAgeMale, MdnAgeFemale;
integer theSchedule;

real TotalBirths1, TotalBirths2, MidFage, TempGeneration, TempFemFert;
real PopNoDeathMale4, PopNoDeathFemale4, PopNoDeathMale3, PopNoDeathFemale3, PopNoDeathMale2, PopNoDeathFemale2;

void f3()
{
for( bigLoop = 1; bigLoop <= get_time(); bigLoop ++)  /*5  year projection each loop*/
                {

                        NofAgeGroups = TheLastGroup(bigLoop);  /*highest non zero pop cohort*/
                        NG1 = NofAgeGroups - 1;

/*initialize some totals*/
                        T1 = 0;
                        TotalBirths = 0.0;
                        TotalBirths1 = 0;
                        TotalBirths2 = 0;

                        TotalMigrantes = 0;
                        TotalPopulationMales = 0;
                        TotalPopulationFemales = 0;
                        TotalMidPeriodPop = 0;

                        for( I = 1; I <= NofAgeGroups; I ++)
                            {
                                    TotalPopulationMales = TotalPopulationMales + PR[bigLoop - 1].PopulationMale[I];
                                    TotalPopulationFemales = TotalPopulationFemales + PR[bigLoop - 1].PopulationFemale[I];
                            }

                        T1 = TotalPopulationMales + TotalPopulationFemales;


                        TotalPopulationMales = 0;
                        TotalPopulationFemales = 0;
                        SpecialEventTotalMales = 0;
                        SpecialEventTotalFemales = 0;


                        for( I = NG1; I >= 4; I --)  /*Calculate projected population  and special rates for cohorts 10-14 and up*/
                                {
                                        PR[bigLoop].PopulationMale[I] = (PR[bigLoop - 1].PopulationMale[I - 1] * SurvivalMaleInter(I - 1, bigLoop) + 0.25 * MigrationMaleInter(I - 1, bigLoop) * (1.0 + SurvivalMaleInter(I - 1, bigLoop)) + 0.25 * MigrationMaleInter(I, bigLoop) * (1.0 + SurvivalMaleInter(I, bigLoop)));
                                        TotalPopulationMales = TotalPopulationMales + PR[bigLoop].PopulationMale[I];
                                        PR[bigLoop].PopulationFemale[I] = (PR[bigLoop - 1].PopulationFemale[I - 1] * SurvivalFemaleInter(I - 1, bigLoop) + 0.25 * MigrationFemaleInter(I - 1, bigLoop) * (1.0 + SurvivalFemaleInter(I - 1, bigLoop)) + 0.25 * MigrationFemaleInter(I, bigLoop) * (1.0 + SurvivalFemaleInter(I, bigLoop)));
                                        TotalPopulationFemales = TotalPopulationFemales + PR[bigLoop].PopulationFemale[I];
                                        TotalMigrantes = TotalMigrantes + MigrationMaleInter(I, bigLoop) + MigrationFemaleInter(I, bigLoop);
                                        SpecialAgeEventMales[I] = PR[bigLoop].PopulationMale[I] * SpecialMaleInter(I, bigLoop);
                                        SpecialAgeEventFemales[I] = PR[bigLoop].PopulationFemale[I] * SpecialFemaleInter(I, bigLoop);
                                        SpecialEventTotalMales = SpecialEventTotalMales + SpecialAgeEventMales[I];
                                        SpecialEventTotalFemales = SpecialEventTotalFemales + SpecialAgeEventFemales[I];
                                }

                        /*Calculate projected population for eldest cohort*/
                        PR[bigLoop].PopulationMale[NofAgeGroups] = ((PR[bigLoop - 1].PopulationMale[NofAgeGroups] + PR[bigLoop - 1].PopulationMale[NG1]) * SurvivalMaleInter(NofAgeGroups, bigLoop)) + (0.5 * MigrationMaleInter(NG1, bigLoop) * (1.0 + (real)(SurvivalMaleInter(NG1, bigLoop)) / 2)) + (MigrationMaleInter(NofAgeGroups, bigLoop) * (1.0 + (real)(SurvivalMaleInter(NofAgeGroups, bigLoop)) / 2));
                        PR[bigLoop].PopulationFemale[NofAgeGroups] = ((PR[bigLoop - 1].PopulationFemale[NofAgeGroups] + PR[bigLoop - 1].PopulationFemale[NG1]) * SurvivalFemaleInter(NofAgeGroups, bigLoop)) + (0.5 * MigrationFemaleInter(NG1, bigLoop) * (1.0 + (real)(SurvivalFemaleInter(NG1, bigLoop)) / 2)) + (MigrationFemaleInter(NofAgeGroups, bigLoop) * (1.0 + (real)(SurvivalFemaleInter(NofAgeGroups, bigLoop)) / 2));

                        TotalPopulationFemales = TotalPopulationFemales + PR[bigLoop].PopulationFemale[NofAgeGroups];
                        TotalPopulationMales = TotalPopulationMales + PR[bigLoop].PopulationMale[NofAgeGroups];
                        TotalMigrantes = TotalMigrantes + MigrationMaleInter(NofAgeGroups, bigLoop) + MigrationFemaleInter(NofAgeGroups, bigLoop) + MigrationMaleInter(1, bigLoop) + MigrationFemaleInter(1, bigLoop) + MigrationMaleInter(2, bigLoop) + MigrationFemaleInter(2, bigLoop) + MigrationMaleInter(3, bigLoop) + MigrationFemaleInter(3, bigLoop);

/*Calculate total births- 5 year*/
                        for( I = 1; I <= 9; I ++)
                                {
                                        TotalBirths1 = TotalBirths1 + (FertilityRateInter(I + 3, bigLoop) * PR[bigLoop].PopulationFemale[i + 3]);
                                        TotalBirths2 = TotalBirths2 + (FertilityRateInter(I + 3, bigLoop - 1) * PR[bigLoop - 1].PopulationFemale[i + 3]);
                                }
                        TotalBirths = (TotalBirths1 + TotalBirths2) * 2.5;

                        /*-----------------------------------------------------------------------*/
/*         calculate births(TotalBirths), deaths(TotalDeaths), total population(TotalPopulationMales & TotalPopulationFemales)*/
/*-----------------------------------------------------------------------*/

/*Calc total births male and female- 1 year*/
                        TotalBirthsFemale = TotalBirths / (5 * (1.0 + SexRatioBirthInter(bigLoop)));
                        TotalBirthsMale = TotalBirthsFemale * SexRatioBirthInter(bigLoop);

/*Calculate projected population for newborns -cohort 0-1*/
                        PR[bigLoop].PopulationMale[1] = (TotalBirthsMale * SurvivalMaleInter(1, bigLoop) + 0.25 * MigrationMaleInter(1, bigLoop) * (1.0 + SurvivalMaleInter(2, bigLoop)));
                        PR[bigLoop].PopulationFemale[1] = (TotalBirthsFemale * SurvivalFemaleInter(1, bigLoop) + 0.25 * MigrationFemaleInter(1, bigLoop) * (1.0 + SurvivalFemaleInter(2, bigLoop)));

/*This section calculates for age cohorts 1-4 & 5-9*/
                        PR[bigLoop].PopulationMale[3] = PR[bigLoop - 1].PopulationMale[1] * SurvivalMaleInter(2, bigLoop) + PR[bigLoop - 1].PopulationMale[2] * SurvivalMaleInter(2, bigLoop) + 0.25 * MigrationMaleInter(2, bigLoop) * (1.0 + SurvivalMaleInter(2, bigLoop)) + 0.25 * MigrationMaleInter(3, bigLoop) * (1.0 + SurvivalMaleInter(3, bigLoop));
                        PR[bigLoop].PopulationMale[2] = PR[bigLoop].PopulationMale[1] * 4 * SurvivalMaleInter(2, bigLoop) + 0.25 * MigrationMaleInter(1, bigLoop) * (1.0 + SurvivalMaleInter(1, bigLoop)) + 0.25 * MigrationMaleInter(2, bigLoop) * (1.0 + SurvivalMaleInter(1, bigLoop));
                        PR[bigLoop].PopulationFemale[3] = PR[bigLoop - 1].PopulationFemale[1] * SurvivalFemaleInter(2, bigLoop) + PR[bigLoop - 1].PopulationFemale[2] * SurvivalFemaleInter(2, bigLoop) + 0.25 * MigrationFemaleInter(2, bigLoop) * (1.0 + SurvivalFemaleInter(2, bigLoop)) + 0.25 * MigrationFemaleInter(3, bigLoop) * (1.0 + SurvivalFemaleInter(3, bigLoop));
                        PR[bigLoop].PopulationFemale[2] = PR[bigLoop].PopulationFemale[1] * 4 * SurvivalFemaleInter(2, bigLoop) + 0.25 * MigrationFemaleInter(1, bigLoop) * (1.0 + SurvivalFemaleInter(1, bigLoop)) + 0.25 * MigrationFemaleInter(2, bigLoop) * (1.0 + SurvivalFemaleInter(1, bigLoop));


                        TotalPopulationMales = TotalPopulationMales + PR[bigLoop].PopulationMale[2] + PR[bigLoop].PopulationMale[3];
                        TotalPopulationFemales = TotalPopulationFemales + PR[bigLoop].PopulationFemale[2] + PR[bigLoop].PopulationFemale[3];


/*Calculate special rates for cohorta 0-1, 1-4, 5-9*/
                        SpecialAgeEventMales[1] = PR[bigLoop].PopulationMale[1] * SpecialMaleInter(1, bigLoop);
                        SpecialAgeEventFemales[1] = PR[bigLoop].PopulationFemale[1] * SpecialFemaleInter(1, bigLoop);
                        SpecialAgeEventMales[2] = PR[bigLoop].PopulationMale[2] * SpecialMaleInter(2, bigLoop);
                        SpecialAgeEventFemales[2] = PR[bigLoop].PopulationFemale[2] * SpecialFemaleInter(2, bigLoop);
                        SpecialAgeEventMales[3] = PR[bigLoop].PopulationMale[3] * SpecialMaleInter(3, bigLoop);
                        SpecialAgeEventFemales[3] = PR[bigLoop].PopulationFemale[3] * SpecialFemaleInter(3, bigLoop);
                        SpecialAgeEventMales[NofAgeGroups] = PR[bigLoop].PopulationMale[NofAgeGroups] * SpecialMaleInter(NofAgeGroups, bigLoop);
                        SpecialAgeEventFemales[NofAgeGroups] = PR[bigLoop].PopulationFemale[NofAgeGroups] * SpecialFemaleInter(NofAgeGroups, bigLoop);
                        SpecialEventTotalMales = SpecialEventTotalMales + SpecialAgeEventMales[1] + SpecialAgeEventMales[2] + SpecialAgeEventMales[3] + SpecialAgeEventMales[NofAgeGroups];
                        SpecialEventTotalFemales = SpecialEventTotalFemales + SpecialAgeEventFemales[1] + SpecialAgeEventFemales[2] + SpecialAgeEventFemales[3] + SpecialAgeEventFemales[NofAgeGroups];



                        TotalPopulationMales = TotalPopulationMales + PR[bigLoop].PopulationMale[1];
                        TotalPopulationFemales = TotalPopulationFemales + PR[bigLoop].PopulationFemale[1];
                        T2 = TotalPopulationMales + TotalPopulationFemales;
                        TotalDeaths = T1 - T2 + TotalMigrantes + (TotalBirths);

                        /*----------------------------------------------------------------------*/
/*          calculate crude vital rates (CBR & CDR), */
/*           and growth rates (RNG & RG)*/
/*----------------------------------------------------------------------*/
                        PR[bigLoop].Parameters[3] = TotalBirths / (2.5 * (T1 + T2)) * 1000; /*Crude Birth rate*/
                        PR[bigLoop].Parameters[4] = TotalDeaths / (2.5 * (T1 + T2)) * 1000; /*Crude Death rate*/
                        PR[bigLoop].Parameters[1] = 100 * (T2 - T1) / (2.5 * (T1 + T2)); /*Rate of Growth*/

                        PR[bigLoop].Parameters[2] = (real)((PR[bigLoop].Parameters[3] - PR[bigLoop].Parameters[4])) / 10; /*Natural Increase Rate*/
                        PR[bigLoop].Parameters[41] = TotalBirths - TotalDeaths;  /*Natural Increase abs*/


/*---------------------------------------------------------------------*/
/*          calculate total and general fertility rates (TotalFertilityRate & GFR)*/
/*          and NetReprodutionRate                                                                      */
/*---------------------------------------------------------------------*/
                        RF = 0.0;
                        NetReprodutionRate = 0;
                        TotalFertilityRate = 0.0;
                        MidFage = 17.5;
                        TempGeneration = 0;
                        TempFemFert = 0;
                        if (TotalBirths == 0) 
                                NetReprodutionRate = 0;
                        else
                                for( I = 1; I <= 6; I ++)
                                        {
                                                RF = RF + PR[bigLoop].PopulationFemale[I + 4] + PR[bigLoop - 1].PopulationFemale[I + 4];
                                                TotalFertilityRate = TotalFertilityRate + FertilityRateInter(I + 4, bigLoop) + FertilityRateInter(I + 4, bigLoop - 1);
                                                NetReprodutionRate = NetReprodutionRate + FertilityRateInter(I + 4, bigLoop) * 5 * ((real)(TotalBirthsFemale) / (TotalBirthsMale + TotalBirthsFemale)) * SurvivalFemaleInter(I + 4, bigLoop);
                                                TempGeneration = TempGeneration + MidFage * FertilityRateInter(I + 4, bigLoop) * 5 * ((real)(TotalBirthsFemale) / (TotalBirthsMale + TotalBirthsFemale)) * SurvivalFemaleInter(I + 4, bigLoop);
                                                TempFemFert = TempFemFert + (real)(MidFage * (FertilityRateInter(I + 4, bigLoop) + FertilityRateInter(I + 4, bigLoop - 1))) / 2;
                                                MidFage = MidFage + 5;
                                        }

 PR[bigLoop].Parameters[42] = TempGeneration / NetReprodutionRate; //{Length Generation}			
 PR[bigLoop].Parameters[43] = TempFemFert / (TotalFertilityRate / 2); //{Mean Age of Childbearing}

 PR[bigLoop].Parameters[5] = (TotalBirths / (RF * 2.5)) * 1000; //{General fertility rate}			
 TotalFertilityRate = TotalFertilityRate * 1000;			
 PR[bigLoop].Parameters[6] = TotalFertilityRate * 2.5;			
 PR[bigLoop].Parameters[12] = NetReprodutionRate * 1000;


/*---------------------------------------------------------------------*/
/*          calculate life expectancy at birth (LifeExpMales  &  LifeExpFemales)*/
/*---------------------------------------------------------------------*/

/*males*/
                        RM = (1 * SurvivalMaleInter(1, bigLoop) + 4 * SurvivalMaleInter(2, bigLoop));
                        LifeExpMales = RM;
                        flag = true;
                        I = 3;
                        while ((flag == true) && (I <= NG1)) 
                                {
                                        value = (SurvivalMaleInter(I + 1, bigLoop) - 0.001);
                                        if (value < 0) 
                                                flag = false;

                                        if (flag) 
                                                {
                                                        RM = RM * SurvivalMaleInter(I, bigLoop);
                                                        LifeExpMales = LifeExpMales + RM;
                                                        I = I + 1;
                                                }
                                }
                        LifeExpMales = LifeExpMales + ((RM * SurvivalMaleInter(I, bigLoop)) / (1.0 - SurvivalMaleInter(I, bigLoop)));

/*females*/
                        RF = (1 * SurvivalFemaleInter(1, bigLoop) + 4 * SurvivalFemaleInter(2, bigLoop));
                        LifeExpFemales = RF;
                        flag = true;
                        i = 3;
                        while ((flag == true) && (i <= NG1)) 
                                {
                                        value = (SurvivalFemaleInter(I + 1, bigLoop) - 0.001);
                                        if (value < 0) 
                                                flag = false;

                                        if (flag == true) 
                                                {
                                                        RF = RF * SurvivalFemaleInter(I, bigLoop);
                                                        LifeExpFemales = LifeExpFemales + RF;
                                                        I = I + 1;
                                                }
                                }
                        LifeExpFemales = LifeExpFemales + ((RF * SurvivalFemaleInter(I, bigLoop)) / (1.0 - SurvivalFemaleInter(I, bigLoop)));

                        PR[bigLoop].Parameters[7] = LifeExpMales;
                        PR[bigLoop].Parameters[8] = LifeExpFemales;
                        PR[bigLoop].Parameters[9] = T2;
                        PR[bigLoop].Parameters[10] = TotalPopulationMales;
                        PR[bigLoop].Parameters[11] = TotalPopulationFemales;

/*InfantMortality*/
                        if (TotalBirths == 0) 
                                PR[bigLoop].Parameters[13] = 0;
                        else
                                PR[bigLoop].Parameters[13] = (((real)(((TotalBirthsMale + TotalBirthsFemale) - (TotalBirthsMale * SurvivalMaleInter(1, bigLoop) + TotalBirthsFemale * SurvivalFemaleInter(1, bigLoop)))) / (TotalBirthsMale + TotalBirthsFemale))) * 1000;




/*ChildWomanRatio*/
                        Pop04 = 0;
                        Popf1549 = 0;
                        for( i = 1; i <= 2; i ++)
                                Pop04 = Pop04 + PR[bigLoop].PopulationMale[i] + PR[bigLoop].PopulationFemale[i];
                        for( i = 5; i <= 11; i ++)
                                Popf1549 = Popf1549 + PR[bigLoop].PopulationFemale[i];
                        PR[bigLoop].Parameters[14] = (real)(Pop04) / Popf1549 * 1000; /*ChildWomanRatio*/


/*Dependency*/
                        DependentPopUnder = 0;
                        DependentPopOver = 0;
                        IndependentPop = 0;
                        for( i = 1; i <= 4; i ++)
                                DependentPopUnder = DependentPopUnder + PR[bigLoop].PopulationMale[i] + PR[bigLoop].PopulationFemale[i];
                        for( i = 15; i <= 22; i ++)
                                DependentPopOver = DependentPopOver + PR[bigLoop].PopulationMale[i] + PR[bigLoop].PopulationFemale[i];
                        for( i = 5; i <= 14; i ++)
                                IndependentPop = IndependentPop + PR[bigLoop].PopulationMale[i] + PR[bigLoop].PopulationFemale[i];
                        DependencyRatioTotal = (real)((DependentPopUnder + DependentPopOver)) / IndependentPop * 100;
                        PR[bigLoop].Parameters[15] = DependencyRatioTotal;


/*DependencyRatioAged*/
                        PR[bigLoop].Parameters[16] = (real)(DependentPopOver) / IndependentPop * 100;

/*DependencyRatioYouth*/
                        PR[bigLoop].Parameters[17] = (real)(DependentPopUnder) / IndependentPop * 100;

/*DoublingTime*/
                        PR[bigLoop].Parameters[18] = 69.3 / PR[bigLoop].Parameters[1];  /*rate of growth*/


/*GrossReprodRate */
                        PR[bigLoop].Parameters[19] = (TotalFertilityRate * 2.5) * TotalBirthsFemale / (TotalBirthsMale + TotalBirthsFemale);

/*PctDemTransComp*/
                        PR[bigLoop].Parameters[20] = 50 * ((real)((235 - PR[bigLoop].Parameters[5])) / 175 + (real)((7500 - TotalFertilityRate)) / 5300);

/*Pop%Under*/
                        PR[bigLoop].Parameters[21] = (real)(DependentPopUnder) / T2 * 100;

/*Pop%Over*/
                        PR[bigLoop].Parameters[22] = (real)(DependentPopOver) / T2 * 100;

/*ChildMortalityRate*/
                        PopNoDeathMale4 = PR[bigLoop - 1].PopulationMale[3] + 0.5 * MigrationMaleInter(3, bigLoop) + 0.5 * MigrationMaleInter(4, bigLoop);
                        PopNoDeathFemale4 = PR[bigLoop - 1].PopulationFemale[3] + 0.5 * MigrationFemaleInter(3, bigLoop) + 0.5 * MigrationFemaleInter(4, bigLoop);
                        PopNoDeathMale3 = PR[bigLoop - 1].PopulationMale[1] + PR[bigLoop - 1].PopulationMale[2] + 0.5 * MigrationMaleInter(2, bigLoop) + 0.5 * MigrationMaleInter(3, bigLoop);
                        PopNoDeathFemale3 = PR[bigLoop - 1].PopulationFemale[1] + PR[bigLoop - 1].PopulationFemale[2] + 0.5 * MigrationFemaleInter(2, bigLoop) + 0.5 * MigrationFemaleInter(3, bigLoop);
                        PopNoDeathMale2 = PR[bigLoop].PopulationMale[1] * 4 + 0.5 * MigrationMaleInter(1, bigLoop) + 0.5 * MigrationMaleInter(2, bigLoop);
                        PopNoDeathFemale2 = PR[bigLoop].PopulationFemale[1] * 4 + 0.5 * MigrationFemaleInter(1, bigLoop) + 0.5 * MigrationFemaleInter(2, bigLoop);
                        MaleFem12 = PR[bigLoop].PopulationMale[2] + PR[bigLoop].PopulationFemale[2] + PR[bigLoop].PopulationMale[3] + PR[bigLoop].PopulationFemale[3] + PR[bigLoop].PopulationMale[4] + PR[bigLoop].PopulationFemale[4];
                        ChildMortalityRate = (real)((PopNoDeathMale4 + PopNoDeathFemale4 + PopNoDeathMale3 + PopNoDeathFemale3 + PopNoDeathMale2 + PopNoDeathFemale2 - MaleFem12)) / MaleFem12;
                        PR[bigLoop].Parameters[23] = ChildMortalityRate * 1000;

/*Totals for special events*/
                        PR[bigLoop].Parameters[24] = SpecialEventTotalMales + SpecialEventTotalFemales;
                        PR[bigLoop].Parameters[25] = SpecialEventTotalFemales;
                        PR[bigLoop].Parameters[26] = SpecialEventTotalMales;

/*Migration Variables*/
                        TotalMigInMale = 0;
                        TotalMigInFemale = 0;
                        TotalMigOutMale = 0;
                        TotalMigOutFemale = 0;
                        for( i = 1; i <= 22; i ++)
                                {
                                        MigrantesMale = MigrationMaleInter(i, bigLoop);
                                        MigrantesFemale = MigrationFemaleInter(i, bigLoop);
                                        if (MigrantesMale > 0) 
                                                TotalMigInMale = TotalMigInMale + MigrantesMale;
                                        else
                                                TotalMigOutMale = TotalMigOutMale + MigrantesMale;

                                        if (MigrantesFemale > 0) 
                                                TotalMigInFemale = TotalMigInFemale + MigrantesFemale;
                                        else
                                                TotalMigOutFemale = TotalMigOutFemale + MigrantesFemale;

                                }

/* Mig. Rate Female In*/
                        PR[bigLoop].Parameters[27] = (real)(TotalMigInFemale) / TotalPopulationFemales * 1000;

/* Mig. Rate Female Out*/
                        PR[bigLoop].Parameters[28] = (real)(TotalMigOutFemale) / TotalPopulationFemales * 1000;

/* Mig. Rate  Gross*/
                        PR[bigLoop].Parameters[29] = (abs(TotalMigOutFemale + TotalMigOutMale) + TotalMigInMale + TotalMigInFemale) / T2 * 1000;

/* Mig. Rate Male In*/
                        PR[bigLoop].Parameters[30] = (real)(TotalMigInMale) / TotalPopulationMales * 1000;

/* Mig. Rate Male Out*/
                        PR[bigLoop].Parameters[31] = (real)(TotalMigOutMale) / TotalPopulationMales * 1000;

/* Mig. Rate Net*/
                        PR[bigLoop].Parameters[32] = (real)((TotalMigOutFemale + TotalMigOutMale + TotalMigInMale + TotalMigInFemale)) / T2 * 1000;

/*Mig. Rate-Total In*/
                        PR[bigLoop].Parameters[33] = (real)((TotalMigInMale + TotalMigInFemale)) / T2 * 1000;

/*Mig. Rate-Total Out*/
                        PR[bigLoop].Parameters[34] = (real)((TotalMigOutMale + TotalMigOutFemale)) / T2 * 1000;

/*Sex Ratio at Birth*/
                        PR[bigLoop].Parameters[35] = SexRatioBirthInter(bigLoop);


/*Median Age*/
                        MdnAgeMale = 0;
                        MdnAgeFemale = 0;
                        for( i = 3; i <= 21; i ++)
                                {
                                        MdnAgeMale = MdnAgeMale + PR[bigLoop].PopulationMale[i] * (2 + 5 * (i - 2));
                                        MdnAgeFemale = MdnAgeFemale + PR[bigLoop].PopulationFemale[i] * (2 + 5 * (i - 2));
                                }
                        MdnAgeMale = MdnAgeMale + PR[bigLoop].PopulationMale[2] * 2;  /*2= (1+4)/2 x4/5*/
                        MdnAgeFemale = MdnAgeFemale + PR[bigLoop].PopulationFemale[2] * 2;
                        MdnAgeMale = MdnAgeMale + PR[bigLoop].PopulationMale[22] * 104.5;
                        MdnAgeFemale = MdnAgeFemale + PR[bigLoop].PopulationFemale[22] * 104.5;
                        PR[bigLoop].Parameters[36] = (MdnAgeMale + MdnAgeFemale) / (T2 + 0.00005);
                        MdnAgeMale = MdnAgeMale / (TotalPopulationMales + 0.00005);
                        MdnAgeFemale = MdnAgeFemale / (TotalPopulationFemales + 0.00005);
                        PR[bigLoop].Parameters[37] = MdnAgeMale;
                        PR[bigLoop].Parameters[38] = MdnAgeFemale;

/*Total Births*/
                        PR[bigLoop].Parameters[39] = TotalBirths;
/*Total Deaths*/
                        PR[bigLoop].Parameters[40] = TotalDeaths;


/*Calculate Global Max and Max within year*/
                        MaxWithinYear = 0;
                        for( i = 1; i <= 22; i ++)
                                {
                                        if (PR[bigLoop].PopulationMale[i] > TheMax) 
                                                TheMax = PR[bigLoop].PopulationMale[i];
                                        if (PR[bigLoop].PopulationFemale[i] > TheMax) 
                                                TheMax = PR[bigLoop].PopulationFemale[i];
                                        if (PR[bigLoop].PopulationMale[i] > MaxWithinYear) 
                                                MaxWithinYear = PR[bigLoop].PopulationMale[i];
                                        if (PR[bigLoop].PopulationFemale[i] > MaxWithinYear) 
                                                MaxWithinYear = PR[bigLoop].PopulationFemale[i];
                                }
/*first 2 cohorts are added together so check max of addition*/
                        if ((PR[bigLoop].PopulationMale[1] + PR[bigLoop].PopulationMale[2]) > TheMax) 
                                TheMax = PR[bigLoop].PopulationMale[1] + PR[bigLoop].PopulationMale[2];
                        if ((PR[bigLoop].PopulationFemale[1] + PR[bigLoop].PopulationFemale[2]) > TheMax) 
                                TheMax = PR[bigLoop].PopulationFemale[1] + PR[bigLoop].PopulationFemale[2];

                        if ((PR[bigLoop].PopulationMale[1] + PR[bigLoop].PopulationMale[2]) > MaxWithinYear) 
                                MaxWithinYear = (PR[bigLoop].PopulationMale[1] + PR[bigLoop].PopulationMale[2]);
                        if ((PR[bigLoop].PopulationFemale[1] + PR[bigLoop].PopulationFemale[2]) > MaxWithinYear) 
                                MaxWithinYear = (PR[bigLoop].PopulationFemale[1] + PR[bigLoop].PopulationFemale[2]);


                        if (T2 != 0) 
                                if (((real)(MaxWithinYear) / T2) > MaxPercent) 
                                        MaxPercent = ((real)(MaxWithinYear) / T2);

/*-----------------------------------------------------------------*/
/*            return to calling program*/
/*-----------------------------------------------------------------*/

        absMax = TheMax;
        percMax = MaxPercent;



    }
}



