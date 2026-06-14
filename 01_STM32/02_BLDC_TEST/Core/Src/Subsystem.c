/*
 * File: Subsystem.c
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Mon May 25 15:53:58 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Subsystem.h"

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
  real_T rtb_Saturation;
  real_T rtb_DiscreteStateSpace[3];
  real_T rtb_Sum1;
  real_T rtb_ProportionalGain;
  real_T rtb_TSamp;
  real_T Integrator;

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/ref'
   *  Inport: '<Root>/theta'
   */
  rtb_Sum1 = rtU.ref - rtU.theta;

  /* DiscreteStateSpace: '<S1>/Discrete State-Space' */
  {
    rtb_DiscreteStateSpace[0] = (1.0)*rtDW.Observer[0];
    rtb_DiscreteStateSpace[1] = (1.0)*rtDW.Observer[1];
    rtb_DiscreteStateSpace[2] = (1.0)*rtDW.Observer[2];
  }

  /* Sum: '<S1>/Sum' incorporates:
   *  Gain: '<S1>/Gain'
   */
  rtb_Sum1 = 5.0 * rtb_Sum1 - rtb_DiscreteStateSpace[1];

  /* Gain: '<S2>/Proportional Gain' */
  rtb_ProportionalGain = 2.8579582517938684 * rtb_Sum1;

  /* DiscreteIntegrator: '<S2>/Integrator' incorporates:
   *  Gain: '<S2>/Integral Gain'
   */
  Integrator = 20.384866275277236 * rtb_Sum1 * 0.001 + rtDW.Integrator_DSTATE;

  /* Gain: '<S2>/Derivative Gain' */
  rtb_Sum1 *= 0.0;

  /* SampleTimeMath: '<S3>/TSamp'
   *
   * About '<S3>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = rtb_Sum1 * 1000.0;

  /* Sum: '<S2>/Sum' incorporates:
   *  Delay: '<S3>/UD'
   *  Sum: '<S3>/Diff'
   */
  rtb_Sum1 = (rtb_ProportionalGain + Integrator) + (rtb_TSamp - rtDW.UD_DSTATE);

  /* Outport: '<Root>/input' */
  rtY.input = rtb_Sum1;

  /* Saturate: '<S1>/Saturation' */
  if (rtb_Sum1 > 12.0) {
    rtb_Saturation = 12.0;
  } else if (rtb_Sum1 < -12.0) {
    rtb_Saturation = -12.0;
  } else {
    rtb_Saturation = rtb_Sum1;
  }

  /* End of Saturate: '<S1>/Saturation' */
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
  rtDW.Integrator_DSTATE = Integrator;

  /* Update for Delay: '<S3>/UD' */
  rtDW.UD_DSTATE = rtb_TSamp;
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
