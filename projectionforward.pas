procedure f3;

var

		flag: boolean;
		value: real;
		bigLoop, PercentM, IA: Integer;

		TotalBirths, TotalBirthsFemale, TotalBirthsMale, TotalMidPeriodPop, RF, TotalFertilityRate, RM, LifeExpMales, LifeExpFemales, SpecialEventTotalMales, SpecialEventTotalFemales: single;

		T1, TotalPopulationMales, TotalPopulationFemales, T2, TotalDeaths, TotalMigrantes: single;
{T1=pop at time 1}
{T2=pop at time 2}

		NofAgeGroups, NGP1, J, NG1, I: Integer;
		RF1: array[1..22] of single;

		index: integer;
		TheMax, MaxPercent, MaxWithinYear: real;

		dataH: GraphDHandle;
		WD: WData;
		SpecialAgeEventMales, SpecialAgeEventFemales: array[1..22] of single;

		NetReprodutionRate, Pop04, Popf1549, DependentPopUnder, DependentPopOver, IndependentPop, DependencyRatioTotal: real;
		GrossReprodRate, ChildMortalityRate, MaleFem12: real;
		TotalMigInMale, TotalMigInFemale, TotalMigOutMale, TotalMigOutFemale, MigrantesMale, MigrantesFemale: real;

		MdnAgeMale, MdnAgeFemale: real;
		theSchedule: integer;

		TotalBirths1, TotalBirths2, MidFage, TempGeneration, TempFemFert: single;
		PopNoDeathMale4, PopNoDeathFemale4, PopNoDeathMale3, PopNoDeathFemale3, PopNoDeathMale2, PopNoDeathFemale2: single;
begin


{------------------------------------------------------------------}
{                 start projection                                                                     }
{------------------------------------------------------------------}

	for BigLoop := 1 to time do  {5  year projection each loop}
		begin

			NofAgeGroups := TheLastGroup(BigLoop); {highest non zero pop cohort}
			NG1 := NofAgeGroups - 1;

{initialize some totals}
			T1 := 0;
			TotalBirths := 0.0;
			TotalBirths1 := 0;
			TotalBirths2 := 0;

			TotalMigrantes := 0;
			TotalPopulationMales := 0;
			TotalPopulationFemales := 0;
			TotalMidPeriodPop := 0;

{Calculate totals at base year}
			for I := 1 to NofAgeGroups do
				begin
					TotalPopulationMales := TotalPopulationMales + PR[BigLoop - 1].PopulationMale[I];
					TotalPopulationFemales := TotalPopulationFemales + PR[BigLoop - 1].PopulationFemale[I];
				end;

{T1= total pop at base year}
			T1 := TotalPopulationMales + TotalPopulationFemales;


			TotalPopulationMales := 0;
			TotalPopulationFemales := 0;
			SpecialEventTotalMales := 0;
			SpecialEventTotalFemales := 0;


			for I := NG1 downto 4 do  {Calculate projected population  and special rates for cohorts 10-14 and up}
				begin
					PR[BigLoop].PopulationMale[I] := (PR[BigLoop - 1].PopulationMale[I - 1] * SurvivalMaleInter(I - 1, BigLoop) + 0.25 * MigrationMaleInter(I - 1, BigLoop) * (1.0 + SurvivalMaleInter(I - 1, BigLoop)) + 0.25 * MigrationMaleInter(I, BigLoop) * (1.0 + SurvivalMaleInter(I, BigLoop)));
					TotalPopulationMales := TotalPopulationMales + PR[BigLoop].PopulationMale[I];
					PR[BigLoop].PopulationFemale[I] := (PR[BigLoop - 1].PopulationFemale[I - 1] * SurvivalFemaleInter(I - 1, BigLoop) + 0.25 * MigrationFemaleInter(I - 1, BigLoop) * (1.0 + SurvivalFemaleInter(I - 1, BigLoop)) + 0.25 * MigrationFemaleInter(I, BigLoop) * (1.0 + SurvivalFemaleInter(I, BigLoop)));
					TotalPopulationFemales := TotalPopulationFemales + PR[BigLoop].PopulationFemale[I];
					TotalMigrantes := TotalMigrantes + MigrationMaleInter(I, BigLoop) + MigrationFemaleInter(I, BigLoop);
					SpecialAgeEventMales[I] := PR[BigLoop].PopulationMale[I] * SpecialMaleInter(I, BigLoop);
					SpecialAgeEventFemales[I] := PR[BigLoop].PopulationFemale[I] * SpecialFemaleInter(I, BigLoop);
					SpecialEventTotalMales := SpecialEventTotalMales + SpecialAgeEventMales[I];
					SpecialEventTotalFemales := SpecialEventTotalFemales + SpecialAgeEventFemales[I];
				end;

