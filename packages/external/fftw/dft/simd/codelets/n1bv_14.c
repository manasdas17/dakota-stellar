/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun Jul 12 06:39:23 EDT 2009 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 14 -name n1bv_14 -include n1b.h */

/*
 * This function contains 74 FP additions, 48 FP multiplications,
 * (or, 32 additions, 6 multiplications, 42 fused multiply/add),
 * 63 stack variables, 6 constants, and 28 memory accesses
 */
#include "n1b.h"

static void n1bv_14(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP900968867, +0.900968867902419126236102319507445051165919162);
     DVK(KP801937735, +0.801937735804838252472204639014890102331838324);
     DVK(KP974927912, +0.974927912181823607018131682993931217232785801);
     DVK(KP692021471, +0.692021471630095869627814897002069140197260599);
     DVK(KP554958132, +0.554958132087371191422194871006410481067288862);
     DVK(KP356895867, +0.356895867892209443894399510021300583399127187);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V TH, T3, TP, Tn, Ta, Tu, TU, TK, TO, Tk, TM, Tg, TL, Td, T1;
	  V T2;
	  T1 = LD(&(xi[0]), ivs, &(xi[0]));
	  T2 = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
	  {
	       V Ti, TI, T6, TJ, T9, Tj, Te, Tf, Tb, Tc;
	       {
		    V T4, T5, T7, T8, Tl, Tm;
		    T4 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    T7 = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    T8 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    Tl = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    Tm = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    Ti = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    TH = VADD(T1, T2);
		    T3 = VSUB(T1, T2);
		    TI = VADD(T4, T5);
		    T6 = VSUB(T4, T5);
		    TJ = VADD(T7, T8);
		    T9 = VSUB(T7, T8);
		    TP = VADD(Tl, Tm);
		    Tn = VSUB(Tl, Tm);
		    Tj = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    Te = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    Tf = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    Tb = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    Tc = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
	       }
	       Ta = VADD(T6, T9);
	       Tu = VSUB(T6, T9);
	       TU = VSUB(TI, TJ);
	       TK = VADD(TI, TJ);
	       TO = VADD(Ti, Tj);
	       Tk = VSUB(Ti, Tj);
	       TM = VADD(Te, Tf);
	       Tg = VSUB(Te, Tf);
	       TL = VADD(Tb, Tc);
	       Td = VSUB(Tb, Tc);
	  }
	  {
	       V T13, TG, TY, T18, TB, Tw, TT, Tz, T11, T16, TE, Tr, TV, TQ;
	       TV = VSUB(TP, TO);
	       TQ = VADD(TO, TP);
	       {
		    V Ts, To, TW, TN;
		    Ts = VSUB(Tk, Tn);
		    To = VADD(Tk, Tn);
		    TW = VSUB(TM, TL);
		    TN = VADD(TL, TM);
		    {
			 V Tt, Th, TR, T12;
			 Tt = VSUB(Td, Tg);
			 Th = VADD(Td, Tg);
			 TR = VFNMS(LDK(KP356895867), TK, TQ);
			 T12 = VFNMS(LDK(KP554958132), TV, TU);
			 {
			      V Tx, TF, TZ, T14;
			      Tx = VFNMS(LDK(KP356895867), Ta, To);
			      TF = VFMA(LDK(KP554958132), Ts, Tu);
			      ST(&(xo[0]), VADD(TH, VADD(TK, VADD(TN, TQ))), ovs, &(xo[0]));
			      TZ = VFNMS(LDK(KP356895867), TN, TK);
			      T14 = VFNMS(LDK(KP356895867), TQ, TN);
			      {
				   V TX, T17, TC, Tp;
				   TX = VFMA(LDK(KP554958132), TW, TV);
				   T17 = VFMA(LDK(KP554958132), TU, TW);
				   ST(&(xo[WS(os, 7)]), VADD(T3, VADD(Ta, VADD(Th, To))), ovs, &(xo[WS(os, 1)]));
				   TC = VFNMS(LDK(KP356895867), Th, Ta);
				   Tp = VFNMS(LDK(KP356895867), To, Th);
				   {
					V TA, Tv, TS, Ty;
					TA = VFMA(LDK(KP554958132), Tt, Ts);
					Tv = VFNMS(LDK(KP554958132), Tu, Tt);
					TS = VFNMS(LDK(KP692021471), TR, TN);
					T13 = VMUL(LDK(KP974927912), VFNMS(LDK(KP801937735), T12, TW));
					Ty = VFNMS(LDK(KP692021471), Tx, Th);
					TG = VMUL(LDK(KP974927912), VFMA(LDK(KP801937735), TF, Tt));
					{
					     V T10, T15, TD, Tq;
					     T10 = VFNMS(LDK(KP692021471), TZ, TQ);
					     T15 = VFNMS(LDK(KP692021471), T14, TK);
					     TY = VMUL(LDK(KP974927912), VFMA(LDK(KP801937735), TX, TU));
					     T18 = VMUL(LDK(KP974927912), VFNMS(LDK(KP801937735), T17, TV));
					     TD = VFNMS(LDK(KP692021471), TC, To);
					     Tq = VFNMS(LDK(KP692021471), Tp, Ta);
					     TB = VMUL(LDK(KP974927912), VFNMS(LDK(KP801937735), TA, Tu));
					     Tw = VMUL(LDK(KP974927912), VFNMS(LDK(KP801937735), Tv, Ts));
					     TT = VFNMS(LDK(KP900968867), TS, TH);
					     Tz = VFNMS(LDK(KP900968867), Ty, T3);
					     T11 = VFNMS(LDK(KP900968867), T10, TH);
					     T16 = VFNMS(LDK(KP900968867), T15, TH);
					     TE = VFNMS(LDK(KP900968867), TD, T3);
					     Tr = VFNMS(LDK(KP900968867), Tq, T3);
					}
				   }
			      }
			 }
		    }
	       }
	       ST(&(xo[WS(os, 2)]), VFMAI(TY, TT), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 12)]), VFNMSI(TY, TT), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 9)]), VFMAI(TB, Tz), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 5)]), VFNMSI(TB, Tz), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 6)]), VFMAI(T13, T11), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 8)]), VFNMSI(T13, T11), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 4)]), VFMAI(T18, T16), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 10)]), VFNMSI(T18, T16), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 13)]), VFNMSI(TG, TE), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 1)]), VFMAI(TG, TE), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 11)]), VFNMSI(Tw, Tr), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 3)]), VFMAI(Tw, Tr), ovs, &(xo[WS(os, 1)]));
	  }
     }
}

