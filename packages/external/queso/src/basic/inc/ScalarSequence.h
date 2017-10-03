//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// QUESO - a library to support the Quantification of Uncertainty
// for Estimation, Simulation and Optimization
//
// Copyright (C) 2008-2015 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-

#ifndef UQ_SCALAR_SEQUENCE_H
#define UQ_SCALAR_SEQUENCE_H

#include <queso/Fft.h>
#include <queso/UniformOneDGrid.h>
#include <queso/Environment.h>
#include <queso/Miscellaneous.h>
#include <queso/Defines.h>
#include <vector>
#include <complex>
#include <sys/time.h>

#define SCALAR_SEQUENCE_INIT_MPI_MSG 1
#define SCALAR_SEQUENCE_SIZE_MPI_MSG 1
#define SCALAR_SEQUENCE_DATA_MPI_MSG 1

namespace QUESO {

/*! \file ScalarSequence.h
 * \brief A templated class for handling scalar samples.
 *
 * \class ScalarSequence
 * \brief Class for handling scalar samples.
 *
 * This class handles scalar samples generated by an algorithm, as well
 * as operations that can be carried over them, e.g., calculation of means,
 * correlation  and covariance matrices. */

template <class T = double>
class ScalarSequence
{
public:
  //! @name Class typedefs
  //@{
  typedef typename std::vector<T>::iterator       seqScalarPositionIteratorTypedef;
  typedef typename std::vector<T>::const_iterator seqScalarPositionConstIteratorTypedef;
  //@}
    //! @name Constructor/Destructor methods
  //@{
  //! Default constructor.
  ScalarSequence(const BaseEnvironment& env,
                        unsigned int subSequenceSize,
                        const std::string& name);
  //! Destructor.
  ~ScalarSequence();
  //@}

  //! @name Set methods
  //@{
  //! Assignment operator; it copies \c rhs to \c this.
  ScalarSequence<T>& operator= (const ScalarSequence<T>& rhs);
  //@}

  //! @name Access methods
  //@{
  //! Access position \c posId of the sequence of scalars (const).
  const T&     operator[]                   (unsigned int posId) const;

  //! Access position \c posId of the sequence of scalars (non-const).
  /*! This routine deletes all stored computed scalars. */
  T&           operator[]                   (unsigned int posId);
  //@}

  //! @name Sequence methods
  //@{
  //! Access to QUESO environment.
  const BaseEnvironment& env               () const;

  //! Access to the name of the sequence of scalars.
  const std::string& name                         () const;

  //! Sets a new name to the sequence of scalars.
  void         setName                      (const std::string& newName);

  //! Clears the sequence of scalars.
  /*! Resets its values and then its size to zero.*/
  void         clear                        ();

  //! Size of the sub-sequence of scalars.
  unsigned int subSequenceSize              () const;

  //! Size of the unified sequence of scalars.
  unsigned int unifiedSequenceSize          (bool useOnlyInter0Comm) const;

  //! Resizes the size of the sequence of scalars.
  /*! This routine deletes all stored computed scalars. */
  void         resizeSequence               (unsigned int newSequenceSize);

  //! Sets \c numPos values of the sequence to zero, starting at position \c initialPos.
  /*! This routine deletes all stored computed scalars. */
  void         resetValues                  (unsigned int initialPos, unsigned int );

  //! Erases \c numPos values of the sequence, starting at position \c initialPos.
  /*! This routine deletes all stored computed scalars. */
  void         erasePositions               (unsigned int initialPos, unsigned int numPos);

  //! Gets the unified contents of processor of rank equals to 0.
  void         getUnifiedContentsAtProc0Only(bool useOnlyInter0Comm,
                                            std::vector<T>& outputVec) const;

  //! Finds the minimum value of the sub-sequence of scalars.
  const T&     subMinPlain                  () const;

  //! Finds the minimum value of the unified sequence of scalars.
  const T&     unifiedMinPlain              (bool                            useOnlyInter0Comm) const;

  //! Finds the maximum value of the sub-sequence of scalars.
  const T&     subMaxPlain                  () const;

  //! Finds the maximum value of the unified sequence of scalars.
  const T&     unifiedMaxPlain              (bool                            useOnlyInter0Comm) const;

  //! Finds the mean value of the sub-sequence of scalars.
  const T&     subMeanPlain                 () const;

  //! Finds the mean value of the unified sequence of scalars.
  const T&     unifiedMeanPlain             (bool                            useOnlyInter0Comm) const;

