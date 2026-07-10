#include "pch.h"
int __cdecl mdec_idct_sse(__m64 *a1, int a2)
{
  __m64 v2; // mm0
  __m64 v3; // mm2
  __m64 v4; // mm4
  __m64 v5; // mm1
  __m64 v6; // mm0
  __m64 v7; // mm2
  __m64 v8; // mm5
  __m64 v9; // mm3
  __m64 v10; // mm6
  __m64 v11; // mm5
  __m64 v12; // mm4
  __m64 v13; // mm3
  __m64 v14; // mm0
  __m64 v15; // mm2
  __m64 v16; // mm5
  __m64 v17; // mm6
  __m64 v18; // mm5
  __m64 v19; // mm4
  __m64 v20; // mm1
  __m64 v21; // mm4
  __m64 v22; // mm7
  __m64 v23; // mm4
  __m64 v24; // mm5
  __m64 v25; // mm0
  __m64 v26; // mm3
  __m64 v27; // mm0
  __m64 v28; // mm2
  __m64 v29; // mm4
  __m64 v30; // mm1
  __m64 v31; // mm0
  __m64 v32; // mm2
  __m64 v33; // mm5
  __m64 v34; // mm3
  __m64 v35; // mm6
  __m64 v36; // mm5
  __m64 v37; // mm4
  __m64 v38; // mm3
  __m64 v39; // mm0
  __m64 v40; // mm2
  __m64 v41; // mm5
  __m64 v42; // mm6
  __m64 v43; // mm7
  __m64 v44; // mm5
  __m64 v45; // mm4
  __m64 v46; // mm1
  __m64 v47; // mm4
  __m64 v48; // mm7
  __m64 v49; // mm4
  __m64 v50; // mm5
  __m64 v51; // mm0
  __m64 v52; // mm3
  __m64 v53; // mm2
  __m64 v54; // mm6
  __m64 v55; // mm3
  __m64 v56; // mm5
  __m64 v57; // mm0
  __m64 v58; // mm1
  __m64 v59; // mm6
  __m64 v60; // mm5
  __m64 v61; // mm2
  __m64 v62; // mm7
  __m64 v63; // mm3
  __m64 v64; // mm4
  __m64 v65; // mm2
  __m64 v66; // mm7
  __m64 v67; // mm0
  __m64 v68; // mm7
  __m64 v69; // mm6
  __m64 v70; // mm5
  __m64 v71; // mm1
  __m64 v72; // mm5
  __m64 v73; // mm3
  __m64 v74; // mm4
  __m64 v75; // mm2
  __m64 v76; // mm3
  __m64 v77; // mm0
  __m64 v78; // mm1
  __m64 v79; // mm6
  __m64 v80; // mm1
  __m64 v81; // mm0
  __m64 v82; // mm3
  __m64 v83; // mm7
  __m64 v84; // mm2
  __m64 v85; // mm6
  __m64 v86; // mm2
  __m64 v87; // mm4
  __m64 v88; // mm7
  __m64 v89; // mm1
  __m64 v90; // mm7
  __m64 v91; // mm4
  __m64 v92; // mm2
  __m64 v93; // mm5
  __m64 v94; // mm0
  __m64 v95; // mm5
  __m64 v96; // mm4
  __m64 v97; // mm1
  __m64 v98; // mm5
  __m64 v99; // mm0
  __m64 v100; // mm3
  __m64 v101; // mm7
  __m64 v102; // mm6
  __m64 v103; // mm3
  __m64 v104; // mm1
  __m64 v105; // mm0
  __m64 v106; // mm2
  __m64 v107; // mm7
  __m64 v108; // mm6
  __m64 v109; // mm7
  __m64 v110; // mm4
  __m64 v111; // mm1
  __m64 v112; // mm5
  __m64 v113; // mm7
  __m64 v114; // mm2
  __m64 v115; // mm6
  __m64 *v116; // ebx
  __m64 v117; // mm3
  __m64 v118; // mm7
  __m64 *v119; // ecx
  __m64 *v120; // ebx
  __m64 v121; // mm2
  __m64 v122; // mm6
  __m64 v123; // mm3
  __m64 v124; // mm5
  __m64 v125; // mm0
  __m64 v126; // mm1
  __m64 v127; // mm6
  __m64 v128; // mm5
  __m64 v129; // mm2
  __m64 v130; // mm7
  __m64 v131; // mm3
  __m64 v132; // mm4
  __m64 v133; // mm2
  __m64 v134; // mm7
  __m64 v135; // mm0
  __m64 v136; // mm7
  __m64 v137; // mm6
  __m64 v138; // mm5
  __m64 v139; // mm1
  __m64 v140; // mm5
  __m64 v141; // mm3
  __m64 v142; // mm4
  __m64 v143; // mm2
  __m64 v144; // mm3
  __m64 v145; // mm0
  __m64 v146; // mm1
  __m64 v147; // mm6
  __m64 v148; // mm1
  __m64 v149; // mm0
  __m64 v150; // mm3
  __m64 v151; // mm7
  __m64 v152; // mm2
  __m64 v153; // mm6
  __m64 v154; // mm2
  __m64 v155; // mm4
  __m64 v156; // mm7
  __m64 v157; // mm1
  __m64 v158; // mm7
  __m64 v159; // mm4
  __m64 v160; // mm2
  __m64 v161; // mm5
  __m64 v162; // mm0
  __m64 v163; // mm5
  __m64 v164; // mm4
  __m64 v165; // mm1
  __m64 v166; // mm5
  __m64 v167; // mm0
  __m64 v168; // mm3
  __m64 v169; // mm7
  __m64 v170; // mm6
  __m64 v171; // mm3
  __m64 v172; // mm1
  __m64 v173; // mm0
  __m64 v174; // mm2
  __m64 v175; // mm7
  __m64 v176; // mm6
  __m64 v177; // mm7
  __m64 v178; // mm4
  __m64 v179; // mm1
  __m64 v180; // mm5
  __m64 v181; // mm7
  __m64 v182; // mm2
  __m64 v183; // mm6
  __m64 *v184; // ebx
  __m64 v185; // mm3
  __m64 v186; // mm7
  __m64 *v187; // ecx
  __m64 *v189; // ebx
  __m64 v190; // [esp+10h] [ebp-84h]
  __m64 v191; // [esp+10h] [ebp-84h]
  __m64 v192; // [esp+10h] [ebp-84h]
  __m64 v193; // [esp+18h] [ebp-7Ch]
  __m64 v194; // [esp+18h] [ebp-7Ch]
  __m64 v195; // [esp+18h] [ebp-7Ch]
  __m64 v196; // [esp+20h] [ebp-74h]
  __m64 v197; // [esp+20h] [ebp-74h]
  __m64 v198; // [esp+20h] [ebp-74h]
  __m64 v199; // [esp+28h] [ebp-6Ch]
  __m64 v200; // [esp+28h] [ebp-6Ch]
  __m64 v201; // [esp+28h] [ebp-6Ch]
  __m64 v202; // [esp+30h] [ebp-64h]
  __m64 v203; // [esp+30h] [ebp-64h]
  __m64 v204; // [esp+38h] [ebp-5Ch]
  __m64 v205; // [esp+38h] [ebp-5Ch]
  __m64 v206; // [esp+40h] [ebp-54h]
  __m64 v207; // [esp+48h] [ebp-4Ch]
  __m64 v208; // [esp+50h] [ebp-44h]
  __m64 v209; // [esp+50h] [ebp-44h]
  __m64 v210; // [esp+58h] [ebp-3Ch]
  __m64 v211; // [esp+58h] [ebp-3Ch]
  __m64 v212; // [esp+60h] [ebp-34h]
  __m64 v213; // [esp+60h] [ebp-34h]
  __m64 v214; // [esp+68h] [ebp-2Ch]
  __m64 v215; // [esp+68h] [ebp-2Ch]
  __m64 v216; // [esp+70h] [ebp-24h]
  __m64 v217; // [esp+78h] [ebp-1Ch]
  __m64 v218; // [esp+80h] [ebp-14h]
  __m64 v219; // [esp+88h] [ebp-Ch]

  v2 = a1[6];
  v3 = a1[10];
  v4 = a1[14];
  v5 = _m_paddw(v3, v2);
  v6 = _m_psllwi(_m_psubw(v3, v2), 2u);
  v7 = _m_pmulhw(v6, (__m64)qword_455C28);
  v8 = a1[2];
  v9 = _m_paddw(v8, v4);
  v10 = _m_psubw(v9, v5);
  v11 = _m_psllwi(_m_psubw(v8, v4), 2u);
  v12 = a1[12];
  v13 = _m_paddw(v9, v5);
  v14 = _m_paddw(_m_pmulhw(v6, (__m64)qword_455C38), _m_pmulhw(v11, (__m64)qword_455C40));
  v15 = _m_psubw(_m_paddw(v7, _m_pmulhw(v11, (__m64)qword_455C30)), v13);
  v16 = a1[4];
  v17 = _m_psubw(_m_pmulhw(_m_psllwi(v10, 2u), (__m64)qword_455C20), v15);
  v190 = _m_paddw(v16, v12);
  v18 = _m_pmulhw(_m_psllwi(_m_psubw(v16, v12), 2u), (__m64)qword_455C20);
  v19 = a1[8];
  v202 = _m_paddw(v14, v17);
  v196 = _m_psubw(v18, v190);
  v20 = _m_psubw((__m64)a1->m64_u64, v19);
  v21 = _m_paddw((__m64)a1->m64_u64, v19);
  v22 = _m_paddw(v21, v190);
  v23 = _m_psubw(v21, v190);
  v24 = _m_psubw(v20, v196);
  v25 = _m_psubw(v22, v13);
  v191 = _m_paddw(v22, v13);
  v26 = _m_paddw(v20, v196);
  v218 = v25;
  v197 = _m_paddw(v26, v15);
  v216 = _m_psubw(v26, v15);
  v208 = _m_paddw(v23, v202);
  v206 = _m_psubw(v23, v202);
  v203 = _m_paddw(v24, v17);
  v212 = _m_psubw(v24, v17);
  v27 = a1[7];
  v28 = a1[11];
  v29 = a1[15];
  v30 = _m_paddw(v28, v27);
  v31 = _m_psllwi(_m_psubw(v28, v27), 2u);
  v32 = _m_pmulhw(v31, (__m64)qword_455C28);
  v33 = a1[3];
  v34 = _m_paddw(v33, v29);
  v35 = _m_psubw(v34, v30);
  v36 = _m_psllwi(_m_psubw(v33, v29), 2u);
  v37 = a1[13];
  v38 = _m_paddw(v34, v30);
  v39 = _m_paddw(_m_pmulhw(v31, (__m64)qword_455C38), _m_pmulhw(v36, (__m64)qword_455C40));
  v40 = _m_psubw(_m_paddw(v32, _m_pmulhw(v36, (__m64)qword_455C30)), v38);
  v41 = a1[5];
  v42 = _m_psubw(_m_pmulhw(_m_psllwi(v35, 2u), (__m64)qword_455C20), v40);
  v193 = _m_paddw(v41, v37);
  v43 = a1[1];
  v44 = _m_pmulhw(_m_psllwi(_m_psubw(v41, v37), 2u), (__m64)qword_455C20);
  v45 = a1[9];
  v204 = _m_paddw(v39, v42);
  v199 = _m_psubw(v44, v193);
  v46 = _m_psubw(v43, v45);
  v47 = _m_paddw(v43, v45);
  v48 = _m_paddw(v47, v193);
  v49 = _m_psubw(v47, v193);
  v50 = _m_psubw(v46, v199);
  v51 = _m_psubw(v48, v38);
  v194 = _m_paddw(v48, v38);
  v52 = _m_paddw(v46, v199);
  v219 = v51;
  v200 = _m_paddw(v52, v40);
  v217 = _m_psubw(v52, v40);
  v210 = _m_paddw(v49, v204);
  v207 = _m_psubw(v49, v204);
  v205 = _m_paddw(v50, v42);
  v214 = _m_psubw(v50, v42);
  v53 = _m_psubw(v191, v194);
  v54 = _m_paddw(v191, v194);
  v55 = _m_paddw(v197, v200);
  v56 = _m_psubw(v197, v200);
  v57 = _m_punpckldq(_m_punpcklwd(v54, v55), _m_punpckhwd(v54, v55));
  v58 = _m_punpckldq(_m_punpcklwd(v53, v56), _m_punpckhwd(v53, v56));
  v59 = _m_paddw(v206, v207);
  v60 = _m_paddw(v203, v205);
  v61 = _m_psubw(v206, v207);
  v62 = _m_psubw(v203, v205);
  v63 = _m_punpckldq(_m_punpcklwd(v60, v59), _m_punpckhwd(v60, v59));
  v64 = _m_punpckldq(_m_punpcklwd(v62, v61), _m_punpckhwd(v62, v61));
  v65 = _m_punpckhdq(v57, v63);
  v66 = _m_punpckldq(v57, v63);
  v67 = _m_paddw(v66, v65);
  v68 = _m_psubw(v66, v65);
  v69 = _m_psubw(_m_pmulhw(_m_psllwi(_m_punpckhdq(v58, v64), 2u), (__m64)qword_455C20), v65);
  v70 = _m_punpckldq(v58, v64);
  v71 = _m_paddw(v70, v69);
  v72 = _m_psubw(v70, v69);
  v73 = _m_punpckldq(v191, v194);
  v74 = _m_punpckhdq(v194, v191);
  v192 = v67;
  v75 = _m_paddw(v73, v74);
  v76 = _m_psubw(v73, v74);
  v195 = v71;
  v77 = _m_punpckhdq(v200, v197);
  v78 = _m_punpckldq(v197, v200);
  v79 = _m_paddw(v78, v77);
  v198 = v72;
  v80 = _m_psubw(v78, v77);
  v201 = v68;
  v81 = _m_punpckhdq(_m_punpckhwd(v76, v80), _m_punpcklwd(v75, v79));
  v82 = _m_punpckhdq(_m_punpcklwd(v76, v80), _m_punpckhwd(v75, v79));
  v83 = _m_punpckhdq(v205, v203);
  v84 = _m_punpckldq(v203, v205);
  v85 = _m_paddw(v84, v83);
  v86 = _m_psubw(v84, v83);
  v87 = _m_punpckhdq(v207, v206);
  v88 = _m_punpckldq(v206, v207);
  v89 = _m_paddw(v88, v87);
  v90 = _m_psubw(v88, v87);
  v91 = _m_punpckhdq(_m_punpckhwd(v86, v90), _m_punpcklwd(v85, v89));
  v92 = _m_punpckhdq(_m_punpcklwd(v86, v90), _m_punpckhwd(v85, v89));
  v93 = v81;
  v94 = _m_punpckldq(v81, v91);
  v95 = _m_punpckhdq(v93, v91);
  v96 = _m_punpckhdq(v82, v92);
  v97 = _m_psubw(v95, v96);
  v98 = _m_paddw(v95, v96);
  v99 = _m_psllwi(v94, 2u);
  v100 = _m_psllwi(_m_punpckldq(v82, v92), 2u);
  v101 = _m_pmulhw(v99, (__m64)qword_455C38);
  v102 = _m_pmulhw(v100, (__m64)qword_455C40);
  v103 = _m_psubw(_m_paddw(_m_pmulhw(v100, (__m64)qword_455C30), _m_pmulhw(v99, (__m64)qword_455C28)), v98);
  v104 = _m_psubw(_m_pmulhw(_m_psllwi(v97, 2u), (__m64)qword_455C20), v103);
  v105 = _m_packsswb(_m_psrawi(_m_paddw(v195, v103), 5u), _m_psrawi(_m_psubw(v192, v98), 5u));
  v106 = _m_packsswb(_m_psrawi(_m_paddw(v192, v98), 5u), _m_psrawi(_m_psubw(v195, v103), 5u));
  v107 = _m_paddw(_m_paddw(v101, v102), v104);
  v108 = _m_packsswb(_m_psrawi(_m_psubw(v201, v107), 5u), _m_psrawi(_m_psubw(v198, v104), 5u));
  v109 = _m_packsswb(_m_psrawi(_m_paddw(v198, v104), 5u), _m_psrawi(_m_paddw(v201, v107), 5u));
  v110 = _m_punpckhbw(v106, v105);
  v111 = _m_punpcklbw(v106, v105);
  v112 = _m_punpcklbw(v109, v108);
  v113 = _m_punpckhbw(v109, v108);
  v114 = _m_punpcklwd(v111, v112);
  v115 = _m_punpcklwd(v113, v110);
  v116 = *(__m64 **)(a2 + 4);
  v117 = _m_punpckhwd(v111, v112);
  v118 = _m_punpckhwd(v113, v110);
  *(__m64 *)*(_DWORD *)a2 = _m_punpckldq(v114, v115);
  v119 = *(__m64 **)(a2 + 8);
  v116->m64_u64 = (unsigned __int64)_m_punpckhdq(v114, v115);
  v120 = *(__m64 **)(a2 + 12);
  v119->m64_u64 = (unsigned __int64)_m_punpckldq(v117, v118);
  v120->m64_u64 = (unsigned __int64)_m_punpckhdq(v117, v118);
  v121 = _m_psubw(v208, v210);
  v122 = _m_paddw(v208, v210);
  v123 = _m_paddw(v212, v214);
  v124 = _m_psubw(v212, v214);
  v125 = _m_punpckldq(_m_punpcklwd(v122, v123), _m_punpckhwd(v122, v123));
  v126 = _m_punpckldq(_m_punpcklwd(v121, v124), _m_punpckhwd(v121, v124));
  v127 = _m_paddw(v218, v219);
  v128 = _m_paddw(v216, v217);
  v129 = _m_psubw(v218, v219);
  v130 = _m_psubw(v216, v217);
  v131 = _m_punpckldq(_m_punpcklwd(v128, v127), _m_punpckhwd(v128, v127));
  v132 = _m_punpckldq(_m_punpcklwd(v130, v129), _m_punpckhwd(v130, v129));
  v133 = _m_punpckhdq(v125, v131);
  v134 = _m_punpckldq(v125, v131);
  v135 = _m_paddw(v134, v133);
  v136 = _m_psubw(v134, v133);
  v137 = _m_psubw(_m_pmulhw(_m_psllwi(_m_punpckhdq(v126, v132), 2u), (__m64)qword_455C20), v133);
  v138 = _m_punpckldq(v126, v132);
  v139 = _m_paddw(v138, v137);
  v140 = _m_psubw(v138, v137);
  v141 = _m_punpckldq(v208, v210);
  v142 = _m_punpckhdq(v210, v208);
  v209 = v135;
  v143 = _m_paddw(v141, v142);
  v144 = _m_psubw(v141, v142);
  v211 = v139;
  v145 = _m_punpckhdq(v214, v212);
  v146 = _m_punpckldq(v212, v214);
  v147 = _m_paddw(v146, v145);
  v213 = v140;
  v148 = _m_psubw(v146, v145);
  v215 = v136;
  v149 = _m_punpckhdq(_m_punpckhwd(v144, v148), _m_punpcklwd(v143, v147));
  v150 = _m_punpckhdq(_m_punpcklwd(v144, v148), _m_punpckhwd(v143, v147));
  v151 = _m_punpckhdq(v217, v216);
  v152 = _m_punpckldq(v216, v217);
  v153 = _m_paddw(v152, v151);
  v154 = _m_psubw(v152, v151);
  v155 = _m_punpckhdq(v219, v218);
  v156 = _m_punpckldq(v218, v219);
  v157 = _m_paddw(v156, v155);
  v158 = _m_psubw(v156, v155);
  v159 = _m_punpckhdq(_m_punpckhwd(v154, v158), _m_punpcklwd(v153, v157));
  v160 = _m_punpckhdq(_m_punpcklwd(v154, v158), _m_punpckhwd(v153, v157));
  v161 = v149;
  v162 = _m_punpckldq(v149, v159);
  v163 = _m_punpckhdq(v161, v159);
  v164 = _m_punpckhdq(v150, v160);
  v165 = _m_psubw(v163, v164);
  v166 = _m_paddw(v163, v164);
  v167 = _m_psllwi(v162, 2u);
  v168 = _m_psllwi(_m_punpckldq(v150, v160), 2u);
  v169 = _m_pmulhw(v167, (__m64)qword_455C38);
  v170 = _m_pmulhw(v168, (__m64)qword_455C40);
  v171 = _m_psubw(_m_paddw(_m_pmulhw(v168, (__m64)qword_455C30), _m_pmulhw(v167, (__m64)qword_455C28)), v166);
  v172 = _m_psubw(_m_pmulhw(_m_psllwi(v165, 2u), (__m64)qword_455C20), v171);
  v173 = _m_packsswb(_m_psrawi(_m_paddw(v211, v171), 5u), _m_psrawi(_m_psubw(v209, v166), 5u));
  v174 = _m_packsswb(_m_psrawi(_m_paddw(v209, v166), 5u), _m_psrawi(_m_psubw(v211, v171), 5u));
  v175 = _m_paddw(_m_paddw(v169, v170), v172);
  v176 = _m_packsswb(_m_psrawi(_m_psubw(v215, v175), 5u), _m_psrawi(_m_psubw(v213, v172), 5u));
  v177 = _m_packsswb(_m_psrawi(_m_paddw(v213, v172), 5u), _m_psrawi(_m_paddw(v215, v175), 5u));
  v178 = _m_punpckhbw(v174, v173);
  v179 = _m_punpcklbw(v174, v173);
  v180 = _m_punpcklbw(v177, v176);
  v181 = _m_punpckhbw(v177, v176);
  v182 = _m_punpcklwd(v179, v180);
  v183 = _m_punpcklwd(v181, v178);
  v184 = *(__m64 **)(a2 + 20);
  v185 = _m_punpckhwd(v179, v180);
  v186 = _m_punpckhwd(v181, v178);
  *(__m64 *)*(_DWORD *)(a2 + 16) = _m_punpckldq(v182, v183);
  v187 = *(__m64 **)(a2 + 24);
  v184->m64_u64 = (unsigned __int64)_m_punpckhdq(v182, v183);
  v189 = *(__m64 **)(a2 + 28);
  v187->m64_u64 = (unsigned __int64)_m_punpckldq(v185, v186);
  v189->m64_u64 = (unsigned __int64)_m_punpckhdq(v185, v186);
  return a2 + 28;
}