{Calculate projected population for eldest cohort}
			PR[BigLoop].PopulationMale[NofAgeGroups] := ((PR[BigLoop - 1].PopulationMale[NofAgeGroups] + PR[BigLoop - 1].PopulationMale[NG1]) * SurvivalMaleInter(NofAgeGroups, BigLoop)) + (0.5 * MigrationMaleInter(NG1, BigLoop) * (1.0 + SurvivalMaleInter(NG1, BigLoop) / 2)) + (MigrationMaleInter(NofAgeGroups, BigLoop) * (1.0 + SurvivalMaleInter(NofAgeGroups, BigLoop) / 2));
			PR[BigLoop].PopulationFemale[NofAgeGroups] := ((PR[BigLoop - 1].PopulationFemale[NofAgeGroups] + PR[BigLoop - 1].PopulationFemale[NG1]) * SurvivalFemaleInter(NofAgeGroups, BigLoop)) + (0.5 * MigrationFemaleInter(NG1, BigLoop) * (1.0 + SurvivalFemaleInter(NG1, BigLoop) / 2)) + (MigrationFemaleInter(NofAgeGroups, BigLoop) * (1.0 + SurvivalFemaleInter(NofAgeGroups, BigLoop) / 2));

			TotalPopulationFemales := TotalPopulationFemales + PR[BigLoop].PopulationFemale[NofAgeGroups];
			TotalPopulationMales := TotalPopulationMales + PR[BigLoop].PopulationMale[NofAgeGroups];
			TotalMigrantes := TotalMigrantes + MigrationMaleInter(NofAgeGroups, BigLoop) + MigrationFemaleInter(NofAgeGroups, BigLoop) + MigrationMaleInter(1, BigLoop) + MigrationFemaleInter(1, BigLoop) + MigrationMaleInter(2, BigLoop) + MigrationFemaleInter(2, BigLoop) + MigrationMaleInter(3, BigLoop) + MigrationFemaleInter(3, BigLoop);

{Calculate total births- 5 year}
			for I := 1 to 9 do
				begin
					TotalBirths1 := TotalBirths1 + (FertilityRateInter(I + 3, BigLoop) * PR[BigLoop].PopulationFemale[i + 3]);
					TotalBirths2 := TotalBirths2 + (FertilityRateInter(I + 3, BigLoop - 1) * PR[BigLoop - 1].PopulationFemale[i + 3]);
				end;
			TotalBirths := (TotalBirths1 + TotalBirths2) * 2.5;


{-----------------------------------------------------------------------}
{         calculate births(TotalBirths), deaths(TotalDeaths), total population(TotalPopulationMales & TotalPopulationFemales)}
{-----------------------------------------------------------------------}

{Calc total births male and female- 1 year}
			TotalBirthsFemale := TotalBirths / (5 * (1.0 + SexRatioBirthInter(BigLoop)));
			TotalBirthsMale := TotalBirthsFemale * SexRatioBirthInter(BigLoop);

{Calculate projected population for newborns -cohort 0-1}
			PR[BigLoop].PopulationMale[1] := (TotalBirthsMale * SurvivalMaleInter(1, BigLoop) + 0.25 * MigrationMaleInter(1, BigLoop) * (1.0 + SurvivalMaleInter(2, BigLoop)));
			PR[BigLoop].PopulationFemale[1] := (TotalBirthsFemale * SurvivalFemaleInter(1, BigLoop) + 0.25 * MigrationFemaleInter(1, BigLoop) * (1.0 + SurvivalFemaleInter(2, BigLoop)));