  //! Finds the median value of the sub-sequence of scalars.
  const T&     subMedianPlain               () const;

  //! Finds the median value of the unified sequence of scalars.
  const T&     unifiedMedianPlain           (bool                            useOnlyInter0Comm) const;

  //! Finds the variance of a sample of the sub-sequence of scalars.
  const T&     subSampleVariancePlain       () const;

  //! Finds the variance of a sample of the unified sequence of scalars.
  const T&     unifiedSampleVariancePlain   (bool                            useOnlyInter0Comm) const;

  //! Deletes all stored scalars.
  void         deleteStoredScalars          ();

  //! Sets the values of the sequence as a Gaussian distribution of mean given by \c meanVec and standard deviation by \c stdDevVec.
  /*! This routine deletes all stored computed scalars. */
  void         setGaussian                  (const T& mean, const T& stdDev);

  //! Sets the values of the sequence as a uniform distribution between the values given by vectors \c aVec and \c bVec.
  /*! This routine deletes all stored computed scalars. */
  void         setUniform                   (const T& a,    const T& b     );

  //! Uniformly samples from the CDF from the sub-sequence.
  void         subUniformlySampledCdf       (unsigned int                    numIntervals,
                                             T&                              minDomainValue,
                                             T&                              maxDomainValue,
                                             std::vector<T>&                 cdfValues) const;

  //! Uniformly samples from the CDF from the unified sequence.
  void         unifiedUniformlySampledCdf   (bool                            useOnlyInter0Comm,
                                             unsigned int                    numIntervals,
                                             T&                              unifiedMinDomainValue,
                                             T&                              unifiedMaxDomainValue,
                                             std::vector<T>&                 unifiedCdfValues) const;
  //! Finds the Cumulative Distribution Function (CDF) of the sub-sequence of scalars.
  void         subBasicCdf                  (unsigned int                    numIntervals,
                                             UniformOneDGrid<T>*&     gridValues,
                                             std::vector<T>&                 cdfValues) const;
  //! Finds the Weighted Cumulative Distribution Function (CDF) of the sub-sequence of scalars.
  void         subWeightCdf                 (unsigned int                    numIntervals,
                                             std::vector<T>&                 gridValues,
                                             std::vector<T>&                 cdfValues) const;

  //! Finds the Weighted Cumulative Distribution Function (CDF) of the sub-sequence of scalars.
  void         subWeightCdf                 (unsigned int                    numIntervals,
                                             UniformOneDGrid<T>*&     gridValues,
                                             std::vector<T>&                 cdfValues) const;

  //! Finds the mean value of the sub-sequence, considering \c numPos positions starting at position \c initialPos.
  T            subMeanExtra                 (unsigned int                    initialPos,
                                            unsigned int                    numPos) const;

  //! Finds the mean value of the unified sequence of \c numPos positions starting at position \c initialPos.
  T            unifiedMeanExtra             (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    localNumPos) const;

  //! Finds the median value of the sub-sequence, considering \c numPos positions starting at position \c initialPos.
  T            subMedianExtra               (unsigned int                    initialPos,
                                             unsigned int                    numPos) const;

  //! Finds the median value of the unified sequence, considering \c numPos positions starting at position \c initialPos.
  T            unifiedMedianExtra           (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    localNumPos) const;

