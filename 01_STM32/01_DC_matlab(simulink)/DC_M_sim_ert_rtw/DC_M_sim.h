/*
 * File: DC_M_sim.h
 *
 * Code generated for Simulink model 'DC_M_sim'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 05 21:06:19 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DC_M_sim_h_
#define RTW_HEADER_DC_M_sim_h_
#include <string.h>
#ifndef DC_M_sim_COMMON_INCLUDES_
# define DC_M_sim_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* DC_M_sim_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay;                    /* '<Root>/Unit Delay' */
  real_T speed_rad;                    /* '<Root>/Transfer Fcn' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  struct {
    void *AQHandles;
  } HiddenToAsyncQueue_InsertedFor_;   /* synthesized block */
} DW;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} X;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
} XDis;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[2];
    real_T odeF[3][2];
    ODE3_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Continuous states (auto storage) */
extern X rtX;

/* Block signals and states (auto storage) */
extern DW rtDW;

/* Model entry point functions */
extern void DC_M_sim_initialize(void);
extern void DC_M_sim_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<S2>/Derivative Gain' : Unused code path elimination
 * Block '<S3>/DTDup' : Unused code path elimination
 * Block '<S3>/Diff' : Unused code path elimination
 * Block '<S3>/TSamp' : Unused code path elimination
 * Block '<S3>/UD' : Unused code path elimination
 * Block '<S2>/Integral Gain' : Unused code path elimination
 * Block '<S2>/Integrator' : Unused code path elimination
 * Block '<S2>/Proportional Gain' : Unused code path elimination
 * Block '<S2>/Sum' : Unused code path elimination
 * Block '<S1>/Discrete State-Space' : Unused code path elimination
 * Block '<S1>/Gain' : Unused code path elimination
 * Block '<S1>/Saturation' : Unused code path elimination
 * Block '<S1>/Scope' : Unused code path elimination
 * Block '<S1>/Scope1' : Unused code path elimination
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Step' : Unused code path elimination
 * Block '<S1>/Sum' : Unused code path elimination
 * Block '<S1>/Sum1' : Unused code path elimination
 * Block '<Root>/Unit Delay1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'DC_M_sim'
 * '<S1>'   : 'DC_M_sim/Subsystem'
 * '<S2>'   : 'DC_M_sim/Subsystem/Discrete PID Controller'
 * '<S3>'   : 'DC_M_sim/Subsystem/Discrete PID Controller/Differentiator'
 */
#endif                                 /* RTW_HEADER_DC_M_sim_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
