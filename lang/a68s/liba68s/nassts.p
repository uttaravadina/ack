38900 #include "rundecs.h"
38910     (*  COPYRIGHT 1983 C.H.LINDSEY, UNIVERSITY OF MANCHESTER  *)
38920 (**)
38930 PROCEDURE GARBAGE (ANOBJECT: OBJECTP); EXTERN;
38940 PROCEDURE ERRORR(N :INTEGER); EXTERN;
38950 PROCEDURE TESTCC(TARGET: OBJECTP); EXTERN ;
38960 PROCEDURE TESTSS (REFSTRUCT: OBJECTP); EXTERN ;
38970 (**)
38980 (**)
38990 PROCEDURE NASSTCMN(ANOBJECT: OBJECTP);
39000     BEGIN
39010     WITH ANOBJECT^ DO
39020       CASE ANCESTOR^.SORT OF
39030         REFR, RECR:
39040           TESTCC(ANOBJECT);
39050         RECN, REFN:
39060           TESTSS(ANCESTOR);
39070         UNDEF:
39080           ERRORR(RSEL);
39090         NILL:
39100           ERRORR(RSELNIL)
39110         END
39120     END;
39130 (**)
39140 (**)
39150 (*-01() (*-05()
39160 FUNCTION NASSTS(TEMP: NAKEGER; SOURCE: A68INT): ASNAKED;
39170 (*PASSIGNNT*)
39180   VAR DEST: UNDRESSP;
39190     BEGIN
39200     WITH TEMP.NAK, STOWEDVAL^.ANCESTOR^ DO
39210       BEGIN
39220         IF FPTWO(PVALUE^) THEN 
39230              NASSTCMN(STOWEDVAL);
39240       PVALUE^.OSCOPE := 0;
39250       DEST := INCPTR(PVALUE, POSITION)
39260       END;
39270     DEST^.FIRSTINT := SOURCE;
39280     NASSTS := TEMP.ASNAK;
39290     END;
39300 (**)
39310 (**)
39320 FUNCTION NASSTS2(TEMP: NAKEGER; SOURCE: A68LONG): ASNAKED;
39330 (*PASSIGNNT+1*)
39340   VAR DEST: UNDRESSP;
39350     BEGIN
39360     WITH TEMP.NAK, STOWEDVAL^.ANCESTOR^ DO
39370       BEGIN
39380         IF FPTWO(PVALUE^) THEN 
39390             NASSTCMN(STOWEDVAL);
39400       PVALUE^.OSCOPE := 0;
39410       DEST := INCPTR(PVALUE, POSITION)
39420       END;
39430     DEST^.FIRSTLONG := SOURCE;
39440     NASSTS2 := TEMP.ASNAK;
39450     END;
39460 ()-05*) ()-01*)
39470 (**)
39480 (**)
39490 FUNCTION NASSTPT(TEMP: NAKEGER; SOURCE: OBJECTP): ASNAKED;
39500  (*+01() EXTERN ; ()+01*)
39510 (*-01()
39520 (*PASSIGNNT+2*)
39530   VAR DEST: UNDRESSP;
39540     BEGIN
39550     WITH TEMP.NAK, STOWEDVAL^.ANCESTOR^ DO
39560       BEGIN
39570         IF FPTWO(PVALUE^) THEN 
39580             NASSTCMN(STOWEDVAL);
39590       PVALUE^.OSCOPE := 0;
39600       DEST := INCPTR(PVALUE, POSITION)
39610       END;
39620     WITH DEST^ DO
39630       BEGIN
39640       FPINC(SOURCE^);
39650       FPDEC(FIRSTPTR^); IF FPTST(FIRSTPTR^) THEN GARBAGE(FIRSTPTR);
39660       FIRSTPTR := SOURCE;
39670       END;
39680     NASSTPT := TEMP.ASNAK;
39690     END;
39700 ()-01*)
39710 FUNCTION SCPNTPT(TEMP: NAKEGER; SOURCE: OBJECTP): ASNAKED;
39720 (*PSCOPENT+2*)
39730     BEGIN
39740     WITH SOURCE^ DO
39750       BEGIN
39760       IF TEMP.NAK.STOWEDVAL^.OSCOPE<OSCOPE THEN ERRORR(RSCOPE);
39770       END;
39780     SCPNTPT := NASSTPT(TEMP, SOURCE);
39790     END;
39800 (**)
39810 (**)
39820 (*-02()
39830   BEGIN
39840   END;
39850 ()-02*)
39860 (*+01()
39870 BEGIN (*OF MAIN PROGRAM*)
39880 END  (*OF EVERYTHING*).
39890 ()+01*)
