/*
 * problem_10_4_wf_model.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "problem_10_4_wf_model".
 *
 * Model version              : 1.225
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Tue Mar 05 11:09:50 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "problem_10_4_wf_model.h"
#include "problem_10_4_wf_model_private.h"
#include "problem_10_4_wf_model_dt.h"

/* Block signals (auto storage) */
B_problem_10_4_wf_model_T problem_10_4_wf_model_B;

/* Continuous states */
X_problem_10_4_wf_model_T problem_10_4_wf_model_X;

/* Block states (auto storage) */
DW_problem_10_4_wf_model_T problem_10_4_wf_model_DW;

/* Real-time model */
RT_MODEL_problem_10_4_wf_mode_T problem_10_4_wf_model_M_;
RT_MODEL_problem_10_4_wf_mode_T *const problem_10_4_wf_model_M =
  &problem_10_4_wf_model_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  problem_10_4_wf_model_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void problem_10_4_wf_model_output(void)
{
  /* local block i/o variables */
  real_T rtb_x_star[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Backgain;
  real_T rtb_Sum4[2];
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    /* set solver stop time */
    if (!(problem_10_4_wf_model_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&problem_10_4_wf_model_M->solverInfo,
                            ((problem_10_4_wf_model_M->Timing.clockTickH0 + 1) *
        problem_10_4_wf_model_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&problem_10_4_wf_model_M->solverInfo,
                            ((problem_10_4_wf_model_M->Timing.clockTick0 + 1) *
        problem_10_4_wf_model_M->Timing.stepSize0 +
        problem_10_4_wf_model_M->Timing.clockTickH0 *
        problem_10_4_wf_model_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(problem_10_4_wf_model_M)) {
    problem_10_4_wf_model_M->Timing.t[0] = rtsiGetT
      (&problem_10_4_wf_model_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: problem_10_4_wf_model/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (problem_10_4_wf_model_DW.HILReadEncoderTimebase_Task, 1,
         &problem_10_4_wf_model_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          problem_10_4_wf_model_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          problem_10_4_wf_model_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          problem_10_4_wf_model_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    problem_10_4_wf_model_B.TravelCounttorad =
      problem_10_4_wf_model_P.travel_gain * rtb_HILReadEncoderTimebase_o1 *
      problem_10_4_wf_model_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    problem_10_4_wf_model_B.Gain = problem_10_4_wf_model_P.Gain_Gain *
      problem_10_4_wf_model_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Travel_offset'
     */
    problem_10_4_wf_model_B.Sum3 = problem_10_4_wf_model_P.Travel_offset_Value +
      problem_10_4_wf_model_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    problem_10_4_wf_model_B.PitchCounttorad =
      problem_10_4_wf_model_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    problem_10_4_wf_model_B.Gain_i = problem_10_4_wf_model_P.Gain_Gain_a *
      problem_10_4_wf_model_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  problem_10_4_wf_model_B.Gain_d = (problem_10_4_wf_model_P.TravelTransferFcn_C *
    problem_10_4_wf_model_X.TravelTransferFcn_CSTATE +
    problem_10_4_wf_model_P.TravelTransferFcn_D *
    problem_10_4_wf_model_B.TravelCounttorad) *
    problem_10_4_wf_model_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  problem_10_4_wf_model_B.Gain_b = (problem_10_4_wf_model_P.PitchTransferFcn_C *
    problem_10_4_wf_model_X.PitchTransferFcn_CSTATE +
    problem_10_4_wf_model_P.PitchTransferFcn_D *
    problem_10_4_wf_model_B.PitchCounttorad) *
    problem_10_4_wf_model_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' */
    problem_10_4_wf_model_B.ElevationCounttorad =
      problem_10_4_wf_model_P.ElevationCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S7>/Gain' */
    problem_10_4_wf_model_B.Gain_e = problem_10_4_wf_model_P.Gain_Gain_lv *
      problem_10_4_wf_model_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    problem_10_4_wf_model_B.Sum = problem_10_4_wf_model_B.Gain_e +
      problem_10_4_wf_model_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  problem_10_4_wf_model_B.Gain_dg =
    (problem_10_4_wf_model_P.ElevationTransferFcn_C *
     problem_10_4_wf_model_X.ElevationTransferFcn_CSTATE +
     problem_10_4_wf_model_P.ElevationTransferFcn_D *
     problem_10_4_wf_model_B.ElevationCounttorad) *
    problem_10_4_wf_model_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  problem_10_4_wf_model_B.Gain1[0] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Sum3;
  problem_10_4_wf_model_B.Gain1[1] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Gain_d;
  problem_10_4_wf_model_B.Gain1[2] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Gain_i;
  problem_10_4_wf_model_B.Gain1[3] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Gain_b;
  problem_10_4_wf_model_B.Gain1[4] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Sum;
  problem_10_4_wf_model_B.Gain1[5] = problem_10_4_wf_model_P.Gain1_Gain *
    problem_10_4_wf_model_B.Gain_dg;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    /* ToFile: '<Root>/To File1' */
    {
      if (!(++problem_10_4_wf_model_DW.ToFile1_IWORK.Decimation % 1) &&
          (problem_10_4_wf_model_DW.ToFile1_IWORK.Count*7)+1 < 100000000 ) {
        FILE *fp = (FILE *) problem_10_4_wf_model_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[7];
          problem_10_4_wf_model_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = problem_10_4_wf_model_M->Timing.t[1];
          u[1] = problem_10_4_wf_model_B.Gain1[0];
          u[2] = problem_10_4_wf_model_B.Gain1[1];
          u[3] = problem_10_4_wf_model_B.Gain1[2];
          u[4] = problem_10_4_wf_model_B.Gain1[3];
          u[5] = problem_10_4_wf_model_B.Gain1[4];
          u[6] = problem_10_4_wf_model_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 7, fp) != 7) {
            rtmSetErrorStatus(problem_10_4_wf_model_M,
                              "Error writing to MAT-file data_wf.mat");
            return;
          }

          if (((++problem_10_4_wf_model_DW.ToFile1_IWORK.Count)*7)+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file data_wf.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/u' */
  {
    real_T *pDataValues = (real_T *) problem_10_4_wf_model_DW.u_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) problem_10_4_wf_model_DW.u_PWORK.TimePtr;
    int_T currTimeIndex = problem_10_4_wf_model_DW.u_IWORK.PrevIndex;
    real_T t = problem_10_4_wf_model_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[100]) {
      currTimeIndex = 99;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    problem_10_4_wf_model_DW.u_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&problem_10_4_wf_model_B.u[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 101;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&problem_10_4_wf_model_B.u[0])[elIdx] = pDataValues[currTimeIndex
                + 1];
              pDataValues += 101;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&problem_10_4_wf_model_B.u[0])[elIdx] = (real_T) rtInterpolate(d1,
              d2, f1, f2);
            pDataValues += 101;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<S5>/x_star' */
  {
    real_T *pDataValues = (real_T *)
      problem_10_4_wf_model_DW.x_star_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      problem_10_4_wf_model_DW.x_star_PWORK.TimePtr;
    int_T currTimeIndex = problem_10_4_wf_model_DW.x_star_IWORK.PrevIndex;
    real_T t = problem_10_4_wf_model_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[100]) {
      currTimeIndex = 99;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    problem_10_4_wf_model_DW.x_star_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_x_star[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 101;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_x_star[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 101;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_x_star[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 101;
          }
        }
      }
    }
  }

  /* Sum: '<S5>/Sum3' */
  for (i = 0; i < 6; i++) {
    problem_10_4_wf_model_B.Sum3_j[i] = problem_10_4_wf_model_B.Gain1[i] -
      rtb_x_star[i];
  }

  /* End of Sum: '<S5>/Sum3' */
  for (i = 0; i < 2; i++) {
    /* Gain: '<S5>/Gain' */
    problem_10_4_wf_model_B.Gain_k[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      problem_10_4_wf_model_B.Gain_k[i] += problem_10_4_wf_model_P.K_lq[(i_0 <<
        1) + i] * problem_10_4_wf_model_B.Sum3_j[i_0];
    }

    /* End of Gain: '<S5>/Gain' */

    /* Sum: '<S5>/Sum4' */
    rtb_Sum4[i] = problem_10_4_wf_model_B.u[i] -
      problem_10_4_wf_model_B.Gain_k[i];
  }

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Sum4[0] > problem_10_4_wf_model_P.Saturation_UpperSat) {
    rtb_Backgain = problem_10_4_wf_model_P.Saturation_UpperSat;
  } else if (rtb_Sum4[0] < problem_10_4_wf_model_P.Saturation_LowerSat) {
    rtb_Backgain = problem_10_4_wf_model_P.Saturation_LowerSat;
  } else {
    rtb_Backgain = rtb_Sum4[0];
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Saturate: '<Root>/Saturation'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  problem_10_4_wf_model_B.Sum1 = ((rtb_Backgain - problem_10_4_wf_model_B.Gain1
    [2]) * problem_10_4_wf_model_P.K_pp - problem_10_4_wf_model_P.K_pd *
    problem_10_4_wf_model_B.Gain1[3]) + problem_10_4_wf_model_P.Vd_ff;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (problem_10_4_wf_model_X.Integrator_CSTATE >=
      problem_10_4_wf_model_P.Integrator_UpperSat) {
    problem_10_4_wf_model_X.Integrator_CSTATE =
      problem_10_4_wf_model_P.Integrator_UpperSat;
  } else {
    if (problem_10_4_wf_model_X.Integrator_CSTATE <=
        problem_10_4_wf_model_P.Integrator_LowerSat) {
      problem_10_4_wf_model_X.Integrator_CSTATE =
        problem_10_4_wf_model_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Backgain = rtb_Sum4[1] - problem_10_4_wf_model_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  problem_10_4_wf_model_B.Sum2 = ((problem_10_4_wf_model_P.K_ep * rtb_Backgain +
    problem_10_4_wf_model_X.Integrator_CSTATE) - problem_10_4_wf_model_P.K_ed *
    problem_10_4_wf_model_B.Gain1[5]) + problem_10_4_wf_model_P.Vs_ff;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  problem_10_4_wf_model_B.K_ei = problem_10_4_wf_model_P.K_ei * rtb_Backgain;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((problem_10_4_wf_model_DW.TimeStampA >= problem_10_4_wf_model_M->Timing.t
       [0]) && (problem_10_4_wf_model_DW.TimeStampB >=
                problem_10_4_wf_model_M->Timing.t[0])) {
    rtb_Backgain = 0.0;
  } else {
    rtb_Backgain = problem_10_4_wf_model_DW.TimeStampA;
    lastU = &problem_10_4_wf_model_DW.LastUAtTimeA;
    if (problem_10_4_wf_model_DW.TimeStampA <
        problem_10_4_wf_model_DW.TimeStampB) {
      if (problem_10_4_wf_model_DW.TimeStampB <
          problem_10_4_wf_model_M->Timing.t[0]) {
        rtb_Backgain = problem_10_4_wf_model_DW.TimeStampB;
        lastU = &problem_10_4_wf_model_DW.LastUAtTimeB;
      }
    } else {
      if (problem_10_4_wf_model_DW.TimeStampA >=
          problem_10_4_wf_model_M->Timing.t[0]) {
        rtb_Backgain = problem_10_4_wf_model_DW.TimeStampB;
        lastU = &problem_10_4_wf_model_DW.LastUAtTimeB;
      }
    }

    rtb_Backgain = (problem_10_4_wf_model_B.PitchCounttorad - *lastU) /
      (problem_10_4_wf_model_M->Timing.t[0] - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  problem_10_4_wf_model_B.Gain_l = problem_10_4_wf_model_P.Gain_Gain_a1 *
    rtb_Backgain;
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (problem_10_4_wf_model_B.Sum2 - problem_10_4_wf_model_B.Sum1) *
    problem_10_4_wf_model_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > problem_10_4_wf_model_P.BackmotorSaturation_UpperSat) {
    problem_10_4_wf_model_B.BackmotorSaturation =
      problem_10_4_wf_model_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < problem_10_4_wf_model_P.BackmotorSaturation_LowerSat)
  {
    problem_10_4_wf_model_B.BackmotorSaturation =
      problem_10_4_wf_model_P.BackmotorSaturation_LowerSat;
  } else {
    problem_10_4_wf_model_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Backgain = (problem_10_4_wf_model_B.Sum1 + problem_10_4_wf_model_B.Sum2) *
    problem_10_4_wf_model_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Backgain > problem_10_4_wf_model_P.FrontmotorSaturation_UpperSat) {
    problem_10_4_wf_model_B.FrontmotorSaturation =
      problem_10_4_wf_model_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Backgain <
             problem_10_4_wf_model_P.FrontmotorSaturation_LowerSat) {
    problem_10_4_wf_model_B.FrontmotorSaturation =
      problem_10_4_wf_model_P.FrontmotorSaturation_LowerSat;
  } else {
    problem_10_4_wf_model_B.FrontmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: problem_10_4_wf_model/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      problem_10_4_wf_model_DW.HILWriteAnalog_Buffer[0] =
        problem_10_4_wf_model_B.FrontmotorSaturation;
      problem_10_4_wf_model_DW.HILWriteAnalog_Buffer[1] =
        problem_10_4_wf_model_B.BackmotorSaturation;
      result = hil_write_analog(problem_10_4_wf_model_DW.HILInitialize_Card,
        problem_10_4_wf_model_P.HILWriteAnalog_channels, 2,
        &problem_10_4_wf_model_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void problem_10_4_wf_model_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (problem_10_4_wf_model_DW.TimeStampA == (rtInf)) {
    problem_10_4_wf_model_DW.TimeStampA = problem_10_4_wf_model_M->Timing.t[0];
    lastU = &problem_10_4_wf_model_DW.LastUAtTimeA;
  } else if (problem_10_4_wf_model_DW.TimeStampB == (rtInf)) {
    problem_10_4_wf_model_DW.TimeStampB = problem_10_4_wf_model_M->Timing.t[0];
    lastU = &problem_10_4_wf_model_DW.LastUAtTimeB;
  } else if (problem_10_4_wf_model_DW.TimeStampA <
             problem_10_4_wf_model_DW.TimeStampB) {
    problem_10_4_wf_model_DW.TimeStampA = problem_10_4_wf_model_M->Timing.t[0];
    lastU = &problem_10_4_wf_model_DW.LastUAtTimeA;
  } else {
    problem_10_4_wf_model_DW.TimeStampB = problem_10_4_wf_model_M->Timing.t[0];
    lastU = &problem_10_4_wf_model_DW.LastUAtTimeB;
  }

  *lastU = problem_10_4_wf_model_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(problem_10_4_wf_model_M)) {
    rt_ertODEUpdateContinuousStates(&problem_10_4_wf_model_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++problem_10_4_wf_model_M->Timing.clockTick0)) {
    ++problem_10_4_wf_model_M->Timing.clockTickH0;
  }

  problem_10_4_wf_model_M->Timing.t[0] = rtsiGetSolverStopTime
    (&problem_10_4_wf_model_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++problem_10_4_wf_model_M->Timing.clockTick1)) {
      ++problem_10_4_wf_model_M->Timing.clockTickH1;
    }

    problem_10_4_wf_model_M->Timing.t[1] =
      problem_10_4_wf_model_M->Timing.clockTick1 *
      problem_10_4_wf_model_M->Timing.stepSize1 +
      problem_10_4_wf_model_M->Timing.clockTickH1 *
      problem_10_4_wf_model_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void problem_10_4_wf_model_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_problem_10_4_wf_model_T *_rtXdot;
  _rtXdot = ((XDot_problem_10_4_wf_model_T *)
             problem_10_4_wf_model_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE +=
    problem_10_4_wf_model_P.TravelTransferFcn_A *
    problem_10_4_wf_model_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += problem_10_4_wf_model_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += problem_10_4_wf_model_P.PitchTransferFcn_A
    * problem_10_4_wf_model_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += problem_10_4_wf_model_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    problem_10_4_wf_model_P.ElevationTransferFcn_A *
    problem_10_4_wf_model_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    problem_10_4_wf_model_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (problem_10_4_wf_model_X.Integrator_CSTATE <=
          problem_10_4_wf_model_P.Integrator_LowerSat);
  usat = (problem_10_4_wf_model_X.Integrator_CSTATE >=
          problem_10_4_wf_model_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (problem_10_4_wf_model_B.K_ei > 0.0)) ||
      (usat && (problem_10_4_wf_model_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = problem_10_4_wf_model_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void problem_10_4_wf_model_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: problem_10_4_wf_model/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &problem_10_4_wf_model_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (problem_10_4_wf_model_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(problem_10_4_wf_model_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
      return;
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_analog_input_ &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_analog_inpu_m && is_switching))
    {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &problem_10_4_wf_model_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] =
            problem_10_4_wf_model_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &problem_10_4_wf_model_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] =
            problem_10_4_wf_model_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_analog_input_chan, 8U,
         &problem_10_4_wf_model_DW.HILInitialize_AIMinimums[0],
         &problem_10_4_wf_model_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_analog_output &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_analog_outp_b && is_switching))
    {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &problem_10_4_wf_model_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] =
            problem_10_4_wf_model_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &problem_10_4_wf_model_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] =
            problem_10_4_wf_model_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_analog_output_cha, 8U,
         &problem_10_4_wf_model_DW.HILInitialize_AOMinimums[0],
         &problem_10_4_wf_model_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_analog_outp_e &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_analog_outp_j && is_switching))
    {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            problem_10_4_wf_model_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(problem_10_4_wf_model_DW.HILInitialize_Card,
        problem_10_4_wf_model_P.HILInitialize_analog_output_cha, 8U,
        &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if (problem_10_4_wf_model_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            problem_10_4_wf_model_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_analog_output_cha, 8U,
         &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_encoder_param &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_encoder_par_m && is_switching))
    {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &problem_10_4_wf_model_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            problem_10_4_wf_model_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &problem_10_4_wf_model_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_encoder_count &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_encoder_cou_k && is_switching))
    {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &problem_10_4_wf_model_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            problem_10_4_wf_model_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_encoder_channels, 8U,
         &problem_10_4_wf_model_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_pwm_params_at &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_pwm_params__f && is_switching))
    {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &problem_10_4_wf_model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = problem_10_4_wf_model_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(problem_10_4_wf_model_DW.HILInitialize_Card,
        problem_10_4_wf_model_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &problem_10_4_wf_model_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          problem_10_4_wf_model_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &problem_10_4_wf_model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            problem_10_4_wf_model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = problem_10_4_wf_model_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            problem_10_4_wf_model_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              problem_10_4_wf_model_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (problem_10_4_wf_model_DW.HILInitialize_Card,
           &problem_10_4_wf_model_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (problem_10_4_wf_model_DW.HILInitialize_Card,
           &problem_10_4_wf_model_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &problem_10_4_wf_model_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &problem_10_4_wf_model_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &problem_10_4_wf_model_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            problem_10_4_wf_model_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_pwm_channels, 8U,
         (t_pwm_configuration *)
         &problem_10_4_wf_model_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &problem_10_4_wf_model_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &problem_10_4_wf_model_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            problem_10_4_wf_model_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &problem_10_4_wf_model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(problem_10_4_wf_model_DW.HILInitialize_Card,
        problem_10_4_wf_model_P.HILInitialize_pwm_channels, 8U,
        &problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[0],
        &problem_10_4_wf_model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_pwm_outputs_a &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_pwm_outputs_g && is_switching))
    {
      {
        int_T i1;
        real_T *dw_POValues = &problem_10_4_wf_model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(problem_10_4_wf_model_DW.HILInitialize_Card,
        problem_10_4_wf_model_P.HILInitialize_pwm_channels, 8U,
        &problem_10_4_wf_model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }

    if (problem_10_4_wf_model_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &problem_10_4_wf_model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (problem_10_4_wf_model_DW.HILInitialize_Card,
         problem_10_4_wf_model_P.HILInitialize_pwm_channels, 8U,
         &problem_10_4_wf_model_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: problem_10_4_wf_model/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (problem_10_4_wf_model_DW.HILInitialize_Card,
       problem_10_4_wf_model_P.HILReadEncoderTimebase_samples_,
       problem_10_4_wf_model_P.HILReadEncoderTimebase_channels, 3,
       &problem_10_4_wf_model_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "data_wf.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(problem_10_4_wf_model_M,
                        "Error creating .mat file data_wf.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,7,0,"simout")) {
      rtmSetErrorStatus(problem_10_4_wf_model_M,
                        "Error writing mat file header to file data_wf.mat");
      return;
    }

    problem_10_4_wf_model_DW.ToFile1_IWORK.Count = 0;
    problem_10_4_wf_model_DW.ToFile1_IWORK.Decimation = -1;
    problem_10_4_wf_model_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/u' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.37979965806618082, 0.11199384493677116,
      -0.10785134520672887, -0.27499732799601012, -0.39624917370456952,
      -0.47821425843532384, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.50284820572160727,
      -0.46448769286732139, -0.42037559322787993, -0.3731495732016194,
      -0.32495703518509333, -0.27749613167187187, -0.23206779708464534,
      -0.18961802731029684, -0.15079559563477876, -0.1159918626093072,
      -0.085387159360934953, -0.058998775827595294, -0.036705632686821033,
      -0.018292067755714583, -0.0034731202392909726, 0.0080843158149269331,
      0.016738116006605224, 0.022853581015960314, 0.026794010112695152,
      0.028907308732799807, 0.029523056114201376, 0.028942832702598707,
      0.027440588711354772, 0.025262368311190914, 0.022622298603643037,
      0.019708784601625114, 0.016683130548149221, 0.013682498697965697,
      0.010819629030640132, 0.00819163983052233, 0.0058734794943262241,
      0.003921408392737945, 0.0023724569927325938, 0.0012400399384490245,
      0.000509228409962232, 0.00012652129605415015, 4.2911109275629327E-7,
      1.0438325458057865E-7, 1.0791776989165002E-7, 1.0791776989165002E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10547470848854171,
      0.12242713416396218, 0.14126075028469326, 0.16186028646241429,
      0.18393257776120178, 0.20692511498450983, 0.22991619815827932,
      0.25147109443133014, 0.26943208009158132, 0.28065728041796562,
      0.28065814682759277, 0.26311622455699973, 0.21926393511699846,
      0.13703848965196613, -7.4985470818018756E-7, -2.0504109506650937E-6,
      -8.6034683602992812E-7, 4.1271977934356858E-7, -5.9634282788804389E-9,
      7.5368707806742108E-7, 1.302698758811332E-6, 1.317730722616252E-6,
      1.0761682331792667E-6, 8.8473388929536323E-7, 3.8068113763374241E-7,
      4.0627365852979706E-7, 5.3773277938773839E-7, -4.1313997351914984E-7,
      -5.69639238244253E-7, -1.1583475125083358E-6, -5.0951135125526729E-7,
      -9.9724764640611E-7, -3.8060502045116554E-8, -2.1987848227735859E-7,
      5.3458558891763871E-7, 4.7689903197024587E-7, 7.5404585677721256E-7,
      -2.0394443449270795E-7, 4.156092309891418E-7, 1.4096081110341109E-7,
      -5.0254592252329334E-7, -4.5630347538397706E-7, 7.7029896460965515E-7,
      1.1511422208939733E-6, -8.7140184658505916E-9, -3.3495105250624859E-7,
      -4.8495588728826985E-7, -7.5305004719279454E-8, 8.5391935426515E-7,
      -3.8170491191863239E-7, -5.8608088942847388E-8, -1.0813320828378475E-7,
      1.3746350647023855E-7, 4.6360745019109468E-7, -2.2366751362615573E-7,
      -2.9124927146134048E-7, 5.2984493387841662E-7, 2.6465806220188077E-7,
      9.3352391128804082E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    problem_10_4_wf_model_DW.u_PWORK.TimePtr = (void *) pTimeValues0;
    problem_10_4_wf_model_DW.u_PWORK.DataPtr = (void *) pDataValues0;
    problem_10_4_wf_model_DW.u_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<S5>/x_star' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625261, 3.1262155534579983,
      3.1033093000299643, 3.0666274151911783, 3.0144539223941584,
      2.9456562771175667, 2.8595077632935446, 2.7555515879651526,
      2.633505110490284, 2.4931956060320961, 2.334518576064299,
      2.1584413474637465, 1.9679778704414657, 1.7677256141126179,
      1.5630273330030038, 1.3592378436793267, 1.1612183729836878,
      0.973021525490912, 0.79763464511357118, 0.63711789727160972,
      0.49283379239341374, 0.36550925660121192, 0.25525697476165582,
      0.16166503228016374, 0.083907958276329617, 0.02085713817162797,
      -0.028819159242043063, -0.066569833305583956, -0.093889890212552368,
      -0.1122636278902065, -0.12312083210955274, -0.12780448707690623,
      -0.12754838391434431, -0.1234631248194788, -0.11652904585345655,
      -0.10759470690956108, -0.0973797575568265, -0.086481109697795822,
      -0.075381477205132524, -0.0644595045876872, -0.05400081731258978,
      -0.044209473997905473, -0.035219381307994679, -0.027105348342008662,
      -0.019893555857658618, -0.013571262246718011, -0.0080956627037081872,
      -0.0034018536682068378, 0.00059010370066847314, 0.0039690153952088138,
      0.00682721066470359, 0.00925599273895501, 0.011341848161940317,
      0.013163387967567018, 0.014789033561135877, 0.016275503417685716,
      0.017667231696853317, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, -0.015002048909068423, -0.046506351618112111,
      -0.091625013712135384, -0.14672753935514371, -0.20869397118807925,
      -0.27519058110636674, -0.34459405529608839, -0.41582470131356869,
      -0.48818590989947463, -0.56123801783275185, -0.63470811987118858,
      -0.70430891440220922, -0.76185390808912334, -0.80100902531539142,
      -0.818793124438457, -0.81515795729470808, -0.79207788278255553,
      -0.75278738997110328, -0.70154752150936361, -0.64206699136784584,
      -0.577136419512784, -0.50929814316880728, -0.44100912735822462,
      -0.37436776992596832, -0.31102829601533644, -0.25220328041880657,
      -0.19870518965468414, -0.15100269625416354, -0.10928022762787369,
      -0.073494950710616472, -0.043428816877384972, -0.018734619869413868,
      0.0010244126502476885, 0.016341036379462031, 0.027736315864088947,
      0.035737355775581951, 0.040859797410938349, 0.043594591436122675,
      0.044398529970653237, 0.043687890469781269, 0.041834749100389708,
      0.039165373258737222, 0.035960370759643173, 0.032456131863944061,
      0.028847169937400188, 0.025289174443762424, 0.021902398172039296,
      0.0187752361420054, 0.015967829475501245, 0.013515646778161361,
      0.011432781077979107, 0.0097151282970056787, 0.0083434216919412319,
      0.0072861592225068033, 0.0065025823742754342, 0.0059458794261993582,
      0.0055669131166704152, 0.0053184405231751454, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10602875205865551, 0.22266037932317656,
      0.31888147181640641, 0.38944360631144165, 0.43795507377677839,
      0.46997264230390062, 0.4905172487754707, 0.5034310014147434,
      0.5114213858602934, 0.51630439857701838, 0.51925862127063693,
      0.49191183358655421, 0.40670603761053808, 0.27673341430729664,
      0.12569122044164649, -0.025691973017321439, -0.16312115183580472,
      -0.277690197240301, -0.36214382059265565, -0.42038567004538568,
      -0.45890448337930145, -0.47945502818712787, -0.48264068258923459,
      -0.47099566245019758, -0.4476592107853018, -0.41575274359762859,
      -0.37810407335839175, -0.33714300466558894, -0.29487847347156948,
      -0.25291667002342844, -0.21249595097900623, -0.1745291531654091,
      -0.13964929541588866, -0.10825204674402254, -0.080537483275650662,
      -0.056548294311605338, -0.03620346109935884, -0.019328479688696554,
      -0.0056819305192781959, 0.0050225285824454617, 0.013097295441163623,
      0.01886612895221601, 0.022651733598761856, 0.024766622164642038,
      0.025506764550496941, 0.025146553267980137, 0.023936441200081905,
      0.022101586892526327, 0.019841678105092235, 0.017331090759316874,
      0.014720899274138931, 0.012139713844460531, 0.00969469839800899,
      0.007472327340888929, 0.0055380218971160288, 0.0039345638192260831,
      0.0026783891397220579, 0.0017561093933746567, 0.0011215287555552524, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462206,
      0.46652650905808424, 0.38488436997291947, 0.282248537980141,
      0.19404586986134689, 0.12807027410848892, 0.0821784258862804,
      0.051655010557090618, 0.031961537782199831, 0.01953205086689987,
      0.011816890774474422, -0.10938715073633096, -0.34082318390406435,
      -0.51989049321296577, -0.60416877546260073, -0.60553277383587167,
      -0.54971671527393318, -0.458276181617985, -0.33781449340941877,
      -0.2329673978109201, -0.15407525333566296, -0.082202179231305822,
      -0.012742617608426805, 0.046580080556148123, 0.093345806659583155,
      0.12762586875069279, 0.15059468095694747, 0.16384427477121119,
      0.169058124776078, 0.16784721379256407, 0.16168287617768887,
      0.15186719125438861, 0.1395194309980817, 0.12558899468746448,
      0.11085825387348747, 0.095956755856181325, 0.081379332848985991,
      0.067499925642649145, 0.054586196677673435, 0.042817836406894627,
      0.032299067434872646, 0.023075334044209552, 0.01514241858618337,
      0.0084595542635207324, 0.0029605695434196081, -0.0014408451300672311,
      -0.0048404482715929077, -0.0073394172302223308, -0.0090396351497363647,
      -0.010042349383101452, -0.010440765940711768, -0.010324741718713603,
      -0.00978006178580616, -0.0088894842284802465, -0.0077372217750915975,
      -0.0064138323115597844, -0.0050246987180161, -0.0036891189853896045,
      -0.0025383225512776168, -0.0016761934503676213, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00421898833954167,
      0.011647466709825161, 0.021586224209801316, 0.033557991499890583,
      0.04723490601600016, 0.062375739665050674, 0.078767491540172152,
      0.096166356855896223, 0.11423225958738703, 0.13245143816876428,
      0.15003998080719891, 0.16581969784578909, 0.17805648624133519,
      0.1842473109509099, 0.180839516332813, 0.17142486510748045,
      0.15854245930509495, 0.14395603772815563, 0.12886248617125107,
      0.11404814387546523, 0.10000509115909405, 0.087017386483481632,
      0.075224603078479751, 0.064668272965494933, 0.055325506001810354,
      0.047133131155926149, 0.040004707517634387, 0.033842311562823343,
      0.02854466290366181, 0.024012334911751459, 0.020151131220004722,
      0.016873875718580768, 0.014101475646506127, 0.011763071779378818,
      0.0097959918166657441, 0.0081452400438240275, 0.006762979469286637,
      0.0056078053650338621, 0.0046441983480799724, 0.0038417275617387268,
      0.0031744570541738805, 0.0026204073950264082, 0.002161030129329554,
      0.0017806335197992206, 0.0014659540003471, 0.0012059075498417585,
      0.00099122212128917786, 0.00081417154996377063, 0.00066832647909112974,
      0.00054823730637251766, 0.00044944839925414745, 0.00036824123739989331,
      0.0003015445028574337, 0.00024681535693396985, 0.00020190714256504918,
      0.00016507794969547953, 0.0001349253420684909, 0.00011024124582696662,
      9.0037508494957558E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.016875953358166679, 0.029713913481133961, 0.039755029999904636,
      0.047887069160357044, 0.0547076580644383, 0.06056333459620207,
      0.0655670075004859, 0.069595461262896258, 0.072263610925963229,
      0.072876714325509045, 0.070354170553738354, 0.063118868154360686,
      0.04894715358218435, 0.024763298838298933, -0.013631178472387585,
      -0.037658604901330252, -0.051529623209542005, -0.058345686307757383,
      -0.060374206227618153, -0.059257369183143296, -0.05617221086548474,
      -0.051950818702449664, -0.047171133620007542, -0.0422253204519393,
      -0.037371067854738323, -0.032769499383536821, -0.028513694553167046,
      -0.024649583819244175, -0.021190594636646125, -0.018129311967641414,
      -0.015444814766986937, -0.013109022005695822, -0.011089600288298576,
      -0.0093536154685092323, -0.0078683198508522935, -0.0066030070913668708,
      -0.0055290422981495585, -0.0046206964170110981, -0.0038544280678155626,
      -0.0032098831453649793, -0.0026690820302593867, -0.00221619863658989,
      -0.0018375090627874174, -0.0015215864381213327, -0.0012587180778084828,
      -0.0010401858020213659, -0.00085874171421032174, -0.00070820228530162944,
      -0.00058338028349056369, -0.00048035669087444845, -0.00039515562847348068,
      -0.00032482864741701663, -0.00026678693816983834, -0.00021891658369385536,
      -0.00017963285747568279, -0.00014731677147827865, -0.00012061043050795453,
      -9.8736384966097152E-5, -8.0814949328036214E-5, -6.61275689291364E-5, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

    problem_10_4_wf_model_DW.x_star_PWORK.TimePtr = (void *) pTimeValues0;
    problem_10_4_wf_model_DW.x_star_PWORK.DataPtr = (void *) pDataValues0;
    problem_10_4_wf_model_DW.x_star_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  problem_10_4_wf_model_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  problem_10_4_wf_model_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  problem_10_4_wf_model_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  problem_10_4_wf_model_X.Integrator_CSTATE =
    problem_10_4_wf_model_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  problem_10_4_wf_model_DW.TimeStampA = (rtInf);
  problem_10_4_wf_model_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void problem_10_4_wf_model_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: problem_10_4_wf_model/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(problem_10_4_wf_model_DW.HILInitialize_Card);
    hil_monitor_stop_all(problem_10_4_wf_model_DW.HILInitialize_Card);
    is_switching = false;
    if ((problem_10_4_wf_model_P.HILInitialize_set_analog_out_ex &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_analog_outp_c && is_switching))
    {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] =
            problem_10_4_wf_model_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((problem_10_4_wf_model_P.HILInitialize_set_pwm_output_ap &&
         !is_switching) ||
        (problem_10_4_wf_model_P.HILInitialize_set_pwm_outputs_p && is_switching))
    {
      {
        int_T i1;
        real_T *dw_POValues = &problem_10_4_wf_model_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] =
            problem_10_4_wf_model_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(problem_10_4_wf_model_DW.HILInitialize_Card
                         ,
                         problem_10_4_wf_model_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , problem_10_4_wf_model_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0]
                         , &problem_10_4_wf_model_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (problem_10_4_wf_model_DW.HILInitialize_Card,
             problem_10_4_wf_model_P.HILInitialize_analog_output_cha,
             num_final_analog_outputs,
             &problem_10_4_wf_model_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (problem_10_4_wf_model_DW.HILInitialize_Card,
             problem_10_4_wf_model_P.HILInitialize_pwm_channels,
             num_final_pwm_outputs,
             &problem_10_4_wf_model_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(problem_10_4_wf_model_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(problem_10_4_wf_model_DW.HILInitialize_Card);
    hil_monitor_delete_all(problem_10_4_wf_model_DW.HILInitialize_Card);
    hil_close(problem_10_4_wf_model_DW.HILInitialize_Card);
    problem_10_4_wf_model_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) problem_10_4_wf_model_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "data_wf.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(problem_10_4_wf_model_M,
                          "Error closing MAT-file data_wf.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(problem_10_4_wf_model_M,
                          "Error reopening MAT-file data_wf.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 7,
           problem_10_4_wf_model_DW.ToFile1_IWORK.Count, "simout")) {
        rtmSetErrorStatus(problem_10_4_wf_model_M,
                          "Error writing header for simout to MAT-file data_wf.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(problem_10_4_wf_model_M,
                          "Error closing MAT-file data_wf.mat");
        return;
      }

      problem_10_4_wf_model_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  problem_10_4_wf_model_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  problem_10_4_wf_model_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  problem_10_4_wf_model_initialize();
}

void MdlTerminate(void)
{
  problem_10_4_wf_model_terminate();
}

/* Registration function */
RT_MODEL_problem_10_4_wf_mode_T *problem_10_4_wf_model(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  problem_10_4_wf_model_P.Integrator_UpperSat = rtInf;
  problem_10_4_wf_model_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)problem_10_4_wf_model_M, 0,
                sizeof(RT_MODEL_problem_10_4_wf_mode_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&problem_10_4_wf_model_M->solverInfo,
                          &problem_10_4_wf_model_M->Timing.simTimeStep);
    rtsiSetTPtr(&problem_10_4_wf_model_M->solverInfo, &rtmGetTPtr
                (problem_10_4_wf_model_M));
    rtsiSetStepSizePtr(&problem_10_4_wf_model_M->solverInfo,
                       &problem_10_4_wf_model_M->Timing.stepSize0);
    rtsiSetdXPtr(&problem_10_4_wf_model_M->solverInfo,
                 &problem_10_4_wf_model_M->ModelData.derivs);
    rtsiSetContStatesPtr(&problem_10_4_wf_model_M->solverInfo, (real_T **)
                         &problem_10_4_wf_model_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&problem_10_4_wf_model_M->solverInfo,
      &problem_10_4_wf_model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&problem_10_4_wf_model_M->solverInfo,
      &problem_10_4_wf_model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&problem_10_4_wf_model_M->solverInfo,
      &problem_10_4_wf_model_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&problem_10_4_wf_model_M->solverInfo,
      &problem_10_4_wf_model_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&problem_10_4_wf_model_M->solverInfo,
                          (&rtmGetErrorStatus(problem_10_4_wf_model_M)));
    rtsiSetRTModelPtr(&problem_10_4_wf_model_M->solverInfo,
                      problem_10_4_wf_model_M);
  }

  rtsiSetSimTimeStep(&problem_10_4_wf_model_M->solverInfo, MAJOR_TIME_STEP);
  problem_10_4_wf_model_M->ModelData.intgData.f[0] =
    problem_10_4_wf_model_M->ModelData.odeF[0];
  problem_10_4_wf_model_M->ModelData.contStates = ((real_T *)
    &problem_10_4_wf_model_X);
  rtsiSetSolverData(&problem_10_4_wf_model_M->solverInfo, (void *)
                    &problem_10_4_wf_model_M->ModelData.intgData);
  rtsiSetSolverName(&problem_10_4_wf_model_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = problem_10_4_wf_model_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    problem_10_4_wf_model_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    problem_10_4_wf_model_M->Timing.sampleTimes =
      (&problem_10_4_wf_model_M->Timing.sampleTimesArray[0]);
    problem_10_4_wf_model_M->Timing.offsetTimes =
      (&problem_10_4_wf_model_M->Timing.offsetTimesArray[0]);

    /* task periods */
    problem_10_4_wf_model_M->Timing.sampleTimes[0] = (0.0);
    problem_10_4_wf_model_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    problem_10_4_wf_model_M->Timing.offsetTimes[0] = (0.0);
    problem_10_4_wf_model_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(problem_10_4_wf_model_M, &problem_10_4_wf_model_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = problem_10_4_wf_model_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    problem_10_4_wf_model_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(problem_10_4_wf_model_M, 25.0);
  problem_10_4_wf_model_M->Timing.stepSize0 = 0.002;
  problem_10_4_wf_model_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  problem_10_4_wf_model_M->Sizes.checksums[0] = (674601011U);
  problem_10_4_wf_model_M->Sizes.checksums[1] = (1903808788U);
  problem_10_4_wf_model_M->Sizes.checksums[2] = (28361194U);
  problem_10_4_wf_model_M->Sizes.checksums[3] = (1758882759U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    problem_10_4_wf_model_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(problem_10_4_wf_model_M->extModeInfo,
      &problem_10_4_wf_model_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(problem_10_4_wf_model_M->extModeInfo,
                        problem_10_4_wf_model_M->Sizes.checksums);
    rteiSetTPtr(problem_10_4_wf_model_M->extModeInfo, rtmGetTPtr
                (problem_10_4_wf_model_M));
  }

  problem_10_4_wf_model_M->solverInfoPtr = (&problem_10_4_wf_model_M->solverInfo);
  problem_10_4_wf_model_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&problem_10_4_wf_model_M->solverInfo, 0.002);
  rtsiSetSolverMode(&problem_10_4_wf_model_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  problem_10_4_wf_model_M->ModelData.blockIO = ((void *)
    &problem_10_4_wf_model_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      problem_10_4_wf_model_B.Gain1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      problem_10_4_wf_model_B.Sum3_j[i] = 0.0;
    }

    problem_10_4_wf_model_B.TravelCounttorad = 0.0;
    problem_10_4_wf_model_B.Gain = 0.0;
    problem_10_4_wf_model_B.Sum3 = 0.0;
    problem_10_4_wf_model_B.Gain_d = 0.0;
    problem_10_4_wf_model_B.PitchCounttorad = 0.0;
    problem_10_4_wf_model_B.Gain_i = 0.0;
    problem_10_4_wf_model_B.Gain_b = 0.0;
    problem_10_4_wf_model_B.ElevationCounttorad = 0.0;
    problem_10_4_wf_model_B.Gain_e = 0.0;
    problem_10_4_wf_model_B.Sum = 0.0;
    problem_10_4_wf_model_B.Gain_dg = 0.0;
    problem_10_4_wf_model_B.u[0] = 0.0;
    problem_10_4_wf_model_B.u[1] = 0.0;
    problem_10_4_wf_model_B.Gain_k[0] = 0.0;
    problem_10_4_wf_model_B.Gain_k[1] = 0.0;
    problem_10_4_wf_model_B.Sum1 = 0.0;
    problem_10_4_wf_model_B.Sum2 = 0.0;
    problem_10_4_wf_model_B.K_ei = 0.0;
    problem_10_4_wf_model_B.Gain_l = 0.0;
    problem_10_4_wf_model_B.BackmotorSaturation = 0.0;
    problem_10_4_wf_model_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  problem_10_4_wf_model_M->ModelData.defaultParam = ((real_T *)
    &problem_10_4_wf_model_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &problem_10_4_wf_model_X;
    problem_10_4_wf_model_M->ModelData.contStates = (x);
    (void) memset((void *)&problem_10_4_wf_model_X, 0,
                  sizeof(X_problem_10_4_wf_model_T));
  }

  /* states (dwork) */
  problem_10_4_wf_model_M->ModelData.dwork = ((void *) &problem_10_4_wf_model_DW);
  (void) memset((void *)&problem_10_4_wf_model_DW, 0,
                sizeof(DW_problem_10_4_wf_model_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      problem_10_4_wf_model_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  problem_10_4_wf_model_DW.TimeStampA = 0.0;
  problem_10_4_wf_model_DW.LastUAtTimeA = 0.0;
  problem_10_4_wf_model_DW.TimeStampB = 0.0;
  problem_10_4_wf_model_DW.LastUAtTimeB = 0.0;
  problem_10_4_wf_model_DW.HILWriteAnalog_Buffer[0] = 0.0;
  problem_10_4_wf_model_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    problem_10_4_wf_model_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  problem_10_4_wf_model_M->Sizes.numContStates = (4);/* Number of continuous states */
  problem_10_4_wf_model_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  problem_10_4_wf_model_M->Sizes.numY = (0);/* Number of model outputs */
  problem_10_4_wf_model_M->Sizes.numU = (0);/* Number of model inputs */
  problem_10_4_wf_model_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  problem_10_4_wf_model_M->Sizes.numSampTimes = (2);/* Number of sample times */
  problem_10_4_wf_model_M->Sizes.numBlocks = (64);/* Number of blocks */
  problem_10_4_wf_model_M->Sizes.numBlockIO = (21);/* Number of block outputs */
  problem_10_4_wf_model_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return problem_10_4_wf_model_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
