# This Makefile.am specifies a set of codelets, efficient transforms
# of small sizes, that are used as building blocks (kernels) by FFTW
# to build up large transforms, as well as the options for generating
# and compiling them.

# You can customize FFTW for special needs, e.g. to handle certain
# sizes more efficiently, by adding new codelets to the lists of those
# included by default.  If you change the list of codelets, any new
# ones you added will be automatically generated when you run the
# bootstrap script (see "Generating your own code" in the FFTW
# manual).

###########################################################################
INCLUDE_DIRECTORIES(
  ${FFTW_SOURCE_DIR}/kernel ${FFTW_SOURCE_DIR}/dft
  ${FFTW_SOURCE_DIR}/dft/scalar)

###########################################################################
# n1_<n> is a hard-coded FFT of size <n> (base cases of FFT recursion)
SET(N1
  n1_2.c n1_3.c n1_4.c n1_5.c n1_6.c n1_7.c n1_8.c n1_9.c n1_10.c
  n1_11.c n1_12.c n1_13.c n1_14.c n1_15.c n1_16.c n1_32.c n1_64.c
  n1_20.c n1_25.c)

###########################################################################
# t1_<r> is a "twiddle" FFT of size <r>, implementing a radix-r DIT step
SET(T1
  t1_2.c t1_3.c t1_4.c t1_5.c t1_6.c t1_7.c t1_8.c t1_9.c
  t1_10.c t1_12.c t1_15.c t1_16.c t1_32.c t1_64.c
  t1_20.c t1_25.c)

# t2_<r> is also a twiddle FFT, but instead of using a complete lookup table
# of trig. functions, it partially generates the trig. values on the fly
# (this is faster for large sizes).
SET(T2
  t2_4.c t2_8.c t2_16.c t2_32.c t2_64.c t2_5.c t2_10.c t2_20.c t2_25.c)

###########################################################################
# q1_<r> is <r> twiddle FFTs of size <r> (DIF step), where the output is
# transposed.  This is used for in-place transposes in sizes that are
# divisible by <r>^2.  These codelets have size ~ <r>^2, so you should
# probably not use <r> bigger than 8 or so.
SET(Q1 q1_2.c q1_4.c q1_8.c  q1_3.c q1_5.c q1_6.c)

###########################################################################
SET(ALL_CODELETS ${N1} ${T1} ${T2} ${F1} ${F2} ${Q1} "codlist.c")
ADD_LIBRARY(dft_scalar_codelets ${ALL_CODELETS})
TARGET_LINK_LIBRARIES(dft_scalar_codelets dft dft_scalar)