{This section calculates for age cohorts 1-4 & 5-9}
			PR[BigLoop].PopulationMale[3] := PR[BigLoop - 1].PopulationMale[1] * SurvivalMaleInter(2, BigLoop) + PR[BigLoop - 1].PopulationMale[2] * SurvivalMaleInter(2, BigLoop) + 0.25 * MigrationMaleInter(2, BigLoop) * (1.0 + SurvivalMaleInter(2, BigLoop)) + 0.25 * MigrationMaleInter(3, BigLoop) * (1.0 + SurvivalMaleInter(3, BigLoop));
			PR[BigLoop].PopulationMale[2] := PR[BigLoop].PopulationMale[1] * 4 * SurvivalMaleInter(2, BigLoop) + 0.25 * MigrationMaleInter(1, BigLoop) * (1.0 + SurvivalMaleInter(1, BigLoop)) + 0.25 * MigrationMaleInter(2, BigLoop) * (1.0 + SurvivalMaleInter(1, BigLoop));
			PR[BigLoop].PopulationFemale[3] := PR[BigLoop - 1].PopulationFemale[1] * SurvivalFemaleInter(2, BigLoop) + PR[BigLoop - 1].PopulationFemale[2] * SurvivalFemaleInter(2, BigLoop) + 0.25 * MigrationFemaleInter(2, BigLoop) * (1.0 + SurvivalFemaleInter(2, BigLoop)) + 0.25 * MigrationFemaleInter(3, BigLoop) * (1.0 + SurvivalFemaleInter(3, BigLoop));
			PR[BigLoop].PopulationFemale[2] := PR[BigLoop].PopulationFemale[1] * 4 * SurvivalFemaleInter(2, BigLoop) + 0.25 * MigrationFemaleInter(1, BigLoop) * (1.0 + SurvivalFemaleInter(1, BigLoop)) + 0.25 * MigrationFemaleInter(2, BigLoop) * (1.0 + SurvivalFemaleInter(1, BigLoop));


			TotalPopulationMales := TotalPopulationMales + PR[BigLoop].PopulationMale[2] + PR[BigLoop].PopulationMale[3];
			TotalPopulationFemales := TotalPopulationFemales + PR[BigLoop].PopulationFemale[2] + PR[BigLoop].PopulationFemale[3];


{Calculate special rates for cohorta 0-1, 1-4, 5-9}
			SpecialAgeEventMales[1] := PR[BigLoop].PopulationMale[1] * SpecialMaleInter(1, BigLoop);
			SpecialAgeEventFemales[1] := PR[BigLoop].PopulationFemale[1] * SpecialFemaleInter(1, BigLoop);
			SpecialAgeEventMales[2] := PR[BigLoop].PopulationMale[2] * SpecialMaleInter(2, BigLoop);
			SpecialAgeEventFemales[2] := PR[BigLoop].PopulationFemale[2] * SpecialFemaleInter(2, BigLoop);
			SpecialAgeEventMales[3] := PR[BigLoop].PopulationMale[3] * SpecialMaleInter(3, BigLoop);
			SpecialAgeEventFemales[3] := PR[BigLoop].PopulationFemale[3] * SpecialFemaleInter(3, BigLoop);
			SpecialAgeEventMales[NofAgeGroups] := PR[BigLoop].PopulationMale[NofAgeGroups] * SpecialMaleInter(NofAgeGroups, BigLoop);
			SpecialAgeEventFemales[NofAgeGroups] := PR[BigLoop].PopulationFemale[NofAgeGroups] * SpecialFemaleInter(NofAgeGroups, BigLoop);
			SpecialEventTotalMales := SpecialEventTotalMales + SpecialAgeEventMales[1] + SpecialAgeEventMales[2] + SpecialAgeEventMales[3] + SpecialAgeEventMales[NofAgeGroups];
			SpecialEventTotalFemales := SpecialEventTotalFemales + SpecialAgeEventFemales[1] + SpecialAgeEventFemales[2] + SpecialAgeEventFemales[3] + SpecialAgeEventFemales[NofAgeGroups];



			TotalPopulationMales := TotalPopulationMales + PR[BigLoop].PopulationMale[1];
			TotalPopulationFemales := TotalPopulationFemales + PR[BigLoop].PopulationFemale[1];
			T2 := TotalPopulationMales + TotalPopulationFemales;
			TotalDeaths := T1 - T2 + TotalMigrantes + (TotalBirths);

