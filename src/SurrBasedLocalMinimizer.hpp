/*  _______________________________________________________________________

    DAKOTA: Design Analysis Kit for Optimization and Terascale Applications
    Copyright 2014 Sandia Corporation.
    This software is distributed under the GNU Lesser General Public License.
    For more information, see the README file in the top Dakota directory.
    _______________________________________________________________________ */

//- Class:       SurrBasedLocalMinimizer
//- Description: A local surrogate-based algorithm which successively invokes
//-              a minimizer on an approximate model within a trust region.
//- Owner:       Mike Eldred
//- Checked by:
//- Version: $Id: SurrBasedLocalMinimizer.hpp 6879 2010-07-30 01:05:11Z mseldre $

#ifndef SURR_BASED_LOCAL_MINIMIZER_H
#define SURR_BASED_LOCAL_MINIMIZER_H

#include "SurrBasedMinimizer.hpp"
#include "DakotaModel.hpp"

namespace Dakota {

class SurrBasedLevelData;


/// Class for provably-convergent local surrogate-based optimization
/// and nonlinear least squares.

/** This minimizer uses a SurrogateModel to perform minimization based
    on local, global, or hierarchical surrogates. It achieves provable
    convergence through the use of a sequence of trust regions and the
    application of surrogate corrections at the trust region centers. */

class SurrBasedLocalMinimizer: public SurrBasedMinimizer
{
public:

  //
  //- Heading: Constructor and destructor
  //

  /// constructor
  SurrBasedLocalMinimizer(ProblemDescDB& problem_db, Model& model);
  /// destructor
  ~SurrBasedLocalMinimizer();

protected:

  //
  //- Heading: Virtual function redefinitions
  //

  void pre_run();

  /// Performs local surrogate-based minimization by minimizing local,
  /// global, or hierarchical surrogates over a series of trust regions.
  void core_run();

  void post_run(std::ostream& s);

  void reset();

  //
  //- Heading: New Virtual functions
  //

  /// return the active SurrBasedLevelData instance
  virtual SurrBasedLevelData& trust_region() = 0;

  /// update the trust region bounds, strictly contained within global bounds
  virtual void update_trust_region() = 0;

  /// build the approximation over the current trust region
  virtual void build() = 0;
  /// solve the approximate subproblem
  virtual void minimize() = 0;
  /// verify the approximate iterate and update the trust region for
  /// the next approximate optimization cycle
  virtual void verify() = 0;

  //
  //- Heading: Member functions
  //

  /// construct and initialize approxSubProbModel
  void initialize_sub_model();
  /// construct and initialize approxSubProbMinimizer
  void initialize_sub_minimizer();
  /// initialize lagrangeMult and augLagrangeMult
  void initialize_multipliers();

  /// update the trust region bounds, strictly contained within global bounds
  void update_trust_region_data(SurrBasedLevelData& tr_data,
				const RealVector& parent_l_bnds,
				const RealVector& parent_u_bnds);

  /// compute trust region ratio (for SBLM iterate acceptance and trust
  /// region resizing) and check for soft convergence (diminishing returns)
  void compute_trust_region_ratio(SurrBasedLevelData& tr_data,
				  bool check_interior = false);

  /// check for hard convergence (norm of projected gradient of
  /// merit function near zero)
  void hard_convergence_check(const Response& response_truth,
			      const RealVector& c_vars,
			      const RealVector& lower_bnds,
			      const RealVector& upper_bnds);

  /// initialize and update the penaltyParameter
  void update_penalty(const RealVector& fns_center_truth,
		      const RealVector& fns_star_truth);

  /// static function used to define the approximate subproblem objective.
  static void approx_subprob_objective_eval(const Variables& surrogate_vars,
					    const Variables& recast_vars,
					    const Response& surrogate_response,
					    Response& recast_response);
  /// static function used to define the approximate subproblem constraints.
  static void approx_subprob_constraint_eval(const Variables& surrogate_vars,
					     const Variables& recast_vars,
					     const Response& surrogate_response,
					     Response& recast_response);

  /// locate an approximate response with the data_pairs cache
  bool find_approx_response(const Variables& search_vars,Response& search_resp);

  /// relax constraints by updating bounds when current iterate is infeasible
  void relax_constraints(SurrBasedLevelData& tr_data);