static const kdft_desc desc = { 14, "n1bv_14", {32, 6, 42, 0}, &GENUS, 0, 0, 0, 0 };

void X(codelet_n1bv_14) (planner *p) {
     X(kdft_register) (p, n1bv_14, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw_c -simd -compact -variables 4 -pipeline-latency 8 -sign 1 -n 14 -name n1bv_14 -include n1b.h */

/*
 * This function contains 74 FP additions, 36 FP multiplications,
 * (or, 50 additions, 12 multiplications, 24 fused multiply/add),
 * 33 stack variables, 6 constants, and 28 memory accesses
 */
#include "n1b.h"

static void n1bv_14(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP900968867, +0.900968867902419126236102319507445051165919162);
     DVK(KP222520933, +0.222520933956314404288902564496794759466355569);
     DVK(KP623489801, +0.623489801858733530525004884004239810632274731);
     DVK(KP781831482, +0.781831482468029808708444526674057750232334519);
     DVK(KP974927912, +0.974927912181823607018131682993931217232785801);
     DVK(KP433883739, +0.433883739117558120475768332848358754609990728);
     INT i;
     const R *xi;
     R *xo;
     xi = ii;
     xo = io;
     for (i = v; i > 0; i = i - VL, xi = xi + (VL * ivs), xo = xo + (VL * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V Tp, Ty, Tl, TL, Tq, TE, T7, TJ, Ts, TB, Te, TK, Tr, TH, Tn;
	  V To;
	  Tn = LD(&(xi[0]), ivs, &(xi[0]));
	  To = LD(&(xi[WS(is, 7)]), ivs, &(xi[WS(is, 1)]));
	  Tp = VSUB(Tn, To);
	  Ty = VADD(Tn, To);
	  {
	       V Th, TC, Tk, TD;
	       {
		    V Tf, Tg, Ti, Tj;
		    Tf = LD(&(xi[WS(is, 4)]), ivs, &(xi[0]));
		    Tg = LD(&(xi[WS(is, 11)]), ivs, &(xi[WS(is, 1)]));
		    Th = VSUB(Tf, Tg);
		    TC = VADD(Tf, Tg);
		    Ti = LD(&(xi[WS(is, 10)]), ivs, &(xi[0]));
		    Tj = LD(&(xi[WS(is, 3)]), ivs, &(xi[WS(is, 1)]));
		    Tk = VSUB(Ti, Tj);
		    TD = VADD(Ti, Tj);
	       }
	       Tl = VSUB(Th, Tk);
	       TL = VSUB(TD, TC);
	       Tq = VADD(Th, Tk);
	       TE = VADD(TC, TD);
	  }
	  {
	       V T3, Tz, T6, TA;
	       {
		    V T1, T2, T4, T5;
		    T1 = LD(&(xi[WS(is, 2)]), ivs, &(xi[0]));
		    T2 = LD(&(xi[WS(is, 9)]), ivs, &(xi[WS(is, 1)]));
		    T3 = VSUB(T1, T2);
		    Tz = VADD(T1, T2);
		    T4 = LD(&(xi[WS(is, 12)]), ivs, &(xi[0]));
		    T5 = LD(&(xi[WS(is, 5)]), ivs, &(xi[WS(is, 1)]));
		    T6 = VSUB(T4, T5);
		    TA = VADD(T4, T5);
	       }
	       T7 = VSUB(T3, T6);
	       TJ = VSUB(Tz, TA);
	       Ts = VADD(T3, T6);
	       TB = VADD(Tz, TA);
	  }
	  {
	       V Ta, TF, Td, TG;
	       {
		    V T8, T9, Tb, Tc;
		    T8 = LD(&(xi[WS(is, 6)]), ivs, &(xi[0]));
		    T9 = LD(&(xi[WS(is, 13)]), ivs, &(xi[WS(is, 1)]));
		    Ta = VSUB(T8, T9);
		    TF = VADD(T8, T9);
		    Tb = LD(&(xi[WS(is, 8)]), ivs, &(xi[0]));
		    Tc = LD(&(xi[WS(is, 1)]), ivs, &(xi[WS(is, 1)]));
		    Td = VSUB(Tb, Tc);
		    TG = VADD(Tb, Tc);
	       }
	       Te = VSUB(Ta, Td);
	       TK = VSUB(TG, TF);
	       Tr = VADD(Ta, Td);
	       TH = VADD(TF, TG);
	  }
	  ST(&(xo[WS(os, 7)]), VADD(Tp, VADD(Ts, VADD(Tq, Tr))), ovs, &(xo[WS(os, 1)]));
	  ST(&(xo[0]), VADD(Ty, VADD(TB, VADD(TE, TH))), ovs, &(xo[0]));
	  {
	       V Tm, Tt, TQ, TP;
	       Tm = VBYI(VFMA(LDK(KP433883739), T7, VFNMS(LDK(KP781831482), Tl, VMUL(LDK(KP974927912), Te))));
	       Tt = VFMA(LDK(KP623489801), Tq, VFNMS(LDK(KP222520933), Tr, VFNMS(LDK(KP900968867), Ts, Tp)));
	       ST(&(xo[WS(os, 3)]), VADD(Tm, Tt), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 11)]), VSUB(Tt, Tm), ovs, &(xo[WS(os, 1)]));
	       TQ = VBYI(VFMA(LDK(KP974927912), TJ, VFMA(LDK(KP433883739), TL, VMUL(LDK(KP781831482), TK))));
	       TP = VFMA(LDK(KP623489801), TH, VFNMS(LDK(KP900968867), TE, VFNMS(LDK(KP222520933), TB, Ty)));
	       ST(&(xo[WS(os, 12)]), VSUB(TP, TQ), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 2)]), VADD(TP, TQ), ovs, &(xo[0]));
	  }
	  {
	       V Tu, Tv, TM, TI;
	       Tu = VBYI(VFMA(LDK(KP781831482), T7, VFMA(LDK(KP974927912), Tl, VMUL(LDK(KP433883739), Te))));
	       Tv = VFMA(LDK(KP623489801), Ts, VFNMS(LDK(KP900968867), Tr, VFNMS(LDK(KP222520933), Tq, Tp)));
	       ST(&(xo[WS(os, 1)]), VADD(Tu, Tv), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 13)]), VSUB(Tv, Tu), ovs, &(xo[WS(os, 1)]));
	       TM = VBYI(VFNMS(LDK(KP433883739), TK, VFNMS(LDK(KP974927912), TL, VMUL(LDK(KP781831482), TJ))));
	       TI = VFMA(LDK(KP623489801), TB, VFNMS(LDK(KP900968867), TH, VFNMS(LDK(KP222520933), TE, Ty)));
	       ST(&(xo[WS(os, 6)]), VSUB(TI, TM), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 8)]), VADD(TI, TM), ovs, &(xo[0]));
	  }
	  {
	       V TO, TN, Tx, Tw;
	       TO = VBYI(VFMA(LDK(KP433883739), TJ, VFNMS(LDK(KP974927912), TK, VMUL(LDK(KP781831482), TL))));
	       TN = VFMA(LDK(KP623489801), TE, VFNMS(LDK(KP222520933), TH, VFNMS(LDK(KP900968867), TB, Ty)));
	       ST(&(xo[WS(os, 4)]), VSUB(TN, TO), ovs, &(xo[0]));
	       ST(&(xo[WS(os, 10)]), VADD(TN, TO), ovs, &(xo[0]));
	       Tx = VBYI(VFNMS(LDK(KP781831482), Te, VFNMS(LDK(KP433883739), Tl, VMUL(LDK(KP974927912), T7))));
	       Tw = VFMA(LDK(KP623489801), Tr, VFNMS(LDK(KP900968867), Tq, VFNMS(LDK(KP222520933), Ts, Tp)));
	       ST(&(xo[WS(os, 5)]), VSUB(Tw, Tx), ovs, &(xo[WS(os, 1)]));
	       ST(&(xo[WS(os, 9)]), VADD(Tx, Tw), ovs, &(xo[WS(os, 1)]));
	  }
     }
}

static const kdft_desc desc = { 14, "n1bv_14", {50, 12, 24, 0}, &GENUS, 0, 0, 0, 0 };

void X(codelet_n1bv_14) (planner *p) {
     X(kdft_register) (p, n1bv_14, &desc);
}

#endif				/* HAVE_FMA */