{----------------------------------------------------------------------}
{          calculate crude vital rates (CBR & CDR), }
{           and growth rates (RNG & RG)}
{----------------------------------------------------------------------}
			PR[BigLoop].Parameters[3] := TotalBirths / (2.5 * (T1 + T2)) * 1000;{Crude Birth rate}
			PR[BigLoop].Parameters[4] := TotalDeaths / (2.5 * (T1 + T2)) * 1000;{Crude Death rate}
			PR[BigLoop].Parameters[1] := 100 * (T2 - T1) / (2.5 * (T1 + T2));{Rate of Growth}

			PR[BigLoop].Parameters[2] := (PR[BigLoop].Parameters[3] - PR[BigLoop].Parameters[4]) / 10; {Natural Increase Rate}
			PR[BigLoop].Parameters[41] := TotalBirths - TotalDeaths; {Natural Increase abs}


{---------------------------------------------------------------------}
{          calculate total and general fertility rates (TotalFertilityRate & GFR)}
{          and NetReprodutionRate                                                                      }
{---------------------------------------------------------------------}
			RF := 0.0;
			NetReprodutionRate := 0;
			TotalFertilityRate := 0.0;
			MidFage := 17.5;
			TempGeneration := 0;
			TempFemFert := 0;
			if TotalBirths = 0 then
				NetReprodutionRate := 0
			else
				for I := 1 to 6 do
					begin
						RF := RF + PR[BigLoop].PopulationFemale[I + 4] + PR[BigLoop - 1].PopulationFemale[I + 4];
						TotalFertilityRate := TotalFertilityRate + FertilityRateInter(I + 4, BigLoop) + FertilityRateInter(I + 4, BigLoop - 1);
						NetReprodutionRate := NetReprodutionRate + FertilityRateInter(I + 4, BigLoop) * 5 * (TotalBirthsFemale / (TotalBirthsMale + TotalBirthsFemale)) * SurvivalFemaleInter(I + 4, BigLoop);
						TempGeneration := TempGeneration + MidFage * FertilityRateInter(I + 4, BigLoop) * 5 * (TotalBirthsFemale / (TotalBirthsMale + TotalBirthsFemale)) * SurvivalFemaleInter(I + 4, BigLoop);
						TempFemFert := TempFemFert + MidFage * (FertilityRateInter(I + 4, BigLoop) + FertilityRateInter(I + 4, BigLoop - 1)) / 2;
						MidFage := MidFage + 5;
					end;

			PR[BigLoop].Parameters[42] := TempGeneration / NetReprodutionRate {Length Generation}
			PR[BigLoop].Parameters[43] := TempFemFert / (TotalFertilityRate / 2){Mean Age of Childbearing}


			PR[BigLoop].Parameters[5] := (TotalBirths / (RF * 2.5)) * 1000; {General fertility rate}
			TotalFertilityRate := TotalFertilityRate * 1000;
			PR[BigLoop].Parameters[6] := TotalFertilityRate * 2.5;
			PR[BigLoop].Parameters[12] := NetReprodutionRate * 1000;

{---------------------------------------------------------------------}
{          calculate life expectancy at birth (LifeExpMales  &  LifeExpFemales)}
{---------------------------------------------------------------------}

{males}
			RM := (1 * SurvivalMaleInter(1, BigLoop) + 4 * SurvivalMaleInter(2, BigLoop));
			LifeExpMales := RM;
			flag := true;
			I := 3;
			while (flag = true) and (I <= NG1) do
				begin
					value := (SurvivalMaleInter(I + 1, BigLoop) - 0.001);
					if value < 0 then
						flag := false;

					if flag then
						begin
							RM := RM * SurvivalMaleInter(I, BigLoop);
							LifeExpMales := LifeExpMales + RM;
							I := I + 1;
						end;
				end;
			LifeExpMales := LifeExpMales + ((RM * SurvivalMaleInter(I, BigLoop)) / (1.0 - SurvivalMaleInter(I, BigLoop)));