  /// static function used by NPSOL as the objective function in the
  /// homotopy constraint relaxation formulation.
  static void hom_objective_eval(int& mode, int& n, double* tau_and_x,
				 double& f, double* grad_f, int&);
  /// static function used by NPSOL as the constraint function in the
  /// homotopy constraint relaxation formulation.
  static void hom_constraint_eval(int& mode, int& ncnln, int& n, int& nrowj,
				  int* needc, double* tau_and_x, double* c,
				  double* cjac, int& nstate);

  //
  //- Heading: Data members
  //

  /// the approximate sub-problem formulation solved on each approximate
  /// minimization cycle: may be a shallow copy of iteratedModel, or may
  /// involve a RecastModel recursion applied to iteratedModel
  Model approxSubProbModel;

  /// type of approximate subproblem objective: ORIGINAL_OBJ, LAGRANGIAN_OBJ,
  /// or AUGMENTED_LAGRANGIAN_OBJ
  short approxSubProbObj;
  /// type of approximate subproblem constraints: NO_CON, LINEARIZED_CON, or
  /// ORIGINAL_CON
  short approxSubProbCon;
  /// flag to indicate when approxSubProbModel involves a RecastModel recursion
  bool recastSubProb;
  /// type of merit function used in trust region ratio logic: PENALTY_MERIT,
  /// ADAPTIVE_PENALTY_MERIT, LAGRANGIAN_MERIT, or AUGMENTED_LAGRANGIAN_MERIT
  short meritFnType;
  /// type of iterate acceptance test logic: FILTER or TR_RATIO
  short acceptLogic;
  /// type of trust region constraint relaxation for infeasible starting
  /// points: NO_RELAX or HOMOTOPY
  short trConstraintRelax;

  /// iteration offset used to update the scaling of the penalty parameter
  /// for adaptive_penalty merit functions
  int penaltyIterOffset;

  // the +/- offsets for each of the variables in the current trust region
  //RealVector trustRegionOffset;
  /// original user specification for trustRegionFactor
  Real origTrustRegionFactor;
  /// a soft convergence control: stop SBLM when the trust region
  /// factor is reduced below the value of minTrustRegionFactor
  Real minTrustRegionFactor;
  /// trust region ratio min value: contract tr if ratio below this value
  Real trRatioContractValue;
  /// trust region ratio sufficient value: expand tr if ratio above this value
  Real trRatioExpandValue;
  /// trust region contraction factor
  Real gammaContract;
  /// trust region expansion factor
  Real gammaExpand;

  /// code indicating satisfaction of hard or soft convergence conditions
  short convergenceFlag;
  /// number of consecutive candidate point rejections.  If the
  /// count reaches softConvLimit, stop SBLM.
  unsigned short softConvCount;
  /// the limit on consecutive candidate point rejections.  If
  /// exceeded by softConvCount, stop SBLM.
  unsigned short softConvLimit;

  /// derivative order of truth data used within the SBLM process
  short truthSetRequest;
  /// derivative order of surrogate data used within the SBLM process
  short approxSetRequest;

  /// flags the use of surrogate correction techniques at the center
  /// of each trust region
  short correctionType;

  /// starting point prior to sequence of SBLM iterations
  RealVector initialPoint;
  
  /// Global lower bounds
  RealVector globalLowerBnds;
  /// Global Upper bounds
  RealVector globalUpperBnds;

  // Data needed for computing merit functions
  /// individual violations of nonlinear inequality constraint lower bounds
  RealVector nonlinIneqLowerBndsSlack;
  /// individual violations of nonlinear inequality constraint upper bounds
  RealVector nonlinIneqUpperBndsSlack;
  /// individual violations of nonlinear equality constraint targets
  RealVector nonlinEqTargetsSlack;
  /// constraint relaxation parameter
  Real tau;
  /// constraint relaxation parameter backoff parameter (multiplier)
  Real alpha;

  /// pointer to SBLM instance used in static member functions
  static SurrBasedLocalMinimizer* sblmInstance;
};


inline void SurrBasedLocalMinimizer::reset()
{
  convergenceFlag = softConvCount = sbIterNum = 0;

  penaltyIterOffset = -200; penaltyParameter  = 5.;

  eta               = 1.;
  alphaEta          = 0.1;
  betaEta           = 0.9;
  etaSequence       = eta*std::pow(2.*penaltyParameter, -alphaEta);
}

} // namespace Dakota

#endif
