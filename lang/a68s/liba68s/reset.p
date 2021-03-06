88100 #include "rundecs.h"
88110     (*  COPYRIGHT 1983 C.H.LINDSEY, UNIVERSITY OF MANCHESTER  *)
88120  (**)
88130 PROCEDURE GARBAGE (ANOBJECT: OBJECTP); EXTERN ;
88140 PROCEDURE ERRORR(N :INTEGER); EXTERN ;
88150 PROCEDURE TESTF(RF:OBJECTP;VAR F:OBJECTP); EXTERN;
88160 PROCEDURE SETREADMOOD(PCOV:OBJECTP); EXTERN;
88170 PROCEDURE SETWRITEMOOD(PCOV:OBJECTP); EXTERN;
88180 PROCEDURE SETCHARMOOD(PCOV:OBJECTP); EXTERN;
88190 (**)
88200 (**)
88210 PROCEDURE RESET(RF: OBJECTP);
88220   VAR F: OBJECTP;
88230     BEGIN
88240     TESTF(RF, F);
88250     WITH F^.PCOVER^ DO
88260       IF OPENED IN STATUS THEN
88270         IF RESETPOSS IN POSSIBLES THEN
88280           BEGIN
88290           STATUS := STATUS-[READMOOD,WRITEMOOD,LFE,PFE,PAGEOVERFLOW,LINEOVERFLOW]+[NOTRESET];
88300           COFCPOS := 1; LOFCPOS := 1; POFCPOS := 1;
88310           IF NOT (GETPOSS IN POSSIBLES) THEN SETWRITEMOOD(F^.PCOVER)
88320           ELSE IF NOT (PUTPOSS IN POSSIBLES) THEN SETREADMOOD(F^.PCOVER);
88330           IF NOT (BINPOSS IN POSSIBLES) THEN SETCHARMOOD(F^.PCOVER)
88340           END
88350         ELSE ERRORR(NORESET)
88360       ELSE ERRORR(NOTOPEN);
88370     IF FPTST(RF^) THEN GARBAGE(RF)
88380     END;
88390 (**)
88400 (**)
88410 (*-02()
88420 BEGIN (*OF A68*)
88430 END; (*OF A68*)
88440 ()-02*)
88450 (*+01()
88460 BEGIN (*OF MAIN PROGRAM*)
88470 END (* OF EVERYTHING *).
88480 ()+01*)