{females}
			RF := (1 * SurvivalFemaleInter(1, BigLoop) + 4 * SurvivalFemaleInter(2, BigLoop));
			LifeExpFemales := RF;
			flag := true;
			i := 3;
			while (flag = True) and (i <= NG1) do
				begin
					value := (SurvivalFemaleInter(I + 1, BigLoop) - 0.001);
					if value < 0 then
						flag := false;

					if flag = true then
						begin
							RF := RF * SurvivalFemaleInter(I, BigLoop);
							LifeExpFemales := LifeExpFemales + RF;
							I := I + 1;
						end;
				end;
			LifeExpFemales := LifeExpFemales + ((RF * SurvivalFemaleInter(I, BigLoop)) / (1.0 - SurvivalFemaleInter(I, BigLoop)));

			PR[BigLoop].Parameters[7] := LifeExpMales;
			PR[BigLoop].Parameters[8] := LifeExpFemales;
			PR[BigLoop].Parameters[9] := T2;
			PR[BigLoop].Parameters[10] := TotalPopulationMales;
			PR[BigLoop].Parameters[11] := TotalPopulationFemales;

{InfantMortality}
			if TotalBirths = 0 then
				PR[BigLoop].Parameters[13] := 0
			else
				PR[BigLoop].Parameters[13] := ((((TotalBirthsMale + TotalBirthsFemale) - (TotalBirthsMale * SurvivalMaleInter(1, BigLoop) + TotalBirthsFemale * SurvivalFemaleInter(1, BigLoop))) / (TotalBirthsMale + TotalBirthsFemale))) * 1000;




{ChildWomanRatio}
			Pop04 := 0;
			Popf1549 := 0;
			for index := 1 to 2 do
				Pop04 := Pop04 + PR[BigLoop].PopulationMale[index] + PR[BigLoop].PopulationFemale[index];
			for index := 5 to 11 do
				Popf1549 := Popf1549 + PR[BigLoop].PopulationFemale[index];
			PR[BigLoop].Parameters[14] := Pop04 / Popf1549 * 1000; {ChildWomanRatio}


{Dependency}
			DependentPopUnder := 0;
			DependentPopOver := 0;
			IndependentPop := 0;
			for index := 1 to 4 do
				DependentPopUnder := DependentPopUnder + PR[BigLoop].PopulationMale[index] + PR[BigLoop].PopulationFemale[index];
			for index := 15 to 22 do
				DependentPopOver := DependentPopOver + PR[BigLoop].PopulationMale[index] + PR[BigLoop].PopulationFemale[index];
			for index := 5 to 14 do
				IndependentPop := IndependentPop + PR[BigLoop].PopulationMale[index] + PR[BigLoop].PopulationFemale[index];
			DependencyRatioTotal := (DependentPopUnder + DependentPopOver) / IndependentPop * 100;
			PR[BigLoop].Parameters[15] := DependencyRatioTotal;


{DependencyRatioAged}
			PR[BigLoop].Parameters[16] := DependentPopOver / IndependentPop * 100;

{DependencyRatioYouth}
			PR[BigLoop].Parameters[17] := DependentPopUnder / IndependentPop * 100;

{DoublingTime}
			PR[BigLoop].Parameters[18] := 69.3 / PR[BigLoop].Parameters[1]; {rate of growth}


{GrossReprodRate }
			PR[BigLoop].Parameters[19] := (TotalFertilityRate * 2.5) * TotalBirthsFemale / (TotalBirthsMale + TotalBirthsFemale);

{PctDemTransComp}
			PR[BigLoop].Parameters[20] := 50 * ((235 - PR[BigLoop].Parameters[5]) / 175 + (7500 - TotalFertilityRate) / 5300);

{Pop%Under}
			PR[BigLoop].Parameters[21] := DependentPopUnder / T2 * 100;

{Pop%Over}
			PR[BigLoop].Parameters[22] := DependentPopOver / T2 * 100;