  //! Finds the sample variance of the sub-sequence,  considering \c numPos positions starting at position \c initialPos and of mean \c meanVec.
  /*! Output: calculated sample variance of the sub-sequence of scalars.
   * The sample variance @f$ \sigma_y^2 @f$ is the second sample central moment and is defined by
   * @f$ \sigma_y^2 = \frac{1}{n} \sum_{i=1}^n \left(y_i - \mu \right)^2 @f$, where @f$ \mu @f$ is
   * the sample mean and @f$ n @f$ is the sample size. This procedure lets the users choose the initial
   * position and the number of elements of the sequence which will be used to evaluate the sample variance.*/
  T            subSampleVarianceExtra       (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             const T&                        meanValue) const;
    //! Finds the sample variance of the unified sequence,  considering \c numPos positions starting at position \c initialPos and of mean \c meanVec.
  /*! Output: \param samVec is the vector of the calculated sample variance of the unified sequence of scalars.*/
  T            unifiedSampleVarianceExtra   (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    localNumPos,
                                             const T&                        unifiedMeanValue) const;
  //! Finds the sample standard deviation of the unified sequence,  considering \c numPos positions starting at position \c initialPos and of mean \c meanValue.
  T            subSampleStd                 (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             const T&                        meanValue) const;
  //! Finds the sample standard deviation of the unified sequence,  considering \c localnumPos positions starting at position \c initialPos and of mean \c unifiedMeanValue.
  T            unifiedSampleStd             (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    localNumPos,
                                             const T&                        unifiedMeanValue) const;
  //! Finds the population variance of the sub-sequence, considering \c numPos positions starting at position \c initialPos and of mean \c meanValue.
  /*! Output: calculated population variance of the sub-sequence of scalars.
   * The population variance  @f$ \sigma^2 @f$ is defined by
   * @f$ \sigma^2 = \frac{1}{n-1} \sum_{i=1}^n \left(y_i - \mu \right)^2 @f$, where @f$ \mu @f$
   * is the sample mean and @f$ n @f$ is the sample size. This procedure lets the users choose the
   * initial position and the number of elements of the sequence which will be used to evaluate the
   * population variance .*/
  T            subPopulationVariance        (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             const T&                        meanValue) const;
  //! Finds the population variance of the unified sequence, considering \c numPos positions starting at position \c initialPos and of mean \c meanValue.
  /*! Output: calculated population variance of the unified sequence of scalars. */
  T            unifiedPopulationVariance    (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             const T&                        unifiedMeanValue) const;
  //! Calculates the autocovariance.
  /*! The autocovariance is the covariance of a variable with itself at some other time. It is
   * calculated over a sequence of scalars with initial position \c initialPos, considering
   * \c numPos positions, a lag of \c lag, with mean given by \c meanValue.
   * Output: the calculated autocovariances of the sequence of scalars.   */
  T            autoCovariance               (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             const T&                        meanValue,
                                             unsigned int                    lag) const;

  //! Calculates the autocorrelation via definition.
  /*! Autocorrelation is the cross-correlation of a variable with itself; it describes the
   * correlation between values of the process at different times, as a function of the two
   * times. It is calculated over a sequence of vectors with initial position \c initialPos,
   * considering \c numPos positions, a lag of \c lag, with mean given by \c meanValue.
   * Output: the calculated autocorrelations of the sequence of vectors.   */
  T            autoCorrViaDef               (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             unsigned int                    lag) const;

  //! Calculates the autocorrelation via  Fast Fourier transforms (FFT).
  void         autoCorrViaFft               (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             unsigned int                    maxLag,
                                             std::vector<T>&                 autoCorrs) const;

