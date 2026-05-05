/*
 * File: DC_M_sim.c
 *
 * Code generated for Simulink model 'DC_M_sim'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 05 17:46:16 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "DC_M_sim.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

/* Continuous states */
X rtX;

/* Block signals and states (auto storage) */
DW rtDW;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* private model entry point functions */
extern void DC_M_sim_derivatives(void);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  DC_M_sim_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  DC_M_sim_step();
  DC_M_sim_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  DC_M_sim_step();
  DC_M_sim_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void DC_M_sim_step(void)
{
  /* local block i/o variables */
  real_T rtb_TSamp;
  real_T Sum;
  int32_T tmp;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Integrator: '<Root>/Integrator' */
  rtDW.theta = rtX.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(rtM)) {
    /* UnitDelay: '<Root>/Unit Delay1' */
    rtDW.UnitDelay1 = rtDW.UnitDelay1_DSTATE;

    /* UnitDelay: '<Root>/Unit Delay' */
    rtDW.UnitDelay = rtDW.UnitDelay_DSTATE;
  }

  /* Step: '<S1>/Step' */
  if (rtM->Timing.t[0] < 3.0) {
    tmp = 0;
  } else {
    tmp = 6;
  }

  /* End of Step: '<S1>/Step' */

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   *  Sum: '<S1>/Sum1'
   */
  Sum = ((real_T)tmp - rtDW.UnitDelay1) * 5.0 - rtDW.UnitDelay;
  if (rtmIsMajorTimeStep(rtM)) {
    /* DiscreteIntegrator: '<S2>/Integrator' incorporates:
     *  Gain: '<S2>/Integral Gain'
     */
    rtDW.Integrator = 20.384866275277236 * Sum * 0.001 + rtDW.Integrator_DSTATE;

    /* SampleTimeMath: '<S3>/TSamp' incorporates:
     *  Gain: '<S2>/Derivative Gain'
     *
     * About '<S3>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    rtb_TSamp = 0.0 * Sum * 1000.0;

    /* Sum: '<S2>/Sum' incorporates:
     *  Delay: '<S3>/UD'
     *  Gain: '<S2>/Proportional Gain'
     *  Sum: '<S3>/Diff'
     */
    Sum = (2.8579582517938684 * Sum + rtDW.Integrator) + (rtb_TSamp -
      rtDW.UD_DSTATE);

    /* Saturate: '<Root>/Saturation' */
    if (Sum > 12.0) {
      rtDW.Saturation = 12.0;
    } else if (Sum < -12.0) {
      rtDW.Saturation = -12.0;
    } else {
      rtDW.Saturation = Sum;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  rtDW.speed_rad = 0.0;
  rtDW.speed_rad += 17.495007132667617 * rtX.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(rtM)) {
    if (rtmIsMajorTimeStep(rtM)) {
      /* Update for UnitDelay: '<Root>/Unit Delay1' */
      rtDW.UnitDelay1_DSTATE = rtDW.theta;

      /* Update for UnitDelay: '<Root>/Unit Delay' */
      rtDW.UnitDelay_DSTATE = rtDW.speed_rad;

      /* Update for DiscreteIntegrator: '<S2>/Integrator' */
      rtDW.Integrator_DSTATE = rtDW.Integrator;

      /* Update for Delay: '<S3>/UD' */
      rtDW.UD_DSTATE = rtb_TSamp;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void DC_M_sim_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = rtDW.speed_rad;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -7.132667617689016 * rtX.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rtDW.Saturation;
}

/* Model initialize function */
void DC_M_sim_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **)
                         &rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->ModelData.intgData.y = rtM->ModelData.odeY;
  rtM->ModelData.intgData.f[0] = rtM->ModelData.odeF[0];
  rtM->ModelData.intgData.f[1] = rtM->ModelData.odeF[1];
  rtM->ModelData.intgData.f[2] = rtM->ModelData.odeF[2];
  rtM->ModelData.contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->ModelData.intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.001;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  rtX.Integrator_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  rtX.TransferFcn_CSTATE = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