{ChildMortalityRate}
			PopNoDeathMale4 := PR[BigLoop - 1].PopulationMale[3] + 0.5 * MigrationMaleInter(3, BigLoop) + 0.5 * MigrationMaleInter(4, BigLoop);
			PopNoDeathFemale4 := PR[BigLoop - 1].PopulationFemale[3] + 0.5 * MigrationFemaleInter(3, BigLoop) + 0.5 * MigrationFemaleInter(4, BigLoop);
			PopNoDeathMale3 := PR[BigLoop - 1].PopulationMale[1] + PR[BigLoop - 1].PopulationMale[2] + 0.5 * MigrationMaleInter(2, BigLoop) + 0.5 * MigrationMaleInter(3, BigLoop);
			PopNoDeathFemale3 := PR[BigLoop - 1].PopulationFemale[1] + PR[BigLoop - 1].PopulationFemale[2] + 0.5 * MigrationFemaleInter(2, BigLoop) + 0.5 * MigrationFemaleInter(3, BigLoop);
			PopNoDeathMale2 := PR[BigLoop].PopulationMale[1] * 4 + 0.5 * MigrationMaleInter(1, BigLoop) + 0.5 * MigrationMaleInter(2, BigLoop);
			PopNoDeathFemale2 := PR[BigLoop].PopulationFemale[1] * 4 + 0.5 * MigrationFemaleInter(1, BigLoop) + 0.5 * MigrationFemaleInter(2, BigLoop);
			MaleFem12 := PR[BigLoop].PopulationMale[2] + PR[BigLoop].PopulationFemale[2] + PR[BigLoop].PopulationMale[3] + PR[BigLoop].PopulationFemale[3] + PR[BigLoop].PopulationMale[4] + PR[BigLoop].PopulationFemale[4];
			ChildMortalityRate := (PopNoDeathMale4 + PopNoDeathFemale4 + PopNoDeathMale3 + PopNoDeathFemale3 + PopNoDeathMale2 + PopNoDeathFemale2 - MaleFem12) / MaleFem12;
			PR[BigLoop].Parameters[23] := ChildMortalityRate * 1000;

{Totals for special events}
			PR[BigLoop].Parameters[24] := SpecialEventTotalMales + SpecialEventTotalFemales;
			PR[BigLoop].Parameters[25] := SpecialEventTotalFemales;
			PR[BigLoop].Parameters[26] := SpecialEventTotalMales;

{Migration Variables}
			TotalMigInMale := 0;
			TotalMigInFemale := 0;
			TotalMigOutMale := 0;
			TotalMigOutFemale := 0;
			for index := 1 to 22 do
				begin
					MigrantesMale := MigrationMaleInter(index, BigLoop);
					MigrantesFemale := MigrationFemaleInter(index, BigLoop);
					if MigrantesMale > 0 then
						TotalMigInMale := TotalMigInMale + MigrantesMale
					else
						TotalMigOutMale := TotalMigOutMale + MigrantesMale;

					if MigrantesFemale > 0 then
						TotalMigInFemale := TotalMigInFemale + MigrantesFemale
					else
						TotalMigOutFemale := TotalMigOutFemale + MigrantesFemale;

				end;

{ Mig. Rate Female In}
			PR[BigLoop].Parameters[27] := TotalMigInFemale / TotalPopulationFemales * 1000;

{ Mig. Rate Female Out}
			PR[BigLoop].Parameters[28] := TotalMigOutFemale / TotalPopulationFemales * 1000;

{ Mig. Rate  Gross}
			PR[BigLoop].Parameters[29] := (Abs(TotalMigOutFemale + TotalMigOutMale) + TotalMigInMale + TotalMigInFemale) / T2 * 1000;

{ Mig. Rate Male In}
			PR[BigLoop].Parameters[30] := TotalMigInMale / TotalPopulationMales * 1000;

{ Mig. Rate Male Out}
			PR[BigLoop].Parameters[31] := TotalMigOutMale / TotalPopulationMales * 1000;

{ Mig. Rate Net}
			PR[BigLoop].Parameters[32] := (TotalMigOutFemale + TotalMigOutMale + TotalMigInMale + TotalMigInFemale) / T2 * 1000;