  //! Calculates the sum of autocorrelation via  Fast Fourier transforms (FFT).
  void         autoCorrViaFft               (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             unsigned int                    numSum,
                                             T&                              autoCorrsSum) const;
  //! Finds the minimum and the maximum values of the sub-sequence, considering \c numPos positions starting at position \c initialPos.
  void         subMinMaxExtra               (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             T&                              minValue,
                                             T&                              maxValue) const;
  //! Finds the minimum and the maximum values of the unified sequence, considering \c numPos positions starting at position \c initialPos.
  void         unifiedMinMaxExtra           (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             T&                              unifiedMinValue,
                                             T&                              unifiedMaxValue) const;
  //! Calculates the histogram of the sub-sequence.
  /*! It requires the specification of the maximum (\c maxHorizontalValue) and the minimum
   * (\c minHorizontalValue) values if the data and the initial position (\c initialPos)
   * from where the data will be considered. Output: the center of each bin (\c centers)
   * and the number of data occurrences in each bin (\c bins).*/
  void         subHistogram                 (unsigned int                    initialPos,
                                             const T&                        minHorizontalValue,
                                             const T&                        maxHorizontalValue,
                                             std::vector<T>&                 centers,
                                             std::vector<unsigned int>&      bins) const;
  //! Calculates the histogram of the unified sequence.
  void         unifiedHistogram             (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             const T&                        unifiedMinHorizontalValue,
                                             const T&                        unifiedMaxHorizontalValue,
                                             std::vector<T>&                 unifiedCenters,
                                             std::vector<unsigned int>&      unifiedBins) const;
  //! Calculates the histogram of the sub-sequence.
  /*! It requires the specification of the maximum (\c maxHorizontalValue) and the minimum
   * (\c minHorizontalValue) values if the data and the initial position (\c initialPos)
   * from where the data will be considered. Output: grid values that will act as the center
   * of each bin (\c gridValues) and the number of data occurrences in each bin (\c bins).*/
  void         subBasicHistogram            (unsigned int                    initialPos,
                                             const T&                        minHorizontalValue,
                                             const T&                        maxHorizontalValue,
                                             UniformOneDGrid<T>*&     gridValues,
                                             std::vector<unsigned int>&      bins) const;
  //! Calculates the weighted histogram of the sub-sequence.
  /*! TODO:Note that this method is exactly the same as subBasicHistogram().*/
  /*! It requires the specification of the maximum (\c maxHorizontalValue) and the minimum
   * (\c minHorizontalValue) values if the data and the initial position (\c initialPos)
   * from where the data will be considered. Output: grid values that will act as the center
   * of each bin (\c gridValues) and the number of data occurrences in each bin (\c bins).*/
  void         subWeightHistogram           (unsigned int                    initialPos,
                                             const T&                        minHorizontalValue,
                                             const T&                        maxHorizontalValue,
                                             UniformOneDGrid<T>*&     gridValues,
                                             std::vector<unsigned int>&      bins) const;
  //! Calculates the weighted histogram of the sub-sequence.
  /*! In this method, \c gridValues is a std::vector<T>, but internally, it will be copied to an
   * structure of the type UniformOneDGrid<T>. */
  void         subWeightHistogram           (unsigned int                    initialPos,
                                             const T&                        minHorizontalValue,
                                             const T&                        maxHorizontalValue,
                                             std::vector<T>&                 gridValues,
                                             std::vector<unsigned int>&      bins) const;
  //! Sorts the sub-sequence of scalars.
  void         subSort                      (unsigned int                    initialPos,
                                             ScalarSequence<T>&       sortedSequence) const;
  //! Sorts the unified sequence of scalars.
  void         unifiedSort                  (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             ScalarSequence<T>&       unifiedSortedSequence) const;
  //! Returns the interquartile range of the values in the sub-sequence.
  /*! The IQR is a robust estimate of the spread of the data, since changes in the upper and
  * lower 25% of the data do not affect it. If there are outliers in the data, then the IQR
  * is more representative than the standard deviation as an estimate of the spread of the
  * body of the data. The IQR is less efficient than the standard deviation as an estimate
  * of the spread when the data is all from the normal distribution. (from Matlab)*/
  T            subInterQuantileRange        (unsigned int                    initialPos) const;

  //! Returns the interquartile range of the values in the unified sequence.
  T            unifiedInterQuantileRange    (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos) const;

  //! Selects the scales (output value) for the kernel density estimation, considering only the sub-sequence.
  /*! The bandwidth of the kernel is a free parameter which exhibits a strong influence on
  * the resulting estimate. Silverman (1986) suggests the following normal-based estimates:
  *   S1 = 1.06 × (standard deviation) × n^{-1/5}
  *   S2 = 0.79 × (\c iqrValue) × n^{-1/5}, where \c iqrValue is the interquartile range
  *   OutputValue = 0.90 × minimum(standard deviation, \c iqrValue /1.34) × n^{-1/5}.
  * These estimates are popular due to their simplicity, and are used in QUESO with the
  * adaptation of the exponent oven the sample size n (-1/5) with -1/(4 + \c kdeDimension)
  * where \c kdeDimension is the  KDE dimension.  */
  T            subScaleForKde               (unsigned int                    initialPos,
                                             const T&                        iqrValue,
                                             unsigned int                    kdeDimension) const;

  //! Selects the scales (bandwidth) for the kernel density estimation, considering the unified sequence.
  T            unifiedScaleForKde           (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             const T&                        unifiedIqrValue,
                                             unsigned int                    kdeDimension) const;
  //! Gaussian kernel for the KDE estimate of the sub-sequence.
  /*! Computes a probability density estimate of the sample in \c this sub-sequence, starting
   * at position \c initialPos. \c densityValues is the vector of density values evaluated at
   * the points in \c evaluationPositions. The estimate is based on Gaussian (normal) kernel
   * function, using a window parameter (\c scaleValue).*/
  void         subGaussian1dKde             (unsigned int                    initialPos,
                                             double                          scaleValue,
                                             const std::vector<T>&           evaluationPositions,
                                             std::vector<double>&            densityValues) const;

