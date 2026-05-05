/*
 * File: Subsystem.c
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue May 05 21:06:41 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Subsystem.h"

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

/* Block signals and states (auto storage) */
DW rtDW;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Subsystem_step(void)
{
  /* local block i/o variables */
  real_T rtb_TSamp;
  real_T rtb_Saturation;
  real_T Sum;
  int32_T tmp;

  /* DiscreteStateSpace: '<S1>/Discrete State-Space' */
  {
    rtDW.DiscreteStateSpace[0] = (1.0)*rtDW.Observer[0];
    rtDW.DiscreteStateSpace[1] = (1.0)*rtDW.Observer[1];
    rtDW.DiscreteStateSpace[2] = (1.0)*rtDW.Observer[2];
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
   *  Inport: '<Root>/theta'
   *  Sum: '<S1>/Sum1'
   */
  Sum = ((real_T)tmp - rtU.theta) * 5.0 - rtDW.DiscreteStateSpace[1];

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

  /* Saturate: '<S1>/Saturation' */
  if (Sum > 12.0) {
    rtb_Saturation = 12.0;
  } else if (Sum < -12.0) {
    rtb_Saturation = -12.0;
  } else {
    rtb_Saturation = Sum;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* Outport: '<Root>/input' */
  rtY.input = Sum;

  /* Update for DiscreteStateSpace: '<S1>/Discrete State-Space' */
  {
    real_T xnew[3];
    xnew[0] = (0.8639107020615695)*rtDW.Observer[0] + (0.00092744868888819626)*
      rtDW.Observer[1]
      + (4.7561471225035705E-7)*rtDW.Observer[2];
    xnew[0] += (8.3208827832216517E-6)*rtb_Saturation + (0.13608929793843055)*
      rtU.theta;
    xnew[1] = (-6.070223424359467)*rtDW.Observer[0] + (0.98979763893419692)*
      rtDW.Observer[1]
      + (0.000995398494069185)*rtDW.Observer[2];
    xnew[1] += (0.017414503753586993)*rtb_Saturation + (6.0702234243594662)*
      rtU.theta;
    xnew[2] = (-116.35513631809506)*rtDW.Observer[0] + (-0.059451839031294619)*
      rtDW.Observer[1]
      + (0.99997993250637562)*rtDW.Observer[2];
    xnew[2] += (-0.00035108094409360389)*rtb_Saturation + (116.35513631809508)*
      rtU.theta;
    (void) memcpy(&rtDW.Observer[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteIntegrator: '<S2>/Integrator' */
  rtDW.Integrator_DSTATE = rtDW.Integrator;

  /* Update for Delay: '<S3>/UD' */
  rtDW.UD_DSTATE = rtb_TSamp;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rtM->Timing.t[0] =
    (++rtM->Timing.clockTick0) * rtM->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, ((const char_T **)
      (&rtmGetErrorStatus(rtM))));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&rtM->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.001;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