{Mig. Rate-Total In}
			PR[BigLoop].Parameters[33] := (TotalMigInMale + TotalMigInFemale) / T2 * 1000;

{Mig. Rate-Total Out}
			PR[BigLoop].Parameters[34] := (TotalMigOutMale + TotalMigOutFemale) / T2 * 1000;

{Sex Ratio at Birth}
			PR[BigLoop].Parameters[35] := SexRatioBirthInter(BigLoop);


{Median Age}
			MdnAgeMale := 0;
			MdnAgeFemale := 0;
			for i := 3 to 21 do
				begin
					MdnAgeMale := MdnAgeMale + PR[BigLoop].PopulationMale[i] * (2 + 5 * (i - 2));
					MdnAgeFemale := MdnAgeFemale + PR[BigLoop].PopulationFemale[i] * (2 + 5 * (i - 2));
				end;
			MdnAgeMale := MdnAgeMale + PR[BigLoop].PopulationMale[2] * 2; {2= (1+4)/2 x4/5}
			MdnAgeFemale := MdnAgeFemale + PR[BigLoop].PopulationFemale[2] * 2;
			MdnAgeMale := MdnAgeMale + PR[BigLoop].PopulationMale[22] * 104.5;
			MdnAgeFemale := MdnAgeFemale + PR[BigLoop].PopulationFemale[22] * 104.5;
			PR[BigLoop].Parameters[36] := (MdnAgeMale + MdnAgeFemale) / (T2 + 0.00005);
			MdnAgeMale := MdnAgeMale / (TotalPopulationMales + 0.00005);
			MdnAgeFemale := MdnAgeFemale / (TotalPopulationFemales + 0.00005);
			PR[BigLoop].Parameters[37] := MdnAgeMale;
			PR[BigLoop].Parameters[38] := MdnAgeFemale;

{Total Births}
			PR[BigLoop].Parameters[39] := TotalBirths;
{Total Deaths}
			PR[BigLoop].Parameters[40] := TotalDeaths;


{Calculate Global Max and Max within year}
			MaxWithinYear := 0;
			for index := 1 to 22 do
				begin
					if PR[BigLoop].PopulationMale[index] > TheMax then
						TheMax := PR[BigLoop].PopulationMale[index];
					if PR[BigLoop].PopulationFemale[index] > TheMax then
						TheMax := PR[BigLoop].PopulationFemale[index];
					if PR[BigLoop].PopulationMale[index] > MaxWithinYear then
						MaxWithinYear := PR[BigLoop].PopulationMale[index];
					if PR[BigLoop].PopulationFemale[index] > MaxWithinYear then
						MaxWithinYear := PR[BigLoop].PopulationFemale[index];
				end;
{first 2 cohorts are added together so check max of addition}
			if (PR[BigLoop].PopulationMale[1] + PR[BigLoop].PopulationMale[2]) > TheMax then
				TheMax := PR[BigLoop].PopulationMale[1] + PR[BigLoop].PopulationMale[2];
			if (PR[BigLoop].PopulationFemale[1] + PR[BigLoop].PopulationFemale[2]) > TheMax then
				TheMax := PR[BigLoop].PopulationFemale[1] + PR[BigLoop].PopulationFemale[2];

			if (PR[BigLoop].PopulationMale[1] + PR[BigLoop].PopulationMale[2]) > MaxWithinYear then
				MaxWithinYear := (PR[BigLoop].PopulationMale[1] + PR[BigLoop].PopulationMale[2]);
			if (PR[BigLoop].PopulationFemale[1] + PR[BigLoop].PopulationFemale[2]) > MaxWithinYear then
				MaxWithinYear := (PR[BigLoop].PopulationFemale[1] + PR[BigLoop].PopulationFemale[2]);


			if T2 <> 0 then
				if (MaxWithinYear / T2) > MaxPercent then
					MaxPercent := (MaxWithinYear / T2);


		end;{big loop}


{-----------------------------------------------------------------}
{            return to calling program}
{-----------------------------------------------------------------}

	absMax := TheMax;
	percMax := MaxPercent;

end;