  //! Gaussian kernel for the KDE estimate of the unified sequence.
  void         unifiedGaussian1dKde         (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             double                          unifiedScaleValue,
                                             const std::vector<T>&           unifiedEvaluationPositions,
                                             std::vector<double>&            unifiedDensityValues) const;

  //! Filters positions in the sequence of vectors.
  /*! Filtered positions will start at \c initialPos, and with spacing given by \c spacing. */
  void         filter                       (unsigned int                    initialPos,
                                             unsigned int                    spacing);

  //! Estimates convergence rate using Brooks & Gelman method.
  /*! TODO: implement me!*/
  T            brooksGelmanConvMeasure      (bool                            useOnlyInter0Comm,
					     unsigned int                    initialPos,
					     unsigned int                    spacing) const;

  //! Appends the scalar sequence \c src to \c this sequence.
  /*! This routine deletes all stored computed scalars. */
  void         append                       (const ScalarSequence<T>& src,
					     unsigned int                    srcInitialPos,
					     unsigned int                    srcNumPos);
  //! Finds the positions where the maximum element occurs in the sub-sequence.
  T            subPositionsOfMaximum        (const ScalarSequence<T>& subCorrespondingScalarValues,
					     ScalarSequence<T>&       subPositionsOfMaximum);
  //! Finds the positions where the maximum element occurs in the unified sequence.
  T            unifiedPositionsOfMaximum    (const ScalarSequence<T>& subCorrespondingScalarValues,
					     ScalarSequence<T>&       unifiedPositionsOfMaximum);

  //! Writes the sub-sequence to a file.
  /*! Given the allowed sub environments (\c allowedSubEnvIds) that are allowed to write to file,
   * together with the file name and type (\c fileName, \c fileType), it writes the entire sub-
   * sequence to the file. The sum of the initial position of the sequence (\c initialPos) with
   * the number of positions that will be written (\c numPos) must equal the size of the sequence. */
  void         subWriteContents             (unsigned int                    initialPos,
					     unsigned int                    numPos,
					     const std::string&              fileName,
					     const std::string&              fileType,
					     const std::set<unsigned int>&   allowedSubEnvIds) const;
  //! Writes the sub-sequence to a file.
  /*! Uses object of the type std::ofstream. */
  void         subWriteContents             (unsigned int                    initialPos,
					     unsigned int                    numPos,
					     std::ofstream&                  ofs,
					     const std::string&              fileType) const;
  //! Writes the unified sequence to a file.
  /*! Writes the unified sequence in Matlab/Octave format or, if enabled, in HDF5 format.*/
  void         unifiedWriteContents         (const std::string&              fileName,
					     const std::string&              fileType) const;

  //! Reads the unified sequence from a file.
  void         unifiedReadContents          (const std::string&              fileName,
					     const std::string&              fileType,
					     const unsigned int              subSequenceSize);
#ifdef QUESO_COMPUTES_EXTRA_POST_PROCESSING_STATISTICS
  T            bmm                          (unsigned int                    initialPos,
                                             unsigned int                    batchLength) const;
  void         psd                          (unsigned int                    initialPos,
                                             unsigned int                    numBlocks,
                                             double                          hopSizeRatio,
                                             std::vector<double>&            psdSequence) const;
  T            geweke                       (unsigned int                    initialPos,
                                             double                          ratioNa,
                                             double                          ratioNb) const;
  T            meanStacc                    (unsigned int                    initialPos) const;
  void         subCdfPercentageRange        (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             double                          range, // \in [0,1]
                                             T&                              lowerValue,
                                             T&                              upperValue) const;
  void         unifiedCdfPercentageRange    (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                             double                          range, // \in [0,1]
                                             T&                              lowerValue,
                                             T&                              upperValue) const;

  void         subCdfStacc                  (unsigned int                    initialPos,
                                             std::vector<double>&            cdfStaccValues,
                                             std::vector<double>&            cdfStaccValuesup,
                                             std::vector<double>&            cdfStaccValueslow,
                                             const ScalarSequence<T>& sortedDataValues) const;
  void         subCdfStacc                  (unsigned int                    initialPos,
                                             const std::vector<T>&           evaluationPositions,
                                             std::vector<double>&            cdfStaccValues) const;
  void         subUniformlySampledMdf       (unsigned int                    numIntervals,
                                             T&                              minDomainValue,
                                             T&                              maxDomainValue,
                                             std::vector<T>&                 mdfValues) const;
  T            subMeanCltStd                (unsigned int                    initialPos,
                                             unsigned int                    numPos,
                                                   const T&                        meanValue) const;
  T            unifiedMeanCltStd            (bool                            useOnlyInter0Comm,
                                             unsigned int                    initialPos,
                                             unsigned int                    localNumPos,
                                             const T&                        unifiedMeanValue) const;
#endif
//@}
private:
  //! Copies the scalar sequence \c src to \c this.
  /*! This routine deletes all stored computed scalars. */
  void         copy                         (const ScalarSequence<T>& src);

