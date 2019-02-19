/*
 * helicopter_10_4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_10_4".
 *
 * Model version              : 1.220
 * Simulink Coder version : 8.9 (R2015b) 13-Aug-2015
 * C source code generated on : Tue Feb 19 11:28:46 2019
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_10_4.h"
#include "helicopter_10_4_private.h"
#include "helicopter_10_4_dt.h"

/* Block signals (auto storage) */
B_helicopter_10_4_T helicopter_10_4_B;

/* Continuous states */
X_helicopter_10_4_T helicopter_10_4_X;

/* Block states (auto storage) */
DW_helicopter_10_4_T helicopter_10_4_DW;

/* Real-time model */
RT_MODEL_helicopter_10_4_T helicopter_10_4_M_;
RT_MODEL_helicopter_10_4_T *const helicopter_10_4_M = &helicopter_10_4_M_;

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
  helicopter_10_4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_10_4_output(void)
{
  /* local block i/o variables */
  real_T rtb_x_star[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T *lastU;
  real_T rtb_Backgain;
  real_T rtb_Gain1[6];
  real_T rtb_Sum4[2];
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* set solver stop time */
    if (!(helicopter_10_4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_10_4_M->solverInfo,
                            ((helicopter_10_4_M->Timing.clockTickH0 + 1) *
        helicopter_10_4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_10_4_M->solverInfo,
                            ((helicopter_10_4_M->Timing.clockTick0 + 1) *
        helicopter_10_4_M->Timing.stepSize0 +
        helicopter_10_4_M->Timing.clockTickH0 *
        helicopter_10_4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_10_4_M)) {
    helicopter_10_4_M->Timing.t[0] = rtsiGetT(&helicopter_10_4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_10_4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_10_4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Elevation: Count to rad' */
    helicopter_10_4_B.ElevationCounttorad =
      helicopter_10_4_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S7>/Gain' */
    helicopter_10_4_B.Gain = helicopter_10_4_P.Gain_Gain *
      helicopter_10_4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_10_4_B.Sum = helicopter_10_4_B.Gain +
      helicopter_10_4_P.elavation_offsetdeg_Value;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_10_4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_10_4_DW.ToFile_IWORK.Count*2)+1 < 100000000 ) {
        FILE *fp = (FILE *) helicopter_10_4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[2];
          helicopter_10_4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_10_4_M->Timing.t[1];
          u[1] = helicopter_10_4_B.Sum;
          if (fwrite(u, sizeof(real_T), 2, fp) != 2) {
            rtmSetErrorStatus(helicopter_10_4_M,
                              "Error writing to MAT-file elev.mat");
            return;
          }

          if (((++helicopter_10_4_DW.ToFile_IWORK.Count)*2)+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elev.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/u' */
  {
    real_T *pDataValues = (real_T *) helicopter_10_4_DW.u_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter_10_4_DW.u_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_4_DW.u_IWORK.PrevIndex;
    real_T t = helicopter_10_4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
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

    helicopter_10_4_DW.u_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&helicopter_10_4_B.u[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&helicopter_10_4_B.u[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
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
            (&helicopter_10_4_B.u[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<S5>/x_star' */
  {
    real_T *pDataValues = (real_T *) helicopter_10_4_DW.x_star_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter_10_4_DW.x_star_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_10_4_DW.x_star_IWORK.PrevIndex;
    real_T t = helicopter_10_4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
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

    helicopter_10_4_DW.x_star_IWORK.PrevIndex = currTimeIndex;

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
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_x_star[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
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
            pDataValues += 81;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopter_10_4_B.TravelCounttorad = helicopter_10_4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopter_10_4_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopter_10_4_B.Gain_p = helicopter_10_4_P.Gain_Gain_a *
      helicopter_10_4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/Travel_offset'
     */
    helicopter_10_4_B.Sum3 = helicopter_10_4_P.Travel_offset_Value +
      helicopter_10_4_B.Gain_p;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopter_10_4_B.PitchCounttorad = helicopter_10_4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopter_10_4_B.Gain_i = helicopter_10_4_P.Gain_Gain_ar *
      helicopter_10_4_B.PitchCounttorad;
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_d = (helicopter_10_4_P.TravelTransferFcn_C *
    helicopter_10_4_X.TravelTransferFcn_CSTATE +
    helicopter_10_4_P.TravelTransferFcn_D * helicopter_10_4_B.TravelCounttorad) *
    helicopter_10_4_P.Gain_Gain_l;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_b = (helicopter_10_4_P.PitchTransferFcn_C *
    helicopter_10_4_X.PitchTransferFcn_CSTATE +
    helicopter_10_4_P.PitchTransferFcn_D * helicopter_10_4_B.PitchCounttorad) *
    helicopter_10_4_P.Gain_Gain_ae;

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopter_10_4_B.Gain_dg = (helicopter_10_4_P.ElevationTransferFcn_C *
    helicopter_10_4_X.ElevationTransferFcn_CSTATE +
    helicopter_10_4_P.ElevationTransferFcn_D *
    helicopter_10_4_B.ElevationCounttorad) * helicopter_10_4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Sum3;
  rtb_Gain1[1] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_d;
  rtb_Gain1[2] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_i;
  rtb_Gain1[3] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_b;
  rtb_Gain1[4] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Sum;
  rtb_Gain1[5] = helicopter_10_4_P.Gain1_Gain * helicopter_10_4_B.Gain_dg;

  /* Sum: '<S5>/Sum3' */
  for (i = 0; i < 6; i++) {
    helicopter_10_4_B.Sum3_j[i] = rtb_Gain1[i] - rtb_x_star[i];
  }

  /* End of Sum: '<S5>/Sum3' */
  for (i = 0; i < 2; i++) {
    /* Gain: '<S5>/Gain' */
    helicopter_10_4_B.Gain_k[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      helicopter_10_4_B.Gain_k[i] += helicopter_10_4_P.K_lq[(i_0 << 1) + i] *
        helicopter_10_4_B.Sum3_j[i_0];
    }

    /* End of Gain: '<S5>/Gain' */

    /* Sum: '<S5>/Sum4' */
    rtb_Sum4[i] = helicopter_10_4_B.u[i] - helicopter_10_4_B.Gain_k[i];
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  helicopter_10_4_B.Sum1 = ((rtb_Sum4[0] - rtb_Gain1[2]) *
    helicopter_10_4_P.K_pp - helicopter_10_4_P.K_pd * rtb_Gain1[3]) +
    helicopter_10_4_P.Vd_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_10_4_X.Integrator_CSTATE >=
      helicopter_10_4_P.Integrator_UpperSat) {
    helicopter_10_4_X.Integrator_CSTATE = helicopter_10_4_P.Integrator_UpperSat;
  } else {
    if (helicopter_10_4_X.Integrator_CSTATE <=
        helicopter_10_4_P.Integrator_LowerSat) {
      helicopter_10_4_X.Integrator_CSTATE =
        helicopter_10_4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Backgain = rtb_Sum4[1] - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  helicopter_10_4_B.Sum2 = ((helicopter_10_4_P.K_ep * rtb_Backgain +
    helicopter_10_4_X.Integrator_CSTATE) - helicopter_10_4_P.K_ed * rtb_Gain1[5])
    + helicopter_10_4_P.Vs_ff;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S3>/K_ei' */
  helicopter_10_4_B.K_ei = helicopter_10_4_P.K_ei * rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  if ((helicopter_10_4_DW.TimeStampA >= helicopter_10_4_M->Timing.t[0]) &&
      (helicopter_10_4_DW.TimeStampB >= helicopter_10_4_M->Timing.t[0])) {
    rtb_Backgain = 0.0;
  } else {
    rtb_Backgain = helicopter_10_4_DW.TimeStampA;
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
    if (helicopter_10_4_DW.TimeStampA < helicopter_10_4_DW.TimeStampB) {
      if (helicopter_10_4_DW.TimeStampB < helicopter_10_4_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_DW.TimeStampB;
        lastU = &helicopter_10_4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_10_4_DW.TimeStampA >= helicopter_10_4_M->Timing.t[0]) {
        rtb_Backgain = helicopter_10_4_DW.TimeStampB;
        lastU = &helicopter_10_4_DW.LastUAtTimeB;
      }
    }

    rtb_Backgain = (helicopter_10_4_B.PitchCounttorad - *lastU) /
      (helicopter_10_4_M->Timing.t[0] - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopter_10_4_B.Gain_l = helicopter_10_4_P.Gain_Gain_a1 * rtb_Backgain;
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Backgain = (helicopter_10_4_B.Sum2 - helicopter_10_4_B.Sum1) *
    helicopter_10_4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_P.BackmotorSaturation_UpperSat) {
    helicopter_10_4_B.BackmotorSaturation =
      helicopter_10_4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_4_P.BackmotorSaturation_LowerSat) {
    helicopter_10_4_B.BackmotorSaturation =
      helicopter_10_4_P.BackmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_B.BackmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Backgain = (helicopter_10_4_B.Sum1 + helicopter_10_4_B.Sum2) *
    helicopter_10_4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Backgain > helicopter_10_4_P.FrontmotorSaturation_UpperSat) {
    helicopter_10_4_B.FrontmotorSaturation =
      helicopter_10_4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Backgain < helicopter_10_4_P.FrontmotorSaturation_LowerSat) {
    helicopter_10_4_B.FrontmotorSaturation =
      helicopter_10_4_P.FrontmotorSaturation_LowerSat;
  } else {
    helicopter_10_4_B.FrontmotorSaturation = rtb_Backgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_10_4_DW.HILWriteAnalog_Buffer[0] =
        helicopter_10_4_B.FrontmotorSaturation;
      helicopter_10_4_DW.HILWriteAnalog_Buffer[1] =
        helicopter_10_4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILWriteAnalog_channels, 2,
        &helicopter_10_4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_10_4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopter_10_4_DW.TimeStampA == (rtInf)) {
    helicopter_10_4_DW.TimeStampA = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
  } else if (helicopter_10_4_DW.TimeStampB == (rtInf)) {
    helicopter_10_4_DW.TimeStampB = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeB;
  } else if (helicopter_10_4_DW.TimeStampA < helicopter_10_4_DW.TimeStampB) {
    helicopter_10_4_DW.TimeStampA = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeA;
  } else {
    helicopter_10_4_DW.TimeStampB = helicopter_10_4_M->Timing.t[0];
    lastU = &helicopter_10_4_DW.LastUAtTimeB;
  }

  *lastU = helicopter_10_4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_10_4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_10_4_M->solverInfo);
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
  if (!(++helicopter_10_4_M->Timing.clockTick0)) {
    ++helicopter_10_4_M->Timing.clockTickH0;
  }

  helicopter_10_4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_10_4_M->solverInfo);

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
    if (!(++helicopter_10_4_M->Timing.clockTick1)) {
      ++helicopter_10_4_M->Timing.clockTickH1;
    }

    helicopter_10_4_M->Timing.t[1] = helicopter_10_4_M->Timing.clockTick1 *
      helicopter_10_4_M->Timing.stepSize1 +
      helicopter_10_4_M->Timing.clockTickH1 *
      helicopter_10_4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_10_4_derivatives(void)
{
  boolean_T lsat;
  boolean_T usat;
  XDot_helicopter_10_4_T *_rtXdot;
  _rtXdot = ((XDot_helicopter_10_4_T *) helicopter_10_4_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_4_P.TravelTransferFcn_A *
    helicopter_10_4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_10_4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_4_P.PitchTransferFcn_A *
    helicopter_10_4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_10_4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_10_4_P.ElevationTransferFcn_A *
    helicopter_10_4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopter_10_4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopter_10_4_X.Integrator_CSTATE <=
          helicopter_10_4_P.Integrator_LowerSat);
  usat = (helicopter_10_4_X.Integrator_CSTATE >=
          helicopter_10_4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_10_4_B.K_ei > 0.0)) || (usat &&
       (helicopter_10_4_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_10_4_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopter_10_4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_10_4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopter_10_4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_10_4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
      return;
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopter_10_4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = helicopter_10_4_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopter_10_4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_10_4_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_analog_input_chan, 8U,
        &helicopter_10_4_DW.HILInitialize_AIMinimums[0],
        &helicopter_10_4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_output && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopter_10_4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = helicopter_10_4_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopter_10_4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_10_4_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_DW.HILInitialize_AOMinimums[0],
         &helicopter_10_4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
        &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_analog_output_cha, 8U,
         &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_encoder_param && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_10_4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopter_10_4_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_encoder_channels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_10_4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_encoder_count && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_10_4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_10_4_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_encoder_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_10_4_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &helicopter_10_4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          helicopter_10_4_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            helicopter_10_4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_10_4_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_10_4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = p_HILInitialize_pwm_channels[i1];
            helicopter_10_4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_10_4_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopter_10_4_DW.HILInitialize_Card,
          &helicopter_10_4_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopter_10_4_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopter_10_4_DW.HILInitialize_Card,
          &helicopter_10_4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopter_10_4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_10_4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_10_4_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_10_4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopter_10_4_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_10_4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopter_10_4_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &helicopter_10_4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopter_10_4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopter_10_4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_10_4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] =
            helicopter_10_4_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(helicopter_10_4_DW.HILInitialize_Card,
        helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
        &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_10_4_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_10_4_DW.HILInitialize_Card,
         helicopter_10_4_P.HILInitialize_pwm_channels, 8U,
         &helicopter_10_4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_10_4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_10_4_DW.HILInitialize_Card,
       helicopter_10_4_P.HILReadEncoderTimebase_samples_,
       helicopter_10_4_P.HILReadEncoderTimebase_channels, 3,
       &helicopter_10_4_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elev.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_10_4_M, "Error creating .mat file elev.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,2,0,"elev")) {
      rtmSetErrorStatus(helicopter_10_4_M,
                        "Error writing mat file header to file elev.mat");
      return;
    }

    helicopter_10_4_DW.ToFile_IWORK.Count = 0;
    helicopter_10_4_DW.ToFile_IWORK.Decimation = -1;
    helicopter_10_4_DW.ToFile_PWORK.FilePtr = fp;
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
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.37449481020923286, 0.10868975074000826,
      -0.10914644699151028, -0.27426529329654142, -0.39346389967647272,
      -0.47334780749462679, -0.52020584646169932, -0.52359877559829882,
      -0.52359877559829882, -0.51885786281478286, -0.48725681144396488,
      -0.44678861768680417, -0.4006604247514538, -0.3515761678760817,
      -0.30176269825764718, -0.25302847296545627, -0.20679444367760996,
      -0.16415586804628943, -0.1259139920202762, -0.09262696534181683,
      -0.064626007161182844, -0.042047373499864767, -0.024823360714858366,
      -0.012680073853933202, -0.0050902186092740172, -0.0012406496975611062,
      6.9057484841649407E-7, -2.9311061589396187E-7, 9.1294381054510813E-7,
      9.1294381054510813E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.10546462059850126, 0.12241376901363421, 0.14124588694758963,
      0.16184466707735695, 0.18391582858012434, 0.20690575646519394,
      0.22989532697826809, 0.25144584896809075, 0.26940619091240725,
      0.28063064126380244, 0.28062960225015182, 0.26309118583076374,
      0.21924208326004632, 0.13702346410220156, 3.9312412688229991E-7,
      -2.26987115215888E-8, 8.3968141347153266E-7, 3.6340430676909992E-7,
      4.7415762463493067E-7, 1.5357778568051043E-6, 3.3888251333286959E-7,
      4.9907405358193177E-7, -7.78338729098931E-7, 3.5706042479385532E-8,
      1.91571320259599E-7, 6.4980888709253481E-7, 5.4052711480201256E-7,
      -6.72929419298734E-7, -2.5353754134919463E-7, -6.6783670141908313E-7,
      1.447474363247926E-7, -1.7602175687586227E-7, -2.2266491367487643E-7,
      5.8911853946232214E-7, -9.92441008016004E-7, 5.0252848452351628E-7,
      -8.0470946387493434E-7, -2.9239622623863091E-7, -7.6207317373553918E-9,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_10_4_DW.u_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_4_DW.u_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_4_DW.u_IWORK.PrevIndex = 0;
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
      19.75, 20.0 } ;

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
      2.1584793458275291, 1.9681193324331012, 1.7680403337678023,
      1.5635670369901435, 1.3600183678572626, 1.1622066313316761,
      0.97415202965463, 0.79884536642453863, 0.6383604144216809,
      0.49403964669120221, 0.36650611054302179, 0.25574918824423781,
      0.161238314504556, 0.082041491255672588, 0.016937205194640956,
      -0.035485359750319849, -0.076739765557456777, -0.10836957655719506,
      -0.13188878568804155, -0.1487342903041517, -0.16022926411479119,
      -0.16755626639078713, -0.17173922703779618, -0.17363372653799294,
      -0.17392553038440661, -0.17313774179592376, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048909068423,
      -0.046506351618112111, -0.091625013712135384, -0.14672753935514371,
      -0.20869397118807925, -0.27519058110636674, -0.34459405529608839,
      -0.41582470131356875, -0.48818590989947469, -0.56123801783275185,
      -0.63470811987118858, -0.704156920947079, -0.76144005357771216,
      -0.80031599466119485, -0.81789318711063552, -0.81419467653152444,
      -0.79124694610234536, -0.75221840670818452, -0.7012266529203659,
      -0.64193980801143058, -0.57728307092191489, -0.51013414459272177,
      -0.44302768919513585, -0.3780434949587273, -0.31678729299553365,
      -0.26041714424412649, -0.20969025977984324, -0.16501762322854771,
      -0.12651924399895312, -0.094076836523385957, -0.067382018464440613,
      -0.045979895242557842, -0.029308009103983842, -0.016731842588036144,
      -0.0075779980007870595, -0.0011672153856547198, 0.0031511543539313822,
      0.0059620795401841287, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205865551, 0.22266037932317656, 0.31888147181640641,
      0.38944360631144165, 0.43795507377677845, 0.46997264230390062,
      0.49051724877547076, 0.5034310014147434, 0.5114213858602934,
      0.51630439857701838, 0.51925862127063693, 0.49083760189552222,
      0.4048553036755585, 0.274760303953938, 0.12422888309492573,
      -0.026139660226133673, -0.162185794402624, -0.2758388105329751,
      -0.36039024083813431, -0.41901677679437832, -0.45696912384027405,
      -0.47458296556140489, -0.47428279723744032, -0.45928346589102881,
      -0.43293544031071252, -0.39840268230692111, -0.35851824561912754,
      -0.31572913362791266, -0.27209184097029143, -0.22929054552898295,
      -0.18866877867008602, -0.1512620329647168, -0.11783052384721007,
      -0.088883541804863075, -0.064695877476989808, -0.0453089630970957,
      -0.030520588033771976, -0.019866545658870919, -0.012620781699441709, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462206,
      0.46652650905808424, 0.38488436997291947, 0.282248537980141,
      0.19404586986134695, 0.12807027410848895, 0.082178425886280382,
      0.051655010557090555, 0.031961537782199831, 0.019532050866899811,
      0.011816890774474322, -0.11368407750045884, -0.34392919287985507,
      -0.5203799988864819, -0.60212568343604911, -0.60147417328423769,
      -0.54418453670596134, -0.45461206452140429, -0.338205721220637,
      -0.23450614382497592, -0.15180938818358292, -0.07045536688452339,
      0.0012006732958582602, 0.05999732538564622, 0.10539210232126507,
      0.13813103201516563, 0.15953774675117416, 0.17115644796485949,
      0.17454917063048481, 0.17120518176523397, 0.16248706743558783,
      0.14962698282147691, 0.1337260364700269, 0.11578792816938799,
      0.096750657311493071, 0.077547657519576443, 0.05915350025329489,
      0.042616169499604228, 0.028983055837716848, 0.018990947051943673, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0042185848239400508,
      0.01164628647884945, 0.021583999556741076, 0.033554562627416351,
      0.04723017363075685, 0.062369587986272255, 0.078759842733481952,
      0.096157046021080508, 0.11422122192079665, 0.13243867127033523,
      0.15002547609323258, 0.16580365956938814, 0.17803923394175403,
      0.18422937074648607, 0.18082189919662023, 0.17140824052889281,
      0.1585272029476481, 0.14394226531391782, 0.12885023358207873,
      0.11403738536153281, 0.099995680641222662, 0.087009182357537393,
      0.075217425028128171, 0.06466200476442284, 0.055320063267927322,
      0.04712844417180858, 0.040000691804504836, 0.033838875700073476,
      0.028541748223732809, 0.024009889996457416, 0.020149110921040318,
      0.016872240835061489, 0.014100145440036032, 0.011762022134359876,
      0.0097951026357124219, 0.008144490152288934, 0.006762286368427791,
      0.0056071727961704973, 0.00464361289324974, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.016874339295760203, 0.0297108066196376,
      0.039750852311566491, 0.0478822522827011, 0.054702444013361981,
      0.060557657422061609, 0.065561018988838773, 0.069588813150394224,
      0.072256703598864588, 0.072869797398154273, 0.070347219291589408,
      0.0631127339046222, 0.048942297489463528, 0.024760547218928262,
      -0.013629886199463391, -0.03765463467090966, -0.051524150324978882,
      -0.0583397505349211, -0.060368126927356422, -0.059251392882183618,
      -0.056166818881240636, -0.051945993134741061, -0.047167029317636916,
      -0.042221681054821332, -0.037367765985982071, -0.032766476384474962,
      -0.028511009469214983, -0.02464726441772545, -0.021188509905362661,
      -0.018127432909101581, -0.015443116301668386, -0.013107480343915318,
      -0.011088381580101829, -0.009352493222704622, -0.00786767799458982,
      -0.0066024499336939484, -0.005528815135444576, -0.0046204542890291734,
      -0.0038542396116830291, -0.0032096914143970967, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopter_10_4_DW.x_star_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_10_4_DW.x_star_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_10_4_DW.x_star_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopter_10_4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopter_10_4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopter_10_4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopter_10_4_X.Integrator_CSTATE = helicopter_10_4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopter_10_4_DW.TimeStampA = (rtInf);
  helicopter_10_4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_10_4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_10_4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_10_4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_10_4_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopter_10_4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_10_4_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((helicopter_10_4_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (helicopter_10_4_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_10_4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_10_4_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_10_4_DW.HILInitialize_Card
                         , helicopter_10_4_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , helicopter_10_4_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_10_4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_10_4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopter_10_4_DW.HILInitialize_Card,
            helicopter_10_4_P.HILInitialize_analog_output_cha,
            num_final_analog_outputs,
            &helicopter_10_4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopter_10_4_DW.HILInitialize_Card,
            helicopter_10_4_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &helicopter_10_4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_10_4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_10_4_DW.HILInitialize_Card);
    hil_close(helicopter_10_4_DW.HILInitialize_Card);
    helicopter_10_4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_10_4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elev.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file elev.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error reopening MAT-file elev.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2, helicopter_10_4_DW.ToFile_IWORK.Count,
           "elev")) {
        rtmSetErrorStatus(helicopter_10_4_M,
                          "Error writing header for elev to MAT-file elev.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_10_4_M, "Error closing MAT-file elev.mat");
        return;
      }

      helicopter_10_4_DW.ToFile_PWORK.FilePtr = (NULL);
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
  helicopter_10_4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_10_4_update();
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
  helicopter_10_4_initialize();
}

void MdlTerminate(void)
{
  helicopter_10_4_terminate();
}

/* Registration function */
RT_MODEL_helicopter_10_4_T *helicopter_10_4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_10_4_P.Integrator_UpperSat = rtInf;
  helicopter_10_4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_10_4_M, 0,
                sizeof(RT_MODEL_helicopter_10_4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_10_4_M->solverInfo,
                          &helicopter_10_4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_10_4_M->solverInfo, &rtmGetTPtr(helicopter_10_4_M));
    rtsiSetStepSizePtr(&helicopter_10_4_M->solverInfo,
                       &helicopter_10_4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_10_4_M->solverInfo,
                 &helicopter_10_4_M->ModelData.derivs);
    rtsiSetContStatesPtr(&helicopter_10_4_M->solverInfo, (real_T **)
                         &helicopter_10_4_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_10_4_M->solverInfo,
      &helicopter_10_4_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_10_4_M->solverInfo, (&rtmGetErrorStatus
      (helicopter_10_4_M)));
    rtsiSetRTModelPtr(&helicopter_10_4_M->solverInfo, helicopter_10_4_M);
  }

  rtsiSetSimTimeStep(&helicopter_10_4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_10_4_M->ModelData.intgData.f[0] = helicopter_10_4_M->
    ModelData.odeF[0];
  helicopter_10_4_M->ModelData.contStates = ((real_T *) &helicopter_10_4_X);
  rtsiSetSolverData(&helicopter_10_4_M->solverInfo, (void *)
                    &helicopter_10_4_M->ModelData.intgData);
  rtsiSetSolverName(&helicopter_10_4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_10_4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_10_4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_10_4_M->Timing.sampleTimes =
      (&helicopter_10_4_M->Timing.sampleTimesArray[0]);
    helicopter_10_4_M->Timing.offsetTimes =
      (&helicopter_10_4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_10_4_M->Timing.sampleTimes[0] = (0.0);
    helicopter_10_4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_10_4_M->Timing.offsetTimes[0] = (0.0);
    helicopter_10_4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_10_4_M, &helicopter_10_4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_10_4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_10_4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_10_4_M, 9.998);
  helicopter_10_4_M->Timing.stepSize0 = 0.002;
  helicopter_10_4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_10_4_M->Sizes.checksums[0] = (409819872U);
  helicopter_10_4_M->Sizes.checksums[1] = (3966934109U);
  helicopter_10_4_M->Sizes.checksums[2] = (648542834U);
  helicopter_10_4_M->Sizes.checksums[3] = (3957047398U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    helicopter_10_4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(helicopter_10_4_M->extModeInfo,
      &helicopter_10_4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_10_4_M->extModeInfo,
                        helicopter_10_4_M->Sizes.checksums);
    rteiSetTPtr(helicopter_10_4_M->extModeInfo, rtmGetTPtr(helicopter_10_4_M));
  }

  helicopter_10_4_M->solverInfoPtr = (&helicopter_10_4_M->solverInfo);
  helicopter_10_4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_10_4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_10_4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_10_4_M->ModelData.blockIO = ((void *) &helicopter_10_4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_10_4_B.Sum3_j[i] = 0.0;
    }

    helicopter_10_4_B.ElevationCounttorad = 0.0;
    helicopter_10_4_B.Gain = 0.0;
    helicopter_10_4_B.Sum = 0.0;
    helicopter_10_4_B.u[0] = 0.0;
    helicopter_10_4_B.u[1] = 0.0;
    helicopter_10_4_B.TravelCounttorad = 0.0;
    helicopter_10_4_B.Gain_p = 0.0;
    helicopter_10_4_B.Sum3 = 0.0;
    helicopter_10_4_B.Gain_d = 0.0;
    helicopter_10_4_B.PitchCounttorad = 0.0;
    helicopter_10_4_B.Gain_i = 0.0;
    helicopter_10_4_B.Gain_b = 0.0;
    helicopter_10_4_B.Gain_dg = 0.0;
    helicopter_10_4_B.Gain_k[0] = 0.0;
    helicopter_10_4_B.Gain_k[1] = 0.0;
    helicopter_10_4_B.Sum1 = 0.0;
    helicopter_10_4_B.Sum2 = 0.0;
    helicopter_10_4_B.K_ei = 0.0;
    helicopter_10_4_B.Gain_l = 0.0;
    helicopter_10_4_B.BackmotorSaturation = 0.0;
    helicopter_10_4_B.FrontmotorSaturation = 0.0;
  }

  /* parameters */
  helicopter_10_4_M->ModelData.defaultParam = ((real_T *)&helicopter_10_4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_10_4_X;
    helicopter_10_4_M->ModelData.contStates = (x);
    (void) memset((void *)&helicopter_10_4_X, 0,
                  sizeof(X_helicopter_10_4_T));
  }

  /* states (dwork) */
  helicopter_10_4_M->ModelData.dwork = ((void *) &helicopter_10_4_DW);
  (void) memset((void *)&helicopter_10_4_DW, 0,
                sizeof(DW_helicopter_10_4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_10_4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_10_4_DW.TimeStampA = 0.0;
  helicopter_10_4_DW.LastUAtTimeA = 0.0;
  helicopter_10_4_DW.TimeStampB = 0.0;
  helicopter_10_4_DW.LastUAtTimeB = 0.0;
  helicopter_10_4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_10_4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_10_4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_10_4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_10_4_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  helicopter_10_4_M->Sizes.numY = (0); /* Number of model outputs */
  helicopter_10_4_M->Sizes.numU = (0); /* Number of model inputs */
  helicopter_10_4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_10_4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_10_4_M->Sizes.numBlocks = (64);/* Number of blocks */
  helicopter_10_4_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  helicopter_10_4_M->Sizes.numBlockPrms = (154);/* Sum of parameter "widths" */
  return helicopter_10_4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