  //! Helper function to write header info for matlab files from all chains
  void writeUnifiedMatlabHeader(std::ofstream & ofs, double sequenceSize) const;

  //! Helper function to write header info for matlab files from one chain
  void writeSubMatlabHeader(std::ofstream & ofs, double sequenceSize) const;

  //! Helper function to write txt info for matlab files
  void writeTxtHeader(std::ofstream & ofs, double sequenceSize) const;

  //! Extracts a sequence of scalars.
  /*! The sequence of scalars has size \c numPos, and it will be extracted starting at position
   * (\c initialPos) of \c this sequence of scalars, given spacing \c spacing.*/
  void         extractScalarSeq             (unsigned int                    initialPos,
					     unsigned int                    spacing,
					     unsigned int                    numPos,
					     ScalarSequence<T>&       scalarSeq) const;
  //! Extracts the raw data.
  /*! This method saves in \c  rawData the data from the sequence of scalars (in private
   * attribute \c m_seq) starting at position (\c initialPos), with a spacing
   * of \c spacing until \c numPos positions have been extracted. */
  void         extractRawData               (unsigned int                    initialPos,
					     unsigned int                    spacing,
					     unsigned int                    numPos,
					     std::vector<double>&            rawData) const;

  //! The sequence of scalars. Access to private attribute \c m_seq.
  std::vector<T>& rawData                   ();

  //! Sorts the sequence of scalars in the private attribute \c m_seq.
  void         subSort                      ();

  //! Sorts/merges data in parallel using MPI.
  void         parallelMerge                (std::vector<T>&                 sortedBuffer,
					     const std::vector<T>&           leafData,
					     unsigned int                    treeLevel) const;

  const BaseEnvironment& m_env;
  std::string                   m_name;
  std::vector<T>                m_seq;

  mutable T*                    m_subMinPlain;
  mutable T*                    m_unifiedMinPlain;
  mutable T*                    m_subMaxPlain;
  mutable T*                    m_unifiedMaxPlain;
  mutable T*                    m_subMeanPlain;
  mutable T*                    m_unifiedMeanPlain;
  mutable T*                    m_subMedianPlain;
  mutable T*                    m_unifiedMedianPlain;
  mutable T*                    m_subSampleVariancePlain;
  mutable T*                    m_unifiedSampleVariancePlain;
};

// --------------------------------------------------
// Additional methods -------------------------------
// (outside class declaration) ----------------------
//---------------------------------------------------
template <class T>
void
ComputeSubGaussian2dKde(const ScalarSequence<T>& scalarSeq1,
                          const ScalarSequence<T>& scalarSeq2,
                          unsigned int                    initialPos,
                          double                          scaleValue1,
                          double                          scaleValue2,
                          const std::vector<T>&           evaluationPositions1,
                          const std::vector<T>&           evaluationPositions2,
                          std::vector<double>&            densityValues);

//---------------------------------------------------
template <class T>
void
ComputeUnifiedGaussian2dKde(bool                            useOnlyInter0Comm,           // INPUT
                              const ScalarSequence<T>& scalarSeq1,                  // INPUT
                              const ScalarSequence<T>& scalarSeq2,                  // INPUT
                              unsigned int                    initialPos,                  // INPUT
                              double                          unifiedScaleValue1,          // INPUT
                              double                          unifiedScaleValue2,          // INPUT
                              const std::vector<T>&           unifiedEvaluationPositions1, // INPUT
                              const std::vector<T>&           unifiedEvaluationPositions2, // INPUT
                              std::vector<double>&            unifiedDensityValues);        // OUTPUT

// --------------------------------------------------
template <class T>
void
ComputeCovCorrBetweenScalarSequences(
  const ScalarSequence<T>& subPSeq,
  const ScalarSequence<T>& subQSeq,
        unsigned int              subNumSamples,
        T&                        covValue,
        T&                        corrValue);

}  // End namespace QUESO

#endif // UQ_SCALAR_SEQUENCE_H
